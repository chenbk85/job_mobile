/* file : PlugIn_Server.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TCentral.h"
#include "PlugIn_Server.h"



jSQ_REGIST_BIND(PlugIn_Server)
{
	jSQ_Interface(PlugIn_Server)
	jSQ_end();
}


void make_serverid_userCnt(PlugIn_Server::serverid_and_cnt_t& List,vector<serverid_t> &sid,vector<uint16> &userCnt)
{
	PlugIn_Server::serverid_and_cnt_it it = List.begin(), ie = List.end();
	for(;it!=ie;++it)
	{
		sid.push_back(it->first);
		userCnt.push_back(it->second);
	}
}


void _Job_LogFIle_Change(nEVENT::jIMessage* pMsg)
{
	nswb256_t buf;
	g_SG.WritePacket(WRITE_C2_LOG_FILE_DAY_CHANGE(buf) , 0);

}

void _Job_C2_USER_CONNECTION_NOTIFY(nEVENT::jIMessage*)
{
	jPS();
	nswb8000_t buf;
	vector<serverid_t> sid;
	vector<uint16> userCnt;

	if(pPS->m_mapC2_USER_CONNECTION_NOTIFY_Channel.size())
	{
		jAUTO_LOCK_CS1(pPS->m_mapC2_USER_CONNECTION_NOTIFY_CS_Channel);
		make_serverid_userCnt(pPS->m_mapC2_USER_CONNECTION_NOTIFY_Channel, sid, userCnt);
		g_SG.m_Login.WritePacket(WRITE_C2_USER_CONNECTION_NOTIFY(buf,sid,userCnt));
		pPS->m_mapC2_USER_CONNECTION_NOTIFY_Channel.clear();
	}
	if(pPS->m_mapC2_USER_CONNECTION_NOTIFY_Game.size())
	{
		jAUTO_LOCK_CS1(pPS->m_mapC2_USER_CONNECTION_NOTIFY_CS_Game);
		PlugIn_Server::m_mapC2_USER_CONNECTION_NOTIFY_Game_it 
			it = pPS->m_mapC2_USER_CONNECTION_NOTIFY_Game.begin(),
			ie = pPS->m_mapC2_USER_CONNECTION_NOTIFY_Game.end();

		for(; it!=ie;++it)
		{
			make_serverid_userCnt(it->second,sid,userCnt);

			#define jLAMDA_send_to_world(X,Z) X(jPacket_Base&,pk) Z(tcstr ,world) 
			jLAMDA_for_each(send_to_world,jIGridNode*)
			{
				jSI(it);
				if(jt_strcmp(si->m_szDomain, world)) return;
				it->WritePacket(pk);
			}
			jLAMDA_end();

			g_SG.for_each(send_to_world(WRITE_C2_USER_CONNECTION_NOTIFY(buf,sid,userCnt), it->first.c_str() ) );
		}
		pPS->m_mapC2_USER_CONNECTION_NOTIFY_Game.clear();
	}

}

jPLUGIN_CPP_CODE_START_Server(PlugIn_Server)
{
	nEVENT::jIMessage* pMsg = m_pMM->Regist_TimeBase(0,_Job_LogFIle_Change, 0, pv_LOG_FILE_CHANGE_MINITE->Get_float()*60);
	pMsg->DoWakeUp();
	pMsg = m_pMM->Regist_TimeBase(0,_Job_C2_USER_CONNECTION_NOTIFY, 0, pv_C2_USER_CONNECTION_NOTIFY->Get_float());
	pMsg->DoWakeUp();

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
	nswb1024_t buf;
	if(szCommand[0]=='~')
	{
#if 0
		jNoticeInfo info;
		jCLEAR(info);
		jPacket_Base pk = nCentralServer::WRITE_C2_NOTICE(buf, info ,jW(szCommand+1), "");
		this->for_each(jxSendToServers(pk,eChannel));
		this->for_each(jxSendToServers(pk,eGame));
#endif
		return false;
	}
	else if(szCommand[0]=='$')
	{
		g_SG.WritePacket(WRITE_C_ECHO(buf, szCommand, 0));
		return true;
	}

	jPS_COMMON_ParseCmd(C);
}

// CIocp의 가상함수들
VOID PlugIn_Server::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromServer(C_HELLO);// jIGridNode* pGN, szIP,nswb256_t buf

}


VOID PlugIn_Server::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //jIGridNode* pGN ,jServerInfo* si ,jServerInfo* si
	nswb256_t buf;
	g_SG.WritePacket(WRITE_C_SERVER_OFFLINE(buf,si->m_sid) , pS );
}

#ifdef TSERVER_PREPARE

void PlugIn_Server::Do_Disconnect_User(player_id_t uid)
{
#if 0
	jPlayerBase* pUser = Find_User(uid);
	if(!pUser) return ;
	serverid_t lobby_sid = pUser->Get_Server(eChannel);
	serverid_t room_sid = pUser->Get_Server(eGame);
	nswb256_t buf;
	if( lobby_sid )
	{
		jIGridNode* lobby= this->find_if(jxFindServer(lobby_sid));
		if(lobby)
		{
			//nLobbyServer::eSMT_ERROR, 

			lobby->Write_Packet(&WRITE_C2_DO_DISCONNECT_USER(buf, uid,eSMT_ERROR,jError(0,CR_t(GM_FORCE_USER_KICK))));
		}
	}
	if( room_sid )
	{
		jIGridNode* room= this->find_if(jxFindServer(room_sid));
		if(room)
		{
			room->Write_Packet(&WRITE_C2_DO_DISCONNECT_USER(buf, uid,eSMT_ERROR,jError(0,CR_t(GM_FORCE_USER_KICK) )));
		}
	}
#endif
}

void PlugIn_Server::Send_Packet_InWorlds(tcstr szWorld, jPacket_Base& pk,jIGridNode* pSkip)
{
#define jLAMDA_jxSendToServerInWorld(X,Z) X(jPacket_Base&,pk) Z(jIGridNode*,pThis)
	jLAMDA_for_each(jxSendToServerInWorld,jIE*)
	{
		if(it->size()) return;
		jIGridNode* pServer = (jIGridNode*)it->GetUserData(jS(jIGridNode));
		if(!pServer) return;
		if(pThis==pServer) return;
		pServer->Write_Packet(pk);
	}
	jLAMDA_end();

	nXML::jE eWorldCluster = m_eServers[szWorld];
	if(eWorldCluster.empty())
	{
		jWARN1(_T("world (%s) not found"), szWorld);
		throw szWorld;
	}
	eWorldCluster->for_each(jxSendToServerInWorld(pk,pSkip));
}

#endif