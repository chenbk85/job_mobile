// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

#if 0
#define CentralServer_jNOTUSE_SQ_CODE
#define UserServer_jNOTUSE_SQ_CODE
#define WorldServer_jNOTUSE_SQ_CODE
#define DBCacheServer_jNOTUSE_SQ_CODE
#define DBQueryServer_jNOTUSE_SQ_CODE
#define LoginServer_jNOTUSE_SQ_CODE
#define MonitorServer_jNOTUSE_SQ_CODE
#define TestServer_jNOTUSE_SQ_CODE
#define GameServer_jNOTUSE_SQ_CODE
#endif

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#define PlugIn_Server PlugIn_Server_CH
#define PlugIn_Connect PlugIn_Connect_CH
#define jSERVER_NAME TChannel
#define jsSERVER_NAME _T("TChannel")
#define jSERVER_TYPE jS(ChannelServer)
#define jPlayerObj	jPlayerObj_CH

#include "../TCommonServer/TCommonServer_header.h"

