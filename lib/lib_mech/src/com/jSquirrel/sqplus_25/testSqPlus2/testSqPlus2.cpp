/* file : testSqPlus2.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-20 18:50:07
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"

#define jSQ_TEST(X) try {	printf("\n====%s\n",#X);void X(); X();} catch (SquirrelError & e) {scprintf(_T("Error: %s, %s\n"),e.desc,_T(#X)); };


void scprintfunc(HSQUIRRELVM v,const SQChar *s,...) 
{
  static SQChar temp[2048];
  va_list vl;
  va_start(vl,s);
  scvsprintf( temp,s,vl);
  SCPUTS(temp);
  va_end(vl);
}


#include "NewTestObj.h"

#include "test_Vector3.h"




// Example debug hook: called back during script execution.
int debug_hook(HSQUIRRELVM v) {
  SQUserPointer up;
  int event_type,line;
  const SQChar *src,*func;
  sq_getinteger(v,2,&event_type);
  sq_getstring(v,3,&src);
  sq_getinteger(v,4,&line);
  sq_getstring(v,5,&func);
  sq_getuserpointer(v,-1,&up);
  return 0;
} // debug_hook



#define SQDBG_DEBUG_HOOK _T("_sqdebughook_")

class TestSqPlus 
{
public:


  void init(void) {
    SquirrelVM::Init();
    HSQUIRRELVM _v = SquirrelVM::GetVMPtr();

#if 1
    sq_pushregistrytable(_v);
    sq_pushstring(_v,SQDBG_DEBUG_HOOK,-1);
    sq_pushuserpointer(_v,this);
    sq_newclosure(_v,debug_hook,1);
    sq_createslot(_v,-3);
//    sq_pop(_v,1);

//    sq_pushregistrytable(_v);
    sq_pushstring(_v,SQDBG_DEBUG_HOOK,-1);
    sq_rawget(_v,-2);
    sq_setdebughook(_v);
    sq_pop(_v,1);

#endif

    sq_enabledebuginfo(_v,SQTrue);

  } // init

  TestSqPlus() 
	{
    init();

		jSQ_TEST(testPureVirtualInterface);
		jSQ_TEST(testScriptingTypeName);
		jSQ_TEST(testPointfBoxf);
		jSQ_TEST(test_Global_Function_Bind);
		jSQ_TEST(test_Namespace);

    try 
		{
      HSQUIRRELVM v = SquirrelVM::GetVMPtr();
      SquirrelObject root = SquirrelVM::GetRootTable();

      // === BEGIN Class Instance tests ===
			NewTestObj::InitSQ();
			jSQ_TEST(test_SquirrelObject);

			Vector3::InitSQ();
			Vector3::test_SquirrelObject_SetGet_Vector3(); // Uses Vector3().

			jSQ_TEST(test_Class_Instance);
			jSQ_TEST(test_Call_SQFunc);
			jSQ_TEST(test_SQ_USE_CLASS_INHERITANCE);
			jSQ_TEST(testInhertianceCase);

#ifdef SQ_USE_CLASS_INHERITANCE
			jSQ_TEST(test_NewTestObj_Constant);

			jSQ_TEST(NewTestObj_Test);
      // === END Class Instance tests ===

			jSQ_TEST(test_Simple_Variable_binding);
			jSQ_TEST(test_Array);

#endif
    } // try
    catch (SquirrelError & e) 
		{
      scprintf(_T("Error: %s, in %s\n"),e.desc,_T("TestSqPlus"));
    } // catch

  }

  ~TestSqPlus() {
    SquirrelVM::Shutdown();
  }

};

void doTest(void) {
  TestSqPlus testSqPlus;
} // doTest

int main(int argc,char * argv[]) {

  // Run twice to make sure cleanup/shutdown works OK.
  SCPUTS(_T("Start Pass 1\n"));
  doTest();
#if 0
  SCPUTS(_T("Start Pass 2\n"));
  doTest();
#endif
  SCPUTS(_T("Done.\n"));

  scprintf(_T("Press RETURN to exit."));
  getchar();

	return 0;
}
