/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-07 11:47:27
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TWorld.h"
#include "../TCommonServer/jServerGrid_functor.h"

#define send_W2_USER_LOGIN_DUPLICATE(server_name,pPlayer)\
{\
	serverid_t sid = pPlayer->Get_Server(e##server_name);\
	if(sid)\
	{\
		jIGridNode* pGN=g_SG.SEND_PACKET_SID(sid,W2_USER_LOGIN_DUPLICATE , pPlayer->m_szID , pPlayer->m_pid );\
		if(!pGN){fname_t szBuf;jWARN("%s Server not found : %s",jS(server_name) ,ToString(pPlayer->m_pid, szBuf));}\
	}\
}\

#define send_all_W2_USER_LOGIN_DUPLICATE(pPlayer)\
	send_W2_USER_LOGIN_DUPLICATE(DBCache,pPlayer);\
	send_W2_USER_LOGIN_DUPLICATE(Channel,pPlayer);\
	send_W2_USER_LOGIN_DUPLICATE(Game,pPlayer);\


jNET_EVENT_BEGIN(PlugIn_Connect)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U2SS_ONLINE_OK,UserServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]

		// user ������ ���������� �� �⵿�Ǹ� ���� ���ӵǾ� uid�� ���� ��� ����������������.
		// �̶� channle������ ������. ���Ӽ��� ������ ����.
#define jLAMDA_send_W2U_ONLINE_USERS(X,Z) X(jIPacketSocket_IOCP*,pS) Z(S_W2U_ONLINE_USERS&,pk)
		jLAMDA_for_each(send_W2U_ONLINE_USERS, jPlayerBase*)
		{
			if(it->m_pid.m_id==0) return;
			pk.pid.push_back(it->m_pid);
			pk.id.push_back(it->m_szID);
			pk.town.push_back(it->Get_Server(eChannel));
			if(pk.pid.size()>100)
			{
				nswb16000_t buf;
				jNET_SEND(pS,W2U_ONLINE_USERS,pk);
				pk = S_W2U_ONLINE_USERS();
			}
		}
		jLAMDA_end();

		S_W2U_ONLINE_USERS pk;
		
		g_PL.for_each(send_W2U_ONLINE_USERS(pS,pk));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U2W_USER_LOGIN,UserServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(U2W_USER_LOGIN);

		jPS();
		jPlayerBase* pPlayer =0;
		pPlayer = g_PL.find(Data.id);
		if(pPlayer)
		{
			send_all_W2_USER_LOGIN_DUPLICATE(pPlayer);
			// DBCache�ʿ��� ����Ÿ �ε������Ϸ��� �뺸�ϸ� ��������.
			//g_PL.erase(pPlayer);
			jERROR("jTODO UserServer�� �뺸�ڵ��߰��Ұ�.")
			return;
		}
#ifdef TSERVER_PREPARE
		collect_sid_tot_t sid_tot;
		g_SG.m_DBCache.for_each(collect_free_server(sid_tot));
		if(!sid_tot.size())
		{
			jWARN("pPS->for_each(collect_free_server()) db cache is not found");
			//���� dbĳ������.
			jNET_SEND(pS,W2U_USER_LOGIN_RESULT, pPlayer->m_pid, jError(SR_t(FREE_DBCache_NOT_FOUND),CR_t(U2W_USER_LOGIN)),Data.id ) ;
			return;
		}
		std::sort(sid_tot.begin(),sid_tot.end(),server_tot_sort);
		serverid_t sid = sid_tot.back().first ;
		g_SG.m_DBCache.SEND_PACKET_SID(sid, W2DC_USER_LOGIN ,pPlayer->m_pid , Data.id);
#endif //TSERVER_PREPARE
	}


	// dungeon , channel ,user server�� ���� ����´�.
	jNET_EVENT_RECEIVER_P2P(U2W_USER_DISCONNECT,UserServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024], 
		READ_PACKET_PC_B(U2W_USER_DISCONNECT);

		jPS();
		pPS->Send_W2DC_USER_DISCONNECT(Data.id);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U2W_USER_LOGIN_DUPLICATE,UserServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(U2W_USER_LOGIN_DUPLICATE);
		jPlayerBase* pPlayer ;
		{
			
			pPlayer = g_PL.find(Data.id);
		}
		if(!pPlayer) 
		{
			fname_t szBuf;
			jWARN1(_T("user not found : %s"),ToString(Data.pid, szBuf));
			pS->WritePacket(&WRITE_W2U_USER_LOGIN_DUPLICATE_OK(buf, Data.id ));
			return;
		}
		//dbcache�ʿ� �α׾ƿ��� ������ ����Ÿ�� �������� �ٽ� DC2W_USER_LOGIN_DUPLICATE_OK�� ������ g_PL.erase_by_name(Data.id);�� ȣ��
		pPlayer->SetFlag_IsDuplicated_so_GoingTo_Logout(true);
		jPS();
		send_all_W2_USER_LOGIN_DUPLICATE(pPlayer);
	}


#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,UserServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_Connect)



