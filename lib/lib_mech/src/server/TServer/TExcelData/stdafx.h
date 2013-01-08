// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "base/jBase.h"
#include "interface/jIConsoleVar.h"
#include "interface/xml/jIXml.h"

using namespace std;
using namespace nMech;




#define SQPLUS_CONST_OPT
#include "base/jSQ_bind.h"

#include "TExcelData.h"


DECLARE_INSTANCE_TYPE(db_uid_type);