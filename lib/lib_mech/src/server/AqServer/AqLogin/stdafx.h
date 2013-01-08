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
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_L
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_L
#define jSERVER_NAME AqLogin
#define jsSERVER_NAME _T("AqLogin")

#include "../AqCommon/AqCommon.h"


#include "PlugIn_ToFrontEnd.h"
#include "PlugIn_ToBackEnd.h"

#include "network/protocal/PT_CentralServer_Enum.h"
#include "network/protocal/PT_LoginServer_Enum.h"
#include "network/protocal/PT_UserServer_Enum.h"

using namespace nMech::nNET::nCentralServer;
using namespace nMech::nNET::nLoginServer;
using namespace nMech::nNET::nUserServer;

#include "../AqCommon/define_code_jFE.h"
#include "../AqCommon/define_code_Server.h"


#define _xmlid_LIST(X)\
	X(Aq_NetDLL)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(var_func)\
var_func(AqLogin,C4_USER_CONNECTION_NOTIFY, 3.0f, 0 , "C4_USER_CONNECTION_NOTIFY send term (sec)")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);

