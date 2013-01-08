////////////////////////////////////////////////////////////////////////////
//
//  jGame Engine Source File.
//  Copyright (C), jGame Studios, 2002.
// -------------------------------------------------------------------------
//  File name:   debugcallstack.cpp
//  Version:     v1.00
//  Created:     1/10/2002 by Timur.
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Interface\jISMTPClient.h"
#include "DebugCallStack.h"
#include "mmsystem.h"

#ifdef WIN32
#include "interface\\jILog.h"
#include <Process.h>
#include <imagehlp.h>
#include <time.h>
#include <crtdbg.h>
#include "Resource.h"
#pragma comment(lib, "version.lib")
#include "header\\m_stltag.h"
#include "interface/xml/jIVar.h"

using namespace std;


namespace nMech
{
	namespace nUtil
	{
		//! Needs one external of DLL handle.
		extern HMODULE gDLLHandle;

		namespace nDebug
		{
			afname_t g_szDumpFile={0};

			jIVar *pvMailServer = nCONSOLE::Get_jIConsoleVar()->CreateVar(_T("debug")
				,_T("crash_mail_server")
				,_T("rocworks.co.kr")
				,nCONSOLE::eCPP_ONLY_DEFINE
				,_T("")
				);

			jIVar* pvMail = nCONSOLE::Get_jIConsoleVar()->CreateVar(_T("debug")
				,_T("mail")
				,_T("rocworks.co.kr")
				,nCONSOLE::eCPP_ONLY_DEFINE
				,_T("")
				);

			static jDebugCallStack* jDebugCallStack_Instance()
			{ 
				static jDebugCallStack s_jDebugCallStack;
				return &s_jDebugCallStack;
			}
			jCTOR_INTERFACE(nMech::nUtil::nDebug::jIDebugCallStack,jDebugCallStack)
			{
				return jDebugCallStack_Instance();
			}
			jDTOR_INTERFACE(nMech::nUtil::nDebug::jIDebugCallStack,jDebugCallStack)
			{

			}

			bool _MakeDumpFile(aname1024_t szFilePath, EXCEPTION_POINTERS*exceptionInfo);
			std::map<std::string,std::string> g_mapBugEmailList;

#ifndef WIN98
			//#pragma comment( lib, "imagehlp" )
#pragma comment( lib, "dbghelp" )
#endif

			static ISystemUserCallback* g_ISystemUserCallback=0;
			static HWND hwndException = 0;
			static int	PrintException( EXCEPTION_POINTERS* pex );

			//=============================================================================
			LONG __stdcall UnhandledExceptionHandler( EXCEPTION_POINTERS *pex )
			{
				jDebugCallStack_Instance()->handleException( pex );
				return EXCEPTION_EXECUTE_HANDLER;
			}

			//=============================================================================
			// Class Statics
			//=============================================================================
			void jDebugCallStack::SetExitUserCallback(ISystemUserCallback* pSCB)
			{
				g_ISystemUserCallback = pSCB;
			}

			static const char* TranslateExceptionCode( DWORD dwExcept )
			{
#define for_each_EXCEPTION_CODE(X)\
	X(EXCEPTION_ACCESS_VIOLATION)\
	X(EXCEPTION_DATATYPE_MISALIGNMENT)\
	X(EXCEPTION_BREAKPOINT)\
	X(EXCEPTION_SINGLE_STEP)\
	X(EXCEPTION_ARRAY_BOUNDS_EXCEEDED)\
	X(EXCEPTION_FLT_DENORMAL_OPERAND)\
	X(EXCEPTION_FLT_DIVIDE_BY_ZERO)\
	X(EXCEPTION_FLT_INEXACT_RESULT)\
	X(EXCEPTION_FLT_INVALID_OPERATION)\
	X(EXCEPTION_FLT_OVERFLOW)\
	X(EXCEPTION_FLT_STACK_CHECK)\
	X(EXCEPTION_FLT_UNDERFLOW)\
	X(EXCEPTION_INT_DIVIDE_BY_ZERO)\
	X(EXCEPTION_INT_OVERFLOW)\
	X(EXCEPTION_PRIV_INSTRUCTION)\
	X(EXCEPTION_IN_PAGE_ERROR)\
	X(EXCEPTION_ILLEGAL_INSTRUCTION)\
	X(EXCEPTION_NONCONTINUABLE_EXCEPTION)\
	X(EXCEPTION_STACK_OVERFLOW)\
	X(EXCEPTION_INVALID_DISPOSITION)\
	X(EXCEPTION_GUARD_PAGE)\
	X(EXCEPTION_INVALID_HANDLE)\

				switch (dwExcept)
				{
#define CASE_EXCEP_CODE42(X) case  X:	return #X; break ;
					for_each_EXCEPTION_CODE(CASE_EXCEP_CODE42);
				default:
					return "Unknown";
					break;
				}
			}
			//--------------------------------------------------------------------------
			static bool _send_email(acstr szMailTo,acstr szBody)
				//--------------------------------------------------------------------------
			{
				jISMTPClient* pMail = jCREATE_INTERFACE(nMech::nUtil::nDebug::jISMTPClient);
				if(!pMail) return false;

				if ( pMail->Connect( jA(pvMailServer->Get_cstr())  ) )
				{
					try
					{
						bool ret;
						string sMailFrom = string("icandoit@")+jA(pvMail->Get_cstr());
						string sMailFromEmail = string("icandoit@") + jA(pvMail->Get_cstr());
						string sMailFromNic = nUNI::scb128_t(g_ExeEnv.m_szUserName).getA();

						string sMailTitle = string("jGame_BugReport : ") + nUNI::scb128_t(g_ExeEnv.m_szUserName).getA() +string(" ")
							+ jDebugCallStack_Instance()->getExceptionModule();

						string sMailBody = szBody;

						ret = pMail->MailFrom( sMailFrom.c_str() );
						if(!ret) throw "MailFrom";
						ret = pMail->MailTo( szMailTo );
						if(!ret) throw "MailTo";
						ret = pMail->MailContents( sMailFromNic.c_str() , sMailFromEmail.c_str(), sMailTitle.c_str() , sMailBody.c_str() );
						if(!ret) throw "MailContents";

						if(nInterface::g_pjILog)
						{
							ret = pMail->MailAttachFileA( nUNI::scb1024_t(nInterface::g_pjILog->GetFileName()).getA() );
							if(!ret) 
								jERROR(_T("%s error mail attach"),nInterface::g_pjILog->GetFileName());
						}

						nFileSystem::jFolder dm;
						dm.GotoStartDir();

						//ret = pMail->MailAttachFile( "editor.log" );
						//if(!ret) GetjILog()->Wanning("editor.log error mail attach");

						ret = pMail->MailAttachFileA( g_szDumpFile );
						if(!ret) 
							jWARN(_T("error mail attach %s"),g_szDumpFile);

						ret = pMail->MailSubmit();
						if(!ret) throw "MailSubmit";

						pMail->Disconnect();
					}
					catch(wcstr szError)
					{
						jWARN(_T("서버로 충돌정보 보내기가 실패했읍니다. : %s"),jT(szError));
						SAFE_RELEASE(pMail);
						return false;

					}
					catch (acstr szError)
					{
						jWARN(_T("서버로 충돌정보 보내기가 실패했읍니다. : %s"),jT(szError));
						SAFE_RELEASE(pMail);
						return false;
					}
					catch (...)
					{
						jWARN(_T("서버로 충돌정보 보내기가 실패했읍니다. 서버로 정보전송 실패"));
						SAFE_RELEASE(pMail);
						return false;
					}
				}
				SAFE_RELEASE(pMail);
				return true;
			}


			//------------------------------------------------------------------------------------------------------------------------
			// Sets up the symbols forfunctions in the debug 	file.
			//------------------------------------------------------------------------------------------------------------------------
			jDebugCallStack::jDebugCallStack()
			{
				prevExceptionHandler = 0;
				m_symbols = false;
			}

			jDebugCallStack::~jDebugCallStack()
			{
			}

			bool jDebugCallStack::initSymbols()
			{
#ifndef WIN98
				if (m_symbols) return true;

				char fullpath[MAX_PATH_LENGTH+1];
				char pathname[MAX_PATH_LENGTH+1];
				char fname[MAX_PATH_LENGTH+1];
				char directory[MAX_PATH_LENGTH+1];
				char drive[10];
				HANDLE process;

				//	SymSetOptions(SYMOPT_DEFERRED_LOADS|SYMOPT_UNDNAME|SYMOPT_LOAD_LINES|SYMOPT_OMAP_FIND_NEAREST|SYMOPT_INCLUDE_32BIT_MODULES);
				SymSetOptions(SYMOPT_DEFERRED_LOADS|SYMOPT_UNDNAME|SYMOPT_LOAD_LINES|SYMOPT_OMAP_FIND_NEAREST);

				process = GetCurrentProcess();

				// Get module file name.
				//GetModuleFileNameA( GetModuleHandle(_T("jBase.dll")), fullpath, MAX_PATH_LENGTH );
				GetModuleFileNameA( GetModuleHandle(0), fullpath, MAX_PATH_LENGTH );

				// Convert it into search path for symbols.
				strcpy( pathname,fullpath );
				_splitpath( pathname, drive, directory, fname, NULL );
				sprintf( pathname, "%s%s", drive,directory );

				// Append the current directory to build a search path forSymInit
				strcat( pathname, ";.;" );

				int result = 0;

				m_symbols = false;

				result = SymInitialize( process,pathname,TRUE );
				if (result) {
					//HMODULE hMod = GetModuleHandle( "imagehlp" );
					//SymGetLineFromAddrPtr = (SymGetLineFromAddrFunction)GetProcAddress( hMod,"SymGetLineFromAddr" );

					char pdb[MAX_PATH_LENGTH+1];
					char res_pdb[MAX_PATH_LENGTH+1];
					sprintf( pdb, "%s.pdb",fname );
					sprintf( pathname, "%s%s", drive,directory );
					if (SearchTreeForFile( pathname,pdb,res_pdb )) {
						m_symbols = true;
					}

					/*
					if (SymLoadModule( process,NULL,fullpath,NULL,0,0 ))
					{	
					//You could load dll/lib information ifyou wish here...
					// if(::SymLoadModule(process, 	NULL, GLibDLLName, NULL, 0, 0))
					{
					m_symbols = true;
					}
					} else {
					SymCleanup( process );
					}
					*/
				} else {
					result = SymInitialize( process,pathname,FALSE );
					if (!result)
					{
						//jLOG(_T("\001SymInitialize faield") );
					}
				}
#else
				return false;
#endif

				//return m_symbols;
				return result != 0;
			}

			void	jDebugCallStack::doneSymbols()
			{
#ifndef WIN98
				if (m_symbols) {
					SymCleanup( GetCurrentProcess() );
				}
				m_symbols = false;
#endif
			}

			void jDebugCallStack::getCallStack( std::vector<std::string> &functions )
			{
				functions = m_functions;
			}

			void jDebugCallStack::updateCallStack()
			{
				if (initSymbols())
				{
					m_functions.clear();

					// (Not used) Rise exception to call updateCallStack(exc) method.
					//riseException();
					//updateCallStack(GetExceptionInformation())

					CONTEXT context;
					memset( &context,0,sizeof(context) );
					context.ContextFlags = CONTEXT_FULL;
					if (GetThreadContext( GetCurrentThread(), &context ) )
					{
#if defined(_WIN64) || defined(AMD64)  
						FillStackTrace( context.Rip,context.Rsp,context.Rbp,&context );
#else
						FillStackTrace( context.Eip,context.Esp,context.Ebp,&context );
#endif
					}

					doneSymbols();
				}
			}

			//------------------------------------------------------------------------------------------------------------------------
			int jDebugCallStack::updateCallStack( void *exception_pointer )
			{
#if 0 // *_* by icandoit : 2011-05-30 21:40:06 기능막음.
				static int callCount = 0;
				if (callCount > 0)
				{
					if (prevExceptionHandler)
					{
						// uninstall our exception handler.
						SetUnhandledExceptionFilter( (LPTOP_LEVEL_EXCEPTION_FILTER)prevExceptionHandler );
					}
					// Immidiate termination of process.
					abort();
				}
				callCount++;
#endif
				EXCEPTION_POINTERS *pex = (EXCEPTION_POINTERS*)exception_pointer;

				HANDLE process = GetCurrentProcess();

				//! Find source line at exception address.
				//m_excLine = lookupFunctionName( (void*)pex->ExceptionRecord->ExceptionAddress,true );

				//! Find Name of .DLL from Exception address.
				strcpy( m_excModule,"<Unknown>" );
#if !defined(WIN98) && !defined(_WIN64)

				//if (m_symbols) 
				{
					DWORD dwAddr = SymGetModuleBase( process,(DWORD)pex->ExceptionRecord->ExceptionAddress );
					if (dwAddr) {
						char szBuff[MAX_PATH_LENGTH];
						if (GetModuleFileNameA( (HINSTANCE)dwAddr,szBuff,MAX_PATH_LENGTH )) {
							strcpy( m_excModule,szBuff );
							std::string path,fname,ext;

							char fdir[_MAX_PATH];
							char fdrive[_MAX_PATH];
							char file[_MAX_PATH];
							char fext[_MAX_PATH];
							_splitpath( m_excModule,fdrive,fdir,file,fext );
							_makepath( fdir,NULL,NULL,file,fext );

							strcpy(m_excModule,fdir);
						}
					}
				}

				// Fill stack trace info.
				FillStackTrace( pex->ContextRecord->Eip,pex->ContextRecord->Esp,pex->ContextRecord->Ebp,pex->ContextRecord );


#endif
				return EXCEPTION_CONTINUE_EXECUTION;
			}

			//////////////////////////////////////////////////////////////////////////
			void jDebugCallStack::FillStackTrace( DWORD64 eip,DWORD64 esp,DWORD64 ebp,PCONTEXT pContext )
			{
				HANDLE hThread = GetCurrentThread();
				HANDLE hProcess = GetCurrentProcess();

				int count;
				STACKFRAME64 stack_frame;
				BOOL b_ret=TRUE; //Setup stack frame 
				memset(&stack_frame, 0, sizeof(stack_frame));
				stack_frame.AddrPC.Mode = AddrModeFlat;
				stack_frame.AddrPC.Offset = eip;
				stack_frame.AddrStack.Mode = AddrModeFlat;
				stack_frame.AddrStack.Offset = esp;
				stack_frame.AddrFrame.Mode = AddrModeFlat; 
				stack_frame.AddrFrame.Offset = 0;	
				stack_frame.AddrFrame.Offset = ebp;

				m_functions.clear();

				PCONTEXT pContextRecord = NULL;
				CONTEXT CpuContext;
				if (pContext)
				{
					pContextRecord = &CpuContext;
					CpuContext = *pContext;
				}

				//While there are still functions on the stack.. 
				for(count=0; count < MAX_DEBUG_STACK_ENTRIES && b_ret==TRUE; count++)
				{
					b_ret = StackWalk64( IMAGE_FILE_MACHINE_I386,	hProcess, hThread, &stack_frame, pContextRecord,
						NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL);

					if (m_symbols)
					{
						std::string funcName = LookupFunctionName( (void*)stack_frame.AddrPC.Offset,true );
						if (funcName.empty()) {
							funcName = "<Unknown Function>";
						}
						m_functions.push_back( funcName );
					} 
					else 
					{
						DWORD p = stack_frame.AddrPC.Offset;
						char str[80];
						sprintf( str,"function=0x%X",p );
						m_functions.push_back( str );
					}
				}
			}

			//------------------------------------------------------------------------------------------------------------------------
			std::string jDebugCallStack::LookupFunctionName( void *pointer,bool fileInfo )
			{
				std::string symName = "";

#ifndef WIN98
				HANDLE process = GetCurrentProcess();
				char symbolBuf[sizeof(SYMBOL_INFO)+MAX_SYMBOL_LENGTH];
				memset( symbolBuf, 0, sizeof(symbolBuf));
				PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)symbolBuf;

				DWORD displacement = 0;
				DWORD64 displacement64 = 0;
				pSymbol->SizeOfStruct = sizeof(symbolBuf);
				pSymbol->MaxNameLen = MAX_SYMBOL_LENGTH;
				if (SymFromAddr( process,(DWORD64)pointer,&displacement64,pSymbol ))
				{
					symName = string(pSymbol->Name) + "()";

					if (fileInfo)
					{
						// Lookup Line in source file.
						IMAGEHLP_LINE64 lineImg;
						memset( &lineImg,0,sizeof(lineImg) );
						lineImg.SizeOfStruct = sizeof(lineImg);

						if (SymGetLineFromAddr64( process,(DWORD_PTR)pointer, &displacement, &lineImg ))
						{
							char lineNum[1024];
							ja_sprintf(lineNum, "%d",lineImg.LineNumber );
							string path;

							char file[1024];
							char fname[1024];
							char fext[1024];
							_splitpath( lineImg.FileName,NULL,NULL,fname,fext );
							_makepath( file,NULL,NULL,fname,fext );
							string fileName = file;
							/*
							string finfo = string("[" ) + fileName + ", line:" + lineNum + "]";
							//symName += string(" --- [" ) + fileName + ", line:" + lineNum + "]";
							//char finfo[1024];
							//sprintf( finfo,"[%s,line:%d]",fileName.
							char temp[4096];
							sprintf( temp,"%30s --- %s",finfo.c_str(),symName.c_str() );
							symName = temp;
							*/

							symName += string("  [" ) + fileName + ":" + lineNum + "]";
						}
					}
				}
#endif

				//jLOG_T( symName.c_str() );
				return symName;
			}

			void jDebugCallStack::registerErrorCallback( ErrorCallback callBack ) {
				m_errorCallbacks.push_back( callBack );
			}

			void jDebugCallStack::unregisterErrorCallback( ErrorCallback callBack ) {
				m_errorCallbacks.remove( callBack );
			}

			void jDebugCallStack::Init( )
			{
				prevExceptionHandler = (void*)SetUnhandledExceptionFilter( UnhandledExceptionHandler );
				// Crash.
				//PrintException( 0 );
			}

			void init_crash_info_send(acstr szDumpFile, EXCEPTION_POINTERS* pex)
			{
				static jIVar* pvMailOwner = jCV( debug,mail_owner,_T("asdf@asdf.com")
					,nCONSOLE::eCPP_ONLY_DEFINE
					,"기본 메일보낼 계정" );
				static jIVar* pvMailTarget= jCV( debug, mail_target,_T("asdf.asdf.com")
					,nCONSOLE::eCPP_ONLY_DEFINE
					, "메일을 여러명에게 보낼때 메일서버이름" );
				astring s_szModuleOwner = jA(pvMailOwner->Get_cstr());
				jLIST_TYPEDEF_vector(std::astring, listSend);
				static CHAR errorString[32768] = "";
				if (pex->ExceptionRecord->ExceptionFlags & EXCEPTION_NONCONTINUABLE) 
				{
					// Disable continue button for non continuable exceptions.
				}

				// Time and Version.
				char versionbuf[1024];
				strcpy( versionbuf,"" );
				//PutVersion( versionbuf );
				strcat( errorString,versionbuf );
				strcat( errorString,"\n" );

				//! Get call stack functions.
				jDebugCallStack *cs = jDebugCallStack_Instance();
				std::vector<string> funcs;
				cs->getCallStack( funcs );

				// Init dialog.
				int iswrite = 0;
				DWORD accessAddr = 0;
				char excCode[80];
				char excAddr[80];
				sprintf( excAddr,"0x%04X:0x%p",pex->ContextRecord->SegCs,pex->ExceptionRecord->ExceptionAddress );
				sprintf( excCode,"0x%08X",pex->ExceptionRecord->ExceptionCode );
				string moduleName = jDebugCallStack_Instance()->getExceptionModule();
				const char *excModule = moduleName.c_str();

				char desc[1024];
				char excDesc[1024];
				const char *excName = TranslateExceptionCode(pex->ExceptionRecord->ExceptionCode);

				if (pex->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
					if (pex->ExceptionRecord->NumberParameters > 1) {
						int iswrite = pex->ExceptionRecord->ExceptionInformation[0];
						accessAddr = pex->ExceptionRecord->ExceptionInformation[1];
						if (iswrite) {
							sprintf( desc,"Attempt to write data to address 0x%08X\r\nThe memory could not be \"written\"",accessAddr );
						} else {
							sprintf( desc,"Attempt to read from address 0x%08X\r\nThe memory could not be \"read\"",accessAddr );
						}
					}
				}
				sprintf( excDesc,"%s\r\n%s",excName,desc );

				jLOG(_T("Exception Code: %s"),jT(excCode ));
				jLOG(_T("Exception Addr: %s"),jT(excAddr ));
				jLOG(_T("Exception Module: %s"),jT(excModule ));
				jLOG(_T("Exception Description: %s"),jT(desc) );
				jDebugCallStack_Instance()->dumpCallStack( funcs );

				char errs[32768];
				sprintf( errs,"Exception Code: %s\nException Addr: %s\nException Module: %s\nException Description: %s, %s\n",
					excCode,excAddr,excModule,excName,desc );

				strcat( errs,"\nCall Stack Trace:\n" );

				// Fill call stack.
				char str[32768];
				strcpy( str,"" );
				for (unsigned int i = 0; i < funcs.size(); i++) {
					char temp[4096];
					sprintf( temp,"%2d) %s",funcs.size()-i,(const char*)funcs[i].c_str() );
					strcat( str,temp );
					strcat( str,"\r\n" );
					strcat( errs,temp );
					strcat( errs,"\n" );
				}

				// Call all error callbacks.
				for (std::list<jDebugCallStack::ErrorCallback>::iterator it = cs->m_errorCallbacks.begin(); it != cs->m_errorCallbacks.end(); ++it) {
					jDebugCallStack::ErrorCallback callback = *it;
					string desc,data;
					callback( desc.c_str(),data.c_str() );
					jLOG(_T("%s"),(const char*)desc.c_str() );
					jLOG(_T("%s"),(const char*)data.c_str() );

					strcat( str,"======================================================\r\n" );
					strcat( str,(const char*)desc.c_str() );
					strcat( str,"\r\n" );
					strcat( str,(const char*)data.c_str() );
					strcat( str,"\r\n" );

					strcat( errs,(const char*)desc.c_str() );
					strcat( errs,"\n" );
					strcat( errs,(const char*)data.c_str() );
					strcat( errs,"\n" );
				}

				strcat( errorString,errs );

				aname1024_t szErrorLogFile1;
				ja_sprintf(szErrorLogFile1,"%s.txt",szDumpFile);
				FILE *f = fopen( szErrorLogFile1,"wt" );
				if (f) {
					fwrite( errorString,strlen(errorString),1,f );
					fclose(f);
				}
				
				if(nMech::nInterface::g_pjILog)
				{
					ja_sprintf(szErrorLogFile1,"%s.log",szDumpFile);
					cstr szLogFile = nMech::nInterface::g_pjILog->GetFileName();
					CopyFile( szLogFile, jT(szErrorLogFile1),FALSE);
				}

// 				if(_send_email(s_szModuleOwner.c_str(),errorString))
// 				{
// 				}
			}//void init_crash_info_send(HWND hwndDlg, unsigned int message, WPARAM wParam, LPARAM lParam)

			//////////////////////////////////////////////////////////////////////////
			int	jDebugCallStack::handleException( void *exception_pointer )
			{
				jIVar* pv_handleException_term_time = jCV(debug ,pv_handleException_term_time ,60,0,"dump write skip time(second) for SEH handle exception per raise event");
				static DWORD s_dwLastWriteEventTime=0;
				DWORD currTime = ::timeGetTime();
				if( (currTime - s_dwLastWriteEventTime) < (DWORD)pv_handleException_term_time->Get_int())
				{
					return EXCEPTION_CONTINUE_EXECUTION;
				}
				s_dwLastWriteEventTime= currTime;
				GetjILog()->ProcessMessage(_T("flush_WriteCache"),0);
				EXCEPTION_POINTERS *pex = (EXCEPTION_POINTERS*)exception_pointer;
				TCHAR excCode[80];
				TCHAR excAddr[80];
				jt_sprintf( excAddr,_T("0x%04X=0x%p"),pex->ContextRecord->SegCs,pex->ExceptionRecord->ExceptionAddress );
				jt_sprintf( excCode,_T("0x%08X"),pex->ExceptionRecord->ExceptionCode );

				aname1024_t szDF;
				ja_sprintf(szDF,"%s %s %s", jA(excAddr),jA(excCode),g_szDumpFile);
				ja_strcpy(g_szDumpFile,szDF);
				_MakeDumpFile(g_szDumpFile, pex);
				int ret = 0;
// 				static bool firstTime = true;
// 
// 				// uninstall our exception handler.
// 				SetUnhandledExceptionFilter( (LPTOP_LEVEL_EXCEPTION_FILTER)prevExceptionHandler );

// 				if (!firstTime)
// 				{
// 					//jLOG(_T("Critical Exception! Called Multiple Times!" );
// 					// Exception called more then once.
// 					exit(1);
// 				}
// 
// 				firstTime = false;
				//hwndException = CreateDialog( gDLLHandle,MAKEINTRESOURCE(IDD_EXCEPTION),NULL,NULL );

				if (initSymbols())
				{
					jLOG(_T("<CRITICAL ERROR>") );
					jLOG(_T("Exception: %s, at Address: %s"),excCode,excAddr );

					// Rise exception to call updateCallStack method.
					updateCallStack( exception_pointer );

					//! Print exception dialog.
					ret = PrintException( pex );

					doneSymbols();
					//exit(0);
				}
				GetjILog()->ProcessMessage(_T("flush_WriteCache"),0);

				init_crash_info_send(g_szDumpFile, pex);

				/*
				if (ret == IDB_DEBUG) 
				{
				//SetUnhandledExceptionFilter( (LPTOP_LEVEL_EXCEPTION_FILTER)prevExceptionHandler );
				//SetUnhandledExceptionFilter( (LPTOP_LEVEL_EXCEPTION_FILTER)prevExceptionHandler );
				DebugActiveProcess( GetCurrentProcessId() );
				DebugBreak();
				}
				*/

				if (pex->ExceptionRecord->ExceptionFlags & EXCEPTION_NONCONTINUABLE)
				{
					// This is non continuable exception. abort application now.
					// *_* by icandoit : 2011-05-30 21:38:47
					//exit(1);
				}

				//typedef long (__stdcall *ExceptionFunc)(EXCEPTION_POINTERS*);
				//ExceptionFunc prevFunc = (ExceptionFunc)prevExceptionHandler;
				//return prevFunc( (EXCEPTION_POINTERS*)exception_pointer );
				//if (ret == IDB_EXIT)
				if( ret == IDB_MAIL )
				{
					// Immidiate exit.
					// *_* by icandoit : 2011-05-30 21:38:44
					//exit(1);
				} else {

				}

				// Continue;
				return EXCEPTION_CONTINUE_EXECUTION;
			}


			void jDebugCallStack::dumpCallStack( std::vector<string> &funcs )
			{
				jLOG(_T("=============================================================================" ));
				int len = (int)funcs.size();
				for (int i = 0; i < len; i++) {
					const char* str = funcs[i].c_str();
					jLOG(_T("%2d) %s"),len-i,str );
				}
				// Call all error callbacks.
				for (std::list<jDebugCallStack::ErrorCallback>::iterator it = m_errorCallbacks.begin(); it != m_errorCallbacks.end(); ++it)
				{
					jDebugCallStack::ErrorCallback callback = *it;
					string desc,data;
					callback( desc.c_str(),data.c_str() );
					jLOG(_T("%s"),nUNI::scb1024_t(desc.c_str()).getT() );
					jLOG(_T("%s"),nUNI::scb1024_t(data.c_str()).getT() );
				}
				jLOG(_T("=============================================================================") );
			}

			//////////////////////////////////////////////////////////////////////////
			void jDebugCallStack::LogCallstack()
			{
				updateCallStack();		// is updating m_functions

				jLOG(_T("=============================================================================") );
				int len = (int)m_functions.size();
				for (int i = 0; i < len; i++) {
					const char* str = m_functions[i].c_str();
					jLOG(_T("%2d) %s"),len-i,str );
				}
				jLOG(_T("=============================================================================") );
			}



			BOOL CALLBACK ExceptionDialogProc(HWND hwndDlg, unsigned int message, WPARAM wParam, LPARAM lParam) 
			{
				static jIVar* pvMailOwner = jCV( debug,mail_owner,_T("whdnrfo@gmail.com")
					,nCONSOLE::eCPP_ONLY_DEFINE
					,"기본 메일보낼 계정" );
				static jIVar* pvMailTarget= jCV( debug, mail_target,_T("mail.gmail.com")
					,nCONSOLE::eCPP_ONLY_DEFINE
					, "메일을 여러명에게 보낼때 메일서버이름" );
				static EXCEPTION_POINTERS *pex;
				astring s_szModuleOwner = jA(pvMailOwner->Get_cstr());
				jLIST_TYPEDEF_vector(std::astring, listSend);
				static CHAR errorString[32768] = "";

				switch (message) 
				{
				case WM_INITDIALOG:
					{

						pex = (EXCEPTION_POINTERS*)lParam;
						HWND h;

						if (pex->ExceptionRecord->ExceptionFlags & EXCEPTION_NONCONTINUABLE) {
							// Disable continue button for non continuable exceptions.
							//h = GetDlgItem( hwndDlg,IDB_CONTINUE );
							//if (h) EnableWindow( h,FALSE );
						}

						// Time and Version.
						char versionbuf[1024];
						strcpy( versionbuf,"" );
						//PutVersion( versionbuf );
						strcat( errorString,versionbuf );
						strcat( errorString,"\n" );

						//! Get call stack functions.
						jDebugCallStack *cs = jDebugCallStack_Instance();
						std::vector<string> funcs;
						cs->getCallStack( funcs );

						// Init dialog.
						int iswrite = 0;
						DWORD accessAddr = 0;
						char excCode[80];
						char excAddr[80];
						sprintf( excAddr,"0x%04X:0x%p",pex->ContextRecord->SegCs,pex->ExceptionRecord->ExceptionAddress );
						sprintf( excCode,"0x%08X",pex->ExceptionRecord->ExceptionCode );
						string moduleName = jDebugCallStack_Instance()->getExceptionModule();
						const char *excModule = moduleName.c_str();

						char desc[1024];
						char excDesc[1024];
						const char *excName = TranslateExceptionCode(pex->ExceptionRecord->ExceptionCode);

						if (pex->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
							if (pex->ExceptionRecord->NumberParameters > 1) {
								int iswrite = pex->ExceptionRecord->ExceptionInformation[0];
								accessAddr = pex->ExceptionRecord->ExceptionInformation[1];
								if (iswrite) {
									sprintf( desc,"Attempt to write data to address 0x%08X\r\nThe memory could not be \"written\"",accessAddr );
								} else {
									sprintf( desc,"Attempt to read from address 0x%08X\r\nThe memory could not be \"read\"",accessAddr );
								}
							}
						}
						sprintf( excDesc,"%s\r\n%s",excName,desc );

						jLOG(_T("Exception Code: %s"),excCode );
						jLOG(_T("Exception Addr: %s"),excAddr );
						jLOG(_T("Exception Module: %s"),excModule );
						jLOG(_T("Exception Description: %s"),desc );
						jDebugCallStack_Instance()->dumpCallStack( funcs );

						char errs[32768];
						sprintf( errs,"Exception Code: %s\nException Addr: %s\nException Module: %s\nException Description: %s, %s\n",
							excCode,excAddr,excModule,excName,desc );

						// Level Info.
						//char szLevel[1024];
						//const char *szLevelName = GetIEditor()->GetGameEngine()->GetLevelName();
						//const char *szMissionName = GetIEditor()->GetGameEngine()->GetMissionName();
						//sprintf( szLevel,"Level %s, Mission %s\n",szLevelName,szMissionName );
						//strcat( errs,szLevel );

						strcat( errs,"\nCall Stack Trace:\n" );

						h = GetDlgItem( hwndDlg,IDC_EXCEPTION_DESC );
						if (h) SendMessage( h,EM_REPLACESEL,FALSE, (LONG_PTR)nUNI::scb1024_t(excDesc).getT() );

						h = GetDlgItem( hwndDlg,IDC_EXCEPTION_CODE );
						if (h) SendMessage( h,EM_REPLACESEL,FALSE, (LONG_PTR)nUNI::scb256_t(excCode).getT() );

						h = GetDlgItem( hwndDlg,IDC_EXCEPTION_MODULE );
						if (h) SendMessage( h,EM_REPLACESEL,FALSE, (LONG_PTR)nUNI::scb256_t(excModule).getT() );

						h = GetDlgItem( hwndDlg,IDC_EXCEPTION_ADDRESS );
						if (h) SendMessage( h,EM_REPLACESEL,FALSE, (LONG_PTR)nUNI::scb256_t(excAddr).getT() );

						if(!g_ISystemUserCallback)
						{
							h = GetDlgItem(hwndDlg,IDB_SAVE);
							if(h) SendMessage( h,BN_DISABLE,FALSE, 0);
						}

						// Fill call stack.
						HWND callStack = GetDlgItem( hwndDlg,IDC_CALLSTACK );
						if (callStack) {
							char str[32768];
							strcpy( str,"" );
							for (unsigned int i = 0; i < funcs.size(); i++) {
								char temp[4096];
								sprintf( temp,"%2d) %s",funcs.size()-i,(const char*)funcs[i].c_str() );
								strcat( str,temp );
								strcat( str,"\r\n" );
								strcat( errs,temp );
								strcat( errs,"\n" );
							}

							// Call all error callbacks.
							for (std::list<jDebugCallStack::ErrorCallback>::iterator it = cs->m_errorCallbacks.begin(); it != cs->m_errorCallbacks.end(); ++it) {
								jDebugCallStack::ErrorCallback callback = *it;
								string desc,data;
								callback( desc.c_str(),data.c_str() );
								jLOG(_T("%s"),(const char*)desc.c_str() );
								jLOG(_T("%s"),(const char*)data.c_str() );

								strcat( str,"======================================================\r\n" );
								strcat( str,(const char*)desc.c_str() );
								strcat( str,"\r\n" );
								strcat( str,(const char*)data.c_str() );
								strcat( str,"\r\n" );

								strcat( errs,(const char*)desc.c_str() );
								strcat( errs,"\n" );
								strcat( errs,(const char*)data.c_str() );
								strcat( errs,"\n" );
							}

							SendMessage( callStack,WM_SETTEXT,FALSE, (LPARAM)nUNI::scb1024_t(str).getT() );
						}

						strcat( errorString,errs );
						FILE *f = fopen( "error.log","wt" );
						if (f) {
							fwrite( errorString,strlen(errorString),1,f );
							fclose(f);
						}

						if (hwndException)
							DestroyWindow( hwndException );

						{
							HWND h = GetDlgItem( hwndDlg,IDC_ERROR_TEXT );
							if (h) {
								char errs[4096];
								strcpy( errs,"" );
								SendMessage( h,WM_GETTEXT,(WPARAM)sizeof(errs),(LPARAM)errs );
								strcat( errorString,"\nError Description:\n" );
								strcat( errorString,errs );
							}

							if(_send_email(s_szModuleOwner.c_str(),errorString))
							{
								listSend.push_back(s_szModuleOwner);
								afname_t bufExe;
								strcpy(bufExe, jDebugCallStack_Instance()->getExceptionModule());
								ja_strlwr(bufExe);
								if(g_mapBugEmailList.count(bufExe))
								{
									afname_t buf;
									ja_sprintf(buf, "%s@%s",g_mapBugEmailList[bufExe].c_str(), jA(pvMailTarget->Get_cstr()) );
									listSend_it it = find(listSend.begin(),listSend.end(), string(buf));
									if(it==listSend.end())
									{
										_send_email(buf,errorString);
										listSend.push_back(buf);
									}
								}
							}

						}

					}
					break;

				case WM_COMMAND:
					switch (LOWORD(wParam)) 
					{
					case IDB_BBS:
						{

						}
					case IDB_MAIL:
						{
							EndDialog(hwndDlg, wParam);
							return TRUE;
						}
						break;

					case IDB_SAVE:
						{
							int res = MessageBoxA( NULL,"Warning!\r\nGame has crashed and is now in unstable state,\r\nand may crash again during saving of document.\r\nProceed with Save?","Save Level",MB_YESNO|MB_ICONEXCLAMATION );
							if (res == IDYES)
							{
								// Make one additional backup.
								if (g_ISystemUserCallback)
									g_ISystemUserCallback->OnSaveDocument();
								MessageBoxA( NULL,"Level has been sucessfully saved!\r\nPress Ok to terminate Game.","Save",MB_OK );
							}
						}
						break;
						/* *_* by icandoit : 2005-10-06 20:02:35
						case IDB_EXIT:
						// Fall through.
						//case IDB_CONTINUE:

						EndDialog(hwndDlg, wParam);
						return TRUE;
						*/ //*_* by icandoit : 2005-10-06 20:02:37

					}
				}
				return FALSE; 
			}


			static int	PrintException( EXCEPTION_POINTERS* pex)
			{
#ifdef _WIN64
				// NOTE: AMD64: implement
				return 0;
#else
				return  DialogBoxParam( gDLLHandle,MAKEINTRESOURCE(IDD_CRITICAL_ERROR),NULL,ExceptionDialogProc,(LPARAM)pex );
#endif
			}

			void jDebugCallStack::PutVersion( char *str )
			{
				char exe[_MAX_PATH];
				DWORD dwHandle;
				unsigned int len;

				char ver[1024*8];
				GetModuleFileNameA( NULL, exe, _MAX_PATH );
				int fv[4],pv[4];

				int verSize = GetFileVersionInfoSizeA( exe,&dwHandle );
				if (verSize > 0)
				{
					GetFileVersionInfoA( exe,dwHandle,1024*8,ver );
					VS_FIXEDFILEINFO *vinfo;
					VerQueryValueA( ver,"\\",(void**)&vinfo,&len );

					fv[0] = vinfo->dwFileVersionLS & 0xFFFF;
					fv[1] = vinfo->dwFileVersionLS >> 16;
					fv[2] = vinfo->dwFileVersionMS & 0xFFFF;
					fv[3] = vinfo->dwFileVersionMS >> 16;

					pv[0] = vinfo->dwProductVersionLS & 0xFFFF;
					pv[1] = vinfo->dwProductVersionLS >> 16;
					pv[2] = vinfo->dwProductVersionMS & 0xFFFF;
					pv[3] = vinfo->dwProductVersionMS >> 16;
				}

				//! Get time.
				time_t ltime;
				time( &ltime );
				tm *today = localtime( &ltime );

				char s[1024];
				//! Use strftime to build a customized time string.
				strftime( s,128,"Logged at %#c\n", today );
				strcat( str,s );
				sprintf( s,"FileVersion: %d.%d.%d.%d\n",fv[3],fv[2],fv[1],fv[0] );
				strcat( str,s );
				sprintf( s,"ProductVersion: %d.%d.%d.%d\n",pv[3],pv[2],pv[1],pv[0] );
				strcat( str,s );
			}

#endif //WIN32

			void jDebugCallStack::AddUserModule(acstr szOwner , acstr szModule)
			{
				g_mapBugEmailList[szModule] = szOwner;
			}

			bool  jDebugCallStack::SaveDumpFile(aname1024_t szFilePath, EXCEPTION_POINTERS*exceptionInfo)
			{
				extern bool _MakeDumpFile(OUT aname1024_t szFilePath, EXCEPTION_POINTERS*exceptionInfo);
				bool is = _MakeDumpFile(szFilePath,exceptionInfo);
				if(is)
				{
					jWARN_T("%s created", jT(szFilePath));
				}
				else
				{
					jERROR_T("%s create fail", jT(szFilePath));
				}
				return is;
			}

		}//namespace nDebug
	}//namespace nUtil
}

