using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using SVNIntegrationNameSpace;
#pragma warning disable 0219, 0414, 0168

public static class SVNGUIControls
{
    public static GUIStyle GetPrefabToolbarStyle(GUIStyle style, bool svnRelated)
    {
        GUIStyle svnStyle = new GUIStyle(style);
        if (svnRelated)
        {
            svnStyle.fontStyle = FontStyle.Bold;
        }
        return svnStyle;
    }

    public static void SVNStatusGUI(GUIStyle style, SVNStatus svnStatus, Object obj, bool showAddCommit, bool showLockBypass, bool showRevert)
    {
        bool svnBusy = SVNCommands.instance.svnBusy;
        using (new PushState<bool>(GUI.enabled, !svnBusy, v => GUI.enabled = v))
        {
            if (svnStatus.lockStatus == ESVNLockStatus.LockedHere || svnStatus.bypassRevisionControl || !SVNUtility.ManagedByRepository(svnStatus))
            {
                if (!svnStatus.bypassRevisionControl && SVNUtility.GetAssetPath(obj) != "" && showAddCommit)
                {
                    if (GUILayout.Button((SVNUtility.ManagedByRepository(svnStatus) ? SVNTerminoligy.commit : SVNTerminoligy.add), GetPrefabToolbarStyle(style, true)))
                    {
                        SVNUtility.CommitPrefab(obj, SVNTerminoligy.commit + " from Inspector");
                    }
                }
            }

            if (!SVNUtility.HaveSVNLock(svnStatus) && SVNUtility.ManagedByRepository(svnStatus) && showLockBypass)
            {
                if (svnStatus.lockStatus != ESVNLockStatus.LockedOther)
                {
                    if (GUILayout.Button(SVNTerminoligy.getlock, GetPrefabToolbarStyle(style, true)))
                    {
                        SVNUtility.GetSVNLock(obj);
                    }
                }
                if (!svnStatus.bypassRevisionControl)
                {
                    if (GUILayout.Button(SVNTerminoligy.bypass, GetPrefabToolbarStyle(style, true)))
                    {
                        SVNUtility.SetBypass(obj);
                    }
                }
            }

            if (showRevert)
            {
                if (GUILayout.Button(SVNTerminoligy.revert, GetPrefabToolbarStyle(style, SVNUtility.ShouldSVNRevert(obj))))
                {
                    SVNUtility.Revert(obj);
                }
            }
        }
    }


    public static string GetObjectTypeName(Object obj)
    {
        string objectType = "Unknown Type";
        if (SVNUtility.IsPrefab(obj, false, true, true)) objectType = "Model";
        if (SVNUtility.IsPrefab(obj, true, false, true)) objectType = "Prefab";
        if (!SVNUtility.IsPrefab(obj, true, true, true)) objectType = "Scene";

        if (SVNUtility.IsPrefabParent(obj)) objectType += " Asset";
        else if (SVNUtility.IsPrefabRoot(obj)) objectType += " Root";
        else objectType += " Child";

        return objectType;
    }

    public static GUIStyle GetSVNBox(SVNStatus svnStatus)
    {
        var prefabBoxStyle = new GUIStyle(GUI.skin.box);
        prefabBoxStyle.border = new RectOffset(2, 2, 2, 2);
        prefabBoxStyle.padding = new RectOffset(1, 1, 1, 1);
        prefabBoxStyle.normal.background = GetSVNBackgroundTexture(svnStatus);
        return prefabBoxStyle;
    }

    public static Texture2D GetSVNBackgroundTexture(SVNStatus svnStatus)
    {
        if (svnStatus.bypassRevisionControl) return BackgroundTextures.instance.bypassTexture;
        if (SVNUtility.ManagedByRepository(svnStatus))
        {
            if (svnStatus.lockStatus == ESVNLockStatus.NoLock) return BackgroundTextures.instance.noLockTexture;
            if (svnStatus.lockStatus == ESVNLockStatus.LockedHere) return BackgroundTextures.instance.lockedTexture;
            if (svnStatus.lockStatus == ESVNLockStatus.LockedOther) return BackgroundTextures.instance.lockedByOtherTexture;
        }
        return BackgroundTextures.instance.noSVNTexture;
    }

    public static GUIStyle GetLockStatusStyle(SVNStatus svnStatus)
    {
        return new GUIStyle(EditorStyles.boldLabel) { alignment = TextAnchor.MiddleCenter };
    }

    public static string GetLockStatusMessage(SVNStatus svnStatus)
    {
        string prefabLockMessage = svnStatus.lockStatus.ToString();
        if (svnStatus.lockStatus == ESVNLockStatus.LockedOther) prefabLockMessage = SVNTerminoligy.getlock + " by: " + svnStatus.owner;
        if (svnStatus.lockStatus == ESVNLockStatus.LockedHere) prefabLockMessage = SVNTerminoligy.getlock + " Here: " + svnStatus.owner;
        if (svnStatus.lockStatus == ESVNLockStatus.NoLock)
        {
            prefabLockMessage = SVNUtility.ManagedByRepository(svnStatus) ? "Not " + SVNTerminoligy.getlock : "Not on SVN";
        }
        if (svnStatus.bypassRevisionControl)
        {
            prefabLockMessage = SVNTerminoligy.bypass;
            if ((svnStatus.lockStatus == ESVNLockStatus.LockedOther))
            {
                prefabLockMessage += " (" + SVNTerminoligy.getlock + " By: " + svnStatus.owner + " )";
            }
        }
        return prefabLockMessage;
    }

}

public sealed class BackgroundTextures
{

    private static BackgroundTextures mInstance;
    public static BackgroundTextures instance
    {
        get
        {
            if (mInstance == null) mInstance = new BackgroundTextures();
            return mInstance;
        }
    }

    private BackgroundTextures()
    {
        noSVNTexture = CreateBackgroundTexture(new Color(0.1f, 0.1f, 0.1f), new Color(0.55f, 0.55f, 0.55f));
        lockedByOtherTexture = CreateBackgroundTexture(new Color(0.1f, 0.1f, 0.1f), new Color(0.85f, 0.4f, 0.4f));
        lockedTexture = CreateBackgroundTexture(new Color(0.1f, 0.1f, 0.1f), new Color(0.4f, 0.7f, 0.4f));
        noLockTexture = CreateBackgroundTexture(new Color(0.1f, 0.1f, 0.1f), new Color(0.3f, 0.55f, 0.85f));
        bypassTexture = CreateBackgroundTexture(new Color(0.1f, 0.1f, 0.1f), new Color(0.8f, 0.6f, 0.3f));
    }

    static Texture2D CreateBackgroundTexture(Color border, Color body)
    {
        Texture2D backgroundTexture = new Texture2D(3, 3);
        backgroundTexture.hideFlags = HideFlags.HideAndDontSave;

        backgroundTexture.SetPixels(new[]{
            border, border, border,
            border,  body , border,
            border, border, border,
        });
        backgroundTexture.wrapMode = TextureWrapMode.Clamp;
        backgroundTexture.filterMode = FilterMode.Point;
        backgroundTexture.Apply();
        return backgroundTexture;
    }

    public readonly Texture2D lockedTexture;
    public readonly Texture2D noLockTexture;
    public readonly Texture2D bypassTexture;
    public readonly Texture2D noSVNTexture;
    public readonly Texture2D lockedByOtherTexture;
}

