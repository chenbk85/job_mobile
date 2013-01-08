namespace MSG
{	
	public class DefaultLogger : Logger
	{
        public override void HandleLog(string log)
		{
			System.Console.Write(log);
		}
	}
}