/* file : PK_Plugin_Connection.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 15:34:14
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PK_Plugin_Connection.h"
#include "PK_Room.h"

//#--------------------------------------------------------------------------
void PK_Plugin_Connection::MOB_OnConnect(Plugin_INetIOModel* p) 
//#--------------------------------------------------------------------------
// PK_Plugin_Connection에 대한 초기화를 해주자.
{
	jAssert0(string("PK_Plugin_NetIOModel") == p->MOB_GetRTTI());
}

//--------------------------------------------------------------------------
void PK_Plugin_Connection::MOB_OnDisconnect(acstr szErrorReason,int iErrorReason)
//--------------------------------------------------------------------------
// PK_Plugin_Connection에 대한 메모리 해제를 해주자.
{
	printf("%s\n",szErrorReason);
	//jLOG(_T("%s"),szErrorReason);

	PK_Room* pRoom = GetParent()->Room_Find(Get_room_id());
	if(!pRoom) // 기존에 방이 있으면 그 방에 join시킴.
	{
		return;
	}

	pRoom->UserDisconnect(m_gid);

#if 0

#	define jLAMDA_erase_by_cid(X,Z) Z(pp_game_id_t,gid)
	jLAMDA_find_if(erase_by_cid,MOB_IConnection*)
	{
		PK_CON(pCon,it->m_pPlugin);
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
		PK_CON(pCon,it->m_pPlugin);
		//매치 되었던 상태는 다시 기다릴 수 있게 한다.
		if(pCon->getMatchUserGameID() != gid) return false;
		pCon->m_YouJoinInfo.Clear();
		return true;
	}
	jLAMDA_end();
	func = clear_m_YouJoinInfo(gid);
	m_pMOB_IConnection->m_pParent->find_if(func);

#endif

}
//#--------------------------------------------------------------------------
void PK_Plugin_Connection::OnReadPacket_Unkown(GReqProtocol *p)
//#--------------------------------------------------------------------------
{

};

//#--------------------------------------------------------------------------
void PK_Plugin_Connection::OnReadPacket_GReqGameEnter(GReqGameEnter* p)
//#--------------------------------------------------------------------------
{
	m_MyInfo.CopyFrom(*p);
	
	PK_Room* pRoom = GetParent()->Room_Find(Get_room_id());
	if(!pRoom) // 기존에 방이 있으면 그 방에 join시킴.
	{
		pRoom = GetParent()->Room_Create(Get_room_id());
	}
	//pRoom->User_Join(this);
	pRoom->User_Join(this,p);


	{// 방에 있는 모든 유저에게 전달.
		GAnsProtocol sendMsg;
		sendMsg.set_type(::GAnsProtocol_Type_GANSGAMEENTER);
		GAnsGameEnter* packet = sendMsg.mutable_ansgameenter();

		pRoom->User_JoinAns(this, packet);

		this->m_gid = p->gameuserinfo().memberinfo().gameid();

		//send_to_room_user(sendMsg,nMOB::eSAT_SendAll);
		send_me(sendMsg);
	}
}

//--------------------------------------------------------------------------
void PK_Plugin_Connection::OnReadPacket_GReqGameLeave(GReqGameLeave* pRecvPacket)
//--------------------------------------------------------------------------
{
	GAnsGameLeave_KICK_TYPE nType = GAnsGameLeave_KICK_TYPE_KICK_ZERO;
	if(!pRecvPacket->kick())
	{
		nType = GAnsGameLeave_KICK_TYPE_EXIT_RESERVATION;
	}
	int gameID = pRecvPacket->gameid();

	GAnsProtocol sendMsg;
	sendMsg.set_type(::GAnsProtocol_Type_GANSGAMELEAVE);
	GAnsGameLeave* pSendPacket = sendMsg.mutable_ansgameleave();
	pSendPacket->set_gameid(gameID);
	pSendPacket->set_ntype(nType);

	send_to_room_user(sendMsg,eSAT_SendAll);

	//연결되어 있던 유저가 있다면 상태를 바꾼다.
	//매치 되었던 상대는 다시 기다릴 수 있게 한다.
	//mulManager->leave(pSendPacket->gameid());

	PK_Room* pRoom = GetParent()->Room_Find(Get_room_id());
	pRoom->User_Leave(this, pRecvPacket);
}

