/* 
	filename:	m_Debug.cpp
	coder	:	Cho Wook Rea (mech12@hanmail.net)
	compiler:	vc++ 6.0
	date	:	1999 / 
	title	:	
*/
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#ifndef _WIN32
#define _WIN32
#endif

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <commdlg.h>

#include "m_Debug.h"
using namespace std;

namespace nMech
{
	namespace nDEBUG
	{

		JBASE_API TCHAR g_szDebug[MAX_TEMP_STRLEN];
		JBASE_API jConsolePrint_t* g_pConsolePrint=0;
		JBASE_API tfname_t g_DebugStringBuf ; // 각종 함수에서 debug용 jstring을 반환하는 버퍼.

		bool g_isDebugFunc=1;
		void jDebugFunc(tcstr s)
		{
			//f(g_isDebugFunc)	g_DebugFunc.SaveValue(const_cast<TCHAR*>(s));
		}

#ifdef _DEBUG
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
#endif

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
		void CDebug::Init(TCHAR *f)
			//----------------------------------------------------------------
		{
			_tcscpy(m_pFile,f);
			if(!_tcslen(m_pFile)) return;
			m_DM.GotoStartDir();
			DeleteFile(m_pFile);
		}

#ifdef M_USING_DEBUGFILE 
		void CDebug::SaveValue(TCHAR* szList, ...)
		{
			m_DM.GotoStartDir();
			//m_DM.Goto(m_DM.GetCirDir().c_str());
			TCHAR            szBuff[1024];
			va_list         vl;
			FILE* f;
			f = _tfopen(m_pFile, TEXT("a+"));
			if(!f) return;
			va_start(vl, szList);
			_vstprintf(szBuff, szList, vl);
			va_end(vl);
			_ftprintf(f , TEXT("\n%s"),szBuff);
			fclose(f);
			m_DM.GoBack();
		}

		void CDebug::SaveValue1(TCHAR* szList, ...)
		{
			TCHAR buf[256];
			_tgetcwd( buf , _MAX_PATH ) ;

			m_DM.GotoStartDir();
			_tgetcwd( buf , _MAX_PATH ) ;
			//m_DM.Goto(m_DM.GetCirDir().c_str());
			TCHAR            szBuff[1024];
			va_list         vl;
			FILE* f;
			f = _tfopen(m_pFile, TEXT("a+"));
			if(!f) return;
			va_start(vl, szList);
			_vstprintf(szBuff, szList, vl);
			va_end(vl);
			_ftprintf(f , TEXT("%s"),szBuff);
			fclose(f);
			_tgetcwd( buf , _MAX_PATH ) ;
			m_DM.GoBack();
			_tgetcwd( buf , _MAX_PATH ) ;
		}

#endif



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
	}

}//namespace nMech
	
