using MSG.Protocol;
namespace MSG
{
	/**  @brief 공지사항이 있는지 요구하는 메시지 */
	public class ReqNotice : AbstractRequest
	{
		public ReqNotice(){}
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQNOTICE,
				reqNotice = new UReqNotice()
			};
			return request;
		}
		
	}
}