/* file : PlugIn_ToBackEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "net_agent.h"
#include "PlugIn_ToBackEnd.h"
#include "base/jWindow_Util.h"
#include "mech/util/sm/jRoC_SharedMemory.h"
#include "util/jProcess.h"

PlugIn_ToBackEnd* g_pCurrPlugIn=0;

void reconnect_to_monitor(nEVENT::jIMessage* pM)
{
	jBE();
	++pBE->m_iRetryCount;

	if(pBE->m_iRetryCount >pv_reconnect_count->Get_int())
	{
		if(pM)
			pM->Erase();

		nCONSOLE::Get_jIConsoleCmd()->ParseCmd(_T("@net_agent.restart"));
		return;
	}

	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(_T("@net_agent.reconnect"));
}


jSQ_REGIST_BIND(PLUGIN)
{
	jSQ_Interface(PlugIn_ToBackEnd)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}

/*

jDummyPlayer* PlugIn_ToBackEnd::GetDummyUser(jIPacketSocket_IOCP* pS)
{
	return (jDummyPlayer*)pS->Get_jIE()->GetUserData(jS(jDummyPlayer));
}
*/


PlugIn_ToBackEnd::PlugIn_ToBackEnd()
{
	m_pS_MonitorServer=0;
	if(!g_peServerExeList)
		g_peServerExeList = nGLOBAL::g_pDocApp->Find(jS(ServerExeList));

	m_pM_Process_live_Check=0;
	m_pReconnecterToMonitor=0;
	if(!nSM::g_jSMA)
	{
		vector<wstring> serverExeList;

		#define jLAMDA_get_server_name(X,Z) Z(vector<wstring>&,serverExeList)
		jLAMDA_for_each(get_server_name,jIE*)
		{
			serverExeList.push_back(jW(it->GetTagName()));
		}
		jLAMDA_end();
		for_each_ServerExeList(get_server_name(serverExeList));

		nSM::g_jSMA = new nSM::jSM_net_agent;
		nSM::g_jSMA->Start(serverExeList);
		uint32 pid =(uint32)GetCurrentProcessId();

		#define jLAMDA_send_eA2S_ONLINE_RQ(X,Z) Z(uint32 ,pid)
		jLAMDA_for_each(send_eA2S_ONLINE_RQ,jIE*)
		{
			jSendToServer(jW(it->GetTagName()) ,nSM::eA2S_ONLINE_RQ, L"%u",pid);
		}
		jLAMDA_end();
		for_each_ServerExeList(send_eA2S_ONLINE_RQ(pid));
	}
}

PlugIn_ToBackEnd::~PlugIn_ToBackEnd()
{
	if(nSM::g_jSMA)
	{
		jLAMDA_for_each0(send_eAGENT_OFFLINE,jIE*)
		{
			jSendToServer(jW(it->GetTagName()),nSM::eAGENT_OFFLINE,L"");
		}
		jLAMDA_end();
		for_each_ServerExeList(send_eAGENT_OFFLINE());

		nSM::g_jSMA->End();
		SAFE_DELETE(nSM::g_jSMA);

	}
	
}


// 기능 작동후 JOB_check_killed_eServerType()는제거 할것.
void JOB_Process_live_Check(nEVENT::jIMessage*)
{
	using namespace nSM;
	jBE();
	jCHECK(pBE->m_pS_MonitorServer);
	if(!pBE->m_pS_MonitorServer)
	{
		reconnect_to_monitor(0);
		return;
	}
	jRETURN(g_jSMA);

	jLAMDA_for_each0(check_process_state,jIE*)
	{
		jIVar* pV = it->GetAttrVar(jS(ENABLE));
		if(pV && pV->Get_bool()==false) return;
		tcstr szServerType = it->GetParent()->GetTagName();

		jBE();
		jRETURN(pBE->m_pS_MonitorServer);
		jRETURN(g_jSMA);

		jSM_net_agent::m_ServerInfo_it itSI , ieSI = g_jSMA->m_ServerInfo.end();
		itSI = g_jSMA->m_ServerInfo.find(jW(szServerType));
		if(itSI==ieSI)
			return;
		jServerInfo& si = itSI->second;
		fname_t szExe;
		nFileSystem::jFileName fn(it->Get_cstr());
		fn.GetName(szExe);
		nswb1024_t buf;
		DWORD pid = nUtil::jProcess::is_Exist(szExe) ;
		if( pid )
		{
			if( si.m_eServerState==jS(eSS_Offline))
			{
				si.m_eServerState=jS(eSS_Online);
				jNET_SEND(pBE->m_pS_MonitorServer,A2M_PROCESS_STATUS_NOTIFY,jA(szServerType) , "eSS_Online" );
				wfname_t szPID;
				jw_sprintf(szPID,L"%u",pid);
				jNET_SEND(pBE->m_pS_MonitorServer,A2M_PROCESS_INFO_NOTIFY,jA(szServerType) , L"pid" , szPID);
			}
		}
		else
		{
			if(si.m_eServerState!=jS(eSS_Offline))
			{
				si.m_eServerState=jS(eSS_Offline);
				jNET_SEND(pBE->m_pS_MonitorServer,A2M_PROCESS_STATUS_NOTIFY,jA(szServerType) , "eSS_Offline");
				jNET_SEND(pBE->m_pS_MonitorServer,A2M_PROCESS_INFO_NOTIFY,jA(szServerType) , L"pid" , L"0");
				//만약 한프로세스에서 login / zone을 뛰우는 상황이라면.
				if(!jt_strcmp(szServerType,jS(eLOGIN)))
				{
					jSM_net_agent::m_ServerInfo_it itZone = g_jSMA->m_ServerInfo.find(jW(szServerType));
					if(itZone!=ieSI)
					{
						nSM::jServerInfo& siZone = itZone->second;
						if(siZone.m_Data[_jW(pid)] == si.m_Data[_jW(pid)])
						{
							siZone.m_eServerState= jS(eSS_Offline);
							jNET_SEND(pBE->m_pS_MonitorServer,A2M_PROCESS_STATUS_NOTIFY,"eZONE" , "eSS_Offline");
							jNET_SEND(pBE->m_pS_MonitorServer,A2M_PROCESS_INFO_NOTIFY,"eZONE", L"pid" , L"0");
						}
					}
				}
				si.m_Data[L"pid"] =L"0";

			}
		}
	}
	jLAMDA_end();

	for_each_ServerExeList(check_process_state(),false);
}

jPLUGIN_BACK_END_cpp_code_Start(PlugIn_ToBackEnd)
{
	m_pMM = nEVENT::jIMsgManager::Get(jS(PlugIn_ToBackEnd), true);\
	m_pS_MonitorServer=0;
	ResetReconnect();
	TryReconnect();

	if(!m_pM_Process_live_Check)
	{
		m_pM_Process_live_Check = m_pMM->Regist_TimeBase(0,jFUNC_Msg(JOB_Process_live_Check),0,pv_Process_live_Check_time->Get_float());
		m_pM_Process_live_Check->DoWakeUp();
	}

	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message"),_T("tcp_mode"),true ,0);
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message_txt"),_T("\"default : to test server\n\r* chat : to game server\""),true ,0);

}

jPLUGIN_cpp_code_Stop(PlugIn_ToBackEnd);
{
	if(g_pCurrPlugIn==this)
		g_pCurrPlugIn=0;
	if(m_pM_Process_live_Check)
	{
		m_pM_Process_live_Check->Erase();
		m_pM_Process_live_Check=0;
	}
}
jPLUGIN_BACK_END_cpp_code_End(PlugIn_ToBackEnd);


bool PlugIn_ToBackEnd::ParseCmd(tcstr szCommand)
{
	nswb256_t buf;

	if(!m_pS_MonitorServer)
		m_pS_MonitorServer = m_pClientSession->Get_ClientSocket(jS(TCP_MonitorServer));
	//jASSERT0(m_pS_MonitorServer);
	if(!m_pS_MonitorServer || !m_pS_MonitorServer->IsConnected())
	{
		jWARN(_T("소켓 연결이 안되었음"));
		return false;
	}

	using namespace nNET::nMonitorServer;
	jNET_SEND(m_pS_MonitorServer,S_ECHO,0,jW(szCommand));
#if 0
	jNET_SEND(m_pS_MonitorServer,X2S_THREAD_TEST1,0,jW(szCommand));
	jNET_SEND(m_pS_MonitorServer,X2S_THREAD_TEST2,0,jW(szCommand));
#endif

	return false;
}



// Init_DummySocket()로 초기화 된 정보를 이용해 접속시도
bool g_isCancel_StartSession_AllDummy=false;

VOID PlugIn_ToBackEnd::OnIoConnected(jIPacketSocket_IOCP* pS)
{
	//jFD1();

	if(pS->Get_jIE()->IsName(jS(TCP_MonitorServer)))
	{
		jMsg_ERASE(m_pReconnecterToMonitor);
		m_pS_MonitorServer = pS;
	}
	else
	{
		if(!m_pS_MonitorServer)
		{
			m_pS_MonitorServer = m_pClientSession->Get_ClientSocket(jS(TCP_MonitorServer));
		}

	}

	jLOG(_T("OnIoConnected(%s) ") , pS->Get_jIE()->GetTagName());
}


VOID PlugIn_ToBackEnd::OnIoDisconnected(jIPacketSocket_IOCP* pS)
{
	if(pS->Get_jIE()->IsName(jS(TCP_MonitorServer)))
	{
		jLOG(_T("OnIoDisconnected (%s) ") , pS->Get_jIE()->GetTagName());
		m_pS_MonitorServer = 0;
		TryReconnect();
		return;
	}

	jWARN(_T("OnIoDisconnected (%s) pUser==NULL") , pS->Get_jIE()->GetTagName());
	return;
}

void PlugIn_ToBackEnd::ResetReconnect()
{
	m_iRetryCount=0;
	jMsg_ERASE(m_pReconnecterToMonitor);
}


void PlugIn_ToBackEnd::TryReconnect()
{
	if(!m_pReconnecterToMonitor)
	{
		m_pReconnecterToMonitor = m_pMM->Regist_TimeBase(0,jFUNC_Msg(reconnect_to_monitor),0,pv_reconnect_time->Get_float());
		m_pReconnecterToMonitor->DoWakeUp();
	}
}

