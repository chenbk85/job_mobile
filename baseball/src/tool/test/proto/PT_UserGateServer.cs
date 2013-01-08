using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using ProtoBuf;
//using Google.ProtocolBuffers;

namespace nPROTO
{
    [ProtoContract]
	public class s_ans_add_item {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_item item {get;set;}

        public s_ans_add_item()
        {
            item = new s_tbl_item();
        }
    }

    //bb_5.0.5_ug_item.usd
    //Sys_아이템의 sid로 강제로 아이템을 획득&#x0A;
    [ProtoContract]
	public class s_req_admin_add_item {
	    [ProtoMember(1, IsRequired = false)]
		public int sid {get;set;}
	    [ProtoMember(2, IsRequired = false)]
		public int category {get;set;}
	    [ProtoMember(3, IsRequired = false)]
		public string etc_info {get;set;}

    }

    //bb_5.0.5_ug_item.usd
    //상점 sid로 해당 물건 구입요청.
    [ProtoContract]
	public class s_req_item_buy {
	    [ProtoMember(1, IsRequired = false)]
		public int shop_sid {get;set;}
	    [ProtoMember(2, IsRequired = false)]
		public int count {get;set;}
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_req_player_create_better {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_playerbetter player {get;set;}

        public s_req_player_create_better()
        {
            player = new s_tbl_playerbetter();
        }
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_ans_player_create_better {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_playerbetter player {get;set;}

        public s_ans_player_create_better()
        {
            player = new s_tbl_playerbetter();
        }
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_req_player_delete {
	    [ProtoMember(1, IsRequired = false)]
		public bool is_pitcher {get;set;}
	    [ProtoMember(2, IsRequired = false)]
		public long db_id {get;set;}
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_ans_player_delete {
	    [ProtoMember(1, IsRequired = false)]
		public bool is_pitcher {get;set;}
	    [ProtoMember(2, IsRequired = false)]
		public long db_id {get;set;}
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_req_echo_to_ug {
	    [ProtoMember(1, IsRequired = false)]
		public int type {get;set;}
	    [ProtoMember(2, IsRequired = false)]
		public string msg {get;set;}
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_ans_echo_from_ug {
	    [ProtoMember(1, IsRequired = false)]
		public s_req_echo_to_ug info {get;set;}

        public s_ans_echo_from_ug()
        {
            info = new s_req_echo_to_ug();
        }
    }

    //bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_req_player_create_pitcher {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_playerpitcher player {get;set;}
	    [ProtoMember(2, IsRequired = false)]
		public s_tbl_pitcherskill skill1 {get;set;}
	    [ProtoMember(3, IsRequired = false)]
		public s_tbl_pitcherskill skill2 {get;set;}

        public s_req_player_create_pitcher()
        {
            player = new s_tbl_playerpitcher();
            skill1 = new s_tbl_pitcherskill();
            skill2 = new s_tbl_pitcherskill();
        }
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_ans_player_create_pitcher {
	    [ProtoMember(1, IsRequired = false)]
		public s_req_player_create_pitcher info {get;set;}

        public s_ans_player_create_pitcher()
        {
            info = new s_req_player_create_pitcher();
        }
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_ans_ug_error {
	    [ProtoMember(1, IsRequired = false)]
		public int sys_error_id {get;set;}
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_req_add_tbl_pitcherskill {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_pitcherskill info {get;set;}

        public s_req_add_tbl_pitcherskill()
        {
            info = new s_tbl_pitcherskill();
        }
    }

    //\bb_5.1.5_ug_player.usd
    [ProtoContract]
	public class s_ans_add_tbl_pitcherskill {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_pitcherskill info {get;set;}

        public s_ans_add_tbl_pitcherskill()
        {
            info = new s_tbl_pitcherskill();
        }
    }

    //\bb_5.3.5_ug_team.usd
    [ProtoContract]
	public class s_req_team_create {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_team team {get;set;}

        public s_req_team_create()
        {
            team = new s_tbl_team();
        }
    }

    //\bb_5.3.5_ug_team.usd
    [ProtoContract]
	public class s_ans_team_create {
	    [ProtoMember(1, IsRequired = false)]
		public s_tbl_team team {get;set;}

        public s_ans_team_create()
        {
            team = new s_tbl_team();
        }
    
    }


    //\bb_5.3.5_ug_team.usd
    [ProtoContract]
	public class s_req_team_delete {
	    [ProtoMember(1, IsRequired = false)]
		public int team_order {get;set;}
    }

    //\bb_5.3.5_ug_team.usd
    [ProtoContract]
	public class s_ans_team_delete {
	    [ProtoMember(1, IsRequired = false)]
		public int team_order {get;set;}
    }

    //\bb_5.3.5_ug_team.usd
    [ProtoContract]
	public class s_req_team_select {
	    [ProtoMember(1, IsRequired = false)]
		public int team_order {get;set;}
    }

    //\bb_5.3.5_ug_team.usd
    [ProtoContract]
	public class s_ans_team_select {
	    [ProtoMember(1, IsRequired = false)]
		public int team_order {get;set;}
    }


    [ProtoContract]
	public class UserGateServer_Client {
	    public enum Type {
		    NONE = 1,
            ans_add_item = 2,
		    ans_player_create_better = 3,
		    ans_player_delete = 4,
		    ans_echo_from_ug = 5,
		    ans_player_create_pitcher = 6,
		    ans_ug_error = 7,
		    ans_add_tbl_pitcherskill = 8,
		    ans_team_create = 9,
		    ans_team_delete = 10,
		    ans_team_select = 11
	    }
        [ProtoMember(1, IsRequired = true)]
	    public Type type {get;set;}

	    [ProtoMember(2, IsRequired = false)]
		public s_ans_add_item m_ans_add_item {get;set;}
	    [ProtoMember(3, IsRequired = false)]
		public s_ans_player_create_better m_ans_player_create_better {get;set;}
	    [ProtoMember(4, IsRequired = false)]
		public s_ans_player_delete m_ans_player_delete {get;set;}
	    [ProtoMember(5, IsRequired = false)]
		public s_ans_echo_from_ug m_ans_echo_from_ug {get;set;}
	    [ProtoMember(6, IsRequired = false)]
		public s_ans_player_create_pitcher m_ans_player_create_pitcher {get;set;}
	    [ProtoMember(7, IsRequired = false)]
		public s_ans_ug_error m_ans_ug_error {get;set;}
	    [ProtoMember(8, IsRequired = false)]
		public s_ans_add_tbl_pitcherskill m_ans_add_tbl_pitcherskill {get;set;}
	    [ProtoMember(9, IsRequired = false)]
		public s_ans_team_create m_ans_team_create {get;set;}
	    [ProtoMember(10, IsRequired = false)]
		public s_ans_team_delete m_ans_team_delete  {get;set;}
	    [ProtoMember(11, IsRequired = false)]
		public s_ans_team_select m_ans_team_select  {get;set;}


        public UserGateServer_Client()
        { 
            m_ans_add_item = new s_ans_add_item();
            m_ans_player_create_better = new s_ans_player_create_better();
            m_ans_player_delete = new s_ans_player_delete();
            m_ans_echo_from_ug = new s_ans_echo_from_ug();
            m_ans_player_create_pitcher = new s_ans_player_create_pitcher();
            m_ans_ug_error = new s_ans_ug_error();
            m_ans_add_tbl_pitcherskill = new s_ans_add_tbl_pitcherskill();
            m_ans_team_create = new s_ans_team_create();
            m_ans_team_delete = new s_ans_team_delete();
            m_ans_team_select = new s_ans_team_select();
        }
    }


    [ProtoContract]
	public class Client_UserGateServer {
	    public enum Type {
		    NONE = 1,

		    req_admin_add_item = 2,
		    req_item_buy = 3,
		    req_player_create_better = 4,
		    req_player_delete = 5,
		    req_echo_to_ug = 6,
		    req_player_create_pitcher = 7,
		    req_add_tbl_pitcherskill = 8,
		    req_team_create = 9,
		    req_team_delete = 10,
		    req_team_select = 11
	    }
        [ProtoMember(1, IsRequired = true)]
	    public Type type {get;set;}

	    [ProtoMember(2, IsRequired = false)]
		public s_req_admin_add_item m_req_admin_add_item {get;set;}
	    [ProtoMember(3, IsRequired = false)]
		public s_req_item_buy m_req_item_buy {get;set;}
	    [ProtoMember(4, IsRequired = false)]
		public s_req_player_create_better m_req_player_create_better {get;set;}
	    [ProtoMember(5, IsRequired = false)]
		public s_req_player_delete m_req_player_delete {get;set;}
	    [ProtoMember(6, IsRequired = false)]
		public s_req_echo_to_ug m_req_echo_to_ug {get;set;}
	    [ProtoMember(7, IsRequired = false)]
		public s_req_player_create_pitcher m_req_player_create_pitcher {get;set;}
	    [ProtoMember(8, IsRequired = false)]
		public s_req_add_tbl_pitcherskill m_req_add_tbl_pitcherskill {get;set;}
	    [ProtoMember(9, IsRequired = false)]
		public s_req_team_create m_req_team_create {get;set;}
	    [ProtoMember(10, IsRequired = false)]
		public s_req_team_delete m_req_team_delete  {get;set;}
	    [ProtoMember(11, IsRequired = false)]
		public s_req_team_select m_req_team_select  {get;set;}

        public Client_UserGateServer()
        { 
            m_req_admin_add_item = new s_req_admin_add_item();
            m_req_item_buy = new s_req_item_buy();
            m_req_player_create_better = new s_req_player_create_better();
            m_req_player_delete = new s_req_player_delete();
            m_req_echo_to_ug = new s_req_echo_to_ug();
            m_req_player_create_pitcher = new s_req_player_create_pitcher();
            m_req_add_tbl_pitcherskill = new s_req_add_tbl_pitcherskill();
            m_req_team_create = new s_req_team_create();
            m_req_team_delete = new s_req_team_delete();
            m_req_team_select = new s_req_team_select();
        }
    }
}
