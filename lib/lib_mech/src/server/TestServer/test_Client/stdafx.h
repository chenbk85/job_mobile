// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define jSERVER_NAME test_Client
#define jsSERVER_NAME _T("test_Client")
#include "../TestCommon/TestCommon.h"

#define _xmlid_LIST(X)\
	X(test_Client)\

_xmlid_LIST(jxDECL);


#define var_enum(func)\
	func(test_Client,TEST_ID_START_NUM,500,0,"Test Account start number")\
	func(test_Client,DummyCount,50,0,"기본 더미클라이언트 세션 갯수")\
	func(test_Client,DEFAULT_LOGIN_IP,_T("50.10.125.119:33100"),0,"SamGame.exe에서 디펄트 접속IP")\
	func(test_Client,DefaultLoginIP,_T("127.0.0.1"), 0,"기본 세션(로긴)접속 IP")\
	func(test_Client,DefaultLoginPort ,33100,0,"기본 로긴접속 포트")\

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

// xml은 패킷중의 jIE*에 해당하는 변수명.
#define aq_READ_PACKET_P2P_PB_xml(PACKET,xml) S_##PACKET Data; Data.xml=GetjIXml()->CreateElement(); _aq_READ_PACKET_P2P_PB_Data(PACKET,Data)


#define jDELAY() if(i>per_user){if(delay_msec)Sleep(delay_msec);i=0;}



#include "../protocal/PT_TestServer_Enum.h"
using namespace nNET::nTestServer;


#include "PlugIn_ToBackEnd.h"
#include "jNetClient.h"


