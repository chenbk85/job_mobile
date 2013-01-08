/* 
	filename:	jWindow_Util.h
	coder	:	Cho Hyun Min (by icandoit) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	4337-11-23 ���� 5:08:41
	title	:	
*/


#ifndef __jWindow_Util_h__
#define __jWindow_Util_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

namespace nMech
{
	namespace nUtil
	{
		namespace nWIN
		{
			extern JBASE_API void MoveWindowTo(HWND hWho, HWND toWin );
			extern JBASE_API void MoveToScreenCenter(HWND hwnd);
			extern JBASE_API void MoveToParentCenter(HWND hWnd);

			extern JBASE_API bool Check_multi_run(tcstr szApp);
			extern JBASE_API void Log(HWND hWnd, tcstr szLocalName); // �ش� �������ڵ��� Ŭ�����̸��� temp������ ���� �Ѵ�.
			extern JBASE_API HWND GetAppHWnd(tcstr sz,TCHAR* szClassName=0); // temp�������� sz�� �ش��ϴ� app�� HWND�� ã�Ƴ���.
			extern JBASE_API void RunApp(tcstr szFolder, tcstr szApp , tcstr szArg=0, bool isDebug = true);
			extern JBASE_API DWORD jCreateProcess( TCHAR* szExe ,bool isWait);
			extern JBASE_API void jRemoveStartDirString(tcstr szFile, tfname_t& buf);
			extern JBASE_API void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName);
			extern JBASE_API bool GetOSType(std::tstring& sOut);
			extern JBASE_API void DoFileBackup(tcstr szFile, int backupCnt, tfname_t szNewBackupFileName);
			extern JBASE_API TCHAR* GetNextBackupFileName(tcstr szFile ,int iMaxBackupFileCnt, tfname_t szNewBackupFileName, tfname_t szDelFile);
			extern JBASE_API tcstr GetLastSystemErrorMessage();
			extern JBASE_API void Save_HWND_Log(HWND hWnd, tcstr szAppNicName);

			class JBASE_API nShell
			{
			public :
				inline std::tstring GetSystemDir()
				{
					tpath_t sz={0,};
					GetSystemDirectory( sz, sizeof(sz) );
					return sz;
				}
				inline std::tstring GetWinDir()
				{
					TCHAR szWinDir[MAX_PATH] = {0};
					GetWindowsDirectory( szWinDir, sizeof(szWinDir) );
					return szWinDir;
				}
				static std::tstring GetOSFodler(DWORD dwFOLDER_TYPE);

				static void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName);
				static bool GetOSType(std::tstring& sOut);
				static TCHAR* GetNextBackupFileName(tcstr szFile ,int iMaxBackupFileCnt, tfname_t szNewBackupFileName, tfname_t szDelFile=0);

			};

		}

	}
}


#endif //__jWindow_Util_h__
