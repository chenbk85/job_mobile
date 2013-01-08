namespace MSG
{
	public class MSGError
	{
		public enum ErrorTypeEnum
		{
			NotError,
			InvalidIpOrUrlOrPort,
			ErrorFromSocket,
			SocketHasBeenClosed,
			SocketNotSupported,
			InvalidSocketStatus,
			BufferError,
			ProtoBufException,
			MemoryStreamException,
			NoPermission
		}

		public ErrorTypeEnum ErrorType { get; set; }
		public int ErrorCode { get; set; }
		public string ErrorMessage { get; set; }

	}
}