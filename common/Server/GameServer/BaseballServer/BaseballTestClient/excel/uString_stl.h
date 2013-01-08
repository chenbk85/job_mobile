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
		inline std::tstring &trim_right(std::tstring& source, const std::tstring& whitespaces=_T(" \t\r\n"))
		{
			source = source.erase(source.find_last_not_of(whitespaces) + 1);
			return source;
		}

		inline std::tstring &trim_left(std::tstring& source, const std::tstring& whitespaces=_T(" \t\r\n"))
		{
			source =source.erase(0, source.find_first_not_of(whitespaces));
			return source;
		}
		inline std::wstring &trim(std::wstring& str, const std::wstring& whitespaces=L" \t\r\n")
		{
			size_t begin = str.find_first_not_of(whitespaces);
			size_t end = str.find_last_not_of(whitespaces);

			if (begin == wstring::npos)
			{
				if (end == wstring::npos)
				{
					str = L"";
					return str;
				}
				else
					begin = 0;
			}
			else if (end == wstring::npos)
			{
				end = str.size();
			}

			str = str.substr(begin , end - begin + 1);
			return str;
		}
		inline std::astring &trim(std::astring& str, const std::astring& whitespaces=" \t\r\n")
		{
			size_t begin = str.find_first_not_of(whitespaces);
			size_t end = str.find_last_not_of(whitespaces);

			if (begin == astring::npos)
			{
				if (end == astring::npos)
				{
					str = "";
					return str;
				}
				else
					begin = 0;
			}
			else if (end == astring::npos)
			{
				end = str.size();
			}

			str = str.substr(begin , end - begin + 1);
			return str;
		}

		/////////////////////////////////////////////////////////////////////////////
		/// \brief 주어진 문자열 내에 존재하는 문자열을 다른 문자열로 치환한다.
		/// \param text 원본 문자열
		/// \param find_token 찾고자 하는 문자열
		/// \param replace_token 치환하고자 하는 문자열
		//////////////////////////////////////////////////////////////////////////////
		inline std::tstring& replace(std::tstring& text, const std::tstring& find_token, const std::tstring& replace_token)
		{
			if(find_token == replace_token)
				return text;
			size_t i = 0;
			while ((i = text.find(find_token)) != tstring::npos)
				text.replace(i, find_token.size(), replace_token);
			return text;
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
		inline std::tstring& squeeze(std::tstring& text, TCHAR target)
		{
			return replace(text, std::tstring(2, target), std::tstring(1, target));
		}



	}// namespace jString_stl

	namespace nString
	{
		inline void jSplit_Str(const std::tstring &in , const std::tstring sep, std::vector<std::tstring>& out)
		{
			out.clear();
			size_t iCurr=0;
			tstring str ;
			for(; ; )
			{
				size_t iNow =in.find(sep,iCurr);
				if(iNow == tstring::npos)
				{
					if( iCurr < in.size())
					{
						str = in.substr(iCurr);
						nSTL::trim(str);
						out.push_back(str);
					}
					break;
				}

				str =in.substr(iCurr,iNow-iCurr);
				nSTL::trim(str);
				out.push_back(str);
				iCurr=iNow+ sep.size();
			}
		}

	}
}//namespace nMech

#endif // __uString_stl_header__
