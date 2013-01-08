/* file : PlugIn_ToBackEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqTrade.h"
#include "PlugIn_ToBackEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"
#include "../AqCommon/jDBCacheConnection.h"

using namespace nMech::nNET::nCentralServer;

jDEFINE_RTTIOBJ_BY_SCOPE(PlugIn_ToBackEnd,jNet, 1,1);
JNET_PLUGIN_SINGTONE_DEFINE(PlugIn_ToBackEnd);

//DECLARE_INSTANCE_TYPE(S_TA_SET_TEST_ENV);
jSQ_REGIST_BIND(PLUGIN)
//jSQ_REGIST_BIND_jINetPlugIn_CLIENT(PlugIn_ToBackEnd)
{
	jSQ_Interface(PlugIn_ToBackEnd)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}

void _OnPacketSize_UsageInfo(tcstr szPlugIn,uint64 packet_size,tname1024_t info)
{
	g_jAqCommon.OnPacketSize_UsageInfo(szPlugIn,packet_size);
#if 0
	jBE();;
	if(!pBE->m_pToCentral) return;
	nswb256_t buf;
	pBE->m_pToCentral->WritePacket(&nCentralServer::WRITE_C4_SERVER_STATUS(buf, g_jAqCommon.Get_PacketUsage() , Get_CURR_USER() ) );
#endif

}

PlugIn_ToBackEnd::PlugIn_ToBackEnd()
{
	m_pToCentral=0;

}

void PlugIn_ToBackEnd::Start()
{	
	g_jDBCacheConnection.clear();
	m_LobbyServers.m_servers.clear();
	Set(this);
	g_pCurrPlugInBE = this;

}

void PlugIn_ToBackEnd::Stop()
{	
	Set(0);
	if(g_pCurrPlugInBE==this)
		g_pCurrPlugInBE=0;
}

bool PlugIn_ToBackEnd::ParseCmd(tcstr szCommand)
{
	if(!m_pToCentral) return false;
	if(!m_pToCentral->IsConnected()) return false;
	net_string256 sendS;
	jt_sprintf(sendS ,_T("%d-%s>%s") , m_sid, g_ExeEnv.m_szComputerName,szCommand);
	nswb1024_t sendBuf;
	m_pToCentral->WritePacket(&nCentralServer::WRITE_C_ECHO(sendBuf,sendS));
	return false;
}

VOID PlugIn_ToBackEnd::OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP)
{
	jIPlugIn_Net::OnIoRead(pS,pk,pIP,pHT);
}


VOID PlugIn_ToBackEnd::OnIoConnected(jIPacketSocket_IOCP* pS)
{
	//nswb1024_t buf;
	if(pS->GetType() == nNET::eACCEPTED_SOCKET) 
	{
#if 0
		TestUser* pUser = Add_User(pS);
		pS->WritePacket(&nTestServer::WRITE_S2C_TCP_ONLINE(buf));
#endif
	}
	else
	{
		GetjILog()->Log(jFUNC1 _T("%s"), pS->Get_jIE()->GetTagName() );
		if(pS->Get_jIE()->IsName(jS(ToCentral)))
		{
			m_pToCentral = pS;
		}
	}
}

VOID PlugIn_ToBackEnd::OnIoDisconnected(jIPacketSocket_IOCP* pS)
{
	if(pS->GetType() == nNET::eACCEPTED_SOCKET) 
	{
		//jAssert0(0);
		GetjILog()->Log(jFUNC1 _T(" from client"));
		//Delete_User(pS);
	}
	else
	{
		GetjILog()->Log(jFUNC1 _T("%s"), pS->Get_jIE()->GetTagName() );
		if(pS->Get_jIE()->IsName(jS(ToCentral)))
			m_pToCentral=0;
		else
		{
			if(g_jDBCacheConnection.IsValidSocket(pS) && g_jDBCacheConnection.erase(pS))
			{
				//jTODO 기존유저중에 이 db cacheserver를 사용하는 유저의 db컨넥션정보를 초기화시켜야한다.
				// 즉 이 유저들은 당분간 db처리관련 액션을 취할수 없다.
			}
		}
	}

}


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
		using namespace nCentralServer;
#if 0
		jNET_EVENT_RECEIVER_P2P(C2_END_SERVER,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_P(C2_END_SERVER);
			if(jServerInfo::IsLobby(Data.sid))
			{
				nUtil::jCriticalSection::Auto a(&pP->m_LobbyServers_CS);
				pP->m_LobbyServers.Delete_Server(Data.sid);
			}
		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_START_SERVER,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_P(C2_START_SERVER);

			if(Data.server.IsLobby())
			{
				nUtil::jCriticalSection::Auto a(&pP->m_LobbyServers_CS);
				pP->m_LobbyServers.Insert_Server(Data.server);
			}
			else if(Data.server.IsDBCache())
			{
				jDBCacheInfo* db= g_jDBCacheConnection.insert(Data.server , pP);
			}
		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C_HELLO,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(C_HELLO);

			fe_PLUGIN(pPF);
			jSOCKADDR_IN* pAddr = pPF->m_pServer->GetTcpListenAddress();
			tname32_t szIP;
			pAddr->GetIP(szIP);
			uint16 port = pAddr->GetPort();
			pS->WritePacket(&nCentralServer::WRITE_SS2C_ONLINE(buf, g_ExeEnv.m_szComputerName, Get_MAX_USER(), jA(szIP),port ));

		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_LOBBY_USERS_COUNT_CHANGE,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_P(C2_LOBBY_USERS_COUNT_CHANGE);
			nUtil::jCriticalSection::Auto a(&pP->m_LobbyServers_CS);
			for(int i= 0; i < Data.servers.size(); ++i)
			{
				jServerUserCountInfo &info = Data.servers[i];
				jServerInfo* pLobby = pP->m_LobbyServers.Find_Server(info.sid);
				if(pLobby)
				{
					pLobby->totClient = info.totClient;
				}
			}
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_LOG_FILE_DAY_CHANGE,CentralServer)
		{
			GetjILog()->SetFileName(0);
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_USERSOCKET_CLOSE,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(C2_USERSOCKET_CLOSE);
			fe_PLUGIN(pPC);
			AqServerNode* pUser = pPC->find_user(Data.uid);
			if(pUser&&pUser->m_pS)
				pPC->m_pServer->DisconnectTcpClient(pUser->m_pS);
		}

#endif


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
