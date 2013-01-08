using MSG.Protocol;
namespace MSG
{
	/**  게임에서 나가기를 요청하는 필드 */
	/**  */
	/**  @warning 사용자가 UReqConnect를 전송해서 로그인 하지 않았다면 요청을 무시한다. */
	/**  @warning 게임 진행중인 경우에만 나가기가 된다, 게임에 접속하고 있지 않다면  */
	/**          메시지를 무시한다. */
	/**  @warning 나가기가 이미 진행중인 경우 재요청에 대해서는 메시지를 무시한다. */
	/**  @warning 게임서버에서 나가기를 허가하지 않은 경우 응답이 안간다. */
	public class ReqLeaveGame : AbstractRequest
	{
		/**  나갈 사용자의 USN으로 본인의 id를 보내주면 된다. 확인용 */
		public long GameID { get; set; }
		/**  게임에서 퇴장 사유를 저장 */
		public byte[] LeaveInfo { get; set; }

		public ReqLeaveGame(){}
		public ReqLeaveGame(long gameID, byte[] leaveInfo)
		{
			GameID = gameID;
			LeaveInfo = leaveInfo;
		}
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQLEAVEGAME,
				reqLeaveGame = new UReqLeaveGame()
				{
					gameID = GameID,
					kick = false,
					leave_info = LeaveInfo
				}
			};
			return request;
		}
		
	}
}