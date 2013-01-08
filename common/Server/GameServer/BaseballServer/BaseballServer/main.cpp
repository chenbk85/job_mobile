#pragma warning(disable : 4819)

//
//  main.cpp
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//
#include "stdafx.h"
#include "BB_header.h"



int main (int argc, const char * argv[])
{
    fname_t szCurDir;
    getcwd(szCurDir,255);
    jLOG("curr dir = %s", szCurDir);

	void Load_Common_CSV();Load_Common_CSV();

	size_t i=0;

#define FUNC_print_CSV(Table,Name,ns1,ns2) for(i=0 ;i<jCSV(Table).size() ; ++i)\
	{\
	Table*pN=jCSV(Table).at(i+1);\
	if(pN)\
	pN->DebugPrint();printf("\n\n");\
	};\
	printf("-------------------------------\n\n");

#define jEXCEL_FUNC_print_CSV(FILE_NAME) _jJOIN_3(for_each_nEXCEL_,FILE_NAME,_Sys_STRUCT_LIST)(FUNC_print_CSV);\
	printf("============================================\n\n");

//	for_each_Sys_files(jEXCEL_FUNC_print_CSV);


	for(i=0 ;i<jCSV(Sys_T_Test4).size() ; ++i)
	{
		Sys_T_Test4*pN=jCSV(Sys_T_Test4).at(i);
		if(pN)
		{
			pN->DebugPrint();
			printf("\n\n");
		}
	};
	printf("-------------------------------\n\n");

    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: BaseballServer <port>\n";
            return 1;
        }
		int port =atoi(argv[1]);
		nMOB::run_tcp_server(&g_BB_Plugin_NetIOModel,port );

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}

