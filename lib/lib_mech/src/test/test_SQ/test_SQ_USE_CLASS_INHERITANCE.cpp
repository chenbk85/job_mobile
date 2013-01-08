/* file : test_SQ_USE_CLASS_INHERITANCE.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 19:00:31
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"



//--------------------------------------------------------------------------
struct CustomTestObj 
	//--------------------------------------------------------------------------
{
	ScriptStringVar128 name;
	int val;
	bool state;
	CustomTestObj() : val(0), state(false) { name = _T("empty"); }
	CustomTestObj(const SQChar * _name,int _val,bool _state) : val(_val), state(_state) 
	{
		name = _name;
	}

	// Custom variable argument constructor
	//--------------------------------------------------------------------------
	static int construct(HSQUIRRELVM v) 
	//--------------------------------------------------------------------------
	{
		StackHandler sa(v);
		int paramCount = sa.GetParamCount();
		if (paramCount == 1) 
		{
			return PostConstruct<CustomTestObj>(v,new CustomTestObj(),release);
		} 
		if (paramCount == 4) 
		{
			return PostConstruct<CustomTestObj>(v,new CustomTestObj(sa.GetString(2),sa.GetInt(3),sa.GetBool(4)?true:false),release);
		} // if
		return GetjISQ()->sq_throwerror(v,_T("Invalid Constructor arguments"));
	} // construct

	SQ_DECLARE_RELEASE(CustomTestObj); // Required when using a custom constructor.

	// Member function that handles variable types.
	//--------------------------------------------------------------------------
	int varArgTypes(HSQUIRRELVM v) 
	//--------------------------------------------------------------------------
	{
		StackHandler sa(v);
		int paramCount = sa.GetParamCount();
		if (sa.GetType(2) == OT_INTEGER) 
		{
			val = sa.GetInt(2);
		} // if
		else if (sa.GetType(2) == OT_STRING) 
		{
			name = sa.GetString(2);
		} // if

		if (sa.GetType(3) == OT_INTEGER) 
		{
			val = sa.GetInt(3);
		} // if
		else if (sa.GetType(3) == OT_STRING) 
		{
			name = sa.GetString(3);
		} // if
		//    return sa.ThrowError(_T("varArgTypes() error"));
		return 0;
	} // varArgTypes

	// Member function that handles variable types and has variable return types+count.
	//--------------------------------------------------------------------------
	int varArgTypesAndCount(HSQUIRRELVM v) 
	//--------------------------------------------------------------------------
	{
		StackHandler sa(v);
		int paramCount = sa.GetParamCount();
		SQObjectType type1 = (SQObjectType)sa.GetType(1); // Always OT_INSTANCE
		SQObjectType type2 = (SQObjectType)sa.GetType(2);
		SQObjectType type3 = (SQObjectType)sa.GetType(3);
		SQObjectType type4 = (SQObjectType)sa.GetType(4);
		int returnCount = 0;
		if (paramCount == 3) 
		{
			GetjISQ()->sq_pushinteger(v,val);
			returnCount = 1;
		} 
		else if (paramCount == 4) 
		{
			GetjISQ()->sq_pushinteger(v,val);
			GetjISQ()->sq_pushstring(v,name,-1);
			returnCount = 2;
		} // if
		return returnCount;
	} //

	//--------------------------------------------------------------------------
	int noArgsVariableReturn(HSQUIRRELVM v) 
	//--------------------------------------------------------------------------
	{
		if (val == 123) 
		{
			val++;
			return 0; // This will print (null).
		} 
		else if (val == 124) 
		{
			GetjISQ()->sq_pushinteger(v,val); // Will return int:124.
			val++;
			return 1;
		} 
		else if (val == 125) 
		{
			GetjISQ()->sq_pushinteger(v,val);
			name = _T("Case 125");
			GetjISQ()->sq_pushstring(v,name,-1);
			val = 123; // reset
			return 2;
		} // if
		return 0;
	} // noArgsVariableReturn

	// Registered with func() instead of funcVarArgs(): fixed (single) return type.
	const SQChar * variableArgsFixedReturnType(HSQUIRRELVM v) 
	{
		StackHandler sa(v);
		int paramCount = sa.GetParamCount();
		SQObjectType type1 = (SQObjectType)sa.GetType(1); // Always OT_INSTANCE
		SQObjectType type2 = (SQObjectType)sa.GetType(2);
		SQObjectType type3 = (SQObjectType)sa.GetType(3);
		if (paramCount == 1) {
			return _T("No Args");
		} else if (paramCount == 2) {
			return _T("One Arg");
		} else if (paramCount == 3) {
			return _T("Two Args");
		} // if
		return _T("More than two args");
	} // variableArgsFixedReturnType

	void manyArgs(int i,float f,bool b,const SQChar * s) 
	{
		scprintf(_T("i: %d, f: %f, b: %s, s: %s\n"),i,f,b?_T("true"):_T("false"),s);
	} // manyArgs

	float manyArgsR1(int i,float f,bool b,const SQChar * s)  
	{
		manyArgs(i,f,b,s);
		return i+f;
	} // manyArgsR1

};//struct CustomTestObj 




void test_SQ_USE_CLASS_INHERITANCE()
{
	SquirrelObject scriptedBase = GetjISQ()->VM_CompileBuffer(_T(" \
								 class ScriptedBase \
								 { \
									 sbval = 5551212; \
									 function multiArgs(a,...) \
									 { \
										 print(\"SBase: \"+a+\"  val = \" + val); \
									 } \n \
								 } \n \
								 ")); // Note val does not exist in base.
	GetjISQ()->VM_RunScript(scriptedBase);


#ifdef SQ_USE_CLASS_INHERITANCE
	// Base class constructors, if registered, must use this form: static int construct(HSQUIRRELVM v).
	//      SQClassDef<CustomTestObj> customClass(_T("CustomTestObj"));
	SQClassDef<CustomTestObj> customClass(_T("CustomTestObj"),_T("ScriptedBase"));
	//      SQClassDef<CustomTestObj> customClass(_T("CustomTestObj"),_T("NewTestObj"));
	customClass.staticFuncVarArgs(&CustomTestObj::construct,_T("constructor"),_T("*"));
	// MUST use this form (or no args) if CustomTestObj will be used as a base class.

	// Using the "*" form will allow a single constructor to be used for all cases.
	//      customClass.staticFuncVarArgs(CustomTestObj::construct,_T("constructor"));                     
	// (this form is also OK if used as a base class)

	customClass.funcVarArgs(&CustomTestObj::varArgTypesAndCount,_T("multiArgs"),_T("*"));                
	// "*": no type or count checking.

	customClass.funcVarArgs(&CustomTestObj::varArgTypesAndCount,_T("varArgTypesAndCount"),_T("*"));      
	// "*": no type or count checking.

#else
	SQClassDef<CustomTestObj> customClass(_T("CustomTestObj"));
	customClass.staticFuncVarArgs(&CustomTestObj::construct,_T("constructor"),_T("snb"));                
	// string, number, bool (all types must match).

	customClass.funcVarArgs(&CustomTestObj::varArgTypesAndCount,_T("varArgTypesAndCount"),_T("*"));      
	// "*": no type or count checking.

#endif
	customClass.funcVarArgs(&CustomTestObj::varArgTypes,_T("varArgTypes"),_T("s|ns|ns|ns|n"));           
	// string or number + string or number.

	customClass.funcVarArgs(&CustomTestObj::noArgsVariableReturn,_T("noArgsVariableReturn"));        
	// No type string means no arguments allowed.

	customClass.func(&CustomTestObj::variableArgsFixedReturnType,_T("variableArgsFixedReturnType")); 
	// Variables args, fixed return type.

	customClass.func(&CustomTestObj::manyArgs,_T("manyArgs"));                                       
	// Many args, type checked.

	customClass.func(&CustomTestObj::manyArgsR1,_T("manyArgsR1"));                                   
	// Many args, type checked, one return value.




#ifdef SQ_USE_CLASS_INHERITANCE
	//      SquirrelObject testInheritance = GetjISQ()->VM_CompileBuffer(_T(" class Derived extends NewTestObj { s1 = 123; \n constructor() { NewTestObj.constructor(this); }; function getParentS2() return s2; \n }; \n local t = Derived(); \n print(\"DerS2: \"+t.getParentS2()); t.multiArgs(); //t.newtestR1(\"R1in\"); "));

	//      SquirrelObject testInheritance = GetjISQ()->VM_CompileBuffer(_T(" local t = CustomTestObj(\"sa\",321,true); \n t.val = 444; print(t.val); t.variableArgsFixedReturnType(4,5.5); t.multiArgs(1,2,3); t.newtestR1(\"R1in\"); "));

	//      SquirrelObject testInheritance = GetjISQ()->VM_CompileBuffer(_T(" class Derived extends CustomTestObj { val = 888; \n function func(a) print(a+dVal);\n } \n local x = Derived(); print(\"x.val \"+x.val); local t = CustomTestObj(\"sa\",321,true); \n t.val = 444; print(t.val); t.variableArgsFixedReturnType(4,5.5); t.multiArgs(1,2,3); t.newtestR1(\"R1in\"); "));

	SquirrelObject testInheritance = GetjISQ()->VM_CompileBuffer(_T(" \
				class Derived extends CustomTestObj \
				{ \
					val = 888; \n \
					function multiArgs(a,...) \
					{ \
						print(a+val); \n \
						print(sbval); \
						::CustomTestObj.multiArgs(4); \
						::ScriptedBase.multiArgs(5,6,7); \n \
					}\n \
				} \n \
				\
				local x = Derived(); \
				print(\"x.val \"+x.val); \
				x.multiArgs(1,2,3); \
				"));

	//      SquirrelObject testInheritance = GetjISQ()->VM_CompileBuffer(_T(" class Derived extends CustomTestObj { val = 888; \n function multiArgs(a,...) print(a+val);\n } \n local x = Derived(); print(\"x.val \"+x.val); x.multiArgs(1,2,3); //local t = CustomTestObj(); \n t.val = 444; print(t.val); t.variableArgsFixedReturnType(4,5.5); t.multiArgs(1,2,3); t.newtestR1(\"R1in\"); "));
	printf("=== BEGIN INHERITANCE ===\n");
	GetjISQ()->VM_RunScript(testInheritance);
	/* 출력

	x.val 888
	889
	5551212
	SBase: 5 val = 888

	*/
	printf("===  END INHERITANCE  ===\n");



	SquirrelObject testReg0 = GetjISQ()->VM_CompileBuffer(_T(" \
					 co <- CustomTestObj(\"hello\",123,true); \
					 co.varArgTypes(\"str\",123,123,\"str\"); \
					 co.varArgTypes(123,\"str\",\"str\",123); "));
	GetjISQ()->VM_RunScript(testReg0);

	SquirrelObject testReg0a = GetjISQ()->VM_CompileBuffer(_T(" \
						print(co.varArgTypesAndCount(1,true)); \
						print(co.varArgTypesAndCount(2,false,3.)); \
						print(\"\\n\"); "));
	GetjISQ()->VM_RunScript(testReg0a);
	/* 출력
	123
	str
	*/

	SquirrelObject testReg0b = GetjISQ()->VM_CompileBuffer(_T(" \
						print(co.noArgsVariableReturn()); \
						print(co.noArgsVariableReturn()); \
						print(co.noArgsVariableReturn()); \
						print(\"\\n\"); "));
	GetjISQ()->VM_RunScript(testReg0b);
	/* 출력
	(null : 0x00000000)
	124
	Case 125
	*/

	SquirrelObject testReg0c = GetjISQ()->VM_CompileBuffer(_T(" \
						print(co.variableArgsFixedReturnType(1)); \
						print(co.variableArgsFixedReturnType(1,2)); \
						print(co.variableArgsFixedReturnType(1,2,3)); \
						print(\"\\n\"); "));
	GetjISQ()->VM_RunScript(testReg0c);
	/*출력
	One Arg
	Two Args
	More than two args
	*/

	SquirrelObject testReg0d = GetjISQ()->VM_CompileBuffer(_T(" \
						co.manyArgs(111,222.2,true,\"Hello\"); \
						print(co.manyArgsR1(333,444.3,false,\"World\")); \
						print(\"\\n\"); "));
	GetjISQ()->VM_RunScript(testReg0d);
	/* 출력
	i: 111, f: 222.199997, b: true, s: Hello
	i: 333, f: 444.299988, b: false, s: World
	777.3
	*/

	SquirrelObject testReg1a = GetjISQ()->VM_CompileBuffer(_T(" \
						co <- CustomTestObj(\"hello\",123,true); \
						co.noArgsVariableReturn(); \
						local t = NewTestObj(\"S1in\",369,true); \
						print(\"C1: \"+t.c1); \
						print(\"C2: \"+t.c2); \
						// t.c1 = 123; "));
	GetjISQ()->VM_RunScript(testReg1a);
	/*출력

	C1: 993
	C2: It's a 9

	*/


#endif






}

