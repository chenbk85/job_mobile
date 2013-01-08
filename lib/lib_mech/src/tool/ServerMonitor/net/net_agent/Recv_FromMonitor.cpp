/* file : Recv_MonitorServer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:05:50
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "net_agent.h"
#include "PlugIn_ToBackEnd.h"

jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	using namespace nSM;

	namespace _from_MonitorServer
	{

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(S_ECHO,MonitorServer)
		{

			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(S_ECHO);

			if(Data.type==0)
			{
				jLOG(_T("TS_ECHO(%d) %s"),Data.type, Data.msg.c_str());
			}
			else
			{
				jLOG(_T("\t%s"),Data.msg);
			}

#if 0
			if( Data.msg[0]=='%' ) 
			{
				tstring str = Data.msg+1;

				if( isdigit(str[0]))
				{

					TCHAR* ch = jt_strchr(Data.msg+1 , ' ');
					if(!ch) return;
					*ch=0;
					int id = jt_atoi(Data.msg+1);
					if(id != pBE->m_DummyID) return;
					++ch;
					str =ch; 
				}
				if(nCONSOLE::Get_jIConsoleCmd()->ParseCmd(jT(str) ))
				{
					nswb1024_t buf;
					pS->WritePacket(&WRITE_TS_ECHO(buf
						, jA(pBE->m_DummyName)
						,str.c_str()
						,2));
				}
			}
#endif
		}
	


		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(S_HELLO,MonitorServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(S_HELLO);
			vector<astring> servers;
			vector<tstring> states;
			jIE* it = g_peServerExeList->begin();
			jrFOR(it)
			{
				jIVar* pV = it->GetAttrVar(jS(ENABLE));
				if(pV && !pV->Get_bool()) continue;

				jCONTINUE(nSM::g_jSMA->m_ServerInfo.count(jW(it->GetTagName()) ) );
				states.push_back(nSM::g_jSMA->m_ServerInfo[jW(it->GetTagName())].m_eServerState);
				servers.push_back(jA(it->GetTagName()) );
			}
			jNET_SEND(pS,X2S_LOGIN,jW(g_ExeEnv.m_szComputerName),"",servers,states);
		}
		jNET_EVENT_RECEIVER_P2P(S2X_LOGIN_OK,MonitorServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(S2X_LOGIN_OK);
			pBE->m_did = Data.did;
			using namespace nSM;

			jRETURN(g_peServerExeList);
			jIE* pE = g_peServerExeList->begin();
			jrFOR(pE)
			{
				jvCONTINUE(g_jSMA->m_ServerInfo.count(jW(pE->GetTagName())) ,_T("pE->GetTagName() = %s"), pE->GetTagName());
				jServerInfo& si = g_jSMA->m_ServerInfo[jW(pE->GetTagName())];
				wstring out;
				si.ToString_Info(out);
				SendToMonitor_ServerInfo(jW(pE->GetTagName()) , si,out.c_str() ,true);
			}
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(M2A_CALL_CMD_RQ,MonitorServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(M2A_CALL_CMD_RQ);
			
			if(Data.eServerType==jS(eST_AGENT) )
			{
				nCONSOLE::Get_jIConsoleCmd()->ParseCmd(jT(Data.cmd.c_str()));
			}
			else
			{
				jSendToServer(jW(Data.eServerType),nSM::eA2SS_CMD, Data.cmd.c_str() );
			}
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(M2A_PROCESS_INFO_UPDATE,MonitorServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(M2A_PROCESS_INFO_UPDATE);
			jRETURN(g_jSMA->m_ServerInfo.count(jW(Data.eServerType)));
			nSM::jServerInfo& si = g_jSMA->m_ServerInfo[jW(Data.eServerType)];
			si.m_Data[Data.name]=Data.value;
			g_jSMA->WritePacket(jW(Data.eServerType) , nSM::eA2S_PROCESS_INFO_UPDATE , L"%s#%s",jW(Data.name),Data.value.c_str() );
		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(M2A_RESET_ERROR_LOG_COUNT,MonitorServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(M2A_RESET_ERROR_LOG_COUNT);

#define __M2A_RESET_ERROR_LOG_COUNT(errorString, tag) \
			if(si.m_Data.count(_jW(tag)))\
			{\
				si.m_Data[_jW(tag)] = L"0";\
				jNET_SEND(pS,A2M_PROCESS_INFO_NOTIFY,jA(it->first.c_str()), _jW(tag) , L"0");\
			}\
				
			jSM_net_agent::m_ServerInfo_it it = g_jSMA->m_ServerInfo.begin() ,ie = g_jSMA->m_ServerInfo.end();
			for(; it!=ie; ++it)
			{
				jServerInfo& si = it->second;
				for_each_ERROR_LOG_GAME(__M2A_RESET_ERROR_LOG_COUNT);
				for_each_ERROR_LOG_PBRMS(__M2A_RESET_ERROR_LOG_COUNT);
			}

		}
	
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(M2A_RUN_EXE,MonitorServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(M2A_RUN_EXE);
			if(Data.type==1)
			{

			}
		}

		jNET_EVENT_RECEIVER_P2P(M2A_SEND_FILE,MonitorServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			READ_PACKET_SEND_FILENAME(szFileName,iTransferTime,iFileSize);
			be_READ_PACKET_P2P_PB(M2A_SEND_FILE);
			jCHECK(Data.type==0);
			jCHECK(Data.target_dir==_T("asdf1234") );

			jLOG(_T("Time=%d,Size= %d , szFileName=%s "),iTransferTime,iFileSize,szFileName);
		}

		

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,MonitorServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(aaa);
		}
#endif

	}//namespace _from_MonitorServer

}
jNET_EVENT_END(PlugIn_ToBackEnd)
