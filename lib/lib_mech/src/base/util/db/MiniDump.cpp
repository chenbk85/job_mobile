/* file : MiniDump.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-06-25 16:51:47
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "MiniDump.h"


namespace nMech
{
	namespace nUtil
	{
		namespace nDB
		{

			CRITICAL_SECTION		s_exception_symbol_cs;

			/**
			@brief
			시스템 예외 발생시 호출되는 함수, 이곳에서 스택을 Dump 한다.
			*/

			static LONG __stdcall ExceptionFilter(_EXCEPTION_POINTERS* pExceptionInfo) 
			{
				EnterCriticalSection(&s_exception_symbol_cs);

				SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);


				if(SymInitialize(GetCurrentProcess(), NULL, TRUE) == FALSE) return EXCEPTION_EXECUTE_HANDLER;


				FILE* pFile;

				if((pFile = fopen("StackDump.txt", "at")) == NULL) return EXCEPTION_EXECUTE_HANDLER;

				char szTemp[256] = {0,};
				fprintf(pFile, "*------------------------------------------------------------*\n");
				fprintf(pFile, "Date:%s\n", _strdate(szTemp));
				fprintf(pFile, "Time:%s\n", _strtime(szTemp));
				fprintf(pFile, "Process:%x\n", GetCurrentProcessId());
				fprintf(pFile, "Thread:%x\n", GetCurrentThreadId());
				fprintf(pFile, "\n");
				fprintf(pFile, "Exception Type:0x%08x\n", pExceptionInfo->ExceptionRecord->ExceptionCode);

				HANDLE hProcess = GetCurrentProcess();
				HANDLE hThread = GetCurrentThread();
				CONTEXT& context = *pExceptionInfo->ContextRecord;

				STACKFRAME stackFrame = {0,};
				stackFrame.AddrPC.Offset	= context.Eip;
				stackFrame.AddrPC.Mode		= AddrModeFlat;
				stackFrame.AddrStack.Offset	= context.Esp;
				stackFrame.AddrStack.Mode	= AddrModeFlat;
				stackFrame.AddrFrame.Offset	= context.Ebp;
				stackFrame.AddrFrame.Mode	= AddrModeFlat;

				for (int i=0; i < 512; i++) { 

					if (stackFrame.AddrPC.Offset == 0) break;

					if (StackWalk(IMAGE_FILE_MACHINE_I386, hProcess, hThread, &stackFrame, &context, NULL, SymFunctionTableAccess, SymGetModuleBase, NULL) != FALSE) {

						DWORD dwDisplacement = 0;
						char chSymbol[256] = {0, };
						PIMAGEHLP_SYMBOL pSymbol = (PIMAGEHLP_SYMBOL)chSymbol;

						pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
						pSymbol->MaxNameLength = sizeof(chSymbol) - sizeof(PIMAGEHLP_SYMBOL) + 1;

						if (SymGetSymFromAddr(hProcess, stackFrame.AddrPC.Offset, &dwDisplacement, pSymbol))
							fprintf(pFile, "0x%08x - %s() + %xh\n", stackFrame.AddrPC.Offset, pSymbol->Name, stackFrame.AddrPC.Offset-pSymbol->Address);
						else
							fprintf(pFile, "0x%08x - [Unknown Symbol:Error %d]\n", stackFrame.AddrPC.Offset, GetLastError());

						IMAGEHLP_MODULE module = {sizeof(IMAGEHLP_MODULE), 0};
						if(SymGetModuleInfo(hProcess, stackFrame.AddrPC.Offset, &module) != FALSE) {
							fprintf(pFile, "\t\t\t\tImageName:%s\n", module.ImageName);
							fprintf(pFile, "\t\t\t\tLoadedImageName:%s\n", module.LoadedImageName);
						}

						IMAGEHLP_LINE line = {sizeof(IMAGEHLP_LINE), 0};
						for(DWORD i=0; i<512; ++i) {
							if(SymGetLineFromAddr(hProcess, stackFrame.AddrPC.Offset - i, &dwDisplacement, &line)  != FALSE) {
								fprintf(pFile, "\t\t\t\tFileName:%s\n", line.FileName);
								fprintf(pFile, "\t\t\t\tLineNumber:%d\n", line.LineNumber);
								break;
							}
						}
					} else {
						break;
					}
				} 
				fclose(pFile);

				SymCleanup(hProcess);

				LeaveCriticalSection(&s_exception_symbol_cs);

				return EXCEPTION_EXECUTE_HANDLER;
			}

			static bool s_isUse = false;		/// this line is not thread safe.

			CStackDumper::CStackDumper()	// when create, setting Exception Filter.
			{
				assert( !s_isUse );
				InitializeCriticalSection(&s_exception_symbol_cs);
				SetUnhandledExceptionFilter( ExceptionFilter );
				s_isUse = true;
			}




			///////////////////////////////////////////////////////////////////////////////////////////////
			//

			CStackDumper::~CStackDumper()
			{
				assert( s_isUse );
				DeleteCriticalSection( &s_exception_symbol_cs );
				s_isUse = false;
			}
		}// nDB
	}// nUTIL
}// nMech

