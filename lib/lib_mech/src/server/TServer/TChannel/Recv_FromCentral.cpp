/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TChannel.h"

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
			TestUser* pUser = pP->GetUser(pS);
			TCHAR msg[1024];
			jt_sprintf(msg, _T("P2P_TcpServ:%s> %s"),pUser->GetName() , Data.msg);
			net_string256 sendS = msg;
			jPacket_Base pk = WRITE_LG2X_ECHO(buf, sendS);

			jIPacketSocket_IOCP* p = 0;
			pP->WritePacket(&pk,p );
		}
	}
#endif

	namespace _from_backend_server
	{
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_NOTICE,CentralServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET_PC_B(C2_NOTICE);

			jPS();
			//pPS->WritePacket(WRITE_L2X_NOTICE(buf, Data.info,Data.msg,Data.date),0);
		}

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,CentralServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET_PC_B(aaa);
		}
#endif

	}//namespace _from_backend_server

}
jNET_EVENT_END(PlugIn_Connect)


