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

#define EXCEL_CSV_STRING_VECTOR std::vector<std::wstring>
#define excel_wcstr	wcstr
#define EXCEL_WSTRING_SPLIT_CODE vector<wstring> out;nString::jSplitW(sz,L";",out);


#include <boost/bind.hpp>
#include <sqltypes.h>
#include "interface/net/Excel_code_util.h"
#include "excel/table_type.h"
#include "excel/excel_enum.h"


namespace nExcelUtil
{
	void jExcelData_ReadCSV      (IN EXCEL_CSV_STRING_VECTOR &out,IN size_t index	,OUT Sys__T_Base*);
	void jExcelData_ReadCSV_array(IN EXCEL_CSV_STRING_VECTOR &out,IN size_t index	,OUT std::vector<int32>& v, IN size_t iArray);
}

for_each_nEXCEL_excel_enum_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE_PROTO);



#endif // __db_type_hlksdjfoiwejfk__

