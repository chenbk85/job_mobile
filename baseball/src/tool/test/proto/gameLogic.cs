using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using ProtoBuf;
//using Google.ProtocolBuffers;

namespace nPROTO
{
    public enum EUserGPS // 유저 상태를  나타내는 지표.
    {
	    eUGPS_LOGOUT				=1,//" 네트웍접속해제
	    eUGPS_LOGIN					=2,// "UserGate서버에접속")
	    eUGPS_SHOP					=3,//	"상점입장")
	    eUGPS_UserGateServer		=50,//"여기까지가 유저게이트서버에서의 상태")

	    eUGPS_GAMEROOM				=500,//"BaseballServer에접속 대기방상태")
	    eUGPS_LABEL_GAME_NOT_QUIT	=599,//"BaseballServer에접속 이상태보다 크면 게임방을 나갈수 없다.
    	
	    eUGPS_GAME_READY			=610,//게임 레디 한 상태
	    eUGPS_GAME_START			=662,//"게임시작"
	    eUGPS_GAME_ROUND_START		=663,//"게임시작"
	    eUGPS_PITCHER_THROW			=664,//"투수가 공을 던졌다"
	    eUGPS_BETTER_HIT			=665,//"타자가 공을 쳤다"
	    eUGPS_BETTER_HIT_RESULT		=666,//타자는 req_result_better_hit를 보냈고 투수는 ans_result_better_hit를 받았다.
	    eUGPS_ATTACK_USER_CHANGED	=667,//팀이 막 바꼈다.
	    eUGPS_GAME_END				=668,//게임을 모두 끝내고 게임종료패킷 ans_game_end 을 보냈다.
	    eUGPS_GAMEROOM_PRE_LEAVE	=689,//"로비로 갈려고 대기중인 상태"
    	
	    eUGPS_BS_USER_IS_ILLEGAL	=900,// 게임서버에 접속된 상태이지만 유저의 정보가 정상이 아님 강제종료대상
	    eUGPS_BS_ABNORMAL_DISCONNECT=901,// 해당 유저는 클라이언트가 비정상적인 TCP DISCONNECT상태이다.
    	
	    eUGPS_BaseballServer		=1000//"여기까지가 게임서버접속상태"
    }
    /* -------------------------------------------------------------------------- */

    [ProtoContract]
	public class GameUserInfo 
    { 
        // 게임의 구동에 필요한 정보 - 디비에서오는 정보와 서버에서 생성된 정보
        [ProtoMember(1, IsRequired = true)]
		public GameInfo       game_info {get; set;} 

        // 피망플러스에서 오는 정보
        [ProtoMember(2, IsRequired = true)]
        public byte[] member_info { get; set; }

        public GameUserInfo()
        {
            game_info = new GameInfo();
        }
    }

    /* -------------------------------------------------------------------------- */
    [ProtoContract]
	public class GameInfo // Client , UserGateServer에서 가지고 있는 유저 정보.
    {
        // 피망 플러스 유저 번호
        [ProtoMember(1, IsRequired = true)]
		public int					game_id					{get; set;}
	    [ProtoMember(2, IsRequired = false)]
		public List< s_tbl_user>				m_tbl_user				{get; set;}
	    [ProtoMember(3, IsRequired = false)]
		public List< s_tbl_team>			m_tbl_team				{get; set;}
	    [ProtoMember(4, IsRequired = false)]
		public List< s_tbl_playerbetter>		m_tbl_playerbetter		{get; set;}
	    [ProtoMember(5, IsRequired = false)]
		public List< s_tbl_playerpitcher>	m_tbl_playerpitcher		{get; set;}

	    [ProtoMember(6, IsRequired = false)]
		public List< s_tbl_friend		>	m_tbl_friend			{get; set;}
	    [ProtoMember(7, IsRequired = false)]
		public List< s_tbl_item			>	m_tbl_item				{get; set;}
	    [ProtoMember(8, IsRequired = false)]
		public List< s_tbl_pitcherskill	>	m_tbl_pitcherskill		{get; set;}


        public GameInfo()
        {
            m_tbl_user = new List<s_tbl_user>();
            m_tbl_team = new List<s_tbl_team>();
            m_tbl_playerbetter = new List<s_tbl_playerbetter>();
            m_tbl_playerpitcher = new List<s_tbl_playerpitcher>();
            m_tbl_friend = new List<s_tbl_friend>();
            m_tbl_item = new List<s_tbl_item>();
            m_tbl_pitcherskill = new List<s_tbl_pitcherskill>();
        }
    }

    /* -------------------------------------------------------------------------- */

    [ProtoContract]
	public class s_game_play_info // BaseballServer에서 가지고 있는 유저 정보.
    {
        [ProtoMember(1, IsRequired = true)]
		public s_tbl_user				m_tbl_user				{get; set;}
        [ProtoMember(2, IsRequired = true)]
		public s_tbl_team				m_tbl_team				{get; set;}
        [ProtoMember(3, IsRequired = true)]
		public s_tbl_playerbetter		m_tbl_playerbetter		{get; set;}
        [ProtoMember(4, IsRequired = true)]
		public s_tbl_playerpitcher	m_tbl_playerpitcher		{get; set;}
	    [ProtoMember(5, IsRequired = false)]
		public List< s_tbl_pitcherskill	>	m_tbl_pitcherskill		{get; set;} //투수가 보유한 변화구 스킬종류.
	    //[ProtoMember(, IsRequired = false)]
		public EUserGPS				m_e_user_gps			{get; set;} // BaseballServer에서 사용하는 유저 GPS
	    //[ProtoMember(6, IsRequired = false)]
		//public int					m_e_user_gps			{get; set;} // BaseballServer에서 사용하는 유저 GPS

        public s_game_play_info()
        { 
            m_tbl_user = new s_tbl_user();
            m_tbl_team = new s_tbl_team();
            m_tbl_playerbetter = new s_tbl_playerbetter();
            m_tbl_playerpitcher = new s_tbl_playerpitcher();
            m_tbl_pitcherskill = new List<s_tbl_pitcherskill>();
        }
    }

    [ProtoContract]
	public class s_result_round // 한라운드 결과 s_result_better_hit
    {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_roundresult		m_tbl_roundresult		{get;set;}

        public s_result_round()
        {
            m_tbl_roundresult = new s_tbl_roundresult();
        }
    }

    [ProtoContract]
	public class s_result_game // 한게임 끝나고 결과.
    {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_result		m_tbl_result		{get;set;}

        public s_result_game()
        {
            m_tbl_result = new s_tbl_result();
        }
    }



    [ProtoContract]
	public class GameRoomInfo // 그방안에 있는 모든유저가 공유해야 하는정보. 최초 방만들고 join상황에서만 주고받는 정보.
    {
        [ProtoMember(1, IsRequired = true)]
		public int						room_id				{get; set;}// 룸 구분 번호
	    [ProtoMember(2, IsRequired = false)]
		public List< s_game_play_info	>		m_game_play_info	{get; set;}
	    [ProtoMember(3, IsRequired = false)]
		public long						m_attack_user		{get; set;} //누가 선공인지. user db_id()
	    [ProtoMember(4, IsRequired = false)]
		public int						m_round_count		{get; set;} //현제 라운드 정보. 0부터시작  TOTAL_ROUND-1 까지.
	    [ProtoMember(5, IsRequired = false)]
		public List< s_result_round	>			m_result_round		{get; set;} // 각 라운드의결과들.
	    [ProtoMember(6, IsRequired = false)]
		public s_result_game				m_result_game		{get; set;}
	    [ProtoMember(7, IsRequired = false)]
		public bool						m_is_auto_play		{get; set;}// 한유저가 나가서 자동플레이 상황인지?


        public GameRoomInfo()
        { 
            m_game_play_info = new List<s_game_play_info>();
            m_result_round = new List<s_result_round>();
            m_result_game = new s_result_game();
        }
    	
    }


    //#--------------------------------------------------------------------------
    // 투수와 타자간의 정보 교환 메세지 리스트
    //#--------------------------------------------------------------------------

    /*
    플레이중에 한 유저가 나가면?
    AI 대치 그리고 이어치기는 없슴. 나가버린 유저는 해당 게임 끝나기 전까지 게임룸 입장 안됨.
    그럼 두 플레이어에 대한 기록은 어떻게? 저장?
    */
    [ProtoContract]
	public class s_vector3
    {
	    [ProtoMember(1, IsRequired = false)]
		public float x{get; set;}
	    [ProtoMember(2, IsRequired = false)]
		public float y{get; set;}
	    [ProtoMember(3, IsRequired = false)]
		public float z{get; set;}
    }
    [ProtoContract]
	public class s_vector2
    {
	    [ProtoMember(1, IsRequired = false)]
		public float x{get; set;}
	    [ProtoMember(2, IsRequired = false)]
		public float y{get; set;}
    }

    [ProtoContract]
	public class s_pitcher_throw_info // 투수가 공을 던져서 서버에서 타자에게로 전달하는내용.
    {
	    [ProtoMember(1, IsRequired = false)]
		public s_vector3 screen_to_world	{get; set;}
	    [ProtoMember(2, IsRequired = false)]
		public int	ball_type			{get; set;}
	    [ProtoMember(3, IsRequired = false)]
		public float	scale_rate			{get; set;}
	    [ProtoMember(4, IsRequired = false)]
		public float	ball_breaking		{get; set;}
	    [ProtoMember(5, IsRequired = false)]
		public float	angle				{get; set;}
	    [ProtoMember(6, IsRequired = false)]
		public long	uid					{get; set;} //투수 uid
	    [ProtoMember(7, IsRequired = false)]
		public int	round				{get; set;} //해당라운드.

        public s_pitcher_throw_info()
        {
            screen_to_world = new s_vector3();
        }

    }

    [ProtoContract]
	public class s_pitcher_throw_info_verify // 투수가 공을 던져서 투수가 서버로 전달하는내용중 검증용 변수들.
    {
	    [ProtoMember(1, IsRequired = false)]
		public s_vector3	screen_to_world_org		{get; set;}
	    [ProtoMember(2, IsRequired = false)]
		public s_vector2	ball_position1			{get; set;}
	    [ProtoMember(3, IsRequired = false)]
		public s_vector2	ball_position2			{get; set;}
	    [ProtoMember(4, IsRequired = false)]
		public s_vector2	pannel_c				{get; set;}
	    [ProtoMember(5, IsRequired = false)]
		public int		control_speed			{get; set;}
	    [ProtoMember(6, IsRequired = false)]
		public float		size_down				{get; set;}
	    [ProtoMember(7, IsRequired = false)]
		public s_vector2	max_line				{get; set;}
	    [ProtoMember(8, IsRequired = false)]
		public s_vector2	min_line				{get; set;}
	    [ProtoMember(9, IsRequired = false)]
		public int	rhythm_judge_verifi			{get; set;}
	    [ProtoMember(10, IsRequired = false)]
		public int	rhythm_depth_verifi			{get; set;}
	    [ProtoMember(11, IsRequired = false)]
		public float	rhythm_effect_time1_verifi	{get; set;}

        public s_pitcher_throw_info_verify()
        { 
            screen_to_world_org = new s_vector3();
            ball_position1 = new s_vector2();
            ball_position2 = new s_vector2();
            pannel_c = new s_vector2();
            max_line = new s_vector2();
            min_line = new s_vector2();
        }
    }

    [ProtoContract]
	public class s_better_hit_info // 타자가 치는 정보중에 서버에서 투수에게 보내는 내용.
    {
	    [ProtoMember(1, IsRequired = false)]
		public s_vector3	screen_to_world		{get; set;}
	    [ProtoMember(2, IsRequired = false)]
		public s_vector2	force_xy			{get; set;} //hit_ball
	    [ProtoMember(3, IsRequired = false)]
		public float		force				{get; set;} //hit_ball
	    [ProtoMember(4, IsRequired = false)]
		public float		torque				{get; set;} //hit_ball
	    [ProtoMember(5, IsRequired = false)]
		public float		velocity_x			{get; set;} //hit_ball
	    [ProtoMember(6, IsRequired = false)]
		public long		uid					{get; set;} //타자 uid
	    [ProtoMember(7, IsRequired = false)]
		public int		round				{get; set;} //해당라운드.

        public s_better_hit_info()
        { 
            screen_to_world = new s_vector3();
            force_xy = new s_vector2();
        }
    }

    [ProtoContract]
	public class s_better_hit_info_verify // 타자가 치는 정보중에 타자가 서버로 보내는 내용중 검증용 변수들.
    {
	    [ProtoMember(1, IsRequired = false)]
		public  float	v3ballposition_z					{get; set;}
	    [ProtoMember(2, IsRequired = false)]
		public  s_vector2	rect_world_ball_pos				{get; set;}
	    [ProtoMember(3, IsRequired = false)]
		public  s_vector2	rect_world_ball_pos_wh			{get; set;}// width , height
	    [ProtoMember(4, IsRequired = false)]
		public  s_vector2	screen_ball_pos					{get; set;}
	    [ProtoMember(5, IsRequired = false)]
		public  s_vector2	screen_ball_pos1				{get; set;}
	    [ProtoMember(6, IsRequired = false)]
		public  s_vector2	screen_wh						{get; set;}// width height
	    [ProtoMember(7, IsRequired = false)]
		public  s_vector2	screen_batting					{get; set;}
	    [ProtoMember(8, IsRequired = false)]
		public  s_vector2	screen_batting_wh				{get; set;}
	    [ProtoMember(9, IsRequired = false)]
		public  s_vector2	screen_batting1					{get; set;}
	    [ProtoMember(10, IsRequired = false)]
		public  s_vector2	screen_batting1_wh				{get; set;}
	    [ProtoMember(11, IsRequired = false)]
		public  s_vector2	batting_pixel_inset				{get; set;}
	    [ProtoMember(12, IsRequired = false)]
		public  s_vector2	batting_pixel_inset_wh			{get; set;}
	    [ProtoMember(13, IsRequired = false)]
		public  s_vector2	batting_transform_pos			{get; set;}
	    [ProtoMember(14, IsRequired = false)]
		public  s_vector2	mcscript_pannel_xw				{get; set;}
	    [ProtoMember(15, IsRequired = false)]
		public  bool		mcscript_left_hand_batter		{get; set;}

        public s_better_hit_info_verify()
        { 
            rect_world_ball_pos = new s_vector2();
            rect_world_ball_pos_wh = new s_vector2();
            screen_ball_pos = new s_vector2();
            screen_ball_pos1 = new s_vector2();
            screen_wh = new s_vector2();
            screen_batting = new s_vector2();
            screen_batting_wh = new s_vector2();
            screen_batting1 = new s_vector2();
            screen_batting1_wh = new s_vector2();
            batting_pixel_inset = new s_vector2();
            batting_pixel_inset_wh = new s_vector2();
            batting_transform_pos = new s_vector2();
            mcscript_pannel_xw = new s_vector2();

        }
    }
    [ProtoContract]
	public class GLReqGameProtocol  //지우지말것.
    {
    }
    [ProtoContract]
	public class GLAnsGameProtocol //지우지말것.
    {
    }
}
