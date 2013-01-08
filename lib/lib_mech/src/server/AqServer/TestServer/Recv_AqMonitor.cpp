/* file : Recv_AqMonitor.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-30 14:25:29
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

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(TM_HELLO)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(TM_HELLO);
		pUser->m_eType = AqTestClientNode::eAqMonitor;
		jt_sprintf(pUser->m_szID, _T("A:%s"),Data.my_computer_name);
		pFE->m_listAqMonitor.push_back(pUser);
		
		pS->WritePacket(&WRITE_TS_ONLINE(buf
			, pv_TEST_ID_START_NUM->Get_int()
			, pv_DummyCount->Get_int()
			, pv_DefaultLoginIP->Get_cstr() 
			, pv_DefaultLoginPort->Get_int()));

#define jLAMDA_send_TS2TM_CLIENT_CONNECT_INFO(X,Z) Z(jIPacketSocket_IOCP*,pS)
		jLAMDA_for_each(send_TS2TM_CLIENT_CONNECT_INFO,AqTestClientNode&)
		{
			if(!it.IsTestClient()) return;
			fname_t buf1,buf2;
			it.m_pS->GetAddressString(buf1);
			jIP_Address ip = g_pjINet_OGS->GetUtil()->String2Addr(buf1);
#ifdef _DEBUG
			g_pjINet_OGS->GetUtil()->Addr2String(ip,buf2);
			assert(!jt_strcmp(buf1,buf2));
#endif
			nswb1024_t buf;
			it.m_pS->WritePacket(&WRITE_TS2TM_CLIENT_CONNECT_INFO(buf, it.iHandle,it.m_szID ,ip));
		}
		jLAMDA_end();

		pFE->for_each(send_TS2TM_CLIENT_CONNECT_INFO(pS));

	}
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(TM_SET_TEST_ENV)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(TM_SET_TEST_ENV);

		pv_DummyCount->Set_int(Data.i_DummySessionCount);
		pv_DefaultLoginIP->Set_cstr(Data.sLoginIP);
		pv_DefaultLoginPort->Set_int(Data.iLoginPort);

#define jLAMDA_send_TM_SET_TEST_ENV(X,Z) X(jIPacketSocket_IOCP*,pS) Z(S_TM_SET_TEST_ENV& , Data)
		jLAMDA_for_each(send_TM_SET_TEST_ENV,AqTestClientNode&)
		{
			if(!it.IsTestClient()) return;
			nswb1024_t buf;
			it.m_pS->WritePacket(&WRITE_TM_SET_TEST_ENV(buf, Data));
		}
		jLAMDA_end();

		pFE->for_each(send_TM_SET_TEST_ENV(pS,Data));

	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(TM_TEST_LOGIN_START)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(TM_TEST_LOGIN_START);
		if(jt_strcmp(jS(NULL),Data.testClientName) )
		{
			AqTestClientNode* it = pFE->find_if(_jxFindTestClient_by_name(Data.testClientName));
			if(!it) 
			{
				tname256_t szBuf;
				jt_sprintf(szBuf , _T("%s is not found") , Data.testClientName);
				pS->WritePacket(&WRITE_T_ERROR_MSG(buf,nTestServer::eEMT_ByTestCentral,szBuf));
			}
			it->Write_Packet(WRITE_TM_TEST_LOGIN_START(buf, Data));
			return;
		}

#define jLAMDA_send_TM_TEST_LOGIN_START(X,Z) X(jIPacketSocket_IOCP*,pS) Z(S_TM_TEST_LOGIN_START& , Data)
		jLAMDA_for_each(send_TM_TEST_LOGIN_START,AqTestClientNode&)
		{
			if(!it.IsTestClient()) return;
			nswb1024_t buf;
			it.Write_Packet(WRITE_TM_TEST_LOGIN_START(buf, Data));
		}
		jLAMDA_end();

		pFE->for_each(send_TM_TEST_LOGIN_START(pS,Data));


	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(TM_TEST_LOG_OUT)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(TM_TEST_LOG_OUT);
		if(jt_strcmp(jS(NULL),Data.testClientName) )
		{
			AqTestClientNode* it = pFE->find_if(_jxFindTestClient_by_name(Data.testClientName));
			if(!it) 
			{
				tname256_t szBuf;
				jt_sprintf(szBuf , _T("%s is not found") , Data.testClientName);
				pS->WritePacket(&WRITE_T_ERROR_MSG(buf,nTestServer::eEMT_ByTestCentral,szBuf));
			}
			it->Write_Packet(WRITE_TM_TEST_LOG_OUT(buf, Data));
			return;
		}

#define jLAMDA_send_TM_TEST_LOG_OUT(X,Z) X(jIPacketSocket_IOCP*,pS) Z(S_TM_TEST_LOG_OUT& , Data)
		jLAMDA_for_each(send_TM_TEST_LOG_OUT,AqTestClientNode&)
		{
			if(!it.IsTestClient()) return;
			nswb1024_t buf;
			it.Write_Packet(WRITE_TM_TEST_LOG_OUT(buf, Data));
		}
		jLAMDA_end();
		pFE->for_each(send_TM_TEST_LOG_OUT(pS,Data));

	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(TM2TS_GET_TEST_ENV)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqTestClientNode* pDummy
		READ_PACKET_TS(TM2TS_GET_TEST_ENV);

		pS->WritePacket(&WRITE_TM_SET_TEST_ENV(buf
			,pv_DummyCount->Get_int()
			,pv_DefaultLoginIP->Get_cstr()
			,pv_DefaultLoginPort->Get_int()
			));
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



