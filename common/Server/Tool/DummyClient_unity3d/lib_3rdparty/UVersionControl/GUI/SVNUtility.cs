// Copyright (c) <2010> <Playdead>
// This file is subject to the MIT License as seen in the trunk of this repository
// Maintained by: <Kristian Kjems> <kristian.kjems+UnitySVN@gmail.com>

// This script includes common SVN related operations

using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using SVNIntegrationNameSpace;
#pragma warning disable 0219, 0414

public static class SVNUtility
{
    public static bool ChangesStoredInScene(Object obj)
    {
        return ((obj is GameObject) && !IsPrefabParent(obj) && !IsPrefab(obj, true, false, true));
    }

    public static string GetAssetPath(Object obj)
    {
        if (obj is Material) return AssetDatabase.GetAssetPath(obj);
        if (ChangesStoredInScene(obj)) return EditorApplication.currentScene;
        if (IsPrefabParent(obj)) return AssetDatabase.GetAssetPath(obj);
        return AssetDatabase.GetAssetPath(EditorUtility.GetPrefabParent(obj));
    }

    public static bool IsPrefabParent(Object go)
    {
        if (!go) return false;
        PrefabType pbtype = EditorUtility.GetPrefabType(go);
        bool isPrefabParent =
            pbtype == PrefabType.ModelPrefab ||
            pbtype == PrefabType.Prefab;

        return isPrefabParent;
    }

    public static bool IsPrefabRoot(Object obj)
    {
        var gameObject = obj as GameObject;
        if (gameObject) return EditorUtility.FindPrefabRoot(gameObject) == gameObject;
        return false;
    }

    public static bool IsPrefab(Object obj, bool includeRegular = true, bool includeModels = true, bool includeDisconnected = true)
    {
        if (!obj) return false;
        PrefabType pbtype = EditorUtility.GetPrefabType(obj);
        bool isPrefab =
            (includeRegular && pbtype == PrefabType.Prefab) ||
            (includeRegular && pbtype == PrefabType.PrefabInstance) ||
            (includeRegular && includeDisconnected && pbtype == PrefabType.DisconnectedPrefabInstance) ||
            (includeModels && pbtype == PrefabType.ModelPrefab) ||
            (includeModels && pbtype == PrefabType.ModelPrefabInstance) ||
            (includeModels && includeDisconnected && pbtype == PrefabType.DisconnectedModelPrefabInstance);
        return isPrefab;
    }

    public static void DisconnectPrefab(GameObject gameObject)
    {
        // instantiate prefab at prefab location, remove original prefab instance.
        var syncedOp = new SyncedToUpdateOperation(() =>
        {
            Undo.RegisterSceneUndo("Disconnect Prefab");
            var prefabRoot = EditorUtility.FindPrefabRoot(gameObject);
            var prefabParent = EditorUtility.GetPrefabParent(prefabRoot) as GameObject;
            string prefabName = prefabParent.name;

            var replacedPrefab = Object.Instantiate(prefabParent, prefabRoot.transform.position, prefabRoot.transform.rotation) as GameObject;
            replacedPrefab.transform.localScale = prefabRoot.transform.localScale;
            replacedPrefab.name = prefabName;
            replacedPrefab.transform.parent = prefabRoot.transform.parent;

            Object.DestroyImmediate(prefabRoot);

            Selection.activeGameObject = replacedPrefab;
            EditorUtility.UnloadUnusedAssets();
        });
        syncedOp.Queue();
        Selection.activeGameObject = null;
    }

    public static void SelectPrefab(GameObject gameObject)
    {
        var prefabParent = EditorUtility.GetPrefabParent(gameObject) as GameObject;
        Selection.activeGameObject = prefabParent;
    }

    public static void GetSVNLock(Object obj)
    {
        SVNCommands.instance.SVNGetLock(new[] { GetAssetPath(obj) }, false);
    }

    public static void SVNReleaseLock(Object obj)
    {
        SVNCommands.instance.SVNReleaseLock(new[] { GetAssetPath(obj) }, false);
    }

    public static void SetBypass(Object obj)
    {
        SVNCommands.SVNBypassRevision(new[] { GetAssetPath(obj) });
    }

    public static void ApplyPrefab(GameObject gameObject)
    {
        Undo.RegisterSceneUndo("Apply Prefab");
        var prefabParent = EditorUtility.GetPrefabParent(gameObject) as GameObject;
        EditorUtility.ReplacePrefab(gameObject, prefabParent, ReplacePrefabOptions.UseLastUploadedPrefabRoot);
        if (IsPrefab(gameObject, true, false, false)) // Connected prefab
        {
            EditorUtility.ResetGameObjectToPrefabState(gameObject);
        }
        else // Disconnected prefab
        {
            EditorUtility.ReconnectToLastPrefab(gameObject);
        }
        EditorApplication.SaveAssets();
        EditorUtility.UnloadUnusedAssets();
    }

    public static void Revert(Object obj)
    {
        var gameObject = obj as GameObject;
        if (gameObject && IsPrefab(gameObject, true, true, true) && !IsPrefabParent(gameObject))
        {
            RevertPrefab(gameObject);
        }
        else
        {
            RevertObject(obj);
        }
    }

    private static void RevertObject(Object obj)
    {
        EditorApplication.SaveAssets();
        EditorUtility.UnloadUnusedAssets();
        SVNRevert(obj);
    }

    private static void RevertPrefab(GameObject gameObject)
    {
        var syncedOp = new SyncedToUpdateOperation(() =>
        {
            EditorUtility.ReconnectToLastPrefab(gameObject);
            var prefabRoot = EditorUtility.FindPrefabRoot(gameObject);
            var prefabParent = EditorUtility.GetPrefabParent(prefabRoot) as GameObject;

            var replacedPrefab = EditorUtility.InstantiatePrefab(prefabParent) as GameObject;

            replacedPrefab.transform.position = prefabRoot.transform.position;
            replacedPrefab.transform.rotation = prefabRoot.transform.rotation;
            replacedPrefab.transform.localScale = prefabRoot.transform.localScale;
            replacedPrefab.transform.parent = prefabRoot.transform.parent;

            Object.DestroyImmediate(prefabRoot);

            Selection.activeGameObject = replacedPrefab;
            EditorUtility.UnloadUnusedAssets();
        });
        syncedOp.Queue();

        // Revert the prefab and Unity reloads it in the scene
        if (ShouldSVNRevert(gameObject)) SVNRevert(gameObject);
    }

    public static bool ShouldSVNRevert(Object obj)
    {
        var assetpath = GetAssetPath(obj);
        var svnStatus = SVNCommands.instance.GetAssetStatus(assetpath);
        var material = obj as Material;

        return
            material && ManagedByRepository(svnStatus) ||
            ((svnStatus.lockStatus == ESVNLockStatus.LockedHere || svnStatus.bypassRevisionControl) && !SVNCommands.instance.svnBusy) &&
            IsPrefab(obj, true, false, true);
    }

    public static void CommitPrefab(Object obj, string commitMessage)
    {
        var gameObject = obj as GameObject;
        if (gameObject && !IsPrefabParent(obj)) ApplyPrefab(gameObject);
        EditorUtility.UnloadUnusedAssets();
        EditorApplication.SaveAssets();
        SVNCommands.instance.SVNCommit(new[] { GetAssetPath(obj) }, commitMessage);
    }

    public static void SVNRevert(Object obj)
    {
        SVNCommands.instance.SVNRevert(new[] { GetAssetPath(obj) }, true);
    }

    public static void RefreshEditableObject(GameObject gameObject)
    {
        var assetpath = GetAssetPath(gameObject);
        var svnStatus = SVNCommands.instance.GetAssetStatus(assetpath);

        SetEditable(gameObject, !HaveAssetControl(svnStatus) && !IsPrefabRoot(gameObject) && ManagedByRepository(svnStatus));
        foreach (var componentIt in gameObject.GetComponents<Component>())
        {
            RefreshEditableComponent(gameObject, componentIt, svnStatus);
        }
    }

    public static void RefreshEditableComponent(GameObject gameObject, Component component, SVNStatus svnStatus)
    {
        bool changesStoredInScene = ChangesStoredInScene(gameObject);
        bool sceneObjectAndNoSVNControl = !HaveAssetControl(svnStatus) && changesStoredInScene;
        bool shouldLock = !(HaveAssetControl(svnStatus) || sceneObjectAndNoSVNControl) && ManagedByRepository(svnStatus);

        SetEditable(component, shouldLock);
        var renderer = component as Renderer;
        if (renderer)
        {
            foreach (var materialIt in renderer.sharedMaterials)
            {
                SetMaterialLock(gameObject, materialIt, shouldLock);
            }
        }
    }

    public static bool MaterialIsPersistent(GameObject hostGameObject, Material material)
    {
        return true;
        //var persistentMaterial = hostGameObject.GetComponent<PersistentMaterialManager>();
        //return (persistentMaterial && persistentMaterial.IsPersistent(material));
    }

    public static void SetMaterialLock(GameObject hostGameObject, Material material, bool gameObjectLocked)
    {
        var assetpath = AssetDatabase.GetAssetPath(material);
        var svnStatus = SVNCommands.instance.GetAssetStatus(assetpath);
        bool materialIsPersistent = MaterialIsPersistent(hostGameObject, material);
        bool lockMaterial = materialIsPersistent ? gameObjectLocked : (ManagedByRepository(svnStatus) && !HaveAssetControl(svnStatus));
        SetEditable(material, lockMaterial);
    }

    public static bool HaveSVNLock(SVNStatus svnStatus)
    {
        bool isManagedByRepository = ManagedByRepository(svnStatus);
        bool hasLocalLock = svnStatus.lockStatus == ESVNLockStatus.LockedHere;
        return isManagedByRepository && hasLocalLock;
    }

    public static bool HaveAssetControl(SVNStatus svnStatus)
    {
        return HaveSVNLock(svnStatus) || svnStatus.bypassRevisionControl;
    }

    public static bool ManagedByRepository(SVNStatus svnStatus)
    {
        return
            (svnStatus.reflectionLevel == ESVNReflectionLevel.Repository ||
            svnStatus.reflectionLevel == ESVNReflectionLevel.Local) &&
            svnStatus.fileStatus != ESVNFileStatus.Unversioned;
    }

    public static void SetEditable(Object obj, bool locked)
    {
        if (obj == null) return;
        if (locked)
        {
            obj.hideFlags |= HideFlags.NotEditable;
        }
        else
        {
            obj.hideFlags &= ~HideFlags.NotEditable;
        }
    }


}
