/* file : test_string.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-29 11:39:17
comp.: www.actoz.com
title : 
desc : 

*/
#include "stdafx.h"
//#include "header/jBoost.h"
#include "base/jTestUnit.h"
#include "header/uString_stl.h"


using namespace nMech;

namespace 
{

	jTEST_SUITE_BEGIN( nSTL_test)
	jTEST( mbs_to_wcs)
	{
		jSET_LOCALE1("kor");

		astring astr = "asdfasdf학교종1234!@#$";
		wstring wstr = L"asdfasdf학교종1234!@#$";
		wstring testW = nUNI::mbs_to_wcs(astr);
		jTEST_CHECK(testW == wstr);

		astring testA = nUNI::wcs_to_mbs(wstr);
		jTEST_CHECK(testA == astr);

	}

	jTEST(string_replace)
	{
		tstring src = _T("asdf1234학교종1234학교종12");
		tstring tok = _T("종1");
		tstring new_tok = _T("쾍9");
		nSTL::replace(src, tok, new_tok);
		jTEST_CHECK(src == _T("asdf1234학교쾍9234학교쾍92"));


		{
			tstring src = _T("asdf1234학교종1234학교종12");
			tstring tok = _T("종1");
			tstring new_tok = _T("쾍9퐦12389");
			nSTL::replace(src, tok, new_tok);
			jTEST_CHECK(src == _T("asdf1234학교쾍9퐦12389234학교쾍9퐦123892"));
		}
	}
	jTEST(string_trim)
	{
		tstring org= _T("\t \n	\r  asdf234k  \t \n	\r  ");
		tstring test= org;
		jTEST_CHECK( nSTL::trim_left(test)  == _T("asdf234k  \t \n	\r  "));

		test= org;
		jTEST_CHECK( nSTL::trim_right(test)  == _T("\t \n	\r  asdf234k"));

		test= org;
		jTEST_CHECK( nSTL::trim(test)  == _T("asdf234k"));

	}

	jTEST_SUITE_END( nSTL_test)

}

