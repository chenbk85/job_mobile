// dllmain.cpp : DLL ���� ���α׷��� �������� �����մϴ�.
#include "stdafx.h"




//_ACCESS_POOL;
volatile float aaa;
HANDLE g_hModule;
BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	g_hModule = hModule;
	aaa = 0.122f; //���� ����������..
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
