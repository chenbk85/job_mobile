/* file : Recv_FromChannel.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-11 21:30:51
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TWorld.h"


#define jGET_DBCache(pDB,pPlayer,errorC)\
	jIGridNode* pDB = g_SG.m_DBCache.find(pPlayer->Get_Server(eDBCache) );\
	if(!pDB){jSEND_ERROR_USER_DISCONNECT(W , SR_t(USER_DSERVER_sid_NOT_FOUND) , CR_t(errorC)  , pPlayer->m_pid); return;}


jNET_EVENT_BEGIN(PlugIn_Server)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(CH2W_USER_LOGIN_CHANNEL)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jServerInfo* si
		READ_PACKET_PS_BS(CH2W_USER_LOGIN_CHANNEL);

		jPlayerBase* pPlayer=0;
		{
			
			pPlayer = g_PL.find(Data.id);
		}
		if(!pPlayer)
		{
			//해당 유저가 로긴서버로 접속된상태가아님. 강제종료시켜야함.
			jSEND_ERROR_USER_DISCONNECT(W , SR_t(USER_IS_NOT_FROM_LSERVER),CR_t(CH2W_USER_LOGIN_CHANNEL) , Data.pid);
			return;
		}
		if(jw_strcmp(pPlayer->m_szID , Data.id))
		{
			//해당 유저 pid는 찾았으나 pid에 해당하는 id name이 틀렸다.
			jSEND_ERROR_USER_DISCONNECT(W , SR_t(IDNAME_IS_NOT_MATCH_FROM_UID) ,CR_t(CH2W_USER_LOGIN_CHANNEL) , Data.pid);
			return;
		}
		pPlayer->Set_Server(eChannel, si->m_sid);
		jGET_DBCache(pDB,pPlayer,CH2W_USER_LOGIN_CHANNEL);

		jNET_SEND(pDB,W2DC_USER_LOGIN_CHANNEL, Data.pid,Data.id,si->m_sid);

	}
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(CH2W_NEW_TOWN)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jServerInfo* si
		READ_PACKET_PS_BS(CH2W_NEW_TOWN);

		jPlayerBase* pPlayer=0;
		{
			
			pPlayer = g_PL.find(Data.pid);
		}
		if(!pPlayer)
		{
			//해당 유저가 로긴서버로 접속된상태가아님. 강제종료시켜야함.
			jSEND_ERROR_USER_DISCONNECT(W , SR_t(USER_IS_NOT_FROM_LSERVER),CR_t(CH2W_NEW_TOWN) , Data.pid);
			return;
		}

		jAUTO_LOCK_CS1(ChannelUsingList::Get().m_CS);
		nXML::jE eChannel = ChannelUsingList::Get().GetFreeChannel(Data.csid,pPlayer->m_szID,Data.tpsid);
		if(eChannel.empty())
		{
			jSEND_ERROR_TO_USER(W , SR_t(FREE_TOWN_NOT_FOUND),CR_t(CH2W_NEW_TOWN) , Data.pid);
			return;
		}

		jGET_DBCache(pDB,pPlayer,CH2W_NEW_TOWN);
		jNET_SEND(pDB,W2DC_NEW_TOWN, Data.pid,Data.csid,Data.tpsid , Data.town_name);
		
	}


	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jServerInfo* si
		READ_PACKET_PS_BS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)





