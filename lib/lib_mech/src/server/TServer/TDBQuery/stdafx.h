// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

#ifndef DBQueryServer_jNOTUSE_SQ_CODE
#define DBQueryServer_jNOTUSE_SQ_CODE
#endif

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#define PlugIn_Server PlugIn_Server_DQ
#define PlugIn_Connect PlugIn_Connect_DQ
#define jSERVER_NAME TDBQuery
#define jsSERVER_NAME _T("TDBQuery")
#define jSERVER_TYPE jS(DBQueryServer)

#include "../TCommonServer/TCommonServer_header.h"

