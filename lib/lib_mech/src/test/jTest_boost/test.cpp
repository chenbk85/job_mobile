#include <stdafx.h>
#include <vector>
#include <boost/test/unit_test.hpp>
using namespace std;
using namespace boost::unit_test_framework;

// 
// STL��vectorŬ���� ���ø��� �׽�Ʈ �ڵ带 �� ���ҽ��ϴ�.
// 

void push_back_test()
{
	vector<int> v;
	BOOST_CHECK( v.empty() );
	BOOST_CHECK_EQUAL( v.size(), 0 );

	v.push_back( 1 );
	v.push_back( 2 );
	BOOST_CHECK( !v.empty() );
	BOOST_CHECK_EQUAL( v.size(), 2 );
	BOOST_CHECK_EQUAL( v.front(), 1 );
	BOOST_CHECK_EQUAL( v.back(),  2 );
}

void at_test()
{
	vector<char> vi( 100, 'a' );
	BOOST_CHECK_THROW( vi.at(100), std::exception );
}

void construct_test()
{
	vector<int> vi( 100, 3 );
	BOOST_CHECK_EQUAL( vi.size(), 100 );
	BOOST_CHECK_EQUAL( vi[10], 3 );

	vector<double> vd( vi.begin(), vi.end() );
	BOOST_CHECK_EQUAL( vd.size(), 100 );
	BOOST_CHECK_EQUAL( vd[99], 3.0 );
}

// 
// ����븦 ���⼭test_suite�� �߰��� �����ָ�,
// �׸���� ���̺귯�������� �׽�Ʈ�� �޸��� �� �ݴϴ�.
// 

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
	test_suite* test = BOOST_TEST_SUITE( "std::vector test" );
	test->add( BOOST_TEST_CASE( &construct_test ) );
	test->add( BOOST_TEST_CASE( &at_test ) );
	test->add( BOOST_TEST_CASE( &push_back_test ) );
	return test;
}
/*
���࿹
�����Ͻÿ��� ���̺귯���� ��ũ�� �ʿ�.�����ϸ�, ������ ���� ǥ�õ˴ϴ�. 

C:temp> cl test.cpp libboost_unit_test_framework.lib
C:temp> test
Running 3 test cases...

*** No errors detected

�׽�Ʈ�� ���а� ������, ������ ���� ǥ�ð� �˴ϴ�. 

Running 3 test cases...
test.cpp(24): error in "at_test": exception std::exception is expected

*** 1 failure detected in test suite "std::vector test"

*/