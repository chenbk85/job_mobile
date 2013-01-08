using MSG.Protocol;
namespace MSG
{
	/**  @brief 사용자 정보 요구 메시지 */
	/**     요구하는 시점의 사용자 정보를 가져온다, 사용자 정보가 갱신되었을때 */
	/**     일괄로 가져올 수 있는 기능을 제공한다 */
	public class ReqInfo : AbstractRequest
	{
		public ReqInfo(){}
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQINFO,
				reqInfo = new UReqInfo()
			};
			return request;
		}
		
	}
}