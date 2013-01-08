using MSG.Protocol;
namespace MSG
{
	/**  사용자 정보 응답 메시지 */
	/**  */
	/**  @warning 사용자가 ReqConnect를 전송해서 로그인 하지 않았다면 요청을 무시한다. */
	/**  @warning 사용자가 게임을 진행하고 있다면 게임 정보가 변동되고 있는중이라고 가정해서 요청이 무시된다 */
	public class AnsInfo
	{
		/**  사용자의 정보가 시리얼라이즈되어서 넘어온다. 사용자 정보는 게임마다 다르기 때문에 게임 서버 제작자가 구현한대로 넘어온다. */
		public byte[] GameInfo { get; set; }
	}
}