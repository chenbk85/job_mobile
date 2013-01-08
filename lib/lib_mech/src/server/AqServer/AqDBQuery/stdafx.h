// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#ifndef DBQueryServer_jNOTUSE_SQ_CODE
#define DBQueryServer_jNOTUSE_SQ_CODE
#endif

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_DQ
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_DQ
#define jSERVER_NAME AqDBQuery
#define jsSERVER_NAME _T("AqDBQuery")
#include "../AqCommon/AqCommon.h"


#define _xmlid_LIST(X)\
	X(AqQuery)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(var_func)\
	var_func(AqDBCache,WORLD_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\
	\
	var_func(AqDBCache,GAMEDB_NAME, _T("main_db_icandoit"), 0 , "odbc name")\
	var_func(AqDBCache,GAMEDB_ID, _T("sa"), 0 , "db id")\
	var_func(AqDBCache,GAMEDB_PWD, _T("qwer"), 0 , "db pwd")\
	\
	var_func(AqDBCache,SM_QUERY2CACHE_NAME, _T("AQ_QUERY2CACHE"), 0 , "query to cache queue name")\
	var_func(AqDBCache,SM_CACHE2QUERY_NAME, _T("AQ_CACHE2QUERY"), 0 , "cache to query queue name")\
	var_func(AqDBCache,SM_USER_INFO_NAME, _T("jUserZoneInfo_DC"), 0 , "user info shared memory name")\
	\
	var_func(AqDBCache,SM_QUEUE_MAX_COUNT, 4096, 0 , "QUERY,CACHE QUEUE SIZE")\
	var_func(AqDBCache,SM_USER_MAX, 3000, 0 , "SHARED MEMORY USER INFO max count")\
	
	

var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);

class Aq_NetDLL;
#define _ARG_jDBEventNode		Aq_NetDLL* pDLL, BYTE* pReadBuff, jPacketNum_t dwLen,jIPacketSocket_IOCP* pS

struct _jDBEventNode{	virtual void Call(_ARG_jDBEventNode)=0;};
extern void _jRegistNamedPointer(int, _jDBEventNode*);

#ifndef jDBQ_EVENT_RECEIVER
#define jDBQ_EVENT_RECEIVER(PROTOCAL) \
struct _jJOIN_2(jDBQEvent_,PROTOCAL) : public _jDBEventNode \
{	_jJOIN_2(jDBQEvent_,PROTOCAL)(){ _jRegistNamedPointer(nMech::nNET::nDBQueryServer::PROTOCAL,this);}\
	virtual void Call(_ARG_jDBEventNode);};	static _jJOIN_2(jDBQEvent_,PROTOCAL) _jJOIN_2(g_jDBEvent_,PROTOCAL);\
	void _jJOIN_2(jDBQEvent_,PROTOCAL)::Call(_ARG_jDBEventNode)
#endif



#define db_code_start() jError e;try {

#define db_code_end() \
}catch(jError ee)\
{\
	e = ee;\
	tname1024_t szBuf;\
	GetjILog()->Warning(jFUNC1 _T(" jError db error : %s"), e.ToString(szBuf) );\
}\
	catch(...) { \
	e = jError(SR_t(SQL_TITLE_INSERT_QUERY_ERR),0);\
	tname1024_t szBuf;\
	GetjILog()->Warning(jFUNC1 _T(" jError db error : %s"), e.ToString(szBuf) );\
}\

#define db_code_end_auto(error_send_type) db_code_end();\
if(e.isError())\
{\
	pDLL->WritePacket(WRITE_DQ_ERROR(buf,e,error_send_type, __FUNCTION__,Data.uid));\
	return;\
}\

