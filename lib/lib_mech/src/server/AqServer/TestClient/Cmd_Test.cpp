/* file : Cmd_Dummy.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-27 16:19:23
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "../AqCommon/AqCommon.h"
#include "PlugIn_ToBackEnd.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>



void JOB_ConsoleCmd(nEVENT::jIMessage*pMsg)
{
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(pMsg->GetArg(0)->Get_cstr());
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,curr_dummy,0,"현제 더미지정","<szID>")
{
#define jCONSOLE_PARAM_curr_dummy(X,Y) 	X(szID,acstr)
	jCONSOLE_PARAM_END(curr_dummy);

	jBE_ret(false);

	g_pCurrUser = pBE->FindDummyUser(szID);
	fname_t buf;
	if(g_pCurrUser)
	{
		jt_sprintf(buf, _T("@con.message dummy:%s"),arg[0].c_str());
		nCONSOLE::Get_jIConsoleCmd()->ParseCmd(buf);
		return true;
	}

	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(_T("@con.message dummy:NULL"));
	return false;
}

int g_default_world_sid=1;
jCONSOLE_CMD_AUTO(jSERVER_NAME,login,0,"로긴테스트","<127.0.0.1:33100> <id> <pwd> [world_sid=1]")
{
#define jCONSOLE_PARAM_login(X,Y) X(ip,tcstr) X(id,acstr) X(pwd,acstr) Y(world_sid,int,1)
	jCONSOLE_PARAM_END(login);

	g_default_world_sid = world_sid;
	jBE_ret(false);
	jDummyPlayer* pUser = pBE->CreateDummyUser(id);
	if(!pUser)
	{
		GetjILog()->Warning(_T("중복접속 : %s"),id);
		return true;

	}
	nXML::jE e_login = pUser->Get_jE_Login();
	assert(e_login.full());
	e_login->Set_cstr(ip);
	ja_strcpy(pUser->m_szPWD , pwd);
	ja_strcpy(pUser->m_szID , id);
	pUser->StartSocket_Login(pBE->m_pClientSession);
	fname_t buf;
	jt_sprintf(buf, _T("dummy:%s"),jT(id));
	nCONSOLE::Get_jIConsoleCmd()->Run(jS(con), jS(message), buf, true,false);
	g_pCurrUser = pUser;
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,world_lists,0,"현제 월드리스트","")
{
	for(int i =0; i < g_world_list.size(); ++i)
	{
		jWorldServerInfo& w = g_world_list[i];
		fname_t buf;
		GetjILog()->Log(_T("world_sid:%d %s"), ToString(&w,buf));
	}
	return true;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,login_all,0,"login dummys","<per_user> <delay_msec>")
{
#define jCONSOLE_PARAM_login_all(X,Y) X(per_user,int)	X(delay_msec,int)
	jCONSOLE_PARAM_END(login_all);

	jBE_ret(false);
	pBE->ConnectToLoginServer_AllDummy(per_user , delay_msec);
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,logout,0,"logout test account ","<szID>")
{
	jBE_ret(false);
	jDummyPlayer* pUser = pBE->FindDummyUser(jA(arg[0]));
	if(!pUser) return false;
	pUser->StopSocket_ALL(true);
	if(g_pCurrUser==pUser)
		g_pCurrUser=0;
	pUser=0;
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,logout_all,0,"logout  all test account ","<per_user> [delay_msec=1]")
{
	jBE_ret(false);
	int per_user = jt_atoi(arg[0].c_str());
	DWORD delay = 1;
	if(arg.size()>1)
		delay = jt_atoi(arg[1].c_str());

	pBE->Logout_Dummy_AllSocket(per_user,delay);
	g_pCurrUser=0;
	return true;
}

bool g_isstop_jMsgManager_worker = true;
DWORD g_m_millisec=0;

void  JOB_DummyChat(nEVENT::jIMessage* pMsg)
{
	jBE();
	static int s_i=0;
	++s_i;
	wname256_t szChat;
	jw_sprintf(szChat, L"test chat %d", s_i);
	nswb1024_t buf;

	nUtil::jCriticalSection::Auto a(&pBE->m_listDummy_CS);
	try
	{
		jFOR_EACH(pBE->m_listDummy , boost::bind(&jDummyPlayer::Send_ChatMsg, _1, szChat,g_m_millisec) );
	}
	catch (...)
	{
		pMsg->Erase();
		pBE->m_pMsg_Chat=0;
	}
}

bool g_chat_roop_quit=false;
void Do_Test_Chat_Loop_Quit()
{
	jBE();
	if(!pBE->m_pMsg_Chat) return;
	pBE->m_pMsg_Chat->Erase();
	pBE->m_pMsg_Chat=0;
	g_chat_roop_quit=true;

}
void Do_Test_Chat_Loop_Start()
{
	jBE();
	g_chat_roop_quit=false;
	if(!pBE->m_pMsg_Chat)
	{
		pBE->m_pMsg_Chat = pBE->m_pMM->Regist_Loop(0,JOB_DummyChat,0,true);
		pBE->m_pMsg_Chat->DoWakeUp();
	}

}


jCONSOLE_CMD_AUTO(jSERVER_NAME,chat,0,"dummy chat start/end","<start | end> [start_delay_msec=1000]")
{
	jBE_ret(false);
	if(arg[0]==jS(start))
	{
		DWORD delay  = 1000;
		if(arg.size()>=2)
			delay = abs(jt_atoi(arg[1].c_str() ) );
#ifdef jUSE_CORE_MM_THREAD
		pBE->m_pMM_ConsoleCmd->StartThread( delay );
#else
		extern DWORD g_m_millisec;
		g_m_millisec = delay;

		Do_Test_Chat_Loop_Start();
#endif
		return true;
	}
	if(arg[0]==jS(end))
	{
#ifdef jUSE_CORE_MM_THREAD
		pBE->m_pMM_ConsoleCmd->StopThread();
#else
		Do_Test_Chat_Loop_Quit();
#endif
		return true;
	}

	return false;
}



