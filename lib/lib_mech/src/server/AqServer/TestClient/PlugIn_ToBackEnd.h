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
#include "jDummy.h"
#include "header/jBoost.h"


class PlugIn_ToBackEnd : public jIPlugIn_Net_SQ<PlugIn_ToBackEnd,jPlugIn_BE_Helper > 
{
public:
	jPLUGIN_BACK_END_header_code(PlugIn_ToBackEnd);

	jLIST_TYPEDEF_YVECTOR(jDummyPlayer,m_listDummy);
	nUtil::jCriticalSection m_listDummy_CS;

	virtual tcstr GetPlugInNicName()
	{ 
		return _T("PlugIn_TestClient");
	}

	// *_* by icandoit : 2008-06-24 18:52:42
	// logic code 
public:
#define for_each_PT_MEMEBER(func)\
	func(nTestServer,TS_HELLO)\

	for_each_PT_MEMEBER(jPT_MEMBER);

	dummy_id_t GetDummyID(){ return m_TS_HELLO.did;}//테스트 서버로부터 부여받은 더미클라이언트 아이디, DUMMY아이디(userdb_id_t)와 다름
	tcstr GetTestIDName(){ return m_TS_HELLO.test_id_name;}
	fname_t m_DummyName;
	bool m_isEnable;
	jIPacketSocket_IOCP* m_pS_TestServer;
	nEVENT::jIMessage* m_pMsg_Chat;
	HANDLE m_hThread;

	void Logout_Dummy_AllSocket(int per_user , DWORD delay );
	void ConnectToLoginServer_AllDummy(int session_count_for_delay ,int delay_time_msec);

	jDummyPlayer* CreateDummyUser(acstr szID);
	jDummyPlayer* FindDummyUser(acstr szID);
	jDummyPlayer* GetDummyUser(jIPacketSocket_IOCP* pS);
	bool RunDummyFunction(tcstr szID, boost::function<void (jDummyPlayer& pUser,DWORD delay_msec)> func ,DWORD delay_msec);
	jIPacketSocket_IOCP* GetUserSocket(acstr szID , jServerInfo::EServerType eType, jDummyPlayer** ppDummy);

};

DECLARE_INSTANCE_TYPE(PlugIn_ToBackEnd);


extern PlugIn_ToBackEnd* g_pCurrPlugIn;


#endif // __PlugIn_ToBackEnd_header__
