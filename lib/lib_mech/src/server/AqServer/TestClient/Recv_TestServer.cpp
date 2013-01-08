/* file : Recv_TestServer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:05:50
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"
#include "PlugIn_ToBackEnd.h"

jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	namespace _from_TestServer
	{
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TS_HELLO,TestServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB_Data(TS_HELLO,pBE->m_TS_HELLO);
			pS->WritePacket(&WRITE_TC_HELLO(buf,g_ExeEnv.m_szComputerName));
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TS_ECHO,TestServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(TS_ECHO);

			if(Data.type==0)
			{
				GetjILog()->Log(_T("TS_ECHO(%d) %s"),Data.type, Data.msg);
			}
			else
			{
				GetjILog()->Log(_T("\t%s"),Data.msg);
			}
#if 0
			if( Data.msg[0]=='%' ) 
			{
				tstring str = Data.msg+1;

				if( isdigit(str[0]))
				{

					TCHAR* ch = jt_strchr(Data.msg+1 , ' ');
					if(!ch) return;
					*ch=0;
					int id = jt_atoi(Data.msg+1);
					if(id != pBE->m_DummyID) return;
					++ch;
					str =ch; 
				}
				if(nCONSOLE::Get_jIConsoleCmd()->ParseCmd(jT(str) ))
				{
					nswb1024_t buf;
					pS->WritePacket(&WRITE_TS_ECHO(buf
						, jA(pBE->m_DummyName)
						,str.c_str()
						,2));
				}
			}
#endif

		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TS_ONLINE,TestServer)
		{

			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(TS_ONLINE);
			pv_TEST_ID_START_NUM->Set_int(Data.TEST_ID_START_NUM);

			pv_DummyCount->Set_int(Data.iDummyCount);
			pv_DefaultLoginIP->Set_cstr(Data.szLoginIP);
			pv_DefaultLoginPort->Set_int(Data.iLoginPort);
			pBE->Logout_Dummy_AllSocket(1000,0);
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TM_SET_TEST_ENV,TestServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(TM_SET_TEST_ENV);
			pv_DummyCount->Set_int(Data.i_DummySessionCount);
			pv_DefaultLoginIP->Set_cstr(Data.sLoginIP);
			pv_DefaultLoginPort->Set_int(Data.iLoginPort);
			//pBE->Logout_Dummy_AllSocket(1000,0);
		}

		S_TM_TEST_LOGIN_START g_TM_TEST_LOGIN_START;
		unsigned __stdcall TM_TEST_LOGIN_START_WorkerThreadCallback( void* pThreadParam)
		{
			jBE_ret(0);
			pBE->ConnectToLoginServer_AllDummy(g_TM_TEST_LOGIN_START.per_user,g_TM_TEST_LOGIN_START.delay);
			return 0;
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TM_TEST_LOGIN_START,TestServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_P_Data(TM_TEST_LOGIN_START,g_TM_TEST_LOGIN_START);
			if(g_TM_TEST_LOGIN_START.per_user==0)return;
			HANDLE WorkerThread = (HANDLE)_beginthreadex(NULL, 0, TM_TEST_LOGIN_START_WorkerThreadCallback,0, 0, NULL);
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TM_TEST_LOG_OUT,TestServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(TM_TEST_LOG_OUT);
			extern bool g_isCancel_StartSession_AllDummy;
			g_isCancel_StartSession_AllDummy=true;

			pBE->Logout_Dummy_AllSocket(Data.per_user,Data.delay);
		}
		
#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,TestServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(aaa);
		}
#endif

	}//namespace _from_TestServer

}
jNET_EVENT_END(PlugIn_ToBackEnd)
