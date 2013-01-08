/* file : Recv_Login.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:03:09
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"
#include "PlugIn_ToBackEnd.h"

#include "base/Random.h"

vector<jWorldServerInfo> g_world_list;
S_L2X_CHANNEL_LIST g_S_L2X_CHANNEL_LIST;

jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	namespace _from_LoginServer
	{
		using namespace nLoginServer;
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L_HELLO,LoginServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			aq_READ_PACKET_P2P_PB(L_HELLO);
			jNetClient_Call_ret(L_HELLO, Data);
			pUser->Write_Packet_Login(WRITE_X2L_GET_WORLD_LIST(buf));
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L_ECHO,LoginServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			aq_READ_PACKET_P2P_PB(L_ECHO);
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L2X_USER_LOGIN_OK,LoginServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			aq_READ_PACKET_P2P_PB_Data(L2X_USER_LOGIN_OK);
			if(!pUser->m_L2X_USER_LOGIN_OK.channel.size())
			{
				GetjILog()->Warning(jFUNC1 _T("channel 이 하나도 없습니다."));
				return;
			}
			if(g_pNetClient->CallBack(jS(L2X_USER_LOGIN_OK),pUser,pS,&pUser->m_L2X_USER_LOGIN_OK)) return;

			int idx = nUtil::Randomi(0,pUser->m_L2X_USER_LOGIN_OK.channel.size()-1);
			pS->WritePacket(&WRITE_X2L_CHANNEL_SELECT(buf,pUser->m_L2X_USER_LOGIN_OK.channel[idx]));
		}
		
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L2X_WORLD_LIST,LoginServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			aq_READ_PACKET_P2P_PB(L2X_WORLD_LIST);
			g_world_list = Data.worlds;

			if(g_pNetClient->CallBack(jS(L2X_WORLD_LIST),pUser,pS,&Data))
				return;

			vector<uint8> pwd;
			extern int g_default_world_sid;
			acstr szWorld = g_world_list.size() ? g_world_list[g_default_world_sid-1].szName: "NULL";
			pS->WritePacket( &WRITE_X2L_USER_LOGIN( buf , szWorld ,pUser->m_szID, pwd, "null" , "null" ) );
		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L2X_CHANNEL_LIST,LoginServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			aq_READ_PACKET_P2P_PB(L2X_CHANNEL_LIST);
			g_S_L2X_CHANNEL_LIST = Data;
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L2X_CHANNEL_SELECT_RESULT,LoginServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			aq_READ_PACKET_P2P_PB_Data(L2X_CHANNEL_SELECT_RESULT);
			pUser->m_L2X_USER_LOGIN_OK.uid = pUser->m_L2X_CHANNEL_SELECT_RESULT.uid;

			//if(g_pNetClient->CallBack(jS(L2X_CHANNEL_SELECT_RESULT),pUser,pS,&pUser->m_L2X_CHANNEL_SELECT_RESULT))return;

			nXML::jE e = pUser->Get_jE_Town();
			if(e.empty())
			{
				GetjILog()->Warning(jFUNC1 _T("net xml : TCP_TownServer is not found"));
				return;
			}
			fname_t szIP;
			jt_sprintf(szIP , _T("%s:%d") ,jT(pUser->m_L2X_CHANNEL_SELECT_RESULT.ip), pUser->m_L2X_CHANNEL_SELECT_RESULT.port);
			e->Set_cstr(szIP);
			jIPacketSocket_IOCP* pSTown = pUser->StartSocket_Town(pBE->m_pClientSession);
			if(!pSTown)
			{
				GetjILog()->Warning(jFUNC1 _T(" to town server connection fail : %s"),szIP);
				return;
			}
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L_ERROR,LoginServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			aq_READ_PACKET_P2P_PB(L_ERROR);
		}

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,LoginServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			aq_READ_PACKET_P2P_PB(aaa);
		}
#endif

	}//namespace _from_LoginServer
}
jNET_EVENT_END(PlugIn_ToBackEnd)
