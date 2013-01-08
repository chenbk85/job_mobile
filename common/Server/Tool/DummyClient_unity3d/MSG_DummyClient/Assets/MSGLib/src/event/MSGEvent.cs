namespace MSG
{
	public enum MSGEventType
	{
		Connected,					/** Connect나 PlugConnect를 호출하여 서버와 TCP 연결에 성공했을 때 발생하는 이벤트입니다. 연결이 끊겼다가 다시 붙었을 때에도 발생합니다.  */
		Disconnected,				/** 서버와의 TCP 연결이 끊겼을 때 발생하는 이벤트입니다. 연결이 끊기는 모든 상황에서 발생합니다. */
		RecvMessage,				/** 메시지를 받았을 떄 발생하는 이벤트입니다. 메시지를 받은 경우에는 AnswerMessage에 해당 메시지가 채워져 있는 상태로 전달됩니다. */
		ErrorRecv,					/** 메시지를 Receive 하는 도중 에러가 발생했을 떄 생기는 이벤트입니다. 해당 에러가 발생하면 연결이 끊기며, Disconnect 이벤트가 뒤따릅니다. 메시지 파싱에 실패했을때에도 발생합니다. */
		ErrorSend,					/** 메시지를 보내는 도중 에러가 발생했을 떄 생기는 이벤트입니다. 해당 에러가 발생하면 연결이 끊기며, Disconnect 이벤트가 뒤따릅니다. 메시지 Serialization에 실패했을때에도 발생합니다. */
		ErrorConnect 				/** 서버에 Connect 하는 도중 에러가 발생했을 때 생기는 이벤트입니다. Connect가 맺어지지 못한채로 에러가 발생한 것이기 떄문에, Disconnect 이벤트가 뒤따르지 않습니다. */
	}
	public class MSGEvent
	{
		

		public MSGEventType EventType { get; set; }

		public MSGConnected Connected { get; set; }
		public MSGDisconnected Disconnected { get; set; }
		public AnswerMessage RecvMessage { get; set; }
		public MSGError Error { get; set; }
		
				
		public void Cleanup()
		{
			Connected = null;
			Disconnected = null;
			RecvMessage = null;
			Error = null;
		}
		public void InitToConnected(string ip, int port)
		{
			Cleanup();
			EventType = MSGEventType.Connected;
			Connected = new MSGConnected();
			Connected.Ip = ip;
			Connected.port = port;
		}
		public void InitToDisconnected(MSGDisconnected.ReasonEnum reason)
		{
			Cleanup();
			EventType = MSGEventType.Disconnected;
			Disconnected = new MSGDisconnected();
			Disconnected.Reason = reason;
		}
		public void InitToRecvMessage(AnswerMessage protocol)
		{
			Cleanup();
			EventType = MSGEventType.RecvMessage;
			RecvMessage = protocol;
		}
		public void InitToErrorRecv(MSGError.ErrorTypeEnum errType, int errCode, string errMsg)
		{
			Cleanup();
			EventType = MSGEventType.ErrorRecv;
			Error = new MSGError();
			Error.ErrorType = errType;
			Error.ErrorCode = errCode;
			Error.ErrorMessage = errMsg;
		}
		public void InitToErrorSend(MSGError.ErrorTypeEnum errType, int errCode, string errMsg)
		{
			Cleanup();
			EventType = MSGEventType.ErrorSend;
			Error = new MSGError();
			Error.ErrorType = errType;
			Error.ErrorCode = errCode;
			Error.ErrorMessage = errMsg;
		}
		public void InitToErrorConnect(MSGError.ErrorTypeEnum errType, int errCode, string errMsg)
		{
			Cleanup();
			Error = new MSGError();
			EventType = MSGEventType.ErrorConnect;
			Error.ErrorType = errType;
			Error.ErrorCode = errCode;
			Error.ErrorMessage = errMsg;
		}
	}
}