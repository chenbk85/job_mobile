// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#define CentralServer_jNOTUSE_SQ_CODE
#define UserServer_jNOTUSE_SQ_CODE
#define WorldServer_jNOTUSE_SQ_CODE
#define DBCacheServer_jNOTUSE_SQ_CODE
#define DBQueryServer_jNOTUSE_SQ_CODE
#define LoginServer_jNOTUSE_SQ_CODE
#define MonitorServer_jNOTUSE_SQ_CODE
#define TestServer_jNOTUSE_SQ_CODE
#define DungeonServer_jNOTUSE_SQ_CODE


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_T
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_T
#define jSERVER_NAME AqTown
#define jsSERVER_NAME _T("AqTown")
#include "../AqCommon/AqCommon.h"


#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
#include "network/protocal/PT_TownServer_Enum.h"
using namespace nMech::nNET::nTownServer;
#include "network/protocal/PT_DungeonServer_Enum.h"
using namespace nMech::nNET::nDungeonServer;
#include "network/protocal/PT_DBCacheServer_Enum.h"
using namespace nMech::nNET::nDBCacheServer;

#include "network/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;

#include "PlugIn_ToBackEnd.h"
#include "PlugIn_ToFrontEnd.h"

#include "../AqCommon/define_code_jFE.h"
#include "../AqCommon/define_code_Server.h"


#define _xmlid_LIST(X)\
	X(AqTown)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(var_func)\
	var_func(AqTown,WORLD_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\
	var_func(AqTown,C4_USER_CONNECTION_NOTIFY, 3.0f, 0 , "C4_USER_CONNECTION_NOTIFY send term (sec)")\



var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);

bool jCheck_ObjName(wcstr szName);

//이름이 규칙에 어긋납니다. 두자 이상!
#define pUser_Check_make_name(name)\
if(!jCheck_ObjName(name))\
{\
	pS_eSEND_jError_ToClient(T,SR_t(OBJ_NAME_LEN_ERROR),CR_t(jCheck_ObjName));\
	return;\
}\



#define jUSER_ERROR_CHECK(condition,SR,CR) if((condition)){	pS_eSEND_jError_ToClient(T,SR_t(SR),CR_t(CR));	return;		}
