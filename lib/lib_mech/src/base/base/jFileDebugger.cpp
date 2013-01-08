/* 
filename:	m_Debug.cpp
coder	:	MECH (mech12@hanmail.net)
compiler:	vc++ 6.0
date	:	1999 / 
title	:	
*/

/* file : jFileDebugger.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-04-03 15:28:23
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jFileDebugger.h"
#include "Interface/ITimer.h"
#include <dbghelp.h>

#ifndef _WIN32
#define _WIN32
#endif

using namespace std;


namespace nMech
{
	namespace nDebug
	{

		//----------------------------------------------------------------
		JBASE_API void jAssertArg( bool is , TCHAR* s , ...)
			//----------------------------------------------------------------
		{
			if(is) return;
			TCHAR            szBuff[1024];
			va_list         vl;
			va_start(vl, s);
			_vstprintf(szBuff, s, vl);
			va_end(vl);

			tfname_t szB;
			_stprintf(szB , TEXT("[Assert]%s"), szBuff);
			int ret = MessageBox(0, szB , TEXT("Do you Debug?"), MB_YESNO );
			if( ret == IDYES)		
			{
#ifndef _WIN64
				__asm int 3; 	
#else
				__debugbreak();
#endif
			}
			throw szBuff;
		}

		JBASE_API void jTRACE( TCHAR* s , ...)
			//----------------------------------------------------------------
		{
#ifdef _DEBUG
			TCHAR            szBuff[1024];
			va_list         vl;
			va_start(vl, s);
			_vstprintf(szBuff, s, vl);
			va_end(vl);
			OutputDebugString(szBuff);
			OutputDebugString(TEXT("\n"));

#endif
		}



		//---------------------------------------------------------------
		void jFileDebugger::Init(tcstr szFile,bool isFileTimeTagAdd)
		//----------------------------------------------------------------
		{
			if(isFileTimeTagAdd)
			{
				fname_t szTime;
				nTIME::Get_ITimer()->GetCurrentTimeString(szTime);
				jt_sprintf(m_szFile , _T("%s_%s.jLog.txt") , szFile ,szTime);
			}
			else
			{
				jt_sprintf(m_szFile , _T("%s.jLog.txt") , szFile );
			}
		}

		void jFileDebugger::Write(TCHAR* szList, ...)
		{
			nFileSystem::jFolder dir(true);
			TCHAR            szBuff[1024];
			va_list         vl;
			FILE* f;
			f = jt_fopen(m_szFile, TEXT("a+"));
			if(!f) return;
			va_start(vl, szList);
			_vstprintf(szBuff, szList, vl);
			va_end(vl);
			jt_fprintf(f , TEXT("\n%s"),szBuff);
			fclose(f);
		}
		void jFileDebugger::WriteWithTime(TCHAR* szList, ...)
		{
			nFileSystem::jFolder dir(true);
			TCHAR            szBuff[1024];
			va_list         vl;
			FILE* f;
			f = jt_fopen(m_szFile, TEXT("a+"));
			if(!f) return;
			va_start(vl, szList);
			_vstprintf(szBuff, szList, vl);
			va_end(vl);
			tfname_t szTime;
			nTIME::Get_ITimer()->GetCurrentTimeString(szTime);

			jt_fprintf(f , TEXT("\n[%s] %s"),szTime, szBuff);
			fclose(f);
		}

		//****************************************************************
		JBASE_API void jDebugOut(TCHAR *format, ...)
			//****************************************************************
		{
			TCHAR szBuf[2048];
			va_list arglist;

			va_start(arglist, format);

			_vstprintf(szBuf, format, arglist);
			OutputDebugString(szBuf);
		}


		//----------------------------------------------------------------
		JBASE_API bool jMyAssert(bool exp, tcstr szDesc, int line ,tcstr fileName)
			//----------------------------------------------------------------
		{
			TCHAR szB[2048];
			if(exp) return false;
			_stprintf(szB , TEXT("%s : line[%d] , file[%s]"), szDesc, line , fileName);
			int ret = MessageBox(0, szB , TEXT("디버그할까요?"), MB_YESNO );
			if( ret == IDYES)		return true;
			return false;
		}

		typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)( // Callback 함수의 원형
			HANDLE hProcess, 
			DWORD dwPid, 
			HANDLE hFile, 
			MINIDUMP_TYPE DumpType,
			CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
			CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
			CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);



		JBASE_API bool MakeDumpFile(IN acstr szDumpTag, IN EXCEPTION_POINTERS*exceptionInfo)
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

					GetLocalTime(&SystemTime);
					ja_snprintf(DumpPath, MAX_PATH, ("%s_%d-%d-%d__%d_%d_%d.dmp")
						,szDumpTag
						,SystemTime.wYear,
						SystemTime.wMonth,
						SystemTime.wDay,
						SystemTime.wHour,
						SystemTime.wMinute,
						SystemTime.wSecond);

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
						MiniDumpExceptionInfo.ExceptionPointers	= exceptionInfo;
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

	}//namespace nDebug

}//namespace nMech

