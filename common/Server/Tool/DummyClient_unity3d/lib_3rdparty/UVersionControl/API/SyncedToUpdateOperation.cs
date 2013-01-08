// Copyright (c) <2010> <Playdead>
// This file is subject to the MIT License as seen in the trunk of this repository
// Maintained by: <Kristian Kjems> <kristian.kjems+UnitySVN@gmail.com>

// This class makes sure an operation performed is executed within the scope of 
// Unity engines update loop. This is used by the callback functions from an
// asynchronous operation that although executing on the same thread as Unity
// not necessarily execute within the update scope.

using System;
using System.Collections.Generic;


public class SyncedToUpdateOperation
{
    public SyncedToUpdateOperation(Action work)
    {
        mWork = work;
    }

    public void Queue()
    {
        SynchedToUpdateOperationManager.instance.EnqueueOperation(mWork);
    }

    Action mWork;
}

public class SynchedToUpdateOperationManager
{
    private static volatile SynchedToUpdateOperationManager mInstance;
    private static object mSyncRoot = new Object();

    public static SynchedToUpdateOperationManager instance
    {
        get
        {
            if (mInstance == null)
            {
                lock (mSyncRoot)
                {
                    if (mInstance == null)
                        mInstance = new SynchedToUpdateOperationManager();
                }
            }
            return mInstance;
        }
    }

    Queue<Action> mActionQueue = new Queue<Action>();

    private bool IsUpdateLoop()
    {

        /*
        UnityEngine.Debug.Log("Thread ID: " + System.Threading.Thread.GetDomainID() + " " + UnityEngine.Application.isEditor);
        System.Diagnostics.StackTrace stackTrace = new System.Diagnostics.StackTrace();
        System.Diagnostics.Process process = new System.Diagnostics.Process();

        System.Diagnostics.StackFrame[] stackFrames = stackTrace.GetFrames();
        foreach (var frameIt in stackFrames)
        {
            UnityEngine.Debug.Log(frameIt.ToString());
        }
        */
        return false;
    }

    public void EnqueueOperation(Action work)
    {
        if (IsUpdateLoop())
        {
            work();
        }
        else
        {
            mActionQueue.Enqueue(work);
            UnityEditor.EditorApplication.update += Update;
        }
    }

    private void Update()
    {
        while (mActionQueue.Count > 0)
        {
            var op = mActionQueue.Dequeue();
            op();
        }
        UnityEditor.EditorApplication.update -= Update;
    }

}