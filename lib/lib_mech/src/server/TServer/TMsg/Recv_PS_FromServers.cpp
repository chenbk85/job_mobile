/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TMsg.h"


jNET_EVENT_BEGIN(PlugIn_Server)
{

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(SS2MG_ONLINE)
	{
		// PlugIn_Server* pPS , BYTE buf[1024] , jIGridNode* pServer
		jRecv_SS2server_ONLINE(MG);
		//User , Central, Command(if not exist Central)  에서만 보낸다.
		//jNET_SEND(pS,W2SS_ONLINE_OK,si->m_sid);
	}


#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server* pPS , BYTE buf[1024] , jServerInfo* si
		READ_PACKET_PS_BS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)

