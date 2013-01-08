#include "stdafx.h"
#include <psapi.h>
#pragma comment(lib, "Psapi.lib")

bool Is_Exist(cstr sz)
{
	FILE* fp = jt_fopen(sz,_T("r") );
	if(!fp) return 
		false;
	fclose(fp);
	return true;
}


#include "header/jBoost.h"
#include <io.h>

void for_each_folder( tcstr szPath,for_each_folder_function_t* func ,void* v)
{
	namespace fs = boost::filesystem;
	fs::tdirectory_iterator end;
	fs::tpath sPath (szPath);
	fs::tpath path2;
	for( fs::tdirectory_iterator it(szPath); it!=end; ++it )
	{
		path2 = *it;
		if( fs::is_directory(*it) )
			for_each_folder(jT(path2.string()),func,v);
		else
			func(jT(path2.string()),v);
	}
}

void kill_Process_byID(DWORD kill_id)
{

	HANDLE hProcess = NULL;
	bool bRet;
	hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, kill_id);
	if(hProcess != NULL)
	{        
		printf("start kill_Process_byID : %d\n", kill_id);
		DWORD    ExitCode = 0;

		GetExitCodeProcess( hProcess, &ExitCode );
		bRet = ::TerminateProcess(hProcess, ExitCode );                

		if( bRet )
		{
			printf("::WaitForSingleObject(hProcess, INFINITE);\n");
			::WaitForSingleObject(hProcess, INFINITE);
			printf("Ok kill_Process_byID : %d\n", kill_id);
		}

		::CloseHandle(hProcess);
	}
}

void kill_Process_byName(tcstr strProcessName,DWORD skip_id)
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
		return;

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.
	bool isfound=false;

	for ( i = 0; i < cProcesses; i++ )
	{
		TCHAR szProcessName[MAX_PATH] = _T("unknown");

		HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, aProcesses[i] );


		if (NULL != hProcess )
		{
			HMODULE hMod;
			DWORD cbNeeded;

			if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
				&cbNeeded) )
			{
				GetModuleBaseName( hProcess, hMod, szProcessName,
					sizeof(szProcessName) );
			}
		}

		bool bRet;

		TCHAR buf[1024];
		jt_strcpy(buf, strProcessName);
		jt_strlwr(buf);
		if(jt_strcmp(jt_strlwr(szProcessName),buf)==0)
		{
			if(aProcesses[i]==skip_id)
				continue;
			if(aProcesses[i]==GetCurrentProcessId())
				continue;


			HANDLE hProcess = NULL;

			hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, aProcesses[i]);
			if(hProcess != NULL)
			{        
				DWORD    ExitCode = 0;
				printf("start kill_Process_byName : %d", aProcesses[i]);

				GetExitCodeProcess( hProcess, &ExitCode );
				bRet = ::TerminateProcess(hProcess, ExitCode );                

				if( bRet )
				{
					isfound=true;
					printf("::WaitForSingleObject(hProcess, INFINITE);\n");
					::WaitForSingleObject(hProcess, INFINITE);
					printf("Ok kill_Process_byID : %s\n", strProcessName);
				}

				::CloseHandle(hProcess);
			}
		}
		CloseHandle( hProcess );
	}
	if(!isfound)
	{
		jt_printf(_T("not found process : %s"),strProcessName );
	}
}