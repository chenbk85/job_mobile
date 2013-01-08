/* file : SAMPLE_Plugin_Connection.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 15:34:14
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "SAMPLE_Plugin_Connection.h"
#include "SAMPLE_Room.h"

//#--------------------------------------------------------------------------
void SAMPLE_Plugin_Connection::MOB_OnConnect(Plugin_INetIOModel* p) 
//#--------------------------------------------------------------------------
// SAMPLE_Plugin_Connection에 대한 초기화를 해주자.
{
	jAssert0(string("SAMPLE_Plugin_NetIOModel") == p->MOB_GetRTTI());
	static int s_i=0;
	m_gid = s_i++;
}

//--------------------------------------------------------------------------
void SAMPLE_Plugin_Connection::MOB_OnDisconnect(acstr szErrorReason,int iErrorReason)
//--------------------------------------------------------------------------
// SAMPLE_Plugin_Connection에 대한 메모리 해제를 해주자.
{
	printf("%s\n",szErrorReason);
	//jLOG(_T("%s"),szErrorReason);


}
//#--------------------------------------------------------------------------
void SAMPLE_Plugin_Connection::OnReadPacket_Unkown(GReqProtocol *p)
//#--------------------------------------------------------------------------
{

};

//#--------------------------------------------------------------------------
void SAMPLE_Plugin_Connection::OnReadPacket_GReqGameEnter(GReqGameEnter* p)
//#--------------------------------------------------------------------------
{
	m_MyInfo.CopyFrom(*p);
	
	SAMPLE_Room* pRoom = GetParent()->Room_Find(Get_room_id());
	if(!pRoom) // 기존에 방이 있으면 그 방에 join시킴.
	{
		pRoom = GetParent()->Room_Create(Get_room_id());
	}

	//로직에 맞게 다시 구현하시오.
	pRoom->User_Join(this);
	{// 방에 있는 모든 유저에게 전달.
		GAnsProtocol sendMsg;
		sendMsg.set_type(::GAnsProtocol_Type_GANSGAMEENTER);
		GAnsGameEnter* packet = sendMsg.mutable_ansgameenter();
		send_to_room_user(sendMsg,nMOB::eSAT_SendAll);
	}
}

//--------------------------------------------------------------------------
void SAMPLE_Plugin_Connection::OnReadPacket_GReqGameLeave(GReqGameLeave* pRecvPacket)
//--------------------------------------------------------------------------
{
	GAnsGameLeave_KICK_TYPE nType = GAnsGameLeave_KICK_TYPE_KICK_ZERO;
	if(!pRecvPacket->kick())
	{
		nType = GAnsGameLeave_KICK_TYPE_EXIT_RESERVATION;
	}
	int gameID = pRecvPacket->gameid();

	//로직에 맞게 다시 구현하시오.
	GAnsProtocol sendMsg;
	sendMsg.set_type(::GAnsProtocol_Type_GANSGAMELEAVE);
	GAnsGameLeave* pSendPacket = sendMsg.mutable_ansgameleave();
	pSendPacket->set_gameid(gameID);
	pSendPacket->set_ntype(nType);

	send_to_room_user(sendMsg,eSAT_SendAll);

}





#if 0

#	define jLAMDA_erase_by_cid(X,Z) Z(pp_game_id_t,gid)
jLAMDA_find_if(erase_by_cid,MOB_IConnection*)
{
	SAMPLE_CON(pCon,it->m_pPlugin);
	if(it->m_pPlugin->m_gid != gid) return false;
	if(pCon->getLogicCommand() != NULL)
	{
		pCon->getLogicCommand()->stopTimer();   
	}            
	return true;
}
jLAMDA_end();
boost::function<bool(MOB_IConnection*)> func = erase_by_cid(gid);
m_pMOB_IConnection->m_pParent->erase_if(func);

#	define jLAMDA_clear_m_YouJoinInfo(X,Z) Z(pp_game_id_t,gid)
jLAMDA_find_if(clear_m_YouJoinInfo,MOB_IConnection*)
{
	SAMPLE_CON(pCon,it->m_pPlugin);
	//매치 되었던 상태는 다시 기다릴 수 있게 한다.
	if(pCon->getMatchUserGameID() != gid) return false;
	pCon->m_YouJoinInfo.Clear();
	return true;
}
jLAMDA_end();
func = clear_m_YouJoinInfo(gid);
m_pMOB_IConnection->m_pParent->find_if(func);

#endif