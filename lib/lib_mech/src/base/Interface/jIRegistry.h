/* file : jIRegistry.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-09-28 10:28:15
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jIRegistry_header__
#define __jIRegistry_header__
#pragma once


namespace nMech
{
	namespace nUtil
	{
#define jINTERFACE_jIRegistry(x) public:	\
		virtual BOOL Open(HKEY rootKey, LPCTSTR subKey) ##x \
		virtual BOOL Close(VOID) ##x \
		virtual BOOL CreateKey(HKEY rootKey, LPCTSTR subKey) ##x \
		virtual BOOL DeleteKey(HKEY rootKey, LPCTSTR subKey) ##x \
		virtual BOOL SetValue(LPCTSTR valueName, LPCTSTR value) ##x \
		virtual BOOL SetValue(LPCTSTR valueName, DWORD value) ##x \
		virtual BOOL SetValueForMultiSz(LPCTSTR valueName, LPCTSTR value, DWORD byteLength) ##x \
		virtual BOOL GetValue(LPCTSTR valueName, LPCTSTR value, LPDWORD bufferLength) ##x \
		virtual BOOL GetValue(LPCTSTR valueName, LPDWORD value) ##x \
		virtual BOOL DeleteValue(LPCTSTR valueName) ##x \

		jINTERFACE_END_BASE1(jIRegistry, nInterface::jIInterface);


	}
}



#endif // __jIRegistry_header__
