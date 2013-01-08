/* file : jTestUnit.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-21 12:50:08
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"


nMech::tcstr g_szTestName =_T("DefaultSuite_jBase");
#define BOOST_TEST_MODULE DefaultSuite_jBase
#include "base/jTestUnit.h"
#include "base/VUTPPBind.h"

void VCTESTPP_RunTest_Init()
{

}



namespace nMech
{
	namespace nTest
	{
		class jTestUnit : public jITestUnit 
		{
			jSINGTON_INTERFACE_DECLEAR(JBASE_API , jTestUnit,jITestUnit);
			jLIST_TYPEDEF_vector(dll_test_function_t*,m_DllTest);

			bool m_isTesting ;
			bool m_isTested_VUTPP;// visual test++에서 테스트수행.

		public:
			~jTestUnit();
			jINTERFACE_HEADER(jITestUnit);

		};
	}
}


namespace nMech
{
	namespace nTest
	{
		jSINGTON_INTERFACE_DEFINE(JBASE_API , jTestUnit,jITestUnit)
		{
			m_isTesting =false;
			m_isTested_VUTPP=true;
		}
		jTestUnit::~jTestUnit()
		{
		}
		bool jTestUnit::IsTested_VUTPP()
		{
			return m_isTested_VUTPP;
		}
		
		inline void caller_dll_test_function(dll_test_function_t* it){	if(it)it();}
		void jTestUnit::RunTest(bool isTested_VUTPP)
		{
			m_isTested_VUTPP= isTested_VUTPP;
#ifdef jUSE_UNITTEST_PLUS
			UnitTest::RunAllTests();
#endif
#ifdef jUSE_BOOST_TEST
			m_isTesting = true;// 테스트 실행중에는 RegistDLLTest가 작동안하게 세팅.
			jFOR_EACH(m_DllTest, caller_dll_test_function);
			m_isTesting = false;
#endif
		}
		void jTestUnit::RegistDLLTest(tcstr szModuleName, dll_test_function_t* pFunc)
		{
			if(m_isTesting) return;
			m_DllTest.push_back(pFunc);
		}

	}//nTest
}

