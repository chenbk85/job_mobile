// KString.h: interface of the KString class.
//
//////////////////////////////////////////////////////////////////////
//////////			Created by		:	Hadi Dayvary		//////////
//////////			Email			:	hdayvary@yahoo.com	//////////
//////////			Creation Date	:	2005/6/17			//////////
//////////			Last Update		:	2006/9/5			//////////
//////////			Description		:	String class		//////////
//////////////////////////////////////////////////////////////////////
#pragma once

#include "stdafx.h"

class KString
{
public:
// - Constructions:
	KString(void);										// - Default constructor
	KString(const LPCTSTR lpszStr);						// - Constructor
	KString(const KString &sStr);						// - Copy constructor

// - Destruction
	~KString(void);										// - Destructor

// - Operators Overloading
	KString& operator =(const KString &sStr);			// - Operator = overloading for KString
	KString& operator =(LPCTSTR lpszStr);				// - Operator = overloading for string
	KString& operator =(const int iNum);				// - Operator = overloading for int
	KString& operator =(const double fNum);				// - Operator = overloading for double
	KString  operator +(const KString &sStr);			// - Operator + overloading : KString + KString
	KString  operator +(LPCTSTR lpszStr);				// - Operator + overloading : KString + LPCTSTR
	KString  operator +(int iNum);						// - Operator + overloading : KString + int
	KString  operator +(double fNum);					// - Operator + overloading : KString + double
	KString& operator+=(const KString &sStr);			// - Operator +=overloading for KString
	KString& operator+=(LPCTSTR lpszStr);				// - Operator +=overloading for LPCTSTR

// - Operations
	BOOL operator <(const KString &sStr);				// - Operator < overloading
	BOOL operator <=(const KString &sStr);				// - Operator <= overloading
	BOOL operator >(const KString &sStr);				// - Operator > overloading
	BOOL operator >=(const KString &sStr);				// - Operator >= overloading
	BOOL operator==(const KString &sStr);				// - Operator ==overloading for KString
	BOOL operator==(LPCTSTR sStr);						// - Operator ==overloading for LPCTSTR
	BOOL operator!=(const KString &sStr);				// - Operator !=overloading for KString
	BOOL operator!=(LPCTSTR sStr);						// - Operator !=overloading for LPCTSTR
	KString& operator--();								// - Operator prefix  -- overloading
	KString  operator--(int);							// - Operator postfix -- overloading

	operator LPTSTR(){return m_sString;}				// - LPTSTR type cast

	TCHAR		GetAt(int iPos);						// - Returns TCHAR in specified position
	int			Find(TCHAR ch);							// - Finds first position of specified TCHAR
	int			Find(const KString &sStr);				// - Finds first position of specified KString
	int			Find(LPCTSTR lpszStr);					// - Finds first position of specified string
	int			Replace(TCHAR cOld, TCHAR cNew);		// - Replace an old TCHAR with a new TCHAR
	int			Replace(LPCTSTR sOld, LPCTSTR sNew);	// - Replace an old string with a new string
	int			Replace(const KString &sOld, const KString &sNew);// - Replace an old KString with a new KString
	KString		Mid(int iStart, int iCount);			// - Returns iCount TCHARs from iStart
	KString		Mid(int iStart);						// - Returns TCHARs from nStart till the end
	KString		Left(int iCount);						// - Returns iCount left TCHARs
	KString		Right(int iCount);						// - Returns iCount right TCHARs
	BOOL		Remove(int iPos);						// - Removes a TCHAR in specified position
	int			Remove(int iStart, int iEnd);			// - Removes TCHARs from nStart to nEnd
	int			Remove(TCHAR ch);						// - Removes all ch TCHAR
	BOOL		Remove(const KString &sStr);			// - Removes all specified string
	KString&	TrimLeft(TCHAR ch = ' ');				// - Trims left specified TCHAR
	KString&	TrimRight(TCHAR ch = ' ');				// - Trims right specified TCHAR
	KString&	Trim(TCHAR ch = ' ');					// - Trims left and right specified TCHAR
	KString&	Insert(const KString &sStr, int iPos);	// - Inserts a string in specified position
	KString&	Append(const KString &sStr){return *this += sStr;};// - Appends a string
	KString&	MakeUpper();							// - Converts to upper case
	KString&	MakeLower();							// - Converts to lower case
	KString&	MakeReverse();							// - Reverses the string
	KString		GetUpper();								// - Returns uppercase of string
	KString		GetLower();								// - Returns lowercase of string
	KString		GetReverse();							// - Returns reverse of string
	void		Empty();								// - Clears the string

	int			GetLength(){return m_iLength;}			// - Return length of the string
	int			GetSize(){return m_iLength*sizeof(TCHAR);}// - Return size of the string
	BOOL		IsEmpty(){return m_iLength ? FALSE : TRUE;}// - return TRUE if the string is empty

	LPTSTR		GetBuffer(int iBuffSize);				// - Creates a sized buffer
	void		FreeExtra();							// - Frees extra space

	void		Format(LPCTSTR pszCharSet, ...);		// - Format string

	int			ToInteger(){return _tstoi(m_sString);}	// - Converts the string to integer and returns it
	long		ToLong(){return _tstol(m_sString);}		// - Converts the string to long and returns it
	float		ToFloat(){return (float)_tstof(m_sString);}// - Converts the string to float and returns it
	double		ToDouble(){return _tstof(m_sString);}	// - Converts the string to double and returns it

private:// - Data Members
	LPTSTR		m_sString;								// - Holds the string data
	int			m_iLength;								// - Holds the string length
};