// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#define DF_NET_AGENT TESTCLIENT_EXPORTS

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#define jSERVER_NAME net_agent
#define jsSERVER_NAME _T("net_agent")
#include "../net_common/net_Common.h"

#define _xmlid_LIST(X)\
	X(net_agent)\

_xmlid_LIST(jxDECL);


#define var_enum(func)\
	func(jSERVER_NAME,Process_live_Check_time, 3.f , 0,"process live / kill check time (sec)")\
	func(jSERVER_NAME,reconnect_time , 10.f , 0,"reconnect time if disconnected (sec)")\
	func(jSERVER_NAME,reconnect_count , 100, 0,"retry reconnect count. if its count over then run pv_reconnect_fail_action")\
	func(jSERVER_NAME,reconnect_fail_action, _T("_net_Agent.bat"), 0,"retry reconnect count")\
	func(jSERVER_NAME,check_time_processkill, 10.f, 0,"if agent received eS2A_ONLINE_RQ then check kill process (SEC)")\

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

// net_agent.dll에서 호출하는 함수.
#define Get_jSMA() if(nSM::g_jSMA)nSM::g_jSMA

// 에이전트->게임서버로 메세지 보내기
#define jSendToServer(szServerType,...) if(nSM::g_jSMA)nSM::g_jSMA->WritePacket(szServerType, __VA_ARGS__)


#include "../protocal/PT_MonitorServer_Enum.h"
using namespace nNET::nMonitorServer;
#include "mech/util/sm/jRoC_SharedMemory.h"


#include "PlugIn_ToBackEnd.h"
#include "jNetClient.h"



const int iMAX_CHECK_KILL_FAST=10;
#define  fTIMEPULS_CHECK_KILL_FAST 2.f