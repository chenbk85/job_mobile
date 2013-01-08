/* file : jDumpFile.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-13 19:15:12
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"

#include <dbghelp.h>
#include "header/uString_stl.h"

namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{

			typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)( // Callback 함수의 원형
				HANDLE hProcess, 
				DWORD dwPid, 
				HANDLE hFile, 
				MINIDUMP_TYPE DumpType,
				CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
				CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
				CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);


			bool _MakeDumpFile(OUT aname1024_t szFilePath, EXCEPTION_POINTERS*pex)
			{
				HMODULE	DllHandle		= NULL;

				// Windows 2000 이전에는 따로 DBGHELP를 배포해서 설정해 주어야 한다.
				DllHandle				= LoadLibrary(_T("DBGHELP.DLL"));

				if (DllHandle)
				{
					MINIDUMPWRITEDUMP Dump = (MINIDUMPWRITEDUMP) GetProcAddress(DllHandle, "MiniDumpWriteDump");

					if (Dump)
					{
						CHAR		DumpPath[MAX_PATH] = {0,};
						SYSTEMTIME	SystemTime;

						tstring sTIME = _T(__TIMESTAMP__);
						nMech::nSTL::replace(sTIME,_T(":"),_T("-"));

						TCHAR excCode[80];
						TCHAR excAddr[80];
						jt_sprintf( excAddr,_T("0x%04X-0x%p"),pex->ContextRecord->SegCs,pex->ExceptionRecord->ExceptionAddress );
						jt_sprintf( excCode,_T("0x%08X"),pex->ExceptionRecord->ExceptionCode );

						tname1024_t szPath;
						//jt_sprintf(szPath ,_T("%sDump\\"),g_ExeEnv.m_szStartDir);
						jt_sprintf(szPath ,_T("%s"),g_ExeEnv.m_szModuleDir);
						jIVar* pv_DUMPFILE_PATH = jCV(debug,DUMPFILE_PATH, szPath, 0,"must termiate by (\\)");
						cstr szD = pv_DUMPFILE_PATH->Get_cstr();
						GetLocalTime(&SystemTime);
						ja_snprintf(DumpPath, MAX_PATH, ("%s%s[%s]-(%s@%s)_%d-%d_%d_%d_%d.dmp")
							,jA(pv_DUMPFILE_PATH->Get_cstr())
							,jA(g_ExeEnv.m_szAppNic)
							,jA(sTIME.c_str())
							,jA(excCode)
							,jA(excAddr)
							,SystemTime.wMonth,
							SystemTime.wDay,
							SystemTime.wHour,
							SystemTime.wMinute,
							SystemTime.wSecond);

						nFileSystem::jFolder::CreateDirForce(jT(DumpPath));
						ja_strcpy(szFilePath , (DumpPath));
						HANDLE FileHandle = CreateFileA(
							DumpPath, 
							GENERIC_WRITE, 
							FILE_SHARE_WRITE, 
							NULL, CREATE_ALWAYS, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);

						if (FileHandle != INVALID_HANDLE_VALUE)
						{
							_MINIDUMP_EXCEPTION_INFORMATION MiniDumpExceptionInfo;

							MiniDumpExceptionInfo.ThreadId			= GetCurrentThreadId();
							MiniDumpExceptionInfo.ExceptionPointers	= pex;
							MiniDumpExceptionInfo.ClientPointers	= NULL;

							BOOL Success = Dump(
								GetCurrentProcess(), 
								GetCurrentProcessId(), 
								FileHandle, 
								MiniDumpNormal, 
								&MiniDumpExceptionInfo, 
								NULL, 
								NULL);

							if (Success)
							{
								CloseHandle(FileHandle);

								return true;
							}
						}

						CloseHandle(FileHandle);
					}
				}

				return false;
			}



		}
	}
}

