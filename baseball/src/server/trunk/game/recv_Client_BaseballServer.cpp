
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

	jRECV_FROM_X2BS(x2bs_echo) // User* pUser , s_x2bs_echo& rd
	{
		jDEFAULT_CHECK_BS(pUser,pRoom);
		jMAKE_MSG_BS2X(sendMsg,sd,bs2x_echo);

		/*
		sd->set_type(rd.type() );
		sd->set_msg(rd.msg());
		sd->set_client_time_msec(rd.client_time_msec());
		sd->set_bs_time_msec(nOS::get_curr_time_msec());
		pUser->room()->send(pUser->db_id(), sendMsg);
		*/
		// client 에서 내가 보낸 것과 남이 보낸 것을 어떻게 구분하는가?
		sd->set_type(rd.type() );
		sd->set_msg(rd.msg());
		sd->set_client_time_msec(rd.client_time_msec());
		sd->set_bs_time_msec(nOS::get_curr_time_msec());
		
		LOG_DEBUG("x2bs_echo  Echo type = " << rd.type() );

		if (rd.type() < 100)							// send to me
		{
			pUser->room()->send(pUser->db_id(), sendMsg);
		}
		else if (rd.type() >= 100 && rd.type() < 200)	// send to other : ping speed check!
		{
			pUser->room()->send_all_except_me(sendMsg, pUser->db_id());
			LOG_DEBUG("x2bs_echo  Send uid	= " << pUser->db_id() );
			LOG_DEBUG("x2bs_echo  rd.type()	= " << rd.type() );
			LOG_DEBUG("x2bs_echo  server time = " << nOS::get_curr_time_msec() );
		}
		else											// send to all
		{
			pUser->room()->send_all(sendMsg);
		}

	}



	jRECV_FROM_X2BS(x2bs_echo2) // User* pUser , s_x2bs_echo2& rd
	{
		jDEFAULT_CHECK_BS(pUser,pRoom);

		jMAKE_MSG_BS2X(sendMsg,sd,bs2x_echo2);
		sd->set_type(rd.type());
		sd->set_msg(rd.msg());
		sd->set_client_time_msec(rd.client_time_msec());
		sd->set_bs_time_msec(nOS::get_curr_time_msec());
		sd->set_etc(333);
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
		LOG_DEBUG("");

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

	void timer_user_goto_lobby(baseball::Room* pRoom,Tbl_User_id_t uid)
	{
		jRETURN(pRoom);
		baseball::User* pUser = pRoom->find_user(uid);
		jRETURN_ERROR_ROOM(pUser!= NULL  ,ERR_SERVER_DATA_ROOM_NULL);
		pRoom->kick_out(uid, MSG::EXIT_RESERVATION, "");
		//pRoom->leave(pUser,true);
	}

	struct user_goto_lobby
	{
		baseball::Room* pRoom;
		user_goto_lobby(baseball::Room* _pRoom)
		{
			pRoom = _pRoom;
		}
		void operator()(baseball::User* it)
		{
			jRETURN(pRoom);
			jRETURN(it);//!!
			int uid = it->db_id();
			jRETURN(uid);//!!
			fname_t szName;
			jt_sprintf(szName , "timer_user_goto_lobby_%d",uid);
			LOG_DEBUG("reg : " << szName );

			pRoom->add_timer_wrapper(
				baseball::Room::E_TIMER_USER_GOTO_LOBBY, 
				1, 
				boost::bind(timer_user_goto_lobby, _1, uid));
		}
	};

	// _AUTO_FUNC : 리매치 대기 후 자동 로비 입장 
	struct auto_goto_lobby
	{
		baseball::Room* pRoom;
		auto_goto_lobby(baseball::Room* _pRoom)
		{
			pRoom = _pRoom;
		}
		void operator()(baseball::User* it)
		{
			jRETURN(pRoom);
			jRETURN(it);//!!
			int uid = it->db_id();
			jRETURN(uid);//!!
			fname_t szName;
			jt_sprintf(szName , "timer_auto_goto_lobby_%d",uid);
			LOG_DEBUG("reg : " << szName );

			pRoom->add_timer_wrapper(
				baseball::Room::E_TIMER_AUTO_GOTO_LOBBY, 
				nG::i_WAIT_TIME_AFTER_GAME_END->Get_int(),
				boost::bind(timer_user_goto_lobby, _1, uid));
		}
	};

	void time_out_req_better_hit(baseball::Room* pRoom)
	{
		// jTODO 서버에서 타자 타격 대기시간이 넘었을때처리
		jRETURN(pRoom);
		jFUNC_LOG2("Room",pRoom->id());

		baseball::User* pUser = pRoom->get_current_better();
		jRETURN_ERROR_ROOM(pUser!= NULL  ,ERR_SERVER_DATA_ROOM_NULL);

		nBASE_BALL::make_random_better_hit(&pRoom->m_req_better_hit);

		jMAKE_MSG_BS2X(sendMsg,sd,ans_better_hit);
		sd->mutable_info()->CopyFrom(pRoom->m_req_better_hit.info());
		sd->set_is_auto(true);//자동으로 타자 치는 동작.
		// pRoom->send_all(sendMsg);
		pRoom->send_all_except_me(sendMsg, pUser->db_id());		// _SIMPLE_MODIFY

		static int s_i=0;
		LOG_DEBUG("ans_better_hit를 보냄.: " << s_i++);
	}

	void time_out_req_pitcher_throw(baseball::Room* pRoom)
	{
		jFUNC_LOG2("Room",pRoom->id());
		baseball::User* pUser = pRoom->get_current_pitcher();
		jRETURN_ERROR_ROOM(pUser!= NULL  ,ERR_SERVER_DATA_ROOM_NULL);

		nBASE_BALL::make_random_pitcher_throw(&pRoom->m_req_pitcher_throw);
		pRoom->send_ans_pitcher_throw(pRoom->m_req_pitcher_throw,true);
	}



	jRECV_FROM_X2BS(x2bs_auto_match_ready2) // User* pUser , s_x2bs_auto_match_ready2& rd ,UserGateServer_Client& ret
	{
		jDEFAULT_CHECK_BS(pUser,pRoom);
		jRETURN_ERROR( pUser->get_m_e_user_gps()< eUGPS_GAME_READY2 ,ERR_x2bs_match_ready_alreay2);
		jCHECK(pUser->db_id() == rd.uid());
		//jRETURN_ERROR(pRoom->get_s_game_play_info_Other(pUser->id()) , );
		s_game_play_info* gpi = pRoom->get_s_game_play_info(pUser->db_id());
		//jRETURN_ERROR(gpi->m_e_user_gps()!=eUGPS_GAME_READY2, ERR_x2bs_match_ready_alreay2);
		LOG_DEBUG("pUser->get_m_e_user_gps() = " << ToString((EUserGPS)pUser->get_m_e_user_gps()));
		gpi->set_m_e_user_gps(eUGPS_GAME_READY2);
		gpi->set_m_batter_sid(rd.batter());
		gpi->set_m_pitcher_sid(rd.pitcher());

		LOG_DEBUG("recv_x2bs_auto_match_ready2   batter  =" << rd.batter() );
		LOG_DEBUG("recv_x2bs_auto_match_ready2   pitcher  =" << rd.pitcher() );

		pRoom->send_bs2x_auto_match_ready2(rd.uid());
	}

	void time_out_req_result_better_hit(baseball::Room* pRoom)
	{
		baseball::User* pUser = pRoom->get_current_better();
		jRETURN_ERROR_ROOM(pUser!= NULL  ,ERR_SERVER_DATA_ROOM_NULL);
		// jTODO
		// jRETURN_ERROR(jS(time_out_req_result_better_hit)==0,ERR_TIME_OUT_req_better_hit );
	}


	jRECV_FROM_X2BS(req_pitcher_throw) // User* pUser , s_req_pitcher_throw& rd ,UserGateServer_Client& ret
	{
		jDEFAULT_CHECK_BS(pUser,pRoom);

		jRETURN_ERROR(pUser->get_m_e_user_gps()==eUGPS_GAME_BATTER_READY, ERR_req_pitcher_throw);	// 던질 상태가 아니면
		jRETURN_ERROR(pRoom->get_attack_uid() != pUser->db_id(),ERR_req_pitcher_throw);				// 투수가 아니면

		set_EUserGPS func(eUGPS_PITCHER_THROW);
		pRoom->for_each_s_game_play_info(func);

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

		LOG_DEBUG("req_better_hit : get_m_e_user_gps = " << pUser->get_m_e_user_gps() );
		jRETURN_ERROR(pUser->get_m_e_user_gps()==eUGPS_PITCHER_THROW
			,ERR_req_better_hit);

		//상대방(투수)이 공을 던졌는냐?
		s_game_play_info* gpi_pitcher= pRoom->get_s_game_play_info_Other(pUser->db_id());
		jRETURN_ERROR(gpi_pitcher && gpi_pitcher->m_e_user_gps() == eUGPS_PITCHER_THROW, ERR_SERVER_DATA_ROOM_NULL);


		set_EUserGPS func(eUGPS_BETTER_HIT);
		pRoom->for_each_s_game_play_info(func);
		//pUser->set_m_e_user_gps(eUGPS_BETTER_HIT);

	#ifdef SERVER_AUTO_PLAY
		pUser->room()->remove_timer_wrapper(baseball::Room::E_TIME_OUT_REQ_BETTER_HIT);
	#endif
		pUser->room()->m_req_better_hit.CopyFrom(rd);

		jMAKE_MSG_BS2X(sendMsg,sd,ans_better_hit);
		sd->mutable_info()->CopyFrom(rd.info());
		sd->set_is_auto(false);//자동으로 타자 치는 동작 아님.
		pUser->room()->send_all(sendMsg);

	}

	// 게임 종료 조건
	int 
	checkGameEnd(baseball::Room* pRoom, Tbl_User_id_t pre_winner)
	{
		int32 iNextRound = pRoom->get_round_count() + 1;				// 정상 종료 조건

		int Scoregab = pRoom->calc_game_score();
		
		if (pRoom->get_round_count() == END_GAME_START_ROUND - 1)		// 마지막 라운드 직전( 14 )
		{
			LOG_DEBUG("current_round_count = " << pRoom->get_round_count() );
			LOG_DEBUG("checkGameEnd : at before last round = << pRoom->get_round_count() ");

			if ( Scoregab >= CALLED_GAME_SCORE )						// 콜드 게임
			{
				LOG_DEBUG("checkGameEnd : CALLED_GAME");
				return CALLED_GAME;		
			}

			int EndGameType = pRoom->check_withoutattack_loser();		// 승부 확정 

			if ( EndGameType > GAME_PLAYING)
				return EndGameType;
		}
	
		if (pRoom->get_round_count() >= END_GAME_START_ROUND)			// 마지막 라운드( 15 이후 )
		{
			if ( Scoregab >= CALLED_GAME_SCORE )						// 콜드 게임
			{
				LOG_DEBUG("checkGameEnd : CALLED_GAME");
				return CALLED_GAME;		
			}
			
			int nCurr_winner = pRoom->get_curr_winner();				// 역전 승 검사 

			if ( Scoregab != 0 && pre_winner >= 0 && nCurr_winner > 0 && pre_winner != nCurr_winner)
			{
				std::cout << "current_round_count : " << pRoom->get_round_count() << std::endl;
				LOG_DEBUG("current_round_count = " << pRoom->get_round_count() );
				LOG_DEBUG("checkGameEnd : WINNING_HIT");
				LOG_DEBUG("pre_winner = " << pre_winner );
				LOG_DEBUG("cur_winner = " << pRoom->get_curr_winner() );
				return WINNING_HIT;		
			}
			// 승부 확정( 보완 처리 )
			int EndGameType = pRoom->check_withoutattack_winner();		// 승부 확정 

			if ( EndGameType > GAME_PLAYING)
				return EndGameType;

			/*
			// 지고 있는 유저가 역전이 가능한 상태 인가? -> 기획에 없어서 disable 
			if (Scoregab >= pRoom->calc_max_remain_score())	
			{
				LOG_DEBUG("checkGameEnd : WITHOUT_ATTACK");
				return WITHOUT_ATTACK;		
			}
			*/
		}

		if(iNextRound >= pRoom->m_i_TOTAL_ROUND * DEF_i_MAX_PLAYING_USER)	// 정상 게임 종료
		{
			LOG_DEBUG("checkGameEnd : NORMAL_END");
			return NORMAL_END;
		}
	
		LOG_DEBUG("checkGameEnd : NOT GameEnd : PLAYING....!");
		return GAME_PLAYING;
	}

	bool
	IsTurnTheGameAround(baseball::Room* pRoom)
	{
		
		return false;
	}

	void 
	GameEndProc(baseball::Room* pRoom, User* pUser)
	{
		set_EUserGPS func(eUGPS_GAME_END);
		pRoom->for_each_s_game_play_info(func);

		// 게임 결과 계산. ( 보너스 경험치 & 게임머니)
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
			//jMAKE_MSG_BS2UG(sendMsg,sd,bs2ug_game_end);
			BaseballServer_UserGateServer sendMsg;
			sendMsg.set_type(::BaseballServer_UserGateServer_Type_bs2ug_game_end);
			s_bs2ug_game_end* sd = sendMsg.mutable_m_bs2ug_game_end();
			LOG_DEBUG("send message : " "bs2ug_game_end" );

			sd->mutable_rg()->CopyFrom(*rg);
			*sd->mutable_rr() = pRoom->m_GameRoomInfo.m_result_round();
			sd->set_is_better(true);
			sd->set_end_type(pRoom->GetGame_End_DB());
			pRoom->send_to_ug(pUser->db_id(), sendMsg);

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
			// _AUTO_FUNC : 자동 로비 입장
			std::cerr << "[auto_goto_lobby] TIMER START!";
			LOG_DEBUG("[auto_goto_lobby] TIMER START!");		// 일정 시간 대기 후 로비 입장
			auto_goto_lobby func(pRoom);
			pRoom->for_each_User(func);
		}

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
		jRETURN_ERROR_ROOM(pNewBetter, ERR_SERVER_DATA_ROOM_NULL);
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
		// LOG_DEBUG("\n\njRECV_FROM_CLIENT_TO_BS(req_result_better_hit)\n\n");
		jDEFAULT_CHECK_BS(pUser,pRoom);
		jRETURN_ERROR(pUser->is_attackable() , ERR_req_better_hit_IS_NOT_BETTER);

		EUserGPS eState = pUser->get_m_e_user_gps();
		jRETURN_ERROR(eState==eUGPS_GAME_ROUND_START || eState==eUGPS_BETTER_HIT
			,ERR_SERVER_DATA_ROOM_NULL);


		//날라온 결과 재확인.
		const s_tbl_roundresult &rr = rd.info().m_tbl_roundresult();
		EBatterHitType eType = (EBatterHitType)rr.hit_type();
		LOG_DEBUG("//--------------------------------------------------------//");
		LOG_DEBUG("used_batter_id			= " << rr.used_batter_id() );
		LOG_DEBUG("used_pitcher_id			= " << rr.used_pitcher_id());
		LOG_DEBUG("round_number				= " << rr.round_number());
		LOG_DEBUG("used_breakingball		= " << rr.used_breakingball());
		LOG_DEBUG("used_breakingball_speed	= " << rr.used_breakingball_speed());
		LOG_DEBUG("used_pitcherability		= " << ToString((EBatterHitType)rr.used_pitcherability()));
		LOG_DEBUG("pitching_rhythm_judge	= " << ToString((EBatterHitType)rr.pitching_rhythm_judge()));
		LOG_DEBUG("used_gesturetype			= " << ToString((EBatterHitType)rr.used_gesturetype()));
		LOG_DEBUG("gesturetype_input_error	= " << rr.gesturetype_input_error());
		LOG_DEBUG("used_batting_fullpower	= " << ToString((EBatterHitType)rr.used_batting_fullpower()));
		LOG_DEBUG("batting_timing_judge		= " << ToString((EBatterHitType)rr.batting_timing_judge()));
		LOG_DEBUG("batting_hittype			= " << ToString((EBatterHitType)rr.batting_hittype()));
		LOG_DEBUG("batting_hittype			= " << ToString((EBatterHitType)rr.batting_hittype()));
		LOG_DEBUG("uid_attack				= " << rr.uid_attack());
		LOG_DEBUG("score					= " << rr.score());
		LOG_DEBUG("base_runner_state		= " << rr.base_runner_state());
		LOG_DEBUG("eType					= " << ToString(eType) << "," << eType);
		LOG_DEBUG("//--------------------------------------------------------//");

		jRETURN_ERROR(IsValid(eType) , ERR_ROUND_RESULT_MISSMATCH);	// 결과 에러 메세지

		Tbl_User_id_t pre_winner = -1;

		if( pRoom->get_round_count() >= END_GAME_START_ROUND - 1 )
		{
			pre_winner = pRoom->get_curr_winner();					// 이전 라운드까지의 승자
			LOG_DEBUG("pre_winner = " << pre_winner );
		}

		pUser->set_m_e_user_gps(eUGPS_BETTER_HIT_RESULT);

		s_result_round rr_server;									// 서버에서 계산하는 라운드 결과

		jCHECK(nG::i_ATTACK_CHANGE_ROUND->Get_int()==3);

		round_t iTeamRoundCount = nBASE_BALL::curr_team_round(pRoom->get_round_count()\
			,nG::i_ATTACK_CHANGE_ROUND->Get_int());

		jCHECK( iTeamRoundCount >= 0 && iTeamRoundCount < nG::i_TOTAL_ROUND->Get_int() );

		ERunnerStateRound eRSType = get_round_state(iTeamRoundCount, pRoom->Get_Curr_RSR() );

		LOG_DEBUG("//----------------------------------------------//");
		LOG_DEBUG("[req_result_better_hit]	: attack_uid = " << pUser->db_id() );
		LOG_DEBUG("[iTeamRoundCount]	: round_count = " <<  iTeamRoundCount );
		LOG_DEBUG("[Curr_RSR] : Curr_RSR = " << pRoom->Get_Curr_RSR() );
		LOG_DEBUG("req_result_better_hit : runner state= " << ToString(eRSType));
		LOG_DEBUG("//----------------------------------------------//");

		pRoom->make_round_result(&rr_server,eType,eRSType);	

		s_tbl_roundresult &rr2 = *rr_server.mutable_m_tbl_roundresult();	// 프로토콜용 데이터 포인터
	 	LOG_DEBUG("client data");
	 	nProtoHelper::message_print(rr,pUser->db_id());
	 	LOG_DEBUG("server data");
	 	nProtoHelper::message_print(rr2,pUser->db_id());

		//jTODO 차후 검증 :jRETURN_ERROR(nProtoHelper::is_equal(rr, rr2) , ERR_req_better_hit_IS_NOT_BETTER);
		//if( nProtoHelper::is_equal(rr, rr2) )
		//	LOG_WARNING("server rr data is not equal client rr data");

		rr2.set_grid(pRoom->m_GameRoomInfo.m_result_game().m_tbl_result().db_id());
		s_result_round* pRR = pRoom->m_GameRoomInfo.add_m_result_round();	// 라운드 결과 저장 구조체
		pRR->CopyFrom(rr_server);											// 라운드 결과 저장

	#ifdef SERVER_AUTO_PLAY
		pRoom->remove_timer_wrapper(baseball::Room::E_TIME_OUT_REQ_RESULT_BETTER_HIT);
		// 만약 타자가 파울등의 아웃이면 req_better_hit대신 바로 req_result_better_hit가 날라 온다.
		pRoom->remove_timer_wrapper(baseball::Room::E_TIME_OUT_REQ_BETTER_HIT);
	#endif

		jMAKE_MSG_BS2X(sendMsg,sd,ans_result_better_hit);			// 받은 결과를 투수에게 전달.
		
		//jTODO 
		// sd->mutable_info()->CopyFrom(rd.info());					// 클라가 보낸 데이터 그대로 에코
		sd->mutable_info()->CopyFrom(rr_server);					// 서버 계산 결과를 클라에 전송

		int nGameEndType = GAME_PLAYING;

		if (pRoom->get_round_count() >= END_GAME_START_ROUND - 1)	// 마지막 라운드 직전 베팅 부터 체크 
		{
			nGameEndType = checkGameEnd(pRoom, pre_winner);
			if (nGameEndType > GAME_PLAYING)
				pRoom->SetGameEndType(nGameEndType);
		}
		LOG_DEBUG("nGameEndType = " << pRoom->GetGameEndType());	// 클라이언트 전송용

		sd->set_end_type(pRoom->GetGameEndType());					// 게임 종료 타입
		
		pUser->room()->send_all(sendMsg);							// 양쪽 모두 필요하다고 함!

		int32 iNextRound = pRoom->get_round_count() +1;
		LOG_DEBUG("curr calculated round = " << iNextRound);

		if ( nGameEndType > GAME_PLAYING )
		{
			GameEndProc( pRoom, pUser );
			return;
		}

		//#--------------------------------------------------------------------------
		//공수를 교대하는 조건.
		//#--------------------------------------------------------------------------
		bool isChange = false;
		if( !(iNextRound % pRoom->m_i_ATTACK_CHANGE_ROUND ))
		{
	// 		LOG_DEBUG("공수 교대 1.curr=%d m_i_TOTAL_ROUND=%d , m_i_ATTACK_CHANGE_ROUND=%d m_i_CheckRound=%d"
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
	// 			LOG_DEBUG("공수 교대 2.curr=%d m_i_TOTAL_ROUND=%d , m_i_ATTACK_CHANGE_ROUND=%d, m_i_CheckRound=%d"
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

	// 		LOG_DEBUG("공수 교대.curr=%d m_i_TOTAL_ROUND=%d , m_i_ATTACK_CHANGE_ROUND=%d, m_i_CheckRound=%d"
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
		LOG_DEBUG("Go next round! curr=" << iNextRound << 
				", m_i_TOTAL_ROUND=" << pRoom->m_i_TOTAL_ROUND <<
			   	", m_i_ATTACK_CHANGE_ROUND=" << pRoom->m_i_ATTACK_CHANGE_ROUND << 
				", m_i_CheckRound=" << pRoom->m_i_CheckRound);
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
		jMAKE_MSG_BS2X(sendMsg,sd,bs2x_echo);
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

	void send_ans_answer_restart_game(baseball::Room* pRoom,Tbl_User_id_t uid1, bool ok1, Tbl_User_id_t uid2, bool ok2)
	{
	// 	print_EUserGPS func1;
	// 	pRoom->for_each_s_game_play_info(func1);
		find_EUserGPS func(eUGPS_GAME_END);
		s_game_play_info* gpi2= pRoom->find_if_s_game_play_info(func);
		jvRETURN( gpi2==0 ,"find = %d", gpi2->m_e_user_gps() );

		pRoom->reset_user_info();
		LOG_DEBUG("ans_answer_restart_game : reset_user_info()");

		// _AUTO_FUNC : 리매치 신청만 와도 자동 로비 입장 diable !
		std::cerr << "[auto_goto_lobby] TIMER OFF!";
		LOG_DEBUG("[auto_goto_lobby] TIMER OFF!");
		pRoom->remove_timer_wrapper(baseball::Room::E_TIMER_AUTO_GOTO_LOBBY);

		jMAKE_MSG_BS2X(sendMsg,sd,ans_answer_restart_game);
		sd->add_uid(uid1);		// repeated 인 경우에만 add
		sd->add_ok(ok1);
		sd->add_uid(uid2);
		sd->add_ok(ok2);
		pRoom->m_GameRoomInfo.set_m_baseball_park(nMOB::make_random());
		sd->set_baseball_park(pRoom->m_GameRoomInfo.m_baseball_park());

		Tbl_User_id_t uid = pRoom->m_GameRoomInfo.m_attack_user();
		sd->set_attack_user(uid);

		pRoom->send_all(sendMsg);
		LOG_DEBUG("pRoom->send_all(sendMsg);ans_answer_restart_game");
		
		LOG_DEBUG("[send_ans_answer_restart_game] Uid1 : " << uid1 << 
				"  ok1 : "<< ok1 << "  Uid2 : " << uid2 << " ok1 : "<< ok2 << "  attack_user : " << uid);

		if(ok1 && ok2)
		{
			set_EUserGPS func(eUGPS_GAME_READY2);		// 방안 모든 유저의 상태를 대기 상태로 SET
			pRoom->for_each_s_game_play_info(func);		

			pRoom->SetGame_End_DB( false );				// 게임 DB 게임 종료 초기화
			pRoom->SetGameEndType(GAME_PLAYING);		// 게임 종료 타입 초기화

	// 		pRoom->add_timer_wrapper(baseball::Room::E_TIMER_JOB_ANS_GAME_START,
	// 				nG::i_TIME_ALL_PLAYER_NOT_READY->Get_int(),
	// 				timer_job_ans_game_start);
		}
		else
		{
			LOG_DEBUG("[user_goto_lobby]");				// 양쪽에서 거절
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
		/*
		// _AUTO_FUNC : 리매치 신청만 와도 자동 로비 입장 diable !
		std::cerr << "[auto_goto_lobby] TIMER OFF!";
		LOG_DEBUG("[auto_goto_lobby] TIMER OFF!");
		pRoom->remove_timer_wrapper(baseball::Room::E_TIMER_AUTO_GOTO_LOBBY);
		*/

		pUser->is_allow_rematch=true;
		if(!pOtherUser->is_allow_rematch)// 허락하지 않은상태이면 물어봄.
		{
			jMAKE_MSG_BS2X(sendMsg,sd,ans_rematch);
			sd->set_uid(rd.uid());
			pRoom->send_all_except_me(sendMsg, pUser->db_id());
			return ;
		}

		pRoom->select_first_attack_user();	// req_answer_restart_game 에도 호출 됨

		//허락한 상태이면 모두에게 재경기 통보.
		pRoom->remove_timer_wrapper(baseball::Room::E_SEND_ANS_ANSWER_RESTART_GAME);
		send_ans_answer_restart_game(pRoom, pUser->db_id() , true, pOtherUser->db_id(), true);
	}

	jRECV_FROM_X2BS(req_answer_restart_game) // User* pUser , s_req_answer_restart_game& rd
	{
		jDEFAULT_CHECK_BS(pUser,pRoom);
		baseball::User* pOtherUser = pRoom->get_other_user(pUser->db_id());
		jRETURN_ERROR(pOtherUser, ERR_SERVER_DATA_UID_DISMATCH)
		pRoom->select_first_attack_user();	// req_rematch 에도 호출 됨

		pUser->is_allow_rematch=rd.ok();
		pRoom->remove_timer_wrapper(baseball::Room::E_SEND_ANS_ANSWER_RESTART_GAME);
		send_ans_answer_restart_game(pRoom, pUser->db_id() , rd.ok(), pOtherUser->db_id(), true);
	}

	jRECV_FROM_X2BS(x2bs_match_ready) // User* pUser , s_x2bs_match_ready& rd
	{
		jDEFAULT_CHECK_BS(pUser,pRoom);

		s_game_play_info *gpi = pRoom->get_s_game_play_info(pUser->db_id());
		jRETURN_ERROR(gpi,ERR_x2bs_match_ready_gpi_NULL);

		// 유저의 상태가 레디한 상태이라면 두번보낸것이므로 에러 리턴.
		if(gpi->m_e_user_gps() >= eUGPS_GAME_READY )
		{
			LOG_WARNING( "jvRETURN_ERROR( ERR_x2bs_match_ready_alreay : " _T("gpi->m_e_user_gps(eUGPS_GAME_READY) == eUGPS_GAME_READY") 
						_T(") : user db_id=")  << pUser->db_id() ) ;
				jMAKE_MSG_BS2X(sendMsg,sd,ans_bs_error);
				sd->set_sys_error_id(jMAKE_ERR(ERR_x2bs_match_ready_alreay));
				pUser->room()->send(pUser->db_id(), sendMsg);
				ILLEGAL_USER_BAN(pUser);
				return;
		}

		gpi->set_m_e_user_gps(eUGPS_GAME_READY);

		jMAKE_MSG_BS2X(sendMsg,sd,bs2x_match_ready);
		sd->set_uid(pUser->db_id());
		pRoom->send_all(sendMsg);


		if (pRoom->is_full_user() && pRoom->is_all_user_ready())
		{
			timer_job_ans_game_start(pRoom);
	// 		add_timer_wrapper(E_TIMER_JOB_ANS_GAME_START
	// 			,nG::i_TIME_ALL_PLAYER_READY->Get_int(),
	// 			timer_job_ans_game_start);
		}
	}


	jRECV_FROM_X2BS(x2bs_batter_ready) // User* pUser , s_x2bs_batter_ready& rd
	{
		jDEFAULT_CHECK_BS(pUser,pRoom);

		jRETURN_ERROR(pUser->get_m_e_user_gps()==eUGPS_GAME_ROUND_START,ERR_x2bs_batter_ready );
		jRETURN_ERROR(pRoom->get_attack_uid() == pUser->db_id(),ERR_x2bs_batter_ready);	// 타자가 아니면

		set_EUserGPS func(eUGPS_GAME_BATTER_READY);	// 방어 코드 통과 후 룸에 있는 모든 유저의 상태를 SET
		pRoom->for_each_s_game_play_info(func);

		jMAKE_MSG_BS2X(sendMsg,sd,bs2x_batter_ready);
		sd->Clear();
		pRoom->send_all_except_me(sendMsg,pUser->db_id() );
	}



	/*

	템플릿입니다.

	jRECV_FROM_X2BS(asdf) // User* pUser , s_asdf& rd
	{
		jDEFAULT_CHECK_BS(pUser,pRoom);
	}

	*/
	
} /* baseball */


