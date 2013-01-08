// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// AQTOWN_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef AQTOWN_EXPORTS
#define AQTOWN_API __declspec(dllexport)
#else
#define AQTOWN_API __declspec(dllimport)
#endif


#include "util/jUtil.h"
#include "util/jConsoleDLL.h"


#include "../TCommonServer/TCommonServer.h"
#include "../TCommonServer/csv_loader.h"
#include "../TCommonServer/jXmlSaveManager.h"

#include "../TCommonClient/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
#include "../TCommonClient/protocal/PT_CommandServer_Enum.h"
using namespace nMech::nNET::nCommandServer;
#include "../TCommonClient/protocal/PT_UserServer_Enum.h"
using namespace nMech::nNET::nUserServer;

#include "../TCommonClient/protocal/PT_DBCacheServer_Enum.h"
using namespace nMech::nNET::nDBCacheServer;
#include "../TCommonClient/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;
#include "../TCommonClient/protocal/PT_DBCacheServer_Enum.h"
using namespace nMech::nNET::nDBCacheServer;

#include "../TCommonClient/protocal/PT_LoginServer_Enum.h"
using namespace nMech::nNET::nLoginServer;
#include "../TCommonClient/protocal/PT_ChannelServer_Enum.h"
using namespace nMech::nNET::nChannelServer;


// ����Ʈ����� �鿣�弭�� ��� include�ؾ���.
#include "../TCommonServer/define_code_BackEndServer.h"
#include "../TCommonServer/define_code_FrontEndServer.h"
#include "../TCommonServer/define_code_Server.h"
#include "../TCommonServer/define_code_PlugIn.h"

//front end server���� Ŭ���̾�Ʈ ���ؼ� ���� �ڵ�.
#include "../TCommonServer/define_code_ToClient.h"

// console cmd .cpp���� �߰�����.
#include "../TCommonServer/define_code_jIConsoleCmd.h"

#include "jPlayerObj.h"
#include "../TCommonServer/jGridNode_Client.h"

#include "PlugIn_Connect.h"
#include "PlugIn_Server.h"




#define _xmlid_LIST(X)\
	X(TChannel)\

_xmlid_LIST(jxDECL);




#define var_enum(var_func)\
	var_func(jSERVER_NAME,DOMAIN_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\
	var_func(jSERVER_NAME,C4_USER_CONNECTION_NOTIFY, 3.0f, 0 , "C4_USER_CONNECTION_NOTIFY send term (sec)")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);


bool jCheck_ObjName(wcstr szName);

//�̸��� ��Ģ�� ��߳��ϴ�. ���� �̻�!
#define pUser_Check_make_name(name)\
	if(!jCheck_ObjName(name))\
{\
	pS_eSEND_jError_ToClient(T,SR_t(OBJ_NAME_LEN_ERROR),CR_t(jCheck_ObjName));\
	return;\
}\



#define jUSER_ERROR_CHECK(condition,SR,CR) if((condition)){	pS_eSEND_jError_ToClient(T,SR_t(SR),CR_t(CR));	return;		}


//--------------------------------------------------------------------------
class T_NetDLL : public nCONSOLE::jConsoleDLL_Net
	//--------------------------------------------------------------------------
{
public:
	jINTERFACE_HEADER(jIConsoleDLL);

};

extern T_NetDLL* g_pjConsoleDLL;
