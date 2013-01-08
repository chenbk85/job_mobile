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
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_TM
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_TM
#define jSERVER_NAME AqMonitor
#define jsSERVER_NAME _T("AqMonitor")
#include "../AqCommon/AqCommon.h"


#define _xmlid_LIST(X)\
	X(AqMonitor)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Connection *g_pCurrPlugIn;


#define var_enum(var_func)\

//var_func(ServerSetting,USER_CERT_SKIP, 1, 0,"is user cert skip ?")\


var_enum(jCV_DECLARE);



#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
#include "network/protocal/PT_TestServer_Enum.h"
using namespace nMech::nNET::nTestServer;

#include "../AqCommon/define_code_jFE.h"
#include "../AqCommon/define_code_Server.h"

#include "PlugIn_ToBackEnd.h"

