/* file : PlugIn_ToBackEnd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:11
comp.: wiki.test.com
title : 
desc : 

*/

#ifndef __PlugIn_ToBackEnd_header__
#define __PlugIn_ToBackEnd_header__
#pragma once


class PlugIn_ToBackEnd : public jIPlugIn_Net_SQ<PlugIn_ToBackEnd,jIPlugIn_Connection > 
{
public:
	~PlugIn_ToBackEnd();
	jPLUGIN_header_code(PlugIn_ToBackEnd)
	virtual int Get_CURR_USER(){return 0;};
	virtual tcstr GetPlugInNicName()
	{ 
		return _T("PlugIn_net_agent");
	}

	jIPacketSocket_IOCP* m_pS_MonitorServer;
	nEVENT::jIMessage* m_pReconnecterToMonitor;
	nEVENT::jIMessage* m_pM_Process_live_Check;


	int m_iRetryCount;
	dummy_id_t m_did; // 서버에서 받은 식별자.
	void TryReconnect();
	void ResetReconnect();

};

DECLARE_INSTANCE_TYPE(PlugIn_ToBackEnd);

extern PlugIn_ToBackEnd* g_pCurrPlugIn;

#define jMsg_ERASE(p)if(p){p->Erase();p=0;}

void SendToMonitor_ServerInfo(const wstring& sServerType,nSM::jServerInfo& si,wcstr sz,bool isSendConnected);
#endif // __PlugIn_ToBackEnd_header__
