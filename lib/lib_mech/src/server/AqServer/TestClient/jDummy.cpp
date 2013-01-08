/* file : jDummy.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-27 13:41:44
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jDummy.h"
#include "PlugIn_ToBackEnd.h"


jDEFINE_YVECTOR_MANAGER(jDummyPlayer, 100,5);

jDummyPlayer *g_pCurrUser=0;

#define  _StopStartSocket(name,idStart,TAG)\
void jDummyPlayer::StopSocket_##name(jINetSession_Service* pSS,bool isRelease)\
{\
	if(!GetSocket_##name()) return;\
	assert(Get_jE_##name().full());\
	pSS->Stop_ClientSocket(Get_jE_##name(),isRelease);\
	SetSocket_##name(0);\
};\
jIPacketSocket_IOCP* jDummyPlayer::StartSocket_##name(jINetSession_Service* pSS)\
{\
	if(GetSocket_##name())\
	{\
		StopSocket_##name(pSS,true);\
	}\
	Get_jE_##name().Attr(jS(ENABLE)).T()=true;\
	jIPacketSocket_IOCP* pS= pSS->Start_ClientSocket(Get_jE_##name());\
	Get_jE_##name().Attr(jS(ENABLE)).T()=false;\
	SetSocket_##name(pS);\
	if(!pS)\
	{\
		/*Get_jE_##name()->DebugPrint(true);*/ \
		GetjILog()->Warning(_T("접속 실패 : %s"),Get_jE_##name()->Get_cstr());\
		return 0;\
	}\
	pS->Get_jIE()->SetUserData(jS(jDummyPlayer), this);\
	return pS;\
}\

for_each_SERVER_TYPE_F(_StopStartSocket);

void jDummyPlayer::StopSocket_ALL(bool isRelease)
{
	jBE();
	if(!pBE) return;
#define  _Stop_ClientSocket_ALL(name,idStart,TAG) StopSocket_##name(pBE->m_pClientSession,isRelease);
	for_each_SERVER_TYPE_F(_Stop_ClientSocket_ALL);
	if(	g_pCurrUser == this)
		g_pCurrUser = 0;
}

void jDummyPlayer::Send_ChatMsg(wcstr szMsg,DWORD delay)
{
	nswb1024_t buf;
	wname256_t szChatBuf;
	jw_sprintf(szChatBuf, L"%s : %s",jW(m_szID), szMsg);
	if(IsTownPlayer())
	{
		if(GetSocket_Town())
			GetSocket_Town()->WritePacket(&WRITE_T_ECHO(buf, jT(szChatBuf),0));
	}
	else if(IsDungeonPlayer())
	{
		if(GetSocket_Dungeon())
			GetSocket_Dungeon()->WritePacket(&WRITE_D_ECHO(buf,jT(szChatBuf) ,0));
	}
	else if(m_EGamePlayerState== eGPS_LOGINSERVER_CONNECTED)
	{
		if(GetSocket_Login())
		{
			GetSocket_Login()->WritePacket(&nLoginServer::WRITE_L_ECHO(buf, 0,jT(szMsg)) );
		}
	}
	extern bool g_chat_roop_quit;
	if(g_chat_roop_quit)
		throw false;
	if(delay)
		Sleep(delay);
}


void jDummyPlayer::InitUdp(tcstr szIP,jIPacketSocket_IOCP* pS)
{
	name_t bufIP;
	m_Udp_VirtualAddr = nInterface::g_pjINet_OGS->GetUtil()->String2Addr(pS->GetIP(bufIP),pS->GetPort());
	m_Udp_ServerIP = nInterface::g_pjINet_OGS->GetUtil()->String2Addr(szIP);
	name_t buf;
	GetjILog()->Log(jFUNC1 _T("udp server ip : %s") , nInterface::g_pjINet_OGS->GetUtil()->Addr2String(m_Udp_ServerIP, buf) );
}


tcstr ToString(jDummyPlayer* v, tname1024_t buf)
{
	jt_sprintf(buf, _T("%s(%I64d) : %s , L=%d,T=%d,D=%d")
		,jT(v->m_szID)
		,v->Get_uid()
		,v->GetString_EGamePlayerState()
		,(bool)v->GetSocket_Login()
		,(bool)v->GetSocket_Town()
		,(bool)v->GetSocket_Dungeon()
		);
	return buf;
}

void jDummyPlayer::Init()
{
	Create();
	m_EGamePlayerState = eGPS_NOT_LOGIN;
}

nAQ::Use_Town* jDummyPlayer::Get_Use_Town(Use_Town_id_t tuid)
{
	for(int i = 0; i<Town_size();++i)
	{
		if( Town()[i].Get_tuid()==tuid) 
			return &Town()[i];
	}
	return 0;
}


void jDummyPlayer::Change_CurrTown(townid_t tid,bool isSendToServer)
{
	if(tid <1 || tid > Town().size()) return;
	m_iCurrTown = tid;
	m_eCurrTown = g_jAqCommon.FindTownBYTUID(m_eUser_file_db , Town_at(tid)->Get_tuid() );
	if(m_eCurrTown.empty())
	{
		m_eUser_file_db->DebugPrint(true);
		GetjILog()->Warning(jFUNC1 _T("town id:%d tuid:%I64d"),tid,Town_at(tid)->Get_tuid().m_db_id);
		return;
	}
	if(isSendToServer)
	{
		nswb256_t buf;
		Write_Packet_Town(WRITE_X2T_TOWN_SELECT(buf,tid ));
	}
}

