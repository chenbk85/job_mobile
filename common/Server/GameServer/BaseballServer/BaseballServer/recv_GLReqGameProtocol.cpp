/* file : recv_GLReqGameProtocol.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 19:48:39
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"

#include "stdafx.h"
#include "BB_Plugin_Connection.h"


jMOB_RECV_PACKET(BB_Plugin_Connection,req_game_test_packet) //pCon , pRecvData
{
	jRETURN(pRecvData);
	int test_int = pRecvData->test_int();
	string test_string = pRecvData->test_string();

	MOB_SEND_PACKET_START(sendMsg,pSendData,ans_game_test_packet);
	//  위의 매크로는 다음코드와 동일하다.
	// 	GAnsProtocol sendMsg;
	// 	sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
	// 	GLAnsGameProtocol sendMsg_GLAnsGameProtocol;
	// 	sendMsg_GLAnsGameProtocol.set_type(::GLAnsGameProtocol_Type_ans_game_test_packet);
	// 	s_ans_game_test_packet* pSendData = sendMsg_GLAnsGameProtocol.mutable_m_ans_game_test_packet();

	pSendData->set_test_string("asdf");
	pSendData->set_test_int(1234);

	MOB_SEND_PACKET_END(sendMsg);
	//  위의 매크로는 다음코드와 동일하다.
	//sendMsg.set_ansgameprotocol(sendMsg_GLAnsGameProtocol.SerializeAsString());


	pCon->send_to_all(sendMsg,nMOB::eSAT_SendAll); //나를 포함해(false) 모든 유저에게 보낼때.
	// pCon->send_to_room_user(sendMsg); // 방의 모든 유저에게 보냄.
	// pCon->send_me(sendMsg); //자신에게 다시 보낼때
	// pCon->send_to(sendMsg,1234); //접속번호 1234에게 보낼때.
	//pCon->setTimer(eTIMER_START);
}
jMOB_RECV_PACKET_END(BB_Plugin_Connection,req_game_test_packet);



#if 0
패킷 추가시 아래코드를 복사해서 사용하세요.

jMOB_RECV_PACKET(BB_Plugin_Connection,req_asdf) //pCon , pRecvData
{
	jRETURN(pRecvData);
	int test_int = pRecvData->test_int();
	string test_string = pRecvData->test_string();

	MOB_SEND_PACKET_START(sendMsg,pSendData,ans_asdf);

	pSendData->set_test_string("asdf");
	pSendData->set_test_int(1234);

	MOB_SEND_PACKET_END(sendMsg);

	pCon->send_to_all(sendMsg,nMOB::eSAT_SendAll); //나를 포함해(false) 모든 유저에게 보낼때.
}
jMOB_RECV_PACKET_END(BB_Plugin_Connection,req_game_test_packet);


#endif
