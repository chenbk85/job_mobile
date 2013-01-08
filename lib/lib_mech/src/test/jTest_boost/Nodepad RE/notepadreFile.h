#ifndef NOTEPADREFILE_H
#define NOTEPADREFILE_H

class CNotepadreFile
{
public:
	enum e_FileType {eANSI, eUnicode, eUnicodeBigEndian, eUTF8, eAutoFileType,
		eINVALID};
	enum e_FileFormat {eWindows, eUNIX, eMacintosh, eAutoFileFormat};

	static HLOCAL Load (CFile *pFile, e_FileType &eFileType,
		e_FileFormat &eFileFormat);
	static void Save (const TCHAR *pszText, const DWORD dwChars,
		const e_FileType eFileType, const e_FileFormat eFileFormat,
		CFile *pFile);

private:
	static const DWORD m_dwBufferSize;

	static void Read (CFile *pFile, unsigned char *pucText,
		const DWORD dwSize);
	static void GetFileType (CFile *pFile, e_FileType &eFileType,
		DWORD &dwSize);
	static DWORD CountBytes (unsigned char *pucText, const DWORD dwSize,
		const e_FileType &eFileType, e_FileFormat &eFileFormat);
	static DWORD CountCharsANSI (const unsigned char *pucText,
		const DWORD dwSize, unsigned __int64 &ui64Windows,
		unsigned __int64 &ui64UNIX, unsigned __int64 &ui64Macintosh);
	static DWORD CountCharsUnicode (const TCHAR *pszText, const DWORD dwSize,
		unsigned __int64 &ui64Windows, unsigned __int64 &ui64UNIX,
		unsigned __int64 &ui64Macintosh);
	// Special case: byte swap whilst counting for efficiencies sake
	static DWORD CountCharsUnicodeBE (TCHAR *pszText,
		const DWORD dwSize, unsigned __int64 &ui64Windows,
		unsigned __int64 &ui64UNIX, unsigned __int64 &ui64Macintosh);
	static DWORD CountCharsUTF8 (const unsigned char *pucText,
		const DWORD dwSize, unsigned __int64 &ui64Windows,
		unsigned __int64 &ui64UNIX, unsigned __int64 &ui64Macintosh);
	inline static wchar_t Swap (wchar_t wc);
	static DWORD CheckUTF8Char (const unsigned char *pucBytes, const DWORD dwCharsLeft);
	static DWORD DecodeUTF8Char (const unsigned char * &pucBytes, wchar_t &wcChar);
	static void LoadUTF8File (CFile *pFile, const e_FileFormat eFileFormat,
		wchar_t *pszText, const DWORD dwSize);
	static void ExpandText (TCHAR *pszText, const DWORD dwSize,
		const DWORD dwChars, const e_FileType eFileType,
		const e_FileFormat eFileFormat);
	static void ZerosToSpaces (TCHAR *pszText, const DWORD dwChars);
	static void SaveHeader (CFile *pFile, const e_FileType eFileType);
	static void FillBuffer (const TCHAR * &lpszText, DWORD &dwCharCount,
		const e_FileType eFileType, const e_FileFormat eFileFormat,
		unsigned char *ucBuffer, const DWORD dwBufferSize, DWORD &dwSize);
};

#endif
