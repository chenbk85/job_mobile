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
#include <sstream>
#include <boost/format.hpp>
#include <stdlib.h>
#include "protocol/ug.pb.h"
#include "stdafx.h"
#include "logdef.h"


using namespace std;
using namespace MSG;

#define jRECV_FROM_BS2UG(X) bool CB_BaseballServer_UserGateServer(jUser* pUser,const s_##X& rd,UserGateServer_BaseballServer& ret,::Database& db)

/* -------------------------------------------------------------------------- */
#define jMAKE_PACKET_UG2BS(sd, PACKET)\
	ret.set_type(UserGateServer_BaseballServer_Type_##PACKET);\
	s_##PACKET* sd = ret.mutable_m_##PACKET();\



#define jMAKE_PACKET_ug2bs_error(ERROR_SYS_ID)	\
	jMAKE_PACKET_UG2BS(sd , ug2bs_error);\
	sd->set_sys_error_id(jMAKE_ERR(ERROR_SYS_ID));\
	LOG_WARNING(#ERROR_SYS_ID );\

#define jMAKE_PACKET_ug2bs_error_BY_ID(iError)	\
	jMAKE_PACKET_UG2BS(sd , ug2bs_error);\
	sd->set_sys_error_id(iError);\
	LOG_WARNING(nError::ToString(iError) );\


jRECV_FROM_BS2UG(bs2ug_echo) //pUser,s_bs2ug_echo&rd ,UserGateServer_BaseballServer& ret,Database& db
{
	jMAKE_PACKET_UG2BS(sd , ug2bs_echo);

	LOG_DEBUG(rd.msg().c_str() );
	sd->set_type(rd.type());
	sd->set_msg(rd.msg());
	return true;
}

jRECV_FROM_BS2UG(bs2ug_error) //pUser,s_bs2ug_error&rd ,UserGateServer_BaseballServer& ret,Database& db
{
	LOG_DEBUG("");
	return false;
}


// 이 함수는 2번 호출 되며 is_better == true 인 경우가 먼저 호출 됨
jRECV_FROM_BS2UG(bs2ug_game_end) //pUser,s_bs2ug_game_end&rd ,UserGateServer_BaseballServer& ret,Database& db
{
	const s_tbl_result& gr = rd.rg().m_tbl_result();
	jRETURN_ret(false, gr.win_uid()!=gr.lose_uid());
	
	bool isWin = gr.win_uid() == pUser->db_id();
	if( gr.win_score() == gr.lose_score())
	{
		//비겼기때문에 패한것처럼 보상.
		isWin = false;
	}

	jMAKE_PACKET_UG2BS(sd , ug2bs_game_end);	// 받아서 저장한 결과 To 클라이언트
	sd->mutable_rg()->CopyFrom(rd.rg());

	//#--------------------------------------------------------------------------
	// 메모리 선수별 전적 처리.
	//#--------------------------------------------------------------------------

	s_tbl_user* user = pUser->get_tbl_user();	// 유저 정보 업데이트

	if(isWin)
	{
		user->set_win_tot(user->win_tot()+1);							//총전적_승
		user->set_win_season(user->win_season()+1);						//시즌전적_승
		user->set_win_tot_continue( (user->win_tot_continue()>=0) ? (user->win_tot_continue()+1) : 0);//연승패

		if(user->win_tot_continue()>user->win_tot_continue_max())
		{
			user->set_win_tot_continue_max(user->win_tot_continue());	//최대 연승
		}
		// _ORACLE
		user->set_elo_point( user->elo_point() + gr.win_elo_point());	// 통 데이터 -> 가감 데이터로 수정
		LOG_DEBUG("Win_db_id : " << user->db_id());
		LOG_DEBUG("win_tot : " << user->db_id());
		LOG_DEBUG("win_tot_continue : " << user->win_tot_continue());
		LOG_DEBUG("win_season : " << user->win_season());
		LOG_DEBUG("lose_tot : " << user->lose_tot());
		LOG_DEBUG("lose_season : " << user->lose_season());
		LOG_DEBUG("elo_point : " << user->elo_point());
	}
	else
	{
		//총전적_패
		user->set_win_tot_continue( (user->win_tot_continue()<=0) ? (user->win_tot_continue()-1) : 0);
		user->set_lose_season(user->lose_season()+1);	// 시즌전적_패
		user->set_lose_tot(user->lose_tot()+1);			// 시즌전적_패
		user->set_elo_point( user->elo_point() + gr.lose_elo_point());		// 통 데이터 -> 가감 데이터로 수정
		LOG_DEBUG("lose_db_id : " << user->db_id());
		LOG_DEBUG("win_tot : " << user->db_id());
		LOG_DEBUG("win_tot_continue : " << user->win_tot_continue());
		LOG_DEBUG("win_season : " << user->win_season());
		LOG_DEBUG("lose_tot : " << user->lose_tot());
		LOG_DEBUG("lose_season : " << user->lose_season());
		LOG_DEBUG("elo_point : " << user->elo_point());
	}

	//시즌 총_홈런수 ,시즌 탈삼진수 , 총_홈런수	 ,탈삼진수가 	calc_game_round_result 에서 갱신
	pUser->calc_game_round_result(user,rd.rr());	// user 데이터에 통 업데이트
	sd->mutable_user()->CopyFrom(*user);

	// _ORACLE : DB 업데이트 -> 2번 호출 하지만 이 루틴은 한 번만 호출되도록 설계 됨
	if(rd.is_better())	
	{
		LOG_DEBUG("end_type :  " << rd.end_type());
		g_pDB->db_game_result(gr, rd.rr(), rd.end_type());
	}
	
	return true;
}

jRECV_FROM_BS2UG(bs2ug_add_discon_tot) //pUser,s_bs2ug_add_discon_tot&rd ,UserGateServer_BaseballServer& ret,Database& db
{
	//Tbl_User_id_t discon_uid = rd.discon_uid();
	//jTODO DB에 Tbl_User테이블 discon_uid값을 증가 하시오.

	jMAKE_PACKET_UG2BS(sd , ug2bs_add_discon_tot);
	sd->set_discon_uid(rd.discon_uid());
	return true;// 
}



jRECV_FROM_BS2UG(bs2ug_set_cvar) //pUser,s_bs2ug_set_cvar&rd ,UserGateServer_BaseballServer& ret,Database& db
{
	jIVar* pV = nG::g_ECV.get(rd.name().c_str());
	if(!pV)
	{
		LOG_WARNING(rd.name().c_str() << "is not found");
	}
	else
	{
		pV->FromString(rd.val().c_str());

		fname_t buf12;
		LOG_DEBUG(rd.name().c_str() << "=" << pV->ToString(buf12));
	}

	jMAKE_PACKET_UG2BS(sd , ug2bs_ans_set_cvar);
	sd->set_name(rd.name());
	sd->set_val(rd.val());
	return true;
}





/*

템플릿입니다.


jRECV_FROM_BS2UG(asdf) //pUser,s_asdf& rd ,UserGateServer_BaseballServer& ret,Database& db
{
	jMAKE_PACKET_UG2BS(sd , ug2bs_1234);

	LOG_DEBUG(rd.msg().c_str() );
	sd->set_type(rd.type());
	return true;
}

*/
