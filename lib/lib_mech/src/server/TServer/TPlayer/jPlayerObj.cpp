/* file : TClientUser_L.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:42:03
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TPlayer.h"
#include "jPlayerObj.h"
#include "jPlayerList_Dummy.h"

jPlayerBase_CREATE(jPlayerObj, 1024,128)
{
	jPlayerServerData::_Create();
	jCLEAR(m_szID);
	m_pUdpSocket=0;
	m_eUser_file_db.clear();
	memset(m_pGrid, 0, sizeof(m_pGrid) );
	m_EGamePlayerState = eGPS_NOT_LOGIN;

}
jPlayerBase_DESTROY(jPlayerObj)
{
	if(m_eUser_file_db.full())
	{
		GetjIXml()->DeleteElement(m_eUser_file_db);
		m_eUser_file_db.clear();
	}
	m_EGamePlayerState = EGamePlayerState_END;
}


jPlayerObj *g_pCurrUser=0;

void jPlayerObj::StopSocket_ALL(bool isRelease)
{
	for(int i=0; i < eEND_EServerTypeFrontEnd; ++i)
	{
		jCONTINUE(m_pGrid[i]);
		jCONTINUE(m_pGrid[i]->m_pPlugIn);
		m_pGrid[i]->m_pPlugIn->DoDisconnect(m_pGrid[i]->m_pS);
	}
	if(	g_pCurrUser == this)g_pCurrUser = 0;
}

void jPlayerObj::Send_ECHO(wcstr szMsg,DWORD delay)
{
	nswb1024_t buf;
	wname256_t szChatBuf;
	jw_sprintf(szChatBuf, L"%s : %s",jW(m_szID), szMsg);
	if(m_pGrid[eChannel])
	{
		jNET_SEND(m_pGrid[eChannel],CH_ECHO, jT(szChatBuf),0);
	}
	else if(m_EGamePlayerState== eGPS_LOGINSERVER_CONNECTED)
	{
		jNET_SEND(m_pGrid[eLogin],L_ECHO, jT(szMsg),0);
	}
	extern bool g_chat_roop_quit;
	if(g_chat_roop_quit)
		throw false;
	if(delay)
		Sleep(delay);
}


void jPlayerObj::InitUdp(tcstr szIP,jIPacketSocket_IOCP* pS)
{
	name_t bufIP;
	m_Udp_VirtualAddr = nInterface::g_pjINet_OGS->GetUtil()->String2Addr(pS->GetIP(bufIP),pS->GetPort());
	m_Udp_ServerIP = nInterface::g_pjINet_OGS->GetUtil()->String2Addr(szIP);
	name_t buf;
	jLOG1(jFUNC1 _T("udp server ip : %s") , nInterface::g_pjINet_OGS->GetUtil()->Addr2String(m_Udp_ServerIP, buf) );
}


tcstr ToString(jPlayerObj* p, tname1024_t buf)
{
	jt_sprintf(buf, _T("%s: %s , L=%d,G=%d")
		,jT(p->m_szID)
		,p->GetString_EGamePlayerState()
		,(bool)p->m_pGrid[eLogin]
	,(bool)p->m_pGrid[eChannel]
	);
	return buf;
}

