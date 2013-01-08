/* file : jIWinUtil.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-11-05 12:10:25
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jIWinUtil_header__
#define __jIWinUtil_header__
#pragma once



namespace nMech
{
	namespace nUtil
	{
#define jINTERFACE_jIWinUtil(x) public:	\
	virtual void SaveWindowPos(HWND hWnd,cstr name) ##x \
	virtual RECT LoadWindowPos(HWND hWnd,cstr name,DWORD flag =SWP_NOSIZE | SWP_SHOWWINDOW ) ##x \
	virtual RECT LoadConsolePos(cstr regName) ##x \
	virtual void SaveConsolePos(cstr regName) ##x \

		jINTERFACE_END_BASE1(jIWinUtil,nInterface::jIInterface);

		// »ç¿ë¹ý 
		// jIWinUtil* pjIWinUtil = jCREATE_INTERFACE(nMech::nUtil::jIWinUtil);
	}
}



#endif // __jIWinUtil_header__
