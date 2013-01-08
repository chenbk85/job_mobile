/* file : Recv_FromLogin.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:50:10
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_Server.h"
#include "../TCommonClient/protocal/PT_CentralServer_Enum.h"
using namespace nCentralServer;




jNET_EVENT_BEGIN(PlugIn_Server)
{

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jServerInfo*si
		READ_PACKET_PS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)


