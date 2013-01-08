using MSG.Protocol;
namespace MSG
{
	/**  게임서버에서 재접속 허가를 낸 경우 받는 메시지 */
	public class AnsPlug
	{
		/**  재접속된 사용자 id */
		public long GameID { get; set; }
		
	}
}