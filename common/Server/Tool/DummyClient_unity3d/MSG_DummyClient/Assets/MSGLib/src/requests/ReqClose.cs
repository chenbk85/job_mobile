using MSG.Protocol;
namespace MSG
{
	/**  @brief 게이트웨이의 종료 요청 메시지 - 강제 접속 해지해도 되지만  */
	/**          명시적으로 접속을 종료하기 위한 요청 */
	/**  */
	/**  @warning 게임에 접속이 되어있으면 나가지 못해서 요청을 무시당한다. */

	public class ReqClose : AbstractRequest
	{
		public ReqClose(){}
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQCLOSE,
				reqClose = new UReqClose()
			};
			return request;
		}
		
	}
}