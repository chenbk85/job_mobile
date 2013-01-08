/* file : Recv_FromLogin.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-03 13:46:47
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(L2U_USER_LOGIN)
	{
		// PlugIn_ToFrontEnd* pFE , BYTE buf[1024] , AqConnectedServerNode*pServer
		READ_PACKET_FromServer(L2U_USER_LOGIN);

		AqConnectedServerNode* pWorld = pFE->find_user(Data.world);
		if(!pWorld)
		{
			pServer->Write_Packet(WRITE_U2L_USER_LOGIN_RESULT(buf, userid_t(), Data.id , jError(SR_t(WORLD_SERVER_NOT_FOUND),CR_t(L2U_USER_LOGIN))));
			return;
		}
		assert( pWorld->Get_m_eType() == jServerInfoBase::eWorld);

		jAUTO_LOCK_CS1(g_Users.m_CS);
		jUserZoneInfo* pUser = g_Users.find_by_username(Data.id);
		if( pUser ) //NULL�̶�� ����� ������ �α�� id�� �ִٴ� ��.
		{
			if(pUser->GetFlag_GoingTo_Login())
			{
				pServer->Write_Packet(WRITE_U2L_USER_LOGIN_RESULT(buf, userid_t(), Data.id , jError(0,CR_t(USER_DUPLICATION_LOGIN))));
				return;
			}
			if(!pUser->GetFlag_IsDuplicated_so_GoingTo_Logout())
			{
				// �������� �ʰ� �����Ұ��̶�� ���弭���� �뺸�Ѵ�. g_Users.erase(pUser);
				// ���弭���ʿ��� �뺸�� ���� �׶� �����Ѵ�.
				pUser->SetFlag_IsDuplicated_so_GoingTo_Logout(true);

				pServer->Write_Packet(WRITE_U2L_USER_LOGIN_RESULT(buf, userid_t(), Data.id , jError(0,CR_t(USER_DUPLICATION_LOGIN))));
				pWorld = pFE->find_user( pUser->m_sid_world );
				if(pWorld)
				{
					pWorld->Write_Packet(WRITE_U2W_USER_LOGIN_DUPLICATE(buf,Data.id ,pUser->m_uid) );
				}
				else
				{
					jAssert0( 0 && "jTODO ��� ���弭���� ������ �ߺ������� ������ ������ �Ѵ�.");
				}
			}
			return;
		}

		pUser = g_Users.push_back_with_world_sid(Data.id,Data.world);
		pUser->Set_ConnectedServer(jServerInfoBase::eLogin , pServer->Get_sid() );
		pWorld->Write_Packet(WRITE_U2W_USER_LOGIN(buf, Data.id));
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
