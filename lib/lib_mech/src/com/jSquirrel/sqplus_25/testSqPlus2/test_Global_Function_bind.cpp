/* file : test_Global_Function_bind.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 11:26:45
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "NewTestObj.h"



// === Standard (non member) function ===
//--------------------------------------------------------------------------
int testFunc(HSQUIRRELVM v) 
//--------------------------------------------------------------------------
{
	StackHandler sa(v);
	int paramCount = sa.GetParamCount();
	scprintf(_T("testFunc: numParams[%d]\n"),paramCount);
	for (int i=1; i <= paramCount; i++) {
		scprintf(_T("param[%d]: "),i);
		switch(sa.GetType(i)) {
		case OT_TABLE:   scprintf(_T("OT_TABLE[0x%x]\n"),sa.GetObjectHandle(i)); break;
		case OT_INTEGER: scprintf(_T("OT_INTEGER[%d]\n"),sa.GetInt(i));    break;
		case OT_FLOAT:   scprintf(_T("OT_FLOAT[%f]\n"),sa.GetFloat(i));    break;
		case OT_STRING:  scprintf(_T("OT_STRING[%s]\n"),sa.GetString(i));  break;
		default:
			scprintf(_T("TYPEID[%d]\n"),sa.GetType(i));
		} // switch
	} // for
	return SQ_OK;
} // testFunc

//--------------------------------------------------------------------------
void newtest(void) 
//--------------------------------------------------------------------------
{
	scprintf(_T("NewTest\n"));
}

//--------------------------------------------------------------------------
SQChar * newtestR1(const SQChar * inString) 
//--------------------------------------------------------------------------
{
	scprintf(_T("NewTestR1: %s\n"),inString);
	return _T("Returned String");
}


//--------------------------------------------------------------------------
void test_Global_Function_Bind()
//--------------------------------------------------------------------------
{
	HSQUIRRELVM v = SquirrelVM::GetVMPtr();
	SquirrelObject root = SquirrelVM::GetRootTable();


	// === BEGIN Global Function binding tests ===
	// Implemented as SquirrelVM::CreateFunction(rootTable,func,name,typeMask). CreateFunctionGlobal() binds a standard SQFUNCTION (stack args).
	SquirrelVM::CreateFunctionGlobal(testFunc,_T("testFunc0"));
	SquirrelVM::CreateFunctionGlobal(testFunc,_T("testFuncN"),_T("n"));
	SquirrelVM::CreateFunctionGlobal(testFunc,_T("testFuncS"),_T("s"));
#if 0
	SquirrelObject testStandardFuncs = SquirrelVM::CompileBuffer(_T(" testFunc0(); testFuncN(1.); testFuncS(\"Hello\"); "));
	SquirrelVM::RunScript(testStandardFuncs);
#endif



	//--------------------------------------------------------------------------
	// === Register Standard Functions using template system (function will be directly called with argument auto-marshaling) ===
	//--------------------------------------------------------------------------

	RegisterGlobal(v,newtest,_T("test"));
	RegisterGlobal(v,newtestR1,_T("newtestR1_global"));


	SquirrelObject testReg3 = SquirrelVM::CompileBuffer(_T(" \
					test(); \
					local rv = newtestR1_global(\"Hello\"); \
					print(rv); "));
	SquirrelVM::RunScript(testReg3);     
	/* 출력

	NewTest
	NewTestR1: Hello
	Returned String

	*/


	//--------------------------------------------------------------------------
	// === Register Member Functions to existing classes (as opposed to instances of classes) ===
	//--------------------------------------------------------------------------

	NewTestObj t1,t2,t3;
	t1.val = 123;
	t2.val = 456;
	t3.val = 789;
	RegisterGlobal(v,t1,&NewTestObj::newtest,_T("testObj_newtest1"));
	RegisterGlobal(v,t2,&NewTestObj::newtest,_T("testObj_newtest2")); // Register newtest() again with different name and object pointer.
	SquirrelObject tr = SquirrelVM::GetRootTable(); // Can be any object supporting closures (functions).
	Register(v,tr.GetObjectHandle(),t3,&NewTestObj::newtestR1,_T("testObj_newtestR1")); // Return value version.

	// === END Global Function binding tests ===


	SquirrelObject testReg4 = SquirrelVM::CompileBuffer(_T(" \
					print(\"\\nMembers:\"); \
					testObj_newtest1(); \
					testObj_newtest2(); \
					print(testObj_newtestR1(\"Hello Again\")); "));
	SquirrelVM::RunScript(testReg4);
	/* 출력

	Members:
	NewTest: 123
	NewTest: 456
	NewTestR1: Member var val is 789, function arg is Hello Again
	Returned String

	*/


}
