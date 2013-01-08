/* file : test_Vector3.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 14:59:22
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "test_Vector3.h"
int g_vec_sid=0;

float Vector3::staticVar = 898.434f;

int globalVar = 5551234;

Vector3 Add2(Vector3 & a,Vector3 & b) {
	scprintf(_T("Vector3 Add2(Vector3 & a,Vector3 & b)\n"));
	Vector3 c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
} // Add2

int Add(HSQUIRRELVM v) {
	//  StackHandler sa(v);
	scprintf(_T("int Add(HSQUIRRELVM v)\n"));
	Vector3 * self = GetInstance<Vector3,true>(v,1);
	Vector3 * arg  = GetInstance<Vector3,true>(v,2);
	//  SquirrelObject so = sa.GetObjectHandle(1);
#if 0
	SQUserPointer type=0;
	so.GetTypeTag(&type);
	SQUserPointer reqType = ClassType<Vector3>::type();
	if (type != reqType) {
		throw SquirrelError(_T("Invalid class type"));
	} // if
#endif
	//  Vector3 * self = (Vector3 *)so.GetInstanceUP(ClassType<Vector3>::type());
	//  if (!self) throw SquirrelError(_T("Invalid class type"));
	Vector3 tv;
	tv.x = arg->x + self->x;
	tv.y = arg->y + self->y;
	tv.z = arg->z + self->z;
	return ReturnCopy(v,tv);
}


void Vector3::InitSQ()
{

#define SQ_10 10
#define SQ_E 2.71828182845904523536f
#define SQ_PI 3.14159265358979323846264338327950288f
#define SQ_CONST_STRING _T("A constant string")
	const int intConstant     = 7;
	const float floatConstant = 8.765f;
	const bool boolConstant   = true;
#if 1
	SQClassDef<Vector3>(_T("Vector3")).
		var(&Vector3::x,_T("x")).
		var(&Vector3::y,_T("y")).
		var(&Vector3::z,_T("z")).
		var(&Vector3::id,_T("id")).
		var(&Vector3::ref,_T("ref")).
		func(&Vector3::Inc,_T("Inc")).
		func(&Vector3::operator+,_T("_add")).
		func(&Vector3::Print,_T("Print") ).
		staticFunc(&Add2,_T("Add2")).
		staticFuncVarArgs(&Add,_T("Add")).
#if 1
		staticVar(&Vector3::staticVar,_T("staticVar")).
#else
		staticVar(&Vector3::staticVar,_T("staticVar"),VAR_ACCESS_READ_ONLY).
#endif
		staticVar(&globalVar,_T("globalVar")).
		constant(SQ_10,_T("SQ_10")).
		constant(SQ_E,_T("SQ_E")).
		constant(SQ_PI,_T("SQ_PI")).
		constant(SQ_CONST_STRING,_T("SQ_CONST_STRING")).
		enumInt(SQ_ENUM_TEST,_T("SQ_ENUM_TEST")).
		constant(intConstant,_T("intConstant")).
		constant(floatConstant,_T("floatConstant")).
		constant(true,_T("boolTrue")).
		constant(false,_T("boolFalse")).
		constant(boolConstant,_T("boolConstant"));
#endif
}


//--------------------------------------------------------------------------
void Vector3::test_SquirrelObject_SetGet_Vector3(void) 
//--------------------------------------------------------------------------
{
	if (1) 
	{
		SquirrelObject v(Vector3(1.f,2.f,3.f)); 
		// Pass in by reference: will be copied once, with memory for new copy managed by Squirrel.

		/* 출력 

		Vector(id=0 ,  1.00, 2.00, 3.00)
		Vector(id=1)
		Vector operator=(id=1 from id=0)
		~Vector(id=0, ref=0)

		*/

		Vector3 * pv = v.Get<Vector3 *>();
		pv->Print();
		/*출력
		
		Vector3 is: 1.000000 2.000000 3.000000

		*/
		pv->z += 1.f;

		if (1) 
		{
			SquirrelObject v2p(pv); // This is a pointer to v's instance (passed in by pointer: see SquirrelObject.h). 
			// A new Squirrel Instance will be created, but the C++ instance pointer will not get freed when v2p goes out of scope (release hook will be null).
			pv = v2p.Get<Vector3 *>();
			pv->Print();
		} // if

		/*출력

		Vector3 is: 1.000000 2.000000 4.000000

		*/

	} // if

	/* 출력

	~Vector(id=1, ref=0)

	*/

	scprintf(_T("Vector3() instance has been released.\n\n"));


	BindConstant(SQ_PI*2,_T("SQ_PI_2"));
	BindConstant(SQ_10*2,_T("SQ_10_2"));
	BindConstant(_T("Global String"),_T("GLOBAL_STRING"));

	SquirrelObject testStaticVars = SquirrelVM::CompileBuffer(_T(" \
										 local v2 = Vector3(); \
										 local v3 = Vector3(); \
										 local v4 = v2+v3; \
										 v4.Print();\
										 v4 += v3; \
										 v4.Print();\
										 print(\"Vector3::staticVar: \"+v2.staticVar+\" Vector3::globalVar: \"+v2.globalVar); \
										 v2.staticVar = 0; "));
	SquirrelVM::RunScript(testStaticVars);
	/* 출력

	Vector(id=2)
	Vector(id=3)
	Vector::operator +(id=2, id=3)
	Vector(id=4 ,  2.00, 4.00, 6.00)
	~Vector(id=4, ref=0)
	Vector(id=5)
	Vector operator=(id=5 from id=4)
	~Vector(id=4, ref=0)
	Print Vector3(id=5), 2.000000 4.000000 6.000000
	Vector::operator +(id=5, id=3)
	Vector(id=6 ,  3.00, 6.00, 9.00)
	~Vector(id=6, ref=0)
	Vector(id=7)
	Vector operator=(id=7 from id=6)
	~Vector(id=6, ref=0)
	~Vector(id=5, ref=0)
	Print Vector3(id=7), 3.000000 6.000000 9.000000
	Vector3::staticVar: 898.434 Vector3::globalVar: 5551234
	~Vector(id=7, ref=0)
	~Vector(id=3, ref=0)
	~Vector(id=2, ref=0)

	*/

	SquirrelObject testConstants0 = SquirrelVM::CompileBuffer(
		_T(" print(\"SQ_PI*2: \"+SQ_PI_2+\" SQ_10_2: \"+SQ_10_2+\" GLOBAL_STRING: \"+GLOBAL_STRING); "));
	SquirrelVM::RunScript(testConstants0);

	/* 출력

	SQ_PI*2: 6.28319 SQ_10_2: 20 GLOBAL_STRING: Global String

	*/

	SquirrelObject testConstants1 = SquirrelVM::CompileBuffer(
		_T("local v = Vector3(); \
			 print(\"SQ_10: \"+v.SQ_10+\" SQ_E: \"+v.SQ_E+\" SQ_PI: \"+v.SQ_PI+\" \
							SQ_CONST_STRING: \"+v.SQ_CONST_STRING+\" SQ_ENUM_TEST: \"+v.SQ_ENUM_TEST);" ));
	SquirrelVM::RunScript(testConstants1);

	/* 출력

	Vector(id=8)
	SQ_10: 10 SQ_E: 2.71828 SQ_PI: 3.14159
	SQ_CONST_STRING: A constant string SQ_ENUM_TEST: 1234321
	~Vector(id=8, ref=0)

	*/

	SquirrelObject testConstants2 = SquirrelVM::CompileBuffer(_T("\
			 local v = Vector3(); \
			 print(\"intConstant: \"+v.intConstant+\" floatConstant: \
			 \"+v.floatConstant+\" boolTrue: \
			 \"+(v.boolTrue?\"True\":\"False\")+\" boolFalse: \"+(v.boolFalse?\"True\":\"False\")+\" boolConstant: \
			 \"+(v.boolConstant?\"True\":\"False\"));" ));
	SquirrelVM::RunScript(testConstants2);
	/*출력

	Vector(id=9)
	intConstant: 7 floatConstant:                    8.765 boolTrue:
	True boolFalse: False boolConstant:                     True
	~Vector(id=9, ref=0)

	*/



	SquirrelObject testRegV = 
		SquirrelVM::CompileBuffer(_T(" \
																 local vec = Vector3(); \
																 print(vec.x); \
																 vec = vec.Add(vec); \
																 print(vec.x); \
																 \
																 vec = vec.Add(vec); \
																 print(vec.x); \
																 \
																 vec = vec.Add2(vec,vec); \
																 print(vec.x); \
																 \
																 local v2 = Vector3(); \
																 vec = v2.Inc(vec); \
																 print(vec.x); \
																 print(v2.x); "));
	SquirrelVM::RunScript(testRegV);



} // test_SquirrelObject_SetGet_Vector3

