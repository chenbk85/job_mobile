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
		RegisterGlobal(*this,&TestScripts::Test1,_T("Gb_Test1"));
		RegisterGlobal(*this,&TestScripts::Test2,_T("Gb_Test2"));
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

#include "interface/net/excel_code_util.h"
enum EAAA
{
	__aa,
	__bb,
	__cc,
};

PROTOS_ENUM_TYPE_csv(EAAA);
DECLARE_ENUM_TYPE_csv(EAAA);

//--------------------------------------------------------------------------
void test_Class_Bind()
//--------------------------------------------------------------------------
{

	nSQ::SquirrelObject asdf=  GetjISQ()->VM_CreateTable();

	nSQ::BindConstant(asdf, __aa,_T("__aa") );


	// Example from forum question:
	testScripts.InitScript1();
	testScripts.InitScript2();
	SquirrelObject testScriptBinding = GetjISQ()->VM_CompileBuffer(_T("\
																																	local testScripts = STestScripts(); \n\
																																	testScripts.Test1(); \n\
																																	testScripts.Test2(); \n\
																																	print(testScripts.Var_ToBind2); \n\
																																	Gb_Test1(); \n\
																																	Gb_Test2(); \n\
																																	print(Var_ToBind1); \n\
																																	"));
	GetjISQ()->VM_RunScript(testScriptBinding);
	/* Ãâ·Â

	Test1 called.
	Test2 called.
	909
	Test1 called.
	Test2 called.
	808

	*/

}

