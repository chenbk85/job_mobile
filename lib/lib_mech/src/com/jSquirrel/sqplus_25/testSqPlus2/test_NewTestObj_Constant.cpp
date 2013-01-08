/* file : test_NewTestObj_Constant.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-22 11:31:37
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"


void test_NewTestObj_Constant()
{
#ifdef SQ_USE_CLASS_INHERITANCE

	// Constant test (read only var). Var can change on C++ side, but not on script side.
	try 
	{
		SquirrelObject testRegConstant = SquirrelVM::CompileBuffer(_T(" \
						local t = NewTestObj(); \
						t.c1 = 123; "));//상수에 쓸려고 했으므로 실패한다.
		SquirrelVM::RunScript(testRegConstant);
	} // try
	catch (SquirrelError & e) 
	{
		scprintf(_T("Error: %s, %s\n"),e.desc,_T("Squirrel::TestConstant"));
	} // catch

#endif

}

