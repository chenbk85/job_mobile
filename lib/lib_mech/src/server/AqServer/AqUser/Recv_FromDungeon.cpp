/* file : Recv_FromDungeon.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-03 13:48:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode*pServer
		READ_PACKET_FromServer(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)




