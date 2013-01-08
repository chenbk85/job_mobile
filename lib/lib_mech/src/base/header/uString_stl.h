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
#if 0
		inline std::tstring trim(const std::tstring& source, const std::tstring& whitespaces=_T(" \t\r\n"))
		{
			tstring str = source;
			return trim_left(trim_right(source, whitespaces), whitespaces);
		}
#else
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
#endif

		/////////////////////////////////////////////////////////////////////////////
		/// \brief �־��� ���ڿ� ���� �����ϴ� ���ڿ��� �ٸ� ���ڿ��� ġȯ�Ѵ�.
		/// \param text ���� ���ڿ�
		/// \param find_token ã���� �ϴ� ���ڿ�
		/// \param replace_token ġȯ�ϰ��� �ϴ� ���ڿ�
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
		/// \brief ���� ���ο� �������� ��� ���ڸ� �ϳ��� �����.
		///
		/// �� target�� ' '�� �� ���, �� �� �̻��� ' '�� �ϳ��� ' '�� �����.
		/// 
		/// \param text ���� ���ڿ�
		/// \param target ����� �Ǵ� ����
		/// \return string ��ȯ�� ���ڿ�
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
