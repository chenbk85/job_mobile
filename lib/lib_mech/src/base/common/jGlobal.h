/* file : jGlobal.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-07 23:14:22
title : 
desc : 

*/

#ifndef __jGlobal_header__
#define __jGlobal_header__
#pragma once

namespace nMech
{

	typedef jIVar* jIVarP;
	namespace jGuiLib
	{
		extern jCOMMON_API DWORD jGetFontWeight(cstr szWeight);
		extern jCOMMON_API DWORD  jGetTextFormat(jIVar* pV);
		extern jCOMMON_API void SetTextFormat(jIVarP& pvFormat, cstr sz);
		extern jCOMMON_API void SetTextFormat(jIVarP& pvFormat, jIVar* pV);
	}

	namespace nCharSystemLib
	{
		extern jCOMMON_API void jMakeAniName(jIE* pE, fname_t &buf);
	}
}

#endif // __jGlobal_header__
