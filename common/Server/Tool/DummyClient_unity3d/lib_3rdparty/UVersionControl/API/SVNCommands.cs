// Copyright (c) <2010> <Playdead>
// This file is subject to the MIT License as seen in the trunk of this repository
// Maintained by: <Kristian Kjems> <kristian.kjems+UnitySVN@gmail.com>

// This script uses the SVNIntegration and a local version of the database to issue
// SVN commands. This class does not directly interact with any asynchronously shared
// state.

using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using SVNIntegrationNameSpace;
using CommandLineExecution;

namespace SVNIntegrationNameSpace
{
    sealed public class SVNCommands : IDelegatePriority
    {
        private SVNCommands()
        {
            svnBusy = false;
            SVNIntegration.instance.SVNDatabaseUpdated += DatabaseEventHandler;
            UpdateSVNStatus();
        }
        ~SVNCommands()
        {
            SVNIntegration.instance.SVNDatabaseUpdated -= DatabaseEventHandler;
        }
        static readonly SVNCommands mInstance = new SVNCommands();
        public static SVNCommands instance { get { return mInstance; } }

        private SVNStatusDatabase mStatusDatabase;
        public bool svnBusy { get; private set; }

        #region Private methods

        private void DatabaseEventHandler(object source, SVNDatabaseArgs e)
        {
            if (e is SVNDatabaseUpdatedArgs)
            {
                var args = e as SVNDatabaseUpdatedArgs;
                mStatusDatabase = args.statusDatabase;
                svnBusy = false;
                //Debug.Log("SVNCommands Updated :  " + mStatusDatabase.Count + ", Command: svn" + args.output.arguments);
            }
            if (e is SVNDatabaseBusyArgs)
            {
                svnBusy = true;
            }
        }

        private CommandLineOperation CreateAddOperation(IEnumerable<string> assets, bool async)
        {
            var needToBeAdded =
                from asset in assets
                where !mStatusDatabase.Keys.Contains(asset) || mStatusDatabase[asset].fileStatus == ESVNFileStatus.Unversioned
                select asset;

            return needToBeAdded.Count() == 0 ? null : SVNIntegration.instance.CreateSVNAction("add", async, needToBeAdded.ToArray());
        }

        private static bool IsPathDirectory(string path)
        {
            return (File.GetAttributes(path) & FileAttributes.Directory) == FileAttributes.Directory;
        }

        private CommandLineOperation CreateCommitOperation(IEnumerable<string> assets, string commitMessage, bool async)
        {
            var needToBeCommited =
                from asset in assets
                let filestatus = mStatusDatabase[asset].fileStatus
                where filestatus != ESVNFileStatus.Normal || IsPathDirectory(asset)
                select asset;

            var command = "commit -m " + "\"" + commitMessage + "\"";
            return needToBeCommited.Count() == 0 ? null : SVNIntegration.instance.CreateSVNAction(command, async, needToBeCommited.ToArray());
        }

        private CommandLineOperation CreateLockOperation(IEnumerable<string> assets, bool force, bool async)
        {
            var needToBelocked =
                from asset in assets
                where
                    (mStatusDatabase[asset].lockStatus == ESVNLockStatus.NoLock || force) &&
                    mStatusDatabase[asset].fileStatus != ESVNFileStatus.Unversioned
                select asset;

            if (needToBelocked.Count() == 0) return null;
            return SVNIntegration.instance.CreateSVNAction("lock" + (force ? " --force" : ""), async, needToBelocked.ToArray());
        }

        private CommandLineOperation CreateUnlockOperation(IEnumerable<string> assets, bool async)
        {
            var needToBeUnlocked =
                from asset in assets
                where
                    mStatusDatabase[asset].lockStatus == ESVNLockStatus.LockedHere &&
                    mStatusDatabase[asset].fileStatus != ESVNFileStatus.Unversioned
                select asset;

            if (needToBeUnlocked.Count() == 0) return null;
            return SVNIntegration.instance.CreateSVNAction("unlock", async, needToBeUnlocked.ToArray());
        }

        private static CommandLineOperation CreateStatusOperation(bool local, bool async)
        {
            if (local)
            {
                return (async ?
                    (CommandLineOperation)SVNIntegration.instance.asyncLocalSvnStatusOperation :
                    (CommandLineOperation)SVNIntegration.instance.syncLocalSvnStatusOperation);
            }
            else
            {
                return (async ?
                    (CommandLineOperation)SVNIntegration.instance.asyncSvnStatusOperation :
                    (CommandLineOperation)SVNIntegration.instance.syncSvnStatusOperation);
            }
        }

        private static CommandLineOperation CreateMoveOperation(string from, string to, bool async)
        {

            return SVNIntegration.instance.CreateSVNAction("move", async, new[] { from, to });
        }

        private static void ExecuteSVNAction(IEnumerable<CommandLineOperation> operations)
        {
            var validOperations =
                from op in operations
                where op != null
                select op;

            SVNIntegration.instance.ExecuteSVNAction(validOperations.ToArray());
        }

        private static void ExecuteSVNAction(CommandLineOperation operation)
        {
            if (operation != null)
                SVNIntegration.instance.ExecuteSVNAction(operation);
        }

        private static void ReleaseHangingFilelocks()
        {
            EditorUtility.UnloadUnusedAssets();
        }

        #endregion

        #region Public methods

        /// <summary>Update SVN status asynchronously</summary>
        public void UpdateSVNStatus()
        {
            if (!svnBusy)
            {
                ExecuteSVNAction(SVNIntegration.instance.asyncSvnStatusOperation);
            }
        }

        public static void UpdateSVNStatusSync()
        {
            ExecuteSVNAction(SVNIntegration.instance.syncSvnStatusOperation);
        }

        /// Synchronous SVN status update
        public static void UpdateLocalSVNStatus()
        {
            ExecuteSVNAction(SVNIntegration.instance.syncLocalSvnStatusOperation);
        }

        public SVNStatus GetAssetStatus(string assetPath)
        {
            if (mStatusDatabase == null || (mStatusDatabase.Count == 0 && !svnBusy))
            {
                UpdateSVNStatus();
            }
            else if (mStatusDatabase.ContainsKey(assetPath))
            {
                return mStatusDatabase[assetPath];
            }
            else
            {
                //Debug.Log("Asset not found in SVN database: " + assetPath);
            }
            return new SVNStatus();
        }

        public static void SVNUpdate()
        {
            ReleaseHangingFilelocks();
            ExecuteSVNAction(new[]{
                SVNIntegration.instance.CreateSVNAction("--force update", true),                
                SVNIntegration.instance.asyncSvnStatusOperation
            });
        }

        private IEnumerable<string> AddFolders(IEnumerable<string> assets)
        {
            var assetFolders =
                from asset in assets
                let directoryName = Path.GetDirectoryName(asset)
                where GetAssetStatus(directoryName).fileStatus != ESVNFileStatus.Normal
                select directoryName;

            return assets.Concat(assetFolders).Distinct();
        }

        private IEnumerable<string> AddMeta(IEnumerable<string> assets)
        {
            List<string> metaFiles = new List<string>();
            foreach (string assetPathIt in assets)
            {
                if (!assetPathIt.EndsWith(".meta"))
                {
                    var metaAssetPath = assetPathIt + ".meta";
                    var metaStatus = mStatusDatabase.GetMetaStatus(metaAssetPath);
                    if (metaStatus.fileStatus != ESVNFileStatus.Normal)
                    {
                        metaFiles.Add(metaAssetPath);
                    }
                }
            }
            return assets.Concat(metaFiles);
        }


        private static void TryGetLock(IEnumerable<string> assets)
        {
            var bypassAssets = assets.Where(asset => instance.GetAssetStatus(asset).bypassRevisionControl).ToArray();
            if (bypassAssets.Length > 0)
            {
                string bypassList = bypassAssets.Aggregate((i, j) => i + "\n" + j);
                if (EditorUtility.DisplayDialog("Get Lock?", "Try and get lock for following unlocked assets?\n\n" + bypassList, "Yes", "No"))
                {
                    instance.SVNGetLock(bypassAssets.ToArray(), false);
                }
            }
        }

        private static bool UserAcceptCommit(IEnumerable<string> assets)
        {
            string depList = assets.Count() > 0 ? assets.Aggregate((i, j) => i + "\n" + j) : "";
            return EditorUtility.DisplayDialog("Commit files?", "Commit following files and directories?\n\n" + depList, "Yes", "No");
        }

        private static IEnumerable<string> GetDependencies(IEnumerable<string> assetPaths)
        {
            return AssetDatabase.GetDependencies(assetPaths.ToArray())
                .Where(dep => instance.GetAssetStatus(dep).fileStatus != ESVNFileStatus.Normal)
                .Except(assetPaths.Select(ap => ap.ToLowerInvariant()));
        }


        private static IEnumerable<string> AddDependencies(IEnumerable<string> assets)
        {
            var dependencies = GetDependencies(assets);
            if (dependencies.Count() > 0)
            {
                string depList = dependencies.Aggregate((i, j) => i + "\n" + j);
                // TODO: Improve by adding the ability to select amoung the dependencies.
                if (EditorUtility.DisplayDialog("Add Following Dependencies?", depList, "Yes", "No"))
                {
                    assets = assets.Concat(dependencies);
                }
            }
            return assets;
        }

        public void SVNCommit(IEnumerable<string> assets, string commitMessage, bool async = true)
        {
            if (assets.Count() > 0)
            {
                if (assets.Contains(EditorApplication.currentScene))
                {
                    EditorApplication.SaveCurrentSceneIfUserWantsTo();
                }
                assets = AddDependencies(assets);
                TryGetLock(assets);
                assets = AddFolders(assets);
                EditorApplication.SaveAssets();
                ReleaseHangingFilelocks();
                UpdateLocalSVNStatus();

                if (UserAcceptCommit(assets))
                {
                    foreach (string assetPathIt in assets)
                    {
                        if (mStatusDatabase[assetPathIt].bypassRevisionControl)
                        {
                            Debug.LogError("Commit Aborted: Tried to commit a file marked as bypass revision control: " + assetPathIt);
                            return;
                        }
                    }
                    assets = AddMeta(assets);
                    ExecuteSVNAction(new[]
                    {
                        CreateAddOperation(assets, async),
                        CreateCommitOperation(assets, commitMessage, async),
                        CreateUnlockOperation(assets, async),
                        CreateStatusOperation(false, async),
                    });
                }
            }
        }

        public void SVNAdd(IEnumerable<string> assets)
        {
            if (assets.Count() > 0)
            {
                ReleaseHangingFilelocks();
                assets = AddMeta(assets);
                CreateAddOperation(assets, true);
            }
        }

        public void SVNRevert(IEnumerable<string> assets, bool async = true)
        {
            if (assets.Count() > 0)
            {
                ReleaseHangingFilelocks();
                assets = AddMeta(assets);
                ExecuteSVNAction(new[]{
                    SVNIntegration.instance.CreateSVNAction("revert -R", async, assets),
                    CreateUnlockOperation(assets, async),                        
                    SVNIntegration.instance.CreateSVNAction("changelist --remove", async, assets),
                    CreateStatusOperation(false, async),
                });
            }
        }

        public void SVNDelete(IEnumerable<string> assets, bool force = false, bool async = false)
        {
            if (assets.Count() > 0)
            {
                ReleaseHangingFilelocks();
                assets = AddMeta(assets);
                var svnDeleteAssets = new List<string>();
                foreach (string assetIt in assets)
                {
                    SVNStatus svnStatus;
                    if (mStatusDatabase.TryGetValue(assetIt, out svnStatus) && svnStatus.fileStatus != ESVNFileStatus.Unversioned)
                    {
                        svnDeleteAssets.Add(assetIt);
                    }
                    else
                    {
                        if (!AssetDatabase.DeleteAsset(assetIt))
                        {
                            File.Delete(assetIt);
                        }
                    }
                }
                if (svnDeleteAssets.Count > 0)
                {
                    ExecuteSVNAction(new[]{
                        SVNIntegration.instance.CreateSVNAction("delete" + (force?" --force":""), async, svnDeleteAssets.ToArray()),   
                        CreateStatusOperation(false, async)
                   });
                }
                else
                {
                    UpdateSVNStatus();
                }
            }
        }

        public void SVNGetLock(IEnumerable<string> assets, bool async = true)
        {
            SVNGetLock(assets, false, async);
        }

        public void SVNGetLock(IEnumerable<string> assets, bool force, bool async)
        {
            if (assets.Count() > 0)
            {
                ReleaseHangingFilelocks();
                ExecuteSVNAction(new[]{
                    SVNIntegration.instance.CreateSVNAction("changelist --remove", async, assets),
                    CreateLockOperation(assets, force, async),                                    
                    SVNIntegration.instance.syncLocalSvnStatusOperation,
                });
            }
        }

        public void SVNReleaseLock(IEnumerable<string> assets, bool async = true)
        {
            if (assets.Count() > 0)
            {
                ReleaseHangingFilelocks();
                ExecuteSVNAction(new[]{
                    CreateUnlockOperation(assets, async),                
                    SVNIntegration.instance.asyncSvnStatusOperation
                });
            }
        }

        public static void SVNResolve(IEnumerable<string> assets, bool async, bool theirs)
        {
            if (assets.Count() > 0)
            {
                string conflictparameter = theirs ? "--accept theirs-full" : "--accept mine-full";
                ExecuteSVNAction(new[]{
                    SVNIntegration.instance.CreateSVNAction("resolve "+conflictparameter, async, assets),                                
                });
            }
        }

        public void SVNMove(string from, string to, bool async)
        {
            string toPath = Path.GetDirectoryName(to);
            bool isAssetFolder = toPath.Equals("Assets", System.StringComparison.OrdinalIgnoreCase);
            ExecuteSVNAction(new[]{
                (isAssetFolder)?null:CreateAddOperation(new[]{toPath, toPath+".meta"}, async),
                CreateMoveOperation(from, to, async),
                CreateMoveOperation(from+".meta", to+".meta", async),
                CreateStatusOperation(true, true),
            });
        }

        public static void SVNBypassRevision(IEnumerable<string> assets)
        {
            SVNIntegration.instance.SVNBypassRevision(assets);
        }

        public void SVNCleanUp()
        {
            SVNIntegration.instance.SVNCleanUp();
        }

        #endregion

        public int priority
        {
            get { return int.MaxValue; }
        }
    }
}
