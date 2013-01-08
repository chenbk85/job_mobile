/* file : TR_csv_loader.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-28 10:33:29
comp.: www.actoz.com
title : 
desc : 


*/

#ifndef __TR_csv_loader_he234234ader__
#define __TR_csv_loader_he234234ader__
#pragma once


#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

#include "interface/net/jDebugPrint.h"
#include "interface/net/excel_code_util.h"
#include "Interface/net/net_common_code.h"
#include "header/jCSV_File.h"
#include "header/nNET_Stream.h"

#define jEXCEL_LIB_API
#define jEXCEL_SERVER_SIDE_CODE
#define nExcelUtil nMech

namespace nMech
{
	typedef int undefined_t;
}

#pragma warning ( disable:4181)
#pragma warning ( disable:4251)
#include "db_type.h"
#include "excel/table_type.h"
#include "excel/excel_enum.h"
#include "excel/sam_hero.h"

#pragma  warning ( default:4251 )
#pragma  warning ( default:4181)

using namespace nExcelUtil::nEXCEL;



#ifndef jNOT_USE_SQ_BIND_CODE
#define SQPLUS_CONST_OPT
#include "base/jSQ_bind.h"
DECLARE_INSTANCE_TYPE(db_uid_type);
#endif



#define for_each_Sys_files(X)\
	X(sam_hero)\

#define jEXCEL_DECL_csv_namespace_ALL(FILE_NAME) _jJOIN_5(for_each_,nTESTSERVER,_,FILE_NAME,_Sys_STRUCT_LIST)(jEXCEL_DECL_csv_namespace);
//for_each_Sys_files(jEXCEL_DECL_csv_namespace_ALL)



/* *_* by icandoit : 2008-08-27 10:58:45
// »ç¿ë ¿¹
	int iTot = jCSV(Sys_Word_Filter).size();
	for(int ii =0; ii < iTot ;++ii)
	{
		Sys_Word_Filter* pNode = jCSV(Sys_Word_Filter).at(i);
	}
	Sys_Word_Filter* pNode = jCSV(Sys_Word_Filter).find(234);
*/ //*_* by icandoit : 2008-08-27 10:58:47



extern AQ_SERVER_LIB_API void Load_Common_CSV(tfname_t szDir);
#endif // __TR_csv_loader_he234234ader__
