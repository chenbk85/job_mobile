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
#define jSERVER_NAME MonitorServer
#define jsSERVER_NAME _T("MonitorServer")

#include "../net_common/net_Common.h"
#include "../net_common/jDLL_Bridge.h"


#define _xmlid_LIST(X)\
	X(MonitorServer_DLL)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(func)\
	func(MonitorServer,TEST_ID_START_NUM,500,0,"Test Account start number")\
	func(MonitorServer,DummyCount,50,0,"default TestClient Dummy count ")\
	func(MonitorServer,DefaultLoginIP,_T("127.0.0.1"), 0,"Default AqLoginServer IP")\
	func(MonitorServer,DefaultLoginPort ,33100,0,"default AqLoginServer Port")\
	func(MonitorServer,TEST_ID_NAME,_T("test"),0,"test user id start name")\


var_enum(jCV_DECLARE);



#define READ_PACKET_net_monitor(X) READ_PACKET(X);\
	PlugIn_ToFrontEnd*pFE = (PlugIn_ToFrontEnd*)pPlugIn;if(!pFE) return;\
	nswb1024_t buf;\
	jAgentNode* pUser= pFE->get_user(pS);\
	if(!pUser){jWARN(_T(#X) _T(" pUser==NULL"));	return;}\


