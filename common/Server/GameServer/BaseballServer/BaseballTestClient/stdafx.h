// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#define		DF_TEST_CLIENT_SIDE //BaseballTestClient.exe에서만 사용하는 코드.
//#define DF_CLIENT_LOGIC_ERROR_CHECK // TestClient에서 로직에러 체크를 할지. 서버테스트를 위해 막아두자.



#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <Mmsystem.h>

#include <boost/bind.hpp>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.


#define jEXCEL_SERVER_SIDE_CODE


#define jSERVER_NAME BaseballTestClient
#define jsSERVER_NAME _T("BaseballTestClient")
#include "./TestCommon.h"

#define _xmlid_LIST(X)\
	X(BaseballTestClient)\

_xmlid_LIST(jxDECL);

//주석 부분에는 xml에서 허용하지 않는 문자는 오면 안된다. 예시 : comma, ', < ,> ,& 등등
#define var_enum(func)\
	func(BaseballTestClient,IsAutoPlay,false,0,"batter pitcher auto play")\
	func(BaseballTestClient,AutoMatchCount,1,0,"auto match play count when auto play")\
	func(BaseballTestClient,AutoReJoinCount,1,0,"auto join count when received UAnsLeaveGame")\
	func(BaseballTestClient,AutoReConnectCount,1,0,"auto join count when called socket-OnDisconnect()")\
	func(BaseballTestClient,AutoReConnectWaitTime,2.f,0,"Wait time of auto Reconnect.")\
	func(BaseballTestClient,GatewayVersion,3,0,"SVNVERSION in server baseball/svn_version.hpp ")\

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


//user_name으로 부터 user객체와 peSession객체를 찾는다.
#define jFIND_USER(peSession,pUser,user_name)\
	jRETURN_ret(false,g_pPlugIn && g_pPlugIn->m_pCSM);\
	jIE* peSession = g_pPlugIn->FindUser(user_name);\
	jRETURN_ret(true, peSession);\
	g_Users_it it = g_Users.find(peSession);\
	jRETURN_ret(true, it!=g_Users.end());\
	jUser *pUser = &it->second;\


//#define jLOG_USER(szFormat, ...) jLOG( _T("[%I64d] ") szFormat  , pUser->db_id() , __VA_ARGS__ );
#define jLOG_USER jLOG
#define jLOG_USER_T jLOG_T

#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "proto/ug.pb.h"
//#include "proto/db.pb.h"
#include "proto/gameLogic.pb.h"
#include "proto/PT_BaseballServer.pb.h"
#include "proto/PT_BaseballServer.proto.h"

#include "proto/PT_UserGateServer.pb.h"
#include "proto/PT_UserGateServer.proto.h"

#include "excel/excel_all.h"

#include "T:/svn/baseball/MOB_lib/DBHelper.h"


#include "PlugIn_BaseballClient.h"


//공용 유틸 해더
#include "base/Random.h"




