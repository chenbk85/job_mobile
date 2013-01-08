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
#include "base/jBase.h"
#include "interface/jIConsoleVar.h"
#include "interface/xml/jIXml.h"
#include "interface/net/jTypedef_net.h"
#include "interface/net/jINet.h"
#include "interface/net/jINet_Util.h"
#include "interface/net/excel_code_util.h"

using namespace std;
using namespace nMech;

#include "../TExcelData/TExcelData.h"

#ifndef SQPLUS_CONST_OPT
#define SQPLUS_CONST_OPT
#endif
#include "base/jSQ_bind.h"
#include "interface/net/jSQ_bind_jINet.h"
#include "../TCommonClient/TServerClient_CommonHeader.h"
#include "../TCommonClient/net_SQ_client.h"

#define T_SERVER_LIB_API
#include "../TCommonServer/jServerInfo.h"
#include "../TCommonServer/net_SQ_Server.h"

#include "TProtocal_back.h"

