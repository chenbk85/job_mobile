/* file : recv_BaseballServer_UserGateServer.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-06-25 17:20:27
comp.: www.neowiz.com
title : 
desc : 


PT_BsaeballServer.proto에서 message BaseabllServer_UserGateServer에 포함된 메세지를 처리.
: UMLPAD에서 BaseabllServer -> UserGateServer로 보낸 패킷을 받는 부분이다.

*/

#include <gateway/database.hpp>
#include <sqlrelay/sqlrclient.h>
#include <sstream>
#include <boost/format.hpp>
#include <stdlib.h>
#include "protocol/ug.pb.h"
#include "stdafx.h"


using namespace std;
using namespace MSG;

#define jRECV_FROM_BS2UG(X) bool CB_BaseballServer_UserGateServer(jUser* pUser,const s_##X& rd,UserGateServer_BaseballServer& ret)

/* -------------------------------------------------------------------------- */
#define jMAKE_PACKET_UG2BS(sd, PACKET)\
	ret.set_type(UserGateServer_BaseballServer_Type_##PACKET);\
	s_##PACKET* sd = ret.mutable_m_##PACKET();\



#define jMAKE_PACKET_ug2bs_error(ERROR_SYS_ID)	\
	jMAKE_PACKET_UG2BS(sd , ug2bs_error);\
	sd->set_sys_error_id(jMAKE_ERR(ERROR_SYS_ID));\
	jWARN("%s",  #ERROR_SYS_ID );\

#define jMAKE_PACKET_ug2bs_error_BY_ID(iError)	\
	jMAKE_PACKET_UG2BS(sd , ug2bs_error);\
	sd->set_sys_error_id(iError);\
	jWARN("%s",  nError::ToString(iError) );\


jRECV_FROM_BS2UG(bs2ug_echo) // jUser* pUser , s_bs2ug_echo& rd ,UserGateServer_BaseballServer& ret
{
	jMAKE_PACKET_UG2BS(sd , ug2bs_echo);

	jLOG("%s> %s",__FUNCTION__ ,rd.msg().c_str() );
	sd->set_type(rd.type());
	sd->set_msg(rd.msg());
	return true;
}

jRECV_FROM_BS2UG(bs2ug_error) // jUser* pUser , s_bs2ug_error& rd ,UserGateServer_BaseballServer& ret
{
	jFUNC_LOG();
	return false;
}


jRECV_FROM_BS2UG(bs2ug_game_end) // jUser* pUser , s_bs2ug_game_end& rd ,UserGateServer_BaseballServer& ret
{
	jFUNC_LOG();
	if(rd.is_better())
	{
		//jTODO : 결과를 db에 저장.
		//rd.rg()
	}

	//nProtoHelper::message_print(rd.rg().m_tbl_result(),pUser->db_id());

	const s_tbl_result& gr = rd.rg().m_tbl_result();
	jRETURN_ret(false, gr.win_uid()!=gr.lose_uid());

	bool isWin = gr.win_uid() == pUser->db_id();
	if( gr.win_score() == gr.lose_score())
	{
		//비겼기때문에 패한것처럼 보상.
		isWin=false;
	}

	jCHECK(!gr.is_singlemode());
	exp_t new_exp=0;
	game_money_t new_money=0;
	Tbl_Team_id_t team_id=0;
	Tbl_PlayerBetter_id_t batter_pid=0;
	Tbl_PlayerPitcher_id_t pitcher_pid=0;

	if(isWin)
	{
		new_exp = gr.win_reward_exp();
		new_money = gr.win_reward_gamemoney();
		team_id = gr.win_team();
		batter_pid= gr.win_better();
		pitcher_pid = gr.win_pitcher();
	}
	else
	{
		new_exp = gr.lose_reward_exp();
		new_money = gr.lose_reward_gamemoney();
		team_id = gr.lose_team();
		batter_pid= gr.lose_better();
		pitcher_pid = gr.lose_pitcher();
	}

	//s_tbl_user* tu = pUser->get_tbl_user();
	s_tbl_team* tt = pUser->get_default_tbl_team();
	//jCHECK(team_id == tt->db_id());
	jLOG("isWin=%d , team_id=%d , tt->db_id()=%d",isWin,team_id,tt->db_id());
	s_tbl_playerbetter* better = pUser->find_tbl_playerbetter(batter_pid);
	s_tbl_playerpitcher* pitcher = pUser->find_tbl_playerpitcher(pitcher_pid);
	jCHECK(better->db_id()==batter_pid);
	jCHECK(pitcher->db_id()==pitcher_pid);

	//#--------------------------------------------------------------------------
	// 선수별 경험치 업데이트 및 보너스 선물 등급계산.
	//#--------------------------------------------------------------------------
	better->set_exp(better->exp()+new_exp);
	pitcher->set_exp(pitcher->exp()+new_exp);
	int isPitcher = nMOB::make_random()%2;
	level_t exp= isPitcher ? pitcher->exp() : better->exp();
	level_t level = nBASE_BALL::get_player_level(exp);
	EItemGradeType eGrade = nBASE_BALL::get_bonus_item_grade(level);
	jCHECK(IsValid(eGrade));

	//#--------------------------------------------------------------------------
	//줄수 있는 아이템 갯수 계산.
	//#--------------------------------------------------------------------------
	int count_Stuff=0 ,  count_Consume=0 , count_Equip=0;
	nBASE_BALL::calc_bonus_item_count(isWin, OUT count_Stuff , OUT count_Consume);
	jLOG("uid=%d count_Stuff=%d , count_Consume= %d " ,pUser->db_id() , count_Stuff ,count_Consume);

	//#--------------------------------------------------------------------------
	// 보상 아이템 지급.
	//#--------------------------------------------------------------------------
	/*
	6-1) 보너스 아이템 :스텁 + 컨슘중에 드링크제! 
		투수&타자 평군 등급에 따라 아이템 지급.
		줄수있는 아이템등급은 업글안된상태인 A , B ,C ,D ,E ,S 등급 스텁&소모(드링크)아이템만 줄수있다.
		스텁아이템은 파는거 아님.
		소모(컨숨)아이템은 is_bonus필드가 true인 아이템만 줄수있다.
		주는 갯수는 XML의 <RewardItemCount>참조.

	*/

	jMAKE_PACKET_UG2BS(sd , ug2bs_game_end);
	sd->mutable_rg()->CopyFrom(rd.rg());

#define add_bonus_item_to_user(TYPE1,TYPE2)\
	if(count_##TYPE2)\
	{\
		vector<Sys_Item##TYPE2*> target_items = jCSV(Sys_Item##TYPE2).m_INDEX_grade[eGrade];\
		for(int i=0; i< count_##TYPE2 ; ++i)\
		{\
			size_t idx = nMOB::random_my(0,target_items.size()-1);\
			jCONTINUE(idx>=0 && idx <target_items.size());\
			Sys_Item##TYPE2* pSys= target_items[idx];\
			jCONTINUE(pSys);\
			s_tbl_item * tbl_item= nDB::insert_item(pUser, pSys->Get_sid(), pSys->Get_category(), "INSERT_TYPE=BONUS") ;\
			jCONTINUE(tbl_item);\
			s_tbl_item* pItem = sd->add_bonus_item();\
			jCONTINUE(pItem);\
			pItem->CopyFrom(*tbl_item);\
		}\
	}\

	for_each_nEXCEL_EItemCategory123(add_bonus_item_to_user);

	jLOG("bonus item count = %d", sd->bonus_item_size());


// 	for(int i=0; i< sd->bonus_item_size() ; ++i)
// 	{
// 		nProtoHelper::message_print(sd->bonus_item(i),pUser->db_id());
// 	}

	//#--------------------------------------------------------------------------
	// 선수별 전적 처리.
	//#--------------------------------------------------------------------------
	{
		s_tbl_user* user = pUser->get_tbl_user();
		s_tbl_team* team = pUser->get_default_tbl_team();

		/*
		OK:총전적_승	tot_win
		OK:총전적_패	tot_lose
		OK:연승	win_continue
		OK:연패	lose_continue
		*/

#		define do_score_record(user)\
		if(isWin)\
		{\
			user->set_win_tot(user->win_tot()+1);\
			user->set_win_season(user->win_season()+1);\
			int win_continue = user->win_continue()+1;\
			if(user->win_continue()<0) win_continue=0;\
			user->set_win_continue(win_continue);\
		}\
		else\
		{\
			int win_continue = user->win_continue()-1;\
			if(user->win_continue()>0) win_continue=0;\
			user->set_win_continue(win_continue);\
		}\

		for_each_SCORE_RECORD_OBJ(do_score_record);


		/*
		Tbl_User
			탈삼진수	pitcher_tot_strikeout
			투수총평균_레벨	pitcher_tot_average_level
			총_홈런수	better_tot_homerun
			타자총평균_레벨	better_tot__average_level

		*/

		/*
		Tbl__PlayerBase

			마지막경기id	last_game_result
			*/

		/*

		Tbl_PlayerBetter
			타율	batting_average
			연속홈런수	continue_homerun_count
			총_홈런수	homeruntotal_count
			싱글홈런카운트	single_homerun_count
			더블홈런카운트	tworun_homerun_count
			쓰리런홈런카운트	threerun_homerun_count
			만루홈런카운트	grandslam_homerun_count
			일루타카운트	one_hit_count
			이루타카운트	double_hit_count
			삼루타카운트	triple_hit_count
			파울카운트	foul_hit_count
			아웃카운트	out_hit_count
			점수카운트	score_count
			*/

		/*

		Tbl_PlayerPitcher
			방어율	pitching_average
			피안타율	hit_count
			탈삼진수	strikeout_count
			피홈런수	homerun_pitching_count
			연속삼진수	continue_strikeout_count
			연속피홈런수	continue_homerun_pitching_count
		*/


		sd->mutable_user()->CopyFrom(*user);
		sd->mutable_better()->CopyFrom(*better);
		sd->mutable_pitcher()->CopyFrom(*pitcher);

	}


	return true;
}



jRECV_FROM_BS2UG(bs2ug_add_discon_tot) // jUser* pUser , s_bs2ug_add_discon_tot& rd ,UserGateServer_BaseballServer& ret
{
	//Tbl_User_id_t discon_uid = rd.discon_uid();
	//jTODO DB에 Tbl_User테이블 discon_uid값을 증가하시오.



	jMAKE_PACKET_UG2BS(sd , ug2bs_add_discon_tot);
	sd->set_discon_uid(rd.discon_uid());
	return true;// 
}



jRECV_FROM_BS2UG(bs2ug_set_cvar) // jUser* pUser , s_bs2ug_set_cvar& rd ,UserGateServer_BaseballServer& ret
{
	jIVar* pV = nG::g_ECV.get(rd.name().c_str());
	if(!pV)
	{
		jWARN("%s is not found", rd.name().c_str());
	}
	else
	{
		pV->FromString(rd.val().c_str());

		fname_t buf12;
		jLOG("%s =%s",rd.name().c_str() , pV->ToString(buf12));
	}

	jMAKE_PACKET_UG2BS(sd , ug2bs_ans_set_cvar);
	sd->set_name(rd.name());
	sd->set_val(rd.val());
	return true;
}





/*

템플릿입니다.


jRECV_FROM_BS2UG(asdf) // jUser* pUser , s_asdf& rd ,UserGateServer_BaseballServer& ret
{
	jMAKE_PACKET_UG2BS(sd , ug2bs_1234);

	jLOG("%s> %s",__FUNCTION__ ,rd.msg().c_str() );
	sd->set_type(rd.type());
	return true;
}

*/
