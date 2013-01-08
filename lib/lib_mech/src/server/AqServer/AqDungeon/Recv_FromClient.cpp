/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToBackEnd.h"
#include "PlugIn_ToFrontEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;



jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(D_ECHO)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(D_ECHO);
		pFE->send_all(WRITE_D_ECHO(buf, Data.msg, Data.type),0);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_CHAT)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2D_CHAT);
		pFE->send_all(WRITE_D2X_CHAT(buf, Data.msg, Data.type),0);
	}

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser_D* pDummy
		READ_PACKET_FromClient(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)




