/* file : jWinUtil.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-11-05 12:15:07
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jWinUtil_header__
#define __jWinUtil_header__
#pragma once

#include "interface/jIWinUtil.h"


namespace nMech
{
	namespace nUtil
	{
		class jWinUtil  : public jIWinUtil
		{
		public:
			jINTERFACE_HEADER(jIInterface);
			jINTERFACE_HEADER(jIWinUtil);

		};
	}
}


/*

jCREATE_INTERFACE_AUTO(pWinUtil, nMech::nUtil::jWinUtil);

*/

#endif // __jWinUtil_header__
