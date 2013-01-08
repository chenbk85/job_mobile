/* file : Recv_SM_server.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-05-08 21:06:07
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToBackEnd.h"

using namespace nSM;
void JOB_check_killed_eServerType(nEVENT::jIMessage* pM);
/*
jDBQ_EVENT_RECEIVER(aaa)
{
	jPARSE_SMA(); //g_jSMA , wcstr sz,vector<wstring> arg,nswb1024_t buf
}
*/

jDBQ_EVENT_RECEIVER(eAGENT_ECHO)
{
	jPARSE_SMA();//g_jSMA , wcstr sz,vector<wstring> arg,nswb1024_t buf
}


void parse_ONLINE_String(jServerInfo& si, wcstr sz)
{
	vector<wstring> out;
	nString::jSplitW(sz,L"~",out);
	for(int i=0; i<out.size();++i)
	{
		vector<wstring> out2;
		nString::jSplitW(out[i], L"=" , out2);
		si.m_Data[out2[0]]=out2[1];
	}
}

void SendToMonitor_ServerInfo(const wstring& sServerType,jServerInfo& si,wcstr sz,bool isSendConnected)
{
	jBE();
	nswb4000_t buf;
	if(isSendConnected)
	{
		jNET_SEND(pBE->m_pS_MonitorServer,A2M_SERVER_CONNECTED,jT(sServerType),si.m_eServerState.c_str());
	}
	jNET_SEND(pBE->m_pS_MonitorServer,A2M_NOTIFY_SERVER_INFO,jT(sServerType),sz,si.m_eServerState.c_str());
}

jDBQ_EVENT_RECEIVER(eSERVER_OFFLINE) // agent's module
{
	jPARSE_SMA();//g_jSMA, arg, nswb1024_t buf
	jServerInfo& si = g_jSMA->m_ServerInfo[arg[0]];
	//
	if(si.m_pM_JOB_check_process_killed)
	{
		si.m_pM_JOB_check_process_killed->Erase();
		si.m_pM_JOB_check_process_killed=0;
	}
	jBE();
	nEVENT::jIMessage* pM= pBE->m_pMM->Regist_TimeBaseAndCount(0,jFUNC_Msg(JOB_check_killed_eServerType),2,fTIMEPULS_CHECK_KILL_FAST,iMAX_CHECK_KILL_FAST);
	pM->GetArg(0)->Set_cstr(jT(arg[0].c_str()));
	pM->GetArg(1)->SetUserData(&si);
	si.m_pM_JOB_check_process_killed = pM;
	pM->DoWakeUp();

}

jDBQ_EVENT_RECEIVER(eS2A_ONLINE_RQ) // agent's module
{
	jPARSE_SMA();//g_jSMA, arg, nswb1024_t buf
	jServerInfo& si = g_jSMA->m_ServerInfo[arg[0]];
	if(si.m_eServerState==jS(eSS_Offline))
		si.m_eServerState = jS(eSS_Online);

	wcstr szInfo  =arg.size()>=2 ? arg[1].c_str():L"";
	parse_ONLINE_String(si,szInfo);

	SendToMonitor_ServerInfo(arg[0],si,szInfo ,false);
	g_jSMA->WritePacket(arg[0],nSM::eA2S_ONLINE_RS,L"%d",(uint32)GetCurrentProcessId());

	jBE();
	if(!si.m_pM_JOB_check_process_killed)
	{
		nEVENT::jIMessage* pM= pBE->m_pMM->Regist_TimeBase( 0 , jFUNC_Msg(JOB_check_killed_eServerType ), 2 , pv_check_time_processkill->Get_float() );
		pM->GetArg(0)->Set_cstr(jT(arg[0].c_str()));
		pM->GetArg(1)->SetUserData(&si);
		pM->DoWakeUp();
		si.m_pM_JOB_check_process_killed = pM;
	}

}


// X(NIC,LOGIN_CMD,ZONE_CMD)  Mythology.exe ¸Þ´º
#define Recv_MYTHOLOGY_MENU_CMD(NIC,LOGIN_CMD,ZONE_CMD)\

for_each_MYTHOLOGY_MENU_CMD(Recv_MYTHOLOGY_MENU_CMD);


jDBQ_EVENT_RECEIVER(eS2A_SERVER_MENU_CMD_RS)
{
	jPARSE_SMA();jBE();
	enum
	{
		eServerExeListNode,
		eEServerState,
	};

	jRETURN( g_jSMA->m_ServerInfo.count(arg[eServerExeListNode]) );
	nSM::jServerInfo& si = g_jSMA->m_ServerInfo[arg[eServerExeListNode]];

	si.m_eServerState = jT(arg[eEServerState]);
	jNET_SEND(pBE->m_pS_MonitorServer,A2M_MYTHOLOGY_MENU_RS,jT(arg[eServerExeListNode]),jA(si.m_eServerState) );
}

jDBQ_EVENT_RECEIVER(eSS2A_CMD_RS)
{
	jPARSE_SMA2(); //g_jSMA , wcstr sz,vector<wstring> arg,nswb1024_t buf
	
	enum
	{
		eServerExeListNode,
		eeCMD,
	};

	wcstr szCmd = jw_strchr(sz,'#');
	if(!szCmd) szCmd = sz;
	else ++szCmd;

	jNET_SEND(pBE->m_pS_MonitorServer , A2M_CALL_CMD_RS , jT(arg[eServerExeListNode]) ,szCmd);

	if(arg[eeCMD] == L"REFRESH_EServerState")
	{
		nSM::jServerInfo& si = g_jSMA->m_ServerInfo[arg[eServerExeListNode]];
		si.m_eServerState = jT(arg[2].c_str());
	}
}

jDBQ_EVENT_RECEIVER(eS2A_SEND_ERROR_LOG)
{
	jRETURN(g_jSMA);
	wcstr sz = (wcstr)pReadBuff;
	std::vector<wstring> arg;
	nString::jSplitW(sz,L"#",arg);
	enum{eServerExeListNode,eTag,eLog,eMAX};
	jRETURN(arg.size()>=eMAX);
	GetjILog()->Log(0,_T("\006%s"),jT(sz));

	nSM::jServerInfo& si = g_jSMA->m_ServerInfo[arg[eServerExeListNode]];
	wstring & str = si.m_Data[arg[eTag]];
	int count = jw_atoi(str.c_str());
	++count;
	wfname_t szBuf;
	jw_sprintf(szBuf,L"%d",count);
	str = szBuf;

	nswb1024_t buf;
	jBE();
	jRETURN(pBE->m_pS_MonitorServer);
	jNET_SEND(pBE->m_pS_MonitorServer,A2M_SEND_ERROR_LOG, jA(arg[eServerExeListNode]),sz); 
	jNET_SEND(pBE->m_pS_MonitorServer,A2M_PROCESS_INFO_NOTIFY, jA(arg[eServerExeListNode]),arg[eTag].c_str(),szBuf); 
}

jDBQ_EVENT_RECEIVER(eS2A_PROCESS_INFO_UPDATE)
{
	jRETURN(g_jSMA);
	wcstr sz = (wcstr)pReadBuff;std::vector<wstring> arg;
	nString::jSplitW(sz,L"#",arg);
	jBE();

	enum{eServerExeListNode,eName,eValue,eMAX};
	jRETURN(arg.size()>=eMAX);
	{
		nswb4000_t buf;
		jNET_SEND(pBE->m_pS_MonitorServer,A2M_PROCESS_INFO_NOTIFY, jA(arg[eServerExeListNode]),arg[eName].c_str(),arg[eValue].c_str()); 
	}
}





/*

jDBQ_EVENT_RECEIVER(eSS2A_CMD_RS)
{
jPARSE_SMA2(); //g_jSMA , wcstr sz,vector<wstring> arg,nswb1024_t buf, jBE();

}

jDBQ_EVENT_RECEIVER(aaa)
{
	jPARSE_SMA(); //g_jSMA , wcstr sz,vector<wstring> arg,nswb1024_t buf
}
*/
