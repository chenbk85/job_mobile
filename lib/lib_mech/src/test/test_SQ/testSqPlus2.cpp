/* file : testSqPlus2.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-20 18:50:07
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "common/jInit.h"
#include <conio.h>

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



#ifdef USE_ORG_SQ_LIB
// Example debug hook: called back during script execution.
int debug_hook(HSQUIRRELVM v) {
  SQUserPointer up;
  int event_type,line;
  const SQChar *src,*func;
  GetjISQ()->sq_getinteger(v,2,&event_type);
  GetjISQ()->sq_getstring(v,3,&src);
  GetjISQ()->sq_getinteger(v,4,&line);
  GetjISQ()->sq_getstring(v,5,&func);
  GetjISQ()->sq_getuserpointer(v,-1,&up);
  return 0;
} // debug_hook
#endif


#define SQDBG_DEBUG_HOOK _T("_sqdebughook_")

class TestSqPlus 
{
public:

  TestSqPlus() 
	{

		void test_Class_Bind();test_Class_Bind();
		jSQ_TEST(test_jString);
		jSQ_TEST(testPureVirtualInterface);
		jSQ_TEST(testScriptingTypeName);
		jSQ_TEST(testPointfBoxf);
		jSQ_TEST(test_Global_Function_Bind);
		jSQ_TEST(test_Namespace);

    try 
		{
      // === BEGIN Class Instance tests ===
			jSQ_TEST(test_SquirrelObject);
			jSQ_TEST(test_SquirrelObject_SetGet_Vector3); // Uses Vector3().
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
			jSQ_TEST(test_jXml);

    } // try
    catch (SquirrelError & e) 
		{
      scprintf(_T("Error: %s, in %s\n"),e.desc,_T("TestSqPlus"));
    } // catch

  }

  ~TestSqPlus() 
	{
#ifdef USE_ORG_SQ_LIB
    GetjISQ()->End();
#endif
  }

};

namespace nSQ_test
{
	jSQ_REGIST_BIND(nSQ_test)
	{
		NewTestObj::Bind_Squirrel();
		Vector3::Bind_Squirrel();
	}
}


int main(int argc,char * argv[]) 
{

  // Run twice to make sure cleanup/shutdown works OK.
  SCPUTS(_T("Start Pass 1\n"));
 // doTest();
#if 0
  SCPUTS(_T("Start Pass 2\n"));
#endif
  SCPUTS(_T("Done.\n"));

#ifdef USE_ORG_SQ_LIB
	GetjISQ()->Bind(_T("NewTestObj::Bind_Squirrel"),NewTestObj::Bind_Squirrel);
	GetjISQ()->Bind(_T("Vector3::Bind_Squirrel"),Vector3::Bind_Squirrel);

	nSQ::Begin_param param;
	param.m_debug_hook_func=debug_hook;
	param.m_enabledebuginfo = SQTrue;
	param.m_SQDBG_DEBUG_HOOK = SQDBG_DEBUG_HOOK;
	GetjISQ()->Begin(&param);
#endif
	jMech_Init();

	TestSqPlus testSqPlus;

	jMech_Close();
  scprintf(_T("Press RETURN to exit."));

	_getch();


	return 0;
}
