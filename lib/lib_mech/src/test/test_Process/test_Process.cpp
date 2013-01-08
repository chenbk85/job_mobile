// test_Process.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	if(argc>=3 && !jt_strcmp(argv[1],_T("-kill_name")))
	{
		void kill_Process_byName(tcstr strProcessName,DWORD skip_id);
		DWORD skip_id=0;
		if(argc>=4)
			skip_id = jt_atoi(argv[3]);

		kill_Process_byName(argv[2], skip_id);
		return 0 ;
	}
	if(argc>=3 && !jt_strcmp(argv[1],_T("-kill_id")))
	{
		void kill_Process_byID(DWORD);	kill_Process_byID(jt_atoi(argv[2]));
		return 0 ;
	}
	if(argc>=2 && !jt_strcmp(argv[1],_T("-loop")))
	{
		int i=0;
		while(1)
		{
			printf("%d-%d\n", GetCurrentProcessId(),++i);
			Sleep(100);
		}
	}

	void print_Process();	print_Process();

	return 0;
}

