/* file : Recv_TestClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:09:22
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"

#include "../protocal/PT_TestServer_Enum.h"
using namespace nMech::nNET::nTestServer;



jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	/*
	jNET_EVENT_RECEIVER(X2S_LOGIN)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(X2S_LOGIN);
		pUser->m_eType = AqTestClientNode::eTestClient;
		jt_sprintf(pUser->m_szID, _T("C:%s"),Data.my_computer_name);

		pS->WritePacket(&WRITE_S_ONLINE(buf
			, pv_TEST_ID_START_NUM->Get_int()
			, pv_DummyCount->Get_int()
			, pv_DefaultLoginIP->Get_cstr() 
			, pv_DefaultLoginPort->Get_int()));

	}
*/
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(S_ECHO)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(S_ECHO);
		if(Data.type==0)
		{
			pS->WritePacket(WRITE_S_ECHO(buf,Data));
		}
		else
		{
			pFE->send_all(WRITE_S_ECHO(buf,Data),0);
		}
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2S_THREAD_TEST1)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(X2S_THREAD_TEST1);
		wfname_t szMsg;
		jw_sprintf(szMsg,L"X2S_THREAD_TEST1 thread=%d",GetCurrentThreadId());
		pFE->send_all(WRITE_S_ECHO(buf,Data.type, szMsg),0);
#if 0
		int *p=0;
		*p = 1234;
		printf("%d",*p);
#endif
	
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2S_THREAD_TEST2)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(X2S_THREAD_TEST2);
		wfname_t szMsg;
		jw_sprintf(szMsg,L"X2S_THREAD_TEST2 thread=%d",GetCurrentThreadId());
		pFE->send_all(WRITE_S_ECHO(buf,Data.type, szMsg),0);
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

