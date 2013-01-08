/* file : recv_GLReqGameProtocol.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 19:48:39
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"

#include "PK_Plugin_Connection.h"

#include "PB_Server/Manager/GameMgr_Poker.h"

#include "PK_Room.h"


//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_game_test_packet) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);
	int test_int = pRecvData->test_int();
	string test_string = pRecvData->test_string();
	jLOG(jFUNC1 _T("%d %s"),test_int , test_string.c_str() );

	MOB_MAKE_SEND_PACKET(sendMsg,pSendData,ans_game_test_packet);

	pSendData->set_test_string("asdf");
	pSendData->set_test_int(1234);

	pCon->send_to_all(sendMsg,nMOB::eSAT_SendAll); //나를 포함해(false) 모든 유저에게 보낼때.
	// pCon->send_to_room_user(sendMsg); // 방의 모든 유저에게 보냄.
	// pCon->send_me(sendMsg); //자신에게 다시 보낼때
	// pCon->send_to(sendMsg,1234); //접속번호 1234에게 보낼때.
	//pCon->setTimer(eTIMER_START);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_game_test_packet);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection, req_join_room) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_join_room);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection, req_send_start) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);
	PK_ROOM(pCon,pRoom);

	int gameid = pRecvData->gameid();

	pRoom->Game_Start(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_send_start);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection, req_send_select_card) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	int32 nCardIdx = pRecvData->m_lcardidx();

	pRoom->User_SelectCard(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_send_select_card);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection, req_betting) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	int32 nBettingType = pRecvData->m_lbettype();

	pRoom->User_Betting(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_betting);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection, req_ping) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);
	//jLOG(jFUNC1 _T("gameid : %d"), pCon->m_gid);

	GAnsProtocol sendMsg;

	sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
	GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
	packet->set_type(GLAnsGameProtocol_Type_ans_pong);

	pCon->send_me(sendMsg);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_ping);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection, req_entry) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	/*
	jLOG(jFUNC1 _T("CLevel : %d\n , Sex : %d\n , Soundtype : %d\n , version : %d\n , sAvt : %s\n , Nickname : %s\n "), 
		pRecvData->m_lclevel(),
		pRecvData->m_lsex(),
		pRecvData->m_lsoundtype(),
		pRecvData->m_nversion(), 
		pRecvData->m_savt(),
		pRecvData->m_snickname());
		*/

	PK_ROOM(pCon, pRoom);

	pRoom->User_Entry(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_entry);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_continue) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->Continue(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_continue);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_ruleset) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->RuleSet(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_ruleset);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_jokboset) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->JoboSet(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_jokboset);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_ack) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->ACK(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_ack);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_choiceremovecard) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->User_ChoiceRemoveCard(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_choiceremovecard);




//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_purge) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->User_Purge(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_purge);


//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_exitque) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->User_ExitQueue(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_exitque);


//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_soundtype) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->User_SoundType(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_soundtype);


//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_abuse) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->User_Abuse(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_abuse);

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,req_observe) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	PK_ROOM(pCon, pRoom);

	jASSERT(pCon != NULL);

	pRoom->User_Observe(pCon, pRecvData);
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,req_observe);
/*

템플릿 코드. 복사해서 사용하시요.

//#--------------------------------------------------------------------------
jMOB_RECV_PACKET(PK_Plugin_Connection,asdf1234) //pCon , pRecvData
//#--------------------------------------------------------------------------
{
	jRETURN(pRecvData);

	MOB_MAKE_SEND_PACKET(sendMsg,pSendData,ans_game_test_packet);

	pSendData->set_test_int(1234);

	pCon->send_to_all(sendMsg,nMOB::eSAT_SendAll); //나를 포함해(false) 모든 유저에게 보낼때.
}jMOB_RECV_PACKET_END(PK_Plugin_Connection,asdf1234);

*/