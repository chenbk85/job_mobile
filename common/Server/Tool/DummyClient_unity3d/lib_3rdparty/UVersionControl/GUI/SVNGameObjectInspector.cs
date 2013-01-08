// Copyright (c) <2010> <Playdead>
// This file is subject to the MIT License as seen in the trunk of this repository
// Maintained by: <Kristian Kjems> <kristian.kjems+UnitySVN@gmail.com>

// The script overrides Unity's inspector for GameObjects to include the state
// of the resource on the repository.
// SVNCommands is used to get state and execute commands on the repository.

using System.Linq;
using UnityEngine;
using UnityEditor;
using SVNIntegrationNameSpace;

#pragma warning disable 0219, 0414, 0168

[CustomEditor(typeof(GameObject))]
public class SVNGameObjectInspector : Editor, IDelegatePriority
{
    SVNStatus mSVNStatus = new SVNStatus();
    string mAssetpath = "";
    GameObject mGameObject;
    bool mSVNBusy = false;
    private bool mGUIStateIsStatic;
    private int mGUIStateLayer;
    private string mGUIStateTag;

    void OnEnable()
    {
        //Debug.Log("Enable: SVNLock_GameObject");
        if (SVNActiveForObject())
        {
            mGameObject = target as GameObject;
            RefreshFromDatabase();
            SVNIntegration.instance.SVNDatabaseUpdated += RefreshGUI;
        }
    }

    void OnDisable()
    {
        SVNIntegration.instance.SVNDatabaseUpdated -= RefreshGUI;
    }

    public override void OnInspectorGUI()
    {
        if (SVNActiveForObject())
        {
            DrawDefaultGameObjectGUI();
            EditorGUILayout.BeginVertical(SVNGUIControls.GetSVNBox(mSVNStatus));
            DrawSVNStatusGUI();
            if (EditorUtility.GetPrefabType(mGameObject) != PrefabType.None)
            {
                DrawPrefabGUI();
            }
            EditorGUILayout.EndVertical();
        }
    }

    bool SVNActiveForObject()
    {
        return ((target as GameObject).tag != "IgnoreSVN");
    }

    void RefreshGUI(object source, SVNDatabaseArgs e)
    {
        if (e is SVNDatabaseUpdatedArgs)
        {
            //var args = e as SVNDatabaseUpdatedArgs;
            //Debug.Log("SVNGameObject Updated : " + args.statusDatabase.Count + ", Command: svn" + args.output.arguments);
            mSVNBusy = false;
            RefreshFromDatabase();
            Repaint();
        }
        if (e is SVNDatabaseBusyArgs)
        {
            mSVNBusy = true;
            Repaint();
        }
    }

    void RefreshFromDatabase()
    {
        mAssetpath = SVNUtility.GetAssetPath(mGameObject);
        mSVNStatus = SVNCommands.instance.GetAssetStatus(mAssetpath);
        //Debug.Log("Refresh from database: " + mAssetpath + " " + mSVNStatus.lockStatus);
    }

    void DrawDefaultGameObjectGUI()
    {
        EditorGUILayout.BeginVertical();
        EditorGUILayout.BeginHorizontal();
        GUILayout.Label(new GUIContent("Static", "Shift click to apply setting to all children"), EditorStyles.miniLabel); mGUIStateIsStatic = GUILayout.Toggle(mGameObject.isStatic, "", EditorStyles.toggle);
        if (mGUIStateIsStatic != mGameObject.isStatic)
        {
            mGameObject.isStatic = mGUIStateIsStatic;
            if (Event.current.shift)
            {
                foreach (var childIt in mGameObject.GetComponentsInChildren<Transform>())
                {
                    childIt.gameObject.isStatic = mGUIStateIsStatic;
                }
            }
        }
        GUILayout.Label("Tag", EditorStyles.miniLabel); mGUIStateTag = EditorGUILayout.TagField(mGameObject.tag);
        if (mGUIStateTag != mGameObject.tag) mGameObject.tag = mGUIStateTag;
        GUILayout.Label("Layer", EditorStyles.miniLabel); mGUIStateLayer = EditorGUILayout.LayerField(mGameObject.layer);
        if (mGUIStateLayer != mGameObject.layer) mGameObject.layer = mGUIStateLayer;
        EditorGUILayout.EndHorizontal();
        EditorGUILayout.EndVertical();
    }



    void DrawPrefabGUI()
    {
        var prefabType = EditorUtility.GetPrefabType(mGameObject);
        var prefabParent = EditorUtility.GetPrefabParent(mGameObject) as GameObject;

        EditorGUILayout.BeginHorizontal(EditorStyles.toolbar);
        GUIStyle buttonStyle = EditorStyles.toolbarButton;
        bool showAddCommit = SVNUtility.IsPrefab(mGameObject, true, false, false);
        bool showLockByPass = SVNUtility.IsPrefab(mGameObject, true, false, false);
        bool showRevert = SVNUtility.IsPrefab(mGameObject) && SVNUtility.HaveAssetControl(mSVNStatus);

        SVNGUIControls.SVNStatusGUI(buttonStyle, mSVNStatus, mGameObject, showAddCommit, showLockByPass, showRevert);
        if (!SVNUtility.IsPrefabParent(mGameObject))
        {
            if (SVNUtility.IsPrefab(mGameObject, true, false, true)) // non-model prefabs
            {
                if (GUILayout.Button("Apply", buttonStyle))
                {
                    SVNUtility.ApplyPrefab(mGameObject);
                    SVNCommands.UpdateLocalSVNStatus();
                }
            }
            if (SVNUtility.IsPrefab(mGameObject, true, false, true)) // non-model prefabs
            {
                if (GUILayout.Button("Disconnect", buttonStyle))
                {
                    SVNUtility.DisconnectPrefab(mGameObject);
                }
            }
            if (prefabParent != null) // has a prefab parent (prefab on disk)
            {
                if (GUILayout.Button("Select", buttonStyle))
                {
                    SVNUtility.SelectPrefab(mGameObject);
                }
            }
        }
        EditorGUILayout.EndHorizontal();
    }



    void DrawSVNStatusGUI()
    {
        SVNUtility.RefreshEditableObject(mGameObject);

        //GUILayout.Label("prefab type: " + EditorUtility.GetPrefabType(gameObject) + " svn: " + svnStatus.lockStatus);
        EditorGUILayout.BeginHorizontal();
        bool isModified = mSVNStatus.fileStatus == ESVNFileStatus.Modified;
        string labelPrefix = "";
        labelPrefix += (isModified ? "*" : "");
        labelPrefix += "[" + SVNGUIControls.GetObjectTypeName(mGameObject) + "] ";
        labelPrefix += SVNGUIControls.GetLockStatusMessage(mSVNStatus);
        var labelContent = new GUIContent(labelPrefix, mAssetpath);
        GUILayout.Label(labelContent, SVNGUIControls.GetLockStatusStyle(mSVNStatus));
        EditorGUILayout.EndHorizontal();
    }

    public int priority
    {
        get { return 1; }
    }
}

