/* file : test_Inheritance.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 19:17:08
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"


class TestBase {
public:
	int x;
	TestBase() : x(0) {
		printf("Constructing TestBase[0x%x]\n",(size_t)this);
	}
	void print(void) {
		printf("TestBase[0x%x], x[%d]\n",(size_t)this,x);
	}
};

DECLARE_INSTANCE_TYPE(TestBase)

class TestDerivedCPP : public TestBase {
public:
	int y;
	TestDerivedCPP() {
		x = 121;
	}
};

typedef void (TestDerivedCPP::*TestDerivedCPP_print)(void);




void testInhertianceCase(void) 
{

	SQClassDef<TestBase>(_T("TestBase")).
		var(&TestBase::x,_T("x")).
		func(&TestBase::print,_T("print"));

	SQClassDef<TestDerivedCPP>(_T("TestDerivedCPP")).
		func((TestDerivedCPP_print)&TestDerivedCPP::print,_T("print"));

	// Note that the constructor definition and call below is not required for this example.
	// (The C/C++ constructor will be called automatically).

	SquirrelObject testInheritance2 = GetjISQ()->VM_CompileBuffer(_T("\
						 class TestDerived extends TestBase { \n\
							 function print() {                 \n\
								 ::TestBase.print();              \n\
								 ::print(\"Derived: \"+x);        \n\
							 }                                  \n\
							 constructor() {                    \n\
								 TestBase.constructor();          \n\
							 }                                  \n\
						 }                                    \n\
						 local a = TestDerived();             \n\
						 local b = TestDerived();             \n\
						 a.x = 1;                             \n\
						 b.x = 2;                             \n\
						 print(\"a.x = \"+a.x);               \n\
						 print(\"b.x = \"+b.x);               \n\
						 a.print();                           \n\
						 b.print();                           \n\
						 local c = TestDerivedCPP();          \n\
						 c.print();                           \n\
						 "));
	GetjISQ()->VM_RunScript(testInheritance2);
	GetjISQ()->VM_RunScript(testInheritance2);
	/* Ãâ·Â

	Constructing TestBase[0x5df3e0]
	Constructing TestBase[0x5d6168]
	a.x = 1
	b.x = 2
	TestBase[0x5df3e0], x[1]
	Derived: 1
	TestBase[0x5d6168], x[2]
	Derived: 2
	Constructing TestBase[0x5df188]
	TestBase[0x5df188], x[121]

	*/
}
