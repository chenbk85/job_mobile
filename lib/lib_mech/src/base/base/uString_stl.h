/* file : uString_stl.h
Coder : by icandoit (mech12@nate.com)
Date : 2006-10-25 14:28:36
title : 
desc : 

*/

#ifndef __uString_stl_header__
#define __uString_stl_header__
#pragma once

#include <fstream>
#include <iostream>

namespace nMech
{

	using namespace std;
	namespace nSTL
	{
		inline std::tstring trim_right(const std::tstring& source, const std::tstring& whitespaces=_T(" \t\r\n"))
		{
			std::tstring str = source;
			return str.erase(str.find_last_not_of(whitespaces) + 1);
		}

		inline std::tstring trim_left(const std::tstring& source, const std::tstring& whitespaces=_T(" \t\r\n"))
		{
			std::tstring str = source;
			return str.erase(0, str.find_first_not_of(whitespaces));
		}
#if 0
		inline std::tstring trim(const std::tstring& source, const std::tstring& whitespaces=_T(" \t\r\n"))
		{
			std::tstring str = source;
			return trim_left(trim_right(source, whitespaces), whitespaces);
		}
#else
		inline std::tstring trim(const std::tstring& str, const std::tstring& whitespaces=_T(" \t\r\n"))
		{
			size_t begin = str.find_first_not_of(whitespaces);
			size_t end = str.find_last_not_of(whitespaces);

			if (begin == std::tstring::npos)
			{
				if (end == std::tstring::npos)
					return std::tstring(_T(""));
				else
					begin = 0;
			}
			else if (end == std::tstring::npos)
			{
				end = str.size();
			}

			return str.substr(begin , end - begin + 1);
		}
#endif

		inline void trim_string(tstring& s)
		{
			s =nMech::nSTL::trim(s);
		}


		/////////////////////////////////////////////////////////////////////////////
		/// \brief 주어진 문자열 내에 존재하는 문자열을 다른 문자열로 치환한다.
		/// \param text 원본 문자열
		/// \param find_token 찾고자 하는 문자열
		/// \param replace_token 치환하고자 하는 문자열
		//////////////////////////////////////////////////////////////////////////////
		inline void replace(std::tstring& text, const std::tstring& find_token, const std::tstring& replace_token)
		{
			size_t i = 0;
			while ((i = text.find(find_token)) != std::tstring::npos)
				text.replace(i, find_token.size(), replace_token);
		}

		//////////////////////////////////////////////////////////////////////////////
		/// \brief 문장 내부에 연속적인 대상 문자를 하나로 만든다.
		///
		/// 즉 target을 ' '로 준 경우, 두 개 이상의 ' '를 하나의 ' '로 만든다.
		/// 
		/// \param text 원본 문자열
		/// \param target 대상이 되는 글자
		/// \return string 변환한 문자열
		//////////////////////////////////////////////////////////////////////////////
		inline std::tstring squeeze(const std::tstring& text, TCHAR target)
		{
			std::tstring str = text;
			replace(str, std::tstring(2, target), std::tstring(1, target));
			return str;
		}

		std::wstring mbs_to_wcs(std::string const& str, std::locale const& loc = std::locale());
		std::string 	wcs_to_mbs(std::wstring const& str, std::locale const& loc = std::locale());


	}// namespace jString_stl
}//namespace nMech

#endif // __uString_stl_header__
