using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using ProtoBuf;
//using Google.ProtocolBuffers;

namespace nPROTO
{

    public enum EUserGPS_notuse {
	    _notuseGPS_LOGOUT = 0,
	    _notuseGPS_LOGIN_OK = 1,
	    _notuseGPS_SHOP = 2,
	    _notuseGPS_GAMEROOM = 3
    }



    //bb_1.1.0-login.usd
    [ProtoContract]
	public class s_req_ping1 {
	    [ProtoMember(1,IsRequired=false)]
		public int type {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public string msg {get;set;}
    }

    //\bb_1.1.0-login.usd
    [ProtoContract]
	public class s_ans_pong1 {
	    [ProtoMember(1,IsRequired=false)]
		public int type {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public string msg {get;set;}
    }

    //\bb_1.1.0-login.usd
    [ProtoContract]
	public class s_req_chat {
	    [ProtoMember(1,IsRequired=false)]
		public int type {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public string msg {get;set;}
	    [ProtoMember(3,IsRequired=false)]
		public string etc {get;set;}
    }

    //bb_1.1.0-login.usd
    //채팅응답&#x0A;
    [ProtoContract]
	public class s_ans_chat {
	    [ProtoMember(1,IsRequired=false)]
		public int type {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public string msg {get;set;}
	    [ProtoMember(3,IsRequired=false)]
		public string etc {get;set;}
    }

    //bb_1.1.0-login.usd
    //클라에서 req_timer_start가 오면 &#x0A;term초만큼 주기적으로 해당방의 
    //클라에 msg를 보냄
    [ProtoContract]
	public class s_ans_timer_start {
	    [ProtoMember(1,IsRequired=false)]
		public int count {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public string msg {get;set;}
    }

    //bb_1.1.0-login.usd
    //term초 마다 서버에서 메세지를 보내라가 요청. 
    //term=0이면 메세지보내기중지
    [ProtoContract]
	public class s_req_timer_start {
	    [ProtoMember(1,IsRequired=false)]
		public int term {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public string msg {get;set;}
    }

    //\bb_1.1.0-login.usd
    [ProtoContract]
	public class s_req_do_disconnect {
	    [ProtoMember(1,IsRequired=false)]
		public string reason {get;set;}
    }

    //\bb_1.1.0-login.usd
    [ProtoContract]
	public class s_req_ping2 {
	    [ProtoMember(1,IsRequired=false)]
		public int type {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public string msg {get;set;}
    }

    //bb_1.1.0-login.usd
    //주석
    [ProtoContract]
	public class s_ans_pong2 {
	    [ProtoMember(1,IsRequired=false)]
		public int type {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public string msg {get;set;}
	    [ProtoMember(3,IsRequired=false)]
		public int etc {get;set;}
    }

    //\bb_1.1.0-login.usd
    [ProtoContract]
	public class s_ans_bs_error {
	    [ProtoMember(1,IsRequired=false)]
		public int sys_error_id {get;set;}
    }

    //\bb_1.1.0-login.usd
    [ProtoContract]
	public class s_req_get_cvar {
	    [ProtoMember(1,IsRequired=false)]
		public string name {get;set;}
    }

    //\bb_1.1.0-login.usd
    [ProtoContract]
	public class s_req_set_cvar {
	    [ProtoMember(1,IsRequired=false)]
		public string name {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public string val {get;set;}
    }

    //\bb_1.1.1_gameenter.usd
    [ProtoContract]
	public class s_ans_join_room {
	    [ProtoMember(1,IsRequired=false)]
		public GameRoomInfo gri {get;set;}

        public s_ans_join_room()
        {
            gri = new GameRoomInfo();
        }
    }

    //\bb_1.1.1_gameenter.usd
    [ProtoContract]
	public class s_req_room_state {
	    [ProtoMember(1,IsRequired=false)]
		public int room {get;set;}
    }

    //\bb_1.1.1_gameenter.usd
    [ProtoContract]
	public class s_ans_room_state {
	    [ProtoMember(1,IsRequired=false)]
		public GameRoomInfo gri {get;set;}

        public s_ans_room_state()
        {
            gri = new GameRoomInfo();
        }
    }

    //bb_5.2.5_ug_match.usd
    //만약 GAMESTART_ZERO_PLAYER_READY_COUNT_FIRST 와 
    //GAMESTART_ZERO_PLAYER_READY_COUNT_SECOND
    //가 지났는데도 ready를 안하면 &#x0A;ans_team_match_ready가 자동으로 날라간다.
    //timer_req_team_match_ready발동.
    [ProtoContract]
	public class s_req_team_match_ready {
	    [ProtoMember(1,IsRequired=false)]
		public int uid {get;set;}
    }

    //bb_5.2.5_ug_match.usd
    //만약 이 패킷을 받고 모두 레디이면&#x0A;GAMESTART_ZERO_PLAYER_READY_COUNT_BOTH(5)초 후에 
    //서버로부터 ans_game_start가 날라온다.
    [ProtoContract]
	public class s_ans_team_match_ready {
	    [ProtoMember(1,IsRequired=false)]
		public int uid {get;set;}
    }

    //\bb_5.2.5_ug_match.usd
    [ProtoContract]
	public class s_ans_game_start {
	    [ProtoMember(1,IsRequired=false)]
		public long attack_user {get;set;}
    }

    //bb_5.2.5_ug_match.usd
    //서버가 ans_game_start를 보낸후 
    //GAME_FIRST_ROUND_WAIT_TIME만큼
    //기다리고 ans_game_round_start를 보낸다.
    //또한 GAME_PITCHER_THROW_WAIT_TIME_COUNT만큼
    //기다려도 req_pitcher_throw가 안날라오면&#x0A;timer_out_req_pitcher_throw에 의해 자동으로 
    //ans_pitcher_throw가 날라간다.
    [ProtoContract]
	public class s_ans_game_round_start {
	    [ProtoMember(1,IsRequired=false)]
		public int round {get;set;}
    }

    //\bb_5.2.6_ug_match_round.usd
    [ProtoContract]
	public class s_req_pitcher_throw {
	    [ProtoMember(1,IsRequired=false)]
		public s_pitcher_throw_info info {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public s_pitcher_throw_info_verify verify {get;set;}

        public s_req_pitcher_throw()
        {
            info = new s_pitcher_throw_info();
            verify = new s_pitcher_throw_info_verify();

        }
    }

    //\bb_5.2.6_ug_match_round.usd
    [ProtoContract]
	public class s_ans_pitcher_throw {
	    [ProtoMember(1,IsRequired=false)]
		public s_pitcher_throw_info info {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public bool is_auto {get;set;}

        public s_ans_pitcher_throw()
        {
            info = new s_pitcher_throw_info();
        }
    }

    //\bb_5.2.6_ug_match_round.usd
    [ProtoContract]
	public class s_req_better_hit {
	    [ProtoMember(1,IsRequired=false)]
		public s_better_hit_info info {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public s_better_hit_info_verify verify {get;set;}

        public s_req_better_hit()
        {
            info = new s_better_hit_info();
            verify = new s_better_hit_info_verify();
        }
    }

    //\bb_5.2.6_ug_match_round.usd
    [ProtoContract]
	public class s_ans_better_hit {
	    [ProtoMember(1,IsRequired=false)]
		public s_better_hit_info info {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public bool is_auto {get;set;}

        public s_ans_better_hit()
        {
            info = new s_better_hit_info();
        }
    }

    //\bb_5.2.6_ug_match_round.usd
    [ProtoContract]
	public class s_req_result_better_hit {
	    [ProtoMember(1,IsRequired=false)]
		public s_result_round info {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public int test {get;set;}

        public s_req_result_better_hit()
        {
            info = new s_result_round();
        }
    }

    //\bb_5.2.6_ug_match_round.usd
    [ProtoContract]
	public class s_ans_result_better_hit {
	    [ProtoMember(1,IsRequired=false)]
		public s_result_round info {get;set;}

        public s_ans_result_better_hit()
        {
            info = new s_result_round();
        }
    }

    //bb_5.2.7_ug_match_end.usd
    //TOTAL_ROUND만큼 지나면 공수전환.
    [ProtoContract]
	public class s_ans_change_attack_team {
	    [ProtoMember(1,IsRequired=false)]
		public int round {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public long attack_user {get;set;}
    }

    //bb_5.2.7_ug_match_end.usd
    //만약 TOTAL_ROUND*2만큼 지나면 게임끝낸다.
    [ProtoContract]
	public class s_ans_game_end {
	    [ProtoMember(1,IsRequired=false)]
		public s_result_game rg {get;set;}

        public s_ans_game_end()
        {
            rg = new s_result_game();
        }
    }

    //\bb_5.2.8_ug_match_round_user_out.usd
    [ProtoContract]
	public class s_ans_user_disconnect {
	    [ProtoMember(1,IsRequired=false)]
		public long uid {get;set;}
	    [ProtoMember(2,IsRequired=false)]
		public int sys_error_id {get;set;}
    }


    [ProtoContract]
	public class BaseballServer_Client {
	    public enum Type {
		    NONE = 1,
		    ans_pong1 =2,
		    ans_chat =3,
		    ans_timer_start =4,
		    ans_pong2 =5,
		    ans_bs_error =6,
		    ans_join_room =7,
		    ans_room_state =8,
		    ans_team_match_ready =9, 
		    ans_game_start = 10,
		    ans_game_round_start = 11,
		    ans_pitcher_throw = 12,
		    ans_better_hit = 13,
		    ans_result_better_hit = 14,
		    ans_change_attack_team = 15,
		    ans_game_end = 16,
		    ans_user_disconnect = 17
	    }

        [ProtoMember(1, IsRequired = true)]
        public Type type {get;set;}

	    [ProtoMember(2,IsRequired=false)]
		public s_ans_pong1 m_ans_pong1 {get;set;}
	    [ProtoMember(3,IsRequired=false)]
		public s_ans_chat m_ans_chat {get;set;}
	    [ProtoMember(4,IsRequired=false)]
		public s_ans_timer_start m_ans_timer_start {get;set;}
	    [ProtoMember(5,IsRequired=false)]
		public s_ans_pong2 m_ans_pong2 {get;set;}
	    [ProtoMember(6,IsRequired=false)]
		public s_ans_bs_error m_ans_bs_error {get;set;}
	    [ProtoMember(7,IsRequired=false)]
		public s_ans_join_room m_ans_join_room {get;set;}
	    [ProtoMember(8,IsRequired=false)]
		public s_ans_room_state m_ans_room_state {get;set;}
	    [ProtoMember(9,IsRequired=false)]
		public s_ans_team_match_ready m_ans_team_match_ready {get;set;}
	    [ProtoMember(10,IsRequired=false)]
		public s_ans_game_start m_ans_game_start {get;set;}
	    [ProtoMember(11,IsRequired=false)]
		public s_ans_game_round_start m_ans_game_round_start {get;set;}
	    [ProtoMember(12,IsRequired=false)]
		public s_ans_pitcher_throw m_ans_pitcher_throw {get;set;}
	    [ProtoMember(13,IsRequired=false)]
		public s_ans_better_hit m_ans_better_hit {get;set;}
	    [ProtoMember(14,IsRequired=false)]
		public s_ans_result_better_hit m_ans_result_better_hit {get;set;}
	    [ProtoMember(15,IsRequired=false)]
		public s_ans_change_attack_team m_ans_change_attack_team {get;set;}
	    [ProtoMember(16,IsRequired=false)]
		public s_ans_game_end m_ans_game_end {get;set;}
	    [ProtoMember(17,IsRequired=false)]
		public s_ans_user_disconnect m_ans_user_disconnect {get;set;}

        public BaseballServer_Client()
        { 
            m_ans_pong1 = new s_ans_pong1();
            m_ans_chat = new s_ans_chat();
            m_ans_timer_start = new s_ans_timer_start();
            m_ans_pong2 = new s_ans_pong2();
            m_ans_bs_error = new s_ans_bs_error();
            m_ans_join_room = new s_ans_join_room();
            m_ans_room_state = new s_ans_room_state();
            m_ans_team_match_ready = new s_ans_team_match_ready();
            m_ans_game_start = new s_ans_game_start();
            m_ans_game_round_start = new s_ans_game_round_start();
            m_ans_pitcher_throw = new s_ans_pitcher_throw();
            m_ans_better_hit = new s_ans_better_hit();
            m_ans_result_better_hit = new s_ans_result_better_hit();
            m_ans_change_attack_team = new s_ans_change_attack_team();
            m_ans_game_end = new s_ans_game_end();
            m_ans_user_disconnect = new s_ans_user_disconnect();
        }
    }



    [ProtoContract]
	public class Client_BaseballServer {
	   public enum Type {
		    NONE =1,
		    req_ping1 =2,
		    req_chat =3,
		    req_timer_start =4,
		    req_do_disconnect =5,
		    req_ping2 =6,
		    req_get_cvar =7,
		    req_set_cvar =8,
		    req_room_state =9,
		    req_team_match_ready =10,
		    req_pitcher_throw =11,
		    req_better_hit =12,
		    req_result_better_hit =13
	    }

       [ProtoMember(1, IsRequired = true)]
        public Type type {get;set;}

	    [ProtoMember(2,IsRequired=false)]
		public s_req_ping1 m_req_ping1 {get;set;}
	    [ProtoMember(3,IsRequired=false)]
		public s_req_chat m_req_chat {get;set;}
	    [ProtoMember(4,IsRequired=false)]
		public s_req_timer_start m_req_timer_start {get;set;}
	    [ProtoMember(5,IsRequired=false)]
		public s_req_do_disconnect m_req_do_disconnect {get;set;}
	    [ProtoMember(6,IsRequired=false)]
		public s_req_ping2 m_req_ping2 {get;set;}
	    [ProtoMember(7,IsRequired=false)]
		public s_req_get_cvar m_req_get_cvar {get;set;}
	    [ProtoMember(8,IsRequired=false)]
		public s_req_set_cvar m_req_set_cvar {get;set;}
	    [ProtoMember(9,IsRequired=false)]
		public s_req_room_state m_req_room_state {get;set;}
	    [ProtoMember(10,IsRequired=false)]
		public s_req_team_match_ready m_req_team_match_ready {get;set;}
	    [ProtoMember(11,IsRequired=false)]
		public s_req_pitcher_throw m_req_pitcher_throw {get;set;}
	    [ProtoMember(12,IsRequired=false)]
		public s_req_better_hit m_req_better_hit {get;set;}
	    [ProtoMember(13,IsRequired=false)]
		public s_req_result_better_hit m_req_result_better_hit {get;set;}

        public Client_BaseballServer()
        { 
            m_req_ping1 = new s_req_ping1();
            m_req_chat = new s_req_chat();
            m_req_timer_start = new s_req_timer_start();
            m_req_do_disconnect = new s_req_do_disconnect();
            m_req_ping2 = new s_req_ping2();
            m_req_get_cvar = new s_req_get_cvar();
            m_req_set_cvar = new s_req_set_cvar();
            m_req_room_state = new s_req_room_state();
            m_req_team_match_ready = new s_req_team_match_ready();
            m_req_pitcher_throw = new s_req_pitcher_throw();
            m_req_better_hit = new s_req_better_hit();
            m_req_result_better_hit = new s_req_result_better_hit();

        }
    }
}
