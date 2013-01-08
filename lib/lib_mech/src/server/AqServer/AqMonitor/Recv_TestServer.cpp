/* file : Recv_TestServer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-30 13:20:11
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqMonitor.h"
#include "PlugIn_ToBackEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"
#include "network/protocal/PT_TestServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
using namespace nMech::nNET::nTestServer;





jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{

	namespace _from_TestServer
	{
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TS_HELLO,TestServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB_Data(TS_HELLO,pBE->m_TS_HELLO);
			pS->WritePacket(&WRITE_TM_HELLO(buf,g_ExeEnv.m_szComputerName));

		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TS_ONLINE,TestServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_P_Data(TS_ONLINE,pBE->m_TS_ONLINE);
		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TS2TM_CLIENT_CONNECT_INFO,TestServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_P(TS2TM_CLIENT_CONNECT_INFO);

		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TS_ECHO,TestServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(TS_ECHO);
		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(TM_SET_TEST_ENV,TestServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(TM_SET_TEST_ENV);
		}
		

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,TestServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(aaa);
		}
#endif

	}//namespace _from_TestServer

}
jNET_EVENT_END(PlugIn_ToBackEnd)
