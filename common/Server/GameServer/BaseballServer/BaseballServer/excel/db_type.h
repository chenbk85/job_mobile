/* file : common_test_server.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-06 10:56:59
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __db_type_hlksdjfoiwejfk__
#define __db_type_hlksdjfoiwejfk__
#pragma once

#ifdef DEF_WINDOWS
#define EXCEL_CSV_STRING_VECTOR std::vector<std::tstring>
#define excel_wcstr	tcstr
#define EXCEL_WSTRING_SPLIT_CODE vector<tstring> out;nString::jSplit(sz,_T(";"),out);
#define nExcelUtil nMech
#define jAPP_NAME test_Excel
#define jNOT_USE_SQ_BIND_CODE
#endif ///#ifdef DEF_WINDOWS


#define jEXCEL_LIB_API

#include "header/jHeader.h"
using namespace nMech;
#include "excel/db_uid_type.h"
#include "excel/Excel_code_util.h"
#include "excel/net_common_code.h"
namespace nMech{}
#define nExcelUtil nMech


#include "excel/jDebugPrint.h"
#include "header/jCSV_File.h"
#include "excel/net_common_code.h"


#include "code/table_type.h"



struct jItemObj1
{
	jIE* pE;
	tstring s;
	int i;
	float f;
	vector<int> aa;
};


// 엑셀에서 사용하는 모든 사용자 자료형이 언급됨.
// 생성방법은 엑셀 11_Tool.xlsm의 도움말(프로그래머용 )탭을  참고하세요.
#include "excel/code/table_type.h"


typedef jItemObj1& jItemObj1_ref;
tcstr ToString(jItemObj1& v,tname1024_t sz);
jItemObj1_ref FromString(jItemObj1* v,excel_wcstr sz);
jItemObj1_ref FromString(jItemObj1* v,tstring& sz);


//--------------------------------------------------------------------------
// 엑셀 자동 코드 해더 
//--------------------------------------------------------------------------
#pragma warning ( disable:4181)
#pragma warning ( disable:4251)
#include "excel/code/excel_enum.h"
#include "excel/code/excel_test.h"
#include "excel/code/excel_test2.h"
#include "excel/code/excel_baseball_table.h"
#include "excel/code/excel_baseball_string_table.h"

#pragma  warning ( default:4251 )
#pragma  warning ( default:4181)


namespace nExcelUtil
{
	void jExcelData_ReadCSV      (IN EXCEL_CSV_STRING_VECTOR &out,IN size_t index	,OUT nEXCEL::Sys__T_Base*);
	void jExcelData_ReadCSV_array(IN EXCEL_CSV_STRING_VECTOR &out,IN size_t index	,OUT std::vector<int32>& v, IN size_t iArray);
}



#endif // __db_type_hlksdjfoiwejfk__

