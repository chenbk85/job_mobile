/* file : excel_all.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-03-16 15:20:01
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __excel_all_header__
#define __excel_all_header__
#pragma once

#define for_each_Sys_files(X)\
	X(excel_test)\
	X(excel_test2)\
	X(excel_baseball_table)\
	X(excel_baseball_string_table)\



#define jEXCEL_DECL_csv_namespace_ALL(FILE_NAME) _jJOIN_5(for_each_,nEXCEL,_,FILE_NAME,_Sys_STRUCT_LIST)(jEXCEL_DECL_csv_namespace);
for_each_Sys_files(jEXCEL_DECL_csv_namespace_ALL)


void Load_Common_CSV(OUT tfname_t szDir);



#endif // __excel_all_header__
