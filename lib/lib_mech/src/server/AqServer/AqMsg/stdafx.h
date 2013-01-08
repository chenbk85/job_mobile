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
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_M
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_M
#define jSERVER_NAME AqMsg
#define jsSERVER_NAME _T("AqMsg")
#include "../AqCommon/AqCommon.h"


#define _xmlid_LIST(X)\
	X(AqMsg)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(var_func)\
	var_func(ServerSetting,WORLD_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);



#include "PlugIn_ToFrontEnd.h"
#include "PlugIn_ToBackEnd.h"

#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;

#include "../AqCommon/define_code_jBE.h"
#include "../AqCommon/define_code_Server.h"

