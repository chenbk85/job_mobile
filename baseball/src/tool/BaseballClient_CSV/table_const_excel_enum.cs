// 10_excel_enum.xls
namespace nEXCEL{ public class table_const_excel_enum{
public const bool b_IS_FIRST_ATTACK_USER_IS_RANDOM = false; // 선공을 랜덤하게 할지 먼저입장한 유저를 공격자로 할지.
public const bool b_IS_GIVE_DAILY_BONUS_TO_ALL = false; // 이값이 true이면 접속할때마다 무조건 일일퀘스트 보너스를 지급
public const int i_ATTACK_CHANGE_ROUND =  3 ; // 공수가 변경되는 ROUND수. 3이면 3라운드마다 공수교대됨.
public const int i_DEFAULT_USER_TEAM_COUNT =  2 ; // 기본적으로 유저가 소유할수있는 팀수
public const int i_GAMECOUNT_EXP_SINGLEPLAY_IN_DAY =  3 ; // 하루 동안 싱글 플레이로 경험치를 받을수있는 횟수
public const int i_DEFAULT_GAME_MONEY =  10000 ; // 최초게임시작시 유저에게주는 게임머니
public const int i_MAX_FRIEND =  50 ; // 최대 친구수
public const int i_MAX_FRIEND_RECORD_MONTH =  1 ; // 친구와의 경기기록은 1개월치만 보여줌. 
public const int i_MAX_PITCHER_SKILL_COUNT =  10 ; // 투수가 보유할수있는 변화구 스킬의 개수- Tbl_PitcherSkill
public const int i_MAX_PITCHER_SKILL_EQUIP =  5 ; // 투수가 게임에 들고나갈수 있는 변화구 스킬수-Tbl_PitcherSkill
public const int i_MAX_PLAYER_CREATE_NUM =  3 ; // 최대 생성가능한 선수(투수 or 타자)
public const int i_MAX_PLAYING_USER =  2 ; // 게임 플레이시 참여하는 유저수
public const int i_MAX_USER_TEAM_COUNT =  5 ; // 아이템으로 사서 확장가능한 최대 팀수
public const int i_MAX_PLAYER_SKILL_STICKER =  10 ; // 선수특수능력 스티커는 최대 10개
public const int i_MAX_BREAKING_BALL_STICKER =  10 ; // 변화구 스티커는 최대 10개
public const int i_PITCHER_THROW_POSITION_SIZE =  9 ; // 투수가 공을 던질때 공의 위치 개수 ( 3 BY 3 =9개)
public const int i_ROUND_PER_GAME =  1 ; // 총 던지게 될 한 턴의 수
public const int i_SINGLEPLAY_1ROUND_TIME_MIN =  3 ; // 한라운드 플레이에 필요한 최소시간(싱글에서 어뷰징체크용)
public const int i_THROW_PER_ROUND =  9 ; // 한 게임당 던지는 수
public const int i_TIME_CLIENT_REPEAT_SEND_PACKET =  1500 ; // 단위-msec 클라이언트가 똑같은 패킷을 연속으로 보낼수 있는 최소시간
public const int i_TIME_1_PLAYER_READY =  1 ; // 한팀만 레디시 다른팀 자동레디 시키는 시간
public const int i_TIME_ALL_PLAYER_NOT_READY =  1 ; // 모두 레디를  하지 않았을 경우 자동레디 시키는 시간
public const int i_TIME_ALL_PLAYER_READY =  1 ; // 모두 레디를  하였을 경우 5초 카운트 후 선후공 결정
public const int i_TIME_GAME_FIRST_ATTACK_DECIDE_COUNT =  1 ; // 사용자 모두 게임 진입 전 선후공 결정에 소요되는 시간은 2초이다. 
public const int i_TIME_GAME_ROUND =  1 ; // 라운드가 끝날때마다 딜레이타임. 기획팀에서 그래픽연출팀이랑 협의후 결정.
public const int i_TIME_GAME_ROUND_CHANGE_TEAM =  1 ; // 선후공결정되어 게임시작 후 선후공 체인지 시 연출시간. 기획팀에서 그래픽연출팀이랑 협의후 결정.
public const int i_TIME_GAME_ROUND_END =  1 ; // 양쪽팀모두 라운드 끝내고 게임종료패킷을 보내고자 할때 기다리는시간
public const int i_TIME_GAME_ROUND_TEAMCHANGE =  1 ; // 모든 라운드끝내고 팀이 바뀔때 기다리는시간
public const int i_TIME_PLAYER_INTRODUCE =  1 ; // 게임 진입 전 선수소개 화면의 재생 시간은 5초 카운트. 플레이어 모두 SKIP버튼  TAP시에 게임 시작. 한명만 SKIP버튼 TAP시에  상대가 게임시작을 준비하고 있습니다. 라고 출력하고 5초 그대로 카운트 
public const int i_TIME_RESULT_WHEN_AUTOPLAY =  20 ; // 게임중 한쪽이 비정상종료시 서버에서 클라가 자동플레이한 한라운드결과를 받는데 기다리는시간(초)
public const int i_TOTAL_ROUND =  9 ; // 플레이어가 10번 치고 10번 던짐
public const int i_WAIT_TIME_AFTER_GAME_END =  60 ; // 게임 종료 후 유저가 아무런 행동이 없을 때 대기 시간( 게임 리매치 요청 시 초기화 됨 )
public const int i_WAIT_TIME_BATTER_HIT =  1 ; // 투수가 공을 던진 후 타자가 공을 칠때까지 서버가 기다려주는 시간(초). 이시간이 넘으면 
public const int i_WAIT_TIME_PITCHER_THROW =  1 ; // 게임 진입시에 투수가 공을 던지지 않고 기다리고 있을 때 자동투구로 전환되기 전까지의 시간(초)
}}
