/* file : jPlayerList_Dummy.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-11-05 16:27:41
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "TPlayer.h"
#include "jPlayerList_Dummy.h"

jPlayerList_Dummy g_PL;
// 접속해제

void jPlayerList_Dummy::Init()
{
	g_SG.m_MyInfo.m_sid=9999;
	m_pMM = nEVENT::jIMsgManager::Get(jS(jPlayerList_Dummy), true);
	m_pMsg_Chat=0;
	m_isEnable=false;
	
	jt_strcpy_s(m_si_Login.m_szServiceIP , pv_DefaultLoginIP->Get_cstr());
	m_si_Login.m_service_port = (uint16)pv_DefaultLoginPort->Get_int();
	m_si_Login.m_eType = eLogin;
}

void jPlayerList_Dummy::Close()
{
	if(m_pMM){m_pMM->clear();m_pMM=0;}
	m_isEnable=false;
	Logout_Dummy_AllSocket(1000,0);

}

void jPlayerList_Dummy::Logout_Dummy_AllSocket(int per_user , DWORD delay )
{
	#define jLAMDA_logout_dummy_all(X,Z) X(int,per_user) X(DWORD,delay) Z(int&,iCount)
	jLAMDA_for_each(logout_dummy_all,jPlayerBase*)
	{
		jPlayerObj* p = (jPlayerObj*)it;

		p->StopSocket_ALL(true);
		if(iCount > per_user && delay)	
		{
			iCount=0;
			Sleep(delay);
		}
		++iCount;
	}
	jLAMDA_end();

	int iCount=0;
	this->for_each(logout_dummy_all(per_user,delay,iCount));

}


jIPacketSocket_IOCP* jPlayerList_Dummy::GetUserSocket(player_name_ct szID , EServerType eType, jPlayerObj** ppDummy)
{
	jPlayerObj* pPlayer = find(szID);
	jRETURN_ret(0,pPlayer);
	*ppDummy = pPlayer;
	jRETURN_ret(0,eType >= eEND_EServerTypeFrontEnd);
	jRETURN_ret(0,pPlayer->m_pGrid[eType]);
	return pPlayer->m_pGrid[eType]->m_pS;
}
bool jPlayerList_Dummy::RunDummyFunction(tcstr szID, tr1::function<void (jPlayerBase* pPlayer,DWORD delay_msec)> func ,DWORD delay_msec)
{
	if(!jt_strcmp(szID,jS(all)))
	{
		this->for_each(tr1::bind(func, tr1::placeholders::_1 , delay_msec));
	}
	else
	{
		g_pCurrUser = find(jW(szID));
		jvRETURN_ret(false,g_pCurrUser,_T("id =%s is not found"),szID);
		func(g_pCurrUser, 0);
	}
	return true;
}


// Init_DummySocket()로 초기화 된 정보를 이용해 접속시도
bool g_isCancel_StartSession_AllDummy=false;
void jPlayerList_Dummy::Start_Login_AllDummy(int per_user ,int delay_msec)
{
	fname_t buf;
	wfname_t szID;
	g_isCancel_StartSession_AllDummy=false;
	int i=0;
	for(int ii =0 ; ii< pv_DummyCount->Get_int();++ii,++i)
	{
		if(g_isCancel_StartSession_AllDummy) 
		{
			return;
		}
		jw_sprintf(szID, L"test%d",GetDummyID()*1000+ii);
		jCONTINUE(this->Start_Login(szID));
		jDELAY(i);
	}
	jt_sprintf(buf, _T("@con.message dummy:%s"),jT(szID) );
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(buf);
}


jPlayerObj* jPlayerList_Dummy::Start_Login(player_name_ct szID,acstr szPWD)
{
	jRETURN_ret(0,!this->find(szID));

	jPlayerObj* pPlayer= (jPlayerObj*)create_Dummy(szID);
	jRETURN_ret(0,pPlayer);
	ja_strcpy_s(pPlayer->m_szPWD , szPWD);

	jIPacketSocket_IOCP* pS= g_SG.Do_SERVER_ONLINE_ACTION(m_si_Login,szID);
	jRETURN_ret(0,pS);
	pS->Get_jIE()->SetUserData(jS(jPlayerObj),pPlayer);
	return pPlayer;
}


