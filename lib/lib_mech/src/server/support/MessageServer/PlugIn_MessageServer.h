/* file : PlugIn_MessageServer.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-06-20 11:31:49
comp.: actoz.com
title : 
desc : 

*/

#ifndef __PlugIn_MessageServer_header__
#define __PlugIn_MessageServer_header__
#pragma once

#include "interface/net/jConnectUser.h"
#include "../common_TR/net_StringID.h"

typedef uint16 serverid_t;
struct jMsgClient
{
	jIPacketSocket_IOCP*m_pS;
	std::tstring m_sServerName;
public:

	virtual userid_t GetUID(){ return m_info.sid; }
	serverid_t GetServerID(){ return m_info.sid;}

	virtual cstr GetUserName(){return m_sServerName.c_str(); }
	tcstr GetServerName(){ return m_sServerName.c_str();}

	void jMsgClient::DebugPrint();

	virtual void Write_Packet(jPacket_Base* pk)
	{
		m_pS->WritePacket(pk);
	}
	jMsgClient::jMsgClient()
	{
		m_pS=0;
	}
};

class PlugIn_MessageServer: public jIPlugIn_Server_IOCP ,public jConnectUserManager<jMsgClient>
{
public:
	jDECLARE_RTTIOBJ(PlugIn_MessageServer);
	//JNET_PLUGIN_SINGTONE_DECL_FOR_USERS(PlugIn_MessageServer,jMsgClient,jIPacketSocket_IOCP*);
	JNET_PLUGIN_SINGTONE_DECL(PlugIn_MessageServer);
	virtual void Start();
	virtual void Stop();
	jLIST_TYPEDEF_map_typedef(jIPacketSocket_IOCP*, jMsgClient, m_ConnectUsers);

	VOID OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP)	
	{	
		GetjILogL()->Warning(_T("%s : %d "),__FUNCTION__ , pk->num);
	}
	virtual VOID OnIoWrote(jIPacketSocket_IOCP*pObject);
	virtual VOID OnIoConnected(jIPacketSocket_IOCP* pPlugIn);
	virtual VOID OnIoDisconnected(jIPacketSocket_IOCP*);

	PlugIn_MessageServer();
	virtual bool ParseCmd(tcstr szCommand);

	//--------------------------------------------------------------------------
	// logic code
	//--------------------------------------------------------------------------

};


struct _jxFindServer
{
	serverid_t sid;
	_jxFindServer(serverid_t s): sid(s){}
	bool operator()(jMsgClient* it)
	{
		if(it->GetServerID()==sid) return true;
		return false;
	}
};

#define jPLUGIN(pP) PlugIn_MessageServer*pP = PlugIn_MessageServer::Get();

#endif // __PlugIn_MessageServer_header__
