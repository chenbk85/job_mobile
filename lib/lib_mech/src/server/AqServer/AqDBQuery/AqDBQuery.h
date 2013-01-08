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
#include "SharedMem.h"
#include "Odbc.h"
#include "MemoryMap.h"
#include "jUserZoneInfo_DC.h"
#include "header/jODBC_Util.h"
#include "Interface/db/jIDB.h"


#include "../AqCommon/net_StringID.h"

#include "network/protocal/PT_DBQueryServer_Enum.h"
using namespace nDBQueryServer;

#define for_each_excel_file_list(X)\
X(sam_user)\
X(sam_castle)\
X(sam_force)\
X(sam_hero)\


namespace nMech
{
	namespace nODBC
	{
		int jSQLGetData(jPatcher& p,db_uid_type& val, int);
		#define jSQLGetData_ENUM_TABLE(enum_tbl,help,root_ns,ns) int jSQLGetData(jPatcher& p,ns::enum_tbl& val, int);
		#define decl_xls_enum234(files) _jJOIN_3(for_each_nAQ_,files,_ENUM)(jSQLGetData_ENUM_TABLE);
		for_each_excel_file_list(decl_xls_enum234);

	}
}

//--------------------------------------------------------------------------
class Aq_NetDLL : public nCONSOLE::jConsoleDLL_Net
	//--------------------------------------------------------------------------
{
public:
	jINTERFACE_HEADER(jIConsoleDLL);

	nMech::nUtil::nSharedMem::CSharedMemQueue m_SendQueue;
	nMech::nUtil::nSharedMem::CSharedMemQueue m_RecvQueue;
	nMech::nUtil::nSharedMem::CMemoryMap<jUserZoneInfo_DC> m_UsersSM;
	jLIST_TYPEDEF_vector(jUserZoneInfo_DC*, m_vecUsersMS);

	BOOL WritePacket(jPacket_Base &pk)
	{
		m_SendQueue.WritePacket(pk);
		return TRUE;
	}
	int m_isQuit;

	jUserZoneInfo_DC* find_by_yhandle(userid_t uid);

};
extern nMech::nDB::jISafeDB*	g_pDB;
extern Aq_NetDLL* g_pjConsoleDLL;
extern jIPlugIn_Connection* g_pCurrPlugInBE;



#define READ_PACKET_DQ(X) READ_PACKET(X);nswb256_t buf;
#define READ_PACKET_DQ_U(X) READ_PACKET(X);nswb256_t buf;\
	jUserZoneInfo_DC* pUser=0; \
	db_code_start()\
	pUser = pDLL->find_by_yhandle(Data.uid);\
	if(!pUser) throw jError(SR_t(X),CR_t(DC_USER_db_handler_not_found));\
	WCHAR			szSQL[2048];\


#define excel_jSQLGetData(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)\
	jSQLGetData(p,d._jJOIN_4(m_,eng_name,_,data_type_simple),sizeof(d._jJOIN_4(m_,eng_name,_,data_type_simple) ));


#define jSQLGetData_UseTABLE_decl(table,help,root_ns,ns) void table##_jSQLGetData ( nODBC::jPatcher& p , ns::table& d);
#define decl_xls_getDatafunc234(files) _jJOIN_3(for_each_nAQ_,files,_Use_STRUCT_LIST)(jSQLGetData_UseTABLE_decl);
for_each_excel_file_list(decl_xls_getDatafunc234);

#define decl_db_sql_q34(table) void make_update_table(WCHAR* szSQL,nAQ::Use_##table* );void make_Insert_table(WCHAR* szSQL, nAQ::Use_##table* );
for_each_User_table(decl_db_sql_q34);
