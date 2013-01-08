

/*
사용법 : kill_Process_byName("IEXPLORE.EXE"); //한줄이면 됨..ㅋ
출처: http://kurapa.com

*/

#include "stdafx.h"

void PrintModules( DWORD processID )
{
	HMODULE hMods[1024];
	HANDLE hProcess;
	DWORD cbNeeded;
	unsigned int i;

	// Print the process identifier.
	if(GetCurrentProcessId() == processID)
	{
		printf( "\nthis is My !!!!! Process ID: %5u ", processID );
	}
	else
	{
		printf( "\nProcess ID: %5u ", processID );
	}


	// Get a list of all the modules in this process.

	hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID );
	if (NULL == hProcess)
		return;

	if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
		{
			TCHAR szModName[MAX_PATH];

			// Get the full path to the module's file.

			if ( GetModuleFileNameEx(hProcess, hMods[i], szModName,
				sizeof(szModName)/sizeof(TCHAR)))
			{
				// Print the module name and handle value.

				if(!jt_strstr(jt_strlwr(szModName),_T(".exe")) )
					continue;
				_tprintf(TEXT("\t%s (0x%08X)\n"),
					szModName, hMods[i]);
			}
		}
	}

	CloseHandle( hProcess );
}

void print_Process( )
{
	// Get the list of process identifiers.

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
		return;

	// Calculate how many process identifiers were returned.

	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name of the modules for each process.

	for ( i = 0; i < cProcesses; i++ )
		PrintModules( aProcesses[i] );
}
