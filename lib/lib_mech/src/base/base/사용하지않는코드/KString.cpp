// KString.cpp: implementation of the KString class.
//
//////////////////////////////////////////////////////////////////////
//////////			Created by		:	Hadi Dayvary		//////////
//////////			Email			:	hdayvary@yahoo.com	//////////
//////////			Creation Date	:	2005/6/17			//////////
//////////			Last Update		:	2006/9/5			//////////
//////////			Description		:	String class		//////////
//////////////////////////////////////////////////////////////////////
#include "KString.h"

//*****************************************************************************
// - Default constructor
//*****************************************************************************
KString::KString(void)
{
	m_sString	= NULL;
	m_iLength	= 0;
}
//*****************************************************************************
// - Constructor
//*****************************************************************************
KString::KString(LPCTSTR lpszStr)
{
	m_iLength	= (int)_tcslen(lpszStr);
	m_sString	= new TCHAR[m_iLength + 1];
	_tcscpy(m_sString, lpszStr);
}
//*****************************************************************************
// - Copy constructor
//*****************************************************************************
KString::KString(const KString &sStr)
{
	m_iLength	= sStr.m_iLength;
	m_sString	= new TCHAR[m_iLength + 1];
	_tcscpy(m_sString, sStr.m_sString);
}
//*****************************************************************************
// - Destructor
//*****************************************************************************
KString::~KString(void)	
{
	if(m_sString)
		delete[] m_sString;

	m_sString = NULL;
}
//*****************************************************************************
// - Operator = overloading for KString
//*****************************************************************************
KString& KString::operator =(const KString &sStr)
{
	if(m_sString)
		delete[] m_sString;

	m_iLength	= sStr.m_iLength;
	m_sString	= new TCHAR[m_iLength + 1];
	_tcscpy(m_sString, sStr.m_sString);

	return *this;
}
//*****************************************************************************
// - Operator = overloading for string
//*****************************************************************************
KString& KString::operator =(LPCTSTR lpszStr)
{
	if(m_sString)
		delete[] m_sString;

	m_iLength	= (int)_tcslen(lpszStr);
	m_sString	= new TCHAR[m_iLength + 1];
	_tcscpy(m_sString, lpszStr);

	return *this;
}
//*****************************************************************************
// - Operator = overloading for int
//*****************************************************************************
KString& KString::operator =(const int iNum)
{
	if(m_sString)
		delete[] m_sString;

	TCHAR	sStr[16];
	_stprintf(sStr, _T("%d"), iNum);

	m_iLength = (int)_tcslen(sStr);
	m_sString = new TCHAR[m_iLength + 1];

	_tcscpy(m_sString, sStr);

	return *this;
}
//*****************************************************************************
// - Operator = overloading for double
//*****************************************************************************
KString& KString::operator =(const double fNum)
{
	if(m_sString)
		delete[] m_sString;

	TCHAR	sStr[16];
	_stprintf(sStr, _T("%f"), fNum);

	m_iLength = (int)_tcslen(sStr);
	m_sString = new TCHAR[m_iLength + 1];

	_tcscpy(m_sString, sStr);

	return *this;
}
//*****************************************************************************
// - Operator + overloading for : KString + KString
//*****************************************************************************
KString KString::operator +(const KString &sStr)
{
	KString	sTemp;

	sTemp.m_iLength = m_iLength + sStr.m_iLength;
	sTemp.m_sString = new TCHAR[sTemp.m_iLength + 1];

	_stprintf(sTemp.m_sString, _T("%s%s"), m_sString, sStr.m_sString);

	return sTemp;
}
//*****************************************************************************
// - Operator + overloading for : KString + LPCTSTR
//*****************************************************************************
KString KString::operator +(LPCTSTR lpszStr)
{
	KString	sTemp;

	sTemp.m_iLength = m_iLength + (int)_tcslen(lpszStr);
	sTemp.m_sString = new TCHAR[sTemp.m_iLength + 1];

	_stprintf(sTemp.m_sString, _T("%s%s"), m_sString, lpszStr);

	return sTemp;
}
//*****************************************************************************
// - Operator + overloading : KString + int
//*****************************************************************************
KString KString::operator +(int iNum)
{
	TCHAR	sStr[16];
	_stprintf(sStr, _T("%d"), iNum);

	return *this + sStr;
}
//*****************************************************************************
// - Operator + overloading : KString + double
//*****************************************************************************
KString KString::operator +(double fNum)
{
	TCHAR	sStr[16];
	_stprintf(sStr, _T("%f"), fNum);

	return *this + sStr;
}
//*****************************************************************************
// - Operator += overloading for KString
//*****************************************************************************
KString& KString::operator +=(const KString &sStr)
{
	if(m_sString)
		return *this = *this + sStr;
	else
		return *this = sStr;
}
//*****************************************************************************
// - Operator += overloading for LPCTSTR
//*****************************************************************************
KString& KString::operator +=(LPCTSTR lpszStr)
{
	if(m_sString)
		return *this = *this + lpszStr;
	else
		return *this = lpszStr;
}
//*****************************************************************************
// - Operator < overloading : return TRUE if specified KString's length is less than
//   this class string's length , otherwise FALSE
//*****************************************************************************
BOOL KString::operator <(const KString &sStr)
{
	if(_tcscmp(m_sString, sStr.m_sString) < 0)
		return TRUE;
	return FALSE;
}
//*****************************************************************************
// - Operator <= overloading : return TRUE if specified KString's length is less than
//   or equal to this class string's length , otherwise FALSE
//*****************************************************************************
BOOL KString::operator <=(const KString &sStr)
{
	if(_tcscmp(m_sString, sStr.m_sString) <= 0)
		return TRUE;
	return FALSE;
}
//*****************************************************************************
// - Operator > overloading : return TRUE if specified KString's length is greater than
//   this class string's length , otherwise FALSE
//*****************************************************************************
BOOL KString::operator >(const KString &sStr)
{
	if(_tcscmp(m_sString, sStr.m_sString) > 0)
		return TRUE;
	return FALSE;
}
//*****************************************************************************
// - Operator >= overloading : return TRUE if specified KString's length is greater than
//   or equal to this class string's length , otherwise FALSE
//*****************************************************************************
BOOL KString::operator >=(const KString &sStr)
{
	if(_tcscmp(m_sString, sStr.m_sString) >= 0)
		return TRUE;
	return FALSE;
}
//*****************************************************************************
// - Operator == overloading : return TRUE if specified KString length is equal to
//   this class string's length , otherwise return FALSE
//*****************************************************************************
BOOL KString::operator ==(const KString &sStr)
{
	if(_tcscmp(m_sString, sStr.m_sString) == 0)
		return TRUE;
	return FALSE;
}
//*****************************************************************************
// - Operator == overloading : return TRUE if specified LPCTSTR length is equal to
//   this class string's length , otherwise return FALSE
//*****************************************************************************
BOOL KString::operator ==(LPCTSTR sStr)
{
	if(_tcscmp(m_sString, sStr) == 0)
		return TRUE;
	return FALSE;
}
//*****************************************************************************
// - Operator != overloading : return TRUE if specified KString length is equal to
//   this class string's length , otherwise return FALSE
//*****************************************************************************
BOOL KString::operator !=(const KString &sStr)
{
	if(_tcscmp(m_sString, sStr.m_sString))
		return TRUE;
	return FALSE;
}
//*****************************************************************************
// - Operator != overloading : return TRUE if specified KString length is equal to
//   this class string's length , otherwise return FALSE
//*****************************************************************************
BOOL KString::operator !=(LPCTSTR sStr)
{
	if(_tcscmp(m_sString, sStr))
		return TRUE;
	return FALSE;
}
//*****************************************************************************
// - Operator postfix -- overloading
//*****************************************************************************
KString& KString::operator--()
{
	Remove(m_iLength - 1);

	return *this;
}
//*****************************************************************************
// - Operator postfix -- overloading
//*****************************************************************************
KString KString::operator--(int)
{
	KString sTemp = *this;
	Remove(m_iLength - 1);

	return sTemp;
}
//*****************************************************************************
// - Returns TCHAR in specified position
//*****************************************************************************
TCHAR KString::GetAt(int iPos)
{
	if(iPos>= 0 && iPos < m_iLength)
		return m_sString[iPos];

	return NULL;
}
//*****************************************************************************
// - Finds position of first specified TCHAR , if did not found return -1
//*****************************************************************************
int KString::Find(TCHAR ch)
{
	TCHAR	*c;
	if(c = _tcschr(m_sString, ch))
	{
		return (int)(c - m_sString);
	}

	return -1;
}
//*****************************************************************************
// - Finds first position of specified KString , if did not found return -1
//*****************************************************************************
int KString::Find(const KString &sStr)
{
	TCHAR	*c;
	if(c = _tcsstr(m_sString, sStr.m_sString))
	{
		return (int)(c - m_sString);
	}

	return -1;
}
//*****************************************************************************
// - Finds first position of specified string , if did not found return -1
//*****************************************************************************
int KString::Find(LPCTSTR lpszStr)
{
	TCHAR	*c;
	if(c = _tcsstr(m_sString, lpszStr))
	{
		return (int)(c - m_sString);
	}

	return -1;
}
//*****************************************************************************
// - Replace an old TCHAR with a new TCHAR
//*****************************************************************************
int KString::Replace(TCHAR cOld, TCHAR cNew)
{
	int i, iTotal = 0;

	for(i=0; i <= m_iLength; i++)
		if(m_sString[i] == cOld)
		{
			m_sString[i] = cNew;
			iTotal++;
		}

	return iTotal;
}
//*****************************************************************************
// - Replace an old string with a new string
//*****************************************************************************
int KString::Replace(LPCTSTR sOld, LPCTSTR sNew)
{
	KString	sTemp, sOrg(m_sString), sReplaced;
	int iFound = Find(sOld);
	if(iFound < 0)
		return 0;

	int	iTotal = 0;

	do
	{
		sTemp.m_iLength = iFound;
		delete[] sTemp.m_sString;
		sTemp.m_sString = new TCHAR[iFound + 1];
		_tcsncpy(sTemp.m_sString, sOrg.m_sString, iFound);
		sTemp.m_sString[iFound] = '\0';

		sReplaced += sTemp;
		sReplaced += sNew;

		iTotal += (int)_tcslen(sNew);
		sOrg.Remove(0, iFound + (int)_tcslen(sOld) - 1);

		iFound = sOrg.Find(sOld);
	}while(iFound >= 0);

	sReplaced += sOrg;

	*this = sReplaced;

	return iTotal;
}
//*****************************************************************************
// - Replace an old KString with a new KString
//*****************************************************************************
int KString::Replace(const KString &sOld, const KString &sNew)
{
	return Replace(sOld.m_sString, sNew.m_sString);
}
//*****************************************************************************
// - Returns iCount TCHARs from iStart
//*****************************************************************************
KString KString::Mid(int iStart, int iCount)
{
	if(iStart > m_iLength)
		return _T("");

	if(iStart + iCount > m_iLength)
		return Mid(iStart);

	KString	sTemp;
	sTemp.m_iLength = iCount;
	sTemp.m_sString = new TCHAR[iCount + 1];

	for(int i=0; i<iCount; i++)
		sTemp.m_sString[i] = m_sString[iStart + i];

	sTemp.m_sString[i] = '\0';

	return sTemp;
}
//*****************************************************************************
// - Returns TCHARs from nStart till the end
//*****************************************************************************
KString KString::Mid(int iStart)
{
	if(iStart > m_iLength)
		return _T("");

	KString	sTemp;
	sTemp.m_iLength = m_iLength - iStart;
	sTemp.m_sString = new TCHAR[sTemp.m_iLength + 1];

	for(int i=0; i<sTemp.m_iLength; i++)
		sTemp.m_sString[i] = m_sString[iStart + i];

	sTemp.m_sString[i] = '\0';

	return sTemp;
}
//*****************************************************************************
// - Returns iCount left TCHARs
//*****************************************************************************
KString KString::Left(int iCount)
{
	if(iCount > m_iLength)
		iCount = m_iLength;

	return Mid(0, iCount);
}
//*****************************************************************************
// - Returns iCount right TCHARs
//*****************************************************************************
KString KString::Right(int iCount)
{
	if(iCount > m_iLength)
		iCount = m_iLength;

	return Mid(m_iLength - iCount, iCount);
}
//*****************************************************************************
// - Removes a TCHAR in specified position
//*****************************************************************************
BOOL KString::Remove(int iPos)
{
	if(iPos > m_iLength - 1)
		return FALSE;

	if(m_iLength == 1)
		Empty();

	else if(m_iLength > 1)
	{
		KString	sTemp(m_sString);

		delete[] m_sString;
		m_sString = new TCHAR[m_iLength--];

		_tcsncpy(m_sString , sTemp.m_sString, iPos);
		m_sString[iPos] = '\0';
		_tcscat(m_sString , sTemp.m_sString + iPos + 1);
	}
	return TRUE;
}
//*****************************************************************************
// - Removes TCHARs from iStart to iEnd
//*****************************************************************************
int KString::Remove(int iStart, int iEnd)
{
	if(iEnd == -1)
		iEnd = m_iLength - 1;

	int	iDelCount = iEnd - iStart + 1;

	KString	sTemp(m_sString);

	delete[] m_sString;
	m_iLength -= iDelCount;
	m_sString = new TCHAR[m_iLength + 1];

	_tcsncpy(m_sString , sTemp.m_sString, iStart);
	m_sString[iStart] = '\0';
	_tcscat(m_sString , sTemp.m_sString + iStart + iDelCount);

	return iDelCount;
}
//*****************************************************************************
// - Removes all ch TCHAR
//*****************************************************************************
int KString::Remove(TCHAR ch)
{
	for(int i=0, j=0; i<m_iLength;)
	{
		if(m_sString[i] == ch)
		{
			Remove(i);
			++j;
		}
		else
			i++;
	}

	return j;
}
//*****************************************************************************
// - Removes all specified string
//*****************************************************************************
BOOL KString::Remove(const KString &sStr)
{
	int f = Find(sStr);
	if(f >= 0)
	{
		KString	sTemp(m_sString);

		delete[] m_sString;
		m_iLength -= sStr.m_iLength;
		m_sString = new TCHAR[m_iLength + 1];

		_tcsncpy(m_sString , sTemp.m_sString, f);
		m_sString[f] = '\0';
		_tcscat(m_sString , sTemp.m_sString + f + sStr.m_iLength);

		return TRUE;
	}

	return FALSE;
}
//*****************************************************************************
// - Trims left specified TCHAR
//*****************************************************************************
KString& KString::TrimLeft(TCHAR ch)
{
	while(m_sString[0] == ch)
		Remove(0);

	return *this;
}
//*****************************************************************************
// - Trims right specified TCHAR
//*****************************************************************************
KString& KString::TrimRight(TCHAR ch)
{
	while(m_sString[m_iLength - 1] == ch)
		Remove(m_iLength - 1);

	return *this;
}
//*****************************************************************************
// - Trims left and right specified TCHAR
//*****************************************************************************
KString& KString::Trim(TCHAR ch)
{
	TrimLeft(ch);
	TrimRight(ch);

	return *this;
}
//*****************************************************************************
// - Inserts a string in specified position
//*****************************************************************************
KString& KString::Insert(const KString &sStr, int iPos)
{
	KString	sTemp(m_sString);

	m_iLength += sStr.m_iLength;

	delete[] m_sString;
	m_sString = new TCHAR[m_iLength + 1];

	_tcsncpy(m_sString , sTemp.m_sString, iPos);
	m_sString[iPos] = '\0';
	_tcscat(m_sString , sStr.m_sString);
	m_sString[iPos + sStr.m_iLength] = '\0';
	_tcscat(m_sString , sTemp.m_sString + iPos);

	m_sString[m_iLength] = '\0';

	return *this;
}
//*****************************************************************************
// - Converts to upper case
//*****************************************************************************
KString& KString::MakeUpper()
{
	_tcsupr(m_sString);
	return *this;
}
//*****************************************************************************
// - Converts to lower case
//*****************************************************************************
KString& KString::MakeLower()
{
	_tcslwr(m_sString);
	return *this;
}
//*****************************************************************************
// - Reverses the string
//*****************************************************************************
KString& KString::MakeReverse()
{
	_tcsrev(m_sString);
	return *this;
}
//*****************************************************************************
// - Returns uppercase of string
//*****************************************************************************
KString KString::GetUpper()
{
	KString	sTemp(m_sString);
	sTemp.MakeUpper();

	return sTemp;
}
//*****************************************************************************
// - Returns lowercase of string
//*****************************************************************************
KString KString::GetLower()
{
	KString	sTemp(m_sString);
	sTemp.MakeLower();

	return sTemp;
}
//*****************************************************************************
// - Returns reverse of string
//*****************************************************************************
KString KString::GetReverse()
{
	KString	sTemp(m_sString);
	sTemp.MakeReverse();

	return sTemp;
}
//*****************************************************************************
// - Clears the string
//*****************************************************************************
void KString::Empty()
{
	if(m_sString)
	{
		delete[] m_sString;
		m_sString	= NULL;
		m_iLength	= 0;
	}
}
//*****************************************************************************
// - Creates a sized buffer (clears previous string)
//*****************************************************************************
LPTSTR KString::GetBuffer(int iBuffSize)
{
	if(m_sString)
		delete[] m_sString;
	m_iLength = iBuffSize;
	m_sString = new TCHAR[m_iLength + 1];
	memset(m_sString, 0, m_iLength);

	return m_sString;
}
//*****************************************************************************
// - Frees extra space
//*****************************************************************************
void KString::FreeExtra()
{
	m_iLength = (int)_tcslen(m_sString);

	LPTSTR pBuff = new TCHAR[m_iLength + 1];
	_tcscpy(pBuff, m_sString);

	if(m_sString )
		delete[] m_sString;

	m_sString = new TCHAR[m_iLength + 1];
	_tcscpy(m_sString, pBuff);

	delete[] pBuff;
}
//*****************************************************************************
// - Format string
//*****************************************************************************
void KString::Format(LPCTSTR pszCharSet, ...)
{
	va_list	vl;
	va_start(vl, pszCharSet);

	LPTSTR	pszTemp = NULL;
	int		nRetVal = -1;

	for(int nBufferSize = 100; nRetVal < 0; nBufferSize += 100)
	{
		delete [] pszTemp;
		pszTemp = new TCHAR[nBufferSize];
		nRetVal = _vsntprintf(pszTemp, nBufferSize, pszCharSet, vl);
	}
	va_end(vl);

	m_iLength	= (int)_tcslen(pszTemp);
	m_sString	= new TCHAR[m_iLength + 1];
	_tcscpy(m_sString, pszTemp);

	delete [] pszTemp;
}
//*****************************************************************************