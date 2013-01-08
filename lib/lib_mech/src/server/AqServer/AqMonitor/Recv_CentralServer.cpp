/* file : Recv_CentralServer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-30 13:20:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqMonitor.h"
#include "util/jRegistry.h"


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

	namespace _from_CentralServer
	{
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C_HELLO,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(C_HELLO);

			//jSend_SS2C_ONLINE(g_ExeEnv.m_szComputerName, jS(AqMonitor),eMonitor);
			tcstr name =g_ExeEnv.m_szComputerName;
			tcstr world = jS(AqMonitor);

			while(pBE->m_eServers.empty());
			nMech::nUtil::CRegistry reg;
			reg.Open(_T("SOFTWAREjGamejAqServer"),HKEY_LOCAL_MACHINE);
			if(!reg[_T("name_number")].Exists()) reg[_T("name_number")] = (int)0;
			int name_number = reg[_T("name_number")];
			fname_t szServerName;
			jt_sprintf(szServerName,_T("%s_%d"),name,name_number);
			++name_number;
			reg[_T("name_number")]=name_number;
			reg.Close();

			pBE->m_MyInfo.MakeInfo(pBE->m_eServers,szServerName, world, _T("127.0.0.1") , jServerInfoBase:: eMonitor, 0 , 0);
			S_SS2C_ONLINE pk= {pBE->m_MyInfo.m_eType ,pBE->m_eServers};
			pS->WritePacket(&nCentralServer::WRITE_SS2C_ONLINE(buf, pk ));

		}
		jNET_EVENT_RECEIVER_P2P(C2SS_ONLINE_OK,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			jRecv_C2SS_ONLINE_OK();
		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C_SERVER_ONLINE,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			jRecv_C_SERVER_ONLINE();
		}


#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(aaa);
		}
#endif

	}//namespace _from_CentralServer

}
jNET_EVENT_END(PlugIn_ToBackEnd)
