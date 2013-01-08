/* file : Cmd_Dummy.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-27 16:19:23
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TPlayer.h"



void JOB_ConsoleCmd(nEVENT::jIMessage*pMsg)
{
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(pMsg->GetArg(0)->Get_cstr());
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,curr_dummy,0,"현제 더미지정","<szID>")
{
#define jCONSOLE_PARAM_curr_dummy(X,Y) 	X(szID,tcstr)
	jCONSOLE_PARAM_END(curr_dummy);

	g_pCurrUser = g_PL.find(szID);
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
jCONSOLE_CMD_AUTO(jSERVER_NAME,login,0,"로긴테스트","<127.0.0.1:3002> <id> <pwd> [world_sid=1]")
{
#define jCONSOLE_PARAM_login(X,Y) X(ip,tcstr) X(id,wcstr) X(pwd,acstr) Y(world_sid,int,1)
	jCONSOLE_PARAM_END(login);

	g_default_world_sid = world_sid;
	jPC_ret(false);
	jPlayerObj* pPlayer = g_PL.Start_Login(id);
	jRETURN_ret(false,pPlayer);
	ja_strcpy(pPlayer->m_szPWD , pwd);

	fname_t buf;
	jt_sprintf(buf, _T("dummy:%s"),jT(id));
	nCONSOLE::Get_jIConsoleCmd()->Run(jS(con), jS(message), buf, true,false);
	g_pCurrUser = pPlayer;
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,world_lists,0,"현제 월드리스트","")
{
	for(size_t i =0; i < g_PL.m_world_list.size(); ++i)
	{
		jWorldServerInfo& w = g_PL.m_world_list[i];
		fname_t buf;
		jLOG1(_T("world_sid:%d %s"), ToString(&w,buf));
	}
	return true;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,login_all,0,"login dummys","<per_user> <delay_msec>")
{
#define jCONSOLE_PARAM_login_all(X,Y) X(per_user,int)	X(delay_msec,int)
	jCONSOLE_PARAM_END(login_all);

	jPC_ret(false);
	g_PL.Start_Login_AllDummy(per_user , delay_msec);
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,logout,0,"logout test account ","<szID>")
{
	jPC_ret(false);
	jPlayerObj* pPlayer = g_PL.find(arg[0].c_str());
	if(!pPlayer) return false;
	pPlayer->StopSocket_ALL(true);
	if(g_pCurrUser==pPlayer)
		g_pCurrUser=0;
	pPlayer=0;
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,logout_all,0,"logout  all test account ","<per_user> [delay_msec=1]")
{
	jPC_ret(false);
	int per_user = jt_atoi(arg[0].c_str());
	DWORD delay = 1;
	if(arg.size()>1)
		delay = jt_atoi(arg[1].c_str());

	g_PL.Logout_Dummy_AllSocket(per_user,delay);
	g_pCurrUser=0;
	return true;
}

DWORD g_m_millisec=0;

void  JOB_DummyChat(nEVENT::jIMessage* pMsg)
{
	jPC();
	static int s_i=0;
	++s_i;
	wname256_t szChat;
	jw_sprintf(szChat, L"test chat %d", s_i);
	nswb1024_t buf;

	#define jLAMDA_send_echo(X,Z) Z(tcstr,szChat)
	jLAMDA_for_each(send_echo,jPlayerBase*)
	{
		jPlayerObj* pPlayer = (jPlayerObj*)it;
		pPlayer->Send_ECHO(szChat,g_m_millisec);
	}
	jLAMDA_end();

	try
	{
		g_PL.for_each(send_echo(szChat));
	}
	catch (...)
	{
		pMsg->Erase();
		g_PL.m_pMsg_Chat=0;
	}
}

bool g_chat_roop_quit=false;
void Do_Test_Chat_Loop_Quit()
{
	jPC();
	if(!g_PL.m_pMsg_Chat) return;
	g_PL.m_pMsg_Chat->Erase();
	g_PL.m_pMsg_Chat=0;
	g_chat_roop_quit=true;

}
void Do_Test_Chat_Loop_Start()
{
	jPC();
	g_chat_roop_quit=false;
	if(!g_PL.m_pMsg_Chat)
	{
		g_PL.m_pMsg_Chat = g_PL.m_pMM->Regist_Loop(0,JOB_DummyChat,0,true);
		g_PL.m_pMsg_Chat->DoWakeUp();
	}

}


jCONSOLE_CMD_AUTO(jSERVER_NAME,chat,0,"dummy chat start/end","<start | end> [start_delay_msec=1000]")
{
	jPC_ret(false);
	if(arg[0]==jS(start))
	{
		DWORD delay  = 1000;
		if(arg.size()>=2)
			delay = abs(jt_atoi(arg[1].c_str() ) );
#ifdef jUSE_CORE_MM_THREAD
		g_PL.m_pMM_ConsoleCmd->StartThread( delay );
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
		g_PL.m_pMM_ConsoleCmd->StopThread();
#else
		Do_Test_Chat_Loop_Quit();
#endif
		return true;
	}

	return false;
}



