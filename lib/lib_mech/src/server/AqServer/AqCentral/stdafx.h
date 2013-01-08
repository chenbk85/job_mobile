// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>



#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_C
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_C
#define jSERVER_NAME AqCentral
#define jsSERVER_NAME _T("AqCentral")

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "../AqCommon/AqCommon.h"


#include "../AqCommon/define_code_Server.h"
#include "../AqCommon/define_code_jBE.h"


#define _xmlid_LIST(X)\
	X(AqCentral)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(var_func)\
	\
	var_func(jSERVER_NAME,LOG_FILE_CHANGE_MINITE, 720.f, 0,"log file rename time (minite)")\
	var_func(jSERVER_NAME,C2_USER_CONNECTION_NOTIFY, 3.0f, 0,"server user tot count notify time (sec)")\
	


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);
