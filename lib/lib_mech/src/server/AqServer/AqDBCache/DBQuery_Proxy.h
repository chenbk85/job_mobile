/* file : DBQuery_Proxy.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 16:09:01
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __DBQuery_Proxy_4232332header__
#define __DBQuery_Proxy_4232332header__
#pragma once

#include "stdafx.h"
#include "../AqDBQuery/SharedMem.h"
#include "AqDBCacheUser.h"


//--------------------------------------------------------------------------
class DBQuery_Proxy
//--------------------------------------------------------------------------
{
public:
	DBQuery_Proxy();
	~DBQuery_Proxy();

	BOOL Begin();
	void WritePacket(nMech::nUtil::nSharedMem::jPacket_Base& pk);

	nMech::nUtil::nSharedMem::CSharedMemQueue m_SendQueue;
	nMech::nUtil::nSharedMem::CSharedMemQueue m_RecvQueue;
	HANDLE m_hReadQueueThread;


	nMech::nUtil::nSharedMem::CMemoryMap<jUserZoneInfo_DC> m_UsersSM;
	jLIST_TYPEDEF_vector(AqDBCacheUser, m_vecUsersSM);

	void DBQuery_Proxy::insertNode(jNamedEventNode* pT );
	jLIST_TYPEDEF_map(nMech::nNET::jPacketNum_t,_jDBEventNode*,m_mapjDBEventNode);

	AqDBCacheUser*	Going_to_Login(userid_t uid , username_t id);
	AqDBCacheUser*  Going_to_delete(acstr id);
	AqDBCacheUser*	find_by_yhandle(userid_t uid);
	AqDBCacheUser*	find_by_username(acstr id);

	void			Set_sid(serverid_t sid);
	void			erase_now(userid_t uid);
	AqDBCacheUser*  erase_now_by_username(acstr id);
};
extern DBQuery_Proxy g_Users_DC;

#endif // __DBQuery_Proxy_4232332header__
