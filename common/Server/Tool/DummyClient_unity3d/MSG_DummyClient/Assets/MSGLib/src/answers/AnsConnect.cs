using MSG.Protocol;
namespace MSG
{
	/**  게이트웨이가 로그인 되었음을 확인해주는 메시지. <br> */
	/**  이 메시지를 수신하면 게이트웨이와 프리젠스 서버가 클라이언트의 정체성은 확인하였고, 재접속을 위한 서비스 준비가 되었다는 의미 */
	public class AnsConnect
	{
		/**  서비스의 고유번호 (게임이 서비스되는 전체 시스템의 구분번호) */
		public int SvcID { get; set; }
		/**  접속하는 사용자의 고유번호 */
		public long GameID { get;set; }
	}
}