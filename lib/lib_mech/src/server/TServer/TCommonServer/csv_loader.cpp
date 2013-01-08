/* file : TR_csv_loader.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-28 10:33:31
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TCommonServer.h"

#include "header/jCSV_File.h"
#include "../TExcelData/TExcelData.h"

#include "csv_loader.h"


#define for_each_make_index_csv(X)\
	X(Sys_LocalizingText)\
	X(Sys_LocalizingWord)\
	X(Sys_Castle)\
	X(Sys_Force)\
	X(Sys_Hero)\

#define define_index_func(table) tcstr jIndexer_##table(table* pN){return pN->Get_name();}

for_each_make_index_csv(define_index_func);


jLIST_TYPEDEF_map(tstring,Sys_TownPos_List_t,g_mapSys_TownPos);

void UnLoad_Common_CSV()
{
	#define jUnLOAD_CSV(Name,Table) g_##Table.UnLoad();
	for_each_CSV_FILE(jUnLOAD_CSV);
};


T_SERVER_LIB_API void Load_Common_CSV(tfname_t szDir)
{
	static bool iFirstRun=false;
	if(iFirstRun==true) return;
	iFirstRun = true;

	tfname_t buf;
	
	nFileSystem::jFolder dir;

	#define jLOAD_CSV(Name,Table) js_sprintf(buf , _T("%s\\file_%s.csv") ,pv_CSV_PATH->Get_cstr(), jS(Table) ); g_##Table.Load(buf);
	for_each_CSV_FILE(jLOAD_CSV);
	jt_strcpy_s(szDir,256, pv_CSV_PATH->Get_cstr());

	#define call_index_func(table )	g_##table.MakeIndex(jIndexer_##table);
	for_each_make_index_csv(call_index_func);
	
	for(size_t i=1; i <= jCSV(Sys_CastlePos).size() ; ++i)
	{
		Sys_CastlePos* pN = jCSV(Sys_CastlePos).at(i);
		g_mapSys_TownPos_it it = g_mapSys_TownPos.find(pN->Get_castle_map());
		if(it!=g_mapSys_TownPos.end()) continue;
		nFileSystem::UFileName fn(pN->Get_castle_map());
		js_sprintf(buf , _T("%s\\file_Sys_TownPos_%s.csv") ,szDir, fn.fname);
		if(!nFileSystem::jFolder::Is_Exist(buf))
		{
			jWARN1(_T("NOT EXIST : %s"),buf);
			continue;
		}
		g_mapSys_TownPos[pN->Get_castle_map()].Load(buf);
	}
	

}

extern T_SERVER_LIB_API Sys_TownPos_List_t* jCSV_Sys_TownPos(Sys_Castle_id_t csid)
{
	Sys_CastlePos* pN = jCSV(Sys_CastlePos).at(csid);
	if(!pN) return 0;
	g_mapSys_TownPos_it it = g_mapSys_TownPos.find(pN->Get_castle_map());
	if(it==g_mapSys_TownPos.end()) return 0;
	return &it->second;

}
T_SERVER_LIB_API nAQ::Sys_TownPos* jCSV_Sys_TownPos(Sys_Castle_id_t csid,Sys_TownPos_id_t tpsid)
{
	Sys_TownPos_List_t* pCSV = jCSV_Sys_TownPos(csid);
	if(!pCSV) 
	{
		return 0;
	}
	return pCSV->at(tpsid);
}