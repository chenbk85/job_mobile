/* file : test_InterfaceTest.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-20 18:50:27
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"



// === BEGIN Interface Test ===

//--------------------------------------------------------------------------
class PureInterface 
//--------------------------------------------------------------------------
{
public:
	virtual void pureFunc1(void)=0;
	virtual void pureFunc2(void)=0;
};

//--------------------------------------------------------------------------
class MyImp : public PureInterface 
//--------------------------------------------------------------------------
{
public:
	PureInterface * getInterface(void) { return (PureInterface *)this; }
	void pureFunc1(void) {
		scprintf(_T("PureFunc1 called [0x%p].\n"),this);
	}
	void pureFunc2(void) {
		scprintf(_T("PureFunc2 called [0x%p].\n"),this);
	}
};

//--------------------------------------------------------------------------
class InterfaceHolder 
//--------------------------------------------------------------------------
{
public:
	PureInterface * theInterface;
	void setInterface(PureInterface * pureInterface) {
		theInterface = pureInterface;
	}
	PureInterface * getInterface(void) {
		return theInterface;
	}
};

DECLARE_INSTANCE_TYPE(PureInterface)
DECLARE_INSTANCE_TYPE(MyImp)
DECLARE_INSTANCE_TYPE(InterfaceHolder)

//--------------------------------------------------------------------------
void testPureVirtualInterface(void) 
//--------------------------------------------------------------------------
{
	SQClassDefNoConstructor<PureInterface>(_T("PureInterface")).
		func(&PureInterface::pureFunc1,_T("pureFunc1")).
		func(&PureInterface::pureFunc2,_T("pureFunc2"));

	SQClassDef<InterfaceHolder>(_T("InterfaceHolder")).
		func(&InterfaceHolder::setInterface,_T("setInterface")).
		func(&InterfaceHolder::getInterface,_T("getInterface"));

	SQClassDef<MyImp>(_T("MyImp")).
		func(&MyImp::getInterface,_T("getInterface"));

	MyImp myImp;

	SquirrelObject test = SquirrelVM::CompileBuffer(_T("ih <- InterfaceHolder();"));
	SquirrelVM::RunScript(test);

	SquirrelObject root = SquirrelVM::GetRootTable();
	SquirrelObject ih = root.GetValue(_T("ih"));
	InterfaceHolder * ihp = (InterfaceHolder * )ih.GetInstanceUP(ClassType<InterfaceHolder>::type());
	ihp->setInterface(&myImp);

	test = SquirrelVM::CompileBuffer(_T("\
																			ih.getInterface().pureFunc1(); \n\
																			ih.getInterface().pureFunc2(); \n\
																			ihp <- ih.getInterface(); \n\
																			ihp.pureFunc1(); \n\
																			ihp.pureFunc2(); \n\
																			myIh <- MyImp(); \n\
																			ih.setInterface(myIh.getInterface()); \n\
																			ih.getInterface().pureFunc1(); \n\
																			ih.getInterface().pureFunc2(); \n\
																			"));
	SquirrelVM::RunScript(test);

	/*
	Start Pass 1

	PureFunc1 called [0x0013F1AC].
	PureFunc2 called [0x0013F1AC].
	PureFunc1 called [0x0013F1AC].
	PureFunc2 called [0x0013F1AC].
	PureFunc1 called [0x005C9960].
	PureFunc2 called [0x005C9960].

	*/



} // testPureVirtualInterface

// === END Interface Test ===
