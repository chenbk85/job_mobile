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
#define PlugIn_ToFrontEnd PlugIn_ToFrontEnd_W
#define PlugIn_ToBackEnd PlugIn_ToBackEnd_W
#define jSERVER_NAME AqWorld
#define jsSERVER_NAME _T("AqWorld")
#include "../AqCommon/AqCommon.h"




#define _xmlid_LIST(X)\
	X(AqWorld)\

_xmlid_LIST(jxDECL);

extern jIPlugIn_Server_IOCP *g_pCurrPlugIn;


#define var_enum(var_func)\
	var_func(AqWorld,WORLD_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\

var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);


//G_USERS_FIND_UID(Data.uid); //jUserZoneInfo* pUser;
#define G_USERS_FIND_UID(uid)\
jUserZoneInfo* pUser= g_Users.find_by_uid(uid);\
if(!pUser)\
{\
	fname_t szBuf;\
	GetjILog()->Warning(jFUNC1 _T("user not found : %s"),ToString(uid,szBuf));\
	return;\
}\






#include "PlugIn_ToFrontEnd.h"
#include "PlugIn_ToBackEnd.h"

#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
#include "network/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;


#include "../AqCommon/define_code_jBE.h"
#include "../AqCommon/define_code_Server.h"

