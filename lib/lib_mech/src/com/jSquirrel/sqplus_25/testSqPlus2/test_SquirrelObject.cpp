/* file : test_SquirrelObject.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 15:18:15
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"


void test_SquirrelObject()
{
	// We can pass in arguments:
	//   by value ('true' arg, required for constant float, int, etc., or when a copy is desired),
	//   by reference (data will be copied to SquirrelObject and memory managed),
	//   by pointer (no data copying: pointer is used directly in SquirrelObject; the memory will not be managed).

	SquirrelObject tc(5.678f); // constant argument is passed by value (even though declaration is by ref: const & results in by-value in this case), memory will be allocated and managed for the copy.
	float valc = tc.Get<float>();

	scprintf(_T("Valc is: %f\n"),valc);

	float val = 1.234f;
	SquirrelObject t(val); // val is passed by reference, memory will be allocated, and the value copied once.

	float val2 = t.Get<float>();

	scprintf(_T("Val2 is: %f\n"),val2);

	/*

	Valc is: 5.678000
	Val2 is: 1.234000

	*/

}

