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
#define PlugIn_Server PlugIn_Server_W
#define PlugIn_Connect PlugIn_Connect_W
#define jSERVER_NAME TWorld
#define jsSERVER_NAME _T("TWorld")
#define jSERVER_TYPE jS(WorldServer)

#include "../TCommonServer/TCommonServer_header.h"
