// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"
#include "PerfReg.h"


nFileSystem::jFileName g_DLLPath;

cstr get_my_service_url(fname_t buf)
{
#if 0
	tcstr sz = jt_strrchr(g_DLLPath.dir, '\\');
	++sz;
	jt_sprintf(buf, _T("%s_%s"),g_DLLPath.fname,sz);
#else
	jt_strcpy(buf, g_DLLPath.fname);
#endif
	return buf;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	fname_t szDLLPath;
	GetModuleFileName(hModule, szDLLPath, _countof(szDLLPath));
	g_DLLPath.Init(szDLLPath);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


extern "C"
{
	JPERFCOUNTER_API void* jCreateInterface(jIE* pE)
	{
		return  &g_pjPerfCounter;
	}
	JPERFCOUNTER_API void jDeleteInterface()
	{
		g_pjPerfCounter.End();
	}
	//DWORD JPERFCOUNTER_API WINAPI jPerf_Open(LPWSTR lpDevNames)
	DWORD __declspec(dllexport) WINAPI jPerf_Open(LPWSTR lpDevNames)
	{
		lpDevNames;

		jAUTO_LOCK_MU(g_jMutex);

		if(!nPerfReg::load_My_ObjectList())
			return (ERROR_SUCCESS);

		PERF_OBJECT_TYPE &h = g_header_PERF_OBJECT_TYPE;
		ZeroMemory(&h, sizeof(PERF_OBJECT_TYPE));

		nPerfReg::load_Counter_Contents();


		LPTSTR	Token = _tcstok(g_szMyObjectList, szTOKEN);
		DWORD FirstIndex				= _ttoi(Token);

		g_pjPerfCounter.update_header_PERF_OBJECT_TYPE();

		h.HeaderLength			= sizeof(PERF_OBJECT_TYPE);
		h.ObjectNameTitleIndex	= FirstIndex;
		h.ObjectNameTitle			= NULL;
		h.ObjectHelpTitleIndex	= FirstIndex + 1;
		h.ObjectHelpTitle			= NULL;
		h.DetailLevel				= PERF_DETAIL_NOVICE;
		h.DefaultCounter			= 0;
		h.NumInstances			= PERF_NO_INSTANCES;
		h.CodePage				= 0;

		// 처음은 무시해 준다.
		Token = _tcstok(NULL, szTOKEN);
		while (Token)
		{
			DWORD idx= _ttoi(Token);
			Token = _tcstok(NULL, szTOKEN);
			g_pjPerfCounter.Init_PerfCounterNode(idx);
		}
		g_pjPerfCounter.update_header_PERF_OBJECT_TYPE();
		return(ERROR_SUCCESS);
	}

	DWORD JPERFCOUNTER_API WINAPI jPerf_Close(VOID)
	{
		return(ERROR_SUCCESS);
	}

	DWORD JPERFCOUNTER_API WINAPI jPerf_Collect(LPWSTR lpValueName, 
		LPVOID* lppData, 
		LPDWORD lpcbTotalBytes, 
		LPDWORD lpNumObjectTypes)
	{
		jAUTO_LOCK_MU(g_jMutex);
		*lpcbTotalBytes		= g_header_PERF_OBJECT_TYPE.TotalByteLength;
		*lpNumObjectTypes	= (DWORD) m_vecMyCountObject.size() + 1;

		PBYTE *Data			= (PBYTE*) lppData;

		CopyMemory(*Data, &g_header_PERF_OBJECT_TYPE, sizeof(PERF_OBJECT_TYPE));
		*Data += sizeof(PERF_OBJECT_TYPE);

		size_t currCounterSize = m_vecMyCountObject.size();

		for (DWORD i=0;i<currCounterSize;i++)
		{
			CopyMemory(*Data, &m_vecMyCountObject[i]->Data, sizeof(m_vecMyCountObject[i]->Data));
			//assert( sizeof(m_vecMyCountObject[i]->Data ) == sizeof(PERF_COUNTER_DEFINITION) );
			*Data += sizeof(PERF_COUNTER_DEFINITION);
		}

		DWORD ValueLength = (DWORD) (sizeof(DWORD) * currCounterSize);
		CopyMemory(*Data, &ValueLength, sizeof(DWORD));
		*Data += sizeof(DWORD);

		for (DWORD i=0 ; i<currCounterSize ; i++)
		{
			CopyMemory(*Data, &m_vecMyCountObject[i]->Value, sizeof(DWORD));
			*Data += sizeof(DWORD);
		}
		return(ERROR_SUCCESS);
	}
}//extern "C"

#pragma comment(linker, "/export:jPerf_Open=_jPerf_Open@4")
#pragma comment(linker, "/export:jPerf_Close=_jPerf_Close@0")
#pragma comment(linker, "/export:jPerf_Collect=_jPerf_Collect@16")

