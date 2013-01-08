


/* file : Recv_BaseballServer_Client.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-03-22 14:45:39
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"




#define jRECV_FROM_BaseballServer(MSG,...) bool On_BaseballServer_Client_##MSG(RECV_PARAM_PlugIn_BaseballClient,const s_##MSG & rd)


jRECV_FROM_BaseballServer(ans_join_room,pPlugIn , peSession,  pUser, const s_ans_join_room1& rd) 
{
	nProtoHelper::message_print(rd.gri());
	pUser->m_GameRoomInfo.CopyFrom(rd.gri());
	return true; 
}
jRECV_FROM_BaseballServer(bs2x_echo	,pPlugIn , peSession,  pUser, const s_bs2x_echo& rd) 
{
	if(rd.type()==IS_REQ_GET_CVAR_STRING)
	{
		jLOG_USER(_T("%s") , rd.msg().c_str());
		return true;
	}
	static int64 server_time=rd.bs_time_msec();
	jLOG_USER(_T("bs2x_echo : client_time=%d , bs_time=%I64d , %s" )
		,timeGetTime()-rd.client_time_msec()
		,rd.bs_time_msec()-server_time, rd.msg().c_str());
	server_time = rd.bs_time_msec();

	/*
	jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,x2bs_echo2);
	sd->set_msg("x2bs_echo2 msg");
	sd->set_type(888);
	sd->set_client_time_msec(timeGetTime());
	pPlugIn->send_to_bs(peSession,sendMsg);
	*/
	if (rd.type() == 100 )
	{
		jLOG_USER(_T("%s bs2x_echo : echo from other : Echo type = %d"), __FUNCTION__, rd.type() );
		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,x2bs_echo);
		sd->set_msg("x2bs_echo msg");
		sd->set_type(101);
		sd->set_client_time_msec(timeGetTime());
		pPlugIn->send_to_bs(peSession,sendMsg);
	}
	else if (rd.type() == 101 )
	{
		jLOG_USER(_T("%s bs2x_echo : echo from me  : Echo type = %d"), __FUNCTION__, rd.type() );
	}

	return true; 
}
jRECV_FROM_BaseballServer(ans_chat	,pPlugIn , peSession,  pUser, const s_ans_chat& rd) 
{
	
	return true; 
}
jRECV_FROM_BaseballServer(ans_timer_start ,pPlugIn , peSession,  pUser, const s_ans_timer_start& rd) 
{
	
	return true; 
}


jRECV_FROM_BaseballServer(bs2x_echo2 ,pPlugIn , peSession,  pUser, const s_bs2x_echo2& rd) 
{
	static int64 server_time=rd.bs_time_msec();
	jLOG_USER(_T("bs2x_echo2 : client_time=%d , bs_time=%I64d , %s" )
		,timeGetTime()-rd.client_time_msec()
		,rd.bs_time_msec()-server_time, rd.msg().c_str());
	server_time = rd.bs_time_msec();

	return true; 
}


jRECV_FROM_BaseballServer( bs2x_auto_match_ready2,pPlugIn , peSession,  pUser, const s_bs2x_auto_match_ready2& rd) 
{
	jCHECK(pUser->db_id()== pUser->game_id);
	s_game_play_info* gpi= pUser->get_s_game_play_info(rd.uid());
	jvRETURN_ret(true, gpi, _T("gpi= pUser->get_ game_play_info(%d); == NULL"),rd.uid());
	gpi->set_m_e_user_gps(eUGPS_GAME_READY);

	if(pUser->IsAutoPlay())
	{
		if( rd.uid() == pUser->db_id())
		{
			fname_t szCmd;
			jt_sprintf(szCmd,_T("@game.x2bs_match_ready %I64d"),pUser->db_id());
			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
		}
	}
	else
	{
		pUser->m_iAutoMatchCount = 0;
		jLOG_USER_T("유저 : %d : 레디상태",rd.uid());
		jLOG_USER_T("batter : %d : ",rd.batter());
		jLOG_USER_T("pitcher: %d : ",rd.pitcher());
		jLOG_USER_T("other batter : %d : ",rd.other_batter());
		jLOG_USER_T("other pitcher: %d : ",rd.other_pitcher());
	}
	return true;
}

jRECV_FROM_BaseballServer( ans_game_start,pPlugIn , peSession,  pUser, const s_ans_game_start& rd) 
{
	pUser->m_GameRoomInfo.clear_m_result_round();
	pUser->m_GameRoomInfo.clear_m_result_game();

	pUser->m_GameRoomInfo.set_m_attack_user(rd.attack_user());
	pUser->m_eEUserGPS = eUGPS_GAME_START;
	if(pUser->IsAutoPlay())
	{

	}
	else
	{
		if(pUser->db_id() == rd.attack_user())
		{
			jLOG_USER_T("내가 공격자 : %d" , rd.attack_user());
		}
		else
		{
			jLOG_USER_T("나는 투수 : %d , recv=%d" , pUser->db_id(), rd.attack_user());
		}
	}

	return true;
}

jRECV_FROM_BaseballServer(ans_game_round_start ,pPlugIn , peSession,  pUser, const s_ans_game_round_start& rd) 
{
	//D:\svn\baseball\야구 1라운드 프로토콜 설계\야구 시나리오5.usd 참고.

	pUser->m_ERunnerStateRound = (ERunnerStateRound)rd.runner_state();
	jCHECK(pUser->m_ERunnerStateRound > eBEGIN_ERunnerStateRound && pUser->m_ERunnerStateRound < eEND_ERunnerStateRound);
	pUser->m_eEUserGPS = eUGPS_GAME_ROUND_START;
	pUser->m_GameRoomInfo.set_m_round_count(rd.round());
		
		if(pUser->IsAutoPlay())
		{
			if(pUser->is_attackable())//jTODO 타자면 타격 조작 시작 가능.
			{
				fname_t szCmd;
				jt_sprintf(szCmd , _T("@game.x2bs_batter_ready %I64d"),pUser->db_id());
				nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
			}
			else//투수면 클라이언트 투수연출 시작. 
			{

			}
		}
		else
		{
			jLOG_USER_T("round = %d, runner_state=%s", rd.round() , ToString((ERunnerStateRound)rd.runner_state()));

		}

	return true; 
}

jRECV_FROM_BaseballServer( ans_pitcher_throw,pPlugIn , peSession,  pUser, const s_ans_pitcher_throw& rd) 
{
	//D:\svn\baseball\야구 1라운드 프로토콜 설계\야구 시나리오5.usd 참고.
	pUser->m_eEUserGPS = eUGPS_PITCHER_THROW;
	pUser->m_ans_pitcher_throw.CopyFrom(rd);

	if(rd.is_auto())
	{
		//GAME_PITCHER_THROW_WAIT_TIME_COUNT에 의해 서버에서 자동으로 투수 투구동작을 실행한것이다.
	}
	
	if(pUser->is_attackable())//이제 타자는 칠수 있는 상태이다.
	{
		if(pUser->IsAutoPlay())
		{
			fname_t szCmd;
			jt_sprintf(szCmd , _T("@game.req_better_hit %I64d"), pUser->db_id());
			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
		}
	}
	else//투수이면 가) 나) 단계의 연출 시작.
	{
		
	}
	
	return true;
}

jRECV_FROM_BaseballServer(ans_better_hit ,pPlugIn , peSession,  pUser, const s_ans_better_hit& rd) 
{
	//jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_temp);
	pUser->m_eEUserGPS = eUGPS_BETTER_HIT;
	pUser->m_ans_better_hit.CopyFrom(rd);

	if(rd.is_auto())
	{
		//서버에서 GAME_BATTER_HIT_WAIT_TIME_COUNT에 의해 자동으로 타자 치기 동작이 수행된것임.
		// 타자 클라 화면에 치는 동작(또는 스윙/파울) 수행.
	}

	if(pUser->is_attackable())//이제 타자는 계산결과값을 서버로 전송하여 데이타 검증.
	{
		if(pUser->IsAutoPlay())
		{
		}
		else
		{
			jLOG_USER_T("내가 공격자이므로  결과를 보냄 me = %d , attacker=%d",pUser->db_id() , pUser->get_attack_uid());
		}
		pUser->send_req_result_better_hit(rd);
	}
	else//투수이면 결과값을 계산후 화면에 연출.
	{
		if(pUser->IsAutoPlay())
		{
		}
		else
		{
			jLOG_USER_T("나는 투수이므로 가만히 있다 me = %d , attacker=%d",pUser->db_id() , pUser->get_attack_uid());
		}
	}

	return true; 
}


jRECV_FROM_BaseballServer(ans_bs_error ,pPlugIn , peSession,  pUser, const s_ans_bs_error& rd) 
{
	Sys_Error_id_t iError = rd.sys_error_id() ;
	Sys_Error* p = jCSV(Sys_Error).Index( iError);
	if(p)
	{
		jWARN_T("[%I64d]%s : %s", pUser->db_id(),p->Get_name(), p->Get_help());
	}
	else
	{
		jWARN_T("[%I64d]unkown error : %d",  pUser->db_id(),rd.sys_error_id());
	}
	//pUser->m_iAutoMatchCount=-1;// stop auto play;
	return true; 
}

jRECV_FROM_BaseballServer(ans_room_state ,pPlugIn , peSession,  pUser, const s_ans_room_state& rd) 
{
	nProtoHelper::message_print(rd.gri());
	return true; 
}

jRECV_FROM_BaseballServer(ans_change_attack_team ,pPlugIn , peSession,  pUser, const s_ans_change_attack_team& rd) 
{
	//jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_temp);
	pUser->m_GameRoomInfo.set_m_attack_user(rd.attack_user() );

	if(pUser->IsAutoPlay())
	{
	}
	else
	{
		jLOG_USER_T("공격자 바뀜 : %d", rd.attack_user());
		if(pUser->db_id() == rd.attack_user())
		{
			jLOG_USER_T("내가 공격자 : %d" , rd.attack_user());
		}
		else
		{
			jLOG_USER_T("나는 투수 : %d , recv=%d" , pUser->db_id(), rd.attack_user());
		}
	}

	return true; 
}

jRECV_FROM_BaseballServer(ans_game_end ,pPlugIn , peSession,  pUser, const s_ans_game_end& rd) 
{
	jRETURN_ret(true,pUser->get_tbl_user());
	pUser->get_tbl_user()->CopyFrom(rd.user());
	pUser->m_eEUserGPS = eUGPS_GAME_END;
	//jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_temp);
	if(pUser->IsAutoPlay())
	{
	}
	else
	{
		nProtoHelper::message_print(rd.user());
	}
	nProtoHelper::message_print(rd.rg().m_tbl_result(),pUser->db_id(),pv_IsAutoPlay->Get_bool() ? true : false);
	jLOG_USER_T("ans_game_end : end_type : %d", rd.end_type());


	return true; 
}

jRECV_FROM_BaseballServer(ans_result_better_hit ,pPlugIn , peSession,  pUser, const s_ans_result_better_hit& rd) 
{
	//jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_temp);
	s_result_round* rr = pUser->m_GameRoomInfo.add_m_result_round();
	rr->CopyFrom(rd.info());
	jLOG_USER_T("ans_result_better_hit : end_type : %d", rd.end_type());

	nProtoHelper::message_print(rd.info().m_tbl_roundresult());

	return true; 
}

jRECV_FROM_BaseballServer(ans_user_disconnect ,pPlugIn , peSession,  pUser, const s_ans_user_disconnect& rd) 
{
	//jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_temp);
	s_game_play_info* gpi = pUser->get_s_game_play_info(rd.uid());
	jvRETURN_ret(true,gpi, _T("user not found = %d"), rd.uid());
	gpi->set_m_e_user_gps(eUGPS_BS_ABNORMAL_DISCONNECT);
	pUser->m_GameRoomInfo.set_m_is_auto_play(true);

	pUser->m_iAutoMatchCount=0;
	return true; 
}

jRECV_FROM_BaseballServer(ans_answer_restart_game ,pPlugIn , peSession,  pUser, const s_ans_answer_restart_game& rd) 
{
	//jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_temp);
	jRETURN_ret(true, rd.ok_size()==2 && rd.uid_size()==2);

	if(pUser->IsAutoPlay())
	{
		if(rd.ok(0) && rd.ok(1))
		{
			//재매치 시작
				fname_t szCmd;
				//jt_sprintf(szCmd,_T("@game.req_answer_restart_game %I64d true"),pUser->db_id());
				jt_sprintf(szCmd,_T("@game.x2bs_match_ready %I64d"),pUser->db_id());
				nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
		}
		else
		{
			//로비로 이동한다.
			// 서버는 자동으로 로비로 이동시킨다.
			// 클라이언트는 @game.UReqLeaveGame <uid>를 안보내도 된다.
		}
	}
	else
	{
		jLOG_USER_T("uid1=%I64d:%s , uid2=%I64d:%s,  baseball_park=%d  "
			, rd.uid(0), rd.ok(0)?"수락":"거절" 
			, rd.uid(1) , rd.ok(1)?"수락":"거절" 
			, rd.baseball_park());

		jLOG_USER_T("attack_user : %d", rd.attack_user());

	}
	
	return true; 
}


jRECV_FROM_BaseballServer(ans_rematch ,pPlugIn , peSession,  pUser, const s_ans_rematch& rd) 
{
	//jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_temp);
	pUser->is_allow_rematch_other=true;
	if(pUser->IsAutoPlay())
	{
	}
	else
	{
		jLOG_USER_T("재매치 요구 :@game.req_answer_restart_game %I64d <is_ok=true | false> 으로 응답하세요",pUser->db_id());
	}
	return true; 
}

// client 에서 로딩 완료후 bs2x_match_ready를 클라가 보내면 받는 부분.
jRECV_FROM_BaseballServer(bs2x_match_ready ,pPlugIn , peSession,  pUser, const s_bs2x_match_ready& rd) 
{
	if(pUser->IsAutoPlay())
	{
	}
	else
	{
		jLOG_USER_T("ready uid : %I64d ",rd.uid());
	}

	return true; 
}

jRECV_FROM_BaseballServer(bs2x_batter_ready ,pPlugIn , peSession,  pUser, const s_bs2x_batter_ready& rd) 
{
	pUser->m_eEUserGPS = eUGPS_GAME_BATTER_READY;

	if(pUser->is_attackable())
	{
	}
	else
	{
		if(pUser->IsAutoPlay())
		{
			fname_t szCmd;
			jt_sprintf(szCmd , _T("@game.req_pitcher_throw  %I64d"), pUser->db_id());
			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
		}
	}

	return true; 
}


jRECV_FROM_BaseballServer(bs2x_game_end_other_user_info ,pPlugIn , peSession,  pUser, const s_bs2x_game_end_other_user_info& rd) 
{
	if(pUser->IsAutoPlay())
	{
		if(pUser->is_attackable())
		{
			--pUser->m_iAutoMatchCount;
			fname_t szCmd;
			jt_sprintf(szCmd,_T("@game.req_rematch %I64d"),pUser->db_id());
			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
		}
		else
		{
			pUser->m_iAutoMatchCount=0; 
			fname_t szCmd;
			jt_sprintf(szCmd,_T("@game.UReqLeaveGame %I64d"),pUser->db_id());
			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
		}
	}
	else
	{
		jLOG_USER_T("other win_tot %d",rd.other_user().db_id() );
		jLOG_USER_T("other win_tot %d",rd.other_user().win_tot() );
		jLOG_USER_T("other lose_tot %d",rd.other_user().lose_tot() );
		jLOG_USER_T("other elo_point %d",rd.other_user().elo_point() );
	}


	return true; 
}

/*

템플릿 코드 

jRECV_FROM_BaseballServer(asdf ,pPlugIn,peSession,pUser, const s_asdf& rd) 
{
	jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_temp);
	return true; 
}

*/
