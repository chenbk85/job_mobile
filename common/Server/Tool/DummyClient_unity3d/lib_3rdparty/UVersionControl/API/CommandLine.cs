// Copyright (c) <2010> <Playdead>
// This file is subject to the MIT License as seen in the trunk of this repository
// Maintained by: <Kristian Kjems> <kristian.kjems+UnitySVN@gmail.com>

// This script contain a wrapper for a commandline application.
// It is possible to execute synchronously (SyncCommandLineOperation) 
// and asynchronously (AsyncCommandLineOperation).
// There are also classes to facilitate chaining asynchronous and synchronous
// commands together (QueuedCommandLineOperation). 
// A delegate (CommandLine.ExecutionFinishedHandler) is provided to handle 
// the result from the commandline application (CommandLineOutput).

using System;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Collections.Generic;

namespace CommandLineExecution
{

    public interface ICommandLineOperation
    {
        bool isBusy { get; }
        void Execute();
        CommandLine command { get; }
    }

    public abstract class CommandLineOperation : ICommandLineOperation
    {
        protected CommandLineOperation(CommandLine command, CommandLine.ExecutionFinishedHandler finishHandler)
        {
            this.command = command;
            this.command.ExecutionFinished += finishHandler;
        }
        public CommandLine command { get; private set; }
        public bool isBusy { get { return command.isBusy; } }
        abstract public void Execute();
        public override string ToString()
        {
            return command.ToString();
        }
    }

    public class AsyncCommandLineOperation : CommandLineOperation
    {
        public AsyncCommandLineOperation(CommandLine command, CommandLine.ExecutionFinishedHandler finishHandler) : base(command, finishHandler) { }

        public override void Execute()
        {
            command.ExecuteAsync();
        }
    }

    public class SyncCommandLineOperation : CommandLineOperation
    {
        public SyncCommandLineOperation(CommandLine command, CommandLine.ExecutionFinishedHandler finishHandler) : base(command, finishHandler) { }

        public override void Execute()
        {
            command.Execute();
        }
    }

    public class QueuedCommandLineOperation : ICommandLineOperation
    {
        public QueuedCommandLineOperation(Queue<ICommandLineOperation> commandQueue)
        {
            this.commandQueue = commandQueue;
            currentCommand = this.commandQueue.Dequeue();
        }
        public CommandLine command { get { return currentCommand.command; } }
        protected readonly Queue<ICommandLineOperation> commandQueue;
        protected ICommandLineOperation currentCommand;

        public bool isBusy { get { return currentCommand.isBusy; } }

        public void Execute()
        {

            currentCommand.command.ExecutionFinished += (source, e) =>
            {
                if (commandQueue.Count > 0)
                {
                    currentCommand = commandQueue.Dequeue();
                    Execute();
                }
            };
            currentCommand.Execute();
        }

        public override string ToString()
        {
            string output = currentCommand + "\n";
            return commandQueue.Aggregate(output, (current, commandIt) => current + (commandIt + "\n"));
        }
    }



    public class AsyncCompletedEventArgs : EventArgs
    {
        protected AsyncCompletedEventArgs(Exception exception, bool cancelled)
        {
            this.exception = exception;
            this.cancelled = cancelled;
        }
        public readonly Exception exception;
        public bool cancelled;

        protected void RaiseExceptionIfNecessary()
        {
            if (exception != null)
            {
                throw exception;
            }
        }
    }

    public struct CommandLineOutput
    {
        public CommandLineOutput(string command, string arguments, string outputStr, string errorStr, int exitcode, Exception exception)
        {
            this.command = command;
            this.arguments = arguments;
            this.outputStr = outputStr;
            this.errorStr = errorStr;
            this.exitcode = exitcode;
            this.exception = exception;
        }
        public readonly string command;
        public readonly string arguments;
        public readonly string outputStr;
        public readonly string errorStr;
        public readonly int exitcode;
        public readonly Exception exception;
        public bool failed { get { return (exitcode != 0 || exception != null || errorStr.Length > 0); } }
    }

    public class CommandLineCompletedEventArgs : AsyncCompletedEventArgs
    {
        public CommandLineCompletedEventArgs(Exception exception, bool cancelled, CommandLineOutput output)
            : base(exception, cancelled)
        {
            mOutput = output;
        }
        CommandLineOutput mOutput;
        public CommandLineOutput output
        {
            get
            {
                RaiseExceptionIfNecessary();
                return mOutput;
            }
        }
    }

    public class CommandLine
    {
        public CommandLine(string command, string arguments, string workingDirectory)
        {
            mCommand = command;
            mArguments = arguments;
            mWorkingDirectory = workingDirectory;
            mIsBusy = false;
        }
        string mCommand;
        string mArguments;
        string mWorkingDirectory;
        volatile bool mIsBusy;
        Exception mException;
        object mIsBusyLock = new object();

        public bool isBusy { get { return mIsBusy; } }
        public string output { get; private set; }
        public string error { get; private set; }

        public override string ToString()
        {
            return mCommand + " " + mArguments;
        }

        public delegate void ExecutionFinishedHandler(object source, CommandLineCompletedEventArgs e);
        public event ExecutionFinishedHandler ExecutionFinished;
        protected virtual void OnExecutionFinishedHandlerEvent(CommandLineCompletedEventArgs e)
        {
            if (ExecutionFinished != null) ExecutionFinished(this, e);
        }

        public void Execute()
        {
            int exitcode = 0;
            try
            {
                var info =
                    new ProcessStartInfo
                    {
                        FileName = mCommand,
                        Arguments = mArguments,
                        WorkingDirectory = mWorkingDirectory,
                        CreateNoWindow = true,
                        UseShellExecute = false,
                        RedirectStandardError = true,
                        RedirectStandardOutput = true
                    };
                //UnityEngine.Debug.Log(info.FileName + " " + info.Arguments);
                var process = Process.Start(info);
                output = process.StandardOutput.ReadToEnd();
                error = process.StandardError.ReadToEnd();
                exitcode = process.ExitCode;
                //UnityEngine.Debug.Log(info.FileName + " " + info.Arguments + "\noutput:\n" + output + "\nerror:" + error);
            }
            catch (Exception e)
            {
                mException = e;
            }
            OnExecutionFinishedHandlerEvent(new CommandLineCompletedEventArgs(mException, false, new CommandLineOutput(mCommand, mArguments, output, error, exitcode, mException)));
        }


        public void ExecuteAsync()
        {
            lock (mIsBusyLock)
            {
                if (!mIsBusy)
                {
                    mIsBusy = true;
                    ThreadPool.QueueUserWorkItem(state =>
                    {
                        Execute();
                        lock (mIsBusyLock)
                        {
                            mIsBusy = false;
                        }
                    });
                }
                else
                {
                    throw new InvalidOperationException("Async command line operation in progress.");
                }
            }
        }
    }
}