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
#define PlugIn_Server PlugIn_Server_P
#define PlugIn_Connect PlugIn_Connect_P
#define jSERVER_NAME TPlayer
#define jsSERVER_NAME _T("TPlayer")
#define jSERVER_TYPE jS(TPlayer)
#define jPlayerObj	jPlayerObj_P



class jPlayerList_Dummy;
#define jPlayerList_IMPLEMENT jPlayerList_Dummy

#include "../TCommonServer/TCommonServer_header.h"
