// Copyright (c) <2010> <Playdead>
// This file is subject to the MIT License as seen in the trunk of this repository
// Maintained by: <Kristian Kjems> <kristian.kjems+UnitySVN@gmail.com>

// This script is a window to display local changes and to perform commands on 
// the repository like updating and committing files.
// SVNIntegration is used to get state and execute commands on the repository.
//
// Although functional the general quality of this file is poor and need a refactor

using System;
using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using SVNIntegrationNameSpace;
using CommandLineExecution;
using Object = UnityEngine.Object;


public class SVNWindow : EditorWindow, IDelegatePriority
{

    [MenuItem("Window/SVN")]
    static public void Init()
    {
        EditorWindow.GetWindow(typeof(SVNWindow));
    }

    public enum ColumnTypeEnum
    {
        AssetPath = 0,
        Revision,
        FileStatus,
        FileType,
        LockedBy
    }

    private List<CommandLineOutput> svnCommandHistory = new List<CommandLineOutput>();

    Vector2 mScrollViewVectorEntries = Vector2.zero;
    Vector2 mScrollViewVectorLog = Vector2.zero;
    bool mSVNBusy = false;
    bool mCheckForConflicts = false;
    ColumnTypeEnum mSortbyColumn = ColumnTypeEnum.AssetPath;
    bool mReverseColumnSort = false;
    bool mShowUnversioned = true;
    string mCommitMessage = "";
    Dictionary<SVNKeyValuePair, bool> mSelectedAssets = new Dictionary<SVNKeyValuePair, bool>();
    CommandLine mCurrentSVNOperation;

    SVNStatusDatabase mSVNStatusDatabase = new SVNStatusDatabase();

    IEnumerable<SVNKeyValuePair> mKeysOfInterrest;
    IEnumerable<SVNKeyValuePair> mFilteredKeysOfInterrest;

    void LoadState()
    {
        mSortbyColumn = (ColumnTypeEnum)EditorPrefs.GetInt("SortbyColumn", 0);
        mShowUnversioned = EditorPrefs.GetBool("ShowUnversioned", true);
    }

    void SaveState()
    {
        EditorPrefs.SetInt("SortbyColumn", (int)mSortbyColumn);
        EditorPrefs.SetBool("ShowUnversioned", mShowUnversioned);
    }

    public class SVNKeyValuePair
    {
        public SVNKeyValuePair(string key, SVNStatus svnStatus)
        {
            this.key = key;
            this.svnStatus = svnStatus;
        }
        public readonly string key;
        public readonly SVNStatus svnStatus;
    }

    void UpdateKeysOfInterrest(SVNStatusDatabase statusDatabase)
    {
        var svnKeysOfInterrest =
            from keys in statusDatabase.Keys
            where !keys.EndsWith(".meta") 
            let svnStatus = statusDatabase[keys]
            let metaStatus = statusDatabase.GetMetaStatus(keys)
            where (svnStatus.fileStatus != ESVNFileStatus.Normal || svnStatus.owner != null || (metaStatus != null && metaStatus.fileStatus != ESVNFileStatus.Normal))
            orderby svnStatus.fileStatus
            select new SVNKeyValuePair(keys, svnStatus);

        mKeysOfInterrest = svnKeysOfInterrest.ToList();
        UpdateFilteringOfKeys();
    }

    void UpdateFilteringOfKeys()
    {
        mFilteredKeysOfInterrest = new List<SVNKeyValuePair>(mKeysOfInterrest.ToList());
        if (!mShowUnversioned) mFilteredKeysOfInterrest = mFilteredKeysOfInterrest.Where(k => mSVNStatusDatabase[k.key].fileStatus != ESVNFileStatus.Unversioned);

        if (mSortbyColumn == ColumnTypeEnum.AssetPath) mFilteredKeysOfInterrest = mFilteredKeysOfInterrest.OrderBy(k => k.key);
        if (mSortbyColumn == ColumnTypeEnum.FileStatus) mFilteredKeysOfInterrest = mFilteredKeysOfInterrest.OrderBy(k => mSVNStatusDatabase[k.key].fileStatus);
        if (mSortbyColumn == ColumnTypeEnum.FileType) mFilteredKeysOfInterrest = mFilteredKeysOfInterrest.OrderBy(k => GetFileType(k.key));
        if (mSortbyColumn == ColumnTypeEnum.Revision) mFilteredKeysOfInterrest = mFilteredKeysOfInterrest.OrderBy(k => mSVNStatusDatabase[k.key].revision);
        if (mSortbyColumn == ColumnTypeEnum.LockedBy) mFilteredKeysOfInterrest = mFilteredKeysOfInterrest.OrderBy(k => mSVNStatusDatabase[k.key].owner);
        if (mReverseColumnSort) mFilteredKeysOfInterrest = mFilteredKeysOfInterrest.Reverse();
    }

    bool InterrestingStatus(SVNStatus svnStatus)
    {
        return svnStatus.fileStatus != ESVNFileStatus.Normal || svnStatus.owner != null;
    }

    List<string> GetSelectedAssets()
    {
        var assetPaths = new List<SVNKeyValuePair>();
        var toBeRemoved = new List<SVNKeyValuePair>();
        foreach (KeyValuePair<SVNKeyValuePair, bool> selectedAssetIt in mSelectedAssets)
        {
            if (!mFilteredKeysOfInterrest.Contains(selectedAssetIt.Key))
            {
                toBeRemoved.Add(selectedAssetIt.Key);
                continue;
            }
            if (selectedAssetIt.Value)
            {
                assetPaths.Add(selectedAssetIt.Key);
            }
        }
        foreach (var keyIt in toBeRemoved)
        {
            mSelectedAssets.Remove(keyIt);
        }
        return assetPaths.Select(kv => kv.key).ToList();
    }

    

    void OnEnable()
    {
        SVNIntegration.instance.SVNDatabaseUpdated += RefreshGUI;
        SVNCommands.instance.UpdateSVNStatus();
        LoadState();
    }

    void OnDisable()
    {
        SVNIntegration.instance.SVNDatabaseUpdated -= RefreshGUI;
        SaveState();
    }

    private static bool ImportantSVNError(CommandLineOutput output)
    {
        if (output.errorStr.Contains("svn: warning:"))
        {
            return false;
        }
        if (output.errorStr.Contains("is not locked in this working copy"))
        {
            return false;
        }
        if (output.errorStr.Contains("is not under version control"))
        {
            return false;
        }
        return true;
    }

    void RefreshGUI(object source, SVNDatabaseArgs e)
    {
        if (e is SVNDatabaseUpdatedArgs)
        {
            var args = e as SVNDatabaseUpdatedArgs;
            mSVNBusy = false;
            mSVNStatusDatabase = args.statusDatabase;
            UpdateKeysOfInterrest(args.statusDatabase);
            svnCommandHistory.Add(args.output);
            Repaint();
            mCheckForConflicts = true;
            SaveState();
            mCurrentSVNOperation = null;
        }
        if (e is SVNDatabaseBusyArgs)
        {
            var args = e as SVNDatabaseBusyArgs;
            mCurrentSVNOperation = args.commandlineOperation.command;
            mSVNBusy = true;
            Repaint();
        }
        if (e is SVNDatabaseErrorArgs)
        {
            var args = e as SVNDatabaseErrorArgs;

            CommandLineOutput output = args.output;
            string userMessage = output.command + " " + output.arguments + "\n\n" + output.errorStr + "\nExitCode:" + output.exitcode;
            if (output.exception != null) userMessage += "\nException: \n" + output.exception.Message;
            if (ImportantSVNError(output))
            {
                Debug.LogWarning(userMessage);
                EditorUtility.DisplayDialog("SVN Warning", userMessage, "OK");
            }
            else
            {
                Debug.Log("Verbose SVN message:\n" + userMessage);
            }

        }
    }

    void HandleConflicts()
    {
        var svnKeysWithConflict = (
            from keys in mSVNStatusDatabase.Keys
            where mSVNStatusDatabase[keys].fileStatus == ESVNFileStatus.Conflicted
            select keys).ToList();

        foreach (var svnStatusKeyIt in svnKeysWithConflict)
        {
            int result = EditorUtility.DisplayDialogComplex("SVN Conflict", "There is a conflict in the file '" + svnStatusKeyIt + "'. Use 'Theirs' or 'Mine'?", "Theirs", "Mine", "Cancel");
            if (result == 0 || result == 1)
            {
                SVNCommands.SVNResolve(new string[] { svnStatusKeyIt }, false, result == 0);
            }
        }
        if (svnKeysWithConflict.Count > 0)
        {
            AssetDatabase.Refresh();
            SVNCommands.UpdateSVNStatusSync();
        }
    }

    void Update()
    {
        if (mCheckForConflicts && !mSVNBusy)
        {
            HandleConflicts();
            mCheckForConflicts = false;
        }
    }

    static string GetFileType(string assetPath)
    {
        int indexOfLastDot = assetPath.LastIndexOf(".");
        return (indexOfLastDot > 0) ? assetPath.Substring(assetPath.LastIndexOf(".") + 1) : "[folder]";
    }

    static Color GetStatusColorCode(SVNStatus svnStatus)
    {

        if (svnStatus.fileStatus == ESVNFileStatus.Unversioned) return Color.grey;
        if (svnStatus.fileStatus == ESVNFileStatus.Normal) return Color.black;
        if (svnStatus.fileStatus == ESVNFileStatus.Missing) return new Color(0.6f, 0.0f, 0.2f);
        if (svnStatus.fileStatus == ESVNFileStatus.Conflicted) return Color.red;
        if (svnStatus.fileStatus == ESVNFileStatus.Modified) return Color.blue;
        return Color.black;
    }


    void OnGUI()
    {
        EditorGUILayout.BeginVertical();
        GUILayoutOption[] buttonLayout = { GUILayout.MaxWidth(50) };
        {// Buttons at top        
            EditorGUILayout.BeginHorizontal(EditorStyles.toolbar);

            using (new PushState<bool>(GUI.enabled, !mSVNBusy, v => GUI.enabled = v))
            {
                if (GUILayout.Button(SVNTerminoligy.status, EditorStyles.toolbarButton, buttonLayout) || Event.current.keyCode == KeyCode.F5)
                {
                    EditorApplication.SaveAssets();
                    SVNCommands.instance.UpdateSVNStatus();
                }
                if (GUILayout.Button(SVNTerminoligy.update, EditorStyles.toolbarButton, buttonLayout))
                {
                    SVNCommands.SVNUpdate();
                }
                if (GUILayout.Button(SVNTerminoligy.revert, EditorStyles.toolbarButton, buttonLayout))
                {
                    EditorApplication.SaveAssets();
                    SVNCommands.instance.SVNRevert(GetSelectedAssets().ToArray());
                }
                if (GUILayout.Button(SVNTerminoligy.delete, EditorStyles.toolbarButton, buttonLayout))
                {
                    SVNCommands.instance.SVNDelete(GetSelectedAssets().ToArray());
                }
                if (GUILayout.Button(SVNTerminoligy.unlock, EditorStyles.toolbarButton, buttonLayout))
                {
                    SVNCommands.instance.SVNReleaseLock(GetSelectedAssets().ToArray());
                }
                if (GUILayout.Button(SVNTerminoligy.commit, EditorStyles.toolbarButton, buttonLayout))
                {
                    var assetsToBeCommited = GetSelectedAssets();
                    SVNCommands.instance.SVNCommit(assetsToBeCommited, mCommitMessage.Length == 0 ? "Commit from Unity" : mCommitMessage);
                }
            }

            mCommitMessage = GUILayout.TextField(mCommitMessage, EditorStyles.toolbarTextField, GUILayout.MinWidth(100), GUILayout.ExpandWidth(true));
            bool newShowUnversioned = GUILayout.Toggle(mShowUnversioned, "Unversioned", EditorStyles.toolbarButton, new GUILayoutOption[] { GUILayout.MaxWidth(80) });

            if (newShowUnversioned != mShowUnversioned)
            {
                mShowUnversioned = newShowUnversioned;
                UpdateFilteringOfKeys();
            }

            EditorGUILayout.EndHorizontal();
            EditorGUILayout.Separator();
        }

        {// SVN elements on scrollable list                  

            const int columnSpacing = 20;

            GUILayoutOption[] propertyLayout = { GUILayout.MaxWidth(75), GUILayout.Width(75) };
            GUILayoutOption[] assetPathLayout = { GUILayout.MaxWidth(600), GUILayout.Width(600) };

            var headingStyle = new GUIStyle(GUI.skin.label);
            var labelStyle = new GUIStyle(GUI.skin.label);
            //labelStyle.normal.textColor = GUI.skin.label.normal new Color(0.2f, 0.2f, 0.2f);

            var selectedLabelStyle = new GUIStyle(labelStyle);
            //selectedLabelStyle.normal.textColor = new Color(0.0f, 0.0f, 0.0f);

            { // Header 
                EditorGUILayout.BeginHorizontal();
                headingStyle.fontStyle = FontStyle.Bold;
                if (GUILayout.Button("\tAsset Path", headingStyle, assetPathLayout))
                {
                    if (mSortbyColumn == ColumnTypeEnum.AssetPath) mReverseColumnSort = !mReverseColumnSort;
                    else mReverseColumnSort = false;
                    mSortbyColumn = ColumnTypeEnum.AssetPath;
                    UpdateFilteringOfKeys();
                }
                GUILayout.Space(columnSpacing);

                //(reverseColumnSort ? "△" : "▽")
                if (GUILayout.Button("File Type", headingStyle, propertyLayout))
                {
                    if (mSortbyColumn == ColumnTypeEnum.FileType) mReverseColumnSort = !mReverseColumnSort;
                    else mReverseColumnSort = false;
                    mSortbyColumn = ColumnTypeEnum.FileType;
                    UpdateFilteringOfKeys();
                }
                GUILayout.Space(columnSpacing);


                if (GUILayout.Button("File Status", headingStyle, propertyLayout))
                {
                    if (mSortbyColumn == ColumnTypeEnum.FileStatus) mReverseColumnSort = !mReverseColumnSort;
                    else mReverseColumnSort = false;
                    mSortbyColumn = ColumnTypeEnum.FileStatus;
                    UpdateFilteringOfKeys();
                }
                GUILayout.Space(columnSpacing);


                if (GUILayout.Button("Locked By", headingStyle, propertyLayout))
                {
                    if (mSortbyColumn == ColumnTypeEnum.LockedBy) mReverseColumnSort = !mReverseColumnSort;
                    else mReverseColumnSort = false;
                    mSortbyColumn = ColumnTypeEnum.LockedBy;
                    UpdateFilteringOfKeys();
                }

                headingStyle.fontStyle = FontStyle.Normal;
                EditorGUILayout.EndHorizontal();
                EditorGUILayout.Separator();

            }
            mScrollViewVectorEntries = EditorGUILayout.BeginScrollView(mScrollViewVectorEntries, false, false);

            // List content
            if (mFilteredKeysOfInterrest != null && mFilteredKeysOfInterrest.Count() != 0)
            {
                foreach (SVNKeyValuePair svnStatusKeyIt in mFilteredKeysOfInterrest)
                {
                    if (!mSelectedAssets.ContainsKey(svnStatusKeyIt)) mSelectedAssets[svnStatusKeyIt] = false;
                    SVNStatus svnStatusValueIt = svnStatusKeyIt.svnStatus;
                    EditorGUILayout.BeginHorizontal();
                    Color previousColor = labelStyle.normal.textColor;
                    var metaStatus = mSVNStatusDatabase.GetMetaStatus(svnStatusKeyIt.key);
                    //if (metaStatus == null) Debug.Log("Missing meta file: " + svnStatusKeyIt.key);
                    bool metaModified = metaStatus!=null &&
                        metaStatus.fileStatus != ESVNFileStatus.Normal &&
                        (metaStatus.fileStatus != ESVNFileStatus.Unversioned || metaStatus.fileStatus != svnStatusValueIt.fileStatus);
                    var tooltip = Path.GetFileName(svnStatusKeyIt.key) + ":\nsvn status :\t[" + svnStatusValueIt.fileStatus + "]";
                    if (metaStatus != null) tooltip += "\nmeta status:\t[" + metaStatus.fileStatus + "]";

                    // AssetPath •
                    if (svnStatusValueIt.treeConflictStatus == ESVNTreeConflictStatus.TreeConflict) labelStyle.normal.textColor = Color.red;
                    string assetPathText = (mSelectedAssets[svnStatusKeyIt] ? "+\t" : "\t") + svnStatusKeyIt.key;
                    var assetPathContent = new GUIContent(assetPathText);
                    if (GUILayout.Button(assetPathContent, (mSelectedAssets[svnStatusKeyIt] ? selectedLabelStyle : labelStyle), assetPathLayout)) mSelectedAssets[svnStatusKeyIt] = !mSelectedAssets[svnStatusKeyIt];
                    GUILayout.Space(columnSpacing);

                    // FileType                
                    GUILayout.Label(GetFileType(svnStatusKeyIt.key), labelStyle, propertyLayout); GUILayout.Space(columnSpacing);
                    labelStyle.normal.textColor = GetStatusColorCode(svnStatusValueIt);

                    // FileStatus
                    var filestatusText = svnStatusValueIt.fileStatus + (metaModified ? "(m)" : "") + (svnStatusValueIt.bypassRevisionControl ? "*" : "");
                    var filestatusContent = new GUIContent(filestatusText, tooltip);
                    GUILayout.Label(filestatusContent, labelStyle, propertyLayout); GUILayout.Space(columnSpacing);
                    labelStyle.normal.textColor = previousColor;

                    // LockedBy
                    GUILayout.Label(svnStatusValueIt.owner, labelStyle, propertyLayout);

                    EditorGUILayout.EndHorizontal();
                }
            }

            EditorGUILayout.EndScrollView();
        }
        { // SVN message box                                
            //Debug.Log(messageHistory.Count);
            string allEntries = "";
            if (mCurrentSVNOperation != null)
            {
                allEntries = "Currently executing following command:\n" + mCurrentSVNOperation;
            }
            else
            {
                for (int i = svnCommandHistory.Count - 1; i >= 0; i--)
                {
                    if (!svnCommandHistory[i].arguments.Contains("status --non-interactive --xml"))
                        allEntries += svnCommandHistory[i].command + " " + svnCommandHistory[i].arguments + ":\n" + svnCommandHistory[i].outputStr + "-----------------------\n";
                }
            }
            EditorGUILayout.BeginVertical(GUILayout.Height(135));
            EditorGUILayout.BeginHorizontal();
            GUILayout.Label(new GUIContent("SVN Output"));
            EditorGUILayout.EndHorizontal();
            mScrollViewVectorLog = EditorGUILayout.BeginScrollView(mScrollViewVectorLog, false, false);
            float heightOfLogInPixles = Mathf.Max(100.0f, GUI.skin.window.CalcSize(new GUIContent(allEntries)).y);

            GUI.skin.box.alignment = TextAnchor.UpperLeft;
            GUILayout.Box(allEntries, GUILayout.MinHeight(heightOfLogInPixles), GUILayout.ExpandWidth(true));
            EditorGUILayout.EndScrollView();
            EditorGUILayout.EndVertical();
        }

        EditorGUILayout.EndVertical();

    }

    public int priority
    {
        get { return 1; }
    }
}

public class PushState<T> : IDisposable
{
    T mInitialValue;
    System.Action<T> mSetAction;
    public PushState(T initialValue, T temporaryValue, System.Action<T> setAction)
    {
        mInitialValue = initialValue;
        mSetAction = setAction;
        setAction(temporaryValue);
    }
    public void Dispose()
    {
        mSetAction(mInitialValue);
    }
}
