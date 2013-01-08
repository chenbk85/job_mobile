/* file : recv_UserGateServer_BaseballServer.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-06-26 11:45:34
comp.: www.neowiz.com
title : 
desc : 

PT_BaseballServer.proto에서 message UserGateServer_BaseballServer 에 포함된 메세지를 처리.
	: UMLPAD에서 UserGateServer -> BaseballServer로 보낸 패킷을 받는 부분이다.


*/

#include "baseball_user.h"
#include "baseball_room.h"
#include "proto.h"
#include "common/jILog.h"
#include "stdafx.h"

#define jRECV_FROM_UG2BS(X) void CB_UserGateServer_BaseballServer(baseball::User* pUser,const s_##X& rd)



jRECV_FROM_UG2BS(ug2bs_echo) // User* pUser , const s_ug2bs_echo& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
// 	jMAKE_MSG_BS2X(sendMsg,sd,ans_pong1);
// 
// 	sd->set_type(rd.type() );
// 	sd->set_msg(rd.msg());
//     pUser->send(sendMsg);

}

jRECV_FROM_UG2BS(ug2bs_error) // User* pUser , const s_ug2bs_error& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

}


jRECV_FROM_UG2BS(ug2bs_game_end)			// User* pUser , const s_ug2bs_game_end& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

	pUser->is_allow_rematch=false;			//게임이 끝나면 리매치 여부를 물어보기위해 리셋.
//#ifndef jUSE_TIMED_GAME_END_RESULT

	s_tbl_user* user = pUser->get_s_game_play_info()->mutable_m_tbl_user();	// 게임 종료 시 게임 서버의 유저 정보
	jRETURN_ERROR(user,ERR_USER_TABLE_NULL);

	user->CopyFrom(rd.user());				// DB에 있는 갱신된 유저 정보(rd.user())를 게임 서버의 유저 정보에 덥어쒸움.

	if ( pRoom->GetGame_End_DB() == false)
	{
		pRoom->SetGame_End_DB( true );		// 게임 DB 게임 종료 상태 set
		// nothing to do
		LOG_DEBUG("First User DB : "  << pUser->db_id() << " data arrive !" );
		return;
	}

	LOG_DEBUG("2nd User DB : " << pUser->db_id() << " data arrive !"  );

	// 방안의 다른 유저 포인터
	s_game_play_info* pOther = pRoom->get_s_game_play_info_Other(pUser->db_id());
	jRETURN_ERROR_ROOM(pOther, ERR_SERVER_DATA_ROOM_NULL);

	{	// 나에게 내 게임 결과 전송
		jMAKE_MSG_BS2X(sendMsg,sd,ans_game_end);
		sd->mutable_rg()->CopyFrom(rd.rg());						// 라운드 결과( 누구든 동일 )
		sd->mutable_user()->CopyFrom(rd.user());					// 내(세션) 정보
		sd->set_end_type(pRoom->GetGameEndType());					// 게임 종료 타입
		LOG_DEBUG("ug2bs_game_end : nGameEndType = " << pRoom->GetGameEndType());	// 클라이언트 전송용
		pRoom->send(pUser->db_id() , sendMsg);						// To me 에게 내(세션) 정보
		LOG_DEBUG("EndType: " << pRoom->GetGameEndType());
		LOG_DEBUG("To Me : " << pUser->db_id());
		LOG_DEBUG("To Me db_id " << rd.user().db_id() );
		LOG_DEBUG("To Me win_tot " << rd.user().win_tot() );
		LOG_DEBUG("To Me lose_tot " << rd.user().lose_tot() );
		LOG_DEBUG("To Me elo_point " << rd.user().elo_point() );
	}

	{	// 나에게 상대방 유저 정보 전송
		jMAKE_MSG_BS2X(sendMsg,sd,bs2x_game_end_other_user_info);
		sd->mutable_other_user()->CopyFrom(pOther->m_tbl_user());
		pRoom->send(pUser->db_id() , sendMsg);		//  To me 상대방 유저 정보 send
		LOG_DEBUG("To Me : " << pUser->db_id());
		LOG_DEBUG("To Me other db_id " << pOther->m_tbl_user().db_id() );
		LOG_DEBUG("To Me other win_tot " << pOther->m_tbl_user().win_tot() );
		LOG_DEBUG("To Me other lose_tot " << pOther->m_tbl_user().lose_tot() );
		LOG_DEBUG("To Me other elo_point " << pOther->m_tbl_user().elo_point() );
	}
	
	LOG_DEBUG("//------------------------------------------------------------//");
	{	
		jMAKE_MSG_BS2X(sendMsg,sd,ans_game_end);

		sd->mutable_rg()->CopyFrom(rd.rg());					// 라운드 결과( 동일 )
		sd->mutable_user()->CopyFrom(pOther->m_tbl_user());		// 상대방 유저 정보
		sd->set_end_type(pRoom->GetGameEndType());				// 게임 종료 타입
		LOG_DEBUG("ug2bs_game_end : nGameEndType = " << pRoom->GetGameEndType());	// 클라이언트 전송용
		pRoom->send_all_except_me(sendMsg, pUser->db_id());		// 상대방 유저에게 상대방 정보 send

		LOG_DEBUG("To Other");
		LOG_DEBUG("To Me Other db_id " << pOther->m_tbl_user().db_id() );
		LOG_DEBUG("To Me Other win_tot " << pOther->m_tbl_user().win_tot() );
		LOG_DEBUG("To Me Other lose_tot " << pOther->m_tbl_user().lose_tot() );
		LOG_DEBUG("To Me Other elo_point " << pOther->m_tbl_user().elo_point() );
		{
			jMAKE_MSG_BS2X(sendMsg,sd,bs2x_game_end_other_user_info);
			sd->mutable_other_user()->CopyFrom(rd.user());		// 내(세션) 정보 set
			pRoom->send_all_except_me(sendMsg, pUser->db_id());	// 상대방에게 내(세션) 정보 send
			LOG_DEBUG("To Other");
			LOG_DEBUG("To Other  db_id " << rd.user().db_id() );
			LOG_DEBUG("To Other  win_tot " << rd.user().win_tot() );
			LOG_DEBUG("To Other  lose_tot " << rd.user().lose_tot() );
			LOG_DEBUG("To Other  elo_point " << rd.user().elo_point() );
		}
		LOG_DEBUG("//------------------------------------------------------------//");
	}

	pRoom->m_GameRoomInfo.clear_m_result_round();			// 라운드 결과 초기화( 게임 시작에 호출해야 함! )

//#endif

}


jRECV_FROM_UG2BS(ug2bs_add_discon_tot) // User* pUser , const s_ug2bs_add_discon_tot& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

}


jRECV_FROM_UG2BS(ug2bs_ans_set_cvar) // User* pUser , const s_ug2bs_ans_set_cvar& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);
}


/*

템플릿입니다.

jRECV_FROM_UG2BS(asdf) // User* pUser , const s_asdf& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

	return true;
}


*/


