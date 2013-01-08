/* file : PlugIn_Connect.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TPlayer.h"


int Get_CURR_USER()
{
	return 0;
}


jSQ_REGIST_BIND(PlugIn_Connect)
{
	jSQ_Interface(PlugIn_Connect)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}


jPLUGIN_CPP_CODE_START_Connect(PlugIn_Connect)
{
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message"),_T("tcp_mode"),true );
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message_txt"),_T("\"default : to test server\n\r* chat : to game server\""),true );
	g_PL.Init();

}
jPLUGIN_CPP_CODE_STOP(PlugIn_Connect);
{
	
}
jPLUGIN_CPP_CODE_END_Connect(PlugIn_Connect);


PlugIn_Connect::PlugIn_Connect()
{
}

bool PlugIn_Connect::ParseCmd(tcstr szCommand)
{
	nswb256_t buf;
	if(g_pCurrUser && szCommand[0]=='*')
	{
		g_pCurrUser->Send_ECHO(jW(szCommand+1),0);
		return false;
	}
	jNET_SEND2(g_SG.m_Dummy , DT_ECHO , szCommand,0);
	return false;
}


VOID PlugIn_Connect::OnIoConnected(jIPacketSocket_IOCP* pS)
{
	jInit_PlugIn_Connect_OnIoConnected();
}

VOID PlugIn_Connect::OnIoDisconnected(jIPacketSocket_IOCP* pS)
{
	jInit_PlugIn_Connect_OnIoDisconnected();

	jPlayerObj* pPlayer = ToPlayerObj(pS);
	if(pPlayer)
	{
		pS->Get_jIE()->SetUserData(jS(jPlayerObj), 0);
	}
}

