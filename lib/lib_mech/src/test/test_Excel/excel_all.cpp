/* file : excel_all.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-03-16 15:20:04
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "excel_all.h"


var_enum_test_Excel(jCV_DEFINE);

#ifndef jNOT_USE_SQ_BIND_CODE
DECLARE_INSTANCE_TYPE_COMPLAX_csv(jItemObj1);
#endif //jNOT_USE_SQ_BIND_CODE

tcstr ToString(jItemObj1_ref v,tname1024_t sz)
{
	jt_sprintf(sz,_T("aaa;%d;%4.3f;%s") , v.i,v.f,v.s.c_str() );
	return sz;
}

jItemObj1_ref FromString(wcstr sz , jItemObj1& v )
{ 
	// sz = "ITEM1;1;2.3;NAME"
	vector<wstring> out;
	nString::jSplitW(sz,L";",out);
	if(out.size()!=4)
	{
		tname1024_t szError;
		jt_sprintf(szError,jFUNC1 _T("out.size()!=4 : %s"), sz);
		throw szError;
	}
	v.aa.clear();
	v.i=jw_atoi(out[1].c_str());
	v.f=jw_atof(out[2].c_str());
	v.s=jT(out[3]);
	v.pE=0;
	return v;
}

jItemObj1_ref FromString(wstring& sz,jItemObj1& v)
{ 
	return FromString( sz.c_str() , v ); 
}


void Load_Common_CSV(OUT tfname_t szDir)
{
	static bool iFirstRun=false;
	if(iFirstRun==true) return;
	iFirstRun = true;

	tfname_t buf;

	nFileSystem::jFolder dir;

	#define jLOAD_CSV(Table,Name,ns1,ns2) js_sprintf(buf , _T("%s\\file_%s.csv") ,pv_CSV_PATH->Get_cstr(), jS(Table) ); g_##Table.Load(buf);
	#define jEXCEL_jLOAD_CSV(FILE_NAME) _jJOIN_5(for_each_,nEXCEL,_,FILE_NAME,_Sys_STRUCT_LIST)(jLOAD_CSV);
	for_each_Sys_files(jEXCEL_jLOAD_CSV);

	g_Excel_PostLoader.Run();

	jt_strcpy_s(szDir,256, pv_CSV_PATH->Get_cstr());

}
