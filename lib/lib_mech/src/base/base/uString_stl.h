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
		/// \brief �־��� ���ڿ� ���� �����ϴ� ���ڿ��� �ٸ� ���ڿ��� ġȯ�Ѵ�.
		/// \param text ���� ���ڿ�
		/// \param find_token ã���� �ϴ� ���ڿ�
		/// \param replace_token ġȯ�ϰ��� �ϴ� ���ڿ�
		//////////////////////////////////////////////////////////////////////////////
		inline void replace(std::tstring& text, const std::tstring& find_token, const std::tstring& replace_token)
		{
			size_t i = 0;
			while ((i = text.find(find_token)) != std::tstring::npos)
				text.replace(i, find_token.size(), replace_token);
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
