

/* file : SAMPLE_Room.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:21
comp.: www.neowiz.com
title : 
desc : 


PT_UserGateServer.proto에서 message Client_UserGateServer에 포함된 메세지를 처리.
: UMLPAD에서 Client -> UserGateServer로 보낸 패킷을 받는 부분이다.

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

#define jRECV_FROM_CLIENT_TO_UG(X) bool CB_Client_UserGateServer(jUser* pUser,const s_##X& rd,UserGateServer_Client& ret)
#define jNOT_REFERANCED_VARIABLE_DONT_WARRY(X) X;
/* -------------------------------------------------------------------------- */
#define jPREPARE_PACKET_UserGateServer_Client(sd, PACKET)\
	ret.set_type(UserGateServer_Client_Type_##PACKET);\
	s_##PACKET* sd = ret.mutable_m_##PACKET();\

#if 1
#	define jRETURN_ans_ug_error_EUserGPS(MENU)	
#else
#	define jRETURN_ans_ug_error_EUserGPS(MENU)	\
	if(!(pUser->m_eEUserGPS==eUGPS_##MENU))\
{\
	jPREPARE_PACKET_UserGateServer_Client(sd , ans_ug_error);\
	sd->set_sys_error_id(jMAKE_ERR(ERR_##MENU));\
	jWARN("%s",  #MENU );\
	return true;\
}\

#endif//1

#define jRETURN_ans_ug_error(is,ERROR_SYS_ID)	\
	if(!(is))\
	{\
		jPREPARE_PACKET_UserGateServer_Client(sd , ans_ug_error);\
		sd->set_sys_error_id(jMAKE_ERR(ERROR_SYS_ID));\
		jWARN("%lld , %s", pUser->db_id(), #ERROR_SYS_ID );\
		return true;\
	}\

// iError==0 아니면 클라에 에러 패킷 보냄.
#define jRETURN_ans_ug_error_BY_ID(iError)	\
	if(iError)\
	{\
		jPREPARE_PACKET_UserGateServer_Client(sd , ans_ug_error);\
		sd->set_sys_error_id(iError);\
		jWARN("%s",  nError::ToString(iError) );\
		return true;\
	}\


jRECV_FROM_CLIENT_TO_UG(req_echo_to_ug) // jUser* pUser , s_req_echo_to_ug& rd ,UserGateServer_Client& ret
{
	jPREPARE_PACKET_UserGateServer_Client(sd , ans_echo_from_ug);

	jLOG("%s> %s",__FUNCTION__ ,rd.msg().c_str() );
	sd->mutable_info()->CopyFrom(rd);
	return true;
}

jRECV_FROM_CLIENT_TO_UG(req_player_create_better) // jUser* pUser , s_req_player_create_better& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_charactor_create);
	jRETURN_ans_ug_error(pUser->m_eEUserGPS<eUGPS_UserGateServer , ERR_GPS_NEED_LOBBY);

	jASSERT0(g_jUser.m_GameUserInfo.mutable_game_info()->m_tbl_user_size()==1);
	int iTot = g_jUser.m_GameUserInfo.mutable_game_info()->m_tbl_playerbetter_size();

	jFUNC_LOG();

	//#--------------------------------------------------------------------------
	// 최대 생성 선수 인원 체크.
	//#--------------------------------------------------------------------------
	jRETURN_ans_ug_error(iTot < nG::i_MAX_PLAYER_CREATE_NUM->Get_int() , ERR_PLAYER_CREATE_FULL);

	//#--------------------------------------------------------------------------
	// 선수 이름 중복체크.
	//#--------------------------------------------------------------------------
	//nProtoHelper::message_print(rd.player(),pUser->db_id());
	cstr szName = rd.player().pname().c_str();
	jRETURN_ans_ug_error(!nDB::player_name_find(szName) , ERR_PLAYER_NAME_DUPLCATE);
	nDB::player_name_add(szName);

	GameInfo* pGameInfo = g_jUser.m_GameUserInfo.mutable_game_info();
	s_tbl_playerbetter* player= pGameInfo->add_m_tbl_playerbetter();
	nProtoHelper::message_init(*player);

	player->CopyFrom(rd.player());
	//TODO 차후에 클라에서 온값들의 범위체크필요

	player->set_db_id(iTot+1);
	player->set_sid(0);
	player->set_uid(pUser->db_id());
	
	//TODO : db save : INSERT INTO Tbl_PlayerBetter

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_player_create_better);
	sd->mutable_player()->CopyFrom(*player);
	//jTODO DB player추가.
	//nProtoHelper::message_print(*player,pUser->db_id());
	jFUNC_LOG();

	return true;
}



jRECV_FROM_CLIENT_TO_UG(req_player_create_pitcher) // jUser* pUser , s_req_player_create_pitcher& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_charactor_create);
	jRETURN_ans_ug_error(pUser->m_eEUserGPS<eUGPS_UserGateServer , ERR_GPS_NEED_LOBBY);

	jASSERT0(g_jUser.m_GameUserInfo.mutable_game_info()->m_tbl_user_size()==1);
	int iTot = g_jUser.m_GameUserInfo.mutable_game_info()->m_tbl_playerpitcher_size();

	//#--------------------------------------------------------------------------
	// 최대 생성 선수 인원 체크.
	//#--------------------------------------------------------------------------
	jRETURN_ans_ug_error(iTot < nG::i_MAX_PLAYER_CREATE_NUM->Get_int() , ERR_PLAYER_CREATE_FULL);

	//#--------------------------------------------------------------------------
	// 투수 스킬 정보 중복체크.
	//#--------------------------------------------------------------------------
	jRETURN_ans_ug_error(
		!(rd.skill1().gesture() == rd.skill2().gesture() || rd.skill1().type() == rd.skill2().type())
		,ERR_ADD_SKILL_PITCHER_DUP_GESTURE);

	//#--------------------------------------------------------------------------
	// 선수 이름 중복체크.
	//#--------------------------------------------------------------------------
	//nProtoHelper::message_print(rd.player(),pUser->db_id());
	cstr szName = rd.player().pname().c_str();
	jRETURN_ans_ug_error(!nDB::player_name_find(szName) ,ERR_PLAYER_NAME_DUPLCATE);

	nDB::player_name_add(szName);

	GameInfo* pGameInfo = g_jUser.m_GameUserInfo.mutable_game_info();
	
	// tbl_playerpitcher정보 세팅.
	s_tbl_playerpitcher* player= pGameInfo->add_m_tbl_playerpitcher();
	jRETURN_ret(true,player);
	nProtoHelper::message_init(*player);

	player->CopyFrom(rd.player());
	//TODO 차후에 클라에서 온값들의 범위체크필요


	player->set_db_id(iTot+1);
	player->set_sid(0);
	player->set_uid(pUser->db_id());

	// tbl_pitcherskill정보 세팅.
	s_tbl_pitcherskill* skill1 = pGameInfo->add_m_tbl_pitcherskill();
	jRETURN_ret(true,skill1);
	nDB::pitcherskill_insert(skill1, pUser->db_id(), player->db_id(),rd.skill1().gesture(), rd.skill1().type());
	
	s_tbl_pitcherskill* skill2 = pGameInfo->add_m_tbl_pitcherskill();
	jRETURN_ret(true,skill2);
	nDB::pitcherskill_insert(skill2, pUser->db_id(), player->db_id() ,rd.skill2().gesture(), rd.skill2().type());

	//TODO DB save : INSERT INTO Tbl_PlayerBetter

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_player_create_pitcher);
	sd->mutable_info()->mutable_player()->CopyFrom(*player);
	sd->mutable_info()->mutable_skill1()->CopyFrom(*skill1);
	sd->mutable_info()->mutable_skill2()->CopyFrom(*skill2);
// 	nProtoHelper::message_print(*player,pUser->db_id());
// 	nProtoHelper::message_print(*skill1,pUser->db_id());
// 	nProtoHelper::message_print(*skill2,pUser->db_id());

	return true;
}


jRECV_FROM_CLIENT_TO_UG(req_player_delete) // jUser* pUser , s_req_player_delete& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_charactor_create);
	jRETURN_ans_ug_error(pUser->m_eEUserGPS<eUGPS_UserGateServer , ERR_GPS_NEED_LOBBY);

	// 선수 찾기, 팀 소속되어 있는지 체크, 팀 소속되어있지 않으면 삭제
	// 선수 찾기
	//s_tbl__playerbase* pPlayerBase = 0;
	//s_tbl__playerbase* pTempBase = 0;
	jFUNC_LOG();
	if( rd.is_pitcher() )
	{
		s_tbl_team* pTeam = pUser->find_team_by_pitcher(rd.db_id());
		jRETURN_ans_ug_error(!pTeam , ERR_PLAYER_DELETE_IN_TEAM);

		s_tbl_playerpitcher* p = pUser->find_tbl_playerpitcher(rd.db_id());
		jRETURN_ans_ug_error(p,ERR_PLAYER_DELETE_NOT_EXIST);
		pUser->delete_tbl_playerpitcher(rd.db_id());
		//jTODO DB player삭제
	}
	else
	{
		s_tbl_team* pTeam = pUser->find_team_by_better(rd.db_id());
		jRETURN_ans_ug_error(!pTeam , ERR_PLAYER_DELETE_IN_TEAM);
		s_tbl_playerbetter* p = pUser->find_tbl_playerbetter(rd.db_id());
		jRETURN_ans_ug_error(p, ERR_PLAYER_DELETE_NOT_EXIST);
		pUser->delete_tbl_playerbetter(rd.db_id());
		//jTODO DB player삭제
	}

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_player_delete);
	sd->set_is_pitcher( rd.is_pitcher() );
	sd->set_db_id( rd.db_id() );

	return true;
}

jRECV_FROM_CLIENT_TO_UG(req_team_create) // jUser* pUser , s_req_team_create& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_team);
	jRETURN_ans_ug_error(pUser->m_eEUserGPS<eUGPS_UserGateServer , ERR_GPS_NEED_LOBBY);

	//TODO: 선수가 존팀에 소속되어 있는지 확인.
	Tbl_Team_id_t tid=0;
	Sys_Error_id_t iError = nDB::team_create(pUser, rd.team() , tid);
	jRETURN_ans_ug_error_BY_ID(iError);
	s_tbl_team* p = pUser->m_GameUserInfo.mutable_game_info()->add_m_tbl_team();
	p->CopyFrom(rd.team());
	p->set_db_id(tid);

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_team_create);
	sd->mutable_team()->CopyFrom(*p);

	return true;
}


jRECV_FROM_CLIENT_TO_UG(req_team_delete) // jUser* pUser , s_req_team_delete& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_team);
	jRETURN_ans_ug_error(pUser->m_eEUserGPS<eUGPS_UserGateServer , ERR_GPS_NEED_LOBBY);

	int iOrder = rd.team_order();

	jFUNC_LOG();
	//bhTODO : req_player_delete 에서도 그렇고 팀과 연관 이상해졌음. 문제점 찾아볼것.
	s_tbl_team* pTeam = pUser->get_tbl_team(iOrder);
	int iSize = pUser->size_tbl_team();

	jRETURN_ans_ug_error( (0 <= iOrder || iOrder < iSize ) ,ERR_TEAM_ORDER);
	jRETURN_ans_ug_error( pTeam ,ERR_TEAM_SELECT_NOT_EXIST_TEAM);
	s_tbl_user* user = pUser->get_tbl_user();
	jRETURN_ans_ug_error( user,ERR_USER_UID_INVALID);

	// 삭제될 팀에 소속된 선수 테이블에서 소속팀id 초기화. ( pitcher & better )
	s_tbl_playerbetter* better = pUser->find_tbl_playerbetter( pTeam->pid_better() );
	jCHECK(better);
	if(better)
	{
		better->set_team(0);
	}
	s_tbl_playerpitcher* pitcher = pUser->find_tbl_playerpitcher( pTeam->pid_pitcher() );
	jCHECK(pitcher);
	if(pitcher)
	{
		pitcher->set_team(0);
	}

	// 기본팀 번호 재설정 ( 추후 기본팀 번호 수정관련 요청이 있을 수 있음)
	if(user->default_tid()== pTeam->db_id())
	{
		user->set_default_tid(0);
	}
	pUser->get_tbl_user()->set_default_tid(rd.team_order());

	pUser->delete_tbl_team(pTeam->db_id());
	//jTODO DB team삭제

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_team_delete);
	sd->set_team_order(rd.team_order());

	return true;
}


jRECV_FROM_CLIENT_TO_UG(req_team_select) // jUser* pUser , s_req_team_select& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_team);
	jRETURN_ans_ug_error(pUser->m_eEUserGPS<eUGPS_UserGateServer , ERR_GPS_NEED_LOBBY);

	int iOrder = rd.team_order();

	jRETURN_ans_ug_error(
		!( 0 > iOrder || pUser->size_tbl_team() <= iOrder ) 
		, ERR_TEAM_SELECT_NOT_EXIST_TEAM);
	
	pUser->get_tbl_user()->set_default_tid(rd.team_order());

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_team_select);
	sd->set_team_order(rd.team_order());

	return true;
}



jRECV_FROM_CLIENT_TO_UG(req_add_tbl_pitcherskill) // jUser* pUser , s_req_add_tbl_pitcherskill& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error(pUser->m_eEUserGPS<eUGPS_UserGateServer , ERR_GPS_NEED_LOBBY);

	s_tbl_playerpitcher* player = pUser->find_tbl_playerpitcher(rd.info().pid());
	jRETURN_ans_ug_error(player, ERR_ADD_SKILL_PITCHER_NOT_FOUND);

	//jTODO rd의 값에대 유효성 체크 필요.
	jRETURN_ans_ug_error(
		(true == pUser->is_duplicate_pitcherskill((EGestureType)rd.info().gesture(), (EPlayerBreakingBall)rd.info().type(), rd.info().pid()) )
		,ERR_ADD_SKILL_PITCHER_DUP_GESTURE_BB);

	s_tbl_pitcherskill* skill = pUser->add_tbl_pitcherskill();
	nDB::pitcherskill_insert(OUT skill, pUser->db_id(), rd.info().pid() ,rd.info().gesture(), rd.info().type());

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_add_tbl_pitcherskill);
	sd->mutable_info()->CopyFrom(*skill);
	//nProtoHelper::message_print(*skill,pUser->db_id());

	return true;
}




jRECV_FROM_CLIENT_TO_UG(req_admin_add_item) // jUser* pUser , s_req_admin_add_item& rd ,UserGateServer_Client& ret
{
	EItemCategory eCategory = (EItemCategory)rd.category();
	jRETURN_ans_ug_error(IsValid(eCategory) , ERR_ITEM_BUY_CATEGORY_ERROR);
	jRETURN_ans_ug_error(pUser->is_abilable_item_buy(rd.sid(), eCategory, rd.etc_info()) ,ERR_ITEM_BUY_CHECK );

	// DB, CSV에서 아이템 정보 검색 & 세팅
	fname_t buf;
	ja_sprintf(buf,"INSERT_TYPE=ADMIN;%s",rd.etc_info().c_str());
	s_tbl_item * new_item = nDB::insert_item(pUser, rd.sid(), eCategory, buf) ;
	jRETURN_ans_ug_error(new_item,ERR_ITEM_BUY_DATA );

	// 아이템 정보 반환 
	jPREPARE_PACKET_UserGateServer_Client(sd , ans_add_item);
	sd->mutable_item()->CopyFrom(*new_item);
	sd->set_reason(1);
	return true;
}

jRECV_FROM_CLIENT_TO_UG(req_item_buy) // jUser* pUser , s_req_item_buy& rd ,UserGateServer_Client& ret
{
	Sys_Shop* pShopItem = jCSV(Sys_Shop).Index(rd.shop_sid());
	jRETURN_ans_ug_error(pShopItem, ERR_NOT_FOUND_SHOP_ITEM);

	
	
	return true;
}

jRECV_FROM_CLIENT_TO_UG(req_admin_item_clear) // jUser* pUser , s_req_admin_item_clear& rd ,UserGateServer_Client& ret
{
	pUser->clear_tbl_item();

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_admin_item_clear);
	sd->set_ok(true);
	//jTODO db update

	return true;
}

jRECV_FROM_CLIENT_TO_UG(req_show_me_the_money) // jUser* pUser , s_req_show_me_the_money& rd ,UserGateServer_Client& ret
{
	//jTODO DB에 게임머니 추가 업데이트.
	pUser->get_tbl_user()->set_game_money(rd.game_money());
	jPREPARE_PACKET_UserGateServer_Client(sd , ans_show_me_the_money);
	sd->set_game_money(rd.game_money());
	//jTODO db update
	return true;
}

//아이템 귀속
jRECV_FROM_CLIENT_TO_UG(req_set_item_owner) // jUser* pUser , s_req_set_item_owner& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_inventory);

	s_tbl_item* pItem = pUser->find_tbl_item(rd.iid());
	jRETURN_ans_ug_error(pItem, ERR_NOT_EXIST_ITEM);
	jRETURN_ans_ug_error(pItem->used_player_id()==0 , ERR_ITEM_WAS_OWNED);

	if(rd.is_better())
	{
		jRETURN_ans_ug_error(pUser->find_tbl_playerbetter(rd.pid()) , ERR_PLAYER_PID_NOT_FOUND);
	}
	else
	{
		jRETURN_ans_ug_error(pUser->find_tbl_playerpitcher(rd.pid()) , ERR_PLAYER_PID_NOT_FOUND);
	}

	pItem->set_is_better(rd.is_better());
	pItem->set_used_player_id(rd.pid());
	fname_t buf;
	pItem->set_date_update(nOS::current_SYSTEMTIME(buf));
	//jTODO db update

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_set_item_owner);
	sd->set_iid(rd.iid());
	sd->set_pid(rd.pid());
	sd->set_is_better(rd.is_better());

	return true;// false이면 접속해제한다.
}


jRECV_FROM_CLIENT_TO_UG(req_item_attach_detach) // jUser* pUser , s_req_item_attach_detach& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_inventory);

	/*
	아이템을 구입 -> 사물함으로 이동(반품가능) -> 귀속시 해당캐릭터의 인벤으로 이동.
	최초 인벤열면 
		-> 디펄트 캐릭이 보임( 타자)
		-> 디펄트 팀 / 선수세팅이 안되어 있으면 인벤못연다.
		-> 

	*/

	s_tbl_item* pItem = pUser->find_tbl_item(rd.iid());
	jRETURN_ans_ug_error(pItem, ERR_NOT_EXIST_ITEM);
	jRETURN_ans_ug_error(pItem->used_player_id()==rd.pid(), ERR_PLAYER_NOT_HAVE_ITEM);
	jRETURN_ans_ug_error(pItem->category()==eIC_EQUIP , ERR_DONT_ATTACH_DETTACH_EQUIP);

	pItem->set_is_equiped(rd.is_attach());
	//jTODO db update

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_item_attach_detach);
	sd->set_iid(rd.iid());
	sd->set_pid(rd.pid());
	sd->set_is_better(rd.is_better());
	sd->set_is_attach(rd.is_attach());
	jLOG("iid=%d  is_attach=%d",pItem->db_id() , pItem->is_equiped());

	return true;// false이면 접속해제한다.
}

namespace nBASE_BALL
{
	Sys_Error_id_t use_item(s_tbl_item* pItem , jUser* pUser)
	{
		//jTODO 소비아이템 적용..
		pItem->set_use_count(pItem->use_count()-1);

		return 0;
	}

}

jRECV_FROM_CLIENT_TO_UG(req_item_use) // jUser* pUser , s_req_item_use& rd ,UserGateServer_Client& ret
{

	s_tbl_item* pItem = pUser->find_tbl_item(rd.iid());
	jRETURN_ans_ug_error(pItem, ERR_NOT_EXIST_ITEM);
	//강화아이템은 강화로만사용됨.
	jRETURN_ans_ug_error(pItem->category()==eIC_CONSUME, ERR_ITEM_NOT_USE_CATEGORY);
	jRETURN_ans_ug_error(pItem->use_count()>0, ERR_SERVER_DATA_ITEM_COUNT_ZERO);

	Sys_Error_id_t iError = nBASE_BALL::use_item(pItem, pUser);
	jRETURN_ans_ug_error_BY_ID(iError);

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_item_use);
	sd->set_iid(rd.iid());
	sd->set_pid(rd.pid());
	sd->set_is_better(rd.is_better());
	sd->set_use_count(pItem->use_count());
	return true;// false이면 접속해제한다.
}



jRECV_FROM_CLIENT_TO_UG(x2ug_single_play_start) // jUser* pUser , s_x2ug_single_play_start& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_single);

	jRETURN_ans_ug_error(pUser->db_id()==rd.uid(), ERR_SERVER_DATA_UID_DISMATCH);
	s_tbl_team* team = pUser->get_default_tbl_team();
	jRETURN_ans_ug_error(team && team->db_id()==rd.team() , ERR_DEFAULT_TEAM_INVALID);
	jRETURN_ans_ug_error(pUser->m_eEUserGPS< eUGPS_UserGateServer, ERR_GPS_NEED_LOBBY);
	//jTODO 차후 어뷰징체크 : 너무 자주보내는 부분 체크 필요.

	static int single_play_id =nMOB::make_random();
	pUser->m_single_play_id = ++single_play_id; 
	jPREPARE_PACKET_UserGateServer_Client(sd , ug2x_single_play_start);
	sd->set_single_play_id(pUser->m_single_play_id);
	pUser->m_timer_game_start = time(0);

	pUser->m_eEUserGPS = eUGPS_SINGLEPLAY;
	
	return true;// false이면 접속해제한다.
}


jRECV_FROM_CLIENT_TO_UG(x2ug_single_play_end) // jUser* pUser , s_x2ug_single_play_end& rd ,UserGateServer_Client& ret
{
	jLOG("timeGetTime() = %d",time(0));
	jRETURN_ans_ug_error(pUser->m_single_play_id && pUser->m_single_play_id == rd.single_play_id() , ERR_SINGLEPLAY_ID);
	jRETURN_ans_ug_error(pUser->m_eEUserGPS== eUGPS_SINGLEPLAY, ERR_GPS_NOT_SINGLEMODE);

	int64 elapsed = time(0) - pUser->m_timer_game_start;
	int64 total_time_min = (nG::i_SINGLEPLAY_1ROUND_TIME_MIN->Get_int() * nG::i_TOTAL_ROUND->Get_int())*2;
	jLOG("total_time_min =%lld , elapsed = %lld, nG::i_SINGLEPLAY_1ROUND_TIME_MIN->Get_float()=d"
		,total_time_min ,elapsed,nG::i_SINGLEPLAY_1ROUND_TIME_MIN->Get_int());
	jRETURN_ans_ug_error(elapsed>=total_time_min, ERR_SINGLE_PLAY_TIME);

	jLOG("%s > play_time_sec = %d",jFUNC,(int32)elapsed);

	bool isWin = rd.user_score() > rd.ai_score();

	s_tbl_user* user = pUser->get_tbl_user();
	s_tbl_playerbetter *better = pUser->get_default_tbl_playerbetter();
	s_tbl_playerpitcher* pitcher= pUser->get_default_tbl_playerpitcher();
	s_tbl_team* team = pUser->get_default_tbl_team();

#	define do_score_record_single(OBJ)\
	if(isWin)\
	{\
		OBJ->set_win_tot_single(OBJ->win_tot_single()+1);\
		OBJ->set_win_season_single(OBJ->win_season_single()+1);\
		int win_continue_single = OBJ->win_continue_single()+1;\
		if(OBJ->win_continue_single()<0) win_continue_single=0;\
		OBJ->set_win_continue_single(win_continue_single);\
	}\
	else\
	{\
		int win_continue_single = OBJ->win_continue_single()-1;\
		if(OBJ->win_continue_single()>0) win_continue_single=0;\
		OBJ->set_win_continue_single(win_continue_single);\
	}\

	for_each_SCORE_RECORD_OBJ(do_score_record_single);

	pUser->m_single_play_id=0;

	//jTODO 싱글플레이 경험치 보상.
	//
	jTE* peGAME_RESULT=0;
	if(isWin)
	{
		static jTE* peWIN = nXML::find(nG::g_DocApp , "baseball.play_data.GAME_RESULT.PVE.WIN");
		jCHECK(peWIN);
		peGAME_RESULT  = peWIN;
	}
	else
	{
		static jTE* peLOSE= nXML::find(nG::g_DocApp , "baseball.play_data.GAME_RESULT.PVE.LOSE");
		jCHECK(peLOSE);
		peGAME_RESULT = peLOSE;
	}
	jRETURN_ans_ug_error(peGAME_RESULT, ERR_SERVER_XML);

	cstr szExpWIN = peGAME_RESULT->Attribute("i_EXP");
	exp_t exp = jt_atoi(szExpWIN);
	bool isGive = nMOB::random_my(0,1);
	if(isGive)
	{
		if(user->singleplay_gift_count() < nG::i_GAMECOUNT_EXP_SINGLEPLAY_IN_DAY->Get_int())
		{
			user->set_singleplay_gift_count(user->singleplay_gift_count()+1);
			pitcher->set_exp(pitcher->exp() + exp);
			better->set_exp(better->exp() + exp);
			//jTODO DB저장 선수경험치.
		}
		else
		{
			isGive=false;
			jLOG_DEBUG("user->singleplay_gift_count() over! skip bonus");
		}
	}

	jPREPARE_PACKET_UserGateServer_Client(sd , ug2x_single_play_end);
	sd->mutable_pitcher()->CopyFrom(*pitcher);
	sd->mutable_better()->CopyFrom(*better);
	sd->mutable_user()->CopyFrom(*user);

	s_tbl_result* rg = sd->mutable_rg()->mutable_m_tbl_result();
	rg->set_is_singlemode(true);
	rg->set_win_uid(isWin ? user->db_id() : 0);
	rg->set_win_better(isWin ? better->db_id() : 0);
	rg->set_win_pitcher(isWin ? pitcher->db_id() : 0);
	rg->set_win_team(isWin ? team->db_id() : 0);
	rg->set_win_score(isWin ? rd.user_score() : rd.ai_score());
	rg->set_win_reward_exp(isWin ? exp : 0);
	rg->set_win_reward_gamemoney(0);

	rg->set_lose_uid(!isWin ? user->db_id() : 0);
	rg->set_lose_better(!isWin ? better->db_id() : 0);
	rg->set_lose_pitcher(!isWin ? pitcher->db_id() : 0);
	rg->set_lose_team(!isWin ? team->db_id() : 0);
	rg->set_lose_score(!isWin ? rd.user_score() : rd.ai_score());
	rg->set_lose_reward_exp(!isWin ? exp : 0);
	rg->set_lose_reward_gamemoney(0);

	rg->set_play_time_sec((int32)elapsed);
	fname_t buf;
	rg->set_time_end(nOS::current_SYSTEMTIME(buf));

	//jTODO DB저장 : rg ,Tbl_User, Tbl_Team ,Tbl_PlayerPitcher , Tbl_PlayerBetter - 싱글 기록정보들. 보상횟수등...

	pUser->m_eEUserGPS= eUGPS_x2ug_goto_single;


	return true;// false이면 접속해제한다.
}


#define jRECV_FROM_CLIENT_TO_UG__goto_menu(MENU)\
jRECV_FROM_CLIENT_TO_UG(MENU)\
{\
	pUser->m_eEUserGPS_prev= pUser->m_eEUserGPS;\
	pUser->m_eEUserGPS = eUGPS_##MENU;\
	jPREPARE_PACKET_UserGateServer_Client(sd , ug2x_goto_ok);\
	sd->set_state(#MENU);\
	sd->set_prev_level(rd.prev_level());\
	sd->set_next_level(rd.next_level());\
	return true;\
}\

for_each_menu_window(jRECV_FROM_CLIENT_TO_UG__goto_menu);


jRECV_FROM_CLIENT_TO_UG(x2ug_quest_start) // jUser* pUser , s_x2ug_quest_start& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_quest);
	Sys_Quest* pQuest = jCSV(Sys_Quest).Index(rd.quest_sid());
	jRETURN_ans_ug_error( pQuest , ERR_QUEST_SID_NOT_FOUND);
	jRETURN_ans_ug_error( pQuest->Get_quest_type()==eEQT_INGAMETUTORIAL , ERR_QUEST_RUN);
	jRETURN_ans_ug_error( pUser->get_default_tbl_team(), ERR_COND_DEFAULT_TEAM);
	jRETURN_ans_ug_error( pUser->get_default_tbl_playerpitcher(), ERR_COND_DEFAULT_PITCHER);
	jRETURN_ans_ug_error( pUser->get_default_tbl_playerbetter(), ERR_COND_DEFAULT_BETTER);

	s_tbl_quest* new_quest = pUser->find_tbl_quest_by_sid(rd.quest_sid());
	if(!new_quest)
	{
		new_quest = pUser->add_tbl_quest();
		nProtoHelper::message_init(*new_quest);// 모든변수 초기화.
		new_quest->set_db_id(nMOB::make_random());
		new_quest->set_quest_sid(rd.quest_sid());
		new_quest->set_uid(pUser->db_id());
		fname_t buf;
		new_quest->set_date_insert(nOS::current_SYSTEMTIME(buf));
		//jTODO DB insert s_tbl_quest
	}
	
	jPREPARE_PACKET_UserGateServer_Client(sd , ug2x_quest_start);
	sd->set_quest_id(new_quest->db_id());
	return true;// false이면 접속해제한다.
}


jRECV_FROM_CLIENT_TO_UG(x2ug_quest_end) // jUser* pUser , s_x2ug_quest_end& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_quest);
	Sys_Quest* pQuest = jCSV(Sys_Quest).Index(rd.quest_sid());
	jRETURN_ans_ug_error( pQuest , ERR_QUEST_SID_NOT_FOUND);
	s_tbl_quest* new_quest = pUser->find_tbl_quest(rd.quest_id());
	jRETURN_ans_ug_error( new_quest , ERR_QUEST_ID);

	jGET_BASEBALL_OBJECT(user,better,pitcher,team);
	jRETURN_ans_ug_error( user, ERR_SERVER_DATA);
	jRETURN_ans_ug_error( team, ERR_COND_DEFAULT_TEAM);
	jRETURN_ans_ug_error( pitcher, ERR_COND_DEFAULT_PITCHER);
	jRETURN_ans_ug_error( better, ERR_COND_DEFAULT_BETTER);

	fname_t buf;
	new_quest->set_date_done(nOS::current_SYSTEMTIME(buf));
	new_quest->set_done_count(new_quest->done_count() + 1);
	//jTODO DB update s_tbl_quest.

	
	//#--------------------------------------------------------------------------
	//	퀘스트 보상처리
	//#--------------------------------------------------------------------------

	//보상머니
	user->set_game_money(user->game_money() + pQuest->Get_reward_money());

	//보상경험치
	better->set_exp(better->exp()+pQuest->Get_reward_exp());
	pitcher->set_exp(pitcher->exp()+pQuest->Get_reward_exp());

	//보상호칭값
	jPREPARE_PACKET_UserGateServer_Client(sd , ug2x_quest_end);
	Sys_Title* pTitle = pQuest->Get_title();
	s_tbl_title* title = nDB::add_quest_title(pTitle,pQuest,pUser,new_quest,user,team,better,pitcher);
	if(title)
	{
		s_tbl_title* send_title = sd->add_title();
		if(send_title)
		{
			send_title->CopyFrom(*title);
		}
		else
		{
			jWARN("send_title is NULL");
		}
	}

	//보상 아이템
#	define give_quest_reword_item(ITEM_ENUM,ItemType)\
	case eIC_##ITEM_ENUM:\
		{\
			if(eGrade==eIGT_NULL) break;\
			vector<Sys_Item##ItemType*>& vList=jCSV(Sys_Item##ItemType).m_INDEX_grade[eGrade];\
			jvBREAK(vList.size(),"vList.size()=%d jCSV(Sys_Item%s), eGrade=%s",vList.size(),#ItemType, ToString(eGrade));\
			if(nMOB::random_my(0,100) > item_percent) break;\
			int sid = nMOB::random_my(1,vList.size()-1);\
			Sys_Item##ItemType* pItem = jCSV(Sys_Item##ItemType).Index(sid);\
			jBREAK(pItem);\
			fname_t buf;\
			ja_sprintf(buf,"INSERT_TYPE=%s",pQuest->Get_name());\
			s_tbl_item* item = nDB::insert_item(pUser , sid , eItemCategory , buf);\
			jBREAK(item);\
			s_tbl_item* send_item = sd->add_bonus_items();\
			send_item->CopyFrom(*item);\
			break;\
		}\

#	define give_quest_reword_item_all(NUMBER)\
	{\
		EItemCategory eItemCategory = pQuest->Get_quest_reward_item##NUMBER();\
		EItemGradeType eGrade = pQuest->Get_quest_reward_item_grade##NUMBER();\
		int item_percent= pQuest->Get_quest_reward_percent##NUMBER();\
	switch(pQuest->Get_quest_reward_item1())\
		{\
			for_each_nEXCEL_EItemCategory123(give_quest_reword_item);\
			case eIC_NULL: break;\
			default:\
			{\
				jWARN("unkown type eItemCategory=%d",eItemCategory);\
				break;\
			}\
		}\
	}\
	
	for_each_12(give_quest_reword_item_all);

	sd->mutable_quest()->CopyFrom(*new_quest);
	sd->mutable_user()->CopyFrom(*user);
	sd->mutable_team()->CopyFrom(*team);
	sd->mutable_better()->CopyFrom(*better);
	sd->mutable_pitcher()->CopyFrom(*pitcher);

	return true;// false이면 접속해제한다.
}


jRECV_FROM_CLIENT_TO_UG(req_team_update) // jUser* pUser , s_req_team_update& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_team);
	s_tbl_team* team = pUser->find_tbl_team(rd.team().db_id());
	jRETURN_ans_ug_error( team , ERR_TEAM_SELECT_NOT_EXIST_TEAM);
	if(rd.team().pid_better()!=-1)
	{
		jRETURN_ans_ug_error( pUser->find_tbl_playerbetter(rd.team().pid_better()) , ERR_PLAYER_PID_NOT_FOUND);
	}
	if(rd.team().pid_better()!=-1)
	{
		jRETURN_ans_ug_error( pUser->find_tbl_playerpitcher(rd.team().pid_pitcher()), ERR_PLAYER_PID_NOT_FOUND);
	}
	if(rd.team().name().size())
	{
		jRETURN_ans_ug_error( nDB::check_name(rd.team().name()) , ERR_INVALID_NAME);
	}

	if(rd.team().pid_better()!= -1)
	{
		team->set_pid_better(rd.team().pid_better());
	}
	if(rd.team().pid_pitcher() != -1)
	{
		team->set_pid_pitcher(rd.team().pid_pitcher());
	}
	if(rd.team().name().size())
	{
		team->set_name(rd.team().name());
	}

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_team_update);
	sd->mutable_team()->CopyFrom(*team);
	nProtoHelper::message_print(*team);
	return true;// false이면 접속해제한다.
}


/*

템플릿입니다.

jRECV_FROM_CLIENT_TO_UG(asdf) // jUser* pUser , s_asdf& rd ,UserGateServer_Client& ret
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_);
	jRETURN_ans_ug_error( 1, ERR_);

	jPREPARE_PACKET_UserGateServer_Client(sd , ans_asdf);

	return true;// false이면 접속해제한다.
}
*/
