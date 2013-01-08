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
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_TC
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_TC
#define jSERVER_NAME TestClient
#define jsSERVER_NAME _T("TestClient")
#include "../AqCommon/AqCommon.h"

#define _xmlid_LIST(X)\
	X(TestClient)\

_xmlid_LIST(jxDECL);


#define var_enum(func)\
	func(TestClient,TEST_ID_START_NUM,500,0,"Test Account start number")\
	func(TestClient,DummyCount,50,0,"기본 더미클라이언트 세션 갯수")\
	func(jSam,DEFAULT_LOGIN_IP,_T("50.10.125.119:33100"),0,"SamGame.exe에서 디펄트 접속IP")\
	func(TestClient,DefaultLoginIP,_T("127.0.0.1"), 0,"기본 세션(로긴)접속 IP")\
	func(TestClient,DefaultLoginPort ,33100,0,"기본 로긴접속 포트")\

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



#include "network/protocal/PT_LoginServer_Enum.h"
using namespace nNET::nLoginServer;
#include "network/protocal/PT_TownServer_Enum.h"
using namespace nNET::nTownServer;
#include "network/protocal/PT_DungeonServer_Enum.h"
using namespace nNET::nDungeonServer;

#include "network/protocal/PT_TestServer_Enum.h"
using namespace nNET::nTestServer;


#include "PlugIn_ToBackEnd.h"


