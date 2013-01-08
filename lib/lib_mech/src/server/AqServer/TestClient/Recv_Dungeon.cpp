/* file : Recv_Dungeon.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:05:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"
#include "PlugIn_ToBackEnd.h"



jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(D_ERROR,DungeonServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(D_ERROR);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(D_ECHO,DungeonServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(D_ECHO);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(D2X_CHAT,DungeonServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(D2X_CHAT);
	}

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,DungeonServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			aq_READ_PACKET_P2P_PB(aaa);
		}
#endif

}
jNET_EVENT_END(PlugIn_ToBackEnd)
