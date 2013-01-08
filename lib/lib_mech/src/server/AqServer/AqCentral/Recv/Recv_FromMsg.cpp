/* file : Recv_FromLogin.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:50:10
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nCentralServer;




jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode*pFServer
		READ_PACKET_C(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)


