/* file : NewTestObj.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 14:46:52
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "NewTestObj.h"


GlobalClass globalClass;

// Will be registered in a class namespace.
//--------------------------------------------------------------------------
void globalFunc(const SQChar * s,int val) 
//--------------------------------------------------------------------------
{
	scprintf(_T("globalFunc: s: %s val: %d\n"),s,val);
} // globalFunc



// Using global functions to construct and release classes.
//--------------------------------------------------------------------------
int releaseNewTestObj(SQUserPointer up,SQInteger size) 
//--------------------------------------------------------------------------
{
	SQ_DELETE_CLASS(NewTestObj);
} // releaseNewTestObj

//--------------------------------------------------------------------------
int constructNewTestObj(HSQUIRRELVM v) 
//--------------------------------------------------------------------------
{
	StackHandler sa(v);
	int paramCount = sa.GetParamCount();
	if (paramCount == 1) {
		return PostConstruct<NewTestObj>(v,new NewTestObj(),releaseNewTestObj);
	} else if (paramCount == 4) {
		return PostConstruct<NewTestObj>(v,new NewTestObj(sa.GetString(2),sa.GetInt(3),sa.GetBool(4)?true:false),releaseNewTestObj);
	} // if
	return sq_throwerror(v,_T("Invalid Constructor arguments"));
} // constructNewTestObj


// Using fixed args with auto-marshaling. Note that the HSQUIRRELVM must be last in the argument list (and must be present to send to PostConstruct).
// SquirrelVM::GetVMPtr() could also be used with PostConstruct(): no HSQUIRRELVM argument would be required.
//--------------------------------------------------------------------------
int constructNewTestObjFixedArgs(const SQChar * s,int val,bool b,HSQUIRRELVM v) 
//--------------------------------------------------------------------------
{
	StackHandler sa(v);
	int paramCount = sa.GetParamCount();
	return PostConstruct<NewTestObj>(v,new NewTestObj(s,val,b),releaseNewTestObj);
} // constructNewTestObj

void NewTestObj::InitSQ()
{
	// Example showing two methods for registration.
#if 0
	SQClassDef<NewTestObj> sqClass(_T("NewTestObj"));
	sqClass.func(NewTestObj::newtestR1,_T("newtestR1"));
	sqClass.var(&NewTestObj::val,_T("val"));
	sqClass.var(&NewTestObj::s1,_T("s1"));
	sqClass.var(&NewTestObj::s2,_T("s2"));
	sqClass.var(&NewTestObj::c1,_T("c1"),VAR_ACCESS_READ_ONLY);
	sqClass.var(&NewTestObj::c2,_T("c2"),VAR_ACCESS_READ_ONLY);
	sqClass.funcVarArgs(NewTestObj::multiArgs,_T("multiArgs"));
#endif
	SQClassDef<NewTestObj>(_T("NewTestObj")).                         
		// If a special constructor+destructor are not needed, 
		//the auto-generated versions can be used.
		// Example methods for custom constructors:
		staticFuncVarArgs(constructNewTestObj,_T("constructor"),_T("*")).   
		// Using a global constructor: 
		//	useful in cases where a custom constructor/destructor are required 
		//  and the original class is not to be modified.

		// staticFunc(constructNewTestObjFixedArgs,_T("constructor")).   
		// Using a global constructor: 
		//	useful in cases where a custom constructor/destructor 
		//  are required and the original class is not to be modified.      

		// staticFuncVarArgs(NewTestObj::construct,_T("constructor")).   
		// Using a static member constructor.

		staticFunc(globalFunc,_T("globalFunc")).                        
		// Any global function can be registered in a class namespace 
		// (no 'this' pointer will be passed to the function).
		staticFunc(globalClass,&GlobalClass::func,_T("globalClassFunc")).
		func(&NewTestObj::newtestR1,_T("newtestR1")).
		var(&NewTestObj::val,_T("val")).
		var(&NewTestObj::s1,_T("s1")).
		var(&NewTestObj::s2,_T("s2")).
		var(&NewTestObj::c1,_T("c1"),VAR_ACCESS_READ_ONLY).
		var(&NewTestObj::c2,_T("c2"),VAR_ACCESS_READ_ONLY).
		funcVarArgs(&NewTestObj::multiArgs,_T("multiArgs"));
}



void NewTestObj_Test()
{
	SquirrelObject testReg1 = SquirrelVM::CompileBuffer(_T(" \
			local t = NewTestObj(); \
			t.newtestR1(\"Hello\"); \
			t.val = 789; \
			print(t.val); \
			print(t.s1); \
			print(t.s2); \
			t.s1 = \"New S1\"; \
			print(t.s1); "));
	SquirrelVM::RunScript(testReg1);
	/*출력

	NewTestR1: Member var val is 777, function arg is Hello
	789
	s1=s1
	s2=s2
	New S1

	*/

	SquirrelObject testReg2 = SquirrelVM::CompileBuffer(_T(" \
			local t = NewTestObj(); \
			t.val = 789; \
			print(t.val); \
			t.val = 876; \
			print(t.val); \
			t.multiArgs(1,2,3); \
			t.multiArgs(1,2,3,4); \
			t.globalFunc(\"Hola\",5150,false); \
			t.globalClassFunc(\"Bueno\",5151,true); "));
	SquirrelVM::RunScript(testReg2);
	/*출력

	789
	876

	globalFunc: s: Hola val: 5150
	globalClassFunc: s: Bueno val: 5151

	*/
}
