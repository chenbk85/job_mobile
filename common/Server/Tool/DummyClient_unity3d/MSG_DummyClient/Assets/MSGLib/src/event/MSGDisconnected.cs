namespace MSG
{
	public class MSGDisconnected
	{
		public enum ReasonEnum
		{
			ByServer,
			ByClient,
			ByError
		}
		public ReasonEnum Reason { get;set; }
	}
}