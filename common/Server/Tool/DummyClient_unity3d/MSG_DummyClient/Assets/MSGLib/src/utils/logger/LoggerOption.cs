namespace MSG
{
    public enum LogDirectoryType
    {
        Cache,
        Persistent,
        Custom
    }
    public struct LoggerOption
    {
        public bool isPrintEnabled;
        public bool isWriteEnabled;

        public string initTime;

        public LogDirectoryType type;

        //LogDirectoryType를 Custom으로 사용 할 경우
        public string customDirectoryPath;
    }
}
