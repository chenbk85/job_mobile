/* file : jNetClient.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-17 22:33:42
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jNetClient.h"
#include "base/jTimeHelper.h"

jNetClient g_jNetClient;
jNetClient *g_pNetClient=&g_jNetClient;

void jNetClient::SendToTown(jPacket_Base* pP)
{
}

bool jNetClient::CallBack(tcstr name, jINetClient_arg)
{
	if(m_isDummyMode) return false;
	jINetClient_Receiver* pAO = (jINetClient_Receiver*)jBase::FindNamedPointer(jS(jINetClient),name);
	if(!pAO) return false;
	pAO->Call(pUser,pS,_pData);
	return true;
}

bool jNetClient::console_parsor(TCHAR* sz)
{
	return nCONSOLE::Get_jIConsoleCmd()->ParseCmd(sz);
}

void jNetClient::Send_X2L_USER_LOGIN(const char* world,const char* id, vector<nMech::uint8> &pwd)
{
	/*
	nswb1024_t buf;
	ja_strcpy(g_pCurrUser->m_szID, id);
	g_pCurrUser->Write_Packet_Login(WRITE_X2L_USER_LOGIN(buf, world,id,pwd,"ver", "cpp_ver"));
	*/
}

jPlayer* jNetClient::GetPlayer()
{
	return 0;
}


void jNetClient::NetworkStart()
{
	/*
	jBE();
	g_pCurrUser = pBE->CreateDummyUser("Player");
	jASSERT0(g_pCurrUser);
	nXML::jE e_login = g_pCurrUser->Get_jE_Login();
	assert(e_login.full());
	e_login->Set_cstr(pv_DEFAULT_LOGIN_IP->Get_cstr());
	ja_strcpy(g_pCurrUser->m_szPWD , "");
	ja_strcpy(g_pCurrUser->m_szID , "");
	g_pCurrUser->StartSocket_Login(pBE->m_pClientSession);
	*/
}

void jNetClient::NetworkEnd()
{
	exit (0);
}

void jNetClient::SetServerTime(time_t t)
{
	m_CurrServerTime = t;
	jTimeHelper th;
	th.Get_curr_time();
	m_CurrClientTime = th.m_t;
}

time_t jNetClient::GetServerTime()
{
	jTimeHelper th;
	th.Get_curr_time();
	return m_CurrServerTime + ( th.m_t - m_CurrClientTime);
}

cstr jNetClient::GetLeftTime(IN time_t server_end_time, OUT fname_t buf)
{
	jTimeHelper th;
	th.m_t = GetServerTime();
	th.Get_diff_day_string(server_end_time,buf);
	return buf;
}

nEVENT::jIMsgManager* jNetClient::Get_MM(){	jBE_ret(0);return pBE->m_pMM;}