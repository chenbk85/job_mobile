#include "stdafx.h"
#include <windows.h>
#include "jTestUnit.h"

extern void VCTESTPP_RunTest_Init();
#ifdef jUSE_UNITTEST_PLUS
#include "UnitTest++.h"
#include "TestReporter.h"

using namespace UnitTest;

typedef void (CALLBACK FAR * TestFailureCB) (LPCSTR failure, int line);

class VUTPP_Reporter : public TestReporter
{
private:
	TestFailureCB m_CB;

public:
	VUTPP_Reporter(TestFailureCB CB) : m_CB( CB ){}
	~VUTPP_Reporter() {}

	void ReportTestStart(TestDetails const& test) override {}
	void ReportFailure(TestDetails const& test, char const* failure) override { m_CB( failure, test.lineNumber ); }
	void ReportTestFinish(TestDetails const& test, float secondsElapsed) override {}
	void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed) override {}
};

EXTERN_C __declspec(dllexport) void RunTest( LPCSTR pSuiteName, LPCSTR pTestName, TestFailureCB CB )
{
	if( pTestName == NULL || pSuiteName == NULL || CB == NULL )
	{
		CB( "", -1 );
		return;
	}

	TestList& rTestList = Test::GetTestList();
	const Test* pTest = rTestList.GetHead();
	while( pTest != NULL )
	{
		if( strcmp( pTest->m_details.testName, pTestName ) == 0 && strcmp( pTest->m_details.suiteName, pSuiteName ) == 0 )
		{
			VUTPP_Reporter reporter( CB );
			TestResults testResult( &reporter );
			pTest->Run(testResult);
			return;
		}

		pTest = pTest->next;
	}

	CB( "", -1 );
	return;
}
#endif //jUSE_UNITTEST_PLUS

#ifdef jUSE_BOOST_TEST


#include <windows.h>
#include <boost/test/framework.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/unit_test_log_formatter.hpp>
#include <boost/test/unit_test_suite_impl.hpp>
typedef void (CALLBACK FAR * TestFailureCB) (LPCSTR failure, int line);
void CALLBACK FAR default_TestFailureCB(LPCSTR failure, int line)
{
	printf("%d : %s\n",line , failure);
}

namespace boost {

	namespace unit_test {

		namespace output {

			class BOOST_TEST_DECL vutpp_log_formatter : public unit_test_log_formatter {
			public:
				vutpp_log_formatter(TestFailureCB CB) : m_CB( CB ), m_line_num(-1) {}

				void    log_start( std::ostream&, counter_t test_cases_amount ) {}
				void    log_finish( std::ostream& ) {}
				void    log_build_info( std::ostream& ) {}

				void    test_unit_start( std::ostream&, test_unit const& tu ) {}
				void    test_unit_finish( std::ostream&, test_unit const& tu, unsigned long elapsed ) {};
				void    test_unit_skipped( std::ostream&, test_unit const& tu ) {}

				void    log_exception( std::ostream&, log_checkpoint_data const&, const_string explanation ) {}

				void    log_entry_start( std::ostream&, log_entry_data const& entry_data, log_entry_types let ) 
				{ if(let >= BOOST_UTL_ET_WARNING) m_line_num = (int)entry_data.m_line_num; }
				void    log_entry_value( std::ostream&, const_string value ) 
				{ m_Log += value.begin(); }
				void    log_entry_finish( std::ostream& )
				{ 
					if(m_line_num >= 0) 
						m_CB( m_Log.c_str(), m_line_num ); 
					m_line_num = -1; 
					m_Log.clear(); 
				}

				TestFailureCB m_CB;
			private:
				int m_line_num;
				std::string m_Log;
			};

		} // namespace output

	} // namespace unit_test

} // namespace boost
boost::unit_test::output::vutpp_log_formatter* g_pCustomLog =0;

using namespace boost::unit_test;

struct test_runner : test_tree_visitor {
	test_runner( const std::string& rSuiteName, const std::string& rTestName ) : m_SuiteName( rSuiteName ), m_TestName( rTestName ), m_bRun( false ) {}

	void        visit( test_case const& test )
	{
		if(m_TestName=="")
		{
			char buf[1024];
			test_suite const& rSuite = framework::get<test_suite>( test.p_parent_id );
			ja_sprintf_s(buf, "%s.%s",string(rSuite.p_name).c_str() , string(test.p_name).c_str() );
			g_pCustomLog->m_CB(buf,-1);
			framework::run( &test, false );
			return;
		}
		if( test.p_name != m_TestName )
			return;

		test_suite const& rSuite = framework::get<test_suite>( test.p_parent_id );
		if( rSuite.p_name != m_SuiteName )
			return;

		framework::run( &test, false );

		m_bRun = true;
	}

	std::string m_SuiteName, m_TestName;
	bool m_bRun;
};

test_suite* init_func( int argc, char* argv[] )
{
	return 0;
}


EXTERN_C __declspec(dllexport) void RunTest( LPCSTR pSuiteName, LPCSTR pTestName, TestFailureCB CB )
{
	static bool isFirst=true;
	if(isFirst)
	{
		VCTESTPP_RunTest_Init();
		isFirst=false;
	}
	if( pTestName == NULL || pSuiteName == NULL || CB == NULL )
	{
		CB( "", -1 );
		return;
	}

	framework::init( init_func,__argc, __argv);

	unit_test_log.set_formatter( new output::vutpp_log_formatter(CB) );	

	test_runner runner( pSuiteName, pTestName );
	traverse_test_tree( framework::master_test_suite().p_id, runner );

	if( runner.m_bRun == false )
		CB( "", -1 );
	return;
}
namespace nMech
{
	namespace nTest
	{
		//http://code.google.com/p/vutpp/issues/detail?id=23#c2
		//추가한 함수 : 아무일도 안 함, framework을 초기화하기위한 용도 
		test_suite* init_func( int argc, char* argv[] )
		{
			return 0;
		}

		void jBoost_RunTest()
		{

			framework::init( init_func,__argc, __argv);
			g_pCustomLog = new output::vutpp_log_formatter(default_TestFailureCB);
			unit_test_log.set_formatter( g_pCustomLog  );	

			test_runner runner( "", "");
			traverse_test_tree( framework::master_test_suite().p_id, runner );
		}

		jONCE_RUN(_BOOST_DLLTEST_REGIST)
		{
			nMech::nTest::Get_jITestUnit()->RegistDLLTest(g_szTestName, jBoost_RunTest);
		}
	}
}

#endif //jUSE_BOOST_TEST