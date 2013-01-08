// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#if 0
#define CentralServer_jNOTUSE_SQ_CODE
#define UserServer_jNOTUSE_SQ_CODE
#define WorldServer_jNOTUSE_SQ_CODE
#define DBCacheServer_jNOTUSE_SQ_CODE
#define DBQueryServer_jNOTUSE_SQ_CODE
#define LoginServer_jNOTUSE_SQ_CODE
#define MonitorServer_jNOTUSE_SQ_CODE
#define TestServer_jNOTUSE_SQ_CODE
#define GameServer_jNOTUSE_SQ_CODE
#endif

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define PlugIn_Server PlugIn_Server_CH
#define PlugIn_Connect PlugIn_Connect_CH
#define jSERVER_NAME TChannel
#define jsSERVER_NAME _T("TChannel")
#define jSERVER_TYPE jS(ChannelServer)
#define jPlayerObj	jPlayerObj_CH

#include "../TCommonServer/TCommonServer_header.h"

