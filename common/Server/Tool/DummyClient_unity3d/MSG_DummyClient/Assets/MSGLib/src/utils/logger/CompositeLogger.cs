using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;
namespace MSG
{
    public class CompositeLogger : Logger
    {
        private List<Logger> mChildLoggers = new List<Logger>();

        public override void HandleLog(string log)
        {
            foreach (Logger logger in mChildLoggers)
                logger.HandleLog(log);
        }

        public void Add(Logger logger)
        {
            mChildLoggers.Add(logger);
        }

        public void Remove(Logger logger)
        {
            mChildLoggers.Remove(logger);
        }
    }
}
