using MSG.Protocol;
namespace MSG
{
	/**  게임서버의 룸에 입장했을 경우에 넘어오는 메시지 */
	public class AnsAutoJoin
	{
		/**  룸의 구성에 관련된 정보를 시리얼라이즈해서 넘겨준다. 게임서버에서 클라이언트와 약속해서 넘겨주는 정보. */
		public byte[] GameRoomInfo { get; set; }
	}
}