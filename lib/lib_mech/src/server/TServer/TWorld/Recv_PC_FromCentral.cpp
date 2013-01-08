/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-07 11:47:27
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TWorld.h"

#include "util/jRegistry.h"


jNET_EVENT_BEGIN(PlugIn_Connect)
{

#if 0
	namespace _tcp_server_not_used
	{
		jNET_EVENT_RECEIVER_P2P_SERVER_tcp(C2S_ECHO)
		{
			// PlugIn_Connect*pPC , BYTE buf[1024] , TestUser* pPlayer
			READ_PACKET_PC_B(C2S_ECHO);
			TestUser* pPlayer = pP->GetUser(pS);
			TCHAR msg[1024];
			js_sprintf(msg, _T("P2P_TcpServ:%s> %s"),pPlayer->GetName() , Data.msg);
			net_string256 sendS = msg;
			jPacket_Base pk = WRITE_LG2X_ECHO(buf, sendS);

			jIPacketSocket_IOCP* p = 0;
			pP->WritePacket(&pk,p );
		}
	}
#endif

	namespace _from_backend_server
	{

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_LOG_FILE_DAY_CHANGE,CentralServer)
		{
			GetjILog()->SetFileName(0);
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_USERSOCKET_CLOSE,CentralServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET_PC_B(C2_USERSOCKET_CLOSE);
			fe_PLUGIN(pPC);
			jIGridNode* pPlayer = g_SG.find_user(Data.pid);
			if(pPlayer&&pPlayer->m_pS)
				g_SG.m_pServer->DisconnectTcpClient(pPlayer->m_pS);
		}

#endif


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



