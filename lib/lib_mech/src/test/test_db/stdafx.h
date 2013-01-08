// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <iostream>
#include <deque>
#include <windows.h>
#include <sqlext.h>
#include <sstream>

#include "base\\jBase.h"
#include "common/jCommon.h"
#include "interface\\jIPak.h"
#include "common/jInit.h"
#include "Interface/db/jIDB.h"

using namespace nMech;


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
struct test_struct
{
	union
	{
		struct {
			aname_t sz;
			int i;
			int j;
			float f;
			BYTE buf[1024];

		};
		BYTE all[2048];
	};

};
extern test_struct pd;
extern string GetSQLErrorStr(SQLHANDLE Handle, SQLSMALLINT iHandleType=SQL_HANDLE_STMT);