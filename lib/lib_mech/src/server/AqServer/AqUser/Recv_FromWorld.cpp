/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"


jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(W2U_USER_LOGIN_RESULT)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode*pServer
		READ_PACKET_FromServer(W2U_USER_LOGIN_RESULT);
		
		jAUTO_LOCK_CS1(g_Users.m_CS);
		jUserZoneInfo* pUser = g_Users.find_by_username(Data.id);
		if(!pUser)
		{
			GetjILog()->Warning(jFUNC1 _T("user not found : %s"),jT(Data.id));
			return;
		}
		g_Users.Regist_by_uid(pUser, Data.uid);
		serverid_t sid = pUser->Get_ConnectedServer(jServerInfo::eLogin);
		AqConnectedServerNode* pLogin = pFE->find_user(sid);
		if(!pLogin)
		{
			pServer->m_E->DebugPrint(false);
			GetjILog()->Warning(jFUNC1 _T("LOGIN SERVER NOT FOUND id=%s login_sid=%d)") , jT(Data.id) , Data.uid.m_id , sid);
			pLogin->Write_Packet(WRITE_U2L_USER_LOGIN_RESULT(buf, userid_t(), Data.id , jError(0,CR_t(SERVER_UNKNOWN))));
			return;
		}
		pLogin->Write_Packet(WRITE_U2L_USER_LOGIN_RESULT(buf,Data.uid, Data.id, Data.e));

		if(Data.e.isError())
		{
			g_Users.erase_by_name(Data.id);
		}
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(W2U_USER_LOGIN_DUPLICATE_OK)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode*pServer
		READ_PACKET_FromServer(W2U_USER_LOGIN_DUPLICATE_OK);
		jAUTO_LOCK_CS1(g_Users.m_CS);
#ifdef _DEBUG
		jUserZoneInfo* pUser = g_Users.find_by_username(Data.id);
		if(!pUser)
		{
			GetjILog()->Warning(jFUNC1 _T("user not found : %s"), jT(Data.id));
			return;
		}
#endif
		g_Users.erase_by_name(Data.id);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(W2U_ONLINE_USERS)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode*pServer
		READ_PACKET_FromServer(W2U_ONLINE_USERS);

		// UserServer가 죽으면 로긴 서버는 모든 유저를 discon시키고 월드서버들은 U_HELLO를 받게 되면 W2U_ONLINE_USERS를 호출한다.
		jAUTO_LOCK_CS1(g_Users.m_CS);
		for(int i=0; i<Data.uid.size();++i)
		{
			jUserZoneInfo *pUser = g_Users.push_back_with_world_sid(const_cast<char*>(Data.id[i].c_str()) , pServer->Get_sid());
			pUser->SetFlag_GoingTo_Login(false);
			pUser->m_uid = Data.uid[i];
			pUser->Set_ConnectedServer(jServerInfoBase::eTown, Data.town[i] );
		}
	}



#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode*pServer
		READ_PACKET_FromServer(aaa);
	}
#endif


}
jNET_EVENT_END(PlugIn_ToFrontEnd)
