/* file : PlugIn_ToBackEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqMonitor.h"
#include "PlugIn_ToBackEnd.h"

PlugIn_ToBackEnd *g_pCurrPlugInBE=0;

int Get_CURR_USER(){return 0;}

jPLUGIN_BACK_END_cpp_code_Start(PlugIn_ToBackEnd)
{
	g_pCurrPlugIn = this;
}
jPLUGIN_cpp_code_Stop(PlugIn_ToBackEnd);
{
	m_pToCentral=0;
	m_pToTestServer=0;
	if(g_pCurrPlugInBE==this)
		g_pCurrPlugInBE=0;
	if(g_pCurrPlugIn==this)
		g_pCurrPlugIn=0;

}
jPLUGIN_BACK_END_cpp_code_End(PlugIn_ToBackEnd);

PlugIn_ToBackEnd::PlugIn_ToBackEnd()
{
	m_pToCentral=0;
	m_pToTestServer=0;
}


//DECLARE_INSTANCE_TYPE(S_TA_SET_TEST_ENV);
jSQ_REGIST_BIND(PLUGIN)
//jSQ_REGIST_BIND_jINetPlugIn_CLIENT(PlugIn_ToBackEnd)
{
	jSQ_Interface(PlugIn_ToBackEnd)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}

bool PlugIn_ToBackEnd::ParseCmd(tcstr szCommand)
{
	if(!m_pToCentral && !m_pToTestServer) return false;
	net_string256 sendS;
	jt_sprintf(sendS ,_T("AqMonitor:%s>%s") , g_ExeEnv.m_szComputerName,szCommand);

	nswb1024_t sendBuf;
	if(m_pToTestServer)
	{
		m_pToTestServer->WritePacket(&nTestServer::WRITE_TS_ECHO(sendBuf,0,sendS));
	}
	return false;
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
		else if(pS->Get_jIE()->IsName(jS(ToTestServer)))
		{
			m_pToTestServer= pS;
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
		}
	}

}
