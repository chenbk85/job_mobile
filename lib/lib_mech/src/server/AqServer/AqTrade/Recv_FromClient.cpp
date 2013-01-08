/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToBackEnd.h"
#include "PlugIn_ToFrontEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"
#include "network/protocal/PT_LoginServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
using namespace nLoginServer;



jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{

#define READ_PACKET_TS(X) READ_PACKET(X);\
	jFE();if(!pFE) return;\
	nswb1024_t seb;\
	AqClientUser* pUser= pFE->get_user(pS);\
	if(!pUser){GetjILog()->Warning(_T(#X) _T(" pUser==NULL"));	return;}\

	//X2LG_USER_EKEY를 클라이언트로부터 받았을때.
	jNET_EVENT_RECEIVER(L_ECHO)
	{
		READ_PACKET_TS(L_ECHO);
		pFE->send_all(WRITE_L_ECHO(seb,0,Data.msg),0);
	}

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




