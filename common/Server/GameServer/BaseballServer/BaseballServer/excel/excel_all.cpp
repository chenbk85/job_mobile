/* file : excel_all.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-03-16 15:20:04
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "excel/db_type.h"
#include "excel_all.h"
#include "common/header/uStringParsor.h"


tcstr ToString(jItemObj1_ref v,tname1024_t sz)
{
	jt_sprintf(sz,_T("aaa;%d;%4.3f;%s") , v.i,v.f,v.s.c_str() );
	return sz;
}
jItemObj1_ref FromString(jItemObj1* v,tcstr sz)
{ 
	// sz = "ITEM1;1;2.3;NAME"
	vector<tstring> out;
	nString::jSplit(sz,_T(";"),out);
	if(out.size()!=4)
	{
		tname1024_t szError;
		jt_sprintf(szError,_T("%s> out.size()!=4 : %s"), jFUNC ,sz);
		throw szError;
	}
	v->aa.clear();
	v->i=jt_atoi(out[1].c_str());
	v->f=jt_atof(out[2].c_str());
	v->s=jT(out[3]);
	v->pE=0;
	return *v;
}

jItemObj1_ref FromString(jItemObj1* v,tstring& sz)
{ 
	return FromString(v,sz.c_str()); 
}


void Load_Common_CSV()
{
	static bool iFirstRun=false;
	if(iFirstRun==true) return;
	iFirstRun = true;

	tfname_t buf;

	//nFileSystem::jFolder dir;

	tstring currDir = fs::current_path().string();
	#define jLOAD_CSV(Table,Name,ns1,ns2) jt_sprintf(buf , _T("%s/csv/file_%s.csv"),currDir.c_str() ,jS(Table) ); g_##Table.Load(buf);
	#define jEXCEL_jLOAD_CSV(FILE_NAME) _jJOIN_5(for_each_,nEXCEL,_,FILE_NAME,_Sys_STRUCT_LIST)(jLOAD_CSV);
	for_each_Sys_files(jEXCEL_jLOAD_CSV);

	g_Excel_PostLoader.Run();

}


void debug_here()
{
	printf("asdf");

}