/* file : PlugIn_ToBackEnd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:11
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_ToBackEnd_header__
#define __PlugIn_ToBackEnd_header__
#pragma once


#include "../AqCommon/net_StringID.h"


class PlugIn_ToBackEnd : public jIPlugIn_Net_SQ<PlugIn_ToBackEnd,jIPlugIn_Connection > 
{
public:
	jDECLARE_RTTIOBJ(PlugIn_ToBackEnd);
	JNET_PLUGIN_SINGTONE_DECL(PlugIn_ToBackEnd);

	PlugIn_ToBackEnd();
	virtual void Start();
	virtual void Stop();
	virtual bool ParseCmd(tcstr szCommand);



	// Ŭ���̾�Ʈ�� ���� �����Ǿ����� ȣ��Ǵ� �����Լ�
	VOID OnIoConnected(jIPacketSocket_IOCP*);
	// Ŭ���̾�Ʈ�� ���� ����Ǿ����� ȣ��Ǵ� �����Լ�
	VOID OnIoDisconnected(jIPacketSocket_IOCP*);
	VOID OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP);

	// *_* by icandoit : 2008-06-24 18:52:42
	// logic code 
public:

	jIPacketSocket_IOCP* m_pToCentral;
	serverid_t m_sid;
	jServerInfoCache m_LobbyServers;
	nUtil::jCriticalSection m_LobbyServers_CS;
	bool IsReady_LogginServer()// �α伭���� �����α�ó���� ���� ���� ������ �����غ� �Ȱ����� ���� �Ǵ�.
	{
		return m_LobbyServers.m_servers.size();
	}

};

DECLARE_INSTANCE_TYPE(PlugIn_ToBackEnd);


#endif // __PlugIn_ToBackEnd_header__
