#include "stdafx.h"
#ifdef _WIN32
#include <time.h>
#endif

#include "jLog.h"
#include "Validator.h"
#include "header/jClipboard.h"
#include "interface/ITimer.h"

volatile float __f__=10;

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	__f__++;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		printf("");
		break;
	}
	return TRUE;
}


