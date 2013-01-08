/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"

jUserZoneList_W g_Users;

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqConnectedServerNode)
{

}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd)
{
	jAUTO_LOCK_CS1(g_Users.m_CS);
	g_Users.Clear();

}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqConnectedServerNode);

PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
{
}

bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCommand)
{
	//nswb1024_t buf;
	std::tstring str = _T("FromAqCentral:");
	str += szCommand;
	net_string256 sendStr = str.c_str();
	//jPacket_Base pk = nTestCentralServer::WRITE_TS_ECHO(buf, sendStr );
	//jIPacketSocket_IOCP* p =0;
	//send_all(&pk, p );	
	return false;
}

void jSocketDebugger(jIPacketSocket_IOCP* pS)
{

}


// CIocp의 가상함수들
serverid_t jSERVER_sid(){ return 0;jBE_ret(0);assert(pBE->m_sid);return pBE->m_sid;}
VOID PlugIn_ToFrontEnd::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromServer(W_HELLO);//AqConnectedServerNode* pServer;nswb256_t buf; fname_t szIP
}

VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //AqConnectedServerNode* pServer
	jLIST_TYPEDEF_map(AqConnectedServerNode*, id_list_t ,id_list_map);

	#define jLAMDA_jxGet_DisconnectUser(X,Z) X(AqConnectedServerNode*, pServer) Z(id_list_map_t&,id_list_map)
	jLAMDA_for_each(jxGet_DisconnectUser,jUserZoneInfo&)
	{
		if( it.Get_ConnectedServer(pServer->GetServerType()) == pServer->Get_sid())
		{
			it.Set_ConnectedServer(pServer->GetServerType() , 0);
		}
		if(!it.IsConnectedServer())
		{
			AqConnectedServerNode* pDB = PlugIn_ToFrontEnd::Get()->find_user(it.m_uid.m_dc_sid);
			id_list_map[pDB].push_back(it.m_szID);
		}
	}
	jLAMDA_end();

	{
		jAUTO_LOCK_CS1(g_Users.m_CS);
		g_Users.for_each(jxGet_DisconnectUser(pServer,id_list_map));
	}

	nswb16000_t buf;
	id_list_map_it it = id_list_map.begin(), ie = id_list_map.end();
	for(;it!=ie; ++it)
	{
		id_list_it it2= it->second.begin(), ie2=it->second.end();
		id_list_t vec;
		for(int i=1 ; it2!=ie2; ++it2 , ++i)
		{
			vec.push_back(*it2);
			if(i%100)
			{
				if(it->first)
					it->first->Write_Packet(WRITE_W2DC_USER_DISCONNECT(buf,vec));
				vec.clear();
			}
		}
	}
	erase(pServer);
}

AqConnectedServerNode* PlugIn_ToFrontEnd::FindServer_by_User(jUserZoneInfo *pUser ,jServerInfo::EServerType eType)
{
	return this->find_user(pUser->Get_ConnectedServer(eType));
}


void PlugIn_ToFrontEnd::Send_UserDisconnection(jUserZoneInfo * pUser,jServerInfo::EServerType eType, jError e, userid_t uid)
{
	AqConnectedServerNode* pServer= this->FindServer_by_User(pUser, eType);
	if(!pServer)
	{
		//GetjILog()->Warning(jFUNC1 _T("%s server not found : %d"),jServerInfo::GetServerTypeName(eType),sid);
		return ;
	}
	nswb256_t buf;
	pServer->Write_Packet(WRITE_W_ERROR(buf, e, 0, "",uid));

}


void PlugIn_ToFrontEnd::Send_W2DC_USER_DISCONNECT(vector<astring>& uids)
{
	jLIST_TYPEDEF_map(AqConnectedServerNode*,id_list_t,db_uid);

	{
		jAUTO_LOCK_CS1(g_Users.m_CS);
		for(int i=0; i< uids.size(); ++i)
		{
			acstr id = uids[i].c_str();
			jUserZoneInfo* pUser = g_Users.find_by_username(id);
			if(!pUser)
			{
				GetjILog()->Warning(jFUNC1 _T("user not found : %s"),id);
				continue;
			}
			userid_t uid = pUser->m_uid;
			g_Users.erase_by_name(id);
			AqConnectedServerNode* pDB = this->find_user(uid .m_dc_sid);
			if(!pDB)
			{
				fname_t buf;
				GetjILog()->Warning(jFUNC1 _T("db cache server not found id(%s)"),id);
				continue;
			}
			db_uid[pDB].push_back(id);
		}

	}
	if(db_uid.size())
	{
		nswb8000_t buf;
		db_uid_it it = db_uid.begin(), ie = db_uid.end();
		for( ; it!=ie ; ++it)
		{
			it->first->Write_Packet(WRITE_W2DC_USER_DISCONNECT(buf,it->second));
			GetjILog()->Log(_T("user disconnect count: %d"),it->second.size());
		}
	}

}

AqConnectedServerNode* PlugIn_ToFrontEnd::GetServerByUserZone(jUserZoneInfo*pUser,jServerInfo::EServerType eType)
{
	serverid_t townS=pUser->Get_ConnectedServer(eType);
	if(townS==0) return 0;
	return this->find_user(townS);
}