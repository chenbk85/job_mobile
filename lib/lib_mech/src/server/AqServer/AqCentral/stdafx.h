// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>



#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_C
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_C
#define jSERVER_NAME AqCentral
#define jsSERVER_NAME _T("AqCentral")

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "../AqCommon/AqCommon.h"


#include "../AqCommon/define_code_Server.h"
#include "../AqCommon/define_code_jBE.h"


#define _xmlid_LIST(X)\
	X(AqCentral)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(var_func)\
	\
	var_func(jSERVER_NAME,LOG_FILE_CHANGE_MINITE, 720.f, 0,"log file rename time (minite)")\
	var_func(jSERVER_NAME,C2_USER_CONNECTION_NOTIFY, 3.0f, 0,"server user tot count notify time (sec)")\
	


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);
