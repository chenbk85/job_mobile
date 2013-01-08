/* file : jProcess.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-11-18 17:38:04
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jProcess.h"
#include <psapi.h>
#pragma comment(lib, "Psapi.lib")
#include "interface/jIConsoleCmd.h"

namespace nMech
{
	namespace nUtil
	{

		DWORD jProcess::is_Exist(DWORD processID)
		{
#if 1
			DWORD aProcesses[1024], cbNeeded, cProcesses;
			unsigned int i;

			if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
				return 0;
			// Calculate how many process identifiers were returned.
			cProcesses = cbNeeded / sizeof(DWORD);
			for ( i = 0; i < cProcesses; i++ )
			{
				if( aProcesses[i]==processID)
					return processID;
			}
#else

			HANDLE hProcess = NULL;
			hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processID);
			if(hProcess != NULL)
			{
				::CloseHandle(hProcess);
				return processID;
			}
#endif
			return 0;
		}
		DWORD jProcess::is_Exist(cstr  strProcessName)
		{
			DWORD aProcesses[1024], cbNeeded, cProcesses;
			unsigned int i;

			if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
				return 0;

			// Calculate how many process identifiers were returned.
			cProcesses = cbNeeded / sizeof(DWORD);

			// Print the name and process identifier for each process.

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
					if(aProcesses[i]==GetCurrentProcessId())
						continue;


					HANDLE hProcess = NULL;

					hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, aProcesses[i]);
					if(hProcess != NULL)
					{        
						::CloseHandle(hProcess);
						return aProcesses[i];
					}
				}
				CloseHandle( hProcess );
			}
			return 0;
		}

		bool jProcess::kill_Process_byID(DWORD kill_id,DWORD waitTime)
		{
			bool isKilled=false;
			HANDLE hProcess = NULL;
			bool bRet;
			hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, kill_id);
			if(hProcess != NULL)
			{        
				printf("start kill_Process_byID : %d", kill_id);
				DWORD    ExitCode = 0;

				GetExitCodeProcess( hProcess, &ExitCode );
				bRet = ::TerminateProcess(hProcess, ExitCode );                

				if( bRet )
				{
					printf("::WaitForSingleObject(hProcess, %d);\n",waitTime);
					::WaitForSingleObject(hProcess, waitTime);
					printf("Ok kill_Process_byID : %d", kill_id);
					isKilled=true;
				}

				::CloseHandle(hProcess);
			}
			return isKilled;
		}

		bool jProcess::kill_Process_byName(tcstr strProcessName,DWORD skip_id,DWORD waitTime)
		{
			bool isKilled=false;
			DWORD aProcesses[1024], cbNeeded, cProcesses;
			unsigned int i;

			if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
				return isKilled;

			// Calculate how many process identifiers were returned.
			cProcesses = cbNeeded / sizeof(DWORD);

			// Print the name and process identifier for each process.

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
							printf("::WaitForSingleObject(hProcess, %d);\n",waitTime);
							::WaitForSingleObject(hProcess, waitTime);
							printf("Ok kill_Process : %s", strProcessName);
							isKilled=true;

						}

						::CloseHandle(hProcess);
					}
				}
				CloseHandle( hProcess );
			}
			return isKilled;
		}
	}//namespace nUtil
#define USE_NOT_AUTO_CMD

#ifdef USE_NOT_AUTO_CMD
	bool util_process_kill(const std::vector<std::tstring>& arg)
#else
	jCONSOLE_CMD_AUTO(util,process_kill,0,"kill process","<pid | process_name> [wait_time]")
#endif
	{
#define jCONSOLE_PARAM_process_kill(X,Y) X(pid,tcstr) Y(wait_time,int,INFINITE)
		jCONSOLE_PARAM_END(process_kill);

		if(isalpha(pid[0]))
		{
			nUtil::jProcess::kill_Process_byName(pid,0,wait_time);
		}
		else
		{
			nUtil::jProcess::kill_Process_byID(jt_atoi(pid),wait_time);
		}
		return true;
	}

}


