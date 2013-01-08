/* file : Cmd_Dummy.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-27 16:19:23
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToBackEnd.h"
#include "base/jWindow_Util.h"



void JOB_ConsoleCmd(nEVENT::jIMessage*pMsg)
{
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(pMsg->GetArg(0)->Get_cstr());
}

// jCONSOLE_CMD_AUTO(jSERVER_NAME,login,0,"로긴테스트","<127.0.0.1:33100> <id> <pwd>")
// {
// #define jCONSOLE_PARAM_login(X,Y) X(ip,tcstr) X(id,acstr) X(pwd,acstr)
// 	jCONSOLE_PARAM_END(login);
// 	return true;
// }
// 

jCONSOLE_CMD_AUTO(jSERVER_NAME,reconnect,0,"reconnect to monitor","")
{
	PlugIn_ToBackEnd::Get();
	jBE_ret(true);
	if(pBE->m_pS_MonitorServer)
	{
		pBE->ResetReconnect();
		return true;
	}
	jRETURN_ret(true,pBE->m_pClientSession);

	jIE* pE = pBE->m_pE->Find(jS(TCP_MonitorServer));
	jRETURN_ret(true,pE);

	pBE->m_pClientSession->Start_ClientSocket(pE);
	nMech::print_memory(jFUNC);
	return true;
}
jCONSOLE_CMD_AUTO(jSERVER_NAME,kill_me,0,"kill agent (need! tool_command.exe)","[delay_time_sec]")
{
#define jCONSOLE_PARAM_kill_me(X,Y) Y(delay_time_sec,int,0)
	jCONSOLE_PARAM_END(kill_me);

	tname1024_t buf;
	jt_sprintf(buf, _T("tool_command.exe kill %u %d"),GetCurrentProcessId() , delay_time_sec );
	nFileSystem::jFolder dir;
	dir.Goto(g_ExeEnv.m_szModuleDir);
	nUtil::nWIN::jCreateProcess(buf,false);
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,restart,0,"restart agent (need! tool_command.exe)","")
{
	tname1024_t buf;
	jt_sprintf(buf, _T("tool_command.exe restart \"%s\" 10 %u %s")
		,(pv_reconnect_fail_action->Get_cstr()),GetCurrentProcessId()
		,(g_ExeEnv.m_szModuleDir));
	jt_printf(_T("GetCurrentProcessId()=%u, call-> %s"),GetCurrentProcessId(),buf);

	nFileSystem::jFolder dir;
	dir.Goto(g_ExeEnv.m_szModuleDir);
	nUtil::nWIN::jCreateProcess(buf,false);
	return true;
}
