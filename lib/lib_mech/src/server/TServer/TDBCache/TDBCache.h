// 다음 ifdef 블록은 DLL에서 내보내기하는 작업을 쉽게 해 주는 매크로를 만드는 
// 표준 방식입니다. 이 DLL에 들어 있는 파일은 모두 명령줄에 정의된 _EXPORTS 기호로
// 컴파일되며, 동일한 DLL을 사용하는 다른 프로젝트에서는 이 기호를 정의할 수 없습니다.
// 이렇게 하면 소스 파일에 이 파일이 들어 있는 다른 모든 프로젝트에서는 
// AQDBCACHE_API 함수를 DLL에서 가져오는 것으로 보고, 이 DLL은
// 이 DLL은 해당 매크로로 정의된 기호가 내보내지는 것으로 봅니다.
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


// 프론트엔드와 백엔드서버 모두 include해야함.
#include "../TCommonServer/define_code_BackEndServer.h"
#include "../TCommonServer/define_code_FrontEndServer.h"
#include "../TCommonServer/define_code_Server.h"
#include "../TCommonServer/define_code_PlugIn.h"

// console cmd .cpp에만 추가하자.
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
