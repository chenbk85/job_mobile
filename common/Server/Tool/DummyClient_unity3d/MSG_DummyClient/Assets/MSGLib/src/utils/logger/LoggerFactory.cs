namespace MSG
{
	public class LoggerFactory 
	{
        public static Logger MakeLogger(LoggerOption option)
        {
#if UNITY_3_0 || UNITY_3_0_0 || UNITY_3_1 || UNITY_3_2 || UNITY_3_3 || UNITY_3_4 || UNITY_3_5 || UNITY_4_0 || UNITY_4_1 || UNITY_4_2
            CompositeLogger logger = new CompositeLogger();
            if (option.isPrintEnabled)
                logger.Add(new UnityConsoleLogger());
            if (option.isWriteEnabled)
                logger.Add(new UnityFileLogger(option));
            return logger;
#else
            CompositeLogger logger = new CompositeLogger();
            if (option.isPrintEnabled)
                logger.Add(new DefaultConsoleLogger());
            if (option.isWriteEnabled)
                logger.Add(new DefaultFileLogger());
            return logger;
#endif
        }

    
    }
}
