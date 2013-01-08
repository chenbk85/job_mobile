/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TUser.h"


jNET_EVENT_BEGIN(PlugIn_Server)
{

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(SS2U_ONLINE)
	{
		// PlugIn_Server* pPS , BYTE buf[1024] , jServerInfo* si
		jRecv_SS2server_ONLINE(U);

		jNET_SEND(pS,U2SS_ONLINE_OK,si->m_sid);

	}
#ifdef TSERVER_PREPARE
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(U4_USER_CONNECTION_NOTIFY)
	{
		// PlugIn_Server* pPS , BYTE buf[1024] , jServerInfo* si
		READ_PACKET_PS_BS(U4_USER_CONNECTION_NOTIFY);
		assert(si->m_eType < eEND_EServerTypeFrontEnd);
		

		size_t i;
		jPlayerBase* pUser;
		
		jLIST_TYPEDEF_map(serverid_t,vector<player_id_t>,login_ids);
		for(i=0; i< Data.id_connect.size(); ++i)
		{
			pUser = g_Users.find_by_username(Data.id_connect[i].c_str());
			if(!pUser)
			{
				jWARN1(_T("user not found  Data.id_connect[%d]: %s") , i,Data.id_connect[i].c_str());
				continue;
			}
			pUser->Set_Server(si->m_eType,si->m_sid);

			if(si->m_eType==eChannel && pUser->Get_Server(eLogin))
			{
				login_ids[pUser->Get_Server(eLogin)].push_back(pUser->m_pid);
			}
		}
		if(login_ids.size())
		{
			login_ids_it it = login_ids.begin(), ie = login_ids.end();
			for(;it!=ie;++it)
			{
				jServerInfo* pLogin = g_SG.ServerInfo_find(it->first);
				if(pLogin)
				{
					//pLogin->Write_Packet(WRITE_U2L_DO_USER_DISCONNECT(buf,it->second));
				}
			}
		}

		int iDeleteCount=0;
		for(i=0; i< Data.id_disconnect.size(); ++i)
		{
			pUser = g_Users.find_by_username(Data.id_disconnect[i].c_str());
			if(!pUser)
			{
				jWARN1(_T("user not found Data.id_disconnect[%d]: %s") , i,Data.id_disconnect[i].c_str());
				continue;
			}
			pUser->Set_Server(si->m_eType,0);
			if(!pUser->IsConnectedServer())
			{
				if(si->m_eType==eLogin)
				{// �� �α伭������ ������������ �޼����� �԰� Game&Channel������ ���ӵ��� ���������̸�
					// ���忡 �뺸�ؼ� DBCache������ ������ �Ѵ�.
					jAUTO_LOCK_CS1(pPS->m_DisconnectedUsers_CS);
					pPS->m_DisconnectedUsers[pUser->m_sid_world].push_back(pUser->m_szID);
				}
				else if(si->m_eType==eWorld)
				{
					jAssert0(0 && "channel������disconnect������ ���弭���� UserServer�� ������ �ʴ´�.�ֳĸ�Channel���� ����world�� discon���������⶧��");
					// channel�� ���������� ���� disconnect������ ���弭���� ���� ���޵ȴ�.
				}
				else
				{
				}
				g_Users.erase(pUser);
				++iDeleteCount;
			}
		}
		jLOG1(_T("User_Delete count = %d"),iDeleteCount);
	}
	
#endif  // TSERVER_PREPARE

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server* pPS , BYTE buf[1024] , jServerInfo* si
		READ_PACKET_PS_BS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)




