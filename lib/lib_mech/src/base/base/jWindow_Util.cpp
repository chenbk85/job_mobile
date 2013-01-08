/* 
	filename:	jWindow_Util.cpp
	coder	:	Cho Hyun Min (by icandoit) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	4337-11-23 오후 5:08:48
	title	:	
*/
#include "stdafx.h"
#include "jWindow_Util.h"
#include "base/juExeEnv.h"
#include "jFolder.h"

namespace nMech
{
	namespace nUtil
	{

		namespace nWIN
		{

			//---------------------------------------------------------------
			extern JBASE_API void Save_HWND_Log(HWND hWnd, tcstr szAppNicName)
				//----------------------------------------------------------------
			{
				afname_t bufClass;
				GetClassNameA(hWnd, bufClass, sizeof(bufClass));
				afname_t szTempPath;
				GetTempPathA(sizeof(szTempPath) ,szTempPath);
				nFileSystem::jFolder dm;
				dm.Goto(jT(szTempPath));
				FILE*fp;
				fp = _tfopen(szAppNicName ,TEXT("wt"));
				assert(fp);
#pragma warning(disable : 4311)
				uint iWnd = (uint)hWnd;
#pragma warning(default : 4311)
				_ftprintf(fp, TEXT("%d"), (int)iWnd) ;
				ja_fprintf(fp, ("\n\nszAppNicName = %s, className = %s"), jA(szAppNicName), bufClass) ;
				fclose(fp);
			}


			// Make system error message string
			//////////////////////////////////////////////////////////////////////////
			//! \return pointer to the null terminated error string or 0
			extern JBASE_API tcstr GetLastSystemErrorMessage()
			{
#ifdef WIN32
				DWORD dwError = GetLastError();

				static TCHAR szBuffer[512]; // function will return pointer to this buffer

				if(dwError)
				{
					//#ifdef _XBOX

					LPVOID lpMsgBuf=0;

					if(FormatMessage( 
						FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM | 
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
						(LPTSTR) &lpMsgBuf,
						0,
						NULL))
					{
						jt_strncpy(szBuffer, (TCHAR*)lpMsgBuf, sizeof(szBuffer));
						LocalFree(lpMsgBuf);
					}
					else return 0;

					//#else

					//jt_sprintf(szBuffer, "Win32 ERROR: %i", dwError);
					//OutputDebugString(szBuffer);

					//#endif

					return szBuffer;
				}
#else
				return 0;

#endif //WIN32

				return 0;
			}

			//---------------------------------------------------------------
			extern JBASE_API void jRemoveStartDirString(tcstr szFile, tfname_t& buf)
				//----------------------------------------------------------------
			{
				nString::jParsor::jChangeString(szFile, g_ExeEnv.m_szStartDir , _T("") , buf);
				if(buf[0]!=_T('\\')) return;
				tfname_t buf1;
				jt_strcpy(buf1, buf+1);
				jt_strcpy(buf, buf1);
			}


			// sz 프로그램이 실행중이면 true 를 리턴.
			extern JBASE_API bool Check_multi_run(tcstr szApp)
			{
				HWND hW = ::FindWindow( szApp, 0);
				if(hW)
				{
					::ShowWindow(hW, SW_RESTORE);
					return true;
				}
				HANDLE hMutex = NULL;
				hMutex = CreateMutex(NULL,TRUE,szApp);
				if (GetLastError() == ERROR_ALREADY_EXISTS)
				{
					//HWND hWnd = GetAppHWnd(szApp);
					//if(hWnd) 
					return true;
				}
				return false;
			}

			//---------------------------------------------------------------
			extern JBASE_API HWND GetAppHWnd(tcstr sz, TCHAR* szClassName)
				//----------------------------------------------------------------
			{
				afname_t szTempPath;
				GetTempPathA(sizeof(szTempPath) ,szTempPath);
				nFileSystem::jFolder dm;
				dm.Goto(jT(szTempPath));
				HANDLE hFile; 

				hFile = CreateFile(sz,           // open MYFILE.TXT 
					GENERIC_READ,              // open for reading 
					FILE_SHARE_READ,           // share for reading 
					NULL,                      // no security 
					OPEN_EXISTING,             // existing file only 
					FILE_ATTRIBUTE_NORMAL,     // normal file 
					NULL);                     // no attr. template 

				if (hFile == INVALID_HANDLE_VALUE) 
				{ 
					return 0;
				}
				TCHAR buf[1024];
				DWORD iReaded;
				HWND hCtrlWnd =0;
				if(ReadFile(hFile,buf, sizeof(buf), &iReaded,0) )
				{
					buf[iReaded]=0;

#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
					uint iWnd = (uint)jt_atoi(buf);
					hCtrlWnd = (HWND)iWnd;
#pragma warning(default : 4311)
#pragma warning(default : 4312)

					int i =GetWindowText(hCtrlWnd , buf , sizeof(buf));
					if(!i)
					{
						hCtrlWnd=0;
					}
				}
				CloseHandle(hFile);
				if(!hCtrlWnd)
				{
					DeleteFile(sz);
				}
				return hCtrlWnd;
			}
			//---------------------------------------------------------------
			extern JBASE_API void Log(HWND hWnd, tcstr szAppNicName)
				//----------------------------------------------------------------
			{
				tfname_t bufClass;
				GetClassName(hWnd, bufClass, sizeof(bufClass));
				afname_t szTempPath;
				GetTempPathA(sizeof(szTempPath) ,szTempPath);
				nFileSystem::jFolder dm;
				dm.Goto(jT(szTempPath));
				FILE*fp;
				fp = _tfopen(szAppNicName ,TEXT("wt"));
				assert(fp);
#pragma warning(disable : 4311)
				uint iWnd = (uint)hWnd;
#pragma warning(default : 4311)
				_ftprintf(fp, TEXT("%d"), (int)iWnd) ;
				_ftprintf(fp, TEXT("\n\nszAppNicName = %s, className = %s"), szAppNicName, bufClass) ;
				fclose(fp);
			}

			//---------------------------------------------------------------
			extern JBASE_API void RunApp(tcstr szFolder, tcstr szApp , tcstr szArg, bool isDebug)
				//----------------------------------------------------------------
			{
				nFileSystem::jFolder dm;
				//dm.Goto(g_ExeEnv.m_szModuleDir);
				tfname_t szAppBuf;
				_stprintf(szAppBuf , TEXT("%s.exe"), szApp);

				TCHAR bufExe[1024];
				_stprintf( bufExe, TEXT("%s\\%s"),szFolder ,szAppBuf);

				if(szArg)
				{
					_tcscat(bufExe, TEXT(" "));
					_tcscat(bufExe, szArg);
				}


				WinExec(nUNI::scb1024_t(bufExe).getA(), SW_NORMAL);
			}


			extern JBASE_API DWORD jCreateProcess( TCHAR* szExe ,bool isWait)
			{
				STARTUPINFO si;
				PROCESS_INFORMATION pi;

				ZeroMemory( &si, sizeof(si) );
				si.cb = sizeof(si);
				ZeroMemory( &pi, sizeof(pi) );

				// Start the child process. 
				if( !::CreateProcess( NULL, // No module name (use command line). 
					szExe, // Command line. 
					NULL,             // Process handle not inheritable. 
					NULL,             // Thread handle not inheritable. 
					FALSE,            // Set handle inheritance to FALSE. 
					0,                // No creation flags. 
					NULL,             // Use parent's environment block. 
					NULL,             // Use parent's starting directory. 
					&si,              // Pointer to STARTUPINFO structure.
					&pi )             // Pointer to PROCESS_INFORMATION structure.
					) 
				{
#ifndef SHIPPING
					jMB( _T("CreateProcess failed.") ,_T("jCreateProcess"));
#endif
				}
				else
				{
					// Wait until child process exits.
					if(isWait)WaitForSingleObject( pi.hProcess, INFINITE );
					// Close process and thread handles. 
					CloseHandle( pi.hProcess );
					CloseHandle( pi.hThread );
					return pi.dwProcessId;
				}
				return 0;
			}


			// Usage: SetThreadName (-1, "MainThread"); 쓰레드에 이름붙이기.
			//http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vsdebug/html/vxtsksettingthreadname.asp
			typedef struct tagTHREADNAME_INFO
			{
				DWORD dwType; // must be 0x1000
				LPCSTR szName; // pointer to name (in user addr space)
				DWORD dwThreadID; // thread ID (-1=caller thread)
				DWORD dwFlags; // reserved for future use, must be zero
			} THREADNAME_INFO;

			JBASE_API void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName)
			{
				THREADNAME_INFO info;
				info.dwType = 0x1000;
				info.szName = szThreadName;
				info.dwThreadID = dwThreadID;
				info.dwFlags = 0;

				__try
				{
					RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (const ULONG_PTR*)&info );
				}
				__except(EXCEPTION_CONTINUE_EXECUTION)
				{
				}
			}


#define BUFSIZE 80

			//ms-help://MS.VSCC.2003/MS.MSDNQTR.2003FEB.1042/sysinfo/base/getting_the_system_version.htm

			JBASE_API bool GetOSType(std::tstring& sOut)
			{
				OSVERSIONINFOEX osvi;
				BOOL bOsVersionInfoEx;
				tfname_t buf;

				// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
				// If that fails, try using the OSVERSIONINFO structure.

				ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
				osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

				if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
				{
					osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
					if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
						return FALSE;
				}
				sOut =_T("");
				switch (osvi.dwPlatformId)
				{
					// Test for the Windows NT product family.
				case VER_PLATFORM_WIN32_NT:

					// Test for the specific product.
					if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
						sOut += std::tstring(_T("Microsoft Windows Server 2003, "));

					if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
						sOut += std::tstring(_T("Microsoft Windows XP "));

					if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
						sOut += std::tstring(_T ("Microsoft Windows 2000 "));

					if ( osvi.dwMajorVersion <= 4 )
						sOut += std::tstring(_T("Microsoft Windows NT "));

					// Test for specific product on Windows NT 4.0 SP6 and later.
					if( bOsVersionInfoEx )
					{
						// Test for the workstation type.
						if ( osvi.wProductType == VER_NT_WORKSTATION )
						{
							if( osvi.dwMajorVersion == 4 )
								sOut += std::tstring(_T ( "Workstation 4.0 " ));
							else if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
								sOut += std::tstring(_T ( "Home Edition " ));
							else
								sOut += std::tstring(_T ( "Professional " ));
						}

						// Test for the server type.
						else if ( osvi.wProductType == VER_NT_SERVER ||
							osvi.wProductType == VER_NT_DOMAIN_CONTROLLER )
						{
							if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
							{
								if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
									sOut += std::tstring(_T ( "Datacenter Edition " ));
								else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
									sOut += std::tstring(_T ( "Enterprise Edition " ));
								else if ( osvi.wSuiteMask == VER_SUITE_BLADE )
									sOut += std::tstring(_T ( "Web Edition " ));
								else
									sOut += std::tstring(_T ( "Standard Edition " ));
							}

							else if( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
							{
								if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
									sOut += std::tstring(_T ( "Datacenter Server " ));
								else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
									sOut += std::tstring(_T ( "Advanced Server " ));
								else
									sOut += std::tstring(_T( "Server " ));
							}

							else // Windows NT 4.0 
							{
								if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
									sOut += std::tstring(_T("Server 4.0, Enterprise Edition " ));
								else
									sOut += std::tstring( _T( "Server 4.0 " ) );
							}
						}
					}
					else // Test for specific product on Windows NT 4.0 SP5 and earlier
					{
						HKEY hKey;
						TCHAR szProductType[BUFSIZE];
						DWORD dwBufLen=BUFSIZE;
						LONG lRet;

						lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
							_T("SYSTEM\\CurrentControlSet\\Control\\ProductOptions"),
							0, KEY_QUERY_VALUE, &hKey );
						if( lRet != ERROR_SUCCESS )
							return FALSE;

#ifdef UNICODE 
						assert(0 && "유니코드 테스트해야함");
						//char szProductType[BUFSIZE]; -> TCHAR ???
#endif

						lRet = RegQueryValueEx( hKey, _T("ProductType"), NULL, NULL,
							(LPBYTE) szProductType, &dwBufLen);
						if( (lRet != ERROR_SUCCESS) || (dwBufLen > BUFSIZE) )
							return FALSE;

						RegCloseKey( hKey );

						if ( lstrcmpi( _T("WINNT"), szProductType) == 0 )
							sOut += std::tstring(_T( "Workstation " ));
						if ( lstrcmpi( _T("LANMANNT"), szProductType) == 0 )
							sOut += std::tstring(_T( "Server " ));
						if ( lstrcmpi( _T("SERVERNT"), szProductType) == 0 )
							sOut += std::tstring(_T( "Advanced Server " ));

						jt_sprintf(buf, _T("%d.%d "), osvi.dwMajorVersion, osvi.dwMinorVersion );
						sOut += std::tstring(buf);

					}

					// Display service pack (if any) and build number.

					if( osvi.dwMajorVersion == 4 && 
						lstrcmpi( osvi.szCSDVersion, _T("Service Pack 6") ) == 0 )
					{
						HKEY hKey;
						LONG lRet;

						// Test for SP6 versus SP6a.
						lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
							_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009"),
							0, KEY_QUERY_VALUE, &hKey );
						if( lRet == ERROR_SUCCESS )
						{

							jt_sprintf(buf, _T("Service Pack 6a (Build %d)\n"), osvi.dwBuildNumber & 0xFFFF ); 
							sOut+= std::tstring(buf);
						}
						else // Windows NT 4.0 prior to SP6a
						{
							jt_sprintf( buf,_T("%s (Build %d)\n"),
								osvi.szCSDVersion,
								osvi.dwBuildNumber & 0xFFFF);
							sOut+= std::tstring(buf);
						}

						RegCloseKey( hKey );
					}
					else // not Windows NT 4.0 
					{
						jt_sprintf(buf, _T("%s (Build %d)\n"),
							osvi.szCSDVersion,
							osvi.dwBuildNumber & 0xFFFF);
						sOut+= std::tstring(buf);

					}


					break;

					// Test for the Windows Me/98/95.
				case VER_PLATFORM_WIN32_WINDOWS:

					if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
					{
						sOut+= std::tstring(_T("Microsoft Windows 95 "));
						if ( osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B' )
							sOut+= std::tstring(_T("OSR2 " ));
					} 

					if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
					{
						sOut+= std::tstring(_T("Microsoft Windows 98 "));
						if ( osvi.szCSDVersion[1] == 'A' )
							sOut+= std::tstring(_T("SE " ));
					} 

					if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
					{
						sOut+= std::tstring(_T ("Microsoft Windows Millennium Edition\n"));
					} 
					break;

				case VER_PLATFORM_WIN32s:

					sOut+= std::tstring(_T("Microsoft Win32s\n"));
					break;
				}

				return TRUE; 
			}


			//---------------------------------------------------------------
			// szFile파일을 백업하고 szNewBackupFileName에 새로 백업된 파일명을 저장한다.
			// 백업되는 파일의 형식은 file.ext -> file.ext01 으로 백업됨. 
			// backupCnt는 최대 백업되는 파일갯수. 가령10이면 10개를 환형 큐방식으로 저장한다.
			JBASE_API void DoFileBackup(tcstr szFile, int backupCnt, tfname_t szNewBackupFileName)
				//----------------------------------------------------------------
			{
				if(backupCnt <=0 ) { szNewBackupFileName=0; return;}
				tfname_t buf,szDelFile;
				GetNextBackupFileName(szFile, backupCnt, buf, szDelFile);
				MoveFile(szFile,buf);
				DeleteFile(szDelFile);
				if(szNewBackupFileName)
				{
					_tcscpy(szNewBackupFileName , buf);
				}
			}

#if 0
			//---------------------------------------------------------------
			int GetNextBackupFileName_TestUnit(int argc, TCHAR *argv[])
				//----------------------------------------------------------------
			{
				nFileSystem::jFolder dm;
				dm.Goto(TEXT("Z:\\bin\\game\\item\\box_item"));
				tfname_t buf;
				tcstr szFile="box_item.xsl";
				tfname_t buf2;
				tcstr sz = GetNextBackupFileName(szFile, 10, buf,buf2);
				printf("new backup file %s , del file =%s \n",buf,buf2);
				CopyFile(szFile, buf ,false);
				DeleteFile(buf2);
				return (0);
			}
#endif

			//---------------------------------------------------------------
			JBASE_API TCHAR* GetNextBackupFileName(tcstr szFile ,int iMaxBackupFileCnt, tfname_t szNewBackupFileName, tfname_t szDelFile)
			{
				WIN32_FIND_DATA wfdFindFileData, oldFileData;
				memset(&wfdFindFileData,0, sizeof(wfdFindFileData));
				memset(&oldFileData,0, sizeof(oldFileData));

				oldFileData.ftLastWriteTime.dwLowDateTime = MAXDWORD;
				oldFileData.ftLastWriteTime.dwHighDateTime = MAXDWORD;

				HANDLE hFind;
				tfname_t buf;
				nFileSystem::jFileName fn(szFile);
				jt_itoa(iMaxBackupFileCnt-1,buf,10);
				size_t iBackupNum = _tcslen(buf);
				int iDelNum =0;
				tfname_t szFormat;
				tcstr sz1=TEXT("%s%"),
					sz2 = TEXT("s%d");
				_stprintf(szFormat ,TEXT("%s%s%d.bak"),sz1,sz2, iBackupNum);
				for(int i =0 ; i< iMaxBackupFileCnt ; ++i)
				{
					_stprintf(szNewBackupFileName , szFormat, fn.fname,fn.ext,i);
					hFind = FindFirstFile(szNewBackupFileName , &wfdFindFileData);
					if (hFind == INVALID_HANDLE_VALUE) 
					{
						iDelNum = (i+1)%iMaxBackupFileCnt;
						_stprintf(szDelFile , szFormat, fn.fname , fn.ext, iDelNum);
						return szNewBackupFileName;
					}

					if( (wfdFindFileData.ftLastAccessTime.dwHighDateTime > oldFileData.ftLastAccessTime.dwHighDateTime )  )
						continue;
					if( ( wfdFindFileData.ftLastAccessTime.dwHighDateTime == oldFileData.ftLastAccessTime.dwHighDateTime )
						&& (wfdFindFileData.ftLastAccessTime.dwLowDateTime > oldFileData.ftLastAccessTime.dwLowDateTime ) )
						continue;
					memcpy(&oldFileData , &wfdFindFileData, sizeof(oldFileData));
					iDelNum = (i + 1) % iMaxBackupFileCnt;
					FindClose(hFind);
				}
				_stprintf(szDelFile , szFormat, fn.fname,fn.ext  ,iDelNum ) ;
				return _tcscpy(szNewBackupFileName, oldFileData.cFileName);
			}


			//---------------------------------------------------------------
			// hWho를 toWin오른쪽에 위치 시킨다.
			JBASE_API void MoveWindowTo(HWND hWho, HWND toWin )
				//----------------------------------------------------------------
			{
				WINDOWPLACEMENT	wp;
				::GetWindowPlacement(toWin, &wp);
				int x = wp.rcNormalPosition.right;
				int y = wp.rcNormalPosition.top;
				::GetWindowPlacement(hWho, &wp);
				int x2 = wp.rcNormalPosition.right -wp.rcNormalPosition.left ;
				int y2 = wp.rcNormalPosition.bottom -wp.rcNormalPosition.top ;
				//MoveWindow(hWho, x,y,x2,y2,true);
				//ShowWindow(hWho, SW_SHOW );
				SetWindowPos(hWho, toWin , x,y,x2,y2,SWP_SHOWWINDOW);
			}

			JBASE_API void MoveToScreenCenter(HWND hwnd)
			{
				// get the width and height of the screen
				int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
				int iScreenHeight= GetSystemMetrics(SM_CYFULLSCREEN);

				// get the rectangle of the window
				RECT rectWindow;
				GetWindowRect(hwnd, &rectWindow);

				// do the centering math
				int iDestX = (iScreenWidth-(rectWindow.right-rectWindow.left)) / 2;
				int iDestY = (iScreenHeight-(rectWindow.bottom-rectWindow.top)) / 2;

				// center the window
				MoveWindow(hwnd, iDestX, iDestY, 
					rectWindow.right-rectWindow.left,
					rectWindow.bottom-rectWindow.top,
					true);
			}


			// 부모 윈도우의 중앙으로 윈도우를 이동하는 함수
			void JBASE_API MoveToParentCenter(HWND hWnd)
			{
				HWND hParentWnd;
				RECT rtParent, rtWindow;
				POINT pt;

				// 부모윈도우와 다이얼로그의 크기를 구해서 중간값(x, y 좌표)을 얻는다.
				hParentWnd = GetParent( hWnd );
				GetWindowRect( hParentWnd, &rtParent );
				GetWindowRect( hWnd, &rtWindow );
				pt.x = (rtParent.right - rtWindow.right) / 2;
				pt.y = (rtParent.bottom - rtWindow.bottom) / 2;

				// x, y 위치를 화면값으로 변환하고 다이얼로그 위치를 이동한다.
				ClientToScreen( hParentWnd, &pt );
				SetWindowPos( hWnd, NULL, pt.x, pt.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
			}

#if 0
			//ShellExecuteEx() - 파일 실행 - 기다리기~~ 
			//http://cpueblo.com/programming/api/contents/147.html
			BOOL ExecuteProgram( String FileName, String Params, INT Flag )
			{
				SHELLEXECUTEINFO execinfo;

				// 실행을 위해 구조체 세트
				ZeroMemory( &execinfo, sizeof(execinfo) );
				execinfo.cbSize = sizeof(execinfo);
				execinfo.lpVerb = "open";
				execinfo.lpFile = FileName.c_str();
				execinfo.lpParameters = Params.c_str();
				execinfo.fMask = SEE_MASK_FLAG_NO_UI SEE_MASK_NOCLOSEPROCESS;
				execinfo.nShow = SW_SHOWDEFAULT;

				// 프로그램을 실행한다.
				int r = (int)ShellExecuteEx( &execinfo );
				if ( r == 0 ) return ( false );

				// 만약 Sync 플랙이 세트되었으면,
				// 실행이 종료될 때까지 기다린다.
				if ( Flag == 1 )
				{
					DWORD ec;
					do
					{
						GetExitCodeProcess( execinfo.hProcess, &ec );
						Application->ProcessMessages();
					}
					while ( ec == STILL_ACTIVE );
				}

				return ( true );
			}
#endif


#if 0
			/* http://www.npteam.net/70
			윈도우 시작시(즉, 부팅시) 프로그램이 자동으로 실행이 됩니다.
			HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run.
			이부분이 Startup시 자동실행을 담당하는 부분이죠..
			이 부분에다가 실행하고자 하는 프로그램의 경로를 입력하는 소스입니다.
			*/

			HKEY hKey;
			CString sKeyName;
			unsigned char szFilePath[100];

			LONG lnRes = RegOpenKeyEx( 
				HKEY_LOCAL_MACHINE, //오픈키의 핸들
				//하부키의 이름
				"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 
				0L,KEY_WRITE,
				&hKey //오픈키 핸들의 주소
				); 

			// RUN에 경로를 추가한다.
			lstrcpy( (char *) szFilePath , LPCTSTR(m_strFileName) );
			GetDlgItemText( IDC_KEYNAME, sKeyName ); //IDC_KEYNAME이라는 에디트 박스에서 텍스트를 가져온다.

			if( ERROR_SUCCESS == lnRes )
			{
				lnRes = RegSetValueEx(hKey,
					LPCTSTR( sKeyName ), // handle of the opened key to set value for 
					0, 
					REG_SZ, 
					szFilePath, //경로명
					REG_SZ ); 
			}  
#endif

			/*

			[API] ShellExecute를 이용해서 cmd 명령 수행하기 
			프로그래밍/소스 코드 | 2006/05/13 23:10


			ShellExecute( NULL, "open", "cmd.exe", "/C ping 192.168.0.2 > C:\\test.txt", "C:\\", SW_NORMAL );
			*/




#if 0 //맥어드레스 가져오기.
			//http://extremendl.net/bbs/zboard.php?id=v3_codelibrary&page=1&sn1=&divpage=1&sn=off&ss=on&sc=on&select_arrange=headnum&desc=asc&no=11
			bool getMacAddress( const char* ipAddress, unsigned short macIndex,
				unsigned char* macAddress, unsigned short* totalCount )
			{
				struct AdapterStatus
				{
					ADAPTER_STATUS        adapterStatus;
					NAME_BUFFER                nameBuffer[30];
				};
				AdapterStatus        adapter;
				NCB                                ncb;
				LANA_ENUM                lanaEnum;
				int                                i;

				//  Make enumerate
				::ZeroMemory( &ncb, sizeof( ncb ) );
				ncb.ncb_command                = NCBENUM;
				ncb.ncb_buffer                = ( UCHAR* )&lanaEnum;
				ncb.ncb_length                = sizeof( lanaEnum );
				::Netbios( &ncb );

				if( *totalCount != 0 )
					*totalCount = lanaEnum.length;

				//  Overflow check
				if( macAddress == 0 || macIndex < 0 || macIndex >= lanaEnum.length )
					return false;

				//  Enumerating about installed NIC
				::ZeroMemory( macAddress, 6 );

				//  Reset NCB(Network Control Block) data at 'nicIndex'
				::ZeroMemory( &ncb, sizeof( ncb ) );
				ncb.ncb_command                = NCBRESET;
				ncb.ncb_lana_num        = lanaEnum.lana[macIndex];
				::Netbios( &ncb );

				::ZeroMemory( &ncb, sizeof( ncb ) );
				ncb.ncb_command                = NCBASTAT;
				ncb.ncb_lana_num        = lanaEnum.lana[macIndex];

				if( ipAddress != 0 )
					strcpy( ( char* )ncb.ncb_callname, ipAddress );
				else
					strcpy( ( char* )ncb.ncb_callname, "*              " );


				//  Find MAC Address at 'nicIndex' NIC
				ncb.ncb_buffer                = ( PUCHAR )&adapter;
				ncb.ncb_length                = sizeof( adapter );
				if( ::Netbios( &ncb ) != 0 )
					return false;

				for( i = 0 ; i < 6 ; i++ )
					macAddress[i] = adapter.adapterStatus.adapter_address[i];

				return true;
			}


			//Windows Reboot code
			bool LocalSystemReboot( LPTSTR msg, DWORD timeout )
			{
				HANDLE                                handleToken;
				TOKEN_PRIVILEGES        tkp;
				BOOL                                result;

				if( ::OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &handleToken ) == FALSE ) 
					return FALSE;

				//  Get the LUID for shutdown privilege.
				LookupPrivilegeValue( 0, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid );
				tkp.PrivilegeCount                                = 1;
				tkp.Privileges[0].Attributes        = SE_PRIVILEGE_ENABLED;


				//  Get shutdown privilege for this process. 
				::AdjustTokenPrivileges( handleToken, FALSE, &tkp, 0, ( PTOKEN_PRIVILEGES )0, 0 );


				//  Cannot test the return value of AdjustTokenPrivileges.
				if( ::GetLastError() != ERROR_SUCCESS )
					return false;

				//  Display the shutdown dialog box and start the countdown. 
				result = ::InitiateSystemShutdown( 0, msg, timeout, FALSE, TRUE);

				if( result == FALSE )
					return false; 

				//  Disable shutdown privilege. 
				if( msg != 0 )
				{
					tkp.Privileges[0].Attributes = 0;

					AdjustTokenPrivileges( handleToken, FALSE, &tkp, 0, ( PTOKEN_PRIVILEGES ) 0, 0 );
				}

				return true;
			}

#endif


#include <Shlobj.h> 
			/************************************************
			flag of SHGetSpecialFolderPath()

			CSIDL_FLAG_CREATE 
			CSIDL_ADMINTOOLS 
			CSIDL_ALTSTARTUP 
			CSIDL_APPDATA 
			CSIDL_BITBUCKET 
			CSIDL_COMMON_ADMINTOOLS
			CSIDL_COMMON_ALTSTARTUP 
			CSIDL_COMMON_APPDATA
			CSIDL_COMMON_DESKTOPDIRECTORY 
			CSIDL_COMMON_DOCUMENTS 
			CSIDL_COMMON_FAVORITES 
			CSIDL_COMMON_PROGRAMS 
			CSIDL_COMMON_STARTMENU 
			CSIDL_COMMON_STARTUP 
			CSIDL_COMMON_TEMPLATES 
			CSIDL_CONTROLS 
			CSIDL_COOKIES
			CSIDL_DESKTOP 
			CSIDL_DESKTOPDIRECTORY 
			CSIDL_DRIVES 
			CSIDL_FAVORITES 
			CSIDL_FONTS 
			CSIDL_HISTORY 
			CSIDL_INTERNET 
			CSIDL_INTERNET_CACHE 
			CSIDL_LOCAL_APPDATA 
			CSIDL_MYMUSIC 
			CSIDL_MYPICTURES
			CSIDL_NETHOOD 
			CSIDL_NETWORK 
			CSIDL_PERSONAL 
			CSIDL_PRINTERS 
			CSIDL_PRINTHOOD 
			CSIDL_PROFILE 
			CSIDL_PROGRAM_FILES 
			CSIDL_PROGRAM_FILES_COMMON 
			CSIDL_PROGRAMS 
			CSIDL_RECENT 
			CSIDL_SENDTO 
			CSIDL_STARTMENU 
			CSIDL_STARTUP 
			CSIDL_SYSTEM
			CSIDL_TEMPLATES 
			CSIDL_WINDOWS

			************************************************/
			std::tstring nShell::GetOSFodler(DWORD dwFOLDER_TYPE)
			{
				TCHAR szSpecialPath[MAX_PATH] = {0};
				SHGetSpecialFolderPath( NULL, szSpecialPath, CSIDL_WINDOWS, FALSE );
				return szSpecialPath;
			}



			// 원본 소스: http://support.microsoft.com/kb/q99261/
			
			//--------------------------------------------------------------------------
			// 여기서부터, 화면 지우기 함수가 시작됨
			//--------------------------------------------------------------------------
			#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s     on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
			void cls( HANDLE hConsole =0)
			{
				if(hConsole ==0)
				{
					hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				}

				COORD coordScreen = { 0, 0 };    /* here's where we'll home the
												 cursor */
				BOOL bSuccess;
				DWORD cCharsWritten;
				CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
				DWORD dwConSize;                 /* number of character cells in
												 the current buffer */

				/* get the number of character cells in the current buffer */

				bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
				PERR( bSuccess, "GetConsoleScreenBufferInfo" );
				dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

				/* fill the entire screen with blanks */

				bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
					dwConSize, coordScreen, &cCharsWritten );
				PERR( bSuccess, "FillConsoleOutputCharacter" );

				/* get the current text attribute */

				bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
				PERR( bSuccess, "ConsoleScreenBufferInfo" );

				/* now set the buffer's attributes accordingly */

				bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
					dwConSize, coordScreen, &cCharsWritten );
				PERR( bSuccess, "FillConsoleOutputAttribute" );

				/* put the cursor at (0, 0) */

				bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
				PERR( bSuccess, "SetConsoleCursorPosition" );
				return;
			}
		}//namespace nWIN
	} // nUtil
} // nMech

