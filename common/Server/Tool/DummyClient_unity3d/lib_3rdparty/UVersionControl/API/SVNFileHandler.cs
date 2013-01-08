using UnityEngine;
using UnityEditor;
using System.Linq;
using System.Collections.Generic;
using SVNIntegrationNameSpace;
#pragma warning disable 0219, 0414, 0168

public class SVNFileHandler : SaveAssetsProcessor
{

    static bool DisplayConfirmationDialog(string command, string assetPath, SVNStatus svnStatus)
    {
        bool acceptOperation = true;
        if (svnStatus.lockStatus == ESVNLockStatus.LockedOther)
        {
            acceptOperation = EditorUtility.DisplayDialog(command + " on SVN?", assetPath + "\nis " + SVNTerminoligy.getlock + " by [" + svnStatus.owner + "], are you sure you want to " + command + "?", command, "Cancel");
        }
        if (acceptOperation && svnStatus.fileStatus == ESVNFileStatus.Modified)
        {
            acceptOperation = EditorUtility.DisplayDialog(command + " on SVN?", assetPath + "\nFile is modified on SVN, are you sure you want to " + command + "?", command, "Cancel");
        }
        return acceptOperation;
    }

    /*
    static AssetMoveResult OnWillMoveAsset(string from, string to)
    {
        Debug.Log("Move: " + from + " => " + to);
        var svnStatus = SVNCommands.instance.GetAssetStatus(from);
        if (SVNUtility.ManagedByRepository(svnStatus))
        {
            if (DisplayConfirmationDialog("Move", from, svnStatus))
            {
                LocalCopyMove(from, to);
                Debug.Log("AssetMoveResult.DidMove");
                return AssetMoveResult.DidMove;
            }
            Debug.Log("AssetMoveResult.FailedMove");
            return AssetMoveResult.FailedMove;
        }
        Debug.Log("AssetMoveResult.DidNotMove");
        return AssetMoveResult.DidNotMove;
    }

    static void OnWillCreateAsset(string assetPath)
    {
        Debug.Log("OnWillCreateAsset: " + assetPath);
    }

    static AssetDeleteResult OnWillDeleteAsset(string assetPath, RemoveAssetOptions option)
    {
        Debug.Log("Delete: " + assetPath);
        var svnStatus = SVNCommands.instance.GetAssetStatus(assetPath);
        if (SVNUtility.ManagedByRepository(svnStatus))
        {
            if (DisplayConfirmationDialog("Delete", assetPath, svnStatus))
            {
                SVNCommands.instance.SVNDelete(new[] { assetPath }, true, false);
                Debug.Log("AssetDeleteResult.DidDelete");
                return AssetDeleteResult.DidDelete;
            }
            Debug.Log("AssetDeleteResult.FailedDelete");
            return AssetDeleteResult.FailedDelete;
        }
        Debug.Log("AssetDeleteResult.DidNotDelete");
        return AssetDeleteResult.DidNotDelete;
    }
    */

    static void LocalCopyMove(string from, string to)
    {
        SVNCommands.instance.SVNMove(from, to, false);
    }


}
