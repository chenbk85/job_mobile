#ifndef NOCASEPRED_H
#define NOCASEPRED_H

#include <functional>

_STD_BEGIN
		// case insensitive predicate
template<class _Ty> struct equal_to_no_case :
	binary_function<_Ty, _Ty, bool>
{
	inline bool operator () (const _Ty &_X, const _Ty &_Y) const
	{
		// ::CharLower is a strange function.  You can pass TCHARs
		// but you must cast to a pointer.  See the VC++ help for more info.
#ifdef _UNICODE
		// a wchar_t is unsigned, so no additional cast required
		return (::CharLower ((LPTSTR) _X) == ::CharLower ((LPTSTR) _Y));
#else
		// TCHAR resolves to char in ANSI build.  This leads to a negative
		// number if the char is > 127.  A cast is needed to prevent
		// the high word of the LPTSTR being 0xffff.
		return (::CharLower ((LPTSTR) (unsigned char) _X) ==
			::CharLower ((LPTSTR) (unsigned char) _Y));
#endif
	}
};
_STD_END

#endif
