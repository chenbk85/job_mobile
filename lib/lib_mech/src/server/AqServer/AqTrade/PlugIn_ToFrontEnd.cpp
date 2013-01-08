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



using namespace nMech::nNET::nCentralServer;

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqServerNode)
{

}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd)
{

}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqServerNode);

PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
{
}

bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCommand)
{
	//nswb1024_t buf;
	std::tstring str = _T("FromAqCentral:");
	str += szCommand;
	net_string256 sendStr = str.c_str();
	//jPacket_Base pk = nTestCentralServer::WRITE_TS_ECHO(buf, sendStr );
	//jIPacketSocket_IOCP* p =0;
	//send_all(&pk, p );	
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
	AqServerNode* pUser = push_back_if_not_found(pS);
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



VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
#if 0
	if(!pS) return;

	jBE();

		fname_t szIP;	
	pS->GetIP(szIP);

	AqServerNode* pUser = get_user(pS);
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
		pBE->m_pToCentral->WritePacket(&WRITE_C4_USER_TCP_DISCONNECT(buf, (user_id_t)pUser->m_uid, this->size()-1 ));
	}
	else
	{
		GetjILog()->Warning(_T("PlugIn_ToFrontEnd::OnIoDisconnected : m_pToCentral==NULL"));
	}
*/
	erase(pUser);
#endif
}

jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
#define READ_PACKET_TS(X) READ_PACKET(X);\
	PlugIn_ToFrontEnd*pFP = (PlugIn_ToFrontEnd*)pPlugIn;if(!pFP) return;\
	nswb1024_t seb;\
	AqServerNode* pUser= pP->get_user(pS);\
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
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqServerNode* pDummy
		READ_PACKET_TS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)




