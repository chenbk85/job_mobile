
#pragma once

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
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
