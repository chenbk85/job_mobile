// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#define		DF_TEST_CLIENT_SIDE //BaseballTestClient.exe������ ����ϴ� �ڵ�.
//#define DF_CLIENT_LOGIC_ERROR_CHECK // TestClient���� �������� üũ�� ����. �����׽�Ʈ�� ���� ���Ƶ���.



#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <Mmsystem.h>

#include <boost/bind.hpp>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.


#define jEXCEL_SERVER_SIDE_CODE


#define jSERVER_NAME BaseballTestClient
#define jsSERVER_NAME _T("BaseballTestClient")
#include "./TestCommon.h"

#define _xmlid_LIST(X)\
	X(BaseballTestClient)\

_xmlid_LIST(jxDECL);

//�ּ� �κп��� xml���� ������� �ʴ� ���ڴ� ���� �ȵȴ�. ���� : comma, ', < ,> ,& ���
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

// xml�� ��Ŷ���� jIE*�� �ش��ϴ� ������.
#define aq_READ_PACKET_P2P_PB_xml(PACKET,xml) S_##PACKET Data; Data.xml=GetjIXml()->CreateElement(); _aq_READ_PACKET_P2P_PB_Data(PACKET,Data)


#define jDELAY() if(i>per_user){if(delay_msec)Sleep(delay_msec);i=0;}


//user_name���� ���� user��ü�� peSession��ü�� ã�´�.
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


//���� ��ƿ �ش�
#include "base/Random.h"




