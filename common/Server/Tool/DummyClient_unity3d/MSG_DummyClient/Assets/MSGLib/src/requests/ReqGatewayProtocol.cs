using MSG.Protocol;
namespace MSG
{
	/** 게이트웨이에 사용자 메시지 전달 */

	public class ReqGatewayProtocol : AbstractRequest
	{
		/** 데이터 */
		public byte[] Buffer { get; set; }
		
		public ReqGatewayProtocol(){}
		public ReqGatewayProtocol(byte[] buffer)
		{
			Buffer = buffer;
		}

		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQGATEWAYPROTOCOL,
				reqGatewayProtocol = Buffer
			};
			return request;
		}
		
	}
}