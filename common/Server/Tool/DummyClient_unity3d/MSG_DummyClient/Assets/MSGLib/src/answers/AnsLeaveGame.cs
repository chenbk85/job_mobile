using MSG.Protocol;
namespace MSG
{
	/**  사용자가 게임에서 내보내질때 오는 메시지 */
	/**  클라이언트가 요청해서 게임서버가 나가기를 허가하는 경우와 */
	/**  게임서버에서 독단적으로 내보내기로 결정할때 온다. */
	/**  게임 서버와의 접속이 끊어지게 되고, 게임중에서 게임 로그인 상태로 상태가 바뀐다. */
	/**   */
	/**  @warning GameID가 본인이 아닌 경우 그냥 포워딩만 해준다. */
	/**  @warning 이 메시지가 발생하는 상황에서 클라이언트가 끊어져 전달 못하는 경우 게이트웨이는 종료된다 */
	/**  @warning KickType이 Kill인 경우 게이트웨이가 바로 종료된다 */
	public class AnsLeaveGame
	{
		public enum KickTypeEnum
		{
			ExitReservation,
			LimitMoney,
			Allin,
			SystemError,
			KickZero,
			Purge,				/** 강퇴처리 */
			Kill 				/** 게이트웨이 종료  */
		}
		/**  게임에서 나가게 된 사용자의 USN  */
		public long GameID { get; set; }
		/**  나가게 된 사유 코드 */
		public KickTypeEnum KickType { get; set; }
		/**  나가게 된 사유 정보 */
		public byte[] LeaveInfo { get; set; }
	}
}