// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#define PlugIn_Server PlugIn_Server_DC
#define PlugIn_Connect PlugIn_Connect_DC
#define jSERVER_NAME TDBCache
#define jsSERVER_NAME _T("TDBCache")
#define jSERVER_TYPE jS(DBCacheServer)
#define jPlayerObj	jPlayerObj_DC

#include "../TCommonServer/TCommonServer_header.h"

