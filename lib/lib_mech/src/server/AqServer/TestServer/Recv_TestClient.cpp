/* file : Recv_TestClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:09:22
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"

#include "network/protocal/PT_TestServer_Enum.h"
using namespace nMech::nNET::nTestServer;



jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	jNET_EVENT_RECEIVER(TC_HELLO)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(TC_HELLO);
		pUser->m_eType = AqTestClientNode::eTestClient;
		jt_sprintf(pUser->m_szID, _T("C:%s"),Data.my_computer_name);

		pS->WritePacket(&WRITE_TS_ONLINE(buf
			, pv_TEST_ID_START_NUM->Get_int()
			, pv_DummyCount->Get_int()
			, pv_DefaultLoginIP->Get_cstr() 
			, pv_DefaultLoginPort->Get_int()));

	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(TS_ECHO)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(TS_ECHO);
		pFE->send_all(WRITE_TS_ECHO(buf,Data),0);
	}


#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)

