
/* file : SAMPLE_Room.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:21
comp.: www.neowiz.com
title : 
desc : 


PT_BaseballServer.proto에서 message Client_BaseballServer 에 포함된 메세지를 처리.
	: UMLPAD에서 Client -> BaseballServer로 보낸 패킷을 받는 부분이다.


*/

#include "baseball_user.h"
#include "baseball_room.h"
#include "proto.h"
#include "common/jILog.h"
#include "stdafx.h"

namespace baseball 
{

const int g_TIME_OUT_OFFSET=3;// 

#define jRECV_FROM_X2BS(X) void CB_Client_BaseballServer(baseball::User* pUser, const s_##X& rd)

jRECV_FROM_X2BS(req_ping1) // User* pUser , s_req_ping& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
	jMAKE_MSG_BS2X(sendMsg,sd,ans_pong1);

	sd->set_type(rd.type() );
	sd->set_msg(rd.msg());
	pUser->room()->send(pUser->db_id(), sendMsg);

}


#ifdef DEF__USE_req_timer_start
static void _send_timer_job_req_timer_start( baseball::User* pUser )
{
	jMAKE_MSG_BS2X(sendMsg,sd,ans_timer_start);
	sd->set_count(++pUser->m_iCount_req_timer_start);
	sd->set_msg(pUser->m_s_req_timer_start.msg());

	pUser->room()->send_all(sendMsg);

	void timer_job_req_timer_start(baseball::Room* pRoom, MSG::GameID game_id);	
	pUser->add_timer_wrapper(baseball::Room::E_TIMER_JOB_REQ_TIMER_START,
			boost::posix_time::seconds(pUser->m_s_req_timer_start.term()) 
			boost::bind(timer_job_req_timer_start, _1, pUser->db_id()));
}


void timer_job_req_timer_start(baseball::Room* pRoom, MSG::GameID game_id)
{
	baseball::User* pUser = pRoom->find_user(game_id);
	if (!pUser)
		return;
	jLOG("%s",jFUNC);

    if (pUser->m_s_req_timer_start.term() ==0)
	{
		pUser->m_iCount_req_timer_start=0;
		return ;
	}
	_send_timer_job_req_timer_start(pUser);
}
#endif //#ifdef DEF__USE_req_timer_start

jRECV_FROM_X2BS(req_timer_start) // User* pUser , s_req_timer_start& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

#ifdef DEF__USE_req_timer_start
	int32 term = pUser->m_s_req_timer_start.term();
	pUser->m_s_req_timer_start.CopyFrom(rd);
	if (rd.term()==0)//타이머중지.
	{
		return ;
	}
	//타이머 시작.
	if (term)  return ;//기존 타이머 작동중이면

	_send_timer_job_req_timer_start(pUser);
#endif //#ifdef DEF__USE_req_timer_start

}


jRECV_FROM_X2BS(req_chat) // User* pUser , s_req_chat& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

	jMAKE_MSG_BS2X(sendMsg,sd,ans_chat);
	sd->set_type(rd.type());
	sd->set_msg(rd.msg());
	sd->set_etc(rd.etc());
// 	switch(rd.type())
// 	{
// 	case 0:
// 		{
// 			break;
// 		}
// 	case 1:
// 		{
// 			break;
// 		}
// 	}
	pUser->room()->send_all(sendMsg);
}

jRECV_FROM_X2BS(req_do_disconnect) // User* pUser , s_req_do_disconnect& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
}


jRECV_FROM_X2BS(req_ping2) // User* pUser , s_asdf& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

	jMAKE_MSG_BS2X(sendMsg,sd,ans_pong2);
	sd->set_type(rd.type());
	sd->set_msg(rd.msg());
	sd->set_etc(333);
	pUser->room()->send(pUser->db_id(), sendMsg);

}


void time_out_req_better_hit(baseball::Room* pRoom)
{
	// jTODO 서버에서 타자 타격 대기시간이 넘었을때처리
	jRETURN(pRoom);
	jFUNC_LOG2("Room",pRoom->id());

	baseball::User* pUser = pRoom->get_current_better();
	jRETURN(pUser);

	nBASE_BALL::make_random_better_hit(&pRoom->m_req_better_hit);

	jMAKE_MSG_BS2X(sendMsg,sd,ans_better_hit);
	sd->mutable_info()->CopyFrom(pRoom->m_req_better_hit.info());
	sd->set_is_auto(true);//자동으로 타자 치는 동작.
	pRoom->send_all(sendMsg);
	static int s_i=0;
	jLOG("ans_better_hit를 보냄.: %d",s_i++);
}

void time_out_req_pitcher_throw(baseball::Room* pRoom)
{
	jFUNC_LOG2("Room",pRoom->id());
	baseball::User* pUser = pRoom->get_current_pitcher();
	jRETURN(pUser);
	nBASE_BALL::make_random_pitcher_throw(&pRoom->m_req_pitcher_throw);
	pRoom->send_ans_pitcher_throw(pRoom->m_req_pitcher_throw,true);
}



jRECV_FROM_X2BS(req_team_match_ready) // User* pUser , s_req_team_match_ready& rd ,UserGateServer_Client& ret
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
	
	jRETURN(!pUser->is_ready());
	jCHECK(pUser->db_id() == rd.uid());
	//jRETURN_ERROR(pRoom->get_s_game_play_info_Other(pUser->id()) , );

	pRoom->send_ans_team_match_ready(rd.uid());

}

void time_out_req_result_better_hit(baseball::Room* pRoom)
{
	baseball::User* pUser = pRoom->get_current_better();
	jRETURN(pUser);
	// todo : pudae : 아래 코드는 무슨 로직? 
	jRETURN_ERROR(jS(time_out_req_result_better_hit)==0,ERR_TIME_OUT_req_better_hit );
}


jRECV_FROM_X2BS(req_pitcher_throw) // User* pUser , s_req_pitcher_throw& rd ,UserGateServer_Client& ret
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

	jRETURN(pRoom->get_attack_uid() != pUser->db_id());
	//jTODO : 차후 이걸로 바꿔야함. jRETURN_ERROR(pRoom->get_attack_uid() != pUser->id()		,ERR_SERVER_DATA);// 투수 여부 체크

// 	jRETURN_ERROR(pUser->check_breaking_ball_type(rd.breaking_ball_type() ) ,ERR_SERVER_DATA);sdf
// 	jRETURN_ERROR(pUser->check_ball_focus(rd.ball_focus())		,ERR_SERVER_DATA);

	jRETURN(pUser->get_m_e_user_gps()==eUGPS_GAME_ROUND_START);
	pUser->set_m_e_user_gps(eUGPS_PITCHER_THROW);
	pRoom->m_req_pitcher_throw.CopyFrom(rd);// 투구 정보 저장
#ifdef SERVER_AUTO_PLAY
	pRoom->remove_timer_wrapper(baseball::Room::E_TIME_OUT_REQ_PITCHER_THROW);
#endif

	if(!pRoom->is_auto_play()) //정상적인상황.
	{
		pRoom->send_ans_pitcher_throw(rd,false);
		return ;
	}

#ifdef SERVER_AUTO_PLAY
	//상대방 비정상 종료로 인한 자동플레이상황
	//BB_5.2.8_UG_match_round_user_out.usd의 내용대로 서버는 클라가 req_result_better_hit를 보낼때까지 기다린다.
	pRoom->add_timer_wrapper(baseball::Room::E_TIME_OUT_REQ_RESULT_BETTER_HIT,
					MAX_TIME_RECV_ROUND_RESULT_WHEN_USER_DISCONN,
					time_out_req_result_better_hit);
#endif

}


jRECV_FROM_X2BS(req_better_hit) // User* pUser , s_req_better_hit& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
	//내가 타자모드이냐? (자동플레이 감안)
	jRETURN_ERROR(pUser->is_attackable() , ERR_req_better_hit_IS_NOT_BETTER);
	//내가 공을 칠수 있는 상태이냐?
	jRETURN(pUser->get_m_e_user_gps()==eUGPS_GAME_ROUND_START);
	//상대방(투수)이 공을 던졌는냐?
	s_game_play_info* gpi_pitcher= pRoom->get_s_game_play_info_Other(pUser->db_id());
	jRETURN(gpi_pitcher && gpi_pitcher->m_e_user_gps() == eUGPS_PITCHER_THROW);

	pUser->set_m_e_user_gps(eUGPS_BETTER_HIT);
#ifdef SERVER_AUTO_PLAY
	pUser->room()->remove_timer_wrapper(baseball::Room::E_TIME_OUT_REQ_BETTER_HIT);
#endif
	pUser->room()->m_req_better_hit.CopyFrom(rd);

	jMAKE_MSG_BS2X(sendMsg,sd,ans_better_hit);
	sd->mutable_info()->CopyFrom(rd.info());
	sd->set_is_auto(false);//자동으로 타자 치는 동작 아님.
	pUser->room()->send_all(sendMsg);

}

// void timer_TIME_GAME_ROUND_END(Room* pRoom)
// {
// 	jMAKE_MSG_BS2X(sendMsg,sd,ans_game_end);
// 	sd->mutable_rg()->CopyFrom(pRoom->m_GameRoomInfo.m_result_game());
// 	pRoom->send_all(sendMsg);
// }

void timer_TIME_GAME_ROUND_TEAMCHANGE(baseball::Room* pRoom)
{
	jMAKE_MSG_BS2X(sendMsg,sd,ans_change_attack_team);
	sd->set_round(pRoom->get_round_count());

	Tbl_User_id_t better = pRoom->get_attack_uid();
	s_game_play_info* pNewBetter = pRoom->get_s_game_play_info_Other(better);
	jRETURN(pNewBetter);
	Tbl_User_id_t new_better = nPH::get_db_id(pNewBetter);
	pRoom->m_GameRoomInfo.set_m_attack_user(new_better);
	jCHECK(pRoom->get_attack_uid() == new_better);
	sd->set_attack_user(new_better);
	pRoom->send_all(sendMsg);
	pRoom->add_timer_wrapper(baseball::Room::E_TIMER_JOB_ANS_GAME_ROUND_START,
			nG::i_TIME_GAME_ROUND_CHANGE_TEAM->Get_int(),
			timer_job_ans_game_round_start);
}

//#--------------------------------------------------------------------------
//한 라운드 종료.
//#--------------------------------------------------------------------------
jRECV_FROM_X2BS(req_result_better_hit) // User* pUser , s_req_result_better_hit& rd
{
	jLOG("\n\njRECV_FROM_CLIENT_TO_BS(req_result_better_hit)\n\n");
	jDEFAULT_CHECK_BS(pUser,pRoom);
	jRETURN_ERROR(pUser->is_attackable() , ERR_req_better_hit_IS_NOT_BETTER);

	EUserGPS eState = pUser->get_m_e_user_gps();
	jRETURN(eState==eUGPS_GAME_ROUND_START || eState==eUGPS_BETTER_HIT);
	pUser->set_m_e_user_gps(eUGPS_BETTER_HIT_RESULT);

	//날라온 결과 재확인.
	const s_tbl_roundresult &rr = rd.info().m_tbl_roundresult();
	EBatterHitType eType = (EBatterHitType)rr.hit_type();
	jLOG("eType = %s,%d",ToString(eType),eType);
	jRETURN_ERROR(IsValid(eType) , ERR_ROUND_RESULT_MISSMATCH);
	s_result_round rr_server;

	ERunnerStateRound get_round_state(round_t, Sys_Runner_State_id_t sid);
	ERunnerStateRound eRSType = get_round_state(pRoom->get_round_count(), pRoom->Get_Curr_RSR() );

	pRoom->make_round_result(&rr_server,eType,eRSType);

	s_tbl_roundresult &rr2 = *rr_server.mutable_m_tbl_roundresult();
// 	jLOG("client data");
// 	nProtoHelper::message_print(rr,pUser->db_id());
// 	jLOG("server data");
// 	nProtoHelper::message_print(rr2,pUser->db_id());

	//jTODO 차후 검증 :jRETURN_ERROR(nProtoHelper::is_equal(rr, rr2) , ERR_req_better_hit_IS_NOT_BETTER);
	rr2.set_grid(pRoom->m_GameRoomInfo.m_result_game().m_tbl_result().db_id());
	s_result_round* pRR = pRoom->m_GameRoomInfo.add_m_result_round();
	pRR->CopyFrom(rr_server);

#ifdef SERVER_AUTO_PLAY
	pRoom->remove_timer_wrapper(baseball::Room::E_TIME_OUT_REQ_RESULT_BETTER_HIT);
	// 만약 타자가 파울등의 아웃이면 req_better_hit대신 바로 req_result_better_hit가 날라 온다.
	pRoom->remove_timer_wrapper(baseball::Room::E_TIME_OUT_REQ_BETTER_HIT);
#endif

	jMAKE_MSG_BS2X(sendMsg,sd,ans_result_better_hit); // 받은 결과를 투수에게 전달.
	
	//jTODO 
	sd->mutable_info()->CopyFrom(rd.info());
	pUser->room()->send_all_except_me(sendMsg,pUser->db_id());

	int32 iNextRound = pRoom->get_round_count() +1;
	jLOG("curr calculated round = %d", iNextRound);

	//#--------------------------------------------------------------------------
	// 게임을 종료하는 조건.
	//#--------------------------------------------------------------------------
	if( iNextRound >= pRoom->m_i_TOTAL_ROUND * DEF_i_MAX_PLAYING_USER) 
	{
		set_EUserGPS func(eUGPS_GAME_END);
		pRoom->for_each_s_game_play_info(func);
//		jLOG("두팀 모두 게임완료. 게임종료.curr=%d m_i_TOTAL_ROUND=%d , m_i_ATTACK_CHANGE_ROUND=%d",iNextRound, pRoom->m_i_TOTAL_ROUND,pRoom->m_i_ATTACK_CHANGE_ROUND);

		//#--------------------------------------------------------------------------
		// 게임 결과 계산. ( 보너스 경험치 & 게임머니)
		//#--------------------------------------------------------------------------
		pRoom->calc_game_result();
		s_result_game* rg = pRoom->m_GameRoomInfo.mutable_m_result_game();

// 		nProtoHelper::message_print(rg->m_tbl_result(),pUser->db_id());

#if jUSE_TIMED_GAME_END_RESULT
		pRoom->add_timer_wrapper(
				baseball::Room::E_TIMER_TIME_GAME_ROUND_END, 
				nG::i_TIME_GAME_ROUND_END->Get_int(),
				timer_TIME_GAME_ROUND_END);
#endif

		{
			jMAKE_MSG_BS2UG(sendMsg,sd,bs2ug_game_end);
			sd->mutable_rg()->CopyFrom(*rg);
			sd->set_is_better(true);
			pRoom->send_to_ug(pUser->db_id() , sendMsg);
			sd->set_is_better(false);
			pRoom->send_all_except_me_to_ug(sendMsg, pUser->db_id());

			baseball::User* pOtherUser = pRoom->get_other_user(pUser->db_id());
			jRETURN_ERROR(pOtherUser , ERR_SERVER_DATA_UID_DISMATCH);

#ifdef SERVER_AUTO_PLAY
			void send_ans_answer_restart_game(Room* pRoom,Tbl_User_id_t uid1, bool ok1, Tbl_User_id_t uid2, bool ok2);
			pRoom->add_timer_wrapper(
					baseball::Room::E_SEND_ANS_ANSWER_RESTART_GAME,
					nG::i_TIME_GOTO_LOBBY_WHEN_GAME_END->Get_int(),
					boost::bind(send_ans_answer_restart_game, _1, pUser->db_id(), false, pOtherUser->db_id(), false));
#endif

		}

		return ;
	}

	//#--------------------------------------------------------------------------
	//공수를 교대하는 조건.
	//#--------------------------------------------------------------------------
	bool isChange = false;
	if( !(iNextRound % pRoom->m_i_ATTACK_CHANGE_ROUND ))
	{
// 		jLOG("공수 교대 1.curr=%d m_i_TOTAL_ROUND=%d , m_i_ATTACK_CHANGE_ROUND=%d m_i_CheckRound=%d"
// 			,iNextRound, pRoom->m_i_TOTAL_ROUND,pRoom->m_i_ATTACK_CHANGE_ROUND,pRoom->m_i_CheckRound);

		isChange = true;
	}

	if(iNextRound == pRoom->m_i_CheckRound)
	{
		isChange = true;
	}

	if( !isChange && iNextRound > pRoom->m_i_CheckRound )
	{
		const round_t halfRound = (pRoom->m_i_TOTAL_ROUND % pRoom->m_i_ATTACK_CHANGE_ROUND);
		round_t lastRound = iNextRound - pRoom->m_i_CheckRound;
		if( lastRound >= halfRound )
		{
// 			jLOG("공수 교대 2.curr=%d m_i_TOTAL_ROUND=%d , m_i_ATTACK_CHANGE_ROUND=%d, m_i_CheckRound=%d"
// 				,iNextRound, pRoom->m_i_TOTAL_ROUND,pRoom->m_i_ATTACK_CHANGE_ROUND,pRoom->m_i_CheckRound);
			isChange= true;
		}
	}
	if(isChange) 
	{
		//#--------------------------------------------------------------------------
		// 상대 팀으로 공격권을 넘긴다.
		//#--------------------------------------------------------------------------
		set_EUserGPS func(eUGPS_ATTACK_USER_CHANGED);
		pRoom->for_each_s_game_play_info(func);

// 		jLOG("공수 교대.curr=%d m_i_TOTAL_ROUND=%d , m_i_ATTACK_CHANGE_ROUND=%d, m_i_CheckRound=%d"
// 			,iNextRound, pRoom->m_i_TOTAL_ROUND,pRoom->m_i_ATTACK_CHANGE_ROUND,pRoom->m_i_CheckRound);
		pRoom->m_GameRoomInfo.set_m_round_count(iNextRound);
		pRoom->add_timer_wrapper(baseball::Room::E_TIMER_TIME_GAME_ROUND_TEAMCHANGE,
				nG::i_TIME_GAME_ROUND_TEAMCHANGE->Get_int(),
				timer_TIME_GAME_ROUND_TEAMCHANGE);

		return ;
	}

	//#--------------------------------------------------------------------------
	// 다음 라운드 진행.
	//#--------------------------------------------------------------------------

	pRoom->m_sid_RunnerState_index=1;
	jLOG("Go next round! curr=%d m_i_TOTAL_ROUND=%d , m_i_ATTACK_CHANGE_ROUND=%d,m_i_CheckRound=%d",iNextRound, pRoom->m_i_TOTAL_ROUND,pRoom->m_i_ATTACK_CHANGE_ROUND,pRoom->m_i_CheckRound);
	pRoom->m_GameRoomInfo.set_m_round_count(iNextRound);
	pRoom->add_timer_wrapper(baseball::Room::E_TIMER_JOB_ANS_GAME_ROUND_START,
			nG::i_TIME_GAME_ROUND->Get_int(),
			timer_job_ans_game_round_start);

}

jRECV_FROM_X2BS(req_room_state) // User* pUser , s_req_room_state& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
	
	jMAKE_MSG_BS2X(sendMsg,sd,ans_room_state);
	sd->mutable_gri()->CopyFrom(pRoom->m_GameRoomInfo);
	pUser->room()->send_all(sendMsg);

}

static void send_cvar(baseball::User*pUser, tcstr value)
{
	jMAKE_MSG_BS2X(sendMsg,sd,ans_pong1);
	sd->set_type(IS_REQ_GET_CVAR_STRING);
	sd->set_msg(value);
	pUser->room()->send_all(sendMsg);
}



#define jLAMDA_get_cvar_list(X,Z) Z(tstring& , cvar_list)
jLAMDA_for_each(get_cvar_list,jExcel_ConstVar::for_each_it_t)
{
	fname_t buf;
	tstring str = it.first;
	str += "=";
	str += it.second->ToString(buf);
	str += "\n";
	cvar_list += str;
}
jLAMDA_end();

jRECV_FROM_X2BS(req_get_cvar) // User* pUser , s_req_get_cvar& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

	fname_t buf;
	jIVar* pV = nG::g_ECV.get(rd.name().c_str());
	if(!pV)
	{
		jt_sprintf(buf, "%s is not found", rd.name().c_str());
		tstring cvar_list;
		
		jExcel_ConstVar::for_each_fn_t func = get_cvar_list(cvar_list);
		nG::g_ECV.for_each(func);
		send_cvar(pUser, cvar_list.c_str());
		return ;
	}
	else
	{
		fname_t buf12;
		jt_sprintf(buf, "%s =%s", rd.name().c_str() , pV->ToString(buf12));
	}


	send_cvar(pUser, buf);
}


jRECV_FROM_X2BS(req_set_cvar) // User* pUser , s_req_set_cvar& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

	fname_t buf;
	jIVar* pV = nG::g_ECV.get(rd.name().c_str());
	if(!pV)
	{
		jt_sprintf(buf, "%s is not found", rd.name().c_str());
	}
	else
	{
		pV->FromString(rd.val().c_str());

		fname_t buf12;
		jt_sprintf(buf, "%s =%s",rd.name().c_str() , pV->ToString(buf12));
	}
	nG::g_ECV.save_to_xml(CONSOLEVAR_XML_FILE);

	send_cvar(pUser,buf);

	jMAKE_MSG_BS2UG(sendMsg,sd, bs2ug_set_cvar);
	sd->set_name(rd.name());
	sd->set_val(rd.val());
	pRoom->send_all_to_ug(sendMsg);
}

void timer_user_goto_lobby(baseball::Room* pRoom,Tbl_User_id_t uid)
{
	jRETURN(pRoom);
	baseball::User* pUser = pRoom->find_user(uid);
	jRETURN(pUser);
	pRoom->kick_out(uid, MSG::EXIT_RESERVATION, "");
	//pRoom->leave(pUser,true);
}

#define jLAMDA_user_goto_lobby(X,Z) Z(baseball::Room*,pRoom)
jLAMDA_for_each(user_goto_lobby,baseball::User*) // it
{
	jRETURN(pRoom);
	jRETURN(it);
	int uid = it->db_id();
	jRETURN(uid);
	fname_t szName;
	jt_sprintf(szName , "timer_user_goto_lobby_%d",uid);
	jLOG("reg : %s",szName );

	pRoom->add_timer_wrapper(
			baseball::Room::E_TIMER_USER_GOTO_LOBBY, 
			1, 
			boost::bind(timer_user_goto_lobby, _1, uid));
}
jLAMDA_end();



void send_ans_answer_restart_game(baseball::Room* pRoom,Tbl_User_id_t uid1, bool ok1, Tbl_User_id_t uid2, bool ok2)
{
// 	print_EUserGPS func1;
// 	pRoom->for_each_s_game_play_info(func1);
	find_EUserGPS func(eUGPS_GAME_END);
	s_game_play_info* gpi2= pRoom->find_if_s_game_play_info(func);
	jvRETURN( gpi2==0 ,"find = %d", gpi2->m_e_user_gps() );

	jMAKE_MSG_BS2X(sendMsg,sd,ans_answer_restart_game);
	sd->add_uid(uid1);
	sd->add_ok(ok1);
	sd->add_uid(uid2);
	sd->add_ok(ok2);
	pRoom->send_all(sendMsg);
	jLOG("pRoom->send_all(sendMsg);ans_answer_restart_game");
	
	if(ok1 && ok2)
	{
		pRoom->add_timer_wrapper(baseball::Room::E_TIMER_JOB_ANS_GAME_START,
				nG::i_TIME_ALL_PLAYER_NOT_READY->Get_int(),
				timer_job_ans_game_start);
	}
	else
	{
		user_goto_lobby func(pRoom);
		pRoom->for_each_User(func);
	}
}

jRECV_FROM_X2BS(req_rematch) // User* pUser , s_req_rematch& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
	jRETURN_ERROR(pUser->db_id()==rd.uid() , ERR_SERVER_DATA_UID_DISMATCH);


	s_game_play_info* gpi = pRoom->get_s_game_play_info_Other(rd.uid());
	jRETURN_ERROR(gpi, ERR_SERVER_DATA_UID_DISMATCH);
	baseball::User* pOtherUser= pRoom->get_other_user(rd.uid());
	jRETURN_ERROR(pOtherUser, ERR_SERVER_DATA_UID_DISMATCH);

	pUser->is_allow_rematch=true;
	if(!pOtherUser->is_allow_rematch)// 허락하지 않은상태이면 물어봄.
	{
		jMAKE_MSG_BS2X(sendMsg,sd,ans_rematch);
		sd->set_uid(rd.uid());
		pRoom->send_all_except_me(sendMsg, pUser->db_id());
		return ;
	}

	//허락한 상태이면 모두에게 재경기 통보.
	pRoom->remove_timer_wrapper(baseball::Room::E_SEND_ANS_ANSWER_RESTART_GAME);
	send_ans_answer_restart_game(pRoom, pUser->db_id() , true, pOtherUser->db_id(), true);
}

jRECV_FROM_X2BS(req_answer_restart_game) // User* pUser , s_req_answer_restart_game& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
	baseball::User* pOtherUser = pRoom->get_other_user(pUser->db_id());
	jRETURN_ERROR(pOtherUser, ERR_SERVER_DATA_UID_DISMATCH);

	pUser->is_allow_rematch=rd.ok();
	pRoom->remove_timer_wrapper(baseball::Room::E_SEND_ANS_ANSWER_RESTART_GAME);
	send_ans_answer_restart_game(pRoom, pUser->db_id() , rd.ok(), pOtherUser->db_id(), true);
}




/*

템플릿입니다.

jRECV_FROM_X2BS(asdf) // User* pUser , s_asdf& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
}

*/
	
} /* baseball */


