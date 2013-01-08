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

//using namespace nTR_excel::nAQ;

#include "../TExcelData/TExcelData.h"

/*

X(nTR_excel::nErrorResult,Sys_ServerResult)\
X(nTR_excel::nErrorResult,Sys_ClientResult)\
\

*/
// name , table , keytype 
#define for_each_CSV_FILE_common(X)\
	X(nTR_excel::nLocal,Sys_LocalizingText)\
	X(nTR_excel::nLocal,Sys_LocalizingWord)\
	X(nTR_excel::nAQ, Sys_Tile)\
	X(nTR_excel::nAQ, Sys_World)\
	X(nTR_excel::nAQ, Sys_Castle)\
	X(nTR_excel::nAQ, Sys_CastlePos)\
	X(nTR_excel::nAQ, Sys_Force)\
	X(nTR_excel::nAQ, Sys_Hero)\
	\
	X(nTR_excel::nAQ, Sys_T_HQ)\
	X(nTR_excel::nAQ, Sys_T_Bar)\
	X(nTR_excel::nAQ, Sys_T_House)\
	X(nTR_excel::nAQ, Sys_T_Farm)\
	X(nTR_excel::nAQ, Sys_T_Barrack)\
	X(nTR_excel::nAQ, Sys_T_Camp)\
	X(nTR_excel::nAQ, Sys_T_Depot)\

#define for_each_CSV_FILE(X) for_each_CSV_FILE_common(X)\

	//X(nTR_excel::nLocal,Sys_LocalizingText)\


//#define jDECL_csv_namespace(Name,Table) using namespace Name;
for_each_CSV_FILE(jDECL_csv_namespace);


//#define jCSV(Table) g_##Table

/* *_* by icandoit : 2008-08-27 10:58:45
// »ç¿ë ¿¹
	int iTot = jCSV(Sys_Word_Filter).size();
	for(int ii =0; ii < iTot ;++ii)
	{
		Sys_Word_Filter* pNode = jCSV(Sys_Word_Filter).at(i);
	}
	Sys_Word_Filter* pNode = jCSV(Sys_Word_Filter).find(234);
*/ //*_* by icandoit : 2008-08-27 10:58:47


typedef nUtil::jCSV_File<Sys_TownPos> Sys_TownPos_List_t;
extern T_SERVER_LIB_API Sys_TownPos_List_t* jCSV_Sys_TownPos(Sys_Castle_id_t csid);
extern T_SERVER_LIB_API Sys_TownPos* jCSV_Sys_TownPos(Sys_Castle_id_t csid,Sys_TownPos_id_t tpsid);

extern T_SERVER_LIB_API void Load_Common_CSV(tfname_t szDir);
#endif // __TR_csv_loader_he234234ader__
