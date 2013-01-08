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
#define jSERVER_NAME test_Server
#define jsSERVER_NAME _T("test_Server")

#include "../TestCommon/TestCommon.h"


#define _xmlid_LIST(X)\
	X(TestServer_DLL)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(func)\
	func(TestServer,TEST_ID_START_NUM,500,0,"Test Account start number")\
	func(TestServer,DummyCount,50,0,"default TestClient Dummy count ")\
	func(TestServer,DefaultLoginIP,_T("127.0.0.1"), 0,"Default AqLoginServer IP")\
	func(TestServer,DefaultLoginPort ,33100,0,"default AqLoginServer Port")\
	func(TestServer,TEST_ID_NAME,_T("test"),0,"test user id start name")\


var_enum(jCV_DECLARE);



#define READ_PACKET_TS(X) READ_PACKET(X);\
	PlugIn_ToFrontEnd*pFE = (PlugIn_ToFrontEnd*)pPlugIn;if(!pFE) return;\
	nswb1024_t buf;\
	AqTestClientNode* pUser= pFE->get_user(pS);\
	if(!pUser){jWARN(_T(#X) _T(" pUser==NULL"));	return;}\


