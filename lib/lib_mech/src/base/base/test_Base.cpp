/* file : Test_jBase.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-16 18:32:34
comp.: actoz.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "header/jBoost.h"
#include "base/jTestUnit.h"
#include "header/uString_stl.h"
#include "header/nUNI_StringA.h"
#include "header/nUNI_StringW.h"

using namespace nMech;

namespace jBase_TestUnit
{
	struct __aaa23
	{
		tr1::function < void (int)> asdf;
		tr1::function < void (int)> asdf2;
		__aaa23(){ memset(this, 0 , sizeof(*this));}
	};

	jTEST_SUITE_BEGIN( boost_test)
	jTEST( function )
	{
		tr1::function < void (int)> asdf;
		jTEST_CHECK(asdf==false)	;
		__aaa23 aaa;
		jTEST_CHECK( aaa.asdf==false);
	}

	jTEST_SUITE_END(boost_test )


	jTEST_SUITE_BEGIN(unicode_test)
	jTEST(wcs_to_mbs_2)
	{
		// 전역 locale 설정
		std::locale::global(std::locale(""));

		std::string mbs1 = "abcdef가나다라";
		std::wstring wcs1 = L"abcdef가나다라";
		std::string mbs2 = nMech::nUNI::wcs_to_mbs(wcs1);
		jTEST_CHECK(mbs1 == mbs2);
		std::wstring wcs2 = nMech::nUNI::mbs_to_wcs(mbs1);
		jTEST_CHECK(wcs1 == wcs2);
	}

	jTEST(jString_test)
	{

		using namespace nUNI;
		jStringW sTestW( L"Test" );
		jStringA sTestA( "Test" );

		// convert
		jStringW sW = sTestA;
		jStringA sA = sTestW;
		jTEST_CHECK(sW==sTestW);


		scb1024_t testBuf;
		testBuf.set(sTestW.GetBuffer(0));
		acstr szA = testBuf.getA();
		wcstr szW = testBuf.getW();
		jTEST_CHECK(sA==szA);
		jTEST_CHECK(sW==szW);

	}
	jTEST_SUITE_END(unicode_test)

	jTEST_SUITE_BEGIN(header_test)
	jTEST(jFlagHelper_)
	{
		int m_iFlag = 0;
		bool myOldValue=jGETFLAG(m_iFlag,jBIT_12);
		bool myNewValue = true;
		jFlagHelper  flagTinyXml(m_iFlag, jBIT_12, myNewValue);
		jEQUAL(flagTinyXml.Get() , myNewValue);
		flagTinyXml.Set(false);
		jEQUAL(flagTinyXml.Get() , false);
		flagTinyXml.Reset();
		jEQUAL(flagTinyXml.Get() , myOldValue);
	}

	jTEST_SUITE_END(header_test)



};
