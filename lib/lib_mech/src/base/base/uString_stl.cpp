/* file : uString_stl.cpp
Coder : by icandoit (mech12@nate.com)
Date : 2006-10-25 14:29:12
title : 
desc : 

*/

#include "stdafx.h"
#include "uString_stl.h"

namespace nMech
{
	namespace nSTL
	{
#if 1
		//multi-byte string을 wide-char string으로 변환하는 코드
		//http://cpplog.tistory.com/19http://cpplog.tistory.com/19
		std::wstring mbs_to_wcs(std::string const& str, std::locale const& loc )
		{
			typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
			codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
			std::mbstate_t state = 0;
			std::vector<wchar_t> buf(str.size() + 1);
			char const* in_next = str.c_str();
			wchar_t* out_next = &buf[0];
			codecvt_t::result r = codecvt.in(state, 
				str.c_str(), str.c_str() + str.size(), in_next, 
				&buf[0], &buf[0] + buf.size(), out_next);
			return std::wstring(&buf[0]);
		}

		//wide-char string을 multi-byte string으로 변환하는 코드
		std::string 	wcs_to_mbs(std::wstring const& str, std::locale const& loc)
		{
			typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
			codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
			std::mbstate_t state = 0;
			std::vector<char> buf((str.size() + 1) * codecvt.max_length());
			wchar_t const* in_next = str.c_str();
			char* out_next = &buf[0];
			codecvt_t::result r = codecvt.out(state, 
				str.c_str(), str.c_str() + str.size(), in_next, 
				&buf[0], &buf[0] + buf.size(), out_next);
			return std::string(&buf[0]);
		}

		void TestUnit(jIE*)
		{
			// 전역 locale 설정
			std::locale::global(std::locale(""));

			std::string mbs1 = "abcdef가나다라";
			std::wstring wcs1 = L"abcdef가나다라";
			std::string mbs2 = wcs_to_mbs(wcs1);
			assert(mbs1 == mbs2);
			std::wstring wcs2 = mbs_to_wcs(mbs1);
			assert(wcs1 == wcs2);

		}


#endif
	}//namespace nSTL

}//namespace nMech

