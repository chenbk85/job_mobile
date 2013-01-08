/** 
\file  winos.cpp
\brief 윈도우 OS( 비스타 포함 )에 관련된 여러가지 함수
*/

//----------------------------------------------------------------------------
// winos.cpp
//
// (C)Copyright 2003, Flagship Studios. All rights reserved.
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// INCLUDE
//----------------------------------------------------------------------------
#include "stdafx.h"
#include <ShlObj.h>
#include "resource.h"
#include "appcommon.h"
#ifdef WIN32


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL PGetModuleDirectory(
	OS_PATH_CHAR * path,
	int size)
{
	int len = OS_PATH_FUNC(GetModuleFileName)(NULL, path, size);
	len = PStrGetPath(path, size, path);

	OS_PATH_CHAR* last = path + len;
	for(;;)
	{
		if (last > path && (*last == OS_PATH_TEXT('\\') || *last == OS_PATH_TEXT('/') || *last == OS_PATH_TEXT(':')))
		{
			last--;
		}
		while (last > path && !(*last == OS_PATH_TEXT('\\') || *last == OS_PATH_TEXT('/') || *last == OS_PATH_TEXT(':')))
		{
			last--;
		}
		if (*last != 0 &&
			(PStrICmp(last + 1, OS_PATH_TEXT("bin\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("MP_x86\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("SP_x86\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("MP_x64\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("SP_x64\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debug\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debugtugboat\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debugoptimizedtugboat\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debugdx10\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debugoptimized\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debugoptimizeddx10\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debugoptimizedserver\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("profile\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("profiledx10\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("profiletugboat\\")) == 0 ||			
			PStrICmp(last + 1, OS_PATH_TEXT("release\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("releaseclientonly\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("releasedemo\\")) == 0 ||			
			PStrICmp(last + 1, OS_PATH_TEXT("releasedx10\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("releasetugboatclientonly\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("releasetugboat\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("Win32\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("x64\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debughellgateserver\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debugtugboatserver\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("retailhellgateserver\\")) == 0 ||
			// 이창용 / 2010-2-13 / 서버 복원 작업
				//PStrICmp(last + 1, OS_PATH_TEXT("debugmythosserver\\")) == 0 ||
			//-----------------------------------------------------------
			PStrICmp(last + 1, OS_PATH_TEXT("retailhellgateserver\\")) == 0
#ifdef USE_PIXO
			||
			PStrICmp(last + 1, OS_PATH_TEXT("debugpixomatic\\")) == 0 ||
			PStrICmp(last + 1, OS_PATH_TEXT("debugoptimizedpixomatic\\")) == 0
#endif // USE_PIXO
			))
		{
			*(last + 1) = 0;
		}
		else
		{
			break;
		}
	}

	return TRUE;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL PSetCurrentDirectory(
	const OS_PATH_CHAR * path)
{
	return OS_PATH_FUNC(SetCurrentDirectory)(path);
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL PGetMemoryStatus(
	MEMORYSTATUSEX & memory_status)
{
	structclear(memory_status);
	memory_status.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memory_status);
	return TRUE;
}


//----------------------------------------------------------------------------
// TIME FUNCTIONS
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
struct PGLOBAL_PERFORMANCE_FREQUENCY
{
	UINT64 iiPerformanceFrequency;

	PGLOBAL_PERFORMANCE_FREQUENCY(
		void);
};


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
PGLOBAL_PERFORMANCE_FREQUENCY::PGLOBAL_PERFORMANCE_FREQUENCY(
	void)
{
	LARGE_INTEGER temp;
	BOOL bResult = QueryPerformanceFrequency(&temp);
	ASSERT(bResult);
	if (bResult)
	{
		iiPerformanceFrequency = (UINT64)temp.QuadPart;
	}
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
UINT64 PGetSystemTimeIn100NanoSecs(
	void)
{
	FILETIME filetime;
	GetSystemTimeAsFileTime(&filetime);
	ULARGE_INTEGER temp;
	temp.LowPart = filetime.dwLowDateTime;
	temp.HighPart = filetime.dwHighDateTime;
	return (UINT64)temp.QuadPart;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
UINT64 PGetPerformanceFrequency(
	void)
{
	static PGLOBAL_PERFORMANCE_FREQUENCY perf_freq;

	return perf_freq.iiPerformanceFrequency;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
HANDLE PFindFirstFile(
	TCHAR * filename,
	FIND_DATA * data)
{
	UNREFERENCED_PARAMETER(filename);
	UNREFERENCED_PARAMETER(data);
	return INVALID_HANDLE_VALUE;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL PFindNextFile(
	HANDLE handle,
	FIND_DATA * data)
{
	UNREFERENCED_PARAMETER(data);
	UNREFERENCED_PARAMETER(handle);
	return FALSE;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void PFindClose(
	HANDLE handle)
{
	UNREFERENCED_PARAMETER(handle);
}


//----------------------------------------------------------------------------
// MODULE
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
FARPROC PGetProcAddress(
	TCHAR * module,
	char * procname)
{
	HMODULE hModule = GetModuleHandle(module);
	ASSERT_RETNULL(hModule);

	return GetProcAddress(hModule, procname);
}


//----------------------------------------------------------------------------
// CPU Timing
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// RDTSC  // don't use this, provided simply for reference
//----------------------------------------------------------------------------
extern "C"
{
#ifdef _M_X64
unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)
#define RDTSC	__rdtsc
#else
__inline unsigned __int64 rdtsc32(
	void) 
{
	unsigned __int64 t;
	__asm
	{
		rdtsc
		mov DWORD PTR[t], eax
		mov DWORD PTR[t + 4], edx
	}
	return t;
}
#define RDTSC rdtsc32
#endif
};


//----------------------------------------------------------------------------
// CPU Info
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------------
#define CPUID_MAX_PROC					32				// max number of logical processors supported
// standard level 1
// ebx
#define CPUID_LOGICAL_COUNT_START		16				// number of logical processors
#define CPUID_LOGICAL_COUNT_END			23
#define CPUID_APIC_ID_START				24				// APIC ID
#define CPUID_APIC_ID_END				31
// edx
#define CPUID_SSE_FEATURE				25				// SSE feature flag
#define CPUID_HYPER_THREADING_START		28				// hyper threading flag
#define CPUID_HYPER_THREADING_END		28

// standard level 4
// eax
#define CPUID_CORES_COUNT_START			26	
#define CPUID_CORES_COUNT_END			31


//----------------------------------------------------------------------------
// reads a mask from flag, expressed in startbit:endbit
//----------------------------------------------------------------------------
unsigned int GetBitValue(
	DWORD dw,
	unsigned int startbit,
	unsigned int endbit)
{
	ASSERT_RETZERO(endbit >= startbit && endbit <= 31);

	DWORD mask = ((1 << (endbit - startbit + 1)) - 1) << startbit;
	return ((dw & mask) >> startbit);
}


//----------------------------------------------------------------------------
// CPUID
//----------------------------------------------------------------------------
struct CPUID_ARGS
{
	DWORD	eax;
	DWORD	ebx;
	DWORD	ecx;
	DWORD	edx;
};


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
extern "C"
{
#ifdef _M_X64
void cpuid64(
	CPUID_ARGS * args);
#define CPUID	cpuid64
#else
inline void cpuid32(
	CPUID_ARGS * args)
{
	__asm
	{
		mov edi, args
		mov eax, [edi].eax
		mov ecx, [edi].ecx
		cpuid
		mov [edi].eax, eax
		mov [edi].ebx, ebx
		mov [edi].ecx, ecx
		mov [edi].edx, edx
	}
}
#define CPUID	cpuid32
#endif
};


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static unsigned int sCPUInfoGetMaxStandardLevel(
	void)
{
	CPUID_ARGS args;
	structclear(args);
	args.eax = 0;

	__try
	{
		CPUID(&args);
	}
#pragma warning(suppress:6320)
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
	return args.eax;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static BOOL sCPUIsAMD(
	void)
{
	if (sCPUInfoGetMaxStandardLevel() < 1)
	{
		return FALSE;
	}
	
	CPUID_ARGS args;
	structclear(args);
	args.eax = 0;
	CPUID(&args);
	
	if (args.ebx == 0x68747541 && args.ecx == 0x444d4163&& args.edx == 0x69746e65)
	{
		return TRUE;
	}
	return FALSE;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static BOOL sCPUInfoHyperThreading(
	void)
{
	if (sCPUInfoGetMaxStandardLevel() < 1)
	{
		return FALSE;
	}
	
	CPUID_ARGS args;
	structclear(args);
	args.eax = 1;
	CPUID(&args);
	
	return (BOOL)GetBitValue(args.edx, CPUID_HYPER_THREADING_START, CPUID_HYPER_THREADING_END);
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static unsigned int sCPUInfoGetLogicalProcessorsPerPackage(
	void)
{
	if (sCPUInfoGetMaxStandardLevel() < 1)
	{
		return 1;
	}
	
	CPUID_ARGS args;
	structclear(args);
	args.eax = 1;
	CPUID(&args);
	
	if (!GetBitValue(args.edx, CPUID_HYPER_THREADING_START, CPUID_HYPER_THREADING_END))
	{
		return 1;
	}
	
	return GetBitValue(args.ebx, CPUID_LOGICAL_COUNT_START, CPUID_LOGICAL_COUNT_END);
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static unsigned int sCPUInfoGetCoresPerPackage(
	void)
{
	if (sCPUIsAMD())
	{
		return sCPUInfoGetLogicalProcessorsPerPackage();
	}

	if (sCPUInfoGetMaxStandardLevel() < 4)
	{
		return 1;
	}
	
	CPUID_ARGS args;
	structclear(args);
	args.eax = 4;
	args.ebx = 0;
	CPUID(&args);
	
	return GetBitValue(args.eax, CPUID_CORES_COUNT_START, CPUID_CORES_COUNT_END) + 1;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static unsigned int sCPUInfoGetAPICId(
	void)
{
	CPUID_ARGS args;
	structclear(args);
	args.eax = 1;
	CPUID(&args);
	return GetBitValue(args.ebx, CPUID_APIC_ID_START, CPUID_APIC_ID_END);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL CPUHasSSE( void )
{
	CPUID_ARGS args;
	structclear(args);
	args.eax = 1; // Get the standard bits
	CPUID(&args);

	return (BOOL)GetBitValue(args.edx, CPUID_SSE_FEATURE, CPUID_SSE_FEATURE);
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL CPUInfo(
	CPU_INFO & info)
{
	static CCritSectLite	g_csInfo;
	static BOOL				g_bGotInfo = FALSE;
	static CPU_INFO			g_Info;

	CSLAutoLock autolock(&g_csInfo);
	if (g_bGotInfo)
	{
		memcpy(&info, &g_Info, sizeof(info));
		return TRUE;
	}
	structclear(g_Info);

	DWORD_PTR dwProcessAffinity, dwSystemAffinity;
	ASSERT_RETFALSE(GetProcessAffinityMask(GetCurrentProcess(), &dwProcessAffinity, &dwSystemAffinity));
	unsigned int numProcessorsForProcess = COUNTBITS((DWORD)dwProcessAffinity);
	g_Info.m_TotalLogical = COUNTBITS((DWORD)dwSystemAffinity);
	ASSERT_RETFALSE(g_Info.m_TotalLogical <= CPUID_MAX_PROC);
	ASSERT_RETFALSE(numProcessorsForProcess >= 1 && g_Info.m_TotalLogical >= numProcessorsForProcess);

	struct CPU_PROC_INFO
	{
		unsigned int m_idSMT;
		unsigned int m_idCore;
		unsigned int m_idPackage;
	};
	CPU_PROC_INFO procinfo[CPUID_MAX_PROC];
	memclear(procinfo, sizeof(procinfo));

	// iterate logical processors & collect data
	for (unsigned int ii = 0; ii < g_Info.m_TotalLogical; ++ii)
	{
		if (SetThreadAffinityMask(GetCurrentThread(), (1 << ii)))
		{
			Sleep(0);

			++g_Info.m_AvailLogical;

			unsigned int numLogicalPerPackage = sCPUInfoGetLogicalProcessorsPerPackage();
			unsigned int numCorePerPackage = sCPUInfoGetCoresPerPackage();
			unsigned int maxLogicalProcessorsPerCore = numLogicalPerPackage / numCorePerPackage;

			unsigned int apicid = sCPUInfoGetAPICId();

			unsigned int CPUID_SMT_WIDTH = ((maxLogicalProcessorsPerCore > 1) ? BIT_SIZE(maxLogicalProcessorsPerCore - 1) : 0);
			unsigned int CPUID_SMT_ID_START = 0;
			unsigned int CPUID_SMT_ID_END = CPUID_SMT_ID_START + CPUID_SMT_WIDTH;
			if (CPUID_SMT_WIDTH > 0)
			{
				procinfo[ii].m_idSMT = GetBitValue(apicid, CPUID_SMT_ID_START, CPUID_SMT_ID_END - 1);
			}
			unsigned int CPUID_CORE_ID_WIDTH = ((numCorePerPackage > 1) ? BIT_SIZE(numCorePerPackage - 1) : 0);
			unsigned int CPUID_CORE_ID_START = CPUID_SMT_ID_END;
			unsigned int CPUID_CORE_ID_END = CPUID_CORE_ID_START + CPUID_CORE_ID_WIDTH;
			if (CPUID_CORE_ID_WIDTH > 0)
			{
				procinfo[ii].m_idCore = GetBitValue(apicid, CPUID_CORE_ID_START, CPUID_CORE_ID_END - 1);
			}
			unsigned int CPUID_PACKAGE_ID_START = CPUID_CORE_ID_END;
			unsigned int CPUID_PACKAGE_ID_END = 31;
			procinfo[ii].m_idPackage = GetBitValue(apicid, CPUID_PACKAGE_ID_START, CPUID_PACKAGE_ID_END);
		}
	}

	// count number of cores
	g_Info.m_AvailCore = 1;
	for (unsigned int ii = 1; ii < g_Info.m_TotalLogical; ++ii)
	{
		BOOL found = FALSE;
		for (unsigned int jj = 0; jj < ii; ++jj)
		{
			if (procinfo[jj].m_idPackage == procinfo[ii].m_idPackage && procinfo[jj].m_idCore == procinfo[ii].m_idCore)
			{
				found = TRUE;
				break;
			}
		}
		if (!found)
		{
			++g_Info.m_AvailCore;
		}
	}

	// count number of processors
	g_Info.m_AvailPhysical = 1;
	for (unsigned int ii = 1; ii < g_Info.m_TotalLogical; ++ii)
	{
		BOOL found = FALSE;
		for (unsigned int jj = 0; jj < ii; ++jj)
		{
			if (procinfo[jj].m_idPackage == procinfo[ii].m_idPackage)
			{
				found = TRUE;
				break;
			}
		}
		if (!found)
		{
			++g_Info.m_AvailPhysical;
		}
	}

	// restore original state
	SetProcessAffinityMask(GetCurrentProcess(), dwProcessAffinity);
	Sleep(0);
	memcpy(&info, &g_Info, sizeof(info));
	g_bGotInfo = TRUE;

	return TRUE;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#if 1 //ISVERSION(DEVELOPMENT)
BOOL IsDebuggerAttached(
	void)
{
	// using the thread info block on windows, check to see if a debugger is attached
	// 
	// this does the same thing as the API call IsDebuggerPresent, but in theory can't be 
	// hooked and modified by persons of nefarious intent... as easily :)

	#if !defined(_WIN64)
		DWORD dw;

		__asm
		{
			push eax						// Preserve the registers
			push ecx
			mov eax, fs:[0x18]				// Get the TIB's linear address
			mov eax, dword ptr [eax + 0x30]
			mov ecx, dword ptr [eax]		// Get the whole DWORD
			mov dw, ecx						// Save it
			pop ecx							// Restore the registers
			pop eax
		}

		// The 3rd byte indicates the presence of a debugger
		return (BOOL)( ( dw & 0x00010000 ) ? TRUE : FALSE );
	#else
		return IsDebuggerPresent();
	#endif
}
#endif

// ----------------------------------------------------------------------------
// Execute a given command line in the Windows environment.
// Optionally, return without waiting for the command to exit.
// If error, return FALSE. See 'CApp::GetCmdForShellFile'.
//
// Caution: If the command is executed asynchronously, and pProcess is
// given, the caller must call CloseHandle on *pProcess.
// ----------------------------------------------------------------------------
BOOL PExecuteCmdLine(
	const OS_PATH_CHAR * CmdLine,
	DWORD dwFlags /*= CMDLINE_RUN_DEFAULT*/,
	HANDLE * pProcess /*= NULL*/,
	DWORD * pProcessID /*= 0*/ )
{
	HANDLE Process;
	UINT Status;
	//char sTemp[512];
	OS_PATH_FUNC(STARTUPINFO) StartupInfo;
	PROCESS_INFORMATION ProcessInfo;
	DWORD ErrCode;

	const OS_PATH_CHAR * pszExt = PStrGetExtension( CmdLine );
	if ( pszExt && ! PStrICmp( pszExt, OS_PATH_TEXT(".lnk"), 4 ) )
		return FALSE;

	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
	StartupInfo.cb = sizeof(StartupInfo);
	if ( dwFlags & CMDLINE_RUN_MAXIMIZED )
	{
		StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
		StartupInfo.wShowWindow = SW_SHOWMAXIMIZED;
	}
	if ( dwFlags & CMDLINE_RUN_MINIMIZED )
	{
		StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
		StartupInfo.wShowWindow = SW_SHOWMINIMIZED;
	}
	if ( dwFlags & CMDLINE_HIDE_WINDOW )
	{
		StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
		StartupInfo.wShowWindow = SW_HIDE;
	}
	Process = INVALID_HANDLE_VALUE;

	// Execute command
	StartupInfo.cb = sizeof(StartupInfo);
	StartupInfo.lpTitle = const_cast<OS_PATH_CHAR *>(CmdLine);
	Status = OS_PATH_FUNC(CreateProcess)(NULL, StartupInfo.lpTitle, NULL, NULL,
		FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);
	if (!Status)
	{
		ErrCode = GetLastError();
		if ( dwFlags & CMDLINE_RUN_NOMSG )
			return FALSE;
		if (ErrCode == 0)
			ErrorDoAssert("Error: System is out of resources.");
		else if (ErrCode == ERROR_BAD_FORMAT)
			ErrorDoAssert("Error: Invalid EXE format for command %s.", CmdLine);
		else if (ErrCode == ERROR_FILE_NOT_FOUND)
			ErrorDoAssert("Error: The EXE file was not found for command %s.", CmdLine);
		else if (ErrCode == ERROR_PATH_NOT_FOUND)
			ErrorDoAssert("Error: The EXE path was not found for command %s.", CmdLine);
		else
		{
			//GetSystemErrMsg(ErrCode, sTemp);
			// Sys err msg might have embedded % specifiers
			ErrorDoAssert("Windows reported error (Error code %ld/0x%lx) on attempting to run command %s.", ErrCode, ErrCode, CmdLine);
		}
		return FALSE;
	} // Error occurred

	Process = ProcessInfo.hProcess;
	if (Process)
		CloseHandle(ProcessInfo.hThread);
	else
	{
		TRACE("*** Process handle is NULL. (Run)");
		Process = INVALID_HANDLE_VALUE;
	}

	if ( dwFlags & CMDLINE_RUN_ASYNC )
	{
		if (pProcess)
			(*pProcess) = Process;
		else
			CloseHandle(Process);
		if (pProcessID)
			(*pProcessID) = ProcessInfo.dwProcessId;
		return TRUE;
	} // Async run

	// (Sync run)

	//WaitForInputIdle((*pProcess), 1000);
	WaitForSingleObject(Process, INFINITE);

	if (Process != INVALID_HANDLE_VALUE)
		CloseHandle(Process);
	if (pProcess)
		(*pProcess) = INVALID_HANDLE_VALUE;
	if (pProcessID)
		(*pProcessID) = 0;
	return TRUE;
}


/*********************************************************************
* Function......: ResolveShortcut
* Parameters....: lpszShortcutPath - string that specifies a path and file name of a shortcut
*				  lpszFilePath - string that will contain a file name
* Returns.......: S_OK on success, error code on failure
* Description...: Resolves a Shell link object (shortcut)
* -- from CodeProject
*********************************************************************/
PRESULT PResolveShortcut(/*in*/ const OS_PATH_CHAR * lpszShortcutPath,
						 int nMaxLenShortcut,
						 /*out*/ OS_PATH_CHAR * lpszFilePath,
						 int nMaxLenFile)
{
	CComPtr<OS_PATH_FUNC(IShellLink)> ipShellLink;
	ASSERT_RETFAIL( nMaxLenFile <= MAX_PATH && nMaxLenShortcut <= MAX_PATH );

	// buffer that receives the null-terminated string 
	// for the drive and path
	OS_PATH_CHAR szPath[MAX_PATH];     
	// buffer that receives the null-terminated 
	// string for the description
	OS_PATH_CHAR szDesc[MAX_PATH]; 
	// structure that receives the information about the shortcut
	OS_PATH_FUNC(WIN32_FIND_DATA) wfd;    
	WCHAR wszTemp[MAX_PATH];

	lpszFilePath[0] = '\0';

	// just in case this happens prior to any other COM initialization
	V_RETURN( CoInitialize( NULL ) );

	// Get a pointer to the IShellLink interface
	V_DO_SUCCEEDED( CoCreateInstance(CLSID_ShellLink,
		NULL, 
		CLSCTX_INPROC_SERVER,
		OS_PATH_FUNC(IID_IShellLink),
		(void**)&ipShellLink) )
	{ 
		// Get a pointer to the IPersistFile interface
		CComQIPtr<IPersistFile> ipPersistFile(ipShellLink);

		// IPersistFile is using LPCOLESTR, 
		// so make sure that the string is Unicode
#ifdef OS_PATH_CHAR_IS_UNICODE
		wcsncpy_s(wszTemp, lpszShortcutPath, MAX_PATH);
#else
		MultiByteToWideChar(CP_ACP, 0, lpszShortcutPath, -1, wszTemp, MAX_PATH);
#endif

		// Open the shortcut file and initialize it from its contents
		V_DO_SUCCEEDED( ipPersistFile->Load(wszTemp, STGM_READ) )
		{
			// Try to find the target of a shortcut, 
			// even if it has been moved or renamed
			V_DO_SUCCEEDED( ipShellLink->Resolve(NULL, SLR_UPDATE) )
			{
				// Get the path to the shortcut target
				V_RETURN( ipShellLink->GetPath(szPath, _countof(szPath), &wfd, SLGP_RAWPATH) );

				// Get the description of the target
				V_RETURN( ipShellLink->GetDescription(szDesc, _countof(szDesc)) ); 

				if ( !szPath )
					return E_FAIL;

				PStrCopy(lpszFilePath, szPath, nMaxLenFile); 
				return S_OK;
			} 
		} 
	} 

	return E_FAIL;
}



#if ! ISVERSION(SERVER_VERSION)

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

struct PRIME_LOGO
{
	HBITMAP hLogo;
	int nLogoWidth;
	int nLogoHeight;
};

static PRIME_LOGO sgtLogo[ NUM_GDI_LOGO_TYPES ];

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void GDI_Init( HWND hWnd, HINSTANCE hInstance )
{
	// select logo based on desktop format

	//D3DDISPLAYMODE tDesc;
	//dxC_GetD3DDisplayMode( &tDesc );
	//int nDepth = dx9_GetTextureFormatBitDepth( tDesc.Format );
	//int nIDB;
	//switch (nDepth)
	//{
	//case 32:
	//case 24:
	//	nIDB = IDB_HELLGATE_LOGO_24;
	//	break;
	//case 16:
	//default:
	//	nIDB = IDB_HELLGATE_LOGO_16;
	//}

	for ( int i = 0; i < NUM_GDI_LOGO_TYPES; ++i )
	{
		sgtLogo[i].hLogo = NULL;
	}
	HDC hDC = GetDC( hWnd );
	if ( ! hDC )
		return;

	int nIDBs[ NUM_GDI_LOGO_TYPES ] =
	{
		AppIsHellgate() ? IDB_HELLGATE_SPLASH				: IDB_TUGBOAT_LOGO_24,		// Splash logo
		AppIsHellgate() ? IDB_HELLGATE_STANDBY_COATOFARMS	: IDB_TUGBOAT_LOGO_24,		// Standby logo
	};

	for ( int i = 0; i < NUM_GDI_LOGO_TYPES; ++i )
	{
		sgtLogo[i].hLogo = (HBITMAP)LoadImage( hInstance, MAKEINTRESOURCE(nIDBs[i]), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR );
		if ( ! sgtLogo[i].hLogo )
			return;

		CBitmap * pBitmap = CBitmap::FromHandle( sgtLogo[i].hLogo );
		if ( ! pBitmap )
			return;
		BITMAP tInfo;
		if ( ! pBitmap->GetBitmap( &tInfo ) )
			return;
		sgtLogo[i].nLogoWidth  = tInfo.bmWidth;
		sgtLogo[i].nLogoHeight = tInfo.bmHeight;
	}
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void GDI_Destroy()
{
	for ( int i = 0; i < NUM_GDI_LOGO_TYPES; ++i )
	{
		if ( sgtLogo[i].hLogo )
		{
			DeleteObject( sgtLogo[i].hLogo );
			sgtLogo[i].hLogo = NULL;
		}
	}
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

static
void GDI_ClearWindow( HWND hWnd, HDC hDC )
{
	if ( ! hWnd )
		return;
	if ( ! hDC )
		return;

	//HDC source = CreateCompatibleDC( hDC );

	RECT tRect;
	GetClientRect( hWnd, &tRect );

	CDC * pDC = CDC::FromHandle( hDC );
	pDC->FillSolidRect( &tRect, RGB(0,0,0) );

	GdiFlush();

	//DeleteDC( source );
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void GDI_ClearWindow( HWND hWnd )
{
	if ( ! hWnd )
		return;
	HDC hDC = GetDC( hWnd );
	if ( ! hDC )
		return;

	GDI_ClearWindow(hWnd, hDC);

	//DeleteDC( source );
	ReleaseDC( hWnd, hDC );
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void GDI_ShowLogo( HWND hWnd, HDC hDest, GDI_LOGO_TYPE eType /*= LOGO_STANDBY*/ )
{
	if ( ! hWnd )
		return;
	if ( ! hDest )
		return;

	if ( !sgtLogo[eType].hLogo )
	{
		GDI_ClearWindow( hWnd, hDest );
		return;
	}

	HDC hSrc = CreateCompatibleDC( hDest );

	RECT tRect;
	GetClientRect( hWnd, &tRect );
	int nCX = ( tRect.right  - tRect.left ) / 2;
	int nCY = ( tRect.bottom - tRect.top  ) / 2;
	int nHW = sgtLogo[eType].nLogoWidth  / 2;
	int nHH = sgtLogo[eType].nLogoHeight / 2;
	RECT tLogo;
	tLogo.left   = nCX - nHW;
	tLogo.top    = nCY - nHH;
	tLogo.right  = tLogo.left + sgtLogo[eType].nLogoWidth;
	tLogo.bottom = tLogo.top  + sgtLogo[eType].nLogoHeight;

	SelectObject( hSrc, sgtLogo[eType].hLogo );
	BitBlt( hDest, tRect.left, tRect.top, tRect.right, tRect.bottom, hSrc, 0, 0, BLACKNESS );
	BitBlt( hDest, tLogo.left, tLogo.top, tLogo.right, tLogo.bottom, hSrc, 0, 0, SRCCOPY );
	GdiFlush();

	DeleteDC( hSrc );
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void GDI_ShowLogo( HWND hWnd, GDI_LOGO_TYPE eType /*= LOGO_STANDBY*/ )
{
	if ( ! hWnd )
		return;
	HDC hDest = GetDC( hWnd );
	if ( ! hDest )
		return;

	GDI_ShowLogo(hWnd, hDest, eType);

	ReleaseDC( hWnd, hDest );
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

BOOL WindowsIsXP()
{
	OSVERSIONINFOEX tInfo;
	structclear( tInfo );
	tInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);


	// Greater than minimum XP version?
	tInfo.dwMajorVersion = 5;
	tInfo.dwMinorVersion = 1;
	tInfo.wServicePackMajor = 0;

	ULONGLONG dwlConditionMask = 0;
	VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION,			VER_GREATER_EQUAL );
	VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION,			VER_GREATER_EQUAL );
	VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR,		VER_GREATER_EQUAL );

	if ( ! VerifyVersionInfo( &tInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask ) )
		return FALSE;	// before XP, fail!



	// Less than minimum Vista version?
	tInfo.dwMajorVersion = 6;
	tInfo.dwMinorVersion = 0;
	tInfo.wServicePackMajor = 0;

	dwlConditionMask = 0;
	VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION,			VER_LESS );
	VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION,			VER_LESS );
	VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR,		VER_LESS );

	return VerifyVersionInfo( &tInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask );
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

BOOL WindowsIsVistaOrLater()
{
	OSVERSIONINFOEX tInfo;
	structclear( tInfo );
	tInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);


	tInfo.dwMajorVersion = 6;
	tInfo.dwMinorVersion = 0;
	tInfo.wServicePackMajor = 0;

	ULONGLONG dwlConditionMask = 0;
	VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION,			VER_GREATER_EQUAL );
	VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION,			VER_GREATER_EQUAL );
	VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR,		VER_GREATER_EQUAL );

	return VerifyVersionInfo( &tInfo, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask );
}

/* ************
* Not sure if this works properly in 64bit compiled mode
************ */
typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
BOOL WindowsIsX86()
{
#ifdef _WIN64
	return FALSE;
#else


	BOOL bIsWow64Process = FALSE;
	LPFN_ISWOW64PROCESS nIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress( GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
	 //If the IsWow64Process function doesn't exist, we're a pre-64 bit aware version of windows...so not 64 bit
	// So the question is...error out and die, or just return true? for now, true!
	ASSERTX_RETVAL(nIsWow64Process, TRUE,"Error: Running a version of Windows that does not support IsWow64Process; Unsupported OS (all post XP-sp2 Windows supports this function)");
	
		
	BOOL ret;
	ret = nIsWow64Process(GetCurrentProcess(), &bIsWow64Process);
	ASSERTX_RETVAL(ret, TRUE, "Error: IsWow64Process returned error; assume we're in 32 bit mode");

	if(bIsWow64Process)
		return FALSE;

	return TRUE;
#endif


}



//------------------------------------------------------------------
// Vista WDDM VA QFE Detection code 
// - Returns TRUE if:
//   - we need to prompt the user to install the KB940105 hotfix
// - and FALSE if:
//   - this is an x64 binary
//   - this isn't Vista RTM
//   - this is an x86 LAA binary on Vista x64
//   - this is a newer version of the file in question than expected
//   - the user already has the hotfix installed
//------------------------------------------------------------------
bool IsVistaKB940105Required()
{
#ifdef _AMD64_
	// The QFE is not required for a 64-bit native application as it has 8 TB of VA
	return false;
#else
	OSVERSIONINFO osv;
	memset( &osv, 0, sizeof(osv) );
	osv.dwOSVersionInfoSize = sizeof(osv);
	GetVersionEx( &osv );

	if ( osv.dwMajorVersion != 6 || osv.dwMinorVersion != 0 || (osv.dwBuildNumber > 6000) )
	{
		// This QFE only ever applies to Windows Vista RTM. Windows Vista SP1 already has this fix,
		// and earlier versions of Windows do not implement WDDM
		return false;
	}

	MEMORYSTATUSEX mex;
	memset( &mex, 0, sizeof(mex) );
	mex.dwLength = sizeof(mex);
	GlobalMemoryStatusEx( &mex );

	if ( mex.ullTotalVirtual >= 4294836224  )
	{
		// If there is 4 GB of VA space total for this process, then we are a
		// 32-bit Large Address Aware application running on a Windows 64-bit OS.

		// We could be a 32-bit Large Address Aware application running on a
		// Windows 32-bit OS and get up to 3 GB, but that has stability implications.
		// Therefore, we recommend the QFE for all 32-bit versions of the OS.

		// No need for the fix unless the game is pushing 4 GB of VA
		return false;
	}

	const LPWSTR sysfile = L"dxgkrnl.sys";

	// Ensure we are checking the system copy of the file
	OS_PATH_CHAR syspath[ MAX_PATH ];

	OS_PATH_FUNC(GetSystemDirectory)( syspath, sizeof(syspath) );

	PStrCat( syspath, OS_PATH_TEXT("\\drivers\\"), MAX_PATH );
	PStrCat( syspath, sysfile, MAX_PATH );

	char vbuff[2048];

	if ( !OS_PATH_FUNC(GetFileVersionInfo)( syspath, NULL, sizeof(vbuff), vbuff ) )
	{
		// This should never happen, but we'll assume it's a newer .sys file since we've
		// narrowed the test to a Windows Vista RTM OS.
		return false;
	}

	VS_FIXEDFILEINFO *ver;
	UINT size;
	if ( !OS_PATH_FUNC(VerQueryValue)( vbuff, OS_PATH_TEXT("\\"), (LPVOID*)&ver, &size )
		|| size != sizeof(VS_FIXEDFILEINFO) 
		|| ver->dwSignature != 0xFEEF04BD )
	{
		// This should never happen, but we'll assume it's a newer .sys file since we've
		// narrowed the test to a Windows Vista RTM OS.
		return false;
	}

	// File major.minor.build.qfe version comparison
	//   WORD major = HIWORD( ver->dwFileVersionMS ); WORD minor = LOWORD( ver->dwFileVersionMS );
	//   WORD build = HIWORD( ver->dwFileVersionLS ); WORD qfe = LOWORD( ver->dwFileVersionLS );

	if ( ver->dwFileVersionMS > MAKELONG( 0, 6 )
		 || (   ver->dwFileVersionMS == MAKELONG( 0, 6 )
		     && ver->dwFileVersionLS >= MAKELONG( 20648, 6000 ) ) )
	{
		// QFE fix version of dxgkrnl.sys is 6.0.6000.20648
		return false;
	}

	// We should alert the user that they need to install the Vista WDDM VA QFE.
	return true;
#endif
}



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

#define _MSG(n) case n: return #n;
const char * WindowsDebugGetMessageName(unsigned nMsg)
{
#if ISVERSION(DEVELOPMENT)
	switch (nMsg)
	{
		_MSG(WM_NULL)
		_MSG(WM_CREATE)
		_MSG(WM_DESTROY)
		_MSG(WM_MOVE)
		_MSG(WM_SIZE)
		_MSG(WM_ACTIVATE)
		_MSG(WM_SETFOCUS)
		_MSG(WM_KILLFOCUS)
		_MSG(WM_ENABLE)
		_MSG(WM_SETREDRAW)
		_MSG(WM_SETTEXT)
		_MSG(WM_GETTEXT)
		_MSG(WM_GETTEXTLENGTH)
		_MSG(WM_PAINT)
		_MSG(WM_CLOSE)
		_MSG(WM_QUERYENDSESSION)
		_MSG(WM_QUERYOPEN)
		_MSG(WM_ENDSESSION)
		_MSG(WM_QUIT)
		_MSG(WM_ERASEBKGND)
		_MSG(WM_SYSCOLORCHANGE)
		_MSG(WM_SHOWWINDOW)
		_MSG(WM_SETTINGCHANGE)
		_MSG(WM_DEVMODECHANGE)
		_MSG(WM_ACTIVATEAPP)
		_MSG(WM_FONTCHANGE)
		_MSG(WM_TIMECHANGE)
		_MSG(WM_CANCELMODE)
		_MSG(WM_SETCURSOR)
		_MSG(WM_MOUSEACTIVATE)
		_MSG(WM_CHILDACTIVATE)
		_MSG(WM_QUEUESYNC)
		_MSG(WM_GETMINMAXINFO)
		_MSG(WM_PAINTICON)
		_MSG(WM_ICONERASEBKGND)
		_MSG(WM_NEXTDLGCTL)
		_MSG(WM_SPOOLERSTATUS)
		_MSG(WM_DRAWITEM)
		_MSG(WM_MEASUREITEM)
		_MSG(WM_DELETEITEM)
		_MSG(WM_VKEYTOITEM)
		_MSG(WM_CHARTOITEM)
		_MSG(WM_SETFONT)
		_MSG(WM_GETFONT)
		_MSG(WM_SETHOTKEY)
		_MSG(WM_GETHOTKEY)
		_MSG(WM_QUERYDRAGICON)
		_MSG(WM_COMPAREITEM)
		_MSG(WM_GETOBJECT)
		_MSG(WM_COMPACTING)
		_MSG(WM_COMMNOTIFY)
		_MSG(WM_WINDOWPOSCHANGING)
		_MSG(WM_WINDOWPOSCHANGED)
		_MSG(WM_POWER)
		_MSG(WM_COPYDATA)
		_MSG(WM_CANCELJOURNAL)
		_MSG(WM_NOTIFY)
		_MSG(WM_INPUTLANGCHANGEREQUEST)
		_MSG(WM_INPUTLANGCHANGE)
		_MSG(WM_TCARD)
		_MSG(WM_HELP)
		_MSG(WM_USERCHANGED)
		_MSG(WM_NOTIFYFORMAT)
		_MSG(WM_CONTEXTMENU)
		_MSG(WM_STYLECHANGING)
		_MSG(WM_STYLECHANGED)
		_MSG(WM_DISPLAYCHANGE)
		_MSG(WM_GETICON)
		_MSG(WM_SETICON)
		_MSG(WM_NCCREATE)
		_MSG(WM_NCDESTROY)
		_MSG(WM_NCCALCSIZE)
		_MSG(WM_NCHITTEST)
		_MSG(WM_NCPAINT)
		_MSG(WM_NCACTIVATE)
		_MSG(WM_GETDLGCODE)
		_MSG(WM_SYNCPAINT)
		_MSG(WM_NCMOUSEMOVE)
		_MSG(WM_NCLBUTTONDOWN)
		_MSG(WM_NCLBUTTONUP)
		_MSG(WM_NCLBUTTONDBLCLK)
		_MSG(WM_NCRBUTTONDOWN)
		_MSG(WM_NCRBUTTONUP)
		_MSG(WM_NCRBUTTONDBLCLK)
		_MSG(WM_NCMBUTTONDOWN)
		_MSG(WM_NCMBUTTONUP)
		_MSG(WM_NCMBUTTONDBLCLK)
//		_MSG(WM_NCXBUTTONDOWN)
//		_MSG(WM_NCXBUTTONUP)
//		_MSG(WM_NCXBUTTONDBLCLK)
		_MSG(WM_INPUT)
//		_MSG(WM_KEYFIRST)
		_MSG(WM_KEYDOWN)
		_MSG(WM_KEYUP)
		_MSG(WM_CHAR)
		_MSG(WM_DEADCHAR)
		_MSG(WM_SYSKEYDOWN)
		_MSG(WM_SYSKEYUP)
		_MSG(WM_SYSCHAR)
		_MSG(WM_SYSDEADCHAR)
//		_MSG(WM_UNICHAR)
		_MSG(WM_KEYLAST)
//		_MSG(WM_KEYLAST)
		_MSG(WM_IME_STARTCOMPOSITION)
		_MSG(WM_IME_ENDCOMPOSITION)
		_MSG(WM_IME_COMPOSITION)
//		_MSG(WM_IME_KEYLAST)
		_MSG(WM_INITDIALOG)
		_MSG(WM_COMMAND)
		_MSG(WM_SYSCOMMAND)
		_MSG(WM_TIMER)
		_MSG(WM_HSCROLL)
		_MSG(WM_VSCROLL)
		_MSG(WM_INITMENU)
		_MSG(WM_INITMENUPOPUP)
		_MSG(WM_MENUSELECT)
		_MSG(WM_MENUCHAR)
		_MSG(WM_ENTERIDLE)
		_MSG(WM_MENURBUTTONUP)
		_MSG(WM_MENUDRAG)
		_MSG(WM_MENUGETOBJECT)
		_MSG(WM_UNINITMENUPOPUP)
		_MSG(WM_MENUCOMMAND)
//		_MSG(WM_CHANGEUISTATE)
//		_MSG(WM_UPDATEUISTATE)
//		_MSG(WM_QUERYUISTATE)
		_MSG(WM_CTLCOLORMSGBOX)
		_MSG(WM_CTLCOLOREDIT)
		_MSG(WM_CTLCOLORLISTBOX)
		_MSG(WM_CTLCOLORBTN)
		_MSG(WM_CTLCOLORDLG)
		_MSG(WM_CTLCOLORSCROLLBAR)
		_MSG(WM_CTLCOLORSTATIC)
//		_MSG(WM_MOUSEFIRST)
		_MSG(WM_MOUSEMOVE)
		_MSG(WM_LBUTTONDOWN)
		_MSG(WM_LBUTTONUP)
		_MSG(WM_LBUTTONDBLCLK)
		_MSG(WM_RBUTTONDOWN)
		_MSG(WM_RBUTTONUP)
		_MSG(WM_RBUTTONDBLCLK)
		_MSG(WM_MBUTTONDOWN)
		_MSG(WM_MBUTTONUP)
		_MSG(WM_MBUTTONDBLCLK)
//		_MSG(WM_MOUSEWHEEL)
//		_MSG(WM_XBUTTONDOWN)
//		_MSG(WM_XBUTTONUP)
//		_MSG(WM_XBUTTONDBLCLK)
//		_MSG(WM_MOUSELAST)
//		_MSG(WM_MOUSELAST)
//		_MSG(WM_MOUSELAST)
		_MSG(WM_PARENTNOTIFY)
		_MSG(WM_ENTERMENULOOP)
		_MSG(WM_EXITMENULOOP)
		_MSG(WM_NEXTMENU)
		_MSG(WM_SIZING)
		_MSG(WM_CAPTURECHANGED)
		_MSG(WM_MOVING)
		_MSG(WM_POWERBROADCAST)
		_MSG(WM_DEVICECHANGE)
		_MSG(WM_MDICREATE)
		_MSG(WM_MDIDESTROY)
		_MSG(WM_MDIACTIVATE)
		_MSG(WM_MDIRESTORE)
		_MSG(WM_MDINEXT)
		_MSG(WM_MDIMAXIMIZE)
		_MSG(WM_MDITILE)
		_MSG(WM_MDICASCADE)
		_MSG(WM_MDIICONARRANGE)
		_MSG(WM_MDIGETACTIVE)
		_MSG(WM_MDISETMENU)
		_MSG(WM_ENTERSIZEMOVE)
		_MSG(WM_EXITSIZEMOVE)
		_MSG(WM_DROPFILES)
		_MSG(WM_MDIREFRESHMENU)
		_MSG(WM_IME_SETCONTEXT)
		_MSG(WM_IME_NOTIFY)
		_MSG(WM_IME_CONTROL)
		_MSG(WM_IME_COMPOSITIONFULL)
		_MSG(WM_IME_SELECT)
		_MSG(WM_IME_CHAR)
		_MSG(WM_IME_REQUEST)
		_MSG(WM_IME_KEYDOWN)
		_MSG(WM_IME_KEYUP)
		_MSG(WM_MOUSEHOVER)
		_MSG(WM_MOUSELEAVE)
		_MSG(WM_NCMOUSEHOVER)
		_MSG(WM_NCMOUSELEAVE)
//		_MSG(WM_WTSSESSION_CHANGE)
		_MSG(WM_CUT)
		_MSG(WM_COPY)
		_MSG(WM_PASTE)
		_MSG(WM_CLEAR)
		_MSG(WM_UNDO)
		_MSG(WM_RENDERFORMAT)
		_MSG(WM_RENDERALLFORMATS)
		_MSG(WM_DESTROYCLIPBOARD)
		_MSG(WM_DRAWCLIPBOARD)
		_MSG(WM_PAINTCLIPBOARD)
		_MSG(WM_VSCROLLCLIPBOARD)
		_MSG(WM_SIZECLIPBOARD)
		_MSG(WM_ASKCBFORMATNAME)
		_MSG(WM_CHANGECBCHAIN)
		_MSG(WM_HSCROLLCLIPBOARD)
		_MSG(WM_QUERYNEWPALETTE)
		_MSG(WM_PALETTEISCHANGING)
		_MSG(WM_PALETTECHANGED)
		_MSG(WM_HOTKEY)
		_MSG(WM_PRINT)
		_MSG(WM_PRINTCLIENT)
//		_MSG(WM_APPCOMMAND)
//		_MSG(WM_THEMECHANGED)
		_MSG(WM_CHANGEUISTATE)
		_MSG(WM_UPDATEUISTATE)
		_MSG(WM_QUERYUISTATE)

		// List view control messages.
		_MSG(LVM_GETBKCOLOR)
		_MSG(LVM_SETBKCOLOR)
		_MSG(LVM_GETIMAGELIST)
		_MSG(LVM_SETIMAGELIST)
		_MSG(LVM_GETITEMCOUNT)
		_MSG(LVM_GETITEMA)
		_MSG(LVM_GETITEMW)
		_MSG(LVM_SETITEMA)
		_MSG(LVM_SETITEMW)
		_MSG(LVM_INSERTITEMA)
		_MSG(LVM_INSERTITEMW)
		_MSG(LVM_DELETEITEM)
		_MSG(LVM_DELETEALLITEMS)
		_MSG(LVM_GETCALLBACKMASK)
		_MSG(LVM_SETCALLBACKMASK)
		_MSG(LVM_GETNEXTITEM)
		_MSG(LVM_FINDITEMA)
		_MSG(LVM_FINDITEMW)
		_MSG(LVM_GETITEMRECT)
		_MSG(LVM_SETITEMPOSITION)
		_MSG(LVM_GETITEMPOSITION)
		_MSG(LVM_GETSTRINGWIDTHA)
		_MSG(LVM_GETSTRINGWIDTHW)
		_MSG(LVM_HITTEST)
		_MSG(LVM_ENSUREVISIBLE)
		_MSG(LVM_SCROLL)
		_MSG(LVM_REDRAWITEMS)
		_MSG(LVM_ARRANGE)
		_MSG(LVM_EDITLABELA)
		_MSG(LVM_EDITLABELW)
		_MSG(LVM_GETEDITCONTROL)
		_MSG(LVM_GETCOLUMNA)
		_MSG(LVM_GETCOLUMNW)
		_MSG(LVM_SETCOLUMNA)
		_MSG(LVM_SETCOLUMNW)
		_MSG(LVM_INSERTCOLUMNA)
		_MSG(LVM_INSERTCOLUMNW)
		_MSG(LVM_DELETECOLUMN)
		_MSG(LVM_GETCOLUMNWIDTH)
		_MSG(LVM_SETCOLUMNWIDTH)
		_MSG(LVM_GETHEADER)
		_MSG(LVM_CREATEDRAGIMAGE)
		_MSG(LVM_GETVIEWRECT)
		_MSG(LVM_GETTEXTCOLOR)
		_MSG(LVM_SETTEXTCOLOR)
		_MSG(LVM_GETTEXTBKCOLOR)
		_MSG(LVM_SETTEXTBKCOLOR)
		_MSG(LVM_GETTOPINDEX)
		_MSG(LVM_GETCOUNTPERPAGE)
		_MSG(LVM_GETORIGIN)
		_MSG(LVM_UPDATE)
		_MSG(LVM_SETITEMSTATE)
		_MSG(LVM_GETITEMSTATE)
		_MSG(LVM_GETITEMTEXTA)
		_MSG(LVM_GETITEMTEXTW)
		_MSG(LVM_SETITEMTEXTA)
		_MSG(LVM_SETITEMTEXTW)
		_MSG(LVM_SETITEMCOUNT)
		_MSG(LVM_SORTITEMS)
		_MSG(LVM_SETITEMPOSITION32)
		_MSG(LVM_GETSELECTEDCOUNT)
		_MSG(LVM_GETITEMSPACING)
		_MSG(LVM_GETISEARCHSTRINGA)
		_MSG(LVM_GETISEARCHSTRINGW)
		_MSG(LVM_SETICONSPACING)
		_MSG(LVM_SETEXTENDEDLISTVIEWSTYLE)
		_MSG(LVM_GETEXTENDEDLISTVIEWSTYLE)
		_MSG(LVM_GETSUBITEMRECT)
		_MSG(LVM_SUBITEMHITTEST)
		_MSG(LVM_SETCOLUMNORDERARRAY)
		_MSG(LVM_GETCOLUMNORDERARRAY)
		_MSG(LVM_SETHOTITEM)
		_MSG(LVM_GETHOTITEM)
		_MSG(LVM_SETHOTCURSOR)
		_MSG(LVM_GETHOTCURSOR)
		_MSG(LVM_APPROXIMATEVIEWRECT)
		_MSG(LVM_SETWORKAREAS)
		_MSG(LVM_GETWORKAREAS)
		_MSG(LVM_GETNUMBEROFWORKAREAS)
		_MSG(LVM_GETSELECTIONMARK)
		_MSG(LVM_SETSELECTIONMARK)
		_MSG(LVM_SETHOVERTIME)
		_MSG(LVM_GETHOVERTIME)
		_MSG(LVM_SETTOOLTIPS)
		_MSG(LVM_GETTOOLTIPS)
		_MSG(LVM_SORTITEMSEX)
		_MSG(LVM_SETBKIMAGEA)
		_MSG(LVM_SETBKIMAGEW)
		_MSG(LVM_GETBKIMAGEA)
		_MSG(LVM_GETBKIMAGEW)
//		_MSG(LVM_SETSELECTEDCOLUMN)
//		_MSG(LVM_SETTILEWIDTH)
//		_MSG(LVM_SETVIEW)
//		_MSG(LVM_GETVIEW)
//		_MSG(LVM_INSERTGROUP)
//		_MSG(LVM_SETGROUPINFO)
//		_MSG(LVM_GETGROUPINFO)
//		_MSG(LVM_REMOVEGROUP)
//		_MSG(LVM_MOVEGROUP)
//		_MSG(LVM_MOVEITEMTOGROUP)
//		_MSG(LVM_SETGROUPMETRICS)
//		_MSG(LVM_GETGROUPMETRICS)
//		_MSG(LVM_ENABLEGROUPVIEW)
//		_MSG(LVM_SORTGROUPS)
//		_MSG(LVM_INSERTGROUPSORTED)
//		_MSG(LVM_REMOVEALLGROUPS)
//		_MSG(LVM_HASGROUP)
//		_MSG(LVM_SETTILEVIEWINFO)
//		_MSG(LVM_GETTILEVIEWINFO)
//		_MSG(LVM_SETTILEINFO)
//		_MSG(LVM_GETTILEINFO)
//		_MSG(LVM_SETINSERTMARK)
//		_MSG(LVM_GETINSERTMARK)
//		_MSG(LVM_INSERTMARKHITTEST)
//		_MSG(LVM_GETINSERTMARKRECT)
//		_MSG(LVM_SETINSERTMARKCOLOR)
//		_MSG(LVM_GETINSERTMARKCOLOR)
//		_MSG(LVM_GETSELECTEDCOLUMN)
//		_MSG(LVM_ISGROUPVIEWENABLED)
//		_MSG(LVM_GETOUTLINECOLOR)
//		_MSG(LVM_SETOUTLINECOLOR)
//		_MSG(LVM_CANCELEDITLABEL)
//		_MSG(LVM_MAPINDEXTOID)
//		_MSG(LVM_MAPIDTOINDEX)

		// Header control messages.
		_MSG(HDM_GETITEMCOUNT)
		_MSG(HDM_INSERTITEMA)
		_MSG(HDM_INSERTITEMW)
		_MSG(HDM_DELETEITEM)
		_MSG(HDM_GETITEMA)
		_MSG(HDM_GETITEMW)
		_MSG(HDM_SETITEMA)
		_MSG(HDM_SETITEMW)
		_MSG(HDM_LAYOUT)
		_MSG(HDM_HITTEST)
		_MSG(HDM_GETITEMRECT)
		_MSG(HDM_SETIMAGELIST)
		_MSG(HDM_GETIMAGELIST)
		_MSG(HDM_ORDERTOINDEX)
		_MSG(HDM_CREATEDRAGIMAGE)
		_MSG(HDM_GETORDERARRAY)
		_MSG(HDM_SETORDERARRAY)
		_MSG(HDM_SETHOTDIVIDER)
		_MSG(HDM_SETBITMAPMARGIN)
		_MSG(HDM_GETBITMAPMARGIN)
		_MSG(HDM_SETFILTERCHANGETIMEOUT)
		_MSG(HDM_EDITFILTER)
		_MSG(HDM_CLEARFILTER)

		// Tree view control messages.
		_MSG(TVM_INSERTITEMA)
		_MSG(TVM_INSERTITEMW)
		_MSG(TVM_DELETEITEM)
		_MSG(TVM_EXPAND)
		_MSG(TVM_GETITEMRECT)
		_MSG(TVM_GETCOUNT)
		_MSG(TVM_GETINDENT)
		_MSG(TVM_SETINDENT)
		_MSG(TVM_GETIMAGELIST)
		_MSG(TVM_SETIMAGELIST)
		_MSG(TVM_GETNEXTITEM)
		_MSG(TVM_SELECTITEM)
		_MSG(TVM_GETITEMA)
		_MSG(TVM_GETITEMW)
		_MSG(TVM_SETITEMA)
		_MSG(TVM_SETITEMW)
		_MSG(TVM_EDITLABELA)
		_MSG(TVM_EDITLABELW)
		_MSG(TVM_GETEDITCONTROL)
		_MSG(TVM_GETVISIBLECOUNT)
		_MSG(TVM_HITTEST)
		_MSG(TVM_CREATEDRAGIMAGE)
		_MSG(TVM_SORTCHILDREN)
		_MSG(TVM_ENSUREVISIBLE)
		_MSG(TVM_SORTCHILDRENCB)
		_MSG(TVM_ENDEDITLABELNOW)
		_MSG(TVM_GETISEARCHSTRINGA)
		_MSG(TVM_GETISEARCHSTRINGW)
		_MSG(TVM_SETTOOLTIPS)
		_MSG(TVM_GETTOOLTIPS)
		_MSG(TVM_SETINSERTMARK)
		_MSG(TVM_SETITEMHEIGHT)
		_MSG(TVM_GETITEMHEIGHT)
		_MSG(TVM_SETBKCOLOR)
		_MSG(TVM_SETTEXTCOLOR)
		_MSG(TVM_GETBKCOLOR)
		_MSG(TVM_GETTEXTCOLOR)
		_MSG(TVM_SETSCROLLTIME)
		_MSG(TVM_GETSCROLLTIME)
		_MSG(TVM_SETINSERTMARKCOLOR)
		_MSG(TVM_GETINSERTMARKCOLOR)
		_MSG(TVM_GETITEMSTATE)
		_MSG(TVM_SETLINECOLOR)
		_MSG(TVM_GETLINECOLOR)
		_MSG(TVM_MAPACCIDTOHTREEITEM)
		_MSG(TVM_MAPHTREEITEMTOACCID)

		// Property sheet messages.
		_MSG(PSM_SETCURSEL)
		_MSG(PSM_REMOVEPAGE)
		_MSG(PSM_ADDPAGE)
		_MSG(PSM_CHANGED)
		_MSG(PSM_RESTARTWINDOWS)
		_MSG(PSM_REBOOTSYSTEM)
		_MSG(PSM_CANCELTOCLOSE)
		_MSG(PSM_QUERYSIBLINGS)
		_MSG(PSM_UNCHANGED)
		_MSG(PSM_APPLY)
		_MSG(PSM_SETTITLEA)
		_MSG(PSM_SETWIZBUTTONS)
		_MSG(PSM_PRESSBUTTON)
		_MSG(PSM_SETCURSELID)
		_MSG(PSM_SETFINISHTEXTA)
		_MSG(PSM_GETTABCONTROL)
		_MSG(PSM_ISDIALOGMESSAGE)
		_MSG(PSM_GETCURRENTPAGEHWND)
		_MSG(PSM_INSERTPAGE)
		_MSG(PSM_SETTITLEW)
		_MSG(PSM_SETFINISHTEXTW)
		_MSG(PSM_SETHEADERTITLEA)
		_MSG(PSM_SETHEADERTITLEW)
		_MSG(PSM_SETHEADERSUBTITLEA)
		_MSG(PSM_SETHEADERSUBTITLEW)
		_MSG(PSM_HWNDTOINDEX)
		_MSG(PSM_INDEXTOHWND)
		_MSG(PSM_PAGETOINDEX)
		_MSG(PSM_INDEXTOPAGE)
		_MSG(PSM_IDTOINDEX)
		_MSG(PSM_INDEXTOID)
		_MSG(PSM_GETRESULT)
		_MSG(PSM_RECALCPAGESIZES)

		default:
			return 0;
	}
#else
	REF(nMsg);
	return 0;
#endif
}
#undef _MSG




#endif // ! ISVERSION(SERVER_VERSION)

#endif // WIN32
