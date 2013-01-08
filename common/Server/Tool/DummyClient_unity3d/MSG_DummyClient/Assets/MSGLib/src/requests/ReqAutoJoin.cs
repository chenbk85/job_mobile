using MSG.Protocol;
namespace MSG
{
/**  게임에 참여 요청 */
/**  @warning 사용자가 UReqConnect를 전송해서 로그인 하지 않았다면 요청을 무시한다. */
/**  @warning 프리젠스 서버와 접속이 끊어져 있다면 Internal 에러를 보내준다 */
/**  @warning 이미 사용자가 게임을 하고 있다면 AlreadyPlaying이 출력된다 */
/**  @warning 프리젠스 서버에 참가할 방에 대한 정보를 요구하는데 30초 안에 응답이  */
/**           없으면 접속이 갑자기 끊어진다 */
/**  @warning 프리젠스에서 방 정보를 얻으면 게임 서버에 접속하는데 게임서버에  */
/**           접속이 실패하는 경우 접속이 갑자기 끊어진다. */
/**  @warning 게임서버에 접속이 성공한 경우라고 해도 게임서버의 응답에 따라서 */
/**           응답이 안 갈 수도 있다. */
	public class ReqAutoJoin : AbstractRequest
	{
		/**  참가할 게임의 카테고리 구분 */
		public int CategoryID { get; set; }
		/**  참가할 게임의 채널 구분 */
		public int ChannelID { get; set; }
		
		public ReqAutoJoin(){}
		public ReqAutoJoin(int categoryID, int channelID)
		{
			CategoryID = categoryID;
			ChannelID = channelID;
		}
		
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQAUTOJOIN,
				reqAutoJoin = new UReqAutoJoin
				{
					categoryID = CategoryID,
					channelID = ChannelID
				}
			};
			
			return request;
		}
	}
}