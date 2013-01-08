/* file : PlugIn_DBCache.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:37
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __P123l4u56gI65789n09_Se67e8r76_header__
#define __P123l4u56gI65789n09_Se67e8r76_header__
#pragma once

#include "Interface/db/jIDB.h"
#include "header/jODBC_Util.h"
#include "header/MemoryMap.h"
#include "jPlayerDBSM.h"

class PlugIn_DBCache;
#define _ARG_jDBEventNode		PlugIn_DBCache* pDC, BYTE* pReadBuff, jPacketNum_t dwLen,jIPacketSocket_IOCP* pS

struct _jDBEventNode{	virtual void Call(_ARG_jDBEventNode)=0;};
extern void _jRegistNamedPointer(int, _jDBEventNode*);

#ifndef jDBQ_EVENT_RECEIVER
#define jDBQ_EVENT_RECEIVER(PROTOCAL) \
struct _jJOIN_2(jDBQEvent_,PROTOCAL) : public _jDBEventNode \
{	_jJOIN_2(jDBQEvent_,PROTOCAL)(){ _jRegistNamedPointer(nMech::nNET::nDBQueryServer::PROTOCAL,this);}\
	virtual void Call(_ARG_jDBEventNode);};	static _jJOIN_2(jDBQEvent_,PROTOCAL) _jJOIN_2(g_jDBEvent_,PROTOCAL);\
	void _jJOIN_2(jDBQEvent_,PROTOCAL)::Call(_ARG_jDBEventNode)
#endif



#define jDB_CODE_START() 	WCHAR szSQL[2048];szSQL;jError e;try {

#define jDB_CODE_END() \
}catch(jError ee)\
{e = ee;	tname1024_t szBuf;jWARN(" jError db error : %s", e.ToString(szBuf) );}\
catch(...) { \
	e = jError(SR_t(SQL_TITLE_INSERT_QUERY_ERR),0);\
	tname1024_t szBuf;jWARN(" jError db error : %s", e.ToString(szBuf) );\
}\

#define jDB_CODE_END_AUTO(eAction) jDB_CODE_END();\
	if(e.isError()){jNET_SEND2(g_PS,DQ_ERROR,jErrorInfo(e,eAction, __FUNCTION__,Data.pid ) );}




#define for_each_excel_file_list(X)\
	X(sam_user)\
	X(sam_castle)\
	X(sam_force)\
	X(sam_hero)\


class PlugIn_DBCache
{
public:
	DWORD m_ProcessID;
	nUtil::nSharedMem::CSharedMemQueue m_SendQueue;
	nUtil::nSharedMem::CSharedMemQueue m_RecvQueue;
	nUtil::jMemoryMap<jPlayerDBSM> m_PlayersSM;

	BOOL WritePacket(jPacket_Base &pk)
	{
		m_SendQueue.WritePacket(pk);
		return TRUE;
	}
	int m_isQuit;
	HANDLE m_hThread_run_dq;

	jPlayerDBSM* find(player_id_t pid){ return m_PlayersSM.at(pid.m_dc_handle);}

	void StartServer();
	void EndServer();

};
extern PlugIn_DBCache g_PS;
extern nMech::nDB::jIDB*	g_pDB;


#endif // __P123l4u56gI65789n09_Se67e8r76_header__
