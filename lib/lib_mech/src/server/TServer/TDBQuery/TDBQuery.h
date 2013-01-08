// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// AQQUERY_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef AQQUERY_EXPORTS
#define AQQUERY_API __declspec(dllexport)
#else
#define AQQUERY_API __declspec(dllimport)
#endif


#include "util/jUtil.h"
#include "util/jConsoleDLL.h"

#include "../TCommonServer/TCommonServer.h"
#include "../TCommonServer/csv_loader.h"
#include "../TCommonServer/net_StringID.h"

#include "../TDBQuery/SharedMemQueue.h"

#include "../TCommonClient/protocal/PT_DBQueryServer_Enum.h"
using namespace nDBQueryServer;


#define _xmlid_LIST(X)\
	X(TQuery)\

_xmlid_LIST(jxDECL);


#define var_enum(var_func)\
	var_func(jSERVER_NAME,DOMAIN_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\
	\
	var_func(jSERVER_NAME,GAMEDB_STRING, _T("Driver={SQL Server};Server=icandoit\\sqlexpress;Uid=sa;Pwd=qwer;Trusted_Connection=Yes;Database=tgame_db;Network=dbmssocn"), 0 , "db ip")\
	var_func(jSERVER_NAME,GAMEDB_ODBC, _T("NULL"), 0 , "sql server ODBC name")\
	var_func(jSERVER_NAME,GAMEDB_NAME, _T("NULL"), 0 , "sql server DATABASE name")\
	var_func(jSERVER_NAME,GAMEDB_ID, _T("NULL"), 0 , "db ID")\
	var_func(jSERVER_NAME,GAMEDB_PWD, _T("NULL"), 0 , "db PWD")\
	\
	var_func(jSERVER_NAME,SM_QUERY2CACHE_NAME, _T("AQ_QUERY2CACHE"), 0 , "query to cache queue name")\
	var_func(jSERVER_NAME,SM_CACHE2QUERY_NAME, _T("AQ_CACHE2QUERY"), 0 , "cache to query queue name")\
	var_func(jSERVER_NAME,SM_USER_INFO_NAME, _T("jPlayerDBSM"), 0 , "user info shared memory name")\
	\
	var_func(jSERVER_NAME,SM_QUEUE_MAX_COUNT, 4096, 0 , "QUERY,CACHE QUEUE SIZE")\
	var_func(jSERVER_NAME,SM_USER_MAX, 3000, 0 , "SHARED MEMORY USER INFO max count")\
	var_func(jSERVER_NAME,isAutoRestartDBCache, false, 0 , "if(DBCache Process Killed) Do AutoStart()")\



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

