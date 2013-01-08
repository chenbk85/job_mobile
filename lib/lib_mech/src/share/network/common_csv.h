/* file : common_csv.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-23 21:12:06
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __common_csv_header__
#define __common_csv_header__
#pragma once

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


#endif // __common_csv_header__
