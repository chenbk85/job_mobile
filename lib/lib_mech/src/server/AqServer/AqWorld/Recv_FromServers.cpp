/* file : Recv_FromServers.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-07 11:49:54
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"


jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(SS2W_ONLINE)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode* pServer
		READ_PACKET_FromServer(SS2W_ONLINE);
		jRecv_SS2server_ONLINE();
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(W_ERROR)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(W_ERROR);

		G_USERS_FIND_UID(Data.uid);//jUserZoneInfo* pUser;

		if(Data.type==0)
		{
			pFE->Send_UserDisconnection(pUser, jServerInfo::eTown , Data.e , Data.uid);
			pFE->Send_UserDisconnection(pUser, jServerInfo::eDungeon , Data.e , Data.uid);
		}
		else
		{
			AqConnectedServerNode* pServer = pFE->FindServer_by_User(pUser,jServerInfo::eTown);
			if(!pServer) pServer = pFE->FindServer_by_User(pUser,jServerInfo::eDungeon);
			if(!pServer) 
			{
				GetjILog()->Warning(jFUNC1 _T("server is not connected : %s"),jT(pUser->m_szID));
				return;
			}
			pServer->Write_Packet(WRITE_W_ERROR(buf, Data.e, Data.type, Data.msg,Data.uid));
		}
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(W4_USER_DISCONNECT)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pDummy
		READ_PACKET_FromServer(W4_USER_DISCONNECT);

		pFE->Send_W2DC_USER_DISCONNECT(Data.id);
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



