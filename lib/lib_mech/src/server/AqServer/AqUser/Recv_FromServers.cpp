/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"


jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(SS2U_ONLINE)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode*pServer
		READ_PACKET_FromServer(SS2U_ONLINE);
		jRecv_SS2server_ONLINE();
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(U4_USER_CONNECTION_NOTIFY)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode*pServer
		READ_PACKET_FromServer(U4_USER_CONNECTION_NOTIFY);
		assert(pServer->m_eType < jServerInfo::eEND_EServerTypeFrontEnd);
		jAUTO_LOCK_CS1(g_Users.m_CS);

		int i;
		jUserZoneInfo* pUser;
		
		jLIST_TYPEDEF_map(serverid_t,vector<userid_t>,login_ids);
		for(i=0; i< Data.id_connect.size(); ++i)
		{
			pUser = g_Users.find_by_username(Data.id_connect[i].c_str());
			if(!pUser)
			{
				GetjILog()->Warning(jFUNC1 _T("user not found  Data.id_connect[%d]: %s") , i,Data.id_connect[i].c_str());
				continue;
			}
			pUser->Set_ConnectedServer(pServer->m_eType,pServer->Get_sid());

			if(pServer->m_eType==jServerInfo::eTown && pUser->Get_ConnectedServer(jServerInfo::eLogin))
			{
				login_ids[pUser->Get_ConnectedServer(jServerInfo::eLogin)].push_back(pUser->m_uid);
			}
		}
		if(login_ids.size())
		{
			login_ids_it it = login_ids.begin(), ie = login_ids.end();
			for(;it!=ie;++it)
			{
				AqConnectedServerNode* pLogin = pFE->find_user(it->first);
				if(pLogin)
				{
					pLogin->Write_Packet(WRITE_U2L_DO_USER_DISCONNECT(buf,it->second));
				}
			}
		}

		int iDeleteCount=0;
		for(i=0; i< Data.id_disconnect.size(); ++i)
		{
			pUser = g_Users.find_by_username(Data.id_disconnect[i].c_str());
			if(!pUser)
			{
				GetjILog()->Warning(jFUNC1 _T("user not found Data.id_disconnect[%d]: %s") , i,Data.id_disconnect[i].c_str());
				continue;
			}
			pUser->Set_ConnectedServer(pServer->m_eType,0);
			if(!pUser->IsConnectedServer())
			{
				if(pServer->m_eType==jServerInfo::eLogin)
				{// �� �α伭������ ������������ �޼����� �԰� Dungeon&Town������ ���ӵ��� ���������̸�
					// ���忡 �뺸�ؼ� DBCache������ ������ �Ѵ�.
					jAUTO_LOCK_CS1(pFE->m_DisconnectedUsers_CS);
					pFE->m_DisconnectedUsers[pUser->m_sid_world].push_back(pUser->m_szID);
				}
				else if(pServer->m_eType==jServerInfo::eWorld)
				{
					jAssert0(0 && "town������disconnect������ ���弭���� UserServer�� ������ �ʴ´�.�ֳĸ�Town���� ����world�� discon���������⶧��");
					// town�� ���������� ���� disconnect������ ���弭���� ���� ���޵ȴ�.
				}
				else
				{
				}
				g_Users.erase(pUser);
				++iDeleteCount;
			}
		}
		GetjILog()->Log(_T("User_Delete count = %d"),iDeleteCount);
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




