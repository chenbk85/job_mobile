/* file : excel_all.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-03-16 15:20:01
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __excel_all_header__
#define __excel_all_header__
#pragma once

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

#include "interface/net/jDebugPrint.h"
#include "interface/db/db_uid_type.h"
#include "interface/net/excel_code_util.h"
#include "Interface/net/net_common_code.h"
#include "header/jCSV_File.h"
#include "header/nNET_Stream.h"


#define jEXCEL_LIB_API
#define nExcelUtil nMech
#define jAPP_NAME test_Excel
#define jEXCEL_SERVER_SIDE_CODE


struct jItemObj1
{
	jIE* pE;
	tstring s;
	int i;
	float f;
	vector<int> aa;
};
typedef jItemObj1& jItemObj1_ref;
tcstr ToString(jItemObj1& v,tname1024_t sz);
jItemObj1_ref FromString(wcstr sz , jItemObj1& v);
jItemObj1_ref FromString(wstring& sz, jItemObj1& v);

#include "excel/table_type.h"


//--------------------------------------------------------------------------
// ¿¢¼¿ ÀÚµ¿ ÄÚµå ÇØ´õ 
//--------------------------------------------------------------------------
#pragma warning ( disable:4181)
#pragma warning ( disable:4251)
#include "excel/excel_enum.h"
#include "excel/excel_test.h"
#include "excel/excel_test2.h"
#include "excel/excel_user.h"
#include "excel/excel_force.h"
#include "excel/excel_hero.h"
#include "excel/excel_world.h"
#include "excel/excel_LocalizingTable.h"
#include "excel/excel_ServerResult.h"
#include "excel/excel_ClientResult.h"
#pragma  warning ( default:4251 )
#pragma  warning ( default:4181)



#define var_enum_test_Excel(var_func)\
	var_func(jAPP_NAME,CSV_PATH, _T("csv\\test_excel\\"), 0,"CSV FILE PATH")\

var_enum_test_Excel(jCV_DECLARE);



#ifndef jNOT_USE_SQ_BIND_CODE
#define SQPLUS_CONST_OPT
#include "base/jSQ_bind.h"
DECLARE_INSTANCE_TYPE(db_uid_type);
#endif


#define for_each_Sys_files(X)\
	X(excel_test)\
	X(excel_test2)\
	X(excel_ServerResult)\
	X(excel_ClientResult)\
	X(excel_user)\
	X(excel_force)\
	X(excel_hero)\
	X(excel_world)\
	X(excel_LocalizingTable)\

#define jEXCEL_DECL_csv_namespace_ALL(FILE_NAME) _jJOIN_5(for_each_,nEXCEL,_,FILE_NAME,_Sys_STRUCT_LIST)(jEXCEL_DECL_csv_namespace);
for_each_Sys_files(jEXCEL_DECL_csv_namespace_ALL)


void Load_Common_CSV(OUT tfname_t szDir);
#endif // __excel_all_header__
