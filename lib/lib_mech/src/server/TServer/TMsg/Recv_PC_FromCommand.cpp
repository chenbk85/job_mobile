/* file : Recv_FromLogin.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:50:10
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TMsg.h"

#include "util/jRegistry.h"


jNET_EVENT_BEGIN(PlugIn_Connect)
{

#if 0
	namespace _tcp_server_not_used
	{
		jNET_EVENT_RECEIVER_P2P_SERVER_tcp(C2S_ECHO)
		{
			// PlugIn_Connect*pPC , BYTE buf[1024] , TestUser* pUser
			READ_PACKET_PC_B(C2S_ECHO);
		}
	}
#endif

	namespace _from_backend_server
	{
#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,CommandServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET_PC_B(aaa);
		}
#endif

	}//namespace _from_backend_server

}
jNET_EVENT_END(PlugIn_Connect)


