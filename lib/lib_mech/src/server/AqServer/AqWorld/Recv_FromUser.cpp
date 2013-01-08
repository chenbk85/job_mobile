/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-07 11:47:27
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "network/protocal/PT_UserServer_Enum.h"
using namespace nUserServer;

#define send_server_W2DC_USER_LOGIN_DUPLICATE(server_name,sid,pUser)\
pServer= pFE->find_user(sid);\
if(!pServer)\
{\
	fname_t szBuf;\
	GetjILog()->Warning(jFUNC1 jS(server_name) _T("not found : %s"),ToString(pUser->Get_uid(), szBuf));\
}\
else\
{\
	pServer->Write_Packet(WRITE_W2DC_USER_LOGIN_DUPLICATE(buf,pUser->m_szID,pUser->Get_uid()) );\
}\

#define jSend_server_W2DC_USER_LOGIN_DUPLICATE(pUser)\
	AqConnectedServerNode* pServer;\
	send_server_W2DC_USER_LOGIN_DUPLICATE(DBCacheServer,pUser->Get_uid().m_dc_sid,pUser);\
	send_server_W2DC_USER_LOGIN_DUPLICATE(TownServer,pUser->Get_ConnectedServer(jServerInfo::eTown),pUser);\
	
	//send_server_W2DC_USER_LOGIN_DUPLICATE(DungeonServer,pUser->Get_ConnectedServer(jServerInfo::eDungeon),pUser);\


jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U_HELLO,UserServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		jSend_SS2server_ONLINE(U);

		// user 서버가 비정상종료 후 기동되면 현제 접속되어 uid를 가진 모든 유저정보를보낸다.
		#define jLAMDA_jxSend_W2U_ONLINE_USERS(X,Z) X(jIPacketSocket_IOCP*,pS) Z(S_W2U_ONLINE_USERS&,pk)
		jLAMDA_for_each(jxSend_W2U_ONLINE_USERS, jUserZoneInfo&)
		{
			if(it.m_uid.m_id==0) return;
			pk.uid.push_back(it.m_uid);
			pk.id.push_back(it.m_szID);
			pk.town.push_back(it.Get_ConnectedServer(jServerInfo::eTown));
			if(pk.uid.size()>100)
			{
				nswb16000_t buf;
				pS->WritePacket(&WRITE_W2U_ONLINE_USERS(buf,pk));
				pk = S_W2U_ONLINE_USERS();
			}
		}
		jLAMDA_end();

		S_W2U_ONLINE_USERS pk;
		jAUTO_LOCK_CS1(g_Users.m_CS);
		g_Users.for_each(jxSend_W2U_ONLINE_USERS(pS,pk));
	}

	bool server_tot_sort( AqConnectedServerNode*a, AqConnectedServerNode* b)
	{
		return a->m_E.Attr(jS(m_iTotClient))->Get_int() > b->m_E.Attr(jS(m_iTotClient))->Get_int();
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U2W_USER_LOGIN,UserServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(U2W_USER_LOGIN);

		jFE();
		jUserZoneInfo* pUser =0;
		{
			jAUTO_LOCK_CS1(g_Users.m_CS);
			pUser = g_Users.find_by_username(Data.id);
			if(pUser)
			{
				jSend_server_W2DC_USER_LOGIN_DUPLICATE(pUser);
				g_Users.erase(pUser);
			}
			pUser = g_Users.push_back_with_world_sid(Data.id,pBE->m_sid);
		}

		vector<AqConnectedServerNode*> servers;
		#define jLAMDA_jxGet_FreeDBCache(X,Z) Z(vector<AqConnectedServerNode*>&,servers)
		jLAMDA_for_each(jxGet_FreeDBCache,AqConnectedServerNode&)
		{
			if(it.Get_m_eType() != jServerInfo::eDBCache) return ;
			if(it.m_E.Attr(jS(m_iTotClient))->Get_int() >=it.Get_m_iMaxClient()) return ;
			servers.push_back(&it);
		}
		jLAMDA_end();
		pFE->for_each(jxGet_FreeDBCache(servers));
		if(!servers.size())
		{
			GetjILog()->Warning(jFUNC1 _T("pFE->for_each(jxGet_FreeDBCache()) db cache is not found"));
			//가용 db캐쉬없음.
			pS->WritePacket(&WRITE_W2U_USER_LOGIN_RESULT(buf, pUser->m_uid, jError(SR_t(FREE_DCServer_NOT_FOUND),CR_t(U2W_USER_LOGIN)),Data.id ) );
			return;
		}
		std::sort(servers.begin(),servers.end(),server_tot_sort);
		AqConnectedServerNode* pDB = servers.back();
		pDB->Write_Packet(WRITE_W2DC_USER_LOGIN(buf,pUser->m_uid , Data.id));
	}


	// dungeon , town ,user server로 부터 날라온다.
	jNET_EVENT_RECEIVER_P2P(U2W_USER_DISCONNECT,UserServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024], 
		be_READ_PACKET_P2P_PB(U2W_USER_DISCONNECT);

		jFE();
		pFE->Send_W2DC_USER_DISCONNECT(Data.id);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U2W_USER_LOGIN_DUPLICATE,UserServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(U2W_USER_LOGIN_DUPLICATE);
		jUserZoneInfo* pUser ;
		{
			jAUTO_LOCK_CS1(g_Users.m_CS);
			pUser = g_Users.find_by_username(Data.id);
		}
		if(!pUser) 
		{
			fname_t szBuf;
			GetjILog()->Warning(jFUNC1 _T("user not found : %s"),ToString(Data.uid, szBuf));
			pS->WritePacket(&WRITE_W2U_USER_LOGIN_DUPLICATE_OK(buf, Data.id ));
			return;
		}
		//dbcache쪽에 로그아웃을 보내고 데이타를 저장한후 다시 DC2W_USER_LOGIN_DUPLICATE_OK를 받으면 g_Users.erase_by_name(Data.id);를 호출
		pUser->SetFlag_IsDuplicated_so_GoingTo_Logout(true);
		jFE();
		jSend_server_W2DC_USER_LOGIN_DUPLICATE(pUser);
	}


#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,UserServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_ToBackEnd)



