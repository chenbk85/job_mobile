
// X(DOMAIN,NAME,ORDER) 
#define for_each_BaseballServer_UserGateServer(X)\
		X(BaseballServer_UserGateServer,bs2ug_set_cvar,2)\
		X(BaseballServer_UserGateServer,bs2ug_game_end,3)\
		X(BaseballServer_UserGateServer,bs2ug_echo,4)\
		X(BaseballServer_UserGateServer,bs2ug_error,5)\
		X(BaseballServer_UserGateServer,bs2ug_add_discon_tot,6)\
  


// X(DOMAIN,NAME,ORDER) 
#define for_each_BaseballServer_Client(X)\
		X(BaseballServer_Client,ans_join_room,2)\
		X(BaseballServer_Client,ans_room_state,3)\
		X(BaseballServer_Client,ans_pong1,4)\
		X(BaseballServer_Client,ans_chat,5)\
		X(BaseballServer_Client,ans_timer_start,6)\
		X(BaseballServer_Client,ans_pong2,7)\
		X(BaseballServer_Client,ans_bs_error,8)\
		X(BaseballServer_Client,ans_team_match_ready,9)\
		X(BaseballServer_Client,ans_game_start,10)\
		X(BaseballServer_Client,ans_game_round_start,11)\
		X(BaseballServer_Client,ans_pitcher_throw,12)\
		X(BaseballServer_Client,ans_better_hit,13)\
		X(BaseballServer_Client,ans_result_better_hit,14)\
		X(BaseballServer_Client,ans_change_attack_team,15)\
		X(BaseballServer_Client,ans_game_end,16)\
		X(BaseballServer_Client,ans_user_disconnect,17)\
		X(BaseballServer_Client,ans_rematch,18)\
		X(BaseballServer_Client,ans_answer_restart_game,19)\
  


// X(DOMAIN,NAME,ORDER) 
#define for_each_UserGateServer_BaseballServer(X)\
		X(UserGateServer_BaseballServer,ug2bs_ans_set_cvar,2)\
		X(UserGateServer_BaseballServer,ug2bs_game_end,3)\
		X(UserGateServer_BaseballServer,ug2bs_echo,4)\
		X(UserGateServer_BaseballServer,ug2bs_error,5)\
		X(UserGateServer_BaseballServer,ug2bs_add_discon_tot,6)\
  


// X(DOMAIN,NAME,ORDER) 
#define for_each_Client_BaseballServer(X)\
		X(Client_BaseballServer,req_room_state,2)\
		X(Client_BaseballServer,req_ping1,3)\
		X(Client_BaseballServer,req_chat,4)\
		X(Client_BaseballServer,req_timer_start,5)\
		X(Client_BaseballServer,req_do_disconnect,6)\
		X(Client_BaseballServer,req_ping2,7)\
		X(Client_BaseballServer,req_get_cvar,8)\
		X(Client_BaseballServer,req_set_cvar,9)\
		X(Client_BaseballServer,req_team_match_ready,10)\
		X(Client_BaseballServer,req_pitcher_throw,11)\
		X(Client_BaseballServer,req_better_hit,12)\
		X(Client_BaseballServer,req_result_better_hit,13)\
		X(Client_BaseballServer,req_rematch,14)\
		X(Client_BaseballServer,req_answer_restart_game,15)\
  


		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.5-bs_admin.usd
		#define for_each_BaseballServer_UserGateServer___bs2ug_set_cvar(X)\
		X(bs2ug_set_cvar,0,string,name)\
		X(bs2ug_set_cvar,1,string,val)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.7_ug_match_end.usd
		#define for_each_BaseballServer_UserGateServer___bs2ug_game_end(X)\
		X(bs2ug_game_end,0,s_result_game,rg)\
		X(bs2ug_game_end,1,bool,is_better)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_6.1.5_bs_ug_etc.usd
		#define for_each_BaseballServer_UserGateServer___bs2ug_echo(X)\
		X(bs2ug_echo,0,int32,type)\
		X(bs2ug_echo,1,string,msg)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_6.1.5_bs_ug_etc.usd
		#define for_each_BaseballServer_UserGateServer___bs2ug_error(X)\
		X(bs2ug_error,0,int32,sys_error_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_6.1.5_bs_ug_etc.usd
		#define for_each_BaseballServer_UserGateServer___bs2ug_add_discon_tot(X)\
		X(bs2ug_add_discon_tot,0,int64,discon_uid)\


  


		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_2.3.1_msg_ureqautojoin.usd
		#define for_each_BaseballServer_Client___ans_join_room(X)\
		X(ans_join_room,0,GameRoomInfo,gri)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_2.3.1_msg_ureqautojoin.usd
		#define for_each_BaseballServer_Client___ans_room_state(X)\
		X(ans_room_state,0,GameRoomInfo,gri)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.5-bs_admin.usd
		#define for_each_BaseballServer_Client___ans_pong1(X)\
		X(ans_pong1,0,int32,type)\
		X(ans_pong1,1,string,msg)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_3.1.5-bs_admin.usd
		#define for_each_BaseballServer_Client___ans_chat(X)\
		X(ans_chat,0,int32,type)\
		X(ans_chat,1,string,msg)\
		X(ans_chat,2,string,etc)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_3.1.5-bs_admin.usd
		#define for_each_BaseballServer_Client___ans_timer_start(X)\
		X(ans_timer_start,0,int32,count)\
		X(ans_timer_start,1,string,msg)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_3.1.5-bs_admin.usd
		#define for_each_BaseballServer_Client___ans_pong2(X)\
		X(ans_pong2,0,int32,type)\
		X(ans_pong2,1,string,msg)\
		X(ans_pong2,2,int32,etc)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.5-bs_admin.usd
		#define for_each_BaseballServer_Client___ans_bs_error(X)\
		X(ans_bs_error,0,int32,sys_error_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.2.5_ug_match.usd
		#define for_each_BaseballServer_Client___ans_team_match_ready(X)\
		X(ans_team_match_ready,0,int32,uid)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.5_ug_match.usd
		#define for_each_BaseballServer_Client___ans_game_start(X)\
		X(ans_game_start,0,int64,attack_user)\
		X(ans_game_start,1,int32,sid_Sys_Runner_State)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.2.5_ug_match.usd
		#define for_each_BaseballServer_Client___ans_game_round_start(X)\
		X(ans_game_round_start,0,int32,round)\
		X(ans_game_round_start,1,int32,runner_state)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.6_ug_match_round.usd
		#define for_each_BaseballServer_Client___ans_pitcher_throw(X)\
		X(ans_pitcher_throw,0,s_pitcher_throw_info,info)\
		X(ans_pitcher_throw,1,bool,is_auto)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.6_ug_match_round.usd
		#define for_each_BaseballServer_Client___ans_better_hit(X)\
		X(ans_better_hit,0,s_better_hit_info,info)\
		X(ans_better_hit,1,bool,is_auto)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.6_ug_match_round.usd
		#define for_each_BaseballServer_Client___ans_result_better_hit(X)\
		X(ans_result_better_hit,0,s_result_round,info)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.2.7_ug_match_end.usd
		#define for_each_BaseballServer_Client___ans_change_attack_team(X)\
		X(ans_change_attack_team,0,int32,round)\
		X(ans_change_attack_team,1,int64,attack_user)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.2.7_ug_match_end.usd
		#define for_each_BaseballServer_Client___ans_game_end(X)\
		X(ans_game_end,0,s_result_game,rg)\
		X(ans_game_end,1,s_tbl_item,bonus_item)\
		X(ans_game_end,2,s_tbl_user,user)\
		X(ans_game_end,3,s_tbl_playerbetter,better)\
		X(ans_game_end,4,s_tbl_playerpitcher,pitcher)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.8_ug_match_round_user_out.usd
		#define for_each_BaseballServer_Client___ans_user_disconnect(X)\
		X(ans_user_disconnect,0,int64,uid)\
		X(ans_user_disconnect,1,int32,sys_error_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.9_bs_rematch.usd
		#define for_each_BaseballServer_Client___ans_rematch(X)\
		X(ans_rematch,0,int64,uid)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.2.9_bs_rematch.usd
		#define for_each_BaseballServer_Client___ans_answer_restart_game(X)\
		X(ans_answer_restart_game,0,int64,uid)\
		X(ans_answer_restart_game,1,bool,ok)\


  


		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.5-bs_admin.usd
		#define for_each_UserGateServer_BaseballServer___ug2bs_ans_set_cvar(X)\
		X(ug2bs_ans_set_cvar,0,string,name)\
		X(ug2bs_ans_set_cvar,1,string,val)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.2.7_ug_match_end.usd
		#define for_each_UserGateServer_BaseballServer___ug2bs_game_end(X)\
		X(ug2bs_game_end,0,s_result_game,rg)\
		X(ug2bs_game_end,1,s_tbl_item,bonus_item)\
		X(ug2bs_game_end,2,s_tbl_user,user)\
		X(ug2bs_game_end,3,s_tbl_playerbetter,better)\
		X(ug2bs_game_end,4,s_tbl_playerpitcher,pitcher)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_6.1.5_bs_ug_etc.usd
		#define for_each_UserGateServer_BaseballServer___ug2bs_echo(X)\
		X(ug2bs_echo,0,int32,type)\
		X(ug2bs_echo,1,string,msg)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_6.1.5_bs_ug_etc.usd
		#define for_each_UserGateServer_BaseballServer___ug2bs_error(X)\
		X(ug2bs_error,0,int32,sys_error_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_6.1.5_bs_ug_etc.usd
		#define for_each_UserGateServer_BaseballServer___ug2bs_add_discon_tot(X)\
		X(ug2bs_add_discon_tot,0,int64,discon_uid)\


  


		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_2.3.1_msg_ureqautojoin.usd
		#define for_each_Client_BaseballServer___req_room_state(X)\
		X(req_room_state,0,int32,room)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_3.1.5-bs_admin.usd
		#define for_each_Client_BaseballServer___req_ping1(X)\
		X(req_ping1,0,int32,type)\
		X(req_ping1,1,string,msg)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.5-bs_admin.usd
		#define for_each_Client_BaseballServer___req_chat(X)\
		X(req_chat,0,int32,type)\
		X(req_chat,1,string,msg)\
		X(req_chat,2,string,etc)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_3.1.5-bs_admin.usd
		#define for_each_Client_BaseballServer___req_timer_start(X)\
		X(req_timer_start,0,int32,term)\
		X(req_timer_start,1,string,msg)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.5-bs_admin.usd
		#define for_each_Client_BaseballServer___req_do_disconnect(X)\
		X(req_do_disconnect,0,string,reason)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.5-bs_admin.usd
		#define for_each_Client_BaseballServer___req_ping2(X)\
		X(req_ping2,0,int32,type)\
		X(req_ping2,1,string,msg)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.5-bs_admin.usd
		#define for_each_Client_BaseballServer___req_get_cvar(X)\
		X(req_get_cvar,0,string,name)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.1.5-bs_admin.usd
		#define for_each_Client_BaseballServer___req_set_cvar(X)\
		X(req_set_cvar,0,string,name)\
		X(req_set_cvar,1,string,val)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.2.5_ug_match.usd
		#define for_each_Client_BaseballServer___req_team_match_ready(X)\
		X(req_team_match_ready,0,int32,uid)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.6_ug_match_round.usd
		#define for_each_Client_BaseballServer___req_pitcher_throw(X)\
		X(req_pitcher_throw,0,s_pitcher_throw_info,info)\
		X(req_pitcher_throw,1,s_pitcher_throw_info_verify,verify)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.6_ug_match_round.usd
		#define for_each_Client_BaseballServer___req_better_hit(X)\
		X(req_better_hit,0,s_better_hit_info,info)\
		X(req_better_hit,1,s_better_hit_info_verify,verify)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.6_ug_match_round.usd
		#define for_each_Client_BaseballServer___req_result_better_hit(X)\
		X(req_result_better_hit,0,s_result_round,info)\
		X(req_result_better_hit,1,int32,test)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.9_bs_rematch.usd
		#define for_each_Client_BaseballServer___req_rematch(X)\
		X(req_rematch,0,int64,uid)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.2.9_bs_rematch.usd
		#define for_each_Client_BaseballServer___req_answer_restart_game(X)\
		X(req_answer_restart_game,0,int64,uid)\
		X(req_answer_restart_game,1,bool,ok)\


  
