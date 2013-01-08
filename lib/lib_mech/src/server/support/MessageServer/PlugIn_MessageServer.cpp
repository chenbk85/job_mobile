/* file : PlugIn_MessageServer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-06-20 11:31:52
comp.: actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_MessageServer.h"
#include "./protocal/PT_MessageServer_Enum.h"

using namespace nMech::nNET::nMessageServer;

void jMsgClient::DebugPrint()
{
}


jDEFINE_RTTIOBJ_BY_SCOPE(PlugIn_MessageServer,jNet_OGS, 1,1);
JNET_PLUGIN_SINGTONE_DEFINE(PlugIn_MessageServer);


void PlugIn_MessageServer::Start()
{	
	jConnectUserManager<jMsgClient,jIPacketSocket_IOCP*>::Begin();	
	PlugIn_MessageServer::Set(this);
	GetjILog()->Log(_T("Start : %s"),jS(PlugIn_MessageServer));

}
void PlugIn_MessageServer::Stop()
{	
	jConnectUserManager<jMsgClient,jIPacketSocket_IOCP*>::Begin();	
	PlugIn_MessageServer::Set(0);
	GetjILog()->Log(_T("End : %s"),jS(PlugIn_MessageServer));
}

PlugIn_MessageServer::PlugIn_MessageServer()
{
	g_pCurrServerPlugIn= this;
}
bool PlugIn_MessageServer::ParseCmd(tcstr szCommand)
{
	return false;
}

// CIocp의 가상함수들
VOID PlugIn_MessageServer::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFD1();
	jMsgClient* pFServer = Add_User(pS);
	fname_t buf;
	GetjILog()->Log(_T("OnIoConnected = %s"), pS->GetAddressString(buf));
	BYTE sendBuf[1024];

}

VOID PlugIn_MessageServer::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	if(!pS) return;
	jMsgClient* pFServer = GetUser(pS);
	if(!pFServer)return;
	serverid_t sid = pFServer->GetServerID();

	Delete_User(pS);
}


VOID PlugIn_MessageServer::OnIoWrote(jIPacketSocket_IOCP* pSocket)
{
	//GetjILogLT(jx(jNet_OGS),jx(CLIENT))->Log(_T(" PlugIn_MessageServer::OnIoWrote"));

}

jNET_EVENT_BEGIN(PlugIn_MessageServer)
{
#define READ_PACKET_C_P(X) READ_PACKET(X); PlugIn_MessageServer*pP = (PlugIn_MessageServer*)pPlugIn;
#define READ_PACKET_C_PS(X) READ_PACKET_C_P(X); jMsgClient* pFServer = pP->GetUser(pS);
#define READ_PACKET_C_PB(X) READ_PACKET_C_P(X);	BYTE buf[1024];
#define READ_PACKET_C(X) READ_PACKET_C_P(X); BYTE buf[1024];jMsgClient* pFServer = pP->GetUser(pS);

	//jIPacketSocket_IOCP* pS,BYTE *pReadBuff, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(M_ECHO)
	{
		// PlugIn_MessageServer*pP , BYTE buf[1024] , jMsgClient* pFServer
		READ_PACKET_C(M_ECHO);
		pP->Send_AllUser(&WRITE_C_ECHO(buf, Data.msg),0);
	}

#if 0
	//jIPacketSocket_IOCP* pS,BYTE *pReadBuff, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_MessageServer*pP , BYTE buf[1024] , jMsgClient* pFServer
		READ_PACKET_C(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_MessageServer)

