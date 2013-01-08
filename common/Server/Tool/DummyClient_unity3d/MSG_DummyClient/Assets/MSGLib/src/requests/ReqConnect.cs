using MSG.Protocol;

namespace MSG
{

	/**  @brief 피망 플러스에서 주어지는 유저 정보를 패킹해서 보내줌 */
		
	public class MemberInfo
	{
		/**  사용자 아이디 */
		public long GameID{ get; set; }
		/**  아바타의 이미지를 받을 수 있는 url */
		public string AvatarUrl{ get; set; }
		/**  사용자의 별명 */
		public string NickName{ get; set; }
		/**  성별이 들어있음 true : 남자, false : 여자 */
		public bool GenderOption{ get; set; }
	}
/**  @brief 접속해서 사용자의 아이덴티티를 알려주는 기능을 하는 패킷 내용 */
/**         프리젠스 서버에 사용자가 접속했음을 알려주고, 디비에서 사용자  */
/**         정보를 읽어들여 게이트웨이에 적재하는 작업을 수행한다 */
/**  */
/**  @warning 버전이 안 맞을 경우 VersionIncorrect 에러가 넘어오고  */
/**           접속을 끊어버린다. */
/**  @warning 프리젠스 서버와의 접속이 안될 경우 Internal에러가 넘어오고  */
/**           접속을 끊어버린다 */
/**  @warning 이 패킷은 프리젠스 서버의 승인을 요구한다. 이 경우 프리젠스가  */
/**           30초 이내에 응답을 주지 않은 경우 아무런 에러 전송없이 접속을  */
/**           종료한다. */
/**           그러므로 일정 시간 동안 응답이 안오고 끊어지는 경우에 대한 */
/**           대비가 필요하다 */
/**  @warning 데이터베이스에서 사용자 정보를 가져올 수 없을 때 Database를 */
/**           보내고 접속을 종료한다 */
/**  @warning 이미 접속한 경우에는 이 메시지를 무시한다 */
	public class ReqConnect : AbstractRequest
	{
		/**  서비스의 고유번호 (게임이 서비스되는 전체 시스템의 구분번호 ex: 맞고개발용:1, 포커 개발용:2 ...) */
		public int SvcID{ get; set; }
		/**  접속하는 사용자의 고유번호 */
		public long GameID{ get; set; }
		/**  클라이언트가 지원하는 버전의 정보 */
		public int Version{ get; set; }
		/**  피망플러스에서 넘어오는 정보를 변환한 자료구조 */
		public MemberInfo MemberInfo { get; set; }
		
		public ReqConnect(){}
		public ReqConnect(int svcID, long gameID, int version, MemberInfo memberInfo)
		{
			SvcID = svcID;
			GameID = gameID;
			Version = version;
			MemberInfo = memberInfo;
		}
		
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQCONNECT,
				reqConnect = new UReqConnect
				{
					svcID = SvcID,
					gameID = GameID,
					lastCloseTime = 0,
					version = new MSG.Protocol.Version
					{
						framework = Settings.FrameworkVersion,
						service = Version
					},
					memberInfo = new MSG.Protocol.MemberInfo
					{
						game_id = MemberInfo.GameID,
						avatar_url = MemberInfo.AvatarUrl,
						nick_name = MemberInfo.NickName,
						gender_option = MemberInfo.GenderOption
					}
				}
			};
			return request;
			
		}
	}	
}
