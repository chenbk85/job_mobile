#include "stdafx.h"

#include "notepadreFile.h"

#include <algorithm>
#include <vector>

const DWORD CNotepadreFile::m_dwBufferSize = 1024;

// One possible apprach and why it was rejected:
// API function MultiByteToWideChar could of been used for UTF-8, but this
// means you either end up with two buffers (maybe doubling your memory usage)
// or you still have to do some pre-processing.
// Also, MultiByteToWideChar does not process non Windows line endings.

// The approach taken:
// After determining the file type, count how many bytes will be needed
// for the decoded file (this includes checking for non Windows
// line endings).  Realloc to the new size and decode the file in place.

// This class will undergo another rewrite, where I will go more for
// readability over efficiency.  I think at the moment it probably
// suffers from 'premature optimisation'..!
HLOCAL CNotepadreFile::Load (CFile *pFile, e_FileType &eFileType,
	e_FileFormat &eFileFormat)
{
	DWORD dwSize = pFile->GetLength ();
	DWORD dwNewSize = 0;
	HLOCAL hMem = 0;
	HLOCAL hNewMem = 0;
	unsigned char *pucText = 0;

	if (eFileType == eAutoFileType)
	{
		// This function can throw an exception. It is caught by
		// CNotepadreDoc::OnOpenDocument.
		GetFileType (pFile, eFileType, dwSize);
	}
	else
	{
		// TODO:  eFileType and eFileFormat are specified.
		// Load as the specified type and format.
	}

	ASSERT (eFileType < eAutoFileType);

	try
	{
		hMem = ::LocalAlloc (LMEM_MOVEABLE, dwSize + sizeof (TCHAR));

		if (hMem == 0) AfxThrowMemoryException ();

		pucText = static_cast<unsigned char *> (::LocalLock (hMem));
		// Call memset so that the trailing zero is set
		// and to make debugging the loader easier...
		::memset (pucText, 0, dwSize + sizeof (TCHAR));
		Read (pFile, pucText, dwSize);
		dwNewSize = CountBytes (pucText, dwSize, eFileType, eFileFormat);
		::LocalUnlock (hMem);
		// realloc to account for any lines that have UNIX or
		// Macintosh end of line characters
		hNewMem = ::LocalReAlloc (hMem, dwNewSize + sizeof (TCHAR),
			LMEM_MOVEABLE);

		if (hNewMem == 0)
		{
			// LocalReAlloc failed, so attempt to re-load
			::LocalFree (hMem);
			hMem = 0;
			hNewMem = ::LocalAlloc (LMEM_MOVEABLE, dwNewSize + sizeof (TCHAR));

			if (hNewMem == 0) AfxThrowMemoryException ();

			pucText = static_cast<unsigned char *> (::LocalLock (hNewMem));
			::memset (pucText, 0, dwNewSize + sizeof (TCHAR));

			if (eFileType == eANSI)
				pFile->SeekToBegin ();
			else if (eFileType != eUTF8)
				pFile->Seek (2, CFile::begin);

			if (eFileType != eUTF8)
			{
				// Use original size (file size has not changed!)
				Read (pFile, pucText, dwSize);
			}
		}
		else
		{
			hMem = 0;
			pucText = static_cast<unsigned char *> (::LocalLock (hNewMem));

			if (dwNewSize > dwSize)
			{
				::memset (pucText + dwSize + sizeof (TCHAR), 0,
					dwNewSize - dwSize);
			}
		}
	}
	catch (...)
	{
		::LocalFree (hMem);
		hMem = 0;
		::LocalFree (hNewMem);
		hNewMem = 0;
		// Pass exception on to CNotepadreDoc::OnOpenDocument
		throw;
	}

	if (eFileType == eUTF8)
	{
		pFile->Seek (3, CFile::begin);
		::memset (pucText, 0, dwNewSize + sizeof (TCHAR));
		// TO DO: Decode the file in place (move it down the buffer and
		// place decoded chars at the front of the buffer).
		LoadUTF8File (pFile, eFileFormat,
			reinterpret_cast<wchar_t *> (pucText), dwSize);
	}
	else
	{
		ExpandText (reinterpret_cast<TCHAR *>(pucText), dwSize,
			dwNewSize / sizeof (TCHAR), eFileType, eFileFormat);
	}

	::LocalUnlock (hNewMem);
	return hNewMem;
}

void CNotepadreFile::Save (const TCHAR *pszText, const DWORD dwChars,
	const e_FileType eFileType, const e_FileFormat eFileFormat, CFile *pFile)
{
	DWORD dwCharCount = dwChars;
	// Must be an even number greater than 3...
	unsigned char ucBuffer[m_dwBufferSize];
	DWORD dwSize = 0;

	SaveHeader (pFile, eFileType);

	while (dwCharCount)
	{
		FillBuffer (pszText, dwCharCount, eFileType, eFileFormat, ucBuffer,
			m_dwBufferSize, dwSize);
		// Write throws CFileException if it fails
		pFile->Write (ucBuffer, dwSize);
	}
}

// All file read operations come through here
void CNotepadreFile::Read (CFile *pFile, unsigned char *pucText, const DWORD dwSize)
{
	if (pFile->Read (pucText, dwSize) != dwSize)
	{
		AfxThrowArchiveException (CArchiveException::endOfFile);
	}
}

void CNotepadreFile::GetFileType (CFile *pFile, e_FileType &eFileType,
	DWORD &dwSize)
{
	// Default to ANSI
	eFileType = eANSI;
	dwSize = pFile->GetLength ();

	if (dwSize > 1)
	{
		unsigned char ucHeader[2];

		Read (pFile, ucHeader, 2);

		// Check for Unicode
		if (ucHeader[0] == 0xff && ucHeader[1] == 0xfe)
		{
			// A Unicode file must have an even number of bytes
			if (dwSize % 2 == 0)
			{
				eFileType = eUnicode;
				dwSize -= 2;
			}
			else
			{
				eFileType = eINVALID;
			}
		}
		// Check for Unicode Big Endian
		else if (ucHeader[0] == 0xfe &&	ucHeader[1] == 0xff)
		{
			// A Unicode (Big Endian) file must have an even number of bytes
			if (dwSize % 2 == 0)
			{
				eFileType = eUnicodeBigEndian;
				dwSize -= 2;
			}
			else
			{
				eFileType = eINVALID;
			}
		}
		// Check for UTF-8
		else if (ucHeader[0] == 0xef &&	ucHeader[1] == 0xbb)
		{
			// UTF-8 has a three char header
			if (dwSize > 2)
			{
				Read (pFile, ucHeader, 1);

				if (ucHeader[0] == 0xbf)
				{
					eFileType = eUTF8;
					dwSize -= 3;
				}
				else
				{
					eFileType = eINVALID;
				}
			}
			else
			{
				eFileType = eINVALID;
			}
		}
		else
		{
			pFile->SeekToBegin ();
		}
	}

	if (eFileType == eINVALID)
	{
		AfxThrowArchiveException (CArchiveException::badIndex);
	}

#ifndef _UNICODE
	if (eFileType != eANSI)
	{
		AfxThrowArchiveException (CArchiveException::badIndex);
	}
#endif
}
DWORD CNotepadreFile::CountBytes (unsigned char *pucText,
	const DWORD dwSize, const e_FileType &eFileType, e_FileFormat &eFileFormat)
{
	DWORD dwNewChars = 0;
	const TCHAR *pszText = reinterpret_cast<const TCHAR *>(pucText);
	unsigned __int64 ui64Windows = 0;
	unsigned __int64 ui64UNIX = 0;
	unsigned __int64 ui64Macintosh = 0;
	std::vector<__int64> FormatVector;

	// It is more efficient to process each file type separately
	if (eFileType == eANSI)
	{
		dwNewChars = CountCharsANSI (pucText, dwSize, ui64Windows, ui64UNIX,
			ui64Macintosh);
	}
	else if (eFileType == eUnicode)
	{
		dwNewChars = CountCharsUnicode (reinterpret_cast<const TCHAR *>
			(pucText), dwSize / sizeof (TCHAR), ui64Windows, ui64UNIX,
			ui64Macintosh);
	}
	else if (eFileType == eUnicodeBigEndian)
	{
		dwNewChars = CountCharsUnicodeBE (reinterpret_cast<TCHAR *>
			(pucText), dwSize / sizeof (TCHAR), ui64Windows, ui64UNIX,
			ui64Macintosh);
	}
	else
	{
		dwNewChars = CountCharsUTF8 (pucText, dwSize, ui64Windows, ui64UNIX,
			ui64Macintosh);
	}

	if (eFileFormat == eAutoFileFormat)
	{
		FormatVector.push_back (ui64Windows);
		FormatVector.push_back (ui64UNIX);
		FormatVector.push_back (ui64Macintosh);
		std::sort (FormatVector.begin (), FormatVector.end ());

		if (FormatVector[2] == ui64Windows)
		{
			eFileFormat = CNotepadreFile::eWindows;
		}
		else if (FormatVector[2] == ui64UNIX)
		{
			eFileFormat = CNotepadreFile::eUNIX;
		}
		else if (FormatVector[2] == ui64Macintosh)
		{
			eFileFormat = CNotepadreFile::eMacintosh;
		}
	}

	return dwNewChars * sizeof (TCHAR);
}

DWORD CNotepadreFile::CountCharsANSI (const unsigned char *pucText,
	const DWORD dwChars, unsigned __int64 &ui64Windows,
	unsigned __int64 &ui64UNIX, unsigned __int64 &ui64Macintosh)
{
	DWORD dwCount = dwChars;
	DWORD dwNewChars = 0;

	while (dwCount)
	{
		if (*pucText == '\r')
		{
			if (*(pucText + 1) != '\n')
			{
				ui64Macintosh++;
				dwNewChars++;
			}
			else
			{
				ui64Windows++;
			}
		}
		else if (*pucText == '\n')
		{
			if (dwCount == dwChars || *(pucText - 1) != '\r')
			{
				ui64UNIX++;
				dwNewChars++;
			}

			// In the case of Windows format \r\n has already been checked
		}

		pucText++;
		dwNewChars++;
		dwCount--;
	}

	return dwNewChars;
}

DWORD CNotepadreFile::CountCharsUnicode (const TCHAR *pszText,
	const DWORD dwChars, unsigned __int64 &ui64Windows,
		unsigned __int64 &ui64UNIX, unsigned __int64 &ui64Macintosh)
{
	DWORD dwCount = dwChars;
	DWORD dwNewChars = 0;

	while (dwCount)
	{
		if (*pszText == '\r')
		{
			if (*(pszText + 1) != '\n')
			{
				ui64Macintosh++;
				dwNewChars++;
			}
			else
			{
				ui64Windows++;
			}
		}
		else if (*pszText == '\n')
		{
			if (dwCount == dwChars || *(pszText - 1) != '\r')
			{
				ui64UNIX++;
				dwNewChars++;
			}

			// In the case of Windows format \r\n has already been checked
		}

		pszText++;
		dwNewChars++;
		dwCount--;
	}

	return dwNewChars;
}

// Swap bytes at the same time for efficiencies sake
DWORD CNotepadreFile::CountCharsUnicodeBE (TCHAR *pszText,
	const DWORD dwChars, unsigned __int64 &ui64Windows,
	unsigned __int64 &ui64UNIX, unsigned __int64 &ui64Macintosh)
{
	DWORD dwCount = dwChars;
	DWORD dwNewChars = 0;

	while (dwCount)
	{
		// Flip wide char to little endian
		*pszText = Swap (*pszText);

		if (*pszText == '\r')
		{
			if (Swap (*(pszText + 1)) != '\n')
			{
				ui64Macintosh++;
				dwNewChars++;
			}
			else
			{
				ui64Windows++;
			}
		}
		else if (*pszText == '\n')
		{
			// *(pszText - 1) is already Swapped
			if (dwCount == dwChars || *(pszText - 1) != '\r')
			{
				ui64UNIX++;
				dwNewChars++;
			}

			// In the case of Windows format \r\n has already been checked
		}

		pszText++;
		dwNewChars++;
		dwCount--;
	}

	return dwNewChars;
}

DWORD CNotepadreFile::CountCharsUTF8 (const unsigned char *pucText,
	const DWORD dwChars, unsigned __int64 &ui64Windows,
		unsigned __int64 &ui64UNIX, unsigned __int64 &ui64Macintosh)
{
	DWORD dwCount = dwChars;
	DWORD dwBytes = 0;
	DWORD dwNewChars = 0;
	wchar_t wcPrevChar = 0;
	wchar_t wcChar = 0;

	while (dwCount)
	{
		dwBytes = CheckUTF8Char (pucText, dwCount);

		dwCount -= dwBytes;

		if (wcPrevChar == '\r')
		{
			if (wcChar != '\n')
			{
				ui64Macintosh++;
				dwNewChars++;
			}
			else
			{
				ui64Windows++;
			}
		}
		else if (wcChar == '\n')
		{
			if (wcPrevChar != '\r')
			{
				ui64UNIX++;
				dwNewChars++;
			}

			// In the case of Windows format \r\n has already been checked
		}

		pucText += dwBytes;
		wcPrevChar = wcChar;
		dwNewChars++;
	}

	// Check if last character is \r
	if (wcChar == '\r')
	{
		ui64Macintosh++;
		dwNewChars++;
	}

	return dwNewChars;
}

inline wchar_t CNotepadreFile::Swap (wchar_t wc)
{
	char *pc = reinterpret_cast<char *> (&wc);
	char c = *pc;

	*pc++ = *(pc + 1);
	*pc = c;
	return wc;
}

// UTF-8 Format:
// 0000:0000 -> 0000:007f = 0xxxxxxx
// 0000:0080 -> 0000:07ff = 110xxxxx 10xxxxxx
// 0000:0800 -> 0000:ffff = 1110xxxx 10xxxxxx 10xxxxxx

// Counts how many bytes the next UTF-8 uses and returns them.
// Checks that there are no obvious data errors in the file
DWORD CNotepadreFile::CheckUTF8Char (const unsigned char * pucBytes,
	const DWORD dwCharsLeft)
{
	DWORD dwBytes = 0;
	unsigned char ucCountMask = 0x80;

	while (*pucBytes & ucCountMask)
	{
		ucCountMask >>= 1;
		dwBytes++;
	}

	if (dwBytes == 0) dwBytes = 1;

	if (dwBytes > 3 || dwCharsLeft - dwBytes < 0)
	{
		// Only support 16 bit unicode, check for unexpected EOF
		AfxThrowArchiveException (CArchiveException::badIndex);
	}

	for (DWORD dwIndex = 1; dwIndex < dwBytes; dwIndex++)
	{
		if ((pucBytes[dwIndex] & 0xc0) != 0x80)
		{
			// Data not as advertised
			AfxThrowArchiveException (CArchiveException::badIndex);
		}
	}

	return dwBytes;
}

DWORD CNotepadreFile::DecodeUTF8Char (const unsigned char * &pucBytes,
	wchar_t &wcChar)
{
	DWORD dwBytes = 0;
	unsigned char ucCountMask = 0x80;
	unsigned char ucHighMask = 0x7f;
	unsigned char ucBytes[2] = {0, 0};

	while (*pucBytes & ucCountMask)
	{
		ucCountMask >>= 1;
		ucHighMask >>= 1;
		dwBytes++;
	}

	if (dwBytes == 0) dwBytes = 1;

	if (dwBytes > 1)
	{
		unsigned char ucHighBits = *(pucBytes + dwBytes - 2) << 6;

		ucBytes[0] = *(pucBytes + dwBytes - 1) & 0x3f;
		ucBytes[0] |= ucHighBits;

		if (dwBytes > 2)
		{
			ucBytes[1] = *(pucBytes + dwBytes - 2) & 0x3f;
			ucBytes[1] >>= 2;
			ucBytes[1] |= (*pucBytes & ucHighMask) << 4;
		}
		else
		{
			ucBytes[1] = (*pucBytes & ucHighMask) >> 2;
		}

		wcChar = *reinterpret_cast<wchar_t *> (ucBytes);
		pucBytes += dwBytes;
	}
	else
	{
		wcChar = *pucBytes++;
	}

	return dwBytes;
}

void CNotepadreFile::LoadUTF8File (CFile *pFile,
	const e_FileFormat eFileFormat, wchar_t *pszText, const DWORD dwSize)
{
	wchar_t wcPreviousChar = 0;
	DWORD dwBytesLeft = dwSize;
	// Must not be less than 3..!
	unsigned char ucBuffer[m_dwBufferSize];
	DWORD dwBufferIndex = 0;
	DWORD dwBytesToLoad = 0;

	while (dwBytesLeft)
	{
		dwBytesToLoad = dwBytesLeft > m_dwBufferSize ? m_dwBufferSize :
			dwBytesLeft;
		Read (pFile, ucBuffer, dwBytesToLoad);
		dwBytesLeft -= dwBytesToLoad;
		dwBufferIndex = 0;

		while (dwBytesToLoad)
		{
			if (ucBuffer[dwBufferIndex] & 0x80)
			{
				unsigned char ucMask = 0x80;
				DWORD dwBytes = 0;
				unsigned char *puc = 0;
				DWORD dwIndex = 0;
				wchar_t wcChar = 0;

				// File format has already been checked for validity
				// so we don't need to check again.
				while (ucBuffer[dwBufferIndex] & ucMask)
				{
					ucMask >>= 1;
					dwBytes++;
				}

				if (dwBytes > dwBytesToLoad)
				{
					DWORD dwAdditional = dwBytesToLoad;

					// Buffer over-run - reload buffer
					memcpy (ucBuffer, &ucBuffer[dwBufferIndex], dwAdditional);
					dwBytesToLoad = dwBytesLeft > m_dwBufferSize ?
						m_dwBufferSize - dwAdditional : dwBytesLeft;
					Read (pFile, &ucBuffer[dwAdditional], dwBytesToLoad);
					dwBytesLeft -= dwBytesToLoad;
					dwBytesToLoad += dwAdditional;
					dwBufferIndex = 0;
				}

				puc = &ucBuffer[dwBufferIndex];

				dwIndex = DecodeUTF8Char (puc, wcChar);
				*pszText++ = wcChar;
				dwBytesToLoad -= dwIndex;
				dwBufferIndex += dwIndex;
			}
			else
			{
				// Because we are decoding a character at a time and the
				// loading of the file is buffered, it is easier to
				// keep track of the previous character.
				if (wcPreviousChar == '\r' && ucBuffer[dwBufferIndex] != '\n')
				{
					*pszText++ = '\n';
				}
				// This means we are one character behind, so we have to check
				// for the last character being \r outside of this loop.
				else if (ucBuffer[dwBufferIndex] == '\n' && wcPreviousChar != '\r')
				{
					*pszText++ = '\r';
				}

				*pszText++ = ucBuffer[dwBufferIndex];
				dwBufferIndex++;
				dwBytesToLoad--;
			}

			wcPreviousChar = *(pszText - 1);
		}
	}

	// Check for case of Macintosh format ending with \r
	if (wcPreviousChar == '\r')
	{
		*pszText++ = '\n';
	}
}

void CNotepadreFile::ExpandText (TCHAR *pszText, const DWORD dwSize,
	const DWORD dwChars, const e_FileType eFileType,
	const e_FileFormat eFileFormat)
{
	// It is more efficient to process each file type separately
	if (eFileType == eANSI)
	{
		DWORD dwCharCount = dwChars;
		// use a char * as the file is read as bytes regardless of build type
		unsigned char *pszRead = (reinterpret_cast<unsigned char *>
			(pszText)) + dwSize - 1;
		// build dependant write pointer (TCHAR)
		TCHAR *pszWrite = pszText + dwChars - 1;

		// Read backwards so that writing out chars
		// does not write over data yet to be read
		while (dwCharCount)
		{
			if (*pszRead == '\r' && *(pszWrite + 1) != '\n')
			{
				*pszWrite-- = '\n';
				dwCharCount--;
				*pszWrite-- = *pszRead--;
			}
			// Check for running off the beginning of the buffer.
			// In this case, dwCharCount will be 2.
			else if (*pszRead == '\n' && (dwCharCount < 3 ||
				*(pszRead - 1) != '\r'))
			{
				*pszWrite-- = *pszRead--;
				*pszWrite-- = '\r';
				dwCharCount--;
			}
			else
			{
				*pszWrite-- = *pszRead--;
			}

			dwCharCount--;
		}
	}
	else if (eFileType == eUnicode || eFileType == eUnicodeBigEndian)
	{
		DWORD dwCharCount = dwChars;
		TCHAR *pszRead = pszText + dwSize / sizeof (wchar_t) - 1;
		TCHAR *pszWrite = pszText + dwChars - 1;

		// Read backwards so that writing out chars
		// does not write over data yet to be read
		while (dwCharCount)
		{
			if (*pszRead == '\r' && *(pszWrite + 1) != '\n')
			{
				*pszWrite-- = '\n';
				dwCharCount--;
				*pszWrite-- = *pszRead--;
			}
			// Check for running off the beginning of the buffer.
			// In this case, dwCharCount will be 2.
			else if (*pszRead == '\n' && (dwCharCount < 3 ||
				*(pszRead - 1) != '\r'))
			{
				*pszWrite-- = *pszRead--;
				*pszWrite-- = '\r';
				dwCharCount--;
			}
			else
			{
				*pszWrite-- = *pszRead--;
			}

			dwCharCount--;
		}
	}
	else
	{
		ASSERT (0);
	}

	ZerosToSpaces (pszText, dwChars);
}

void CNotepadreFile::ZerosToSpaces (TCHAR *pszText, const DWORD dwChars)
{
	for (DWORD c = 0; c < dwChars; c++)
	{
		if (!*pszText) *pszText = ' ';

		pszText++;
	}
}

void CNotepadreFile::SaveHeader (CFile *pFile, const e_FileType eFileType)
{
	if (eFileType == eUnicode)
	{
		char szHeader[] = {(char) 0xff, (char) 0xfe};

		// Write throws CFileException if it fails
		pFile->Write (szHeader, 2);
	}
	else if (eFileType == eUnicodeBigEndian)
	{
		char szHeader[] = {(char) 0xfe, (char) 0xff};

		// Write throws CFileException if it fails
		pFile->Write (szHeader, 2);
	}
	else if (eFileType == eUTF8)
	{
		char szHeader[] = {(char) 0xef, (char) 0xbb, (char) 0xbf};

		// Write throws CFileException if it fails
		pFile->Write (szHeader, 3);
	}
	else if (eFileType != eANSI)
	{
		ASSERT (0);
	}
}

void CNotepadreFile::FillBuffer (const TCHAR * &pszText, DWORD &dwCharCount,
	const e_FileType eFileType,	const e_FileFormat eFileFormat,
	unsigned char *ucBuffer, const DWORD dwBufferSize, DWORD &dwSize)
{
	DWORD dwBufferIndex = 0;

	dwSize = 0;

	if (eFileType == eANSI)
	{
#ifdef _UNICODE
		while (dwCharCount && dwBufferIndex < dwBufferSize)
		{
			if (!(eFileFormat == eUNIX && *pszText == '\r') &&
				!(eFileFormat == eMacintosh && *pszText == '\n'))
			{
				ucBuffer[dwBufferIndex++] =
					*reinterpret_cast<const unsigned char *> (pszText);
				dwSize++;
			}

			pszText++;
			dwCharCount--;
		}
#else
		while (dwCharCount && dwBufferIndex < dwBufferSize)
		{
			if (!(eFileFormat == eUNIX && *pszText == '\r') &&
				!(eFileFormat == eMacintosh && *pszText == '\n'))
			{
				ucBuffer[dwBufferIndex++] = *pszText;
				dwSize++;
			}

			pszText++;
			dwCharCount--;
		}
#endif
	}
	else if (eFileType == eUnicode)
	{
#ifdef _UNICODE
		while (dwCharCount && dwBufferIndex < dwBufferSize)
		{
			if (!(eFileFormat == eUNIX && *pszText == '\r') &&
				!(eFileFormat == eMacintosh && *pszText == '\n'))
			{
				ucBuffer[dwBufferIndex++] = LOBYTE (*pszText);
				ucBuffer[dwBufferIndex++] = HIBYTE (*pszText);
				dwSize += 2;
			}

			pszText++;
			dwCharCount--;
		}
#else
		while (dwCharCount && dwBufferIndex < dwBufferSize)
		{
			if (!(eFileFormat == eUNIX && *pszText == '\r') &&
				!(eFileFormat == eMacintosh && *pszText == '\n'))
			{
				ucBuffer[dwBufferIndex++] = *pszText;
				ucBuffer[dwBufferIndex++] = 0;
				dwSize += 2;
			}

			pszText++;
			dwCharCount--;
		}
#endif
	}
	else if (eFileType == eUnicodeBigEndian)
	{
#ifdef _UNICODE
		while (dwCharCount && dwBufferIndex < dwBufferSize)
		{
			if (!(eFileFormat == eUNIX && *pszText == '\r') &&
				!(eFileFormat == eMacintosh && *pszText == '\n'))
			{
				ucBuffer[dwBufferIndex++] = HIBYTE (*pszText);
				ucBuffer[dwBufferIndex++] = LOBYTE (*pszText);
				dwSize += 2;
			}

			pszText++;
			dwCharCount--;
		}
#else
		while (dwCharCount && dwBufferIndex < dwBufferSize)
		{
			if (!(eFileFormat == eUNIX && *pszText == '\r') &&
				!(eFileFormat == eMacintosh && *pszText == '\n'))
			{
				ucBuffer[dwBufferIndex++] = 0;
				ucBuffer[dwBufferIndex++] = *pszText;
				dwSize += 2;
			}

			pszText++;
			dwCharCount--;
		}
#endif
	}
	else if (eFileType == eUTF8)
	{
		wchar_t wc = 0;
		unsigned char ucHeader = 0;
		unsigned char ucHigh = 0;
		unsigned char ucLow = 0;
		unsigned char ucHighBitsHigh = 0;
		unsigned char ucHighBitsLow = 0;

		while (dwCharCount && dwBufferIndex < dwBufferSize)
		{
			wc = *pszText;

			if (wc > 0x7ff)
			{
				// break if buffer will over-run
				if (dwBufferIndex > dwBufferSize - 3) break;

				ucHeader = 0xe0;
				ucHigh = HIBYTE (wc);
				ucLow = LOBYTE (wc);
				ucHighBitsHigh = ucHigh & 0xf0;
				ucHighBitsLow = ucLow & 0xc0;

				ucLow &= 0x3f;
				ucLow |= 0x80;
				ucHigh <<= 2;
				ucHigh &= 0x3f;
				ucHigh |= 0x80;

				if (ucHighBitsLow & 0x80) ucHigh |= 2;
				if (ucHighBitsLow & 0x40) ucHigh |= 1;
				if (ucHighBitsHigh & 0x80) ucHeader |= 8;
				if (ucHighBitsHigh & 0x40) ucHeader |= 4;
				if (ucHighBitsHigh & 0x20) ucHeader |= 2;
				if (ucHighBitsHigh & 0x10) ucHeader |= 1;

				ucBuffer[dwBufferIndex++] = ucHeader;
				ucBuffer[dwBufferIndex++] = ucHigh;
				ucBuffer[dwBufferIndex++] = ucLow;
				dwSize += 3;
			}
			else if (wc > 0x7f)
			{
				// break if buffer will over-run
				if (dwBufferIndex > dwBufferSize - 2) break;

				ucHigh = HIBYTE (wc);
				ucLow = LOBYTE (wc);
				ucHighBitsLow = ucLow & 0xc0;

				ucLow &= 0x3f;
				ucLow |= 0x80;
				ucHigh <<= 2;

				if (ucHighBitsLow & 0x80) ucHigh |= 2;
				if (ucHighBitsLow & 0x40) ucHigh |= 1;

				ucHigh |= 0xc0;

				ucBuffer[dwBufferIndex++] = ucHigh;
				ucBuffer[dwBufferIndex++] = ucLow;
				dwSize += 2;
			}
			else if (!(eFileFormat == eUNIX && *pszText == '\r') &&
				!(eFileFormat == eMacintosh && *pszText == '\n'))
			{
				ucBuffer[dwBufferIndex++] =
					*reinterpret_cast<const char *> (pszText);
				dwSize++;
			}

			pszText++;
			dwCharCount--;
		}
	}
	else
	{
		ASSERT (0);
	}
}
