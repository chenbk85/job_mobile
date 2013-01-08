// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

// Windows 헤더 파일:
#include <windows.h>
#include <Mmsystem.h>

// boost 
#include <boost/bind.hpp>

// google protocal buffer
#include <google/protobuf/io/zero_copy_stream_impl.h>



#define jEXCEL_SERVER_SIDE_CODE
#define jSERVER_NAME MSG_presence_dummy
#define jsSERVER_NAME _T("MSG_presence_dummy")

#define _xmlid_LIST(X)\
  X(MSG_presence_dummy)\

_xmlid_LIST(jxDECL);

//주석 부분에는 xml에서 허용하지 않는 문자는 오면 안된다. 예시 : comma, ', < ,> ,& 등등
#define var_enum(func)\
  func(MSG_presence_dummy,IsAutoPlay,false,0,"batter pitcher auto play")\
  func(MSG_presence_dummy,AutoReJoinCount,1,0,"auto join count when received UAnsLeaveGame")\
  func(MSG_presence_dummy,AutoReConnectCount,1,0,"auto join count when called socket-OnDisconnect()")\
  func(MSG_presence_dummy,AutoReConnectWaitTime,2.f,0,"Wait time of auto Reconnect.")\

var_enum(jCV_DECLARE);

//user_name으로 부터 user객체와 peSession객체를 찾는다.
#define jFIND_USER(peSession,pSession,user_name)\
  jRETURN_ret(false,g_pPlugIn && g_pPlugIn->m_pCSM);\
  jIE* peSession = g_pPlugIn->FindSession(user_name);\
  jRETURN_ret(true, peSession);\
  g_SessionList_it it = g_SessionList.find(peSession);\
  jRETURN_ret(true, it!=g_SessionList.end());\
  TestSession *pSession = &it->second;\


//#define jLOG_USER(szFormat, ...) jLOG( _T("[%I64d] ") szFormat  , pSession->db_id() , __VA_ARGS__ );
#define jLOG_USER jLOG
#define jLOG_USER_T jLOG_T

#include "Plugin_Common.h"
#include "PlugIn_presence_client.h"



#define RECV_PARAM_PlugIn_presence_client PlugIn_presence_client* pPlugIn,jIE* peSession,TestSession* pSession

// client -> user gate로 패킷전송.
#define jMAKE_MESSAGE_X2UG(pSession,sendMsg, sd ,NAME)\
  Client_UserGateServer sendMsg;\
  sendMsg.set_type(::Client_UserGateServer_Type_##NAME);\
  s_##NAME* sd = sendMsg.mutable_m_##NAME();\
  jLOG_USER(_T("%s>send X2UG:") jS(NAME),jFUNC);\


#define jRECV_PAnsProtocol(MSG,...) bool OnRecv_##MSG(RECV_PARAM_PlugIn_presence_client,const MSG &rd)


