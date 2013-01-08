/* file : PlugIn_ToBackEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"
#include "PlugIn_ToBackEnd.h"

PlugIn_ToBackEnd* g_pCurrPlugIn=0;


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
}

/*
extern bool g_isstop_jMsgManager_worker;
DWORD WINAPI	_jMsgManager_worker(LPVOID p)
{
	nEVENT::jIMsgManager* pMM = (nEVENT::jIMsgManager*)p;
	//for( ; pMM->m_isThreadExit==false ; )
	while( !g_isstop_jMsgManager_worker)
	{
		pMM->Run();
		//if(g_m_millisec)Sleep(g_m_millisec);
	}
	//_endthreadex( 0 );
	return 0;
} 
*/


jPLUGIN_BACK_END_cpp_code_Start(PlugIn_ToBackEnd)
{
	m_pS_TestServer=0;
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message"),_T("tcp_mode"),true ,0);
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message_txt"),_T("\"default : to test server\n\r* chat : to game server\""),true ,0);

}
jPLUGIN_cpp_code_Stop(PlugIn_ToBackEnd);
{
	if(g_pCurrPlugIn==this)
		g_pCurrPlugIn=0;

}
jPLUGIN_BACK_END_cpp_code_End(PlugIn_ToBackEnd);


bool PlugIn_ToBackEnd::ParseCmd(tcstr szCommand)
{
	nswb256_t buf;

	if(!m_pS_TestServer)
		m_pS_TestServer = m_pClientSession->Get_ClientSocket(jS(TCP_TestServer));
	//jASSERT0(m_pS_TestServer);
	if(!m_pS_TestServer || !m_pS_TestServer->IsConnected())
	{
		jWARN(_T("소켓 연결이 안되었음"));
		return false;
	}

	using namespace nNET::nTestServer;
	jNET_SEND(m_pS_TestServer,S_ECHO,0,jW(szCommand));
	jNET_SEND(m_pS_TestServer,X2S_THREAD_TEST1,0,jW(szCommand));
	jNET_SEND(m_pS_TestServer,X2S_THREAD_TEST2,0,jW(szCommand));

	return false;
}


// Init_DummySocket()로 초기화 된 정보를 이용해 접속시도
bool g_isCancel_StartSession_AllDummy=false;

VOID PlugIn_ToBackEnd::OnIoConnected(jIPacketSocket_IOCP* pS)
{
	//jFD1();
	m_pS_TestServer = pS;
	m_Users[pS->Get_jIE()].m_pS = pS;

/*
	if(pS->Get_jIE()->IsName(jS(TCP_TestServer)))
	{
		m_pS_TestServer = pS;
	}
	else
	{
		if(!m_pS_TestServer)
			m_pS_TestServer = m_pClientSession->Get_ClientSocket(jS(TCP_TestServer));

	}
*/
	jLOG(_T("OnIoConnected(%s) ") , pS->Get_jIE()->GetTagName());
}

VOID PlugIn_ToBackEnd::OnIoDisconnected(jIPacketSocket_IOCP* pS)
{
	if(pS->Get_jIE()->IsName(jS(TCP_TestServer)))
	{
		jLOG(_T("OnIoDisconnected (%s) ") , pS->Get_jIE()->GetTagName());
		m_pS_TestServer = 0;
		return;
	}

	jAUTO_LOCK_CS(m_Users_CS);
	m_Users.erase(pS->Get_jIE());

	jLOG(_T("OnIoDisconnected (%s) pUser==NULL") , pS->Get_jIE()->GetTagName());
	return;
}

