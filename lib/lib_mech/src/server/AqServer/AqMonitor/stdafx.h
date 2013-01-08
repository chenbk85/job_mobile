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
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_TM
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_TM
#define jSERVER_NAME AqMonitor
#define jsSERVER_NAME _T("AqMonitor")
#include "../AqCommon/AqCommon.h"


#define _xmlid_LIST(X)\
	X(AqMonitor)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Connection *g_pCurrPlugIn;


#define var_enum(var_func)\

//var_func(ServerSetting,USER_CERT_SKIP, 1, 0,"is user cert skip ?")\


var_enum(jCV_DECLARE);



#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
#include "network/protocal/PT_TestServer_Enum.h"
using namespace nMech::nNET::nTestServer;

#include "../AqCommon/define_code_jFE.h"
#include "../AqCommon/define_code_Server.h"

#include "PlugIn_ToBackEnd.h"

