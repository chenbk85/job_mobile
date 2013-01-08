/* file : jIConsoleDlg.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-01-21 16:27:29
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __jIConsoleDlg_header__
#define __jIConsoleDlg_header__
#pragma once

#include "header/jInterface.h"

namespace nMech
{
	namespace nCONSOLE
	{
		typedef bool Finalizer_t();
#define jINTERFACE_jIConsoleDlg(X) public:	\
		virtual HWND console_LoadWinPos(cstr szConsoleName)##X \
		virtual void console_SaveWinPos()##X \
		virtual void Run_WTL_Dlg(HINSTANCE hInstance,  int nCmdShow , tcstr szDlgName,HWND hWnd=0,bool InitCo =true)##X \
		virtual	void Set_Finalizer(Finalizer_t* f)##X\
		virtual	void Set_Canceler(Finalizer_t* f)##X\
		virtual HWND GetDlgHWnd()##X\

		jINTERFACE_END_BASE1(jIConsoleDlg, nInterface::jIInterface);


		// ����.
		//
		// jIConsoleDlg* pjIConsoleDlg= jCREATE_INTERFACE(nMech::nThread::jIConsoleDlg); 
		// pjIConsoleDlg�� �̱����̶� Release�� �ʿ� ����.

	}
}

#define jIConsoleDlg_GET(pConDlg) nMech::nCONSOLE::jIConsoleDlg* pConDlg= jCREATE_INTERFACE(nMech::nCONSOLE::jIConsoleDlg); 

#endif // __jIConsoleDlg_header__
