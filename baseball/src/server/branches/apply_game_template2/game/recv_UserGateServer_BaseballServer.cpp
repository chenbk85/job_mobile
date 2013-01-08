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


jRECV_FROM_UG2BS(ug2bs_game_end) // User* pUser , const s_ug2bs_game_end& rd
{
	jDEFAULT_CHECK_BS(pUser,pRoom);

#ifndef jUSE_TIMED_GAME_END_RESULT

	jMAKE_MSG_BS2X(sendMsg,sd,ans_game_end);
	sd->mutable_rg()->CopyFrom(rd.rg());
	sd->mutable_bonus_item()->CopyFrom(rd.bonus_item());

// 	for(int i=0; i< rd.bonus_item_size() ; ++i)
// 	{
// 		nProtoHelper::message_print(rd.bonus_item(i),pUser->db_id());
// 	}

	sd->mutable_user()->CopyFrom(rd.user());
	sd->mutable_better()->CopyFrom(rd.better());
	sd->mutable_pitcher()->CopyFrom(rd.pitcher());

	pRoom->send(pUser->db_id() , sendMsg);

#endif

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


