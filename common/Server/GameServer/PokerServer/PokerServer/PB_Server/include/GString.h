//
// GString.h
//

#if !defined(DEF_LINUX)
#include <windows.h>
#endif

#include <string>
#include <functional>

using namespace std;

#ifndef GSTRING_H
#define GSTRING_H

typedef string::size_type strsize;
typedef string::size_type strpos;
typedef wstring::size_type wstrsize;
typedef wstring::size_type wstrpos;

#ifdef UNICODE
typedef wstring tstring;
#else
typedef string tstring;
#endif

#ifndef NPOS
#define NPOS (string::npos)
#endif
#ifndef WNPOS
#define WNPOS (wstring::npos)
#endif
#ifndef GNPOS
#define GNPOS (GString::npos)
#endif

class astring
{
public:
	astring() : m_ptr(_alloc(0)) { }
	astring(const astring& s) : m_ptr(_alloc(s.capacity())) { assign(s.c_str()); }
	explicit astring(LPCSTR sz) : m_ptr(_alloc(_length(sz))) { assign(sz); }
	astring(LPCSTR sz, UINT len) : m_ptr(_alloc(len)) { assign(sz, len); }
	~astring() { _free(m_ptr); }

	astring& assign(LPCSTR sz) { UINT len = _length(sz); return assign(sz, len); }
	astring& assign(LPCSTR sz, UINT len) { resize(len); _copy(m_ptr, sz, len); return *this; }
	astring& operator=(const astring& s) { return assign(s.c_str()); }
	astring& operator=(LPCSTR sz) { return assign(sz); }

	operator LPCSTR () const { return m_ptr; }
	operator LPSTR () { return m_ptr; }

	LPCSTR c_str() const { return m_ptr; }
	LPSTR str() { return m_ptr; }
	bool empty() const { return(m_ptr[0] == 0); }
	UINT size() const { return _length(m_ptr); }
	UINT length() const { return _length(m_ptr); }
	UINT capacity() const { return _capacity(m_ptr); }
	void erase() { m_ptr[0] = 0; }
	void resize(UINT cap) { 
		if(capacity() >= cap) return; 
		LPSTR p = _alloc(cap); 
		_copy(p, m_ptr, length()); 
		_free(m_ptr); 
		m_ptr = p; 
	}

	const CHAR& operator[](UINT pos) const { return m_ptr[pos]; }
	CHAR& operator[](UINT pos) { return m_ptr[pos]; }
	const CHAR& at(UINT pos) const { return m_ptr[pos]; }
	CHAR& at(UINT pos) { return m_ptr[pos]; }

	astring& append(LPCSTR sz) 
	{
		UINT addlen = _length(sz);
		UINT len = length();
		resize(len + addlen);
		_copy(m_ptr + len, sz, addlen); 
		return *this;
	}
	astring& operator+=(LPCSTR sz) { return append(sz); }
	astring operator+(LPCSTR sz) const { astring a(m_ptr); return a.append(sz); }

	int compare(const astring& a)
	{
		return _compare(m_ptr, a.m_ptr);
	}
	bool operator<(const astring& a)
	{
		return(compare(a) < 0);
	}
	bool operator==(const astring& a)
	{
		return(compare(a) == 0);
	}
protected:
	static LPSTR _alloc(UINT cap)
	{
		cap = ((cap/256 + 1) * 256) - 1;
		UINT size = sizeof(CHAR) * (cap + 1);
		void* p = malloc(size + sizeof(DWORD));
		*(DWORD*)p = cap;
		*(LPSTR)((DWORD*)p + 1) = 0;
		return (LPSTR)((DWORD*)p + 1);	
	}
	static void _free(LPSTR pstr)
	{
		free((DWORD*)pstr - 1);
	}
	static UINT _capacity(LPCSTR pstr)
	{
		return *((DWORD*)pstr - 1);
	}
	static void _copy(LPSTR d, LPCSTR s, UINT n)
	{
		memcpy(d, s, sizeof(CHAR) * n);
		d[n] = 0;
	}
	static UINT _length(LPCSTR pstr)
	{
        UINT i;
		for(i = 0; pstr[i]; ++i); return i; 
	}
	static int _compare(LPCSTR a, LPCSTR b)
	{
		return strcmp(a, b);
	}
protected:
	CHAR* m_ptr;
};

#define _TXT(txt) ((txt).c_str())

///////////////////////////////////////////////////////////////////////////////
// Format-string

string vformat(LPCSTR fmt, va_list vl);
wstring vformat(LPCWSTR fmt, va_list vl);
string format(LPCSTR fmt, ...);
wstring format(LPCWSTR fmt, ...);

///////////////////////////////////////////////////////////////////////////////
// string Utils

string& tolower(string& str);
string& toupper(string& str);
string& trimleft(string& str);
string& trimright(string& str);
string& trim(string& str);
int strcmp(const string& a, const string& b);
int stricmp(const string& a, const string& b);
int strncmp( const string& a, const string& b, strsize n );
int strnicmp( const string& a, const string& b, strsize n );
bool strless( const string& a, const string& b);
bool striless( const string& a, const string& b);
bool strabbrless(const string& a, const string& b);
bool striabbrless(const string& a, const string& b);

///////////////////////////////////////////////////////////////////////////////
// wstring Utils

wstring& tolower(wstring& str);
wstring& toupper(wstring& str);
wstring& trimleft(wstring& str);
wstring& trimright(wstring& str);
int strcmp(const wstring& a, const wstring& b);
int stricmp(const wstring& a, const wstring& b);
int strncmp( const wstring& a, const wstring& b, strsize n );
int strnicmp( const wstring& a, const wstring& b, strsize n );
bool strless( const wstring& a, const wstring& b);
bool striless( const wstring& a, const wstring& b);
bool striabbrless(const wstring& a, const wstring& b);

///////////////////////////////////////////////////////////////////////////////
// string/wstring Utils

wstring str2wstr(const string& str);
string wstr2str(const wstring& str);

#ifdef UNICODE
#define str2tstr(str)	str2wstr(str)
#define tstr2str(str)	wstr2str(str)
#define wstr2tstr(str)	str
#define tstr2wstr(str)	str
#else
#define str2tstr(str)	str
#define tstr2str(str)	str
#define wstr2tstr(str)	wstr2str(str)
#define tstr2wstr(str)	str2wstr(str)
#endif

inline BOOL str2wstr(wstring& wstr, string str)
{
	wstr = str2wstr(str);
	return TRUE;
}

inline BOOL wstr2str(string& str, wstring wstr)
{
	str = wstr2str(wstr);
	return TRUE;
}

#ifdef UNICODE
#define _TSTR(s) str2tstr(s)
#else
#define _TSTR(s) s
#endif

///////////////////////////////////////////////////////////////////////////////
// Predicates
struct StrILess : public std::binary_function<string, string, bool> 
{
	bool operator()(const string& a, const string& b) const 
	{
		return striless(a, b);
	}
};

struct StrLess : public std::binary_function<string, string, bool> 
{
	bool operator()(const string& a, const string& b) const 
	{
		return strless(a, b);
	}
};
struct WStrILess : public std::binary_function<wstring, wstring, bool> 
{
	bool operator()(const wstring& a, const wstring& b) const 
	{
		return striless(a, b);
	}
};

struct WStrLess : public std::binary_function<wstring, wstring, bool> 
{
	bool operator()(const wstring& a, const wstring& b) const 
	{
		return strless(a, b);
	}
};

#endif //!TSTRING_H
