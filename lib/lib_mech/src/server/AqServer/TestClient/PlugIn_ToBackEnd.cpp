/* file : PlugIn_ToBackEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"
#include "PlugIn_ToBackEnd.h"

#include <boost/bind.hpp>

PlugIn_ToBackEnd* g_pCurrPlugIn=0;

int Get_CURR_USER()
{
	return g_pCurrPlugIn->m_listDummy.size();
}


jSQ_REGIST_BIND(PLUGIN)
{
	jSQ_Interface(PlugIn_ToBackEnd)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}


// 접속해제
void PlugIn_ToBackEnd::Logout_Dummy_AllSocket(int per_user , DWORD delay )
{
	nXML::jE e = m_pE;
	nUtil::jCriticalSection::Auto a(&m_listDummy_CS);
	//jFOR_EACH(m_listDummy, boost::bind(&jDummyPlayer::StopSocket_ALL, _1,delay) );
	m_listDummy_it it = m_listDummy.begin() , ie = m_listDummy.end();
	for(int i=0;it!=ie; ++it,++i)
	{
		jDummyPlayer& p = *it;
		p.StopSocket_ALL(true);
		if(i> per_user && delay)	
		{
			i = 0;
			Sleep(delay);
		}
	}

}

jDummyPlayer* PlugIn_ToBackEnd::GetDummyUser(jIPacketSocket_IOCP* pS)
{
	return (jDummyPlayer*)pS->Get_jIE()->GetUserData(jS(jDummyPlayer));
}


jIPacketSocket_IOCP* PlugIn_ToBackEnd::GetUserSocket(acstr szID , jServerInfo::EServerType eType, jDummyPlayer** ppDummy)
{
	jDummyPlayer* pUser = FindDummyUser(szID);
	if(!pUser)
	{
		GetjILog()->Warning(_T("dummy not found : %s"), szID );
		return 0;
	}
	*ppDummy = pUser;

	jIPacketSocket_IOCP* pS =0;
#define _GetUserSocket_(name,idStart,TAG)\
	if(eType==jServerInfo::e##name)\
	{\
	pS = pUser->GetSocket_##name();\
	if(!pS)\
	{\
	GetjILog()->Warning(_T("pUser->GetSocket_%s == NULL"),#name);\
	return 0;\
	}\
	return pS;\
	}

	for_each_SERVER_TYPE_F(_GetUserSocket_);

	return 0;
}
bool PlugIn_ToBackEnd::RunDummyFunction(tcstr szID, boost::function<void (jDummyPlayer& pUser,DWORD delay_msec)> func ,DWORD delay_msec)
{
	if(!jt_strcmp(szID,jS(all)))
	{
		jFOR_EACH(m_listDummy , boost::bind(func, _1 , delay_msec));
	}
	else
	{
		g_pCurrUser = FindDummyUser(jA(szID));
		if(!g_pCurrUser) 
		{
			GetjILog()->Warning(_T("id =%s is not found"),szID);
			return false;
		}
		func(*g_pCurrUser, 0);
	}
	return true;
}


PlugIn_ToBackEnd::PlugIn_ToBackEnd()
{
	m_TS_HELLO.did=9888;
}

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


jPLUGIN_BACK_END_cpp_code_Start(PlugIn_ToBackEnd)
{
	m_pMM = nEVENT::jIMsgManager::Get(jS(PlugIn_ToBackEnd), true);\

	m_pMsg_Chat=0;

	g_isstop_jMsgManager_worker=false;
	DWORD	dwThreadID	= 0;
	m_hThread = CreateThread(NULL, 0, _jMsgManager_worker, (nEVENT::jIMsgManager*)m_pMM, NULL, &dwThreadID);

	g_pCurrPlugIn = this;
	m_isEnable=false;
	m_pS_TestServer=0;
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message"),_T("tcp_mode"),true );
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message_txt"),_T("\"default : to test server\n\r* chat : to game server\""),true );

	m_listDummy.clear();

}
jPLUGIN_cpp_code_Stop(PlugIn_ToBackEnd);
{
	g_isstop_jMsgManager_worker=true;

	if(m_pMM){m_pMM->clear();m_pMM=0;}

	m_isEnable=false;

	if(g_pCurrPlugIn==this)
		g_pCurrPlugIn=0;

	Logout_Dummy_AllSocket(1000,0);
	//m_pE->for_each(_jxClearAnyData());
	nUtil::jCriticalSection::Auto a(&m_listDummy_CS);
	m_listDummy.clear();
}
jPLUGIN_BACK_END_cpp_code_End(PlugIn_ToBackEnd);



bool PlugIn_ToBackEnd::ParseCmd(tcstr szCommand)
{
	nswb256_t buf;
	if(g_pCurrUser && szCommand[0]=='*')
	{
		g_pCurrUser->Send_ChatMsg(jW(szCommand+1),0);
		return false;
	}

	if(!m_pS_TestServer)
		m_pS_TestServer = m_pClientSession->Get_ClientSocket(jS(TCP_TestServer));
	jAssert0(m_pS_TestServer);
	if(!m_pS_TestServer->IsConnected())
	{
		GetjILog()->Warning(_T("소켓 연결이 안되었음"));
		return false;
	}
	m_pS_TestServer->WritePacket(&nTestServer::WRITE_TS_ECHO(buf, 0,szCommand));

	return false;
}


// Init_DummySocket()로 초기화 된 정보를 이용해 접속시도
bool g_isCancel_StartSession_AllDummy=false;
void PlugIn_ToBackEnd::ConnectToLoginServer_AllDummy(int per_user ,int delay_msec)
{
	int i=0;
	fname_t buf;
	afname_t szID;
	g_isCancel_StartSession_AllDummy=false;
	for(int ii =0 ; ii< pv_DummyCount->Get_int(); ++i,++ii)
	{
		if(g_isCancel_StartSession_AllDummy) 
		{
			return;
		}
		ja_sprintf(szID, ("test%d"),GetDummyID()*1000+ii);
#if 1
		jDummyPlayer* pUser = this->CreateDummyUser(szID);
		nXML::jE e_login = pUser->Get_jE_Login();
		assert(e_login.full());

		tfname_t szIP;
		jt_sprintf(szIP,_T("%s:%d"),pv_DefaultLoginIP->Get_cstr(),pv_DefaultLoginPort->Get_int());
		e_login->Set_cstr(szIP);
		ja_strcpy(pUser->m_szPWD , "0000");
		pUser->StartSocket_Login(this->m_pClientSession);
		g_pCurrUser = pUser;
#else
		fname_t szCmd;
		jt_sprintf(szCmd , _T("@test.login %s:%d %s 0000")
			,pv_DefaultLoginIP->->Get_cstr()
			,pv_DefaultLoginPort->Get_int()
			,szID
			);
		nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
#endif
		jDELAY()

	}
	jt_sprintf(buf, _T("@con.message dummy:%s"),jT(szID) );
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(buf);
}


jDummyPlayer* PlugIn_ToBackEnd::FindDummyUser(acstr szID)
{
	nUtil::jCriticalSection::Auto a(&m_listDummy_CS);
	m_listDummy_it it = m_listDummy.begin(), ie = m_listDummy.end();
	for(;it!=ie;++it)
	{
		if(ja_stricmp(it->m_szID, szID)) continue;
		return &(*it);
	}
	return 0;
}
jDummyPlayer* PlugIn_ToBackEnd::CreateDummyUser(acstr szID)
{
	//기존에 있으면 연결을 초기화하고 없으면 만든다.
	nXML::jE e = m_pE;
	fname_t szB;

#define  __CreateDummyUser_init(name,idStart,TAG)\
	jt_sprintf(szB,_T("TCP_%sServer"),_T(#name));\
	jIE* s_pe##name = m_pE->Find(szB);\
	fname_t sz##name;\
	jt_sprintf(sz##name,_T("TCP_%s_%s") , _T(#name), jT(szID));\
	nXML::jE e_##name = e[sz##name];\
	jIE* pe##name = e_##name;\

	for_each_SERVER_TYPE_F(__CreateDummyUser_init);


	jDummyPlayer* pUser = FindDummyUser(szID);
	//jGetType<jDummyPlayer>(e_Login->GetVar());

	if(pUser)// 기존 유저는 접속해제.
	{
		assert(!ja_stricmp(pUser->m_szID, szID));
		pUser->StopSocket_ALL(true);
		pUser->Init();
	}
	else
	{
		nUtil::jCriticalSection::Auto a(&m_listDummy_CS);
		pUser = m_listDummy.push_back();
	}

	ja_strcpy(pUser->m_szID, szID);

#define  __CreateDummyUser_copy_src(name,idStart,TAG)\
	s_pe##name->CopyTo(pe##name);\
	pe##name->ChangeTagName(sz##name);\
	e_##name.Attr(jS(ENABLE)).M() = true;\
	pe##name->SetUserData(jS(jDummyPlayer),pUser);\
	pUser->Set_jE_##name(e_##name);\

	for_each_SERVER_TYPE_F(__CreateDummyUser_copy_src);

	return pUser;

}

VOID PlugIn_ToBackEnd::OnIoConnected(jIPacketSocket_IOCP* pS)
{
	//jFD1();
	jDummyPlayer test;

	if(pS->Get_jIE()->IsName(jS(TCP_TestServer)))
	{
		m_pS_TestServer = pS;
	}
	else
	{
		if(g_pNetClient->m_isDummyMode && !m_pS_TestServer)
			m_pS_TestServer = m_pClientSession->Get_ClientSocket(jS(TCP_TestServer));

		if(jt_strstr(pS->Get_jIE()->GetTagName(),jS(Login)) )
		{
			jDummyPlayer* pUser = GetDummyUser(pS);
			if(pUser)
			{
				pUser->SetState(eGPS_LOGINSERVER_CONNECTED);
			}
		}
	}

	GetjILog()->Log(_T("OnIoConnected(%s) ") , pS->Get_jIE()->GetTagName());
}

VOID PlugIn_ToBackEnd::OnIoDisconnected(jIPacketSocket_IOCP* pS)
{
	if(pS->Get_jIE()->IsName(jS(TCP_TestServer)))
	{
		GetjILog()->Log(_T("OnIoDisconnected (%s) ") , pS->Get_jIE()->GetTagName());
		m_pS_TestServer = 0;
		return;
	}

	jDummyPlayer* pUser = GetDummyUser(pS);
	if(!pUser) 
	{
		GetjILog()->Warning(_T("OnIoDisconnected (%s) pUser==NULL") , pS->Get_jIE()->GetTagName());
		return;
	}
	pS->Get_jIE()->SetUserData(jS(jDummyPlayer), 0);
	GetjILog()->Log(_T("OnIoDisconnected %s(%s) ") , jT(pUser->m_szID) ,pS->Get_jIE()->GetTagName());
}

