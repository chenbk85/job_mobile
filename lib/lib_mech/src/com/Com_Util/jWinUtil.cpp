/* file : jWinUtil.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-11-05 12:13:10
comp.: jgame.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jWinUtil.h"
#include "util/jUtil.h"
#include "util/jRegistry.h"


namespace nMech
{
	namespace nUtil
	{
		jCTOR_INTERFACE(nMech::nUtil::jIWinUtil,jWinUtil)
		{
			static jWinUtil a;
			return &a;
		}
		jDTOR_INTERFACE(nMech::nUtil::jIWinUtil,jWinUtil)
		{
		}

		RECT jWinUtil::LoadWindowPos(HWND hWnd,cstr regName,DWORD flag)
		{
			RECT r = { 0, 0, 0, 0};
			if(!hWnd) return r;

			nMech::nUtil::CRegistry reg;
			fname_t buf;
			jt_sprintf(buf, _T("SOFTWARE\\jGame\\%s\\Ver01_param"), regName);
			reg.Open(buf,HKEY_LOCAL_MACHINE);
			if(reg[_T("SaveWindowPos")].Exists()) 
			{
				r = reg[_T("SaveWindowPos")];
				::SetWindowPos( hWnd, HWND_TOP, r.left,r.top,r.left,r.bottom, flag /*SWP_NOSIZE | SWP_SHOWWINDOW*/ );
			}
			return r;
		}
		void jWinUtil::SaveWindowPos(HWND hWnd,cstr name)
		{
			if(!hWnd) return;
			RECT rect;
			nMech::nUtil::CRegistry reg;
			fname_t buf;
			jt_sprintf(buf, _T("SOFTWARE\\jGame\\%s\\Ver01_param"), name);
			reg.Open(buf,HKEY_LOCAL_MACHINE);
			::GetWindowRect( hWnd, &rect);
			reg[_T("SaveWindowPos")] = rect;
			reg.Close();
		}

		//--------------------------------------------------------------------------
		RECT jWinUtil::LoadConsolePos(cstr regName)
		//--------------------------------------------------------------------------
		{
			RECT r = { 10, 10, 450, 450};

			SetConsoleTitle( regName);
			//Sleep(1000);
			HWND m_ConsoleHWND=FindWindow( NULL, regName );
			if(!m_ConsoleHWND) return r;
			nMech::nUtil::CRegistry reg;
			fname_t buf;
			jt_sprintf(buf, _T("SOFTWARE\\jGame\\%s\\Ver01_param"), regName);
			reg.Open(buf,HKEY_LOCAL_MACHINE);
			if(reg[_T("SaveConsolePos")].Exists()) 
			{
				r = reg[_T("SaveConsolePos")];
				::SetWindowPos( m_ConsoleHWND, HWND_TOP, r.left,r.top,r.left,r.bottom, SWP_NOSIZE | SWP_SHOWWINDOW );
			}
			return r;
		}

		//--------------------------------------------------------------------------
		void jWinUtil::SaveConsolePos(cstr regName)
		//--------------------------------------------------------------------------
		{
			RECT rect;
			HWND m_ConsoleHWND=FindWindow( NULL, regName );

			if(m_ConsoleHWND)
			{
				nMech::nUtil::CRegistry reg;
				fname_t buf;
				jt_sprintf(buf, _T("SOFTWARE\\jGame\\%s\\Ver01_param"), regName);

				reg.Open(buf,HKEY_LOCAL_MACHINE);
				::GetWindowRect( m_ConsoleHWND, &rect);
				reg[_T("SaveConsolePos")] = rect;
				reg.Close();
			}
		}
	}//namespace nUtil
}//namespace nMech

