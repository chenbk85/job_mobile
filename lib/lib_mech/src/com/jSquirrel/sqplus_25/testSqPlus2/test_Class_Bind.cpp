/* file : test_Class_Bind.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-20 19:23:07
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"


// Example from forum post question:
//--------------------------------------------------------------------------
class STestScripts {}; // Proxy class
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
class TestScripts 
//--------------------------------------------------------------------------
{
public:
	int Var_ToBind1,Var_ToBind2;

	void InitScript1(void) 
	{
		Var_ToBind1 = 808;
		RegisterGlobal(*this,&TestScripts::Test1,_T("Test1"));
		RegisterGlobal(*this,&TestScripts::Test2,_T("Test2"));
		BindVariable(&Var_ToBind1,_T("Var_ToBind1"));
	} // InitScript1

	void InitScript2(void) 
	{
		Var_ToBind2 = 909;
		SQClassDef<STestScripts>(_T("STestScripts")).
			staticFunc(*this,&TestScripts::Test1,_T("Test1")).
			staticFunc(*this,&TestScripts::Test2,_T("Test2")).
			staticVar(&Var_ToBind2,_T("Var_ToBind2"));
	} // InitScript2

	void Test1(void)	{		scprintf(_T("Test1 called.\n"));	}
	void Test2(void) 	{		scprintf(_T("Test2 called.\n"));	}

} testScripts; // class TestScripts 


//--------------------------------------------------------------------------
void test_Class_Bind()
//--------------------------------------------------------------------------
{
	// Example from forum question:
	testScripts.InitScript1();
	testScripts.InitScript2();
	SquirrelObject testScriptBinding = SquirrelVM::CompileBuffer(_T("\
																																	local testScripts = STestScripts(); \n\
																																	testScripts.Test1(); \n\
																																	testScripts.Test2(); \n\
																																	print(testScripts.Var_ToBind2); \n\
																																	Test1(); \n\
																																	Test2(); \n\
																																	print(Var_ToBind1); \n\
																																	"));
	SquirrelVM::RunScript(testScriptBinding);
	/* Ãâ·Â

	Test1 called.
	Test2 called.
	909
	Test1 called.
	Test2 called.
	808

	*/

}

