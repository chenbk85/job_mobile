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
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_U
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_U
#define jSERVER_NAME AqUser
#define jsSERVER_NAME _T("AqUser")
#include "../AqCommon/AqCommon.h"


#define _xmlid_LIST(X)\
	X(AqUser)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(var_func)\
	var_func(AqUser,U2W_USER_DISCONNECT, 3.0f, 0 , "time of disconnected user notify to world(sec)")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);




#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;

#include "network/protocal/PT_DBCacheServer_Enum.h"
using namespace nMech::nNET::nDBCacheServer;

#include "network/protocal/PT_UserServer_Enum.h"
using namespace nMech::nNET::nUserServer;


#include "PlugIn_ToBackEnd.h"
#include "PlugIn_ToFrontEnd.h"


#include "../AqCommon/define_code_jBE.h"
#include "../AqCommon/define_code_Server.h"
