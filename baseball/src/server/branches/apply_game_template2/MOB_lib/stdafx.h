
#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#ifdef DEF_WINDOWS
#include <tchar.h>
#else
#define _T(X) X
#endif

#define JBASE_API

#include "common/header/jHeader.h"
#include "common/header/uStringParsor.h"
#include "jILog.h"
using namespace nMech;


#include "excel/db_type.h"
#include "excel/excel_all.h"

#include "common_typedef.h"
#include "common_define_const.h"
#include "common_util.h"

#include "nMOB.h"
#include "nBASE_BALL.h"
