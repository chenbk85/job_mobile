// Copyright (c) <2010> <Playdead>
// This file is subject to the MIT License as seen in the trunk of this repository
// Maintained by: <Kristian Kjems> <kristian.kjems+UnitySVN@gmail.com>

// This script includes menu items for common SVN operations


using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using System.Linq;
using SVNIntegrationNameSpace;

public class SVNMenuItems : ScriptableObject
{
    static IEnumerable<string> GetAssetPathsOfSelected()
    {
        IEnumerable<string> selectedAssets =
            from go in Selection.objects
            let assetPath = AssetDatabase.GetAssetPath(go)
            select assetPath;
        return selectedAssets.Distinct();
    }


    // Get Lock
    [MenuItem("SVN/" + SVNTerminoligy.getlock + " %L")]
    public static void SVNGetLock()
    {
        SVNCommands.instance.SVNGetLock(GetAssetPathsOfSelected().ToArray(), false);
    }

    [MenuItem("CONTEXT/GameObject/" + SVNTerminoligy.getlock)]
    static void SVNGetLockGameobjectContext(MenuCommand command)
    {
        SVNCommands.instance.SVNGetLock(new[] { SVNUtility.GetAssetPath(command.context) }, false);
    }

    [MenuItem("CONTEXT/GameObject/Force " + SVNTerminoligy.getlock)]
    static void SVNForceGetLockGameobjectContext(MenuCommand command)
    {
        string assetPath = SVNUtility.GetAssetPath(command.context);
        SVNStatus svnStatus = SVNCommands.instance.GetAssetStatus(assetPath);
        if (svnStatus.lockStatus == ESVNLockStatus.LockedOther)
        {
            if (EditorUtility.DisplayDialog("Force " + SVNTerminoligy.getlock, "Are you sure you will steal the file from: [" + svnStatus.owner + "]", "Yes", "Cancel"))
            {
                SVNCommands.instance.SVNGetLock(new[] { assetPath }, true, false);
            }
        }
    }

    [MenuItem("Assets/SVN/Open")]
    static void SVNGetLockProjectContext()
    {
        SVNCommands.instance.SVNGetLock(GetAssetPathsOfSelected().ToArray(), false);
    }


    // Commit
    [MenuItem("Assets/SVN/" + SVNTerminoligy.commit)]
    static void SVNCommitProjectContext()
    {
        SVNCommands.instance.SVNCommit(GetAssetPathsOfSelected().ToArray(), "Commit from unity");
    }

    // Revert
    [MenuItem("CONTEXT/GameObject/" + SVNTerminoligy.revert)]
    static void SVNRevertGameobjectContext(MenuCommand command)
    {
        SVNCommands.instance.SVNRevert(new[] { SVNUtility.GetAssetPath(command.context) });
    }

    [MenuItem("Assets/SVN/" + SVNTerminoligy.revert)]
    static void SVNRevertProjectContext()
    {
        Debug.Log(GetAssetPathsOfSelected().Aggregate((a, b) => a + "\n" + b));
        SVNCommands.instance.SVNRevert(GetAssetPathsOfSelected().ToArray());
    }



    // ByPass
    [MenuItem("SVN/" + SVNTerminoligy.bypass + " %K")]
    public static void SVNBypassLockOnSelected()
    {
        SVNCommands.SVNBypassRevision(GetAssetPathsOfSelected().ToArray());
    }

    [MenuItem("CONTEXT/GameObject/" + SVNTerminoligy.bypass)]
    public static void SVNBypassLockGameobjectContext(MenuCommand command)
    {
        SVNCommands.SVNBypassRevision(new[] { SVNUtility.GetAssetPath(command.context) });
    }

    [MenuItem("Assets/SVN/" + SVNTerminoligy.bypass)]
    public static void SVNBypassLockProjectContext()
    {
        SVNCommands.SVNBypassRevision(GetAssetPathsOfSelected().ToArray());
    }




    [MenuItem("SVN/Refresh")]
    public static void SVNRefresh()
    {
        SVNCommands.instance.UpdateSVNStatus();
    }

    [MenuItem("SVN/Update")]
    public static void SVNUpdate()
    {
        SVNCommands.SVNUpdate();
    }

    //[MenuItem("SVN/Test SVN")]
    public static void SVNTest()
    {
    }

    //[MenuItem("SVN/Diff Selection")]
    public static void SVNDiff()
    {
        const string assetPath = "Assets/Editor/_Playdead/Autosave.cs";
        EditorUtility.InvokeDiffTool("Working Base", assetPath, "Working Copy", assetPath, assetPath, assetPath);
    }
}
