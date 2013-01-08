using MSG.Protocol;
namespace MSG
{
	/** 게임서버에 포워딩해줄 메시지 */
	public class ReqGameProtocol : AbstractRequest
	{
		/** 포워딩할 데이터  */
		public byte[] Buffer{get;set;}
		
		public ReqGameProtocol(){}
		public ReqGameProtocol(byte[] buffer)
		{
			Buffer = buffer;
		}
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.GLREQGAMEPROTOCOL,
				reqGameProtocol = Buffer
			};
			return request;
		}
		
	}
}