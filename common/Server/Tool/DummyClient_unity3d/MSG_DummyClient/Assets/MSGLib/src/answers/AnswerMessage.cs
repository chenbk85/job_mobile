namespace MSG
{
	/**  서버에서 보내온 메시지를 표현하는 클래스. */
	/**  @warning 요청에대한 응답은 반드시 짝이 맞는 것은 아니며 연속되게 같은 요청이  */
	/**           가는 경우 무시될 수도 있고, 처리가 불가능한 경우 에러 응답이  */
	/**           나갈 수도 있음 */
	public class AnswerMessage
	{
		/**  응답의 분류 정보. */
		public enum AnsType
		{
			None,
			Connect,
			Channel,
			Info,
			AutoJoin,
			LeaveGame,
			Close,
			Plug,
			GameProtocol,
			GatewayProtocol,
			Notice,
			DB,
			Error
		}
		
		/**  응답의 분류 정보. */
		public AnsType Type { get; set; } 
				
		public AnsConnect Connect { get; set; } /**  접속에 대한 응답 메시지 */
		public AnsChannel Channel { get; set; }	/**  채널 정보에 대한 응답 메시 */
		public AnsInfo Info { get; set; }  /**  본인 정보에 대한 응답 메시지 */
		public AnsAutoJoin AutoJoin { get; set; }  /**  게임 자동 입장에 대한 응답 메시지 */
		public AnsLeaveGame LeaveGame { get; set; }  /**  게임 나가기에 대한 응답 메시지 */
		public AnsClose Close { get; set; }  
		public AnsPlug Plug  { get; set; }  /**  재접속 허용 메시지  */
		public AnsGameProtocol GameProtocol { get; set; }  /**  게임서버에서부터 나온 게임관련 응답 메시지  */
		public AnsGatewayProtocol GatewayProtocol {get; set; }  /**  게이트웨이의 사용자 메시지에 대한 응답 */
		public AnsNotice Notice{ get; set; }  /**  공지사항 응답 메시지 */
		public AnsError Error{get;set;} /**  에러가 발생했을 경우의 처리 */
		public AnsDB DB{ get; set; }   /**  디비 요청에 대한 응답 메시지 */
	}
}