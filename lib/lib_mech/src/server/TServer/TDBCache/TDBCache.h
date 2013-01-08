// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// AQDBCACHE_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef AQDBCACHE_EXPORTS
#define AQDBCACHE_API __declspec(dllexport)
#else
#define AQDBCACHE_API __declspec(dllimport)
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
#include "../TCommonClient/protocal/PT_DBCacheServer_Enum.h"
using namespace nMech::nNET::nDBCacheServer;
#include "../TCommonClient/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;


// ����Ʈ����� �鿣�弭�� ��� include�ؾ���.
#include "../TCommonServer/define_code_BackEndServer.h"
#include "../TCommonServer/define_code_FrontEndServer.h"
#include "../TCommonServer/define_code_Server.h"
#include "../TCommonServer/define_code_PlugIn.h"

// console cmd .cpp���� �߰�����.
#include "../TCommonServer/define_code_jIConsoleCmd.h"

#include "jPlayerObj.h"
#include "PlugIn_Server.h"
#include "PlugIn_Connect.h"
#include "PlugIn_DBQuery.h"


#include "../TDBQuery/SharedMemQueue.h"



#define _xmlid_LIST(X)\
	X(TDBCache)\

_xmlid_LIST(jxDECL);


#define var_enum(var_func)\
	var_func(jSERVER_NAME,DOMAIN_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\
	\
	var_func(jSERVER_NAME,SM_QUERY2CACHE_NAME, _T("AQ_QUERY2CACHE"), 0 , "query to cache queue name")\
	var_func(jSERVER_NAME,SM_CACHE2QUERY_NAME, _T("AQ_CACHE2QUERY"), 0 , "cache to query queue name")\
	var_func(jSERVER_NAME,SM_USER_INFO_NAME, _T("jPlayerDBSM"), 0 , "user info shared memory name")\
	\
	var_func(jSERVER_NAME,SM_QUEUE_MAX_COUNT, 4096, 0 , "QUERY,CACHE QUEUE SIZE")\
	var_func(jSERVER_NAME,SM_USER_MAX, 3000, 0 , "SHARED MEMORY USER INFO max count")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);


//--------------------------------------------------------------------------
class T_NetDLL : public nCONSOLE::jConsoleDLL_Net
	//--------------------------------------------------------------------------
{
public:
	jINTERFACE_HEADER(jIConsoleDLL);

};

extern T_NetDLL* g_pjConsoleDLL;
