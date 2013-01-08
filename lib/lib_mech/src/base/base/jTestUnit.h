/* file : jITestUnit.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-21 12:50:56
comp.: pantavision.co.kr
title : 
desc : 

#include "base/jTestUnit.h"

using namespace nMech;
namespace 
{
	jTEST_SUITE_BEGIN(suit)
	jTEST(test)
	{

	}

	jTEST_SUITE_END(suit)
}

*/

#ifndef __jITestUnit_header__
#define __jITestUnit_header__
#pragma once

#include "header/jSington.h"
#include "header/jInterface.h"

// UnitTest++
//#define jUSE_UNITTEST_PLUS

// 부스트 테스트
#define jUSE_BOOST_TEST

namespace nMech
{
	namespace nTest 
	{
		typedef void dll_test_function_t();

//--------------------------------------------------------------------------
// struct jITestUnit
//--------------------------------------------------------------------------
#define jINTERFACE_jITestUnit(x) public:	\
	virtual void RunTest(bool isTested_VUTPP=false) ##x \
	virtual void RegistDLLTest(tcstr szModuleName,dll_test_function_t*) ##x\
	virtual bool IsTested_VUTPP() ##x\

		jINTERFACE_END(jITestUnit);
		jSINGTON_INTERFACE_HEADER(JBASE_API , jITestUnit);
	
	}//nTest
}

#ifdef jUSE_UNITTEST_PLUS

	#include "y:/UnitTest++/src/UnitTest++.h"
	#ifdef _DEBUG
	#pragma comment(lib, "y:/UnitTest++/debug/UnitTest++.vsnet2005.lib")
	#else
	#pragma comment(lib, "y:/UnitTest++/release/UnitTest++.vsnet2005.lib")
	#endif

	#define jTEST_SUITE_BEGIN(X)		SUITE( X ){
	#define jTEST_SUITE_END(X)			}
	#define jTEST(X)								TEST(X)
	#define jEQUAL(X,Y)							CHECK_EQUAL(X,Y)
	#define jTEST_CHECK(X)								CHECK(X)
	#define jCLOSE(X,Y,OFFSET)			CHECK_CLOSE( X, Y, OFFSET );
	using namespace UnitTest;

#endif 

#ifdef jUSE_BOOST_TEST
	

	//#include <boost/test/floating_point_comparison.hpp>
	#include <boost/test/unit_test.hpp>
	#include "header/uString_stl.h"

	#define jTEST_SUITE_BEGIN(X)		BOOST_AUTO_TEST_SUITE(X)
	#define jTEST_SUITE_END(X)			BOOST_AUTO_TEST_SUITE_END()
	#define jTEST(X)								BOOST_AUTO_TEST_CASE(X)
	#define jEQUAL(X,Y)							BOOST_CHECK_EQUAL(X,Y)
	#define jTEST_CHECK(X)								BOOST_CHECK(X)
	#define jCLOSE(X,Y,OFFSET)			BOOST_CHECK_CLOSE( X, Y, OFFSET );

#ifdef jUSE_VC80_VER 
	//http://reiot.springnote.com/pages/117356
	namespace boost { namespace test_tools { namespace tt_detail {
		template<> struct print_log_value<std::wstring>
		{
			void    operator()( std::ostream& ostr, std::wstring t )
			{
				std::string s = nMech::nUNI::wcs_to_mbs(t);
				ostr <<s;
			}
		};
	} } }
#else

	

#pragma warning(disable : 4996)
	inline std::wstring widen(const std::string& source) 
	{ 
		std::wstring result(source.size(), wchar_t(0)); 
		typedef std::ctype<wchar_t> ctype_t; 
		const ctype_t& ct = std::use_facet<ctype_t>(std::locale()); 
		ct.widen(source.data(), source.data() + source.size(), 
			&(*result.begin())); 
		return result; 
	} 


	inline std::string narrow(std::wstring source) 
	{ 
		std::string result(source.size(), char(0)); 
		typedef std::ctype<wchar_t> ctype_t; 
		const ctype_t& ct = std::use_facet<ctype_t>(std::locale()); 
		char ccc = (char)'\u00B6';
		ct.narrow(source.data(), source.data() + source.size(), ccc, 
			&(*result.begin())); 
		return result; 
	} 
#pragma warning(default : 4996)


	inline std::ostream& operator<<(std::ostream& out, const std::wstring& value) 
	{ 
		out << narrow(value); 
		return out; 
	} 


	inline std::wostream& operator<<(std::wostream& out, const std::string& value) 
	{ 
		out << widen(value); 
		return out; 
	} 

#endif


#endif //jUSE_UNITTEST_PLUS


#endif // __jITestUnit_header__
