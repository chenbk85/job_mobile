//////////////////////////////////////////////////////////////////////////
// SafeStr template class
// Author: Chunmin Ahn (emocreator@gmail.com)
// History: 
//  2007-02: Initial work
//  2008-05: Add Insert(), bug fixed Replace()
//

#pragma once

#pragma warning( disable : 4996 )

namespace nMech
{

template <size_t T>
int ConvertUTF8(const CHAR* Src, int nSrcLen, CHAR* Dst, int nDstLen)
{
	WCHAR wbuf[T+1];
	wbuf[T] = 0;

	MultiByteToWideChar(CP_OEMCP, 0, Src, nSrcLen, wbuf, T);
	return WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, Dst, nDstLen, NULL, NULL);
}

template <size_t T>
int ConvertOEM(const CHAR* Src, int nSrcLen, CHAR* Dst, int nDstLen)
{
	WCHAR wbuf[T+1];
	wbuf[T] = 0;

	MultiByteToWideChar(CP_UTF8, 0, Src, nSrcLen, wbuf, T);
	return WideCharToMultiByte(CP_OEMCP, 0, wbuf, -1, Dst, nDstLen, NULL, NULL);
}


template <size_t T>
struct SafeStr
{
public:
	CHAR _s[T+1];

	SafeStr()
	{
		Clear();
	}

	SafeStr(const CHAR* str)
	{
		lstrcpynA(_s, str, T+1);
		//_s[T] = 0;
	}

	SafeStr& operator=(const SafeStr& str)
	{
		lstrcpynA(_s, str._s, T+1);
		//_s[T] = 0;
		return *this;
	}

	SafeStr& operator=(const CHAR* str)
	{
		lstrcpynA(_s, str, T+1);
		//_s[T] = 0;
		return *this;
	}

	SafeStr& operator=(CHAR c)
	{
		if (T > 0)
		{
			_s[0] = c;
			_s[1] = NULL;
		}
		return *this;
	}

	SafeStr& operator+=(const SafeStr& str)
	{
		int nSrcLen = lstrlenA(_s);
		int nDstLen = lstrlenA(str._s);
		lstrcpynA(_s+nSrcLen, str._s, T+1-nSrcLen);
		//_s[T] = 0;
		return *this;
	}

	SafeStr& operator+=(const CHAR* str)
	{
		int nSrcLen = lstrlenA(_s);
		int nDstLen = lstrlenA(str);
		lstrcpynA(_s+nSrcLen, str, T+1-nSrcLen);
		//_s[T] = 0;
		return *this;
	}

	SafeStr& operator+=(CHAR c)
	{
		int nLen = Len();
		if (nLen < T)
		{
			_s[nLen] = c;
			_s[nLen+1] = NULL;
		}
		return *this;
	}

	bool operator==(const SafeStr& str) const
	{
		return (strcmp(_s, str._s) == 0);
	}

	bool operator==(const CHAR* str) const
	{
		return (strcmp(_s, str) == 0);
	}

	bool operator!=(const SafeStr& str) const
	{
		return (strcmp(_s, str._s) != 0);
	}

	bool operator!=(const CHAR* str) const
	{
		return (strcmp(_s, str) != 0);
	}

	bool operator<(const SafeStr& str) const
	{
		return (strcmp(_s, str._s) < 0);
	}

	bool operator<(const CHAR* str) const
	{
		return (strcmp(_s, str) < 0);
	}

	bool operator<=(const SafeStr& str) const
	{
		return (strcmp(_s, str._s) <= 0);
	}

	bool operator<=(const CHAR* str) const
	{
		return (strcmp(_s, str) <= 0);
	}

	bool operator>(const SafeStr& str) const
	{
		return (strcmp(_s, str._s) > 0);
	}

	bool operator>(const CHAR* str) const
	{
		return (strcmp(_s, str) > 0);
	}

	bool operator>=(const SafeStr& str) const
	{
		return (strcmp(_s, str._s) >= 0);
	}

	bool operator>=(const CHAR* str) const
	{
		return (strcmp(_s, str) >= 0);
	}

	const CHAR& operator[](size_t idx) const
	{
		return _s[idx];
	}

	CHAR& operator[](size_t idx)
	{
		return _s[idx];
	}

	int Find(CHAR c) const
	{
		const CHAR* p = (const CHAR*)strchr(_s, c);
		return (int)(p == NULL ? -1: p - _s);
	}

	int Find(const CHAR* str) const
	{
		CHAR* p = strstr(_s, str);
		return (int)(p == NULL ? -1: p - _s);
	}

	int Find(CHAR c, int istart) const
	{
		if (istart < 0 || istart >= T) return -1;
		CHAR* p = strchr(_s+istart, c);
		return (int)(p == NULL ? -1: p - _s);
	}

	int Find(const CHAR* str, int istart) const
	{
		if (istart < 0 || istart >= T) return -1;
		CHAR* p = strstr(_s+istart, str);
		return (int)(p == NULL ? -1: p - _s);
	}

	int _Find(const CHAR* src, const CHAR* s) const
	{
		const CHAR* pos = (const CHAR*)strstr(src, s);
		return (int)(pos ? pos-src: -1);
	}

	int ReverseFind(CHAR c) const
	{
		CHAR* p = strrchr(_s, c);
		return (int)(p == NULL ? -1: p - _s);
	}

	int Replace(const CHAR* src, const CHAR* dst)
	{
		return Replace(src, dst, (dst ? lstrlenA(dst): 0));
	}

	int Replace(const CHAR* src, const CHAR* dst, int dstLen)
	{
		if (src == NULL)
			return 0;

		dst = (dst ? dst: "");
		if (dstLen < 0)
			dstLen = lstrlenA(dst);

		int count = 0;
		int srcLen = lstrlenA(src);
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

	int ReplaceOnce(const CHAR* src, const CHAR* dst)
	{
		return ReplaceOnce(src, dst, (dst ? lstrlenA(dst): 0));
	}

	int ReplaceOnce(const CHAR* src, const CHAR* dst, int dstLen)
	{
		if (src == NULL)
			return 0;

		dst = (dst ? dst: "");
		if (dstLen < 0)
			dstLen = lstrlenA(dst);

		int count = 0;
		int srcLen = lstrlenA(src);
		int _len = Len();

		int n = 0;
		int p = 0;
		int l = dstLen-srcLen;

		if (min(_len+l, T) != T && (n= _Find(_s+p, src)) != -1) {
			p += n;
			if (srcLen != dstLen)
				memmove(_s+p+dstLen, _s+p+srcLen, _len-(p+srcLen)+1);
			memcpy(_s+p, dst, dstLen);
			_len += l;
			count++;
		}

		return count;
	}

	int Insert(int idx, CHAR c)
	{
		int _len = Len();
		idx = min(idx, _len);

		if (_len < (T-1))
		{
			memmove(_s+idx+1, _s+idx, _len+idx+1);
			_s[idx] = c;
			_len++;
		}
		return _len;
	}

	int Insert(int idx, const CHAR* str)
	{
		if (str == NULL)
			return 0;

		str = (str ? str: "");
		int srcLen = lstrlenA(str);
		int _len = Len();
		idx = min(idx, _len);

		srcLen = min((int)T - _len, srcLen);
		if (srcLen > 0)
		{
			memmove(_s+idx+srcLen, _s+idx, _len-idx+1);
			memcpy(_s+idx, str, srcLen);
			_len += srcLen;
		}
		return _len;
	}

	int Format(const CHAR* fmt, ...)
	{
		va_list v;
		va_start(v, fmt);
		int nLen = FormatV(fmt, v);
		va_end(v);
		return nLen;
	}
	
	int FormatV(const CHAR* fmt, va_list args)
	{
		int nLen = _vsnprintf(_s, T, fmt, args);
		if (nLen == -1)
			nLen = T;
		return nLen;
	}

	void Assign(const CHAR* str, int len)
	{
		if (len >= T)
			len = T;
		lstrcpynA(_s, str, len+1);
		//_s[len+1] = 0;
	}

	void Assign(const WCHAR* str, int len)
	{
		int strLen = WideCharToMultiByte(CP_OEMCP, 0, str, len, _s, MaxLen(), NULL, NULL);
		_s[strLen] = 0;
	}

	void AssignUtf8(const CHAR* str, int len = -1)
	{
		WCHAR buf[T+1];
		int bufLen = MultiByteToWideChar(CP_UTF8, 0, str, len, buf, T+1);
		buf[bufLen] = 0;

		bufLen = WideCharToMultiByte(CP_OEMCP, 0, buf, -1, _s, MaxLen(), NULL, NULL);
		_s[bufLen] = 0;
	}

	void ToUnicode(WCHAR* str, int maxLen) const
	{
		MultiByteToWideChar(CP_OEMCP, 0, _s, -1, str, maxLen);
	}

	void ToAnsi(CHAR* str, int maxLen) const
	{
		lstrcpynA(str, _s, maxLen);
	}

	void ToUtf8(CHAR* str, int maxLen) const
	{
		WCHAR buf[T+1];
		MultiByteToWideChar(CP_OEMCP, 0, _s, -1, buf, T+1);
		WideCharToMultiByte(CP_UTF8, 0, buf, -1, str, maxLen, NULL, NULL);
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
		return lstrlenA(_s);
	}

	int MaxLen() const
	{
		return T+1;
	}
};


#define SAFE_NAME_LEN	24
#define SAFE_PATH_LEN	MAX_PATH
#define SAFE_MSG_LEN	1024

typedef SafeStr<SAFE_NAME_LEN>	aSafeName;
typedef SafeStr<SAFE_PATH_LEN>	aSafePath;
typedef SafeStr<SAFE_MSG_LEN>	aSafeMsg;

#ifndef UNICODE 
#define tSafeStr	SafeStr
typedef aSafeName	tSafeName;
typedef aSafePath	tSafePath;
typedef aSafeMsg	tSafeMsg;
#endif

}
