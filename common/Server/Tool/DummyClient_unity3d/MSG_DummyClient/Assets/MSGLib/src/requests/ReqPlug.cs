using MSG.Protocol;
namespace MSG
{
	/**  통신 불량으로 접속이 떨어지거나 클라이언트가 오류나 기타 이유로 */
	/**  강제 종료되는 경우 다시 접속을 요구하는 메시지로 UAnsConnect에서  */
	/**  넘겨준 재접속 포트 정보로 접속을 한 후 아래의 메시지를 전송한다 */
	/**  @warning 게임아이디가 게이트웨이 원래의 주인 아이디와 안맞을 경우 접속 끊음 */
	/**  @warning 게임이 진행중이 아니면 Plug 에러를 보내고 게이트웨이 종료 */
	/**  @warning 게임서버가 플러그에 대한 응답을 주지 않으면 응답이 안보내질 수 있음 */
	public class ReqPlug : AbstractRequest
	{
		/**  접속하려는 유저의 아이디 */
		public long GameID{ get; set; }

		public ReqPlug(){}
		public ReqPlug(long gameID)
		{
			GameID = gameID;
		}
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQPLUG,
				reqPlug = new UReqPlug
				{
					gameID = GameID,
					passwd = tmpData.PlugPassword
				}
			};
			return request;
		}
		
	}
}