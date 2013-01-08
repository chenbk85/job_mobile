/* file : Recv_FromTown.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-11 21:30:51
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

#define jGET_DBCache_ret(pDB,pUser,errorC)\
	AqConnectedServerNode* pDB = pFE->find_user(pUser->m_uid.m_dc_sid);\
	if(!pDB){jSEND_ERROR_USER_DISCONNECT(W , SR_t(USER_DSERVER_sid_NOT_FOUND) , CR_t(errorC)  , pUser->m_uid); return;}


jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(T2W_USER_LOGIN_CHANNEL)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pServer
		READ_PACKET_FromServer(T2W_USER_LOGIN_CHANNEL);

		jUserZoneInfo* pUser=0;
		{
			jAUTO_LOCK_CS1(g_Users.m_CS);
			pUser = g_Users.find_by_username(Data.id);
		}
		if(!pUser)
		{
			//해당 유저가 로긴서버로 접속된상태가아님. 강제종료시켜야함.
			jSEND_ERROR_USER_DISCONNECT(W , SR_t(USER_IS_NOT_FROM_LSERVER),CR_t(T2W_USER_LOGIN_CHANNEL) , Data.uid);
			return;
		}
		if(ja_strcmp(pUser->m_szID , Data.id))
		{
			//해당 유저 uid는 찾았으나 uid에 해당하는 id name이 틀렸다.
			jSEND_ERROR_USER_DISCONNECT(W , SR_t(IDNAME_IS_NOT_MATCH_FROM_UID) ,CR_t(T2W_USER_LOGIN_CHANNEL) , Data.uid);
			return;
		}
		pUser->Set_ConnectedServer(jServerInfo::eTown, pServer->Get_sid());
		jGET_DBCache_ret(pDB,pUser,T2W_USER_LOGIN_CHANNEL);

		pDB->Write_Packet(WRITE_W2DC_USER_LOGIN_CHANNEL(buf, Data.uid,Data.id,pServer->Get_sid()));

	}
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(T2W_NEW_TOWN)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pServer
		READ_PACKET_FromServer(T2W_NEW_TOWN);

		jUserZoneInfo* pUser=0;
		{
			jAUTO_LOCK_CS1(g_Users.m_CS);
			pUser = g_Users.find_by_uid(Data.uid);
		}
		if(!pUser)
		{
			//해당 유저가 로긴서버로 접속된상태가아님. 강제종료시켜야함.
			jSEND_ERROR_USER_DISCONNECT(W , SR_t(USER_IS_NOT_FROM_LSERVER),CR_t(T2W_NEW_TOWN) , Data.uid);
			return;
		}

		jAUTO_LOCK_CS1(TownUsingList::Get().m_CS);
		nXML::jE eTown = TownUsingList::Get().GetFreeTown(Data.csid,pUser->m_szID,Data.tpsid);
		if(eTown.empty())
		{
			jSEND_ERROR_TO_USER(W , SR_t(FREE_TOWN_NOT_FOUND),CR_t(T2W_NEW_TOWN) , Data.uid);
			return;
		}

		jGET_DBCache_ret(pDB,pUser,T2W_NEW_TOWN);
		pDB->Write_Packet(WRITE_W2DC_NEW_TOWN(buf, Data.uid,Data.csid,Data.tpsid , Data.town_name));
		
	}


	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*pFE , BYTE buf[1024] , AqConnectedServerNode* pServer
		READ_PACKET_FromServer(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)





