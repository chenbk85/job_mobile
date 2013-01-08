/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 13:27:24
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"

using namespace nNET::nCentralServer;


jSQ_REGIST_BIND(PLUGIN)
{
	jSQ_Interface(PlugIn_ToFrontEnd)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}



void _Job_LogCnange(nEVENT::jIMessage* pMsg)
{
	jFE();
	nswb256_t buf;
	pFE->send_all(WRITE_C2_LOG_FILE_DAY_CHANGE(buf) , 0);

}

void make_serverid_userCnt(PlugIn_ToFrontEnd::serverid_and_cnt_t& List,vector<serverid_t> &sid,vector<uint16> &userCnt)
{
	PlugIn_ToFrontEnd::serverid_and_cnt_it it = List.begin(), ie = List.end();
	for(;it!=ie;++it)
	{
		sid.push_back(it->first);
		userCnt.push_back(it->second);
	}
}

void _Job_C2_USER_CONNECTION_NOTIFY(nEVENT::jIMessage*)
{
	jFE();
	nswb8000_t buf;
	vector<serverid_t> sid;
	vector<uint16> userCnt;

	if(pFE->m_mapC2_USER_CONNECTION_NOTIFY_Town.size())
	{
		jAUTO_LOCK_CS1(pFE->m_mapC2_USER_CONNECTION_NOTIFY_CS_Town);
		make_serverid_userCnt(pFE->m_mapC2_USER_CONNECTION_NOTIFY_Town, sid, userCnt);
		pFE->Send_Packet_ToServers(jS(L), WRITE_C2_USER_CONNECTION_NOTIFY(buf,sid,userCnt));
		pFE->m_mapC2_USER_CONNECTION_NOTIFY_Town.clear();
	}
	if(pFE->m_mapC2_USER_CONNECTION_NOTIFY_Dungeon.size())
	{
		jAUTO_LOCK_CS1(pFE->m_mapC2_USER_CONNECTION_NOTIFY_CS_Dungeon);
		PlugIn_ToFrontEnd::m_mapC2_USER_CONNECTION_NOTIFY_Dungeon_it 
			it = pFE->m_mapC2_USER_CONNECTION_NOTIFY_Dungeon.begin(),
			ie = pFE->m_mapC2_USER_CONNECTION_NOTIFY_Dungeon.end();

		for(; it!=ie;++it)
		{
			make_serverid_userCnt(it->second,sid,userCnt);
			pFE->Send_Packet_InWorlds(it->first.c_str(), WRITE_C2_USER_CONNECTION_NOTIFY(buf,sid,userCnt),0);
		}
		pFE->m_mapC2_USER_CONNECTION_NOTIFY_Dungeon.clear();
	}


}

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqConnectedServerNode)
{
	nEVENT::jIMessage* pMsg = m_pMM->Regist_TimeBase(0,_Job_LogCnange, 0, pv_LOG_FILE_CHANGE_MINITE->Get_float()*60);
	pMsg->DoWakeUp();

	pMsg = m_pMM->Regist_TimeBase(0,_Job_C2_USER_CONNECTION_NOTIFY, 0, pv_C2_USER_CONNECTION_NOTIFY->Get_float());
	pMsg->DoWakeUp();

	m_eServers = GetjIXml()->CreateMemoryDoc(jS(AqConnectedServerNode));
	m_eServers->EraseChild();

}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd)
{

}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqConnectedServerNode);


PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
{
	g_pCurrPlugIn= this;
}
bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCmd)
{
	nswb1024_t buf;
	if(szCmd[0]=='~')
	{
#if 0
		jNoticeInfo info;
		jCLEAR(info);
		jPacket_Base pk = nCentralServer::WRITE_C2_NOTICE(buf, info ,jW(szCmd+1), "");
		this->for_each(jxSendToServers(pk,jServerInfo::eTown));
		this->for_each(jxSendToServers(pk,jServerInfo::eDungeon));
#endif
	}
	else
	{
		std::tstring str = _T("FromAqCentral : ");
		if(szCmd[0]=='$')
		{
			str = szCmd;
		}
		else
			str += szCmd;

		net_string256 sendStr = str.c_str();
		jPacket_Base pk = WRITE_C_ECHO(buf, jW(sendStr ));
		send_all(pk, 0);
	}
	return false;
}

void PlugIn_ToFrontEnd::Send_Packet_ToServers(const tstring& szClust, jPacket_Base& pk)
{
	#define send_ToServers234(name,idStart,TAG) this->for_each(jxSendToServers(pk,jServerInfo::e##name ,0));
	if(szClust==jS(ALL)){	this->send_all(pk,0);	return;	}
	if(jt_strstr(szClust.c_str(),jS(FRONT) ) ) {for_each_SERVER_TYPE_F(send_ToServers234);}
	if(jt_strstr(szClust.c_str(),jS(BACK) ) ){for_each_SERVER_TYPE_B(send_ToServers234);}

	#define send_byTag234(name,idStart,TAG) if(jt_strstr(szClust.c_str(),_T( #TAG ) ) )	this->for_each(jxSendToServers(pk,jServerInfo::e##name,0));
	for_each_SERVER_TYPE(send_byTag234);
}

void jSocketDebugger(jIPacketSocket_IOCP* pS)
{
	AqConnectedServerNode* pFServer = (AqConnectedServerNode*)pS->GetUserData();
	if(!pFServer || !pFServer->m_sid) return;
	GetjILog()->LogTime(_T("sid=%d"),pFServer->Base().Get_m_sid());
}

serverid_t jSERVER_sid(){ return 0;}
VOID PlugIn_ToFrontEnd::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromServer(C_HELLO);//AqConnectedServerNode* pServer;nswb256_t buf; fname_t szIP
}

VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //AqConnectedServerNode* pServer
	nswb256_t buf;
	this->send_all(WRITE_C_SERVER_OFFLINE(buf,pServer->Get_m_sid()) , pS );
	if(pServer->m_E.full())
	{
		pServer->m_E->Erase();
		pServer->m_E.clear();
	}

	erase(pServer);
}


void PlugIn_ToFrontEnd::Do_Disconnect_User(userid_t uid)
{
#if 0
	jUserZoneInfo* pUser = Find_User(uid);
	if(!pUser) return ;
	serverid_t lobby_sid = pUser->Get_ConnectedServer(jServerInfo::eTown);
	serverid_t room_sid = pUser->Get_ConnectedServer(jServerInfo::eDungeon);
	nswb256_t buf;
	if( lobby_sid )
	{
		AqConnectedServerNode* lobby= this->find_if(jxFindServer(lobby_sid));
		if(lobby)
		{
			//nLobbyServer::eSMT_ERROR, 

			lobby->Write_Packet(&WRITE_C2_DO_DISCONNECT_USER(buf, uid,eSMT_ERROR,jError(0,CR_t(GM_FORCE_USER_KICK))));
		}
	}
	if( room_sid )
	{
		AqConnectedServerNode* room= this->find_if(jxFindServer(room_sid));
		if(room)
		{
			room->Write_Packet(&WRITE_C2_DO_DISCONNECT_USER(buf, uid,eSMT_ERROR,jError(0,CR_t(GM_FORCE_USER_KICK) )));
		}
	}
#endif
}

void PlugIn_ToFrontEnd::Send_Packet_InWorlds(tcstr szWorld, jPacket_Base& pk,AqConnectedServerNode* pSkip)
{
	#define jLAMDA_jxSendToServerInWorld(X,Z) X(jPacket_Base&,pk) Z(AqConnectedServerNode*,pThis)
	jLAMDA_for_each(jxSendToServerInWorld,jIE*)
	{
		if(it->size()) return;
		AqConnectedServerNode* pServer = (AqConnectedServerNode*)it->GetUserData(jS(AqConnectedServerNode));
		if(!pServer) return;
		if(pThis==pServer) return;
		pServer->Write_Packet(pk);
	}
	jLAMDA_end();

	nXML::jE eWorldCluster = m_eServers[szWorld];
	if(eWorldCluster.empty())
	{
		GetjILog()->Warning(jFUNC1 _T("world (%s) not found"), szWorld);
		throw szWorld;
	}
	eWorldCluster->for_each(jxSendToServerInWorld(pk,pSkip));
}

