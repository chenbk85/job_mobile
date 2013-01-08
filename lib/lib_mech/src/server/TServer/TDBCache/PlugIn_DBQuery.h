/* file : PlugIn_DBQuery.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 16:09:01
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef PlugIn_DBQuery__DBQuery_Proxy_4232332header__
#define PlugIn_DBQuery__DBQuery_Proxy_4232332header__
#pragma once

#include "../TCommonClient/protocal/PT_DBQueryServer_Enum.h"
using namespace nMech::nNET::nDBQueryServer;

#include "jPlayerObj.h"

#include "header/MemoryMap.h"
#include "../TDBQuery/SharedMemQueue.h"


#define _ARG_jDBEventNode	BYTE* pReadBuff,nMech::nNET::jPacketLen_t dwLen,jIPacketSocket_IOCP* pS , class PlugIn_DBQuery*pDQ
struct _jDBEventNode{virtual void Call(_ARG_jDBEventNode)=0;};

#ifndef jDB_EVENT_RECEIVER
#define jDB_EVENT_RECEIVER(PROTOCAL) \
struct _jJOIN_2(jDBEvent_,PROTOCAL) : public _jDBEventNode {	_jJOIN_2(jDBEvent_,PROTOCAL)()\
{nMech::jBase::RegistNamedPointer(jS(jDBEvent),_T(#PROTOCAL),(_jDBEventNode*)this);	}	virtual void Call(_ARG_jDBEventNode);};\
	static _jJOIN_2(jDBEvent_,PROTOCAL) _jJOIN_2(g_jDBEvent_,PROTOCAL);	void _jJOIN_2(jDBEvent_,PROTOCAL)::Call(_ARG_jDBEventNode)
#endif


//--------------------------------------------------------------------------
class PlugIn_DBQuery
	//--------------------------------------------------------------------------
{
public:
	PlugIn_DBQuery();
	~PlugIn_DBQuery();

	BOOL Begin();
	void WritePacket(nUtil::nSharedMem::jPacket_Base* pk){WritePacket(*pk);}
	void WritePacket(nUtil::nSharedMem::jPacket_Base& pk);

	DWORD m_ProcessID;

	nUtil::nSharedMem::CSharedMemQueue m_SendQueue;
	nUtil::nSharedMem::CSharedMemQueue m_RecvQueue;
	HANDLE m_hReadQueueThread;

	nUtil::jMemoryMap<jPlayerDBSM> m_PlayersSM;

	void PlugIn_DBQuery::insertNode(jNamedEventNode* pT );
	jLIST_TYPEDEF_map(nMech::nNET::jPacketNum_t,_jDBEventNode*,m_mapjDBEventNode);

	void			Init_sid(serverid_t sid); // Central 에 접속후 sid를 발급받고 호출한다.

};
extern PlugIn_DBQuery g_DQ;



#endif // PlugIn_DBQuery__DBQuery_Proxy_4232332header__
