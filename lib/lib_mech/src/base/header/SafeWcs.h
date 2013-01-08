//////////////////////////////////////////////////////////////////////////
// Safe Wide-Char String class
// Author: Chunmin Ahn (emocreator@gmail.com)
// Version: 1.00
// History: 
//  2008-07: Initial work
//  2008-08: Fixed some bug and add ReplaceOnce()
//

#pragma once


namespace nMech
{


inline int w_ConvertUTF8(const WCHAR* Src, int nSrcLen, CHAR* Dst, int nDstLen)
{
	return WideCharToMultiByte(CP_UTF8, 0, Src, nSrcLen, Dst, nDstLen, NULL, NULL);
}

inline int w_ConvertOEM(const WCHAR* Src, int nSrcLen, CHAR* Dst, int nDstLen)
{
	return WideCharToMultiByte(CP_OEMCP, 0, Src, nSrcLen, Dst, nDstLen, NULL, NULL);
}

inline int w_ConvertFromUTF8(const CHAR* Src, int nSrcLen, WCHAR* Dst, int nDstLen)
{
	return MultiByteToWideChar(CP_UTF8, 0, Src, nSrcLen, Dst, nDstLen);
}

inline int w_ConvertFromOEM(const CHAR* Src, int nSrcLen, WCHAR* Dst, int nDstLen)
{
	return MultiByteToWideChar(CP_OEMCP, 0, Src, nSrcLen, Dst, nDstLen);
}


// Wide Char String

template <size_t T>
struct SafeWcs
{
public:
	WCHAR _s[T+1];

	SafeWcs()
	{
		Clear();
	}

	SafeWcs(const WCHAR* str)
	{
		lstrcpynW(_s, str, T+1);
		//_s[T] = 0;
	}

	SafeWcs& operator=(const SafeWcs& str)
	{
		lstrcpynW(_s, str._s, T+1);
		//_s[T] = 0;
		return *this;
	}

	SafeWcs& operator=(const WCHAR* str)
	{
		lstrcpynW(_s, str, T+1);
		//_s[T] = 0;
		return *this;
	}

	SafeWcs& operator=(WCHAR c)
	{
		if (T > 0)
		{
			_s[0] = c;
			_s[1] = NULL;
		}
		return *this;
	}

	SafeWcs& operator+=(const SafeWcs& str)
	{
		int nSrcLen = lstrlenW(_s);
		int nDstLen = lstrlenW(str._s);
		lstrcpynW(_s+nSrcLen, str._s, T+1-nSrcLen);
		//_s[T] = 0;
		return *this;
	}

	SafeWcs& operator+=(const WCHAR* str)
	{
		int nSrcLen = lstrlenW(_s);
		int nDstLen = lstrlenW(str);
		lstrcpynW(_s+nSrcLen, str, T+1-nSrcLen);
		//_s[T] = 0;
		return *this;
	}

	SafeWcs& operator+=(WCHAR c)
	{
		int nLen = Len();
		if (nLen < T)
		{
			_s[nLen] = c;
			_s[nLen+1] = NULL;
		}
		return *this;
	}

	bool operator==(const SafeWcs& str) const
	{
		return (wcscmp(_s, str._s) == 0);
	}

	bool operator==(const WCHAR* str) const
	{
		return (wcscmp(_s, str) == 0);
	}

	bool operator!=(const SafeWcs& str) const
	{
		return (wcscmp(_s, str._s) != 0);
	}

	bool operator!=(const WCHAR* str) const
	{
		return (wcscmp(_s, str) != 0);
	}

	bool operator<(const SafeWcs& str) const
	{
		return (wcscmp(_s, str._s) < 0);
	}

	bool operator<(const WCHAR* str) const
	{
		return (wcscmp(_s, str) < 0);
	}

	bool operator<=(const SafeWcs& str) const
	{
		return (wcscmp(_s, str._s) <= 0);
	}

	bool operator<=(const WCHAR* str) const
	{
		return (wcscmp(_s, str) <= 0);
	}

	bool operator>(const SafeWcs& str) const
	{
		return (wcscmp(_s, str._s) > 0);
	}

	bool operator>(const WCHAR* str) const
	{
		return (wcscmp(_s, str) > 0);
	}

	bool operator>=(const SafeWcs& str) const
	{
		return (wcscmp(_s, str._s) >= 0);
	}

	bool operator>=(const WCHAR* str) const
	{
		return (wcscmp(_s, str) >= 0);
	}

	const WCHAR& operator[](size_t idx) const
	{
		return _s[idx];
	}

	WCHAR& operator[](size_t idx)
	{
		return _s[idx];
	}

	int Find(WCHAR c) const
	{
		const WCHAR* p = wcschr(_s, c);
		return (int)(p == NULL ? -1: p - _s);
	}

	int Find(const WCHAR* str) const
	{
		const WCHAR* p = wcsstr(_s, str);
		return (int)(p == NULL ? -1: p - _s);
	}

	int Find(WCHAR c, int istart) const
	{
		if (istart < 0 || istart >= T) return -1;
		WCHAR* p = wcschr(_s+istart, c);
		return (int)(p == NULL ? -1: p - _s);
	}

	int Find(const WCHAR* str, int istart) const
	{
		if (istart < 0 || istart >= T) return -1;
		WCHAR* p = wcsstr(_s+istart, str);
		return (int)(p == NULL ? -1: p - _s);
	}

	int _Find(const WCHAR* src, const WCHAR* s) const
	{
		const WCHAR* pos = wcsstr(src, s);
		return (int)(pos ? pos-src: -1);
	}

	int ReverseFind(WCHAR c) const
	{
		const WCHAR* p = wcsrchr(_s, c);
		return (int)(p == NULL ? -1: p - _s);
	}

	int Replace(const WCHAR* src, const WCHAR* dst)
	{
		return Replace(src, dst, (dst ? lstrlenW(dst): 0));
	}

	int Replace(const WCHAR* src, const WCHAR* dst, int dstLen)
	{
		if (src == NULL)
			return 0;

		dst = (dst ? dst: L"");
		if (dstLen < 0)
			dstLen = lstrlenW(dst);

		int count = 0;
		int srcLen = lstrlenW(src);
		int _len = Len();

		int n = 0;
		int p = 0;
		int l = dstLen-srcLen;

		while (min(_len+l, T) != T && (n= _Find(_s+p, src)) != -1) {
			p += n;
			if (srcLen != dstLen)
				memmove(_s+p+dstLen, _s+p+srcLen, _len-(p+srcLen)+1);
			memcpy(_s+p, dst, dstLen);
			_len += l;
			count++;
		}

		return count;
	}

	int ReplaceOnce(const WCHAR* src, const WCHAR* dst)
	{
		return ReplaceOnce(src, dst, (dst ? lstrlenW(dst): 0));
	}

	int ReplaceOnce(const WCHAR* src, const WCHAR* dst, int dstLen)
	{
		if (src == NULL)
			return 0;

		dst = (dst ? dst: L"");
		if (dstLen < 0)
			dstLen = lstrlenW(dst);

		int count = 0;
		int srcLen = lstrlenW(src);
		int _len = Len();

		int n = 0;
		int p = 0;
		int l = dstLen-srcLen;

		if (min(_len+l, T) != T && (n= _Find(_s+p, src)) != -1) {
			p += n;
			if (srcLen != dstLen)
				memmove(_s+p+dstLen, _s+p+srcLen, (_len-(p+srcLen)+1) * sizeof(WCHAR));
			memcpy(_s+p, dst, dstLen * sizeof(WCHAR));
			_len += l;
			count++;
		}

		return count;
	}

	int Insert(int idx, WCHAR c)
	{
		int _len = Len();
		idx = min(idx, _len);

		if (_len < (T-1))
		{
			memmove(_s+idx+1, _s+idx, (_len+idx+1) * sizeof(WCHAR));
			_s[idx] = c;
			_len++;
		}
		return _len;
	}

	int Insert(int idx, const WCHAR* str)
	{
		if (str == NULL)
			return 0;

		str = (str ? str: L"");
		int srcLen = lstrlenW(str);
		int _len = Len();
		idx = min(idx, _len);

		srcLen = min((int)T - _len, srcLen);
		if (srcLen > 0)
		{
			memmove(_s+idx+srcLen, _s+idx, (_len-idx+1) * sizeof(WCHAR));
			memcpy(_s+idx, str, srcLen * sizeof(WCHAR));
			_len += srcLen;
		}
		return _len;
	}

	int Format(const WCHAR* fmt, ...)
	{
		va_list v;
		va_start(v, fmt);
		int nLen = FormatV(fmt, v);
		va_end(v);
		return nLen;
	}

	int FormatV(const WCHAR* fmt, va_list args)
	{
		int nLen = _vsnwprintf(_s, T, fmt, args);
		if (nLen == -1)
			nLen = T;
		return nLen;
	}

	void Assign(const CHAR* str, int len)
	{
		int strLen = MultiByteToWideChar(CP_OEMCP, 0, str, len, _s, MaxLen());
		_s[strLen] = 0;
	}

	void Assign(const WCHAR* str, int len)
	{
		if (len >= T)
			len = T;
		lstrcpynW(_s, str, len+1);
		//_s[len+1] = 0;
	}

	void AssignUtf8(const CHAR* str, int len = -1)
	{
		int bufLen = MultiByteToWideChar(CP_UTF8, 0, str, len, _s, MaxLen());
		_s[bufLen] = 0;
	}

	void ToUnicode(WCHAR* str, int maxLen) const
	{
		lstrcpynW(_s, str, maxLen);
	}

	void ToAnsi(CHAR* str, int maxLen) const
	{
		WideCharToMultiByte(CP_OEMCP, 0, _s, -1, str, maxLen, NULL, NULL);
	}

	void ToUtf8(CHAR* str, int maxLen) const
	{
		WideCharToMultiByte(CP_UTF8, 0, _s, -1, str, maxLen, NULL, NULL);
	}

	void Clear()
	{
		_s[0] = 0;
		_s[T] = 0;
	}

	bool IsNull() const
	{
		return *_s == 0;
	}

	bool IsNotNull() const
	{
		return *_s != 0;
	}

	int Len() const
	{
		return lstrlenW(_s);
	}

	int MaxLen() const
	{
		return T+1;
	}
};


#define SAFE_NAME_WLEN	24
#define SAFE_PATH_WLEN	MAX_PATH
#define SAFE_MSG_WLEN	1024

typedef SafeWcs<SAFE_NAME_WLEN>	wSafeName;
typedef SafeWcs<SAFE_PATH_WLEN>	wSafePath;
typedef SafeWcs<SAFE_MSG_WLEN>	wSafeMsg;



#ifdef UNICODE 
#define tSafeStr	SafeWcs
typedef wSafeName	tSafeName;
typedef wSafePath	tSafePath;
typedef wSafeMsg	tSafeMsg;
#endif


}