/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(SS2DC_ONLINE)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(SS2DC_ONLINE);
		jRecv_SS2server_ONLINE();
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(DC_ECHO)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(DC_ECHO);
		pS->WritePacket(&WRITE_DC_ECHO(buf, Data));
	}

	

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)



