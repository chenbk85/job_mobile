/* file : Recv_FromDBCache.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-04 21:40:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "network/protocal/PT_UserServer_Enum.h"
using namespace nMech::nNET::nUserServer;

jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(DC2W_USER_LOGIN_RESULT)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(DC2W_USER_LOGIN_RESULT);
		jAUTO_LOCK_CS1(g_Users.m_CS);
		jUserZoneInfo* pUser = g_Users.find_by_username(Data.id);
		if(!pUser)
		{
			fname_t buf;
			GetjILog()->Warning(jFUNC1 _T("user not found : %s"), jT(Data.id), buf);
#ifdef _DEBUG
			jAssert0(0 && "DC2W_USER_LOGIN_RESULT");
#endif
		}
		else
		{
			if(!Data.e.isError())
			{
				g_Users.Regist_by_uid(pUser,Data.uid);
			}
		}
		jBE();
		pBE->m_pToUser->WritePacket(&WRITE_W2U_USER_LOGIN_RESULT(buf, Data.uid , Data.e , Data.id));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(DC2W_USER_LOGIN_DUPLICATE_OK)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(DC2W_USER_LOGIN_DUPLICATE_OK);
		jAUTO_LOCK_CS1(g_Users.m_CS);
		g_Users.erase_by_name(Data.id);
		jBE();
		if(!pBE->m_pToUser)
		{
			GetjILog()->Warning(jFUNC1 _T("m_pToUser ==NULL"));
			return;
		}
		pBE->m_pToUser->WritePacket(&WRITE_W2U_USER_LOGIN_DUPLICATE_OK(buf, Data.id ));
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(DC2W_NEW_TOWN_ERROR)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(DC2W_NEW_TOWN_ERROR);

		{
			jAUTO_LOCK_CS1(TownUsingList::Get().m_CS);
			TownUsingList::Get().TownToFree(Data.csid,Data.tpsid);
		}

		jUserZoneInfo* pUser = g_Users.find_by_uid(Data.uid);
		if(!pUser)
		{
			GetjILog()->Warning(jFUNC1 _T("user not found : "));
			jAssert0(0 && "DQ2DC_TOWN_CREATE_ERROR");
			return;
		}
		AqConnectedServerNode* pTown = pFE->GetServerByUserZone(pUser,jServerInfo::eTown);
		if(!pTown)
		{
			GetjILog()->Warning(jFUNC1 _T("user's TownServer not found : %s"),jT(pUser->m_szID));
			return;
		}
		pTown->Write_Packet(WRITE_W_ERROR(buf,Data.e,2,"DQ2DC_NEW_TOWN_ERROR" , Data.uid));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(DC2W_TOWN_DELETE_OK	)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(DC2W_TOWN_DELETE_OK	);
		jAUTO_LOCK_CS1(TownUsingList::Get().m_CS);
		TownUsingList::Get().TownToFree(Data.csid,Data.tp);

	}


	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)





