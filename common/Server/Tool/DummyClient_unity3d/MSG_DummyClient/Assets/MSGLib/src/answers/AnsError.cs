namespace MSG
{
	/**  에러를 표현하는 클래스. */
	public class AnsError
	{
		public enum ErrorCodeEnum
		{
			VersionIncorrect,	/**  버전이 잘못됌. */
			Database, 			/**  Database 에러 */
			Internal, 			/**  내부 서버 문제 */
			AlreadyLogged, 		/**  다른 접속이 존재 */
			NotLogged, 			/**  로그인이 되어 있지 않음 */
			AlreadyPlaying, 	/**  이미 게임중임 */
			NotPlaying, 		/**  게임중이 아님 */
			CantPlugGS, 		/**  게임서버가 플러그를 거부함 */
			InvalidValue,   	/**  요청 인자가 잘못 들어올 경우 : 현재 plug때 game_id가 상이할때 */
			TimeOut,        	/**  unused */
			Undefine,        	/**  unused */
			MaxRefill,  		/** 리필 제한 */
			OverUser,  			/** 유저가 넘친다 */
			Plug,            	/**  플러그가 안됨 */
			Busy            	/**  현재는 이 패킷은 처리 못함 다시 시도할것 */
		}
		public ErrorCodeEnum ErrorCode { get; set; }
		public string ErrorInfo { get; set; }
	}
}