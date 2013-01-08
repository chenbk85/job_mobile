/* file : Recv_FromDBCache.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-04 21:40:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TWorld.h"

jNET_EVENT_BEGIN(PlugIn_Server)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(DC2W_USER_LOGIN_RESULT)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jIGridNode* pDummy
		READ_PACKET_PS_BS(DC2W_USER_LOGIN_RESULT);

		
		jPlayerBase* pPlayer = g_PL.find(Data.id);
		if(pPlayer)
		{ // 최초 등록인데 기존에 있다는 예기는 에러 상황!
			jERROR("user found : %s, jTODO 발생하면 안됨.", jT(Data.id));
		}
		else
		{
			if(!Data.e.isError())
			{
				g_PL.create(Data.id,Data.pid);
			}
		}
		jNET_SEND2(g_SG.m_User,W2U_USER_LOGIN_RESULT, Data.pid , Data.e , Data.id);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(DC2W_USER_LOGIN_DUPLICATE_OK)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jIGridNode* pDummy
		READ_PACKET_PS_BS(DC2W_USER_LOGIN_DUPLICATE_OK);
		
		g_PL.erase(Data.id);
		jNET_SEND2(g_SG.m_User, W2U_USER_LOGIN_DUPLICATE_OK, Data.id );
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(DC2W_NEW_TOWN_ERROR)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jIGridNode* pDummy
		READ_PACKET_PS_BS(DC2W_NEW_TOWN_ERROR);

		{
			jAUTO_LOCK_CS1(ChannelUsingList::Get().m_CS);
			ChannelUsingList::Get().ChannelToFree(Data.csid,Data.tpsid);
		}

		jGET_pPlayer(Data.pid);

		jPC();
		jIGridNode* pChannel = g_SG.SEND_PACKET_SID(pPlayer->Get_Server(eChannel) 
					, W_ERROR,jErrorInfo(Data.e,eEAT_NOTIFY_ALL_CLIENT,__FUNCTION__ , Data.pid) );
		if(!pChannel)
		{
			jWARN("user's ChannelServer not found : %s",jT(pPlayer->m_szID));
		}
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(DC2W_TOWN_DELETE_OK	)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jIGridNode* pDummy
		READ_PACKET_PS_BS(DC2W_TOWN_DELETE_OK	);
		jAUTO_LOCK_CS1(ChannelUsingList::Get().m_CS);
		ChannelUsingList::Get().ChannelToFree(Data.csid,Data.tp);

	}


	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jIGridNode* pDummy
		READ_PACKET_PS_BS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)





