/* file : PlugIn_Server.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TWorld.h"

jPLUGIN_CPP_CODE_START_Server(PlugIn_Server)
{
}
jPLUGIN_CPP_CODE_STOP(PlugIn_Server)
{

}
jPLUGIN_CPP_CODE_END_Server(PlugIn_Server);

PlugIn_Server::PlugIn_Server()
{
}

bool PlugIn_Server::ParseCmd(tcstr szCommand)
{
	jPS_COMMON_ParseCmd(W);
}

// CIocp의 가상함수들
serverid_t jSERVER_sid(){ return 0;jPC_ret(0);assert(g_SG.m_MyInfo.m_sid);return g_SG.m_MyInfo.m_sid;}
VOID PlugIn_Server::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromServer(W_HELLO);// jIGridNode* pGN, szIP,nswb256_t buf
}

#define jLAMDA_send_W2DC_USER_DISCONNECT(X,Z) X(nswb16000_t&,buf) X(serverid_t,db_sid) Z(wstrings_t&,names)
jLAMDA_find_if(send_W2DC_USER_DISCONNECT,jIGridNode*)
{
	jSI_ret(it,false);
	if(si->m_sid != db_sid) return false;

	wstrings_it it2= names.begin(), ie2=names.end();
	wstrings_t vec;
	for(int i=1 ; it2!=ie2; ++it2 , ++i)
	{
		vec.push_back(*it2);
		if(i%100)
		{
#ifdef TSERVER_PREPARE
			jNET_SEND(it,W2DC_USER_DISCONNEC,vec);
#endif 
			vec.clear();
		}
	}
	return true;
}
jLAMDA_end();


VOID PlugIn_Server::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //jIGridNode* pGN ,jServerInfo* si ,jServerInfo* si

	typedef serverid_t db_cache_serverid_t;
	jLIST_TYPEDEF_map(db_cache_serverid_t, wstrings_t ,idList_per_DC);

	#define jLAMDA_collect_DisconnectUser(X,Z) X(EServerType,eType) X(serverid_t ,sid) Z(idList_per_DC_t&,idList_per_DC)
	jLAMDA_for_each(collect_DisconnectUser,jPlayerBase*)
	{
		if( it->Get_Server(eType) == sid) // pS(접속이 끊기는 서버에 접속해 있는유저들이면
		{
			it->Set_Server(eType, 0); // 접속끊은걸로 표시.
		}
		if(!it->IsConnectedServer()) // 접속한 서버가 없으면 DC에 유저 offline으로 통보하기위해 세팅
		{
			idList_per_DC[it->m_pid.m_dc_sid].push_back(it->m_szID);
		}
	}
	jLAMDA_end();

	g_PL.for_each(collect_DisconnectUser(si->m_eType, si->m_sid , idList_per_DC));

	nswb16000_t buf;
	idList_per_DC_it it = idList_per_DC.begin(), ie = idList_per_DC.end();
	for(;it!=ie; ++it)
	{
		g_SG.m_DBCache.find_if(send_W2DC_USER_DISCONNECT(buf,it->first,it->second));
	}

}


void PlugIn_Server::Send_W2DC_USER_DISCONNECT(wstrings_t& pids)
{

	typedef serverid_t db_cache_serverid_t;
	jLIST_TYPEDEF_map(db_cache_serverid_t, wstrings_t ,idList_per_DC);
	for(size_t i=0; i< pids.size(); ++i)
	{
		player_name_ct id = pids[i].c_str();
		jPlayerBase* pPlayer = g_PL.find(id);
		if(!pPlayer)
		{
			jWARN("user not found : %s",id);
			continue;
		}
		// g_PL에서 해당 유저 삭제는 DC2W로 통보가온후 한다.
		player_id_t pid = pPlayer->m_pid;
		idList_per_DC[pid.m_dc_sid].push_back(id);
	}
	nswb16000_t buf;
	idList_per_DC_it it = idList_per_DC.begin(), ie = idList_per_DC.end();
	for(;it!=ie; ++it)
	{
		g_SG.m_DBCache.find_if(send_W2DC_USER_DISCONNECT(buf,it->first,it->second));
	}

}
