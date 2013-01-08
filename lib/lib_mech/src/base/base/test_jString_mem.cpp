/* file : test_jString_mem.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-18 16:59:01
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jString_mem.h"
#include "base/jTestUnit.h"
#include "header/jBoost.h"

namespace nMech
{
	namespace nString
	{

		jTEST_SUITE_BEGIN( string_test)
		jTEST( jString_mem )
		{
#if 0
#ifndef _ORG_NEW
			TCHAR* p = _T("1234");
			const int iT = 64-iOFFSET;
			TCHAR* sz = char_p_new(iT);
			int iSize =char_p_size(sz) ;
			jEQUAL(iSize , (iT) );

			using namespace boost::lambda;
			for_each(sz , sz+iSize , _1 = _T('@')) ;
			jEQUAL(sz[iT-1], '@');
			jEQUAL(sz[iT] , 0);
			std::fill(sz, sz+iSize , _T('#'));
			jEQUAL(sz[iT-1] , _T('#'));
			jEQUAL(sz[iT] , 0);
			char_p_delete(sz);
#endif
#endif
		}
		jTEST_SUITE_END(string_test)
	}

}
