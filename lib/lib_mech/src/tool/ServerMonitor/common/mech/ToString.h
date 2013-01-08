/* file : ToString.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-01-19 14:54:33
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __ToString_header__
#define __ToString_header__
#pragma once


#include "mech/header/jDefine.h"
#include "mech/header/jTypedef_type.h"

namespace nMech
{

	inline tcstr ToString(SYSTEMTIME& t,tfname_t buf)
	{
		jt_sprintf(buf, _T(jPRINTF_SYSTEMTIME),jSPREED_SYSTEMTIME(t));
		return buf;
	}


}//namespace nMech

#endif // __ToString_header__
