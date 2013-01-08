using MSG.Protocol;

namespace MSG
{
	/**  채널 정보를 요구하는 메시지 */
	public class ReqChannel : AbstractRequest
	{
		public ReqChannel(){}
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQCHANNEL,
				reqChannel = new UReqChannel()
			};
			
			return request;
		}
	}
}