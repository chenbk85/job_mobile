/* file : TCommonServer.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-07 12:55:43
comp.: wiki.aqrius.com
title : 
desc : 


//TCommonServer.h�� ���� �� ������ �ʴ°͵�. server.dll�� stdafx.h���� �Ұ�.
// ���� ��� packet header�� excel header���� ���Ե� ����.
// �ִ��� ������ ����.

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
// ���� Ŭ���̾�Ʈ ���� ���� �ش�
//--------------------------------------------------------------------------
#include "../TCommonClient/TServerClient_CommonHeader.h"


#define SQPLUS_CONST_OPT
#include "base/jSQ_bind.h"
#include "interface/net/jSQ_bind_jINet.h"



//--------------------------------------------------------------------------
// ������ ���� ���� �ش�
//--------------------------------------------------------------------------


#ifndef jxDEFINE_NET
#define jxDEFINE_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{ \
	jNET_COMMON_LIB_API StringID x_##X= Get_jIStringTable()->RegistID(_T(#X),&x_##X);} } }
#endif

#ifndef jxDECL_NET
#define jxDECL_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{extern jNET_COMMON_LIB_API StringID x_##X;}}}
#endif

#include "jServerInfo.h"

// ���� Ŭ���̾�Ʈ�� ���� ������ �ش�
#include "..\TCommonClient/TServerClient_CommonHeader_End.h"




//--------------------------------------------------------------------------
// �������� �ڷᱸ������ ���� ��� �ڵ� ���� �ش�
//--------------------------------------------------------------------------

// �׼��� ������ڷᱸ�� ���� �ڵ�
#include "..\TCommonClient/excel_jSetter.h"

// ../common_AQ/net_Struct.h���� ���ǵ� �ڷᱸ���� ���� ����� & ��Ŀ�� ����
#include "jDebugPrint_TCommonServer.h"
#include "..\TCommonClient/net_SQ_client.h"
#include "net_SQ_Server.h"
#include "jNetStreamRead_TServer.h"



#endif // __AqCo1234m41mo432n4124_3h4e43214a4deasafdr__
