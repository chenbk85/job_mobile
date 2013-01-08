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

#include "network/protocal/PT_DungeonServer_Enum.h"
using namespace nMech::nNET::nDungeonServer;

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqClientUser_D)
{
	m_pMM->Regist_TimeBase(0 , jMsg_C4_USER_CONNECTION_NOTIFY, 0,pv_C4_USER_CONNECTION_NOTIFY->Get_float())->DoWakeUp();

}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd)
{

}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqClientUser_D);


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
	jFE_OnIoConnected_fromClient(D);
}

VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromClient(D);

	erase(pUser);
}


jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
#define READ_PACKET_TS(X) READ_PACKET(X);\
	PlugIn_ToFrontEnd*pFP = (PlugIn_ToFrontEnd*)pPlugIn;if(!pFP) return;\
	nswb1024_t seb;\
	AqClientUser_D* pUser= pFP->get_user(pS);\
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
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser_D* pDummy
		READ_PACKET_TS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)




