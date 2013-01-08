/* file : test_PointBox.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-20 18:50:20
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"




// From forum questions

#if 1

template<typename T>
//--------------------------------------------------------------------------
struct jPoint {
//--------------------------------------------------------------------------
	jPoint() {}
	jPoint(T X, T Y) : X(X), Y(Y) {}
	T X, Y;
};

template<typename T>
//--------------------------------------------------------------------------
struct jBox {
//--------------------------------------------------------------------------
	jBox() {}
	jBox(jPoint<T> UpperLeft, jPoint<T> LowerRight) 
		: UpperLeft(UpperLeft)
		, LowerRight(LowerRight) {}
	jPoint<T> UpperLeft, LowerRight;
	void print(void) {
		scprintf(_T("UL.X %f UL.Y %f LR.X %f LR.Y %f\n")
			,UpperLeft.X,UpperLeft.Y,LowerRight.X,LowerRight.Y);
	}
};

template<typename T>
//--------------------------------------------------------------------------
struct jWindow {
//--------------------------------------------------------------------------
	int id;
	jBox<T> box;
};

typedef jPoint<float> jPointf;
typedef jBox<float> jBoxf;
typedef jWindow<float> jWindowf;

#else

struct jPointf {
	float X,Y;
	jPointf() {}
	jPointf(float _X, float _Y) : X(_X), Y(_Y) {}
};

struct jBoxf {
	jPointf UpperLeft,LowerRight;
	jBoxf() {}
	jBoxf(jPointf _UpperLeft,jPointf _LowerRight) : UpperLeft(_UpperLeft), LowerRight(_LowerRight) {}
	void print(void) {
		scprintf(_T("UL.X %f UL.Y %f LR.X %f LR.Y %f\n"),UpperLeft.X,UpperLeft.Y,LowerRight.X,LowerRight.Y);
	}
};

struct jWindowf {
	int id;
	jBoxf box;
};

#endif

DECLARE_INSTANCE_TYPE(jPointf)
DECLARE_INSTANCE_TYPE(jBoxf)
DECLARE_INSTANCE_TYPE(jWindowf)

//--------------------------------------------------------------------------
int constructPointf(float X,float Y,HSQUIRRELVM v) 
//--------------------------------------------------------------------------
{
	return PostConstruct<jPointf>(v,new jPointf(X,Y),ReleaseClassPtr<jPointf>::release);
} // constructPointf

// Must pass by reference or pointer (not copy)
//--------------------------------------------------------------------------
int constructBoxf(jPointf & UpperLeft,jPointf & LowerRight,HSQUIRRELVM v) 
//--------------------------------------------------------------------------
{
	return PostConstruct<jBoxf>(v,new jBoxf(UpperLeft,LowerRight),ReleaseClassPtr<jBoxf>::release);
} // constructBoxf

//--------------------------------------------------------------------------
struct WindowHolder 
//--------------------------------------------------------------------------
{
	static jWindowf * currentWindow;
	static jWindowf * getWindow(void) 
	{
		return currentWindow;
	} // getWindow
};
jWindowf * WindowHolder::currentWindow = 0;

// From forum post: compiler works OK.
//--------------------------------------------------------------------------
void testCompiler(void) 
//--------------------------------------------------------------------------
{
	SquirrelObject test = SquirrelVM::CompileBuffer(_T("\
																										 local SceneManager = getSceneManager() ; \n\
																										 \n\
																										 SceneManager.AddScene(\"Scene1\") ; \n\
																										 SceneManager.AddScene(\"Scene4\") ; \n\
																										 SceneManager.ActivateScene(\"Scene1\") ; \n\
																										 "));
	SquirrelVM::RunScript(test);
}

//--------------------------------------------------------------------------
void testPointfBoxf(void) 
//--------------------------------------------------------------------------
{

	//  testCompiler();

	SQClassDef<jPointf>(_T("jPointf")).
		staticFunc(constructPointf,_T("constructor")).
		var(&jPointf::X,_T("X")).
		var(&jPointf::Y,_T("Y"));

	SQClassDef<jBoxf>(_T("jBoxf")).
		staticFunc(constructBoxf,_T("constructor")).
		func(&jBoxf::print,_T("print")).
		var(&jBoxf::UpperLeft,_T("UpperLeft")).
		var(&jBoxf::LowerRight,_T("LowerRight"));

	SQClassDef<jWindowf>(_T("jWindowf")).
		var(&jWindowf::id,_T("Id")).
		var(&jWindowf::box,_T("box"));

	RegisterGlobal(WindowHolder::getWindow,_T("getWindow"));
	jWindowf myWindow;
	myWindow.id = 42;
	myWindow.box = jBoxf(jPointf(1.f,2.f),jPointf(3.f,4.f));
	WindowHolder::currentWindow = &myWindow;

	// The createWindow() function below creates a new instance on the root table.
	// The instance data is a pointer to the C/C++ instance, and will not be freed
	// or otherwise managed.

	scprintf(_T("\n\n"));
	SquirrelObject test = SquirrelVM::CompileBuffer(_T("\
																										 local MyWindow = jWindowf(); \n\
																										 MyWindow.box = jBoxf(jPointf(11.,22.),jPointf(33.,44.)); \n\
																										 print(MyWindow.box.LowerRight.Y); \n\
																										 \
																										 MyWindow.box.LowerRight.Y += 1.; \n\
																										 local MyWindow2 = jWindowf(); \n\
																										 MyWindow2 = MyWindow; \n\
																										 print(MyWindow2.box.LowerRight.Y); \n\
																										 \
																										 local MyBox = jBoxf(jPointf(10.,20.),jPointf(30.,40.)); \n\
																										 MyBox.UpperLeft = jPointf(1000.,1000.); \n\
																										 MyBox.UpperLeft.X = 5000. \n\
																										 print(MyBox.UpperLeft.X) \n\
																										 print(MyBox.UpperLeft.Y) \n\
																										 \
																										 MyWindow2.box = MyBox; \n\
																										 MyWindow2.box.print(); \n\
																										 MyWindow2 = getWindow(); \n\
																										 print(\"MyWindow2: \"+MyWindow2.Id); \n\
																										 \
																										 MyWindow2.box.print(); \n\
																										 \
																										 function createWindow(name,instance) { \n\
																											::rawset(name,instance); \n\
																										 } \n\
																										 "));
	SquirrelVM::RunScript(test);
	/* 출력
	44
	45
	5000
	1000
	UL.X 5000.000000 UL.Y 1000.000000 LR.X 30.000000 LR.Y 40.000000
	MyWindow2: 42
	UL.X 1.000000 UL.Y 2.000000 LR.X 3.000000 LR.Y 4.000000

	*/

	jWindowf window = myWindow;
	window.id = 54;
	window.box.UpperLeft.X  += 1;
	window.box.UpperLeft.Y  += 1;
	window.box.LowerRight.X += 1;
	window.box.LowerRight.Y += 1;
	// Create a new jWindow instance "NewWindow" on the root table.
	SquirrelFunction<void>(_T("createWindow"))(_T("NewWindow"),&window);

	SquirrelObject test2 = SquirrelVM::CompileBuffer(_T("\
																											print(\"NewWindow: \"+NewWindow.Id); \n\
																											NewWindow.box.print(); NewWindow.box.UpperLeft.X=999;\n\
																											"));
	SquirrelVM::RunScript(test2);
	/* 출력

	NewWindow: 54
	UL.X 2.000000 UL.Y 3.000000 LR.X 4.000000 LR.Y 5.000000
	
	*/
	int i=0;
	++i;
} // testPointfBoxf
