
// X(DOMAIN,NAME,ORDER) 
#define for_each_UserGateServer_Client(X)\
		X(UserGateServer_Client,ug2x_goto_ok,2)\
		X(UserGateServer_Client,ug2x_single_play_start,3)\
		X(UserGateServer_Client,ug2x_single_play_end,4)\
		X(UserGateServer_Client,ug2x_quest_start,5)\
		X(UserGateServer_Client,ug2x_quest_end,6)\
		X(UserGateServer_Client,ans_add_item,7)\
		X(UserGateServer_Client,ans_admin_item_clear,8)\
		X(UserGateServer_Client,ans_show_me_the_money,9)\
		X(UserGateServer_Client,ans_set_item_owner,10)\
		X(UserGateServer_Client,ans_item_attach_detach,11)\
		X(UserGateServer_Client,ans_item_use,12)\
		X(UserGateServer_Client,ans_player_create_better,13)\
		X(UserGateServer_Client,ans_player_delete,14)\
		X(UserGateServer_Client,ans_echo_from_ug,15)\
		X(UserGateServer_Client,ans_player_create_pitcher,16)\
		X(UserGateServer_Client,ans_ug_error,17)\
		X(UserGateServer_Client,ans_add_tbl_pitcherskill,18)\
		X(UserGateServer_Client,ans_team_create,19)\
		X(UserGateServer_Client,ans_team_delete,20)\
		X(UserGateServer_Client,ans_team_select,21)\
		X(UserGateServer_Client,ans_team_update,22)\
  


// X(DOMAIN,NAME,ORDER) 
#define for_each_Client_UserGateServer(X)\
		X(Client_UserGateServer,x2ug_goto_match,2)\
		X(Client_UserGateServer,x2ug_goto_main,3)\
		X(Client_UserGateServer,x2ug_goto_charactor_create,4)\
		X(Client_UserGateServer,x2ug_goto_inventory,5)\
		X(Client_UserGateServer,x2ug_goto_single,6)\
		X(Client_UserGateServer,x2ug_goto_friend_match,7)\
		X(Client_UserGateServer,x2ug_goto_upgrade_pitcher,8)\
		X(Client_UserGateServer,x2ug_goto_upgrade_tranner,9)\
		X(Client_UserGateServer,x2ug_goto_upgrade_maestro,10)\
		X(Client_UserGateServer,x2ug_goto_etc_ativate,11)\
		X(Client_UserGateServer,x2ug_goto_rank,12)\
		X(Client_UserGateServer,x2ug_goto_quest,13)\
		X(Client_UserGateServer,x2ug_goto_option,14)\
		X(Client_UserGateServer,x2ug_goto_shop,15)\
		X(Client_UserGateServer,x2ug_goto_team,16)\
		X(Client_UserGateServer,x2ug_single_play_start,17)\
		X(Client_UserGateServer,x2ug_single_play_end,18)\
		X(Client_UserGateServer,x2ug_quest_start,19)\
		X(Client_UserGateServer,x2ug_quest_end,20)\
		X(Client_UserGateServer,req_admin_add_item,21)\
		X(Client_UserGateServer,req_item_buy,22)\
		X(Client_UserGateServer,req_admin_item_clear,23)\
		X(Client_UserGateServer,req_show_me_the_money,24)\
		X(Client_UserGateServer,req_set_item_owner,25)\
		X(Client_UserGateServer,req_item_attach_detach,26)\
		X(Client_UserGateServer,req_item_use,27)\
		X(Client_UserGateServer,req_player_create_better,28)\
		X(Client_UserGateServer,req_player_delete,29)\
		X(Client_UserGateServer,req_echo_to_ug,30)\
		X(Client_UserGateServer,req_player_create_pitcher,31)\
		X(Client_UserGateServer,req_add_tbl_pitcherskill,32)\
		X(Client_UserGateServer,req_team_create,33)\
		X(Client_UserGateServer,req_team_delete,34)\
		X(Client_UserGateServer,req_team_select,35)\
		X(Client_UserGateServer,req_team_update,36)\
  


		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_UserGateServer_Client___ug2x_goto_ok(X)\
		X(ug2x_goto_ok,0,string,state)\
		X(ug2x_goto_ok,1,string,prev_level)\
		X(ug2x_goto_ok,2,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_4.5.0_ug_single_play.usd
		#define for_each_UserGateServer_Client___ug2x_single_play_start(X)\
		X(ug2x_single_play_start,0,int32,single_play_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_4.5.0_ug_single_play.usd
		#define for_each_UserGateServer_Client___ug2x_single_play_end(X)\
		X(ug2x_single_play_end,0,s_result_game,rg)\
		X(ug2x_single_play_end,1,s_tbl_item,bonus_item)\
		X(ug2x_single_play_end,2,s_tbl_user,user)\
		X(ug2x_single_play_end,3,s_tbl_playerbetter,better)\
		X(ug2x_single_play_end,4,s_tbl_playerpitcher,pitcher)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_4.6.5_ug_quest.usd
		#define for_each_UserGateServer_Client___ug2x_quest_start(X)\
		X(ug2x_quest_start,0,int64,quest_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_4.6.5_ug_quest.usd
		#define for_each_UserGateServer_Client___ug2x_quest_end(X)\
		X(ug2x_quest_end,0,s_tbl_user,user)\
		X(ug2x_quest_end,1,s_tbl_team,team)\
		X(ug2x_quest_end,2,s_tbl_playerbetter,better)\
		X(ug2x_quest_end,3,s_tbl_playerpitcher,pitcher)\
		X(ug2x_quest_end,4,s_tbl_quest,quest)\
		X(ug2x_quest_end,5,s_tbl_title,title)\
		X(ug2x_quest_end,6,s_tbl_item,bonus_items)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.0.5_ug_item.usd
		#define for_each_UserGateServer_Client___ans_add_item(X)\
		X(ans_add_item,0,s_tbl_item,item)\
		X(ans_add_item,1,int32,reason)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.0.5_ug_item.usd
		#define for_each_UserGateServer_Client___ans_admin_item_clear(X)\
		X(ans_admin_item_clear,0,bool,ok)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.0.5_ug_item.usd
		#define for_each_UserGateServer_Client___ans_show_me_the_money(X)\
		X(ans_show_me_the_money,0,int32,game_money)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.0.6_ug_item_inven.usd
		#define for_each_UserGateServer_Client___ans_set_item_owner(X)\
		X(ans_set_item_owner,0,int64,iid)\
		X(ans_set_item_owner,1,int64,pid)\
		X(ans_set_item_owner,2,bool,is_better)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.0.6_ug_item_inven.usd
		#define for_each_UserGateServer_Client___ans_item_attach_detach(X)\
		X(ans_item_attach_detach,0,int64,iid)\
		X(ans_item_attach_detach,1,bool,is_attach)\
		X(ans_item_attach_detach,2,int64,pid)\
		X(ans_item_attach_detach,3,bool,is_better)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.0.6_ug_item_inven.usd
		#define for_each_UserGateServer_Client___ans_item_use(X)\
		X(ans_item_use,0,int64,iid)\
		X(ans_item_use,1,int64,pid)\
		X(ans_item_use,2,bool,is_better)\
		X(ans_item_use,3,int32,use_count)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_UserGateServer_Client___ans_player_create_better(X)\
		X(ans_player_create_better,0,s_tbl_playerbetter,player)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_UserGateServer_Client___ans_player_delete(X)\
		X(ans_player_delete,0,bool,is_pitcher)\
		X(ans_player_delete,1,int64,db_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_UserGateServer_Client___ans_echo_from_ug(X)\
		X(ans_echo_from_ug,0,s_req_echo_to_ug,info)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_UserGateServer_Client___ans_player_create_pitcher(X)\
		X(ans_player_create_pitcher,0,s_req_player_create_pitcher,info)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_UserGateServer_Client___ans_ug_error(X)\
		X(ans_ug_error,0,int32,sys_error_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_UserGateServer_Client___ans_add_tbl_pitcherskill(X)\
		X(ans_add_tbl_pitcherskill,0,s_tbl_pitcherskill,info)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.3.5_ug_team.usd
		#define for_each_UserGateServer_Client___ans_team_create(X)\
		X(ans_team_create,0,s_tbl_team,team)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.3.5_ug_team.usd
		#define for_each_UserGateServer_Client___ans_team_delete(X)\
		X(ans_team_delete,0,int32,team_order)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.3.5_ug_team.usd
		#define for_each_UserGateServer_Client___ans_team_select(X)\
		X(ans_team_select,0,int32,team_order)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.3.5_ug_team.usd
		#define for_each_UserGateServer_Client___ans_team_update(X)\
		X(ans_team_update,0,s_tbl_team,team)\


  


		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_match(X)\
		X(x2ug_goto_match,0,string,prev_level)\
		X(x2ug_goto_match,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_main(X)\
		X(x2ug_goto_main,0,string,prev_level)\
		X(x2ug_goto_main,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_charactor_create(X)\
		X(x2ug_goto_charactor_create,0,string,prev_level)\
		X(x2ug_goto_charactor_create,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_inventory(X)\
		X(x2ug_goto_inventory,0,string,prev_level)\
		X(x2ug_goto_inventory,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_single(X)\
		X(x2ug_goto_single,0,string,prev_level)\
		X(x2ug_goto_single,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_friend_match(X)\
		X(x2ug_goto_friend_match,0,string,prev_level)\
		X(x2ug_goto_friend_match,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_upgrade_pitcher(X)\
		X(x2ug_goto_upgrade_pitcher,0,string,prev_level)\
		X(x2ug_goto_upgrade_pitcher,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_upgrade_tranner(X)\
		X(x2ug_goto_upgrade_tranner,0,string,prev_level)\
		X(x2ug_goto_upgrade_tranner,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_upgrade_maestro(X)\
		X(x2ug_goto_upgrade_maestro,0,string,prev_level)\
		X(x2ug_goto_upgrade_maestro,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_etc_ativate(X)\
		X(x2ug_goto_etc_ativate,0,string,prev_level)\
		X(x2ug_goto_etc_ativate,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_rank(X)\
		X(x2ug_goto_rank,0,string,prev_level)\
		X(x2ug_goto_rank,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_quest(X)\
		X(x2ug_goto_quest,0,string,prev_level)\
		X(x2ug_goto_quest,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_option(X)\
		X(x2ug_goto_option,0,string,prev_level)\
		X(x2ug_goto_option,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_shop(X)\
		X(x2ug_goto_shop,0,string,prev_level)\
		X(x2ug_goto_shop,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_3.5.1_ug_eusergps.usd
		#define for_each_Client_UserGateServer___x2ug_goto_team(X)\
		X(x2ug_goto_team,0,string,prev_level)\
		X(x2ug_goto_team,1,string,next_level)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_4.5.0_ug_single_play.usd
		#define for_each_Client_UserGateServer___x2ug_single_play_start(X)\
		X(x2ug_single_play_start,0,int64,uid)\
		X(x2ug_single_play_start,1,int64,team)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_4.5.0_ug_single_play.usd
		#define for_each_Client_UserGateServer___x2ug_single_play_end(X)\
		X(x2ug_single_play_end,0,int32,single_play_id)\
		X(x2ug_single_play_end,1,int32,user_score)\
		X(x2ug_single_play_end,2,int32,ai_score)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_4.6.5_ug_quest.usd
		#define for_each_Client_UserGateServer___x2ug_quest_start(X)\
		X(x2ug_quest_start,0,int32,quest_sid)\
		X(x2ug_quest_start,1,string,mode)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_4.6.5_ug_quest.usd
		#define for_each_Client_UserGateServer___x2ug_quest_end(X)\
		X(x2ug_quest_end,0,int64,quest_id)\
		X(x2ug_quest_end,1,int32,quest_sid)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.0.5_ug_item.usd
		#define for_each_Client_UserGateServer___req_admin_add_item(X)\
		X(req_admin_add_item,0,int32,sid)\
		X(req_admin_add_item,1,int32,category)\
		X(req_admin_add_item,2,string,etc_info)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.0.5_ug_item.usd
		#define for_each_Client_UserGateServer___req_item_buy(X)\
		X(req_item_buy,0,int32,shop_sid)\
		X(req_item_buy,1,int32,count)\
		X(req_item_buy,2,string,option)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.0.5_ug_item.usd
		#define for_each_Client_UserGateServer___req_admin_item_clear(X)\
		X(req_admin_item_clear,0,int64,uid)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.0.5_ug_item.usd
		#define for_each_Client_UserGateServer___req_show_me_the_money(X)\
		X(req_show_me_the_money,0,int64,uid)\
		X(req_show_me_the_money,1,int32,game_money)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.0.6_ug_item_inven.usd
		#define for_each_Client_UserGateServer___req_set_item_owner(X)\
		X(req_set_item_owner,0,int64,uid)\
		X(req_set_item_owner,1,int64,iid)\
		X(req_set_item_owner,2,int64,pid)\
		X(req_set_item_owner,3,bool,is_better)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.0.6_ug_item_inven.usd
		#define for_each_Client_UserGateServer___req_item_attach_detach(X)\
		X(req_item_attach_detach,0,int64,uid)\
		X(req_item_attach_detach,1,int64,iid)\
		X(req_item_attach_detach,2,bool,is_attach)\
		X(req_item_attach_detach,3,int64,pid)\
		X(req_item_attach_detach,4,bool,is_better)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.0.6_ug_item_inven.usd
		#define for_each_Client_UserGateServer___req_item_use(X)\
		X(req_item_use,0,int64,uid)\
		X(req_item_use,1,int64,iid)\
		X(req_item_use,2,int64,pid)\
		X(req_item_use,3,bool,is_better)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_Client_UserGateServer___req_player_create_better(X)\
		X(req_player_create_better,0,s_tbl_playerbetter,player)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_Client_UserGateServer___req_player_delete(X)\
		X(req_player_delete,0,bool,is_pitcher)\
		X(req_player_delete,1,int64,db_id)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_Client_UserGateServer___req_echo_to_ug(X)\
		X(req_echo_to_ug,0,int32,type)\
		X(req_echo_to_ug,1,string,msg)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //bb_5.1.5_ug_player.usd
		#define for_each_Client_UserGateServer___req_player_create_pitcher(X)\
		X(req_player_create_pitcher,0,s_tbl_playerpitcher,player)\
		X(req_player_create_pitcher,1,s_tbl_pitcherskill,skill1)\
		X(req_player_create_pitcher,2,s_tbl_pitcherskill,skill2)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.1.5_ug_player.usd
		#define for_each_Client_UserGateServer___req_add_tbl_pitcherskill(X)\
		X(req_add_tbl_pitcherskill,0,s_tbl_pitcherskill,info)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.3.5_ug_team.usd
		#define for_each_Client_UserGateServer___req_team_create(X)\
		X(req_team_create,0,s_tbl_team,team)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.3.5_ug_team.usd
		#define for_each_Client_UserGateServer___req_team_delete(X)\
		X(req_team_delete,0,int32,team_order)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.3.5_ug_team.usd
		#define for_each_Client_UserGateServer___req_team_select(X)\
		X(req_team_select,0,int32,team_order)\

		// X(STRUCT,ORDER,TYPE,MEMVER)  //\bb_5.3.5_ug_team.usd
		#define for_each_Client_UserGateServer___req_team_update(X)\
		X(req_team_update,0,s_tbl_team,team)\


  

