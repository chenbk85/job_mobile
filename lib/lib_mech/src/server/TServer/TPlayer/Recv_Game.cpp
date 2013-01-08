/* file : Recv_Game.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:05:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TPlayer.h"
#include "PlugIn_Connect.h"



jNET_EVENT_BEGIN(PlugIn_Connect)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(G_ERROR,GameServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(G_ERROR);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(G_ECHO,GameServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(G_ECHO);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(G2X_CHAT,GameServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(G2X_CHAT);
	}

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,GameServer)
		{
			// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
			aq_READ_PACKET_P2P_PB(aaa);
		}
#endif

}
jNET_EVENT_END(PlugIn_Connect)
