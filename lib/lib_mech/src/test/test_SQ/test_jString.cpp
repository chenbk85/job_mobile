/* file : test_jString.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-13 22:08:40
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "header/jString.h"

//DECLARE_INSTANCE_TYPE(nMech::jString);

void test_jString()
{
	/*
	작업보류.
	size_t sss = sizeof(jString32);
	jString32 buf32=_T("asdf");
	buf32 = _T("1234567890123456789012345678901234567890");
	jChar * ch = buf32;
	jt_printf(_T("Valc is: %s\n"),buf32);
	*/
#if 0
	SquirrelObject tc(buf32 ); 
	// constant argument is passed by value (even though declaration is by ref: const & results in by-value in this case), memory will be allocated and managed for the copy.

	jString32 valc = tc.Get<jString32>();
	scprintf(_T("Valc is: %s\n"),valc);
#endif

}

