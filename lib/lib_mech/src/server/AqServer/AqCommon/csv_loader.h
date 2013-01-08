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


#include "header/jCSV_File.h"
namespace nMech
{
	typedef int undefined_t;
}

#include "network/excel/LocalizingTable.h"
#include "network/excel/ClientResult.h"
#include "network/excel/ServerResult.h"

#pragma warning ( disable:4181)
#pragma warning ( disable:4251)

#include "network/excel/aq_enum.h"
#include "network/excel/sam_world.h"
#include "network/excel/sam_user.h"
#include "network/excel/sam_hero.h"
#include "network/excel/Sam_Castle.h"
#include "network/excel/sam_force.h"

#pragma  warning ( default:4251 )
#pragma  warning ( default:4181)

using namespace nTR_excel::nAQ;


#include "network/common_csv.h"

#define for_each_CSV_FILE(X) for_each_CSV_FILE_common(X)\

	//X(nTR_excel::nLocal,Sys_LocalizingText)\


#define jDECL_csv_namespace(Name,Table) using namespace Name;
for_each_CSV_FILE(jDECL_csv_namespace);


#define jCSV(Table) g_##Table

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
extern AQ_SERVER_LIB_API Sys_TownPos_List_t* jCSV_Sys_TownPos(Sys_Castle_id_t csid);
extern AQ_SERVER_LIB_API Sys_TownPos* jCSV_Sys_TownPos(Sys_Castle_id_t csid,Sys_TownPos_id_t tpsid);

extern AQ_SERVER_LIB_API void Load_Common_CSV(tfname_t szDir);
#endif // __TR_csv_loader_he234234ader__
