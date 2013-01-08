/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TGame.h"



jNET_EVENT_BEGIN(PlugIn_Server)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(G_ECHO)
	{
		// PlugIn_Server*p , BYTE buf[1024] , TClientUser* pUser
		READ_PACKET_FromClient(G_ECHO);
		jNET_SEND2(g_SG.m_Client , G_ECHO,Data.msg, Data.type);
	}

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server*p , BYTE buf[1024] , TClientUser_D* pDummy
		READ_PACKET_FromClient(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)




