/* file : TR_csv_loader.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-28 10:33:31
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "csv_loader.h"

namespace nMech{namespace nEXCEL{Excel_PostLoader g_Excel_PostLoader;}}


AQ_SERVER_LIB_API void Load_Common_CSV(tfname_t szDir)
{
	static bool iFirstRun=false;
	if(iFirstRun==true) return;
	iFirstRun = true;

	tfname_t buf;
	
	nFileSystem::jFolder dir;

	#define jLOAD_CSV(Table,Name,ns1,ns2) js_sprintf(buf , _T("%s\\file_%s.csv") ,pv_CSV_PATH->Get_cstr(), jS(Table) ); g_##Table.Load(buf);

	#define jEXCEL_jLOAD_CSV(FILE_NAME) _jJOIN_5(for_each_,nTESTSERVER,_,FILE_NAME,_Sys_STRUCT_LIST)(jLOAD_CSV);
	
	for_each_Sys_files(jEXCEL_jLOAD_CSV)

	jt_strcpy(szDir, pv_CSV_PATH->Get_cstr());

}

