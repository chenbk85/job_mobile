/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToBackEnd.h"
#include "PlugIn_ToFrontEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"
#include "network/protocal/PT_LoginServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
using namespace nLoginServer;


jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{

#if 0
	namespace _tcp_server_not_used
	{
		jNET_EVENT_RECEIVER_P2P_SERVER_tcp(C2S_ECHO)
		{
			// PlugIn_ToBackEnd*pBE , BYTE buf[1024] , TestUser* pUser
			be_READ_PACKET_P2P_PB(C2S_ECHO);
			TestUser* pUser = pP->GetUser(pS);
			TCHAR msg[1024];
			jt_sprintf(msg, _T("P2P_TcpServ:%s> %s"),pUser->GetName() , Data.msg);
			net_string256 sendS = msg;
			jPacket_Base pk = WRITE_LG2X_ECHO(buf, sendS);

			jIPacketSocket_IOCP* p = 0;
			pP->send_all(&pk,p );
		}
	}
#endif

	namespace _from_backend_server
	{
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C_HELLO,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(C_HELLO);

			jFE();
			jSOCKADDR_IN* pAddr = pFE->m_pServer->GetTcpListenAddress();
			tname32_t szIP;
			pAddr->GetIP(szIP);

			pBE->m_MyInfo.MakeInfo(pBE->m_eServers,g_ExeEnv.m_szComputerName, pv_WORLD_NAME->Get_cstr()
				, szIP , jServerInfoBase::eLogin 
				, pAddr->GetPort() , 0, Get_MAX_USER() );
			//pBE->m_eServers->DebugPrint(true);
			S_SS2C_ONLINE pk;	pk.eType = jServerInfoBase::eLogin;  pk.xml = pBE->m_eServers;
			pS->WritePacket(&nCentralServer::WRITE_SS2C_ONLINE(buf, pk ));

		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_NOTICE,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(C2_NOTICE);

			jFE();
			pFE->send_all(WRITE_L2X_NOTICE(buf, Data.info,Data.msg,Data.date),0);
		}

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(aaa);
		}
#endif

	}//namespace _from_backend_server

}
jNET_EVENT_END(PlugIn_ToBackEnd)


