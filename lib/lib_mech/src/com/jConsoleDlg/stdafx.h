// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

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

using namespace std;
using namespace nMech;

#define _xmlid_LIST(X)\


_xmlid_LIST(jxDECL);
