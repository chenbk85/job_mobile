// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <SHELLAPI.H>
#include <mmsystem.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include "base/jBase.h"
using namespace std;
using namespace nMech;
#include "interface/xml/jIXml.h"
#include "interface/net/jTypedef_net.h"
#include "interface/net/jINet.h"
#include "interface/net/jINet_Util.h"
#include "header/nNET_Stream.h"
#include "interface/net/jDebugPrint.h"
#include "interface/net/jSQ_bind_jINet.h"
#include "interface/net/excel_code_util.h"
#include "Interface/jIConsoleDLL.h"
#include "interface/jIConsoleCmd.h"
#include "base/jMsgManager.h"
using namespace nMech::nNET;


#define PT_OrbHost_LIB_API 
#define jxDECL_OrbHost jxDECL
#define jxDEFINE_OrbHost jxDEFINE


#define _xmlid_LIST(X)\
	X(jOrb)\

_xmlid_LIST(jxDECL);


#define var_enum(var_func)\

	//var_func(jINet_OGS,OnPacketSize_UsageInfo_TIME, 20.f, 0,"time term of current packet usage info(SEC)")\

var_enum(jCV_DECLARE);

#include "jOrb.h"

