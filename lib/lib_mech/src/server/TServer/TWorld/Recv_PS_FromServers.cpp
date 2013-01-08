/* file : Recv_FromServers.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-07 11:49:54
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TWorld.h"


jNET_EVENT_BEGIN(PlugIn_Server)
{

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(SS2W_ONLINE)
	{
		// PlugIn_Server* pPS , BYTE buf[1024] , jIGridNode* pServer
		jRecv_SS2server_ONLINE(W);
		
		//User , Central, Command(if not exist Central)  에서만 보낸다.
		//jNET_SEND(pS,W2SS_ONLINE_OK,si->m_sid);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(W_ERROR)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jIGridNode* pDummy
		READ_PACKET_PS_BS(W_ERROR);
		jPacket_Base pk = WRITE_W_ERROR(buf,Data);
		jPlayerBase* pPlayer= g_PL.find(Data.ei.pid);
		if(pPlayer)
		{ // 해당 서버에만 보냄.
			jIGridNode* pGN = g_SG.find_if(eChannel,send_packet_sid(pPlayer->Get_Server(eChannel), pk ) );
			if(!pGN) jWARN("Channelserver is not connected : %s",jT(pPlayer->m_szID));

			pGN = g_SG.find_if(eGame,send_packet_sid(pPlayer->Get_Server(eGame), pk ) );
			if(!pGN) jWARN("Gameserver is not connected : %s",jT(pPlayer->m_szID));
		}
		else
		{ // 모두 다 보냄.
			jWARN("User not found : %s",jT(pPlayer->m_szID));
			g_SG.find_if(eChannel,send_packet(pk ) );
			g_SG.find_if(eGame,send_packet(pk ) );
		}
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(W4_USER_DISCONNECT)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jIGridNode* pDummy
		READ_PACKET_PS_BS(W4_USER_DISCONNECT);

		pPS->Send_W2DC_USER_DISCONNECT(Data.id);
	}

	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jIGridNode* pDummy
		READ_PACKET_PS_BS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)



