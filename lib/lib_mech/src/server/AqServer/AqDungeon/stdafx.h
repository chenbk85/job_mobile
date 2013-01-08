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
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_D
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_D
#define jSERVER_NAME AqDungeon
#define jsSERVER_NAME _T("AqDungeon")
#include "../AqCommon/AqCommon.h"

#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;

#include "network/protocal/PT_DBCacheServer_Enum.h"
using namespace nMech::nNET::nDBCacheServer;

#include "network/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;

#include "network/protocal/PT_UserServer_Enum.h"
using namespace nMech::nNET::nUserServer;

#include "network/protocal/PT_DungeonServer_Enum.h"
using namespace nMech::nNET::nDungeonServer;

#include "PlugIn_ToBackEnd.h"
#include "PlugIn_ToFrontEnd.h"

#include "../AqCommon/define_code_jFE.h"
#include "../AqCommon/define_code_Server.h"


#define _xmlid_LIST(X)\
	X(AqDungeon)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;

#define var_enum(var_func)\
	var_func(ServerSetting,WORLD_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\
	var_func(ServerSetting,C4_USER_CONNECTION_NOTIFY, 3.0f, 0 , "C4_USER_CONNECTION_NOTIFY send term (sec)")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);


