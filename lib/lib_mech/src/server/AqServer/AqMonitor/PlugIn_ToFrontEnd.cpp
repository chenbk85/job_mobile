/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"
#include "network/protocal/PT_LoginServer_Enum.h"


int Get_CURR_USER()
{
	jFE_ret(0);
	return pFE->size();
}

int Get_MAX_USER()
{
	jFE_ret(0);
	return pFE->m_pE->GetAttrVar(jS(MaxTcpUser))->Get_int();
}


jCONSOLE_CMD_AUTO(login , load_client_version,0,"클라이언트 버젼체크파일 리로드","")
{
	PlugIn_ToFrontEnd* pP = PlugIn_ToFrontEnd::Get();
	if(!pP) return false;
#if 0
	nFileSystem::jFolder dir;
	tstring ver_file = tstring(pv_SERVER_RESOUCE->Get_cstr())+_T("av.lvf");
	memset(&pP->m_ClientVer, 0, sizeof(pP->m_ClientVer));
	pP->m_isClientVerCheck = GetAqVer(jA(ver_file.c_str()), pP->m_ClientVer);
	if(pP->m_isClientVerCheck)
	{
		GetjILog()->Log(_T("%s load ok"),ver_file.c_str());
	}
	else
	{
		GetjILog()->Warning(_T("%s load Fail"),ver_file.c_str());
	}
#endif
	return true;
}



using namespace nMech::nNET::nCentralServer;

jDEFINE_RTTIOBJ_BY_SCOPE(PlugIn_ToFrontEnd,jNet, 1,1);
JNET_PLUGIN_SINGTONE_DEFINE(PlugIn_ToFrontEnd);


void PlugIn_ToFrontEnd::Start()
{	
	jServerUsers<AqClientUser>::start();	
	PlugIn_ToFrontEnd::Set(this);
	GetjILog()->Log(_T("Start : %s"),jS(PlugIn_ToFrontEnd));

}

void PlugIn_ToFrontEnd::Stop()
{	
	jServerUsers<AqClientUser>::start();	
	PlugIn_ToFrontEnd::Set(0);
	GetjILog()->Log(jFUNC1 _T(" stop"));
}

PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
:m_isClientVerCheck(false)
{
	//g_pCurrPlugIn= this;
	// 버젼체크 파일로딩
	//nFileSystem::jFolder dir;
	//tstring ver_file = tstring(pv_SERVER_RESOUCE->Get_cstr())+_T("av.lvf");
	//m_isClientVerCheck = GetAqVer(jA(ver_file.c_str()), m_ClientVer);
	m_pMM = nEVENT::jIMsgManager::Get(jS(LoginServer), true);
}

bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCommand)
{
	//nswb1024_t buf;
	std::tstring str = _T("FromAqCentral:");
	str += szCommand;
	net_string256 sendStr = str.c_str();
	//jPacket_Base pk = nTestCentralServer::WRITE_TS_ECHO(buf, sendStr );
	//jIPacketSocket_IOCP* p =0;
	//Send_AllUser(&pk, p );	
	return false;
}

void jSocketDebugger(jIPacketSocket_IOCP* pS)
{

}

// CIocp의 가상함수들
VOID PlugIn_ToFrontEnd::OnIoConnected(jIPacketSocket_IOCP *pS)
{
#if 0
	nswb256_t buf;
	PlugIn_ToBackEnd* pBE = PlugIn_ToBackEnd::Get();
	if(!pBE || !pBE->IsReady_LogginServer())
	{
		GetjILog()->Warning(_T("lobby server is not ready"));
		m_pServer->DisconnectTcpClient(pS);
		return;
	}
	AqClientUser* pUser = push_back_if_not_found(pS);
	fname_t szIP;

	GetjILog()->Log(_T("OnIoConnected = %s"), pS->GetAddressString(szIP));
	char* ch = ja_strchr(szIP,':');
	if(ch) *ch = 0;
	ja_strcpy( pUser->m_EkeyInfo.ip , jA(szIP));

	/*
	pS->WritePacket(&nLoginServer::WRITE_LG_HELLO(buf, sendPK) );
	*/
#endif
}

VOID PlugIn_ToFrontEnd::OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP)	
{	
	jIPlugIn_Net::OnIoRead(pS,pk,pIP,pHT);
	//GetjILog()->Log(jFUNC1 _T(" %d "), pk->num);
}

VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
#if 0
	if(!pS) return;

	jBE();

		fname_t szIP;	
	pS->GetIP(szIP);

	AqClientUser* pUser = get_user(pS);
	if(!pUser)
	{
		GetjILog()->Warning(jFUNC1 _T(" pUser==null"));
		return;
	}

	nswb256_t buf;
	GetjILog()->Log(jFUNC1 _T("loginserver : tcp user disconnected : %s"), jT(pUser->m_szID) );
/*
	if(pBE->m_pToCentral)
	{
		pBE->m_pToCentral->WritePacket(&WRITE_C4_USER_TCP_DISCONNECT(buf, (userdb_id_t)pUser->m_uid, this->size()-1 ));
	}
	else
	{
		GetjILog()->Warning(_T("PlugIn_ToFrontEnd::OnIoDisconnected : m_pToCentral==NULL"));
	}
*/
	erase(pUser);
#endif
}

VOID PlugIn_ToFrontEnd::OnIoWrote(jIPacketSocket_IOCP* pSocket)
{
	//GetjILogLT(jx(jNet),jx(CLIENT))->Log(_T(" PlugIn_ToFrontEnd::OnIoWrote"));

}

jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	using namespace nLoginServer;

#define READ_PACKET_TS(X) READ_PACKET(X);\
	PlugIn_ToFrontEnd*pP = (PlugIn_ToFrontEnd*)pPlugIn;if(!pP) return;\
	nswb1024_t buf;\
	AqClientUser* pUser= pP->get_user(pS);\
	if(!pUser){GetjILog()->Warning(_T(#X) _T(" pUser==NULL"));	return;}\

#if 0
	//X2LG_USER_EKEY를 클라이언트로부터 받았을때.
	jNET_EVENT_RECEIVER(X2LG_USER_EKEY)
	{
		READ_PACKET_TS(X2LG_USER_EKEY);
	}
#endif

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pDummy
		READ_PACKET_TS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)




