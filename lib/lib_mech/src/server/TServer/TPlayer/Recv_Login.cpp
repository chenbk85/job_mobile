/* file : Recv_Login.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:03:09
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TPlayer.h"

#include "base/Random.h"

S_L2X_CHANNEL_LIST g_S_L2X_CHANNEL_LIST;

jNET_EVENT_BEGIN(PlugIn_Connect)
{
	namespace _from_LoginServer
	{
		using namespace nLoginServer;
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L_HELLO,LoginServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			aq_READ_PACKET_P2P_PB(L_HELLO);
			jNetClient_Call_ret(L_HELLO, Data);
			jNET_SEND(pPlayer->m_pGrid[eLogin],X2L_GET_WORLD_LIST);
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L_ECHO,LoginServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			aq_READ_PACKET_P2P_PB(L_ECHO);
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L2X_USER_LOGIN_OK,LoginServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			aq_READ_PACKET_P2P_PB_Data(L2X_USER_LOGIN_OK);
			if(!pPlayer->m_L2X_USER_LOGIN_OK.channel.size())
			{
				jWARN1(_T("channel 이 하나도 없습니다."));
				return;
			}
			if(g_pNetClient->CallBack(jS(L2X_USER_LOGIN_OK),pPlayer,pS,&pPlayer->m_L2X_USER_LOGIN_OK)) return;

			int idx = nUtil::Randomi(0,pPlayer->m_L2X_USER_LOGIN_OK.channel.size()-1);
			pS->WritePacket(&WRITE_X2L_CHANNEL_SELECT(buf,pPlayer->m_L2X_USER_LOGIN_OK.channel[idx]));
		}
		
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L2X_WORLD_LIST,LoginServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			aq_READ_PACKET_P2P_PB(L2X_WORLD_LIST);
			g_PL.m_world_list = Data.worlds;

			if(g_pNetClient->CallBack(jS(L2X_WORLD_LIST),pPlayer,pS,&Data))
				return;

			vector<uint8> pwd;
			extern int g_default_world_sid;
			acstr szWorld = g_PL.m_world_list.size() ? g_PL.m_world_list[g_default_world_sid-1].szName: "NULL";
			pS->WritePacket( &WRITE_X2L_USER_LOGIN( buf , szWorld ,pPlayer->m_szID, pwd, "null" , "null" ) );
		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L2X_CHANNEL_LIST,LoginServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			aq_READ_PACKET_P2P_PB(L2X_CHANNEL_LIST);
			g_S_L2X_CHANNEL_LIST = Data;
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L2X_CHANNEL_SELECT_RESULT,LoginServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			aq_READ_PACKET_P2P_PB_Data(L2X_CHANNEL_SELECT_RESULT);
// 			pPlayer->m_L2X_USER_LOGIN_OK.pid = pPlayer->m_L2X_CHANNEL_SELECT_RESULT.pid;
// 
// 			//if(g_pNetClient->CallBack(jS(L2X_CHANNEL_SELECT_RESULT),pPlayer,pS,&pPlayer->m_L2X_CHANNEL_SELECT_RESULT))return;
// 
// 			nXML::jE e = pPlayer->Get_jE_Channel();
// 			if(e.empty())
// 			{
// 				jWARN1(_T("net xml : TCP_ChannelServer is not found"));
// 				return;
// 			}
// 			fname_t szIP;
// 			jt_sprintf(szIP , _T("%s:%d") ,jT(pPlayer->m_L2X_CHANNEL_SELECT_RESULT.ip), pPlayer->m_L2X_CHANNEL_SELECT_RESULT.port);
// 			e->Set_cstr(szIP);
// 			jIPacketSocket_IOCP* pSChannel = pPlayer->StartSocket_Channel(g_PL.m_pClientSession);
// 			if(!pSChannel)
// 			{
// 				jWARN1(_T(" to channel server connection fail : %s"),szIP);
// 				return;
// 			}
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(L_ERROR,LoginServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			aq_READ_PACKET_P2P_PB(L_ERROR);
		}

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,LoginServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			aq_READ_PACKET_P2P_PB(aaa);
		}
#endif

	}//namespace _from_LoginServer
}
jNET_EVENT_END(PlugIn_Connect)
