/* file : Recv_DummyServer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:05:50
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TPlayer.h"





jNET_EVENT_BEGIN(PlugIn_Connect)
{
	namespace _from_DummyServer
	{
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(DT_HELLO,DummyServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			READ_PACKET_PC_B(DT_HELLO);
			g_SG.m_MyInfo = Data.si;
			jt_strcpy_s(g_SG.m_MyInfo.m_szName , g_ExeEnv.m_szComputerName);
			jNET_SEND(pS,X2DT_HELLO,g_SG.m_MyInfo);
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(DT_ECHO,DummyServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			READ_PACKET_PC_B(DT_ECHO);

			if(Data.type==0)
			{
				jLOG1(_T("DT_ECHO(%d) %s"),Data.type, Data.msg);
			}
			else
			{
				jLOG1(_T("\t%s"),Data.msg);
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
					if(id != g_PL.m_DummyID) return;
					++ch;
					str =ch; 
				}
				if(nCONSOLE::Get_jIConsoleCmd()->ParseCmd(jT(str) ))
				{
					nswb1024_t buf;
					pS->WritePacket(&WRITE_DT_ECHO(buf
						, jA(g_PL.m_DummyName)
						,str.c_str()
						,2));
				}
			}
#endif

		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(DT_ONLINE,DummyServer)
		{

			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			READ_PACKET_PC_B(DT_ONLINE);
			pv_TEST_ID_START_NUM->Set_int(Data.TEST_ID_START_NUM);

			pv_DummyCount->Set_int(Data.iDummyCount);
			pv_DefaultLoginIP->Set_cstr(Data.szLoginIP);
			pv_DefaultLoginPort->Set_int(Data.iLoginPort);
			g_PL.Logout_Dummy_AllSocket(1000,0);
		}

// 		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
// 		jNET_EVENT_RECEIVER_P2P(DT_SET_TEST_ENV,DummyServer)
// 		{
// 			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
// 			READ_PACKET_PC_B(DT_SET_TEST_ENV);
// 			pv_DummyCount->Set_int(Data.i_DummySessionCount);
// 			pv_DefaultLoginIP->Set_cstr(Data.sLoginIP);
// 			pv_DefaultLoginPort->Set_int(Data.iLoginPort);
// 			//g_PL.Logout_Dummy_AllSocket(1000,0);
// 		}

// 		S_TM_TEST_LOGIN_START g_TM_TEST_LOGIN_START;
// 		unsigned __stdcall TM_TEST_LOGIN_START_WorkerThreadCallback( void* pThreadParam)
// 		{
// 			jPC_ret(0);
// 			g_PL.Start_Login_AllDummy(g_TM_TEST_LOGIN_START.per_user,g_TM_TEST_LOGIN_START.delay);
// 			return 0;
// 		}
// 
// 		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
// 		jNET_EVENT_RECEIVER_P2P(TM_TEST_LOGIN_START,DummyServer)
// 		{
// 			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
// 			jPC_READ_PACKET_P_Data(TM_TEST_LOGIN_START,g_TM_TEST_LOGIN_START);
// 			if(g_TM_TEST_LOGIN_START.per_user==0)return;
// 			HANDLE WorkerThread = (HANDLE)_beginthreadex(NULL, 0, TM_TEST_LOGIN_START_WorkerThreadCallback,0, 0, NULL);
// 		}
// 
// 		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
// 		jNET_EVENT_RECEIVER_P2P(TM_TEST_LOG_OUT,DummyServer)
// 		{
// 			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
// 			READ_PACKET_PC_B(TM_TEST_LOG_OUT);
// 			extern bool g_isCancel_StartSession_AllDummy;
// 			g_isCancel_StartSession_AllDummy=true;
// 
// 			g_PL.Logout_Dummy_AllSocket(Data.per_user,Data.delay);
// 		}
		
#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,DummyServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			READ_PACKET_PC_B(aaa);
		}
#endif

	}//namespace _from_DummyServer

}
jNET_EVENT_END(PlugIn_Connect)
