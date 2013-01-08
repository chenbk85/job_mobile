/* file : jConsoleDLL.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-10 18:35:51
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jConsoleDLL_header__
#define __jConsoleDLL_header__
#pragma once

#include "interface/jIConsoleDLL.h"

namespace nMech
{
	namespace nCONSOLE
	{
#pragma warning(disable : 4275)
		class JUTIL_API jConsoleDLL_Net : public jIConsoleDLL
		{
			jINTERFACE_HEADER(jIConsoleDLL);
			typedef jIConsoleDLL interfact_t;
			typedef jConsoleDLL_Net parent_t;
		public:
			jIE* m_eNetConfig;
			jConsoleDLL_Net():m_eNetConfig(0){}
		};

#pragma warning(default : 4275)

	}//namespace nCONSOLE
}



#endif // __jConsoleDLL_header__
