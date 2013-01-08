// test_template.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "common/jInit.h"


int _tmain(int argc, _TCHAR* argv[])
{
	jMech_Init();

	tfname_t szDir;
	Load_Common_CSV(szDir);

	size_t i=0;

#define FUNC_print_CSV(Table,Name,ns1,ns2) for(i=0 ;i<jCSV(Table).size() ; ++i)\
	{\
		Table*pN=jCSV(Table).at((int32)(i+1));\
		if(pN)\
			pN->DebugPrint();printf("\n\n");\
	};\
	printf("-------------------------------\n\n");

#define jEXCEL_FUNC_print_CSV(FILE_NAME) _jJOIN_3(for_each_nEXCEL_,FILE_NAME,_Sys_STRUCT_LIST)(FUNC_print_CSV);\
	printf("============================================\n\n");

	for_each_Sys_files(jEXCEL_FUNC_print_CSV);


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

	jMech_Close();
	return 0;
}

