/* file : Cmd_team.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-17 15:14:53
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"


namespace nCmdGame
{

	jCONSOLE_CMD_AUTO(game,match_auto_join_team,0,"goto match_team(join baseball server)","<uid> [category] [channel]")
	{
	#define jCONSOLE_PARAM_match_auto_join_team(X,Y) X(uid,tcstr) Y(category,int,0) Y(channel,int,0)
		jCONSOLE_PARAM_END(match_auto_join_team);
		jFIND_USER(peSession,pUser,uid);

		UReqProtocol sendMsg;
		sendMsg.set_type(UReqProtocol::UREQAUTOJOIN);
		UReqAutoJoin* sd = sendMsg.mutable_reqautojoin();
		sd->set_categoryid(category);
		sd->set_channelid(channel);
		g_pPlugIn->send_to_ug(peSession, sendMsg);

		return true;
	}

	jCONSOLE_CMD_AUTO(game,x2bs_auto_match_ready2,0,"send x2bs_auto_match_ready2"
		,"<uid> [batter=1] [pitcher=1]")
	{
	#define jCONSOLE_PARAM_x2bs_auto_match_ready2(X,Y) X(uid,tcstr) Y(batter,int32,1) Y(pitcher,int32,1) 
		jCONSOLE_PARAM_END(x2bs_auto_match_ready2);
		jFIND_USER(peSession,pUser,uid);

		s_game_play_info* gpi= pUser->get_s_game_play_info(pUser->db_id());
		jvRETURN_ret(true, gpi, _T("gpi= pUser->get_ game_play_info(%d); == NULL"),uid);

		jLOG_USER(_T("유저 : %d : 레디상태"),pUser->db_id());

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,x2bs_auto_match_ready2);
		sd->set_uid(pUser->game_id);
		sd->set_batter(batter);
		sd->set_pitcher(pitcher);
		g_pPlugIn->send_to_bs(peSession,sendMsg);

		return true;
	}

	jCONSOLE_CMD_AUTO(game,UReqLeaveGame,0,"게임서버에서나와 로비(UserGate)로 이동","<uid> [is_kick=false]")
	{
	#define jCONSOLE_PARAM_UReqLeaveGame(X,Y) X(uid,tcstr) Y(is_kick,bool,false)
		jCONSOLE_PARAM_END(UReqLeaveGame);
		jFIND_USER(peSession,pUser,uid);
		
		UReqProtocol sendMsg;
		sendMsg.set_type(UReqProtocol::UREQLEAVEGAME);
		UReqLeaveGame* sd = sendMsg.mutable_reqleavegame();

		jASSERT0(jt_atoi(uid)==pUser->game_id);
		sd->set_gameid(pUser->game_id);
		sd->set_kick(is_kick);
		g_pPlugIn->send_to_ug(peSession, sendMsg);

		return true;
	}


	jCONSOLE_CMD_AUTO(game,req_pitcher_throw,0,"후공일때 공던짐.","<uid> ")
	//jCONSOLE_CMD_AUTO(game,req_pitcher_throw,0,"후공일때 공던짐.","<uid> <position> <EPlayerBreakingBall> <scale_rate> <ball_breaking> <angle>")
	{
	#define jCONSOLE_PARAM_req_pitcher_throw(X,Y) X(uid,tcstr) 
	//#define jCONSOLE_PARAM_req_pitcher_throw(X,Y) X(uid,tcstr) X(position,tcstr) X(ball_type,tcstr) X(scale_rate,float) X(ball_breaking,float) X(angle,float)

		jCONSOLE_PARAM_END(req_pitcher_throw);
		//jCCE_ret(false, ball_type,EPlayerBreakingBall);

		jFIND_USER(peSession,pUser,uid);
		jCHECK(!pUser->is_attackable());

#ifdef DF_CLIENT_LOGIC_ERROR_CHECK
		jRETURN_ret(true, pUser->m_eEUserGPS==eUGPS_GAME_ROUND_START);
#endif

		//jTODO : 서버에서 체크되는지 검증하기 위해 여기서는 테스트 안함.
		// 그러나 실제 클라이언트에서는 검증해야함.
		// 세가지 값 모두 검증필요.

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_pitcher_throw);
		s_pitcher_throw_info info;
		sd->mutable_info()->CopyFrom(info);
		g_pPlugIn->send_to_bs(peSession,sendMsg);

		return true;
	}


	jCONSOLE_CMD_AUTO(game,req_better_hit,0,"req_better_hit","<uid>")
	//jCONSOLE_CMD_AUTO(game,req_better_hit,0,"req_better_hit","<uid> <screen_to_world> <force_xy> <force> <torque> <velocity_x>")
	{
	#define jCONSOLE_PARAM_req_better_hit(X,Y) X(uid,tcstr) 
	//#define jCONSOLE_PARAM_req_better_hit(X,Y) X(uid,tcstr) X(screen_to_world,tcstr) X(force_xy,tcstr) X(force,float) X(torque,float) X(velocity_x,float)

		jCONSOLE_PARAM_END(req_better_hit);
		jFIND_USER(peSession,pUser,uid);

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_better_hit);
		jCHECK(pUser->db_id()==pUser->game_id );
		jCHECK(pUser->is_attackable());
		
		s_better_hit_info info;

		sd->mutable_info()->CopyFrom(info);
	
		g_pPlugIn->send_to_bs(peSession,sendMsg);

		if(pUser->is_attackable())
		{
			pUser->calc_better_hit(*sd);
			pUser->do_play_client_production();//여기서 게임 결과를 계산하여 클라이언트 타자 연출 시작.
		}
		return true;
	}

	jCONSOLE_CMD_AUTO(game,req_room_state,0,"req_room_state","<uid> [is_server=false]")
	{
#define jCONSOLE_PARAM_req_room_state(X,Y) X(uid,tcstr) Y(is_server,bool,false)
		jCONSOLE_PARAM_END(req_room_state);
		jFIND_USER(peSession,pUser,uid);
#ifdef DF_CLIENT_LOGIC_ERROR_CHECK 
		jRETURN_ret(true,pUser->m_eEUserGPS> eUGPS_UserGateServer);
#endif

		if(!is_server)
		{
			nProtoHelper::message_print(pUser->m_GameRoomInfo);
			return true;
		}
		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_room_state);
		sd->set_room(pUser->m_GameRoomInfo.room_id());
		g_pPlugIn->send_to_bs(peSession,sendMsg);
		return true;
	}

	jCONSOLE_CMD_AUTO(game,print_score,0,"경기 스코어 출력( + 라운드정보)","<uid>")
	{
	#define jCONSOLE_PARAM_print_score(X,Y) X(uid,tcstr)
		jCONSOLE_PARAM_END(print_score);
		jFIND_USER(peSession,pUser,uid);

		pUser->print_score();

		return true;
	}


	jCONSOLE_CMD_AUTO(game,req_rematch,0,"req_rematch","<uid>")
	{
#define jCONSOLE_PARAM_req_rematch(X,Y) X(uid,tcstr)
		jCONSOLE_PARAM_END(req_rematch);
		jFIND_USER(peSession,pUser,uid);

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_rematch);
		sd->set_uid(pUser->db_id());
		g_pPlugIn->send_to_bs(peSession,sendMsg);
		pUser->is_allow_rematch=true;

		return true;
	}

	//@game.req_answer_restart_game <uid> <is_ok>
	jCONSOLE_CMD_AUTO(game,req_answer_restart_game,0,"req_answer_restart_game","<uid> <is_ok>")
	{
#define jCONSOLE_PARAM_req_answer_restart_game(X,Y) X(uid,tcstr) X(ok,bool)
		jCONSOLE_PARAM_END(req_answer_restart_game);
		jFIND_USER(peSession,pUser,uid);

		jRETURN_ret(true, pUser->is_allow_rematch_other);

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_answer_restart_game);
		sd->set_ok(ok);
		g_pPlugIn->send_to_bs(peSession,sendMsg);
		pUser->is_allow_rematch=ok;

		return true;
	}


	jCONSOLE_CMD_AUTO(game,req_result_better_hit,0,"req_result_better_hit","<uid>")
	{
#define jCONSOLE_PARAM_req_result_better_hit(X,Y) X(uid,tcstr)
		jCONSOLE_PARAM_END(req_result_better_hit);
		jFIND_USER(peSession,pUser,uid);

		s_ans_better_hit abh;
		pUser->send_req_result_better_hit(abh);

		return true;
	}


	jCONSOLE_CMD_AUTO(game,x2bs_match_ready,0,"x2bs_match_ready","<uid>")
	{
#define jCONSOLE_PARAM_x2bs_match_ready(X,Y) X(uid,tcstr)
		jCONSOLE_PARAM_END(x2bs_match_ready);
		jFIND_USER(peSession,pUser,uid);

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,x2bs_match_ready);
		sd->set_uid(pUser->db_id());
		g_pPlugIn->send_to_bs(peSession,sendMsg);

		return true;
	}

	jCONSOLE_CMD_AUTO(game,x2bs_batter_ready,0,"x2bs_batter_ready","<uid> [EBatterHitType]")
	{
#define jCONSOLE_PARAM_x2bs_batter_ready(X,Y) X(uid,tcstr) Y(HitType,tcstr ,jS(NULL))
		jCONSOLE_PARAM_END(x2bs_batter_ready);
		jFIND_USER(peSession,pUser,uid);
		
		jCCE_ret(false, HitType,EBatterHitType);
		pUser->m_EBatterHitType = eHitType;

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,x2bs_batter_ready);
		sd->Clear();
		g_pPlugIn->send_to_bs(peSession,sendMsg);


		return true;
	}

	#if 0

	jCONSOLE_CMD_AUTO(game,asdf,0,"asdf","<uid>")
	{
	#define jCONSOLE_PARAM_asdf(X,Y) X(uid,tcstr)
		jCONSOLE_PARAM_END(asdf);
		jFIND_USER(peSession,pUser,uid);

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,asdf);
		g_pPlugIn->send_to_bs(peSession,sendMsg);


		return true;
	}

#endif




}//namespace nCmdGame
