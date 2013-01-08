namespace MSG
{
    public class DefaultFileLogger : Logger
    {
        public override void HandleLog(string log)
        {
            System.Console.Write(log);
        }
    }
}