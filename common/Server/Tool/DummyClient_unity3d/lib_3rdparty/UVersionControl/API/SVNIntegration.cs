// Copyright (c) <2010> <Playdead>
// This file is subject to the MIT License as seen in the trunk of this repository
// Maintained by: <Kristian Kjems> <kristian.kjems+UnitySVN@gmail.com>

// This script uses the CommandLine wrapper for a console version of 'svn'.
// All version of svn using 'svn status -v -u --xml' returns an identical XML formated
// document containing the current state of the repository. The XML document is parsed
// and all information is stored in a hashtable with assetpath as key and a class of
// SVN state enums as value. The hashtable work as a SVNStatus database. The 
// SVNStatus database is private and not directly accesible. Any component interrested
// should subscribe to SVNDatabaseHandler event to receive a copy of the database.
// A copy is made for isolation to avoid unnecessary synchronization of shared state.

using System;
using UnityEngine;
using UnityEditor;
using System.Xml;
//using System.Xml.Linq;
using System.Linq;
using System.Collections.Generic;
using CommandLineExecution;

#pragma warning disable 0219,0414


namespace SVNIntegrationNameSpace
{

    #region SVNEnums
    public enum ESVNFileStatus
    {
        Normal,
        Added,
        Conflicted,
        Deleted,
        Ignored,
        Modified,
        Replaced,
        Unversioned,
        Missing,
        External,
        Incomplete,
        Merged,
        Obstructed,
        None,
    }

    public enum ESVNDirectoryStatus
    {
        NoModification,
        Conflicted,
        Modified
    }

    public enum ESVNRepositoryStatus // Locked status. If Locked then clean up needs to be executed
    {
        NotLocked,
        Locked
    }

    public enum ESVNScheduleStatus
    {
        None,
        Commit
    }

    public enum ESVNLockStatus
    {
        NoLock,
        LockedHere,
        LockedOther,
        LockedButStolen,
        NoLockButHasToken
    }

    public enum ESVNTreeConflictStatus
    {
        Normal,
        TreeConflict
    }

    public enum ESVNProperty
    {
        None,
        Normal,
        Conflicted,
        Modified,
    }

    public enum ESVNReflectionLevel
    {
        None,
        Local,
        Repository,
    }

    #endregion

    #region EventArgs
    public abstract class SVNDatabaseArgs : System.EventArgs
    {
    }

    public class SVNDatabaseUpdatedArgs : SVNDatabaseArgs
    {
        public SVNDatabaseUpdatedArgs(CommandLineOutput output, SVNStatusDatabase statusDatabase)
        {
            this.statusDatabase = statusDatabase;
            this.output = output;
        }
        public readonly SVNStatusDatabase statusDatabase;
        public readonly CommandLineOutput output;
    }

    public class SVNDatabaseBusyArgs : SVNDatabaseArgs
    {
        public SVNDatabaseBusyArgs(ICommandLineOperation commandlineOperation)
        {
            this.commandlineOperation = commandlineOperation;
        }
        public readonly ICommandLineOperation commandlineOperation;
    }

    public class SVNDatabaseErrorArgs : SVNDatabaseArgs
    {
        public SVNDatabaseErrorArgs(CommandLineOutput output)
        {
            this.output = output;
        }
        public readonly CommandLineOutput output;
    }
    #endregion

    public class SVNStatus
    {
        //public SVNStatus metaStatus;
        public ESVNReflectionLevel reflectionLevel;
        public ESVNFileStatus fileStatus;
        public ESVNDirectoryStatus directoryStatus;
        public ESVNRepositoryStatus repositoryStatus;
        public ESVNScheduleStatus scheduleStatus;
        public ESVNLockStatus lockStatus;
        public ESVNProperty property;
        public ESVNTreeConflictStatus treeConflictStatus;
        public string user;
        public string owner;
        public string changelist;
        public int revision;
        public int lastModifiedRevision;
        public bool bypassRevisionControl = false;
        public bool initialized = false;
    }

    interface IDelegatePriority
    {
        int priority { get; }
    }

    public sealed class SVNStatusDatabase : Dictionary<string, SVNStatus>
    {
        public SVNStatusDatabase() { }
        public SVNStatusDatabase(IDictionary<string, SVNStatus> database) : base(database, StringComparer.CurrentCultureIgnoreCase) { }
        public SVNStatus GetMetaStatus(string key)
        {
            if (!key.EndsWith(".meta"))
            {
                key = key + ".meta";
                SVNStatus svnStatus;
                return TryGetValue(key, out svnStatus) ? svnStatus : null;
            }
            if (!ContainsKey(key))
            {
                Debug.LogWarning("SVNDatabase does not contain AssetPath: " + key);
                return new SVNStatus();
            }
            return base[key];
        }
    }

    public sealed class SVNIntegration
    {
        SVNIntegration()
        {
            EditorApplication.update += EditorUpdate;
            asyncSvnStatusOperation = new AsyncCommandLineOperation(new CommandLine("svn", "status --non-interactive --xml -v -u", Application.dataPath), (source, e) =>
            {
                svnStatusDatabase.Clear();
                HandleSVNStatusUpdate(e.output, true);
            });

            syncSvnStatusOperation = new SyncCommandLineOperation(new CommandLine("svn", "status --non-interactive --xml -v -u", Application.dataPath), (source, e) =>
            {
                svnStatusDatabase.Clear();
                HandleSVNStatusUpdate(e.output, false);
            });

            asyncLocalSvnStatusOperation = new AsyncCommandLineOperation(new CommandLine("svn", "status --non-interactive --xml", Application.dataPath), (source, e) =>
            {
                HandleSVNStatusUpdate(e.output, true);
            });

            syncLocalSvnStatusOperation = new SyncCommandLineOperation(new CommandLine("svn", "status --non-interactive --xml", Application.dataPath), (source, e) =>
            {
                HandleSVNStatusUpdate(e.output, false);
            });
        }
        static readonly SVNIntegration mInstance = new SVNIntegration();
        public static SVNIntegration instance { get { return mInstance; } }


        #region SVNEnumMaps
        private static Dictionary<string, ESVNFileStatus> SVNFileStatusMap = new Dictionary<string, ESVNFileStatus>()
        {
            {"normal", ESVNFileStatus.Normal},
            {"added", ESVNFileStatus.Added},
            {"conflicted", ESVNFileStatus.Conflicted},
            {"deleted", ESVNFileStatus.Deleted},
            {"ignored", ESVNFileStatus.Ignored},
            {"modified", ESVNFileStatus.Modified},
            {"replaced", ESVNFileStatus.Replaced},
            {"unversioned", ESVNFileStatus.Unversioned},
            {"missing", ESVNFileStatus.Missing},
            {"external", ESVNFileStatus.External},
            {"incomplete", ESVNFileStatus.Incomplete},
            {"merged", ESVNFileStatus.Merged},
            {"obstructed", ESVNFileStatus.Obstructed},
            {"none", ESVNFileStatus.None},
        };

        private static Dictionary<string, ESVNProperty> SVNPropertyMap = new Dictionary<string, ESVNProperty>()
        {
            {"none", ESVNProperty.None},
            {"normal", ESVNProperty.Normal},
            {"conflicted", ESVNProperty.Conflicted},
            {"modified", ESVNProperty.Modified},
        };
        #endregion

        #region Varible declaration
        const string bypassIdentifier = "bypass";
        private bool mNeedCleanUp = false;
        private ICommandLineOperation mSVNCurrentAssetsOperation;
        private object mSVNStatusDatabaseLock = new object();
        private SVNStatusDatabase mSvnStatusDatabase = new SVNStatusDatabase();
        private SVNStatusDatabase svnStatusDatabase
        {
            get
            {
                lock (mSVNStatusDatabaseLock)
                {
                    return mSvnStatusDatabase;
                }
            }
        }

        public readonly AsyncCommandLineOperation asyncSvnStatusOperation;
        public readonly AsyncCommandLineOperation asyncLocalSvnStatusOperation;
        public readonly SyncCommandLineOperation syncSvnStatusOperation;
        public readonly SyncCommandLineOperation syncLocalSvnStatusOperation;

        public delegate void SVNDatabaseHandler(object source, SVNDatabaseArgs e);
        public event SVNDatabaseHandler SVNDatabaseUpdated;

        #endregion

        #region Private methods

        private void HandleSVNStatusUpdate(CommandLineOutput output, bool async)
        {
            var xmlResult = new XmlDocument();
            xmlResult.LoadXml(output.outputStr);
            ParseStatusResult(xmlResult);
            if (async)
            {
                var syncOp = new SyncedToUpdateOperation(() =>
                {
                    if (output.failed)
                    {
                        SendSVNErrorEvent(output);
                    }
                    AssetDatabase.Refresh();
                    OnDatabaseHandlerEvent(new SVNDatabaseUpdatedArgs(output, new SVNStatusDatabase(svnStatusDatabase)));
                });
                syncOp.Queue();
            }
            else
            {
                if (output.failed)
                {
                    SendSVNErrorEvent(output);
                }
                var syncOp = new SyncedToUpdateOperation(AssetDatabase.Refresh);
                syncOp.Queue();
                OnDatabaseHandlerEvent(new SVNDatabaseUpdatedArgs(output, new SVNStatusDatabase(svnStatusDatabase)));
            }
        }

        private void OnDatabaseHandlerEvent(SVNDatabaseArgs e)
        {
            if (SVNDatabaseUpdated != null)
            {
                var prioritySorted =
                    from callback in SVNDatabaseUpdated.GetInvocationList()
                    let delegatePriority = callback.Target as IDelegatePriority
                    let priority = (delegatePriority != null) ? delegatePriority.priority : 0
                    orderby priority descending
                    select callback;

                foreach (var callbackIt in prioritySorted)
                {
                    callbackIt.DynamicInvoke(this, e);
                }
            }
        }

        private void EditorUpdate()
        {
            if (!IsBusy() && mNeedCleanUp)
            {
                SVNCleanUp();
                mNeedCleanUp = false;
            }
        }

        private bool IsBusy()
        {
            return (mSVNCurrentAssetsOperation != null && mSVNCurrentAssetsOperation.isBusy);
        }

        private SVNStatus ParseXMLNode(XmlNode entryIt)
        {
            SVNStatus svnStatus = new SVNStatus();
            XmlElement repos_status = entryIt["repos-status"];
            if (repos_status != null)
            {
                svnStatus.reflectionLevel = ESVNReflectionLevel.Repository;
                XmlElement lockStatus = repos_status["lock"];
                if (lockStatus != null)
                {
                    if (lockStatus["owner"] != null) svnStatus.owner = lockStatus["owner"].InnerText;
                    svnStatus.lockStatus = ESVNLockStatus.LockedOther;
                }
            }

            XmlElement wc_status = entryIt["wc-status"];
            if (wc_status != null)
            {
                if (wc_status.Attributes["item"] == null || !SVNFileStatusMap.TryGetValue(wc_status.Attributes["item"].InnerText, out svnStatus.fileStatus)) Debug.Log("SVN: Unknown file status: " + wc_status.Attributes["item"].InnerText);
                if (wc_status.Attributes["props"] == null || !SVNPropertyMap.TryGetValue(wc_status.Attributes["props"].InnerText, out svnStatus.property)) Debug.Log("SVN: Unknown property: " + wc_status.Attributes["props"].InnerText);

                if (svnStatus.reflectionLevel == ESVNReflectionLevel.None) svnStatus.reflectionLevel = ESVNReflectionLevel.Local;
                if (wc_status.Attributes["revision"] != null) svnStatus.revision = Int32.Parse(wc_status.Attributes["revision"].InnerText);
                if (wc_status.Attributes["wc-locked"] != null && wc_status.Attributes["wc-locked"].InnerText == "true") mNeedCleanUp = true;
                if (wc_status.Attributes["tree-conflicted"] != null) svnStatus.treeConflictStatus = (wc_status.Attributes["tree-conflicted"].InnerText == "true") ? ESVNTreeConflictStatus.TreeConflict : ESVNTreeConflictStatus.Normal;

                XmlElement commit = wc_status["commit"];
                if (commit != null)
                {
                    if (commit.Attributes["revision"] != null) svnStatus.lastModifiedRevision = Int32.Parse(commit.Attributes["revision"].InnerText);
                    if (commit["author"] != null) svnStatus.user = commit["author"].InnerText;
                }

                XmlElement lockStatus = wc_status["lock"];
                if (lockStatus != null)
                {
                    if (lockStatus["owner"] != null) svnStatus.owner = lockStatus["owner"].InnerText;
                    svnStatus.lockStatus = ESVNLockStatus.LockedHere;
                }
            }

            if (svnStatus.fileStatus == ESVNFileStatus.Modified && svnStatus.lockStatus != ESVNLockStatus.LockedHere && svnStatus.property != ESVNProperty.None)
            {
                svnStatus.bypassRevisionControl = true;
            }
            svnStatus.initialized = true;
            return svnStatus;
        }



        private void ParseStatusResult(XmlDocument xmlDoc)
        {
            if (!xmlDoc.HasChildNodes) return;

            XmlNodeList entries = xmlDoc.GetElementsByTagName("entry");
            //List<XmlNode> metaEntries = new List<XmlNode>();
            foreach (XmlNode entryIt in entries)
            {
                string assetPath = ("Assets/" + entryIt.Attributes["path"].InnerText.Replace('\\', '/')).Trim();
                var svnStatus = ParseXMLNode(entryIt);
                if (svnStatus.reflectionLevel != ESVNReflectionLevel.None)
                {
                    lock (mSVNStatusDatabaseLock)
                    {
                        mSvnStatusDatabase[assetPath] = svnStatus;
                    }
                }
            }

            XmlNodeList changelists = xmlDoc.GetElementsByTagName("changelist");
            foreach (XmlNode changelistIt in changelists)
            {
                string changelist = changelistIt.Attributes["name"].InnerText;
                foreach (XmlNode entryIt in changelistIt.ChildNodes)
                {
                    string assetPath = ("Assets/" + entryIt.Attributes["path"].InnerText.Replace('\\', '/')).Trim();
                    lock (mSVNStatusDatabaseLock)
                    {
                        if (mSvnStatusDatabase.ContainsKey(assetPath))
                        {
                            mSvnStatusDatabase[assetPath].changelist = changelist;
                            if (changelist == bypassIdentifier)
                            {
                                mSvnStatusDatabase[assetPath].bypassRevisionControl = true;
                            }
                        }
                    }
                }
            }

            foreach (var keyIt in mSvnStatusDatabase.Keys)
            {
                if (mSvnStatusDatabase.GetMetaStatus(keyIt) == null && keyIt != "Assets/.") Debug.LogWarning("Missing Meta: " + keyIt);
            }

            //Debug.Log("SVN Database updated. Number of elements: [" + m_svnStatusMap.Count + "]");

        }

        private void SendSVNErrorEvent(CommandLineOutput output)
        {
            if (output.failed)
            {
                OnDatabaseHandlerEvent(new SVNDatabaseErrorArgs(output));
            }
        }

        #endregion

        public void SVNCleanUp()
        {
            Debug.Log("SVNCleanUp");
            EditorUtility.UnloadUnusedAssets();
            ExecuteSVNAction(new[]{
                CreateSVNAction("cleanup", true),                
                asyncLocalSvnStatusOperation
            });
        }

        public void SVNBypassRevision(IEnumerable<string> assets)
        {
            EditorUtility.UnloadUnusedAssets();
            ExecuteSVNAction(new[]{
                CreateSVNAction("changelist " + bypassIdentifier, true, assets),                
                asyncSvnStatusOperation
            });
        }

        public CommandLineOperation CreateSVNAction(string action, bool asynchronous = true)
        {
            return CreateSVNAction(action, asynchronous, new string[] { });
        }

        public CommandLineOperation CreateSVNAction(string action, bool asynchronous, IEnumerable<string> assets)
        {
            return CreateSVNAction(action, asynchronous, assets, (source, e) =>
            {
                if (asynchronous)
                {
                    var syncOp = new SyncedToUpdateOperation(() =>
                    {
                        if (e.output.failed)
                        {
                            SendSVNErrorEvent(e.output);
                        }
                        OnDatabaseHandlerEvent(new SVNDatabaseUpdatedArgs(e.output, new SVNStatusDatabase(svnStatusDatabase)));
                    });
                    syncOp.Queue();
                }
                else
                {
                    if (e.output.failed)
                    {
                        SendSVNErrorEvent(e.output);
                    }
                    OnDatabaseHandlerEvent(new SVNDatabaseUpdatedArgs(e.output, new SVNStatusDatabase(svnStatusDatabase)));
                }
            });
        }

        public static CommandLineOperation CreateSVNAction(string action, bool asynchronous, IEnumerable<string> assets, CommandLine.ExecutionFinishedHandler finishedHandler)
        {
            string workingDirectory = Application.dataPath + "\\..\\";
            string arguments = action;
            if (assets.Count() > 0)
            {
                arguments += " \"" + assets.Aggregate((i, j) => i + "\" \"" + j) + "\"";
            }
            CommandLineOperation operation;
            if (asynchronous)
            {
                operation = new AsyncCommandLineOperation(new CommandLine("svn", "--non-interactive " + arguments, workingDirectory), finishedHandler);
            }
            else
            {
                operation = new SyncCommandLineOperation(new CommandLine("svn", "--non-interactive " + arguments, workingDirectory), finishedHandler);
            }

            return operation;
        }

        public void ExecuteSVNAction(ICommandLineOperation operation)
        {
            ExecuteSVNAction(new[] { operation });
        }
        public void ExecuteSVNAction(IEnumerable<ICommandLineOperation> operations)
        {
            if (!EditorApplication.isPlaying)
            {
                if (!IsBusy())
                {
                    var commandQueue = new Queue<ICommandLineOperation>();
                    foreach (var operationIt in operations)
                    {
                        commandQueue.Enqueue(operationIt);
                    }
                    var commandQueueOperation = new QueuedCommandLineOperation(commandQueue);
                    mSVNCurrentAssetsOperation = commandQueueOperation;
                    OnDatabaseHandlerEvent(new SVNDatabaseBusyArgs(mSVNCurrentAssetsOperation));
                    mSVNCurrentAssetsOperation.Execute();
                }
                else
                {
                    string request = operations.Aggregate("", (current, operationIt) => current + (operationIt + "\n"));
                    Debug.Log("Busy with: \n" + mSVNCurrentAssetsOperation + "\n\nOperation canceled: \n" + request);
                }
            }
            else
            {
                Debug.Log("SVN Action ignored during play");
            }

        }


    }
}


/*
 * 'SVN status --xml' schema
 * 
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
#
# XML RELAX NG schema for Subversion command-line client output
# For "svn status"

# The DTD compatibility annotations namespace, used for adding default
# attribute values.
namespace a = "http://relaxng.org/ns/compatibility/annotations/1.0"

include "common.rnc"

start = status

status = element status { (target | changelist)* }

target = element target { attlist.target, entry*, against? }
attlist.target &=
  ## The target path.
  attribute path { string }

changelist = element changelist { attlist.changelist, entry*, against? }
attlist.changelist &=
  ## The changelist name.
  attribute name { string }

## Status information for a path under the target.
entry = element entry { attlist.entry, wc-status, repos-status? }
attlist.entry &=
  ## Path inside the target.
  attribute path { text }

## Status of the entry in the working copy.
wc-status = element wc-status { attlist.wc-status, commit?, lock? }

attlist.wc-status &=
  ## Item/text status.
  attribute item {
    "added" | "conflicted" | "deleted" | "external" | "ignored" |
    "incomplete" | "merged" | "missing" | "modified" | "none" |
    "normal" | "obstructed" | "replaced" | "unversioned"
  },
  ## Properties status.
  attribute props { "conflicted" | "modified" | "normal" | "none" },
  ## Base revision number.
  attribute revision { revnum.type }?,
  ## WC directory locked.
  [ a:defaultValue = "false" ]
  attribute wc-locked { "true" | "false" }?,
  ## Add with history.
  [ a:defaultValue = "false" ]
  attribute copied { "true" | "false" }?,
  # Item switched relative to its parent.
  [ a:defaultValue = "false" ]
  attribute switched { "true" | "false" }?,
  ## Tree-conflict status of the item.
  [ a:defaultValue = "false" ]
  attribute tree-conflicted { "true" | "false" }?

## Status in repository (if --update was specified).
repos-status = element repos-status { attlist.repos-status, lock? }
attlist.repos-status &=
  ## Text/item status in the repository.
  attribute item {
    "added" | "deleted" | "modified" | "replaced" | "none"
  },
  ## Properties status in repository.
  attribute props { "modified" | "none" }

against = element against { attlist.against, empty }
attlist.against &=
  ## Revision number at which the repository information was obtained.
  attribute revision { revnum.type }
*/

