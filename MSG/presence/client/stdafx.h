// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

// Windows ��� ����:
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

//�ּ� �κп��� xml���� ������� �ʴ� ���ڴ� ���� �ȵȴ�. ���� : comma, ', < ,> ,& ���
#define var_enum(func)\
  func(MSG_presence_dummy,IsAutoPlay,false,0,"batter pitcher auto play")\
  func(MSG_presence_dummy,AutoReJoinCount,1,0,"auto join count when received UAnsLeaveGame")\
  func(MSG_presence_dummy,AutoReConnectCount,1,0,"auto join count when called socket-OnDisconnect()")\
  func(MSG_presence_dummy,AutoReConnectWaitTime,2.f,0,"Wait time of auto Reconnect.")\

var_enum(jCV_DECLARE);

//user_name���� ���� user��ü�� peSession��ü�� ã�´�.
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

// client -> user gate�� ��Ŷ����.
#define jMAKE_MESSAGE_X2UG(pSession,sendMsg, sd ,NAME)\
  Client_UserGateServer sendMsg;\
  sendMsg.set_type(::Client_UserGateServer_Type_##NAME);\
  s_##NAME* sd = sendMsg.mutable_m_##NAME();\
  jLOG_USER(_T("%s>send X2UG:") jS(NAME),jFUNC);\


#define jRECV_PAnsProtocol(MSG,...) bool OnRecv_##MSG(RECV_PARAM_PlugIn_presence_client,const MSG &rd)


