/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"


jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{

#define READ_PACKET_TS(X) READ_PACKET(X);\
	jFE();if(!pFE) return;\
	nswb1024_t seb;\
	AqConnectedServerNode* pUser= pFE->get_user(pS);\
	if(!pUser){GetjILog()->Warning(_T(#X) _T(" pUser==NULL"));	return;}\

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_TS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)



