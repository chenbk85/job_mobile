// XFile.h  Version 1.2
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// This software is released into the public domain.  You are free to use it 
// in any way you like.
//
// This software is provided "as is" with no expressed or implied warranty.  
// I accept no liability for any damage or loss of business that this software 
// may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef XFILE_H
#define XFILE_H

#define XFILE_ERROR ((DWORD)-1)
#define XFILE_EOF	((DWORD)-2)

class JBASE_API CXFile
{
// Constructors
public:
	typedef		enum tagFILESIZELIMITTYPE
				{
					SHRINK,
					TRUNCATE
				} FILESIZELIMITTYPE;

	CXFile(LPCTSTR lpszFile = NULL,				// file name
		   BOOL bReadOnly = FALSE,				// TRUE = file is readonly
		   BOOL bTruncate = FALSE,				// TRUE = open existing and 
												// truncate, or create new;
												// FALSE = open existing (do not 
												// truncate), or create new
		   BOOL bUnicode = FALSE,				// TRUE = file is Unicode text file,
												// Unicode header will be written
		   DWORD dwBufSize = 64 * 1024,			// internal buffer size for writes
		   DWORD dwReadBufSize = 64 * 1024);	// internal buffer size for GetRecord()

	virtual void Init();
	virtual ~CXFile();

// Attributes
public:
	DWORD		GetAllocationGranularity()	// may be called anytime after CXFile
											// object created
	{ 
		return m_dwAllocationGranularity; 
	}
	DWORD		GetBufferSize()              { return m_dwBufferSize; }
	HANDLE		GetFileHandle()              { return m_hFile; }
	LPTSTR		GetFileName()                { return m_szFile; }
	LPTSTR		GetFullName(LPCTSTR lpszFile);
	LPTSTR		GetLastErrorString();
	DWORD		GetLastFileError()           { return m_dwLastError; }
	BOOL		GetReadOnly()                { return m_bReadOnly; }
	LPBYTE		GetRecordDelimiter()         { return m_RecordDelimiter; }
	DWORD		GetRecordDelimiterSize()     { return m_dwRecordDelimiterSize; }
	LPCTSTR		GetRolloverLogFile()         { return m_szRolloverLogFile; }
	DWORD		GetSizeLimitBytes()          { return m_dwSizeLimitBytes; }
	LPBYTE		GetSizeLimitDelimiter()      { return m_SizeLimitDelimiter; }
	DWORD		GetSizeLimitDelimiterSize()  { return m_dwLimitDelimiterSize; }
	FILESIZELIMITTYPE	GetSizeLimitType()   { return m_eSizeLimitType; }
	DWORD		GetTotalBytesReadFromFile()  { return m_dwTotalBytesReadFromFile; }
	DWORD		GetTotalBytesWrittenToFile() { return m_dwTotalBytesWrittenToFile; }
	DWORD		GetTotalNumberOfReads()      { return m_dwTotalNumberOfReads; }
	DWORD		GetTotalNumberOfWrites()     { return m_dwTotalNumberOfWrites; }
	DWORD		GetTotalRecordsRead()        { return m_dwTotalRecordsRead; }
	BOOL		GetTruncate()                { return m_bTruncate; }
	BOOL		GetUnicode()                 { return m_bUnicode; }
	BOOL		IsBufferEmpty()              // TRUE = buffer is empty
				{
					return (m_dwBufferIndex == 0); 
				}
	static BOOL IsFileAccessible(LPCTSTR lpszFile, DWORD dwAccess = GENERIC_READ);
	BOOL		IsFileOpen()				// TRUE = file is open
				{
					if (m_bMappedFile)
						return ((m_hFile != NULL) && (m_hMappedFile != NULL));
					else
						return ((m_hFile != NULL) && (m_hFile != INVALID_HANDLE_VALUE));
				}
	void		SetRecordDelimiter(LPBYTE lpDelimiter, DWORD dwDelimiterSize)
				{
					memset(m_RecordDelimiter, 0, sizeof(m_RecordDelimiter));
					m_dwRecordDelimiterSize = 0;
					if (lpDelimiter && dwDelimiterSize)
					{
						if (dwDelimiterSize > sizeof(m_RecordDelimiter))
							dwDelimiterSize = sizeof(m_RecordDelimiter);
						memcpy(m_RecordDelimiter, lpDelimiter, dwDelimiterSize);
						m_dwRecordDelimiterSize = dwDelimiterSize;
					}
				}
	void		SetRolloverLogFile(LPCTSTR lpszLogFile);
	BOOL		SetSizeLimit(DWORD dwSizeLimitBytes = 0, 
							 FILESIZELIMITTYPE eLimitType = TRUNCATE,
							 LPBYTE lpDelimiter = NULL,
							 DWORD dwDelimiterSize = 0);

// Operations
public:
			BOOL	ClearBuffer();
	virtual	BOOL	Close();
			BOOL	Compare(LPCTSTR lpszFile1, LPCTSTR lpszFile2, BOOL *pbResult);
			BOOL	Copy(LPCTSTR lpszExistingFileName, 
						 LPCTSTR lpszNewFileName, 
						 BOOL bFailIfExists = TRUE);
			BOOL	Delete(LPCTSTR lpszFile);
			DWORD	Flush();
	virtual	DWORD	GetRecord(LPTSTR lpszBuffer, DWORD dwBytes);
	virtual	BOOL	Open(LPCTSTR lpszFile, 
						 BOOL bReadOnly = FALSE, 
						 BOOL bTruncate = FALSE,
						 BOOL bUnicode = FALSE);
	virtual BOOL	OpenMapped(LPCTSTR lpszFile);
			DWORD	Prepend(LPTSTR lpszBuffer, DWORD dwBytes);
			int		Printf(LPCTSTR lpszFmt, ...);
	virtual	DWORD	Read(LPTSTR lpszBuffer, DWORD dwBytes);
	virtual	DWORD	ReadMapped(LPTSTR lpszBuffer, DWORD dwBytes);
			BOOL	Rename(LPCTSTR lpszExistingFileName,
						   LPCTSTR lpszNewFileName,
						   BOOL bFailIfExists = TRUE);
			BOOL	Rollover(LPCTSTR lpszRolloverFileName = NULL,
							 LPTSTR lpszFileNameBuffer = NULL,
							 DWORD dwFileNameBufferSize = 0,
							 BOOL bFailIfExists = TRUE,
							 BOOL bZip = FALSE,
							 BOOL bGenerateRolloverLogFile = FALSE);
			DWORD	Search(LPBYTE lpSearch, 
						   DWORD dwSearchSize, 
						   BOOL bCaseInsensitive = FALSE);
			DWORD	Seek(LONG lOffset, DWORD dwOrigin);
			DWORD	Shrink(DWORD dwMaxFileSize, 
						   DWORD dwBytesToShrink, 
						   LPBYTE lpDelimiter = NULL,
						   DWORD dwDelimiterSize = 0);

	virtual	DWORD	Write(LPCTSTR lpszBuffer, DWORD dwBytes);
			BOOL	Zip(LPCTSTR lpszZipArchive, 
						LPCTSTR lpszSrcFile, 
						BOOL bFailIfExists = TRUE,
						BOOL bDeleteSrcFile = FALSE);

// Implementation
protected:

	DWORD		FillReadBuf();
	DWORD		FindDelimiter();
	BOOL		GenerateRolloverLogFile(LPCTSTR lpszFile);
	DWORD		OutputPartialRecord(LPTSTR lpszBuffer, DWORD dwBytes);
	BOOL		WriteUnicodeHeader(HANDLE hFile);

	BOOL		m_bUnicode;						// TRUE = write Unicode header
	BOOL		m_bReadOnly;					// TRUE = open for read only
	BOOL		m_bTruncate;					// TRUE = create new file, or open 
												// and truncate existing file
	DWORD		m_dwBufferSize;					// size of internal write buffer
	BYTE *		m_pBuffer;						// pointer to internal write buffer

	// following values are initialized in Init()
	HANDLE		m_hFile;						// file handle
	BOOL		m_bMappedFile;					// TRUE = file is mapped
	HANDLE		m_hMappedFile;					// file handle for mapped reads
	DWORD		m_dwMappedFileSize;				// file size of mapped file
	DWORD		m_dwAllocationGranularity;		// system's virtual memory 
												// allocation granularity
	DWORD		m_dwMappedFileOffset;			// file offset for mapped reads
	TCHAR		m_szFile[_MAX_PATH*2];			// file name
	DWORD		m_dwBufferIndex;				// no. of bytes in internal write 
												// buffer
	DWORD		m_dwLastError;					// last file error
	TCHAR		m_szLastError[_MAX_PATH*2];		// last file error string
	DWORD		m_dwSizeLimitBytes;				// max file size in bytes -
												// any writes will be discarded 
												// once this size is reached; 
												// 0 = no limit
	FILESIZELIMITTYPE m_eSizeLimitType;			// action when size limit reached:
												// TRUNCATE = file writes will 
												// be discarded
												// SHRINK = data from beginning of
												// file will be discarded
	BYTE		m_SizeLimitDelimiter[_MAX_PATH]; // delimiter used when limit
												// type is SHRINK
	DWORD		m_dwLimitDelimiterSize;			// limit delimiter size (bytes)
	TCHAR		m_szRolloverLogFile[_MAX_PATH*2]; // rollover log file name

	// added for GetRecord()
	BYTE		m_RecordDelimiter[_MAX_PATH];	// record delimiter use by GetRecord()
	DWORD		m_dwRecordDelimiterSize;		// record delimiter size (bytes)
	BYTE *		m_pReadBuf;						// buffer used for GetRecord()
	DWORD		m_dwReadBufSize;				// size in bytes allocated for m_pReadBuf
	DWORD		m_dwReadBufIndex;				// index position in m_pReadBuf
	DWORD		m_dwReadBufCount;				// size in bytes now contained in m_pReadBuf

	// read/write statistics
	DWORD		m_dwTotalBytesWrittenToFile;
	DWORD		m_dwTotalNumberOfWrites;
	DWORD		m_dwTotalBytesReadFromFile;
	DWORD		m_dwTotalNumberOfReads;
	DWORD		m_dwTotalRecordsRead;
};


#endif //XFILE_H
