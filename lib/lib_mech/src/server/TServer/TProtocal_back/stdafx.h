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
#include "base/jBase.h"
#include "interface/jIConsoleVar.h"
#include "interface/xml/jIXml.h"
#include "interface/net/jTypedef_net.h"
#include "interface/net/jINet.h"
#include "interface/net/jINet_Util.h"
#include "interface/net/excel_code_util.h"

using namespace std;
using namespace nMech;

#include "../TExcelData/TExcelData.h"

#ifndef SQPLUS_CONST_OPT
#define SQPLUS_CONST_OPT
#endif
#include "base/jSQ_bind.h"
#include "interface/net/jSQ_bind_jINet.h"
#include "../TCommonClient/TServerClient_CommonHeader.h"
#include "../TCommonClient/net_SQ_client.h"

#define T_SERVER_LIB_API
#include "../TCommonServer/jServerInfo.h"
#include "../TCommonServer/net_SQ_Server.h"

#include "TProtocal_back.h"

