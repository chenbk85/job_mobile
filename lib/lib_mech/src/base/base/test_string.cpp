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

		astring astr = "asdfasdf�б���1234!@#$";
		wstring wstr = L"asdfasdf�б���1234!@#$";
		wstring testW = nUNI::mbs_to_wcs(astr);
		jTEST_CHECK(testW == wstr);

		astring testA = nUNI::wcs_to_mbs(wstr);
		jTEST_CHECK(testA == astr);

	}

	jTEST(string_replace)
	{
		tstring src = _T("asdf1234�б���1234�б���12");
		tstring tok = _T("��1");
		tstring new_tok = _T("�Z9");
		nSTL::replace(src, tok, new_tok);
		jTEST_CHECK(src == _T("asdf1234�б��Z9234�б��Z92"));


		{
			tstring src = _T("asdf1234�б���1234�б���12");
			tstring tok = _T("��1");
			tstring new_tok = _T("�Z9��12389");
			nSTL::replace(src, tok, new_tok);
			jTEST_CHECK(src == _T("asdf1234�б��Z9��12389234�б��Z9��123892"));
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

