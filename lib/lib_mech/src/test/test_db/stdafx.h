// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
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


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
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