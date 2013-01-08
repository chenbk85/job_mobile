/* file : cmd_Agent.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-05-09 01:49:25
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "util/jProcess.h"
using namespace nSM;

void send_A2M_CALL_CMD_RS(cstr szCmd)
{
	nswb1024_t buf;
	jBE();
	if(!pBE->m_pS_MonitorServer) return;
	jNET_SEND(pBE->m_pS_MonitorServer , A2M_CALL_CMD_RS ,jS(eST_AGENT) ,jW(szCmd));
}




jCONSOLE_CMD_AUTO(jSERVER_NAME,send_eAGENT_ECHO,0,"send to agent clients","<msg> [server_id]")
{
#define jCONSOLE_PARAM_send_eAGENT_ECHO(X,Y) X(msg,wcstr) Y(server_id,int,0)
	jCONSOLE_PARAM_END(send_eAGENT_ECHO);

	jRETURN_ret(true,g_jSMA);

	jRETURN_ret(false,g_peServerExeList);
	jIE* pE=g_peServerExeList->begin();
	jrFOR(pE)
	{
		jSendToServer(jW(pE->GetTagName()),nSM::eAGENT_ECHO,L"%s#%s",jW(jS(eVAL)),msg);
	}
	return true;
}

void server_kill_or_run(tcstr szServerType,bool isKill,DWORD iSleep=0)
{
	jRETURN(g_peServerExeList);
	jRETURN(CheckSeverType(szServerType));
	jIE* peServerExe = g_peServerExeList->Find(szServerType);
	jRETURN(peServerExe);

	jIE* it = peServerExe->begin();
	jIVar* pV;
	jrFOR(it)
	{
		pV = it->GetAttrVar(jS(ENABLE));
		if(!pV || !pV->Get_bool()) continue;
		if(it->GetVar()->IsContents(jS(NULL)) ) continue;

		nFileSystem::jFolder dir;
		fname_t szExe;
		nFileSystem::jFileName fn(it->Get_cstr());
		fn.GetName(szExe);

		if(isKill)
		{
			nUtil::jProcess::kill_Process_byName(szExe,0);
		}
		else
		{
			if(!nUtil::jProcess::is_Exist(szExe))
			{
				dir.GotoByFileName(it->Get_cstr());
				WinExec(jA(it->Get_cstr()), SW_SHOW);
				if(iSleep)
					Sleep(iSleep);
			}
		}
	}
}
bool check_process_killed(cstr szServerType)
{
	jRETURN_ret(true,g_peServerExeList);
	jIE* peServerType = g_peServerExeList->Find(szServerType);
	jRETURN_ret(true,peServerType);

	jIVar* pV = peServerType->GetAttrVar(jS(ENABLE));
	if(pV && pV->Get_bool()==false) return true;

	jRETURN_ret(true,nSM::g_jSMA->m_ServerInfo.count(jW(szServerType)) );
	nSM::jServerInfo& si = nSM::g_jSMA->m_ServerInfo[jW(szServerType)];
	if(si.m_eServerState==jS(eSS_Offline)) return true;

	bool isRet =false;
	jIE* peEXE = peServerType->begin();
	jrFOR(peEXE)
	{
		pV = peEXE->GetAttrVar(jS(ENABLE));
		if(pV && pV->Get_bool()==false) continue;

		fname_t szExe;
		nFileSystem::jFileName fn(peEXE->Get_cstr());
		fn.GetName(szExe);
		if( nUtil::jProcess::is_Exist(szExe) ) continue;
		si.m_eServerState=jS(eSS_Offline);
		fname_t szBuf;
		jt_sprintf(szBuf,_T("server_kill %s"), peServerType->GetTagName());
		send_A2M_CALL_CMD_RS(szBuf);

		jONCE
		{
			if(jt_strcmp(szServerType,jS(eLOGIN))) break;
			if(!nSM::g_jSMA->m_ServerInfo.count(_jW(eZONE))) break;
			nSM::jServerInfo& siZone = nSM::g_jSMA->m_ServerInfo[_jW(eZONE)];
			if(!siZone.m_Data.count(_jW(pid))) break;
			if(si.m_Data[_jW(pid)] != siZone.m_Data[_jW(pid)]) break;

			siZone.m_eServerState=jS(eSS_Offline);
			send_A2M_CALL_CMD_RS(_T("server_kill eZONE"));
		}
		isRet=true;
	}
	return isRet;
}

void JOB_check_killed_eServerType(nEVENT::jIMessage* pM)
{
	if( check_process_killed(pM->GetArg(0)->Get_cstr()) )
	{
		nSM::jServerInfo* pSI = (nSM::jServerInfo*)pM->GetArg(1)->GetUserData();
		pM->Erase();
		assert(pM == pSI->m_pM_JOB_check_process_killed);
		pSI->m_pM_JOB_check_process_killed=0;
	}
}

void server_kill(tcstr server_type,int delay=0)
{
	server_kill_or_run(server_type, true, delay);
	jRETURN(g_jSMA->m_ServerInfo.count(jW(server_type)));
	nSM::jServerInfo* pSI = &g_jSMA->m_ServerInfo[_jW(eVAL)];
	
	jBE();

	if(pSI->m_pM_JOB_check_process_killed) 
		pSI->m_pM_JOB_check_process_killed->Erase();

	nEVENT::jIMessage* pM = pBE->m_pMM->Regist_TimeBaseAndCount(0,jFUNC_Msg(JOB_check_killed_eServerType),2,fTIMEPULS_CHECK_KILL_FAST,iMAX_CHECK_KILL_FAST);
	pM->GetArg(0)->Set_cstr(server_type);
	pM->GetArg(1)->SetUserData(pSI);
	pSI->m_pM_JOB_check_process_killed=pM;
	pM->DoWakeUp();
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,server_kill,0,"kill mythology server","<eLOGIN | eZONE | ePBRMS | eCHAT | all>")
{
#define jCONSOLE_PARAM_server_kill(X,Y) X(server_type,tcstr)
	jCONSOLE_PARAM_END(server_kill);
	bool isall=false;
	if(tstring(server_type) == jS(all)) isall=true;

	if(isall)
	{
		jLAMDA_for_each0(__server_kill,jIE*)
		{
			server_kill(it->GetTagName() , 2000);
		}
		jLAMDA_end();
		for_each_ServerExeList(__server_kill());
	}
	else
	{
		server_kill(server_type);
	}

	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,server_start,0,"start mythology server","<eLOGIN | eZONE | ePBRMS | eCHAT | all>")
{
#define jCONSOLE_PARAM_server_start(X,Y) X(server_type,tcstr)
	jCONSOLE_PARAM_END(server_start);
	bool isall=false;
	if(tstring(server_type) == jS(all)) isall=true;

	if(isall)
	{
		jLAMDA_for_each0(__server_start,jIE*)
		{
			server_kill_or_run( it->GetTagName() , false, 2000);
		}
		jLAMDA_end();
		
		for_each_ServerExeList(__server_start());
	}
	else
	{
		server_kill_or_run(server_type, false, 0);
	}
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,SendMenuCmd,0,"start mythology server"
				  ,"<eLOGIN | eZONE | all> <eSS_StartUp | eSS_Accept | eSS_SOS | eSS_DisAccept | eSS_DisUser | eSS_ShutDown >")
{
	jRETURN_ret(true,g_jSMA);

#define jCONSOLE_PARAM_SendMenuCmd(X,Y) X(server_type,tcstr) X(server_cmd,tcstr)
	jCONSOLE_PARAM_END(SendMenuCmd);

	bool isLOGIN=false;
	bool isZONE=false;
	if(jt_strstr(server_type,jS(eLOGIN))) isLOGIN=true;
	if(jt_strstr(server_type,jS(eZONE))) isZONE=true;
	if(jt_strcmp(server_type,jS(all)) ==0)
	{
		isLOGIN=true;
		isZONE=true;
	}

	if(isLOGIN) jSendToServer(_jW(eLOGIN),nSM::eA2S_SERVER_MENU_CMD_RQ,jW(server_cmd) );
	if(isZONE)	jSendToServer(_jW(eZONE),nSM::eA2S_SERVER_MENU_CMD_RQ,jW(server_cmd) );
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,Cmd_SS,0,"start mythology server"
				  ,"<server_type=all,eLOGIN,eZONE,ePBRMS> <cmd> [arg1] [arg2] [arg3] [arg4]")
{
	jRETURN_ret(true,g_jSMA);
	#define jCONSOLE_PARAM_Send_Cmd_To_Mythology(X,Y) X(server_type,tcstr) X(cmd,wcstr) Y(arg1,wcstr,L"") Y(arg2,wcstr,L"") Y(arg3,wcstr,L"") Y(arg4,wcstr,L"")
	jCONSOLE_PARAM_END(Send_Cmd_To_Mythology);
#if 0
	bool isall = tstring(server_type)==jS(all) ? true :false;

	if(isall)
	{
		#define jLAMDA_Cmd_SS_all(X,Z) X(wcstr,server_type) X(wcstr,cmd) X(wcstr,arg1) X(wcstr,arg2) X(wcstr,arg3) Z(wcstr,arg4)
		jLAMDA_for_each(Cmd_SS_all,jIE*)
		{
			jSendToServer(jW(server_type) , nSM::eA2SS_CMD , L"%s#%s#%s#%s#%s" , cmd,arg1,arg2,arg3,arg4 );
		}
		jLAMDA_end();

		for_each_ServerExeList(Cmd_SS_all(server_type, cmd, arg1,arg2,arg3,arg4));
	}
	else
	{
		jSendToServer(jW(server_type) , nSM::eA2SS_CMD , L"%s#%s#%s#%s#%s" , cmd,arg1,arg2,arg3,arg4 );
	}
#endif
	return true;
}

