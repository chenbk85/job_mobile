namespace MSG
{
    public enum LogLevel
    {
        None,
        Info,
        Warning,
        Error,
        Debug
    }

    public abstract class Logger
    {
        private LogLevel logLevel = LogLevel.None;
        public LogLevel LogLevel
        {
            set { logLevel = value; }
            get { return logLevel; }
        }

        public abstract void HandleLog(string log);

        private void Log(LogLevel level,string log)
        {
            if (logLevel == LogLevel.None)
                return;
            else if (level <= logLevel)
            {
                var dateTime = System.DateTime.Now;
                string logData = level.ToString() + "=>" + dateTime.ToLongTimeString() + ", " + log;
                HandleLog(logData);
            }
        }

        public void i(string log)
        {
            this.Log(LogLevel.Info, log);
        }

        public void w(string log)
        {
            this.Log(LogLevel.Warning, log);
        }

        public void e(string log)
        {
            this.Log(LogLevel.Error, log);
        }

        public void d(string log)
        {
            this.Log(LogLevel.Debug, log);
        }

    }
}