/* file : string_util.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2009-12-28 20:22:30
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __string_util_header__
#define __string_util_header__
#pragma once

namespace nMech
{
	namespace nString
	{
		// returns the decimal string representation of the given int
		inline cstr ToString (int nNumber, name1024_t buf)
		{
			char szNumber[16];
			//	itoa (nNumber, szNumber, 10);
			jt_sprintf (szNumber, _T("%d"), nNumber);
			return szNumber;
		}

		// returns hexadecimal string representation of the given dword
		inline cstr ToHexString(DWORD dwNumber,name1024_t buf)
		{
			char szNumber[24];
			jt_sprintf (szNumber, _T("0x%X"), dwNumber);
			return szNumber;
		}
	}

}//namespace nMech

#endif // __string_util_header__
