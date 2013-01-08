/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDummy.h"


jNET_EVENT_BEGIN(PlugIn_Server)
{
	//사용하지 않음.
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2DT_HELLO)
	{
		// PlugIn_Server* pPS , BYTE buf[1024] , jIGridNode* pServer
		READ_PACKET_PS_BS(X2DT_HELLO);
		*si = Data.si;
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

