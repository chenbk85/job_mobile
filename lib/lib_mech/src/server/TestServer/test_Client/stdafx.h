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
#define jSERVER_NAME test_Client
#define jsSERVER_NAME _T("test_Client")
#include "../TestCommon/TestCommon.h"

#define _xmlid_LIST(X)\
	X(test_Client)\

_xmlid_LIST(jxDECL);


#define var_enum(func)\
	func(test_Client,TEST_ID_START_NUM,500,0,"Test Account start number")\
	func(test_Client,DummyCount,50,0,"�⺻ ����Ŭ���̾�Ʈ ���� ����")\
	func(test_Client,DEFAULT_LOGIN_IP,_T("50.10.125.119:33100"),0,"SamGame.exe���� ����Ʈ ����IP")\
	func(test_Client,DefaultLoginIP,_T("127.0.0.1"), 0,"�⺻ ����(�α�)���� IP")\
	func(test_Client,DefaultLoginPort ,33100,0,"�⺻ �α����� ��Ʈ")\

var_enum(jCV_DECLARE);


// Data , pBE , buf, pUser
#define aq_READ_PACKET_P2P_PB(PACKET) PlugIn_ToBackEnd*pBE = (PlugIn_ToBackEnd*)pPlugIn; \
	nswb1024_t buf;jDummyPlayer* pUser = pBE->GetDummyUser(pS);if(!pUser) return;\
	READ_PACKET(PACKET);

#define _aq_READ_PACKET_P2P_PB_Data(PACKET,Data)	nswb1024_t buf;\
	PlugIn_ToBackEnd*pBE = (PlugIn_ToBackEnd*)pPlugIn;\
	jDummyPlayer* pUser = pBE->GetDummyUser(pS);\
	if(!pUser) return;\
	READ_PACKET_Data(PACKET,Data);

#define aq_READ_PACKET_P2P_PB_Data(PACKET) _aq_READ_PACKET_P2P_PB_Data(PACKET,pUser->m_##PACKET)

// xml�� ��Ŷ���� jIE*�� �ش��ϴ� ������.
#define aq_READ_PACKET_P2P_PB_xml(PACKET,xml) S_##PACKET Data; Data.xml=GetjIXml()->CreateElement(); _aq_READ_PACKET_P2P_PB_Data(PACKET,Data)


#define jDELAY() if(i>per_user){if(delay_msec)Sleep(delay_msec);i=0;}



#include "../protocal/PT_TestServer_Enum.h"
using namespace nNET::nTestServer;


#include "PlugIn_ToBackEnd.h"
#include "jNetClient.h"


