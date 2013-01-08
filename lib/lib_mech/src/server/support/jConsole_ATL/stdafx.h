// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.
//

#pragma once

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#include <atlbase.h>
#include <atlapp.h>

#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlstr.h>

#include <list>

#include "common/jCommon.h"
#include "interface/net/jINet.h"
#include "interface/jIConsoleDLL.h"
#include "header/jDllLoader.h"
#include "interface/jIConsoleDlg.h"
#include "interface/jIConsoleCmd.h"


using namespace nMech;
using namespace nMech::nNET;

