// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_DC
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_DC
#define jSERVER_NAME AqDBCache
#define jsSERVER_NAME _T("AqDBCache")

#include "../AqCommon/AqCommon.h"


#define _xmlid_LIST(X)\
	X(AqDBCache)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(var_func)\
	var_func(AqDBCache,WORLD_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\
	\
	var_func(AqDBCache,SM_QUERY2CACHE_NAME, _T("AQ_QUERY2CACHE"), 0 , "query to cache queue name")\
	var_func(AqDBCache,SM_CACHE2QUERY_NAME, _T("AQ_CACHE2QUERY"), 0 , "cache to query queue name")\
	var_func(AqDBCache,SM_USER_INFO_NAME, _T("jUserZoneInfo_DC"), 0 , "user info shared memory name")\
	\
	var_func(AqDBCache,SM_QUEUE_MAX_COUNT, 4096, 0 , "QUERY,CACHE QUEUE SIZE")\
	var_func(AqDBCache,SM_USER_MAX, 3000, 0 , "SHARED MEMORY USER INFO max count")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);



#include "../AqDBQuery/SharedMem.h"

class DBQuery_Proxy;
#define _ARG_jDBEventNode	BYTE* pReadBuff,nMech::nNET::jPacketLen_t dwLen,jIPacketSocket_IOCP* pS , DBQuery_Proxy*pDQ

struct _jDBEventNode
{
	virtual void Call(_ARG_jDBEventNode)=0;
};

#ifndef jDB_EVENT_RECEIVER
#define jDB_EVENT_RECEIVER(PROTOCAL) \
struct _jJOIN_2(jDBEvent_,PROTOCAL) : public _jDBEventNode {	_jJOIN_2(jDBEvent_,PROTOCAL)()\
{nMech::jBase::RegistNamedPointer(jS(jDBEvent),_T(#PROTOCAL),(_jDBEventNode*)this);	}	virtual void Call(_ARG_jDBEventNode);};\
	static _jJOIN_2(jDBEvent_,PROTOCAL) _jJOIN_2(g_jDBEvent_,PROTOCAL);	void _jJOIN_2(jDBEvent_,PROTOCAL)::Call(_ARG_jDBEventNode)
#endif

//jGet_DBUser(Data.uid,pS); //AqDBCacheUser* pUser
#define jGet_DBUser(uid,pS)\
AqDBCacheUser* pUser= g_Users_DC.find_by_yhandle(uid);\
if(!pUser)\
{\
	fname_t szBuf;\
	GetjILog()->Warning(jFUNC1 _T("uid is wrong : %s"), ToString(uid,szBuf));\
	jError e(SR_t(SQL_INV_SFKIND_QUERY_ERR),0);\
	if(pS)pS->WritePacket(&WRITE_DC_ERROR(buf,e,eSEND_jError_ToClient,__FUNCTION__,uid));\
	jBE();\
	pBE->m_pToWorld->WritePacket(&WRITE_W_ERROR(buf,e,eSEND_Disconn_User,__FUNCTION__,uid));\
	return;\
}\


#define jGet_DBUser_byName(id,uid,pS)\
	AqDBCacheUser* pUser= g_Users_DC.find_by_username(id);\
	if(!pUser)\
{\
	fname_t szBuf;\
	GetjILog()->Warning(jFUNC1 _T("uid is wrong : %s"), id);\
	jError e(SR_t(SQL_INV_SFKIND_QUERY_ERR),0);\
	if(pS)pS->WritePacket(&WRITE_DC_ERROR(buf,e,eSEND_jError_ToClient,__FUNCTION__,uid));\
	jBE();\
	pBE->m_pToWorld->WritePacket(&WRITE_W_ERROR(buf,e,eSEND_Disconn_User,__FUNCTION__,uid));\
	return;\
}\

// jTODO jError pS->WritePacket(&WRITE_DC_ERROR(buf,jError(SR_t(SQL_INV_SFKIND_QUERY_ERR),0),0,""));\



// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode* pServer , AqDBCacheUser* pUser
#define READ_PACKET_FromServer_UID(X)READ_PACKET_FromServer(X);jGet_DBUser(Data.uid,pS);


#include "DBQuery_Proxy.h"
#include "AqDBCacheUser.h"

#include "PlugIn_ToFrontEnd.h"
#include "PlugIn_ToBackEnd.h"

#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
#include "network/protocal/PT_DBCacheServer_Enum.h"
using namespace nMech::nNET::nDBCacheServer;

#include "network/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;

#include "../AqCommon/define_code_jBE.h"
#include "../AqCommon/define_code_Server.h"
