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
#define PlugIn_Server PlugIn_Server_DT
#define PlugIn_Connect PlugIn_Connect_DT
#define jSERVER_NAME TDummy
#define jsSERVER_NAME _T("TDummy")
#define jSERVER_TYPE jS(DummyServer)

#include "../TCommonServer/TCommonServer_header.h"
