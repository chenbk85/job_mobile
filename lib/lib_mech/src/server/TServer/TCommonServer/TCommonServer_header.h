/* file : TCommonServer.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-07 12:55:43
comp.: wiki.aqrius.com
title : 
desc : 


//TCommonServer.h에 비해 잘 변하지 않는것들. server.dll의 stdafx.h포함 할거.
// 또한 모든 packet header와 excel header에도 포함될 내용.
// 최대한 가볍게 하자.

*/

#ifndef __AqCo1234m41mo432n4124_3h4e43214a4deasafdr__
#define __AqCo1234m41mo432n4124_3h4e43214a4deasafdr__
#pragma once

#ifdef AQCOMMON_EXPORTS
#define T_SERVER_LIB_API __declspec(dllexport)
#else
#define T_SERVER_LIB_API __declspec(dllimport)
#pragma comment(lib, "TCommonServer.lib")
#endif


#include "common/jCommon.h"
#include "interface/jIConsoleVar.h"
#include "interface/xml/jIXml.h"
#include "interface/net/jTypedef_net.h"
#include "interface/net/jINet.h"
#include "interface/net/jINet_Util.h"
#include "interface/net/excel_code_util.h"

using namespace std;
using namespace nMech;
using namespace nMech::nNET;


#define jNET_COMMON_LIB_API T_SERVER_LIB_API

#include "interface/net/net_common_code.h"

//--------------------------------------------------------------------------
// 서버 클라이언트 공유 시작 해더
//--------------------------------------------------------------------------
#include "../TCommonClient/TServerClient_CommonHeader.h"


#define SQPLUS_CONST_OPT
#include "base/jSQ_bind.h"
#include "interface/net/jSQ_bind_jINet.h"



//--------------------------------------------------------------------------
// 서버간 공유 시작 해더
//--------------------------------------------------------------------------


#ifndef jxDEFINE_NET
#define jxDEFINE_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{ \
	jNET_COMMON_LIB_API StringID x_##X= Get_jIStringTable()->RegistID(_T(#X),&x_##X);} } }
#endif

#ifndef jxDECL_NET
#define jxDECL_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{extern jNET_COMMON_LIB_API StringID x_##X;}}}
#endif

#include "jServerInfo.h"

// 서버 클라이언트간 공유 마지막 해더
#include "..\TCommonClient/TServerClient_CommonHeader_End.h"




//--------------------------------------------------------------------------
// 서버공용 자료구조들을 위한 기반 코드 지원 해더
//--------------------------------------------------------------------------

// 액셀용 사용자자료구조 지원 코드
#include "..\TCommonClient/excel_jSetter.h"

// ../common_AQ/net_Struct.h에서 정의된 자료구조에 대한 디버깅 & 스커럴 선언
#include "jDebugPrint_TCommonServer.h"
#include "..\TCommonClient/net_SQ_client.h"
#include "net_SQ_Server.h"
#include "jNetStreamRead_TServer.h"



#endif // __AqCo1234m41mo432n4124_3h4e43214a4deasafdr__
