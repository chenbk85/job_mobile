#include "stdafx.h"
// XFile.cpp  Version 1.2
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// Description:
//     XFile.cpp implements CXFile, a class for doing file reads and buffered
//     file writes using Win32 file functions.
//
// History
//     Version 1.2 - 2003 May 19
//     - Enabled use on Win9x - removed dependency on MoveFileEx().
//     - Added Prepend() function.
//     - Added GetRecord() function.
//     - Added GetTotalRecordsRead() function
//     - Added Search() function
//     - Added ClearBuffer() function
//     - Fixed SetSizeLimit() and Shrink() parameters to accept
//       byte array rather than string, and also added parameter
//       for byte array size.  This allows sequence of non-text
//       values to be used for delimiter.
//     - Added FILE_FLAG_SEQUENTIAL_SCAN flag to CreateFile,
//       suggested by mattb79.
//     - Added #define XFILE_ERROR ((DWORD)-1)
//     - Added #define XFILE_EOF ((DWORD)-2)
//
//     Version 1.1 - 2003 May 5
//     - Initial public release
//
// Public APIs:
//        NAME                      DESCRIPTION
//     -----------     ------------------------------------------------
//     ClearBuffer()   Clear write buffer
//     Close()         Close an open file, reset class variables
//     Compare()       Binary compare two files
//     Copy()          Copies an existing file to a new file
//     Delete()        Deletes an existing file
//     Flush()         Flushes internal write buffer to disk
//     GetRecord()     Get a record
//     Open()          Open file
//     OpenMapped()    Open file for mapped reads
//     Prepend()       Prepend data to open file
//     Printf()        Write formatted output to open file
//     Read()          Read data from file
//     ReadMapped()    Read data from a mapped file
//     Rename()        Rename existing file
//     Rollover()      Rollover file to new file, continue with empty file
//     Search()        Search file for a byte sequence
//     Seek()          Move file pointer of an open file
//     Shrink()        Shrink an open file when it exceeds a size limit
//     Write()         Write data to file
//     Zip()           Zip a file
//
// Get/Set APIs:
//     GetAllocationGranularity()
//     GetBufferSize()
//     GetFileHandle()
//     GetFileName()
//     GetFullName()
//     GetLastErrorString()
//     GetLastFileError()
//     GetReadOnly()
//     GetRecordDelimiter()
//     GetRecordDelimiterSize()
//     GetRolloverLogFile()
//     GetSizeLimitBytes()
//     GetSizeLimitDelimiter()
//     GetSizeLimitDelimiterSize()
//     GetSizeLimitType()
//     GetTotalBytesReadFromFile()
//     GetTotalBytesWrittenToFile()
//     GetTotalNumberOfReads()
//     GetTotalNumberOfWrites()
//     GetTotalRecordsRead()
//     GetTruncate()
//     GetUnicode()
//     IsBufferEmpty()
//     IsFileAccessible()
//     IsFileOpen()
//     SetRecordDelimiter()
//     SetRolloverLogFile()
//     SetSizeLimit()
//
// Known limitations:
//     1.  File size must be smaller than a DWORD value.
//     2.  Maximum number of Printf() output characters (TCHARs) must be less
//         than MAX_PRINTF_CHARACTERS.
//     3.  When using the mapped file functions, the read buffer MUST be a
//         multiple of system's virtual memory allocation granularity, or
//         the next call to ReadMapped will fail because the file offset
//         will be illegal.  (The first call will succeed because the file
//         offset will be 0).
//     4.  XFile has only been tested with files.
//
// This software is released into the public domain.  You are free to use it
// in any way you like.
//
// This software is provided "as is" with no expressed or implied warranty.
// I accept no liability for any damage or loss of business that this software
// may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <tchar.h>
#include <crtdbg.h>
#include "XFile.h"
#include "XTrace.h"


///////////////////////////////////////////////////////////////////////////////
//
// If you do not need the Zip() function you can uncomment the following line:
//
//#define DO_NOT_INCLUDE_XZIP
//
///////////////////////////////////////////////////////////////////////////////


#ifndef DO_NOT_INCLUDE_XZIP
#include "xzip.h"
#endif


///////////////////////////////////////////////////////////////////////////////
//
// If you do not want TRACE output from XFile.cpp you can
// uncomment the following lines:
//
//#undef  TRACE
//#define TRACE ((void)0)
//
// You can also suppress TRACEERROR output by uncommenting the following
// lines.  This is not recommended:
//
//#undef  TRACEERROR
//#define TRACEERROR ((void)0)
//
///////////////////////////////////////////////////////////////////////////////


#define IsValidFileHandle(x)	((x) && ((x) != INVALID_HANDLE_VALUE))

// turn off warnings from _ASSERTE statements
#pragma warning(disable : 4127)		// conditional expression is constant

// maximum number of characters that can be outputted with Printf()
#define MAX_PRINTF_CHARACTERS (64*1024)

// minimum buffer size
#define MIN_BUFFER_SIZE 4096

// buffer used for file compares - increase size to improve speed
#define COMPARE_BUF_SIZE (64*1024)

// buffer used by Shrink to locate line delimiter - increase or decrease
// size if needed
#define SHRINK_BUF_SIZE (64*1024)

// buffer used by GetRecord - should accommodate at least several lines
#define GETRECORD_BUF_SIZE (64*1024)

// name of default rollover log file
#define ROLLOVER_LOG_FILE _T("_XF Rollover Log.log")

///////////////////////////////////////////////////////////////////////////////
// utility functions used by Search()
static
void *memichr(const void *buf, int c, size_t buf_len);
static
void *memimem(const void *buf,
			  size_t buf_len,
			  const void *byte_sequence,
			  size_t byte_sequence_len);
static
void *memmem(const void *buf,
			 size_t buf_len,
			 const void *byte_sequence,
			 size_t byte_sequence_len);
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
//
// CXFile()
//
// Purpose:     Construct CXFile object
//
// Parameters:  lpszFile  - file name
//              bReadOnly - TRUE = file is readonly
//              bTruncate - TRUE = open existing and truncate, or create new
//              bUnicode  - TRUE = file is Unicode text file
//              dwBufSize - internal buffer size for writes
//
// Returns:     None
//
// Notes:       If ctor is called with a file name, then Open() does not need
//              to be called.
//
CXFile::CXFile(LPCTSTR lpszFile /*= NULL*/,		// file name
			   BOOL bReadOnly /*= FALSE*/,		// TRUE = file is readonly
			   BOOL bTruncate /*= FALSE*/,		// TRUE = open existing and
												// truncate, or create new
												// FALSE = open existing (do not
												// truncate), or create new
			   BOOL bUnicode /*= FALSE*/,		// TRUE = file is Unicode text file,
												// Unicode header will be written
			   DWORD dwBufSize /*= 64 * 1024*/,	// internal buffer size for writes
			   DWORD dwReadBufSize /*= 64 * 1024*/)	// internal buffer size for GetRecord()
{
	TRACE(_T("in CXFile::CXFile\n"));

	Init();

	_ASSERTE(dwBufSize >= MIN_BUFFER_SIZE);
	if (dwBufSize < MIN_BUFFER_SIZE)
	{
		TRACE(_T("Changing buffer size to %d\n"), MIN_BUFFER_SIZE);
		TRACE(_T("Recommended buffer size is at least %d\n"), 64 * 1024);
		dwBufSize = MIN_BUFFER_SIZE;
	}

	m_dwBufferSize              = dwBufSize;
	m_pBuffer                   = new BYTE [m_dwBufferSize];
	m_bReadOnly                 = bReadOnly;
	m_bTruncate                 = bTruncate;
	m_bUnicode                  = bUnicode;
	m_dwSizeLimitBytes          = 0;
	m_eSizeLimitType            = TRUNCATE;
	memset(m_SizeLimitDelimiter, 0, sizeof(m_SizeLimitDelimiter));
#ifdef _UNICODE
	m_SizeLimitDelimiter[0]		= '\r';
	m_SizeLimitDelimiter[1]		= 0;
	m_SizeLimitDelimiter[2]		= '\n';
	m_SizeLimitDelimiter[3]		= 0;
	m_dwLimitDelimiterSize      = 4;
#else
	m_SizeLimitDelimiter[0]		= '\r';
	m_SizeLimitDelimiter[1]		= '\n';
	m_dwLimitDelimiterSize      = 2;
#endif

	// added for GetRecord()
	memset(m_RecordDelimiter, 0, sizeof(m_RecordDelimiter));
#ifdef _UNICODE
	m_RecordDelimiter[0]		= '\r';
	m_RecordDelimiter[1]		= 0;
	m_RecordDelimiter[2]		= '\n';
	m_RecordDelimiter[3]		= 0;
	m_dwRecordDelimiterSize     = 4;
#else
	m_RecordDelimiter[0]		= '\r';
	m_RecordDelimiter[1]		= '\n';
	m_dwRecordDelimiterSize     = 2;
#endif
	m_dwReadBufIndex            = 0;
	m_dwReadBufCount			= 0;

	_ASSERTE(dwReadBufSize >= MIN_BUFFER_SIZE);
	if (dwReadBufSize < MIN_BUFFER_SIZE)
	{
		TRACE(_T("Changing read buffer size to %d\n"), MIN_BUFFER_SIZE);
		TRACE(_T("Recommended read buffer size is at least %d\n"), 64 * 1024);
		dwReadBufSize = MIN_BUFFER_SIZE;
	}

	m_dwReadBufSize             = dwReadBufSize;
	m_pReadBuf                  = new BYTE [m_dwReadBufSize];//m_dwReadBufSize];

	// get system's virtual memory allocation granularity - file offset must
	// be a multiple of this, or MapViewOfFile() will fail
	SYSTEM_INFO si;
	::GetSystemInfo(&si);
	m_dwAllocationGranularity = si.dwAllocationGranularity;
	TRACE(_T("m_dwAllocationGranularity=%d\n"), m_dwAllocationGranularity);

	if (lpszFile && lpszFile[0] != _T('\0'))
	{
		_tcsncpy(m_szFile, lpszFile, _MAX_PATH*2-2);
		m_szFile[_MAX_PATH*2-2] = _T('\0');
		Open(lpszFile, bReadOnly, bTruncate, bUnicode);
	}

	memset(m_szRolloverLogFile, 0, sizeof(m_szRolloverLogFile));
	_tcscpy(m_szRolloverLogFile, ROLLOVER_LOG_FILE);
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CXFile()
//
// Purpose:     Destroy CXFile object.
//
// Parameters:  None
//
// Returns:     None
//
CXFile::~CXFile()
{
	TRACE(_T("in CXFile::~CXFile\n"));

	Close();

	if (m_pBuffer)
		delete [] m_pBuffer;
	m_pBuffer = NULL;

	if (m_pReadBuf)
		delete [] m_pReadBuf;
	m_pReadBuf = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearBuffer()
//
// Purpose:     Clears the write buffer
//
// Parameters:  none
//
// Returns:     BOOL - always returns TRUE
//
// Notes:       ClearBuffer() is useful if you are writing data in pieces,
//              and then at some point you decide you want to discard all 
//              the data you have written, after some previous checkpoint 
//              (Flush()).  ClearBuffer() will only discard data in the 
//              current write buffer - what has already been written to 
//              disk will not be affected.  To accommodate larger amounts of
//              data, the size of the write buffer may be increased.
//
BOOL CXFile::ClearBuffer()
{
	m_dwBufferIndex = 0;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// Close()
//
// Purpose:     Close an open file, reset class variables
//
// Parameters:  none
//
// Returns:     BOOL - always returns TRUE
//
// Notes;       For mapped files, both the file-mapping object and the
//              mapped file will be closed.
//
BOOL CXFile::Close()
{
	TRACE(_T("in CXFile::Close\n"));

	if (IsValidFileHandle(m_hFile))
	{
		Flush();
		if (!m_bReadOnly)
			::FlushFileBuffers(m_hFile);
		if (!::CloseHandle(m_hFile))
		{
			TRACEERROR(_T("ERROR: CloseHandle(m_hFile) failed\n"));
		}

		m_hFile = NULL;

		TRACE(_T("============ Closing file %s ============\n"), m_szFile);
		TRACE(_T("Total reads = %d  Total bytes read = %d\n"),
			m_dwTotalNumberOfReads, m_dwTotalBytesReadFromFile);
		TRACE(_T("Total writes = %d  Total bytes written = %d\n"),
			m_dwTotalNumberOfWrites, m_dwTotalBytesWrittenToFile);
	}

	if (m_bMappedFile && m_hMappedFile)
	{
		if (!::CloseHandle(m_hMappedFile))
		{
			TRACEERROR(_T("ERROR: CloseHandle(m_hMappedFile) failed\n"));
		}
		m_hMappedFile = NULL;
		m_bMappedFile = FALSE;
	}

	Init();

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// Compare()
//
// Purpose:     Binary compare two files
//
// Parameters:  lpszFile1 - file 1 name
//              lpszFile2 - file 2 name
//              pbResult  - pointer to BOOL that receives result of compare;
//                          TRUE = files are identical.  pbResult is valid
//                          only if Compare() returns TRUE.
//
// Returns:     BOOL - TRUE = no problems encountered during compare, see
//                     pbResult for result of compare.  If FALSE returned,
//                     pbResult is meaningless.
//
BOOL CXFile::Compare(LPCTSTR lpszFile1, LPCTSTR lpszFile2, BOOL *pbResult)
{
	TRACE(_T("in CXFile::Compare\n"));

	_ASSERTE(pbResult);
	if (!pbResult)
		return FALSE;

	*pbResult = FALSE;

	BOOL bCompare = FALSE;		// TRUE = files identical
								// FALSE = files not identical
	BOOL bOp = TRUE;			// TRUE = no API failures, compare completed
								// FALSE = file or memory API failed

	_ASSERTE(lpszFile1);
	_ASSERTE(lpszFile1[0] != _T('\0'));

	if (!lpszFile1 || lpszFile1[0] == _T('\0'))
		return FALSE;

	_ASSERTE(lpszFile2);
	_ASSERTE(lpszFile2[0] != _T('\0'));

	if (!lpszFile2 || lpszFile2[0] == _T('\0'))
		return FALSE;

	HANDLE hFile1 = NULL, hFile2 = NULL;

	TRACE(_T("opening '%s'"), lpszFile1);

	// open file 1
	hFile1 = ::CreateFile(lpszFile1,
						  GENERIC_READ,
						  FILE_SHARE_READ | FILE_SHARE_WRITE,
						  NULL,
						  OPEN_EXISTING,
						  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						  NULL);

	m_dwLastError = GetLastError();

	if (hFile1 == INVALID_HANDLE_VALUE)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFile"),
			GetLastErrorString());
		return FALSE;
	}

	TRACE(_T("opening '%s'"), lpszFile2);

	// open file 2
	hFile2 = ::CreateFile(lpszFile2,
						  GENERIC_READ,
						  FILE_SHARE_READ | FILE_SHARE_WRITE,
						  NULL,
						  OPEN_EXISTING,
						  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						  NULL);

	m_dwLastError = GetLastError();

	if (hFile2 == INVALID_HANDLE_VALUE)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFile"),
			GetLastErrorString());
		::CloseHandle(hFile1);
		return FALSE;
	}

	DWORD dwFileSize1 = ::GetFileSize(hFile1, NULL);
	DWORD dwFileSize2 = ::GetFileSize(hFile2, NULL);

	if ((dwFileSize1 != INVALID_FILE_SIZE) && (dwFileSize2 != INVALID_FILE_SIZE))
	{
		// continue if file sizes match
		if (dwFileSize1 == dwFileSize2)
		{
			BYTE * pBuf1 = new BYTE [COMPARE_BUF_SIZE];
			_ASSERTE(pBuf1);

			BYTE * pBuf2 = new BYTE [COMPARE_BUF_SIZE];
			_ASSERTE(pBuf2);

			if (pBuf1 && pBuf2)
			{
				while (dwFileSize1)
				{
					DWORD dwBytesRead1 = 0;
					BOOL bRet1 = ::ReadFile(hFile1,
											(LPVOID) pBuf1,
											COMPARE_BUF_SIZE,
											&dwBytesRead1,
											NULL);

					m_dwLastError = GetLastError();

					if (!bRet1)
					{
						TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("ReadFile"),
							GetLastErrorString());
						bOp = FALSE;
						break;
					}

					DWORD dwBytesRead2 = 0;
					BOOL bRet2 = ::ReadFile(hFile2,
											(LPVOID) pBuf2,
											COMPARE_BUF_SIZE,
											&dwBytesRead2,
											NULL);

					m_dwLastError = GetLastError();

					if (!bRet2)
					{
						TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("ReadFile"),
							GetLastErrorString());
						bOp = FALSE;
						break;
					}

					if (dwBytesRead1 != dwBytesRead2)
					{
						TRACE(_T("Compare failed ==> file Read sizes different\n"));
						break;
					}

					if (dwBytesRead1 == 0)
					{
						// Read ok, but nothing read
						TRACE(_T("Read %s ==> EOF reached.\n"), lpszFile1);
						bCompare = TRUE;
						break;
					}

					if (dwBytesRead2 == 0)
					{
						// Read ok, but nothing read
						TRACE(_T("Read %s ==> EOF reached.\n"), lpszFile2);
						bCompare = TRUE;
						break;
					}

					// do contents match?
					int nCmp = memcmp(pBuf1, pBuf2, dwBytesRead1);
					if (nCmp != 0)
					{
						TRACE(_T("Compare failed ==> file contents different\n"));
						break;
					}

					dwFileSize1 -= dwBytesRead1;

				} // while (dwFileSize1)

				if (dwFileSize1 == 0)
					bCompare = TRUE;

				if (pBuf1)
					delete [] pBuf1;
				if (pBuf2)
					delete [] pBuf2;
			}
			else
			{
				// memory allocation failed
				TRACEERROR(_T("ERROR: memory allocation failure\n"));
				bOp = FALSE;
			}
		}
		else
		{
			TRACE(_T("Compare failed ==> file sizes different\n"));
		}
	}
	else
	{
		// GetFileSize failed
		m_dwLastError = GetLastError();

		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("GetFileSize"),
			GetLastErrorString());
		bOp = FALSE;
	}

	if (IsValidFileHandle(hFile1))
		::CloseHandle(hFile1);
	if (IsValidFileHandle(hFile2))
		::CloseHandle(hFile2);

	*pbResult = bCompare;

	return bOp;
}

///////////////////////////////////////////////////////////////////////////////
//
// Copy()
//
// Purpose:     Copies an existing file to a new file
//
// Parameters:  lpszExistingFileName - name of an existing file
//              lpszNewFileName      - name of new file
//              bFailIfExists        - operation if file exists:
//                                     TRUE = if new file already exists, the
//                                     function fails
//                                     FALSE = if new file already exists, the
//                                     function overwrites the existing file
//                                     and succeeds
//
// Returns:     BOOL - TRUE = success
//
BOOL CXFile::Copy(LPCTSTR lpszExistingFileName,
				  LPCTSTR lpszNewFileName,
				  BOOL bFailIfExists /*= TRUE*/)
{
	TRACE(_T("in CXFile::Copy: '%s' ==> '%s'\n"),
		lpszExistingFileName, lpszNewFileName);

	BOOL bRet = ::CopyFile(lpszExistingFileName, lpszNewFileName, bFailIfExists);

	m_dwLastError = GetLastError();

	if (!bRet)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CopyFile"),
			GetLastErrorString());
	}

	return bRet;
}

///////////////////////////////////////////////////////////////////////////////
//
// Delete()
//
// Purpose:     Deletes an existing file
//
// Parameters:  lpszFile - file name
//
// Returns:     BOOL - TRUE = success
//
BOOL CXFile::Delete(LPCTSTR lpszFile)
{
	TRACE(_T("in CXFile::Delete: '%s'\n"), lpszFile);

	BOOL bRet = ::DeleteFile(lpszFile);

	m_dwLastError = GetLastError();

	if (!bRet)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("DeleteFile"),
			GetLastErrorString());
	}

	return bRet;
}

///////////////////////////////////////////////////////////////////////////////
//
// FillReadBuf()
//
// Purpose:     Read more data into the read buffer.  If there is still some
//              data left in read buffer, it will be moved to the beginning
//              of the buffer.
//
// Parameters:  none
//
// Returns:     DWORD - number of bytes added to read buffer, or (DWORD)-1 if
//                      Read() fails
//
DWORD CXFile::FillReadBuf()
{
	TRACE(_T("in CXFile::FillReadBuf\n"));

	if (m_dwReadBufIndex < m_dwReadBufCount)
	{
		// there's something in buffer, move to beginning

		// is data already at beginning?
		if (m_dwReadBufIndex)
		{
			TRACE(_T("moving buffer =====\n"));
			memmove(m_pReadBuf, &m_pReadBuf[m_dwReadBufIndex],
				m_dwReadBufCount-m_dwReadBufIndex);

			m_dwReadBufCount = m_dwReadBufCount - m_dwReadBufIndex;
			m_dwReadBufIndex = 0;
		}
	}
	else
	{
		m_dwReadBufIndex = 0;
		m_dwReadBufCount = 0;
	}

	DWORD dwBytesRead = Read((LPTSTR)&m_pReadBuf[m_dwReadBufCount],
		m_dwReadBufSize - m_dwReadBufCount);

	if (dwBytesRead == XFILE_ERROR)
	{
		TRACE(_T("ERROR:  Read failed\n"));
		return XFILE_ERROR;
	}

	TRACE(_T("read %d bytes\n"), dwBytesRead);

	m_dwReadBufCount += dwBytesRead;

	return dwBytesRead;
}

///////////////////////////////////////////////////////////////////////////////
//
// FindDelimiter()
//
// Purpose:     Find the next delimiter in the file.  Called by GetRecord().
//
// Parameters:  none
//
// Returns:     DWORD - index within buffer of start of delimiter, or 0 if
//                      delimiter not found
//
DWORD CXFile::FindDelimiter()
{
	TRACE(_T("in CXFile::FindDelimiter\n"));

	DWORD dwIndex = m_dwReadBufIndex;

	// will delimiter fit in what's left in buffer?
	if ((dwIndex + m_dwRecordDelimiterSize) > m_dwReadBufCount)	//5.13
	{
		TRACE(_T("won't fit\n"));
		return 0;
	}

	BOOL bDelimiterFound = FALSE;

	while (dwIndex < m_dwReadBufCount)
	{
		BYTE b = m_pReadBuf[dwIndex];

		// could this be a delimiter?
		if (b == m_RecordDelimiter[0])
		{
			bDelimiterFound = TRUE;

			// loop to check rest of delimiter string
			for (UINT i = 1; i < m_dwRecordDelimiterSize; i++)
			{
				if (m_pReadBuf[i+dwIndex] != m_RecordDelimiter[i])
				{
					bDelimiterFound = FALSE;
					break;
				}
			}

			if (bDelimiterFound)
			{
				TRACE(_T("delimiter found\n"));
				break;
		}
		}
		dwIndex++;
	}

	if (!bDelimiterFound)
		dwIndex = 0;

	TRACE(_T("m_dwReadBufCount = %d\n"), m_dwReadBufCount);
	TRACE(_T("m_dwReadBufIndex = %d\n"), m_dwReadBufIndex);
	TRACE(_T("FindDelimiter returning %d\n"), dwIndex);

	return dwIndex;
}

///////////////////////////////////////////////////////////////////////////////
//
// Flush()
//
// Purpose:     Flushes internal write buffer to an open file.  Flush() is
//              called automatically when file is closed.
//
// Parameters:  none
//
// Returns:     DWORD - number of bytes written, or (DWORD)-1 if error
//
DWORD CXFile::Flush()
{
	TRACE(_T("in CXFile::Flush\n"));

	_ASSERTE(IsValidFileHandle(m_hFile));
	if (!IsValidFileHandle(m_hFile))
		return XFILE_ERROR;

	if (m_bReadOnly)
		return 0;

	if (m_bMappedFile)
		return 0;

	if (IsBufferEmpty())
		return 0;

	BOOL bRet = FALSE;
	DWORD dwBytesWritten = 0;
	DWORD dwIndex = m_dwBufferIndex;
	m_dwBufferIndex = 0;	// ensure that index is reset, even if error occurs

	DWORD dwCurrentFilePosition = Seek(0, FILE_CURRENT);
	if (dwCurrentFilePosition == XFILE_ERROR)
		return 0;

	// is this Unicode (UTF-16) text file?
	if (m_bUnicode)
	{
		if (dwCurrentFilePosition == 0)
		{
			// at beginning of file, so write Unicode header bytes
			bRet = WriteUnicodeHeader(m_hFile);

			if (!bRet)
				return XFILE_ERROR;
		}
	}

	DWORD dwFileSize = ::GetFileSize(m_hFile, NULL);

	m_dwLastError = GetLastError();

	if (dwFileSize == INVALID_FILE_SIZE)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("GetFileSize"),
			GetLastErrorString());
		return 0;
	}

	// is there anything to write?
	if (dwIndex)
	{
		// has file size limit been reached?

		BOOL bLimitReached = FALSE;

		if ((m_dwSizeLimitBytes != 0) &&				// must have a limit set
			(dwFileSize >= m_dwSizeLimitBytes) &&		// must be over the limit
			(dwCurrentFilePosition >= dwFileSize))		// must be writing at eof
		{
			// file size limit has been reached

			TRACE(_T("size limit reached:  m_dwSizeLimitBytes=%d  dwFileSize=%d =====\n"),
				m_dwSizeLimitBytes, dwFileSize);

			bLimitReached = TRUE;

			if (m_eSizeLimitType == TRUNCATE)
			{
				TRACE(_T("WARNING: write discarded, limit of %d bytes reached\n"),
					m_dwSizeLimitBytes);
			}
			else // SHRINK
			{
				// shrink by discarding first half of file
				DWORD dwResult = Shrink(m_dwSizeLimitBytes-2,
										m_dwSizeLimitBytes/2,
										m_SizeLimitDelimiter,
										m_dwLimitDelimiterSize);

				if ((dwResult != XFILE_ERROR) && (dwResult > 0))
				{
					bLimitReached = FALSE;
				}
				else
				{
					TRACEERROR(_T("ERROR:  Shrink() failed\n"));
				}
			}
		}

		if (!bLimitReached)
		{
			_ASSERTE(m_pBuffer);

			bRet = ::WriteFile(m_hFile,
							   m_pBuffer,
							   dwIndex,
							   &dwBytesWritten,
							   NULL);

			m_dwLastError = GetLastError();

			if (!bRet)
			{
				TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("WriteFile"),
					GetLastErrorString());
				return XFILE_ERROR;
			}

			// write succeeded
			m_dwTotalNumberOfWrites++;
			m_dwTotalBytesWrittenToFile += dwBytesWritten;
		}
	}

	TRACE(_T("dwBytesWritten=%d =====\n"), dwBytesWritten);

	return dwBytesWritten;
}

///////////////////////////////////////////////////////////////////////////////
//
// GenerateRolloverLogFile()
//
// Purpose:     Create the rollover log file (if necessary) and then write an
//              entry.  If the file does not exist, it will be created in the
//              same directory as lpszFile.  The name of the log file is set
//              by default to ROLLOVER_LOG_FILE, but can be changed by
//              SetRolloverLogFile().  If the file does exist, it will be
//              appended to.
//
// Parameters:  lpszFile - file being rolled over
//
// Returns:     BOOL - TRUE = success
//
// Notes:       Each entry in the rollover log file has the format
//                <file> : created 2003/04/27 00:01:07, rolled over 2003/04/28 00:01:03
//
BOOL CXFile::GenerateRolloverLogFile(LPCTSTR lpszFile)
{
	TRACE(_T("in CXFile::GenerateRolloverLogFile\n"));

	BOOL bRet = TRUE;

	_ASSERTE(lpszFile);
	_ASSERTE(lpszFile[0] != _T('\0'));

	if (!lpszFile || lpszFile[0] == _T('\0'))
	{
		TRACEERROR(_T("ERROR:  lpszFile is NULL\n"));
		return FALSE;
	}

	// get full name of file to be rolled, incl. drive & dir
	TCHAR * lpszFullPathName = GetFullName(lpszFile);
	if (!lpszFullPathName)
		return FALSE;

	// save original file name
	TCHAR szOriginalFile[_MAX_PATH*2];
	memset(szOriginalFile, 0, _MAX_PATH*2*sizeof(TCHAR));
	_tcscpy(szOriginalFile, lpszFullPathName);

	delete [] lpszFullPathName;
	lpszFullPathName = NULL;

	WIN32_FILE_ATTRIBUTE_DATA fad;

	// get file attributes
	bRet = ::GetFileAttributesEx(szOriginalFile,		// file
								 GetFileExInfoStandard,	// attribute class
								 (LPVOID) &fad);		// attribute information

	m_dwLastError = GetLastError();

	if (!bRet)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("GetFileAttributesEx"),
			GetLastErrorString());
		return FALSE;
	}

	// get local time of file creation
	FILETIME localft;
	::FileTimeToLocalFileTime(&fad.ftCreationTime, &localft);

	// file creation SYSTEMTIME
	SYSTEMTIME file_systime;
	::FileTimeToSystemTime(&localft, &file_systime);

	// local SYSTEMTIME
	SYSTEMTIME systime;
	::GetLocalTime(&systime);

	TCHAR szLogRecord[_MAX_PATH*2];
	_tcscpy(szLogRecord, szOriginalFile);

	int n = _tcslen(szLogRecord);

	n += _stprintf(&szLogRecord[n], _T(" : created %04d/%02d/%02d %02d:%02d:%02d,"),
		file_systime.wYear, file_systime.wMonth, file_systime.wDay,
		file_systime.wHour, file_systime.wMinute, file_systime.wSecond);

	n += _stprintf(&szLogRecord[n], _T(" rolled over %04d/%02d/%02d %02d:%02d:%02d\r\n"),
		systime.wYear, systime.wMonth, systime.wDay,
		systime.wHour, systime.wMinute, systime.wSecond);

	TRACE(_T("'%s'"), szLogRecord);

	// open/create log file
	TCHAR szLogFile[_MAX_PATH*2];

	_tcscpy(szLogFile, m_szRolloverLogFile);

	// does log file name include path?
	TCHAR *cp = _tcsrchr(szLogFile, _T('\\'));
	if (cp == NULL)
	{
		// no path - use path from rolled-over file
		_tcscpy(szLogFile, szOriginalFile);

		cp = _tcsrchr(szLogFile, _T('\\'));
		if (cp == NULL)
		{
			// no path, use current directory
			memset(szLogFile, 0, _MAX_PATH*2*sizeof(TCHAR));
			::GetCurrentDirectory(_MAX_PATH*2-2, szLogFile);
		}
		else
		{
			*cp = _T('\0');
		}

		_tcscat(szLogFile, _T("\\"));
		_tcscat(szLogFile, m_szRolloverLogFile);
	}

	TRACE(_T("rollover log file = '%s'\n"), szLogFile);

	// open the log file
	HANDLE hLogFile = NULL;
	hLogFile = ::CreateFile(szLogFile,						// file name
							GENERIC_READ | GENERIC_WRITE,	// open for read/write
							FILE_SHARE_READ,				// share for reading
							NULL,							// no security
							OPEN_ALWAYS,					// open existing or create
							FILE_ATTRIBUTE_NORMAL,			// normal file
							NULL);							// no attr. template

	m_dwLastError = GetLastError();

	if (!IsValidFileHandle(hLogFile))
	{
		TRACEERROR(_T("ERROR: failed to open log file '%s'\n"), szLogFile);
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFile"),
			GetLastErrorString());
		return FALSE;
	}

	// try to go to end of file
	DWORD dwPos = ::SetFilePointer(hLogFile, 0, NULL, FILE_END);

	m_dwLastError = GetLastError();

	DWORD dwBytesWritten = 0;

	if (dwPos == INVALID_SET_FILE_POINTER)	//0xFFFFFFFF)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("SetFilePointer"),
			GetLastErrorString());
		bRet = FALSE;
	}
	else
	{
		bRet = TRUE;

		if (dwPos == 0)
		{
			// at beginning of file, so write Unicode header bytes
#ifdef _UNICODE
			bRet = WriteUnicodeHeader(hLogFile);
#endif
		}

		if (bRet)
		{
			// write log entry - if this is a Unicode app,
			// entry will be written as Unicode UTF-16
			bRet = ::WriteFile(hLogFile,
							   szLogRecord,
							   n * sizeof(TCHAR),
							   &dwBytesWritten,
							   NULL);
		}

		if (bRet)
			::FlushFileBuffers(hLogFile);

		m_dwLastError = GetLastError();

		if (!bRet)
		{
			TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("WriteFile"),
				GetLastErrorString());
		}
	}

	::CloseHandle(hLogFile);

	return bRet;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFullName()
//
// Purpose:     Retrieves the full path and file name of a specified file
//
// Parameters:  lpszFile - file name to return full path for
//
// Returns:     LPTSTR - If non-NULL, pointer to buffer that contains the full
//                       path name for the file.  This buffer must be freed with
//                       "delete [] pBuf".  If null, an error occurred.
//
LPTSTR CXFile::GetFullName(LPCTSTR lpszFile)
{
	TCHAR * lpszFullPathName = NULL;

	DWORD dwPathLen = 0;
	lpszFullPathName = new TCHAR [_MAX_PATH*2];		// this is usually big enough
	LPTSTR lpFilePart;
	dwPathLen = ::GetFullPathName(lpszFile,			// file name
								  _MAX_PATH*2-2,	// size of path buffer
								  lpszFullPathName,	// path buffer
								  &lpFilePart);		// address of file name in path

	m_dwLastError = GetLastError();

	if (dwPathLen > (_MAX_PATH*2-2))
	{
		// need bigger buffer - try again

		delete [] lpszFullPathName;
		lpszFullPathName = new TCHAR [dwPathLen + 16];

		dwPathLen = ::GetFullPathName(lpszFile,			// file name
									  dwPathLen+2,		// size of path buffer
									  lpszFullPathName,	// path buffer
									  &lpFilePart);		// address of file name in path

		m_dwLastError = GetLastError();
	}

	if (dwPathLen == 0)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("GetFullPathName"),
			GetLastErrorString());
		if (lpszFullPathName)
			delete [] lpszFullPathName;
		lpszFullPathName = NULL;
	}

	TRACE(_T("lpszFullPathName='%s'\n"), lpszFullPathName);

	return 	lpszFullPathName;
}


///////////////////////////////////////////////////////////////////////////////
//
// GetLastErrorString()
//
// Purpose:     Return string for last GetLastError() error code
//
// Parameters:  none
//
// Returns:     LPTSTR - error string for error code
//
// Notes:       GetLastErrorString uses error code previously stored
//              in m_dwLastError.
//
LPTSTR CXFile::GetLastErrorString()
{
	memset(m_szLastError, 0, sizeof(m_szLastError));

	LPTSTR lpMsgBuf = NULL;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		m_dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0,
		NULL);

	if (lpMsgBuf)
	{
		int n = _tcslen(lpMsgBuf);

		// eliminate trailing newlines and linefeeds
		if (lpMsgBuf[n-1] == _T('\r') || lpMsgBuf[n-1] == _T('\n'))
			lpMsgBuf[n-1] = _T('\0');
		if (lpMsgBuf[n-2] == _T('\r') || lpMsgBuf[n-2] == _T('\n'))
			lpMsgBuf[n-2] = _T('\0');

		_sntprintf(m_szLastError, (sizeof(m_szLastError)/sizeof(TCHAR)) - 2,
			_T("%s [%u] "), lpMsgBuf, m_dwLastError);

		LocalFree(lpMsgBuf);
	}

	return m_szLastError;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetRecord()
//
// Purpose:     Read byte data from an open file.  The file may have been
//              opened either with Open() or OpenMapped(). Up to dwBytes of
//              data are read into buffer specified by lpszBuffer, or until
//              the record delimiter is found.  See SetRecordDelimiter().
//              Each successive GetRecord() will return the next record,
//              until 0 is returned at the end of file.
//
// Parameters:  lpszBuffer - pointer to byte buffer that byte data will be
//                           read into
//              dwBytes    - size of buffer in bytes
//
// Returns:     DWORD - number of bytes read, or (DWORD)-1 if error; EOF found
//                      if (DWORD)-2 returned.
//
// Notes:       GetRecord() starts reading from current file position.  Use
//              of Seek() will interfere with the sequential reading of data.
//
//              GetRecord() may be used on both text and binary files.  The
//              record delimiter (specified by SetRecordDelimiter()) will be
//              searched for as a sequence of bytes, regardless of whether
//              the file is ANSI text, Unicode, or binary.
//
DWORD CXFile::GetRecord(LPTSTR lpszBuffer, DWORD dwBytes)
{
	DWORD dwBytesReturned = 0;

	_ASSERTE(IsValidFileHandle(m_hFile));
	if (!IsValidFileHandle(m_hFile))
		return XFILE_ERROR;

	_ASSERTE(lpszBuffer);
	if (!lpszBuffer)
		return XFILE_ERROR;

	if (dwBytes == 0)
		return 0;

	_ASSERTE(!IsBadWritePtr(lpszBuffer, dwBytes));
	if (IsBadWritePtr(lpszBuffer, dwBytes))
	{
		TRACEERROR(_T("ERROR: bad pointer\n"));
		return XFILE_ERROR;
	}

	memset(lpszBuffer, 0, dwBytes);

	DWORD dwBytesRead = 0;

	if (m_dwReadBufIndex >= m_dwReadBufCount)
	{
		// refill buffer
		dwBytesRead = FillReadBuf();

		if (dwBytesRead == XFILE_ERROR)
			return XFILE_ERROR;

		if (dwBytesRead == 0)
			return XFILE_EOF;
	}

	// there should be some text in buffer now -
	// m_dwReadBufIndex and m_dwReadBufCount have
	// been set by FillReadBuf()

	// loop to get record
	while (m_dwReadBufIndex < m_dwReadBufCount)
	{
		DWORD dwIndex = FindDelimiter();
		TRACE(_T("FindDelimiter returned %d\n"), dwIndex);

		if (dwIndex)
		{
			DWORD dwRecordLength = dwIndex - m_dwReadBufIndex;

			if (dwRecordLength == 0)
			{
				// zero-length record (probably caused by blank line)
				// return record size of 0 bytes

				m_dwReadBufIndex = dwIndex + m_dwRecordDelimiterSize;
				m_dwTotalRecordsRead++;
				return 0;
			}
			else
			{
				// found delimiter, and record is not empty

				DWORD dwNewIndex = dwIndex + m_dwRecordDelimiterSize;

				// will record fit in caller's buffer?
				if (dwRecordLength > dwBytes)
				{
					dwRecordLength = dwBytes;
					dwNewIndex = m_dwReadBufIndex + dwRecordLength;
				}

				memcpy(lpszBuffer, &m_pReadBuf[m_dwReadBufIndex], dwRecordLength);

				m_dwReadBufIndex = dwNewIndex;
				dwBytesReturned = dwRecordLength;

				break;
			}
		}
		else	// delimiter not found
		{
			TRACE(_T("delimiter not found\n"));
			dwBytesRead = FillReadBuf();
			TRACE(_T("FillReadBuf returned %d\n"), dwBytesRead);

			if (dwBytesRead == XFILE_ERROR)
				return XFILE_ERROR;

			if (dwBytesRead == 0)
			{
				// nothing more to read, probably at eof

				TRACE(_T("m_dwReadBufCount = %d\n"), m_dwReadBufCount);
				TRACE(_T("m_dwReadBufIndex = %d\n"), m_dwReadBufIndex);

				DWORD dwResult = OutputPartialRecord(lpszBuffer, dwBytes);
				if (dwResult == 0)
					return XFILE_EOF;
				m_dwTotalRecordsRead++;
				return dwResult;
			}

			dwIndex = FindDelimiter();

			if (dwIndex == 0)
			{
				// delimiter not found, may be at eof

				DWORD dwResult = OutputPartialRecord(lpszBuffer, dwBytes);
				if (dwResult == 0)
					return XFILE_EOF;
				m_dwTotalRecordsRead++;
				return dwResult;
			}
		}

	}  // while (m_dwReadBufIndex < m_dwReadBufCount)

	m_dwTotalRecordsRead++;

	return dwBytesReturned;
}

///////////////////////////////////////////////////////////////////////////////
//
// Init()
//
// Purpose:     Initializes per-file class variables
//
// Parameters:  None
//
// Returns:     None
//
void CXFile::Init()
{
	m_hFile                     = NULL;
	m_hMappedFile               = NULL;
	m_bMappedFile               = FALSE;
	m_dwMappedFileOffset        = 0;
	m_dwMappedFileSize          = 0;
	m_dwBufferIndex             = 0;
	m_dwTotalBytesWrittenToFile = 0;
	m_dwTotalNumberOfWrites     = 0;
	m_dwTotalBytesReadFromFile  = 0;
	m_dwTotalNumberOfReads      = 0;
	m_dwTotalRecordsRead        = 0;
	m_dwLastError               = 0;
	m_szFile[0]                 = _T('\0');
	m_szLastError[0]            = _T('\0');
}

///////////////////////////////////////////////////////////////////////////////
//
// IsFileAccessible()
//
// Purpose:     Verify that a file is accessible
//
// Parameters:  lpszFile - file name
//              dwAccess - desired access; this parameter can be any
//                         combination of the following values:
//                             GENERIC_READ
//                             GENERIC_WRITE
//                         A minimum access of GENERIC_READ is used
//                         if none is specified.
//
// Returns:     BOOL - TRUE = file is accessible with specified access
//
// Notes:       static member function.
//
BOOL CXFile::IsFileAccessible(LPCTSTR lpszFile, DWORD dwAccess /*= GENERIC_READ*/)
{
	int mode = 04;
	if (dwAccess & GENERIC_WRITE)
		mode |= 02;

	return (_taccess(lpszFile, mode) == 0);
}

///////////////////////////////////////////////////////////////////////////////
//
// Open()
//
// Purpose:     Open file
//
// Parameters:  lpszFile  - file name
//              bReadOnly - TRUE  = file will be opened for read only
//                          FALSE = open file for reading and writing
//              bTruncate - TRUE  = open existing and truncate, or create new
//                          FALSE = open existing (do not truncate)
//                                  or create new
//              bUnicode  - TRUE  = file is Unicode text file, write Unicode
//                                  header (Byte Order Mark, or BOM)
//                          FALSE = do not write Unicode header
//
// Returns:     BOOL - TRUE = success
//
// Notes:       Some text editors (e.g., TextPad) and other applications write
//              a Unicode header of two bytes (0xFF followed by 0xFE).  However,
//              TextPad seems to have no problem figuring out that the file
//              contains UTF-16 even if the header is not present.  You should
//              test this with your application to see if it makes any
//              difference.  In particular, you should verify that the presence
//              of a BOM does not interfere with your app's read operations.
//
BOOL CXFile::Open(LPCTSTR lpszFile,
				  BOOL bReadOnly /*= FALSE*/,
				  BOOL bTruncate /*= FALSE*/,
				  BOOL bUnicode /*= FALSE*/)
{
	TRACE(_T("in CXFile::Open\n"));

	_ASSERTE(lpszFile);
	_ASSERTE(lpszFile[0] != _T('\0'));

	if (!lpszFile || lpszFile[0] == _T('\0'))
		return FALSE;

	Close();		// close file if open

	_tcsncpy(m_szFile, lpszFile, _MAX_PATH*2-2);
	m_szFile[_MAX_PATH*2-2] = _T('\0');

	TRACE(_T("opening '%s'"), m_szFile);

	m_bReadOnly = bReadOnly;
	m_bTruncate = bTruncate;
	m_bUnicode  = bUnicode;

	TRACE(_T("m_bReadOnly=%d  m_bTruncate=%d  m_bUnicode=%d\n"),
		m_bReadOnly, m_bTruncate, m_bUnicode);

	DWORD dwDesiredAccess       = m_bReadOnly ? GENERIC_READ : GENERIC_READ | GENERIC_WRITE;
	DWORD dwCreationDisposition = m_bTruncate ? CREATE_ALWAYS : OPEN_ALWAYS;
	DWORD dwFlagsAndAttributes  = m_bReadOnly ? FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN :
												FILE_ATTRIBUTE_NORMAL;

	// open existing or create new
	m_hFile = ::CreateFile(m_szFile,
						   dwDesiredAccess,
						   FILE_SHARE_READ | FILE_SHARE_WRITE,
						   NULL,
						   dwCreationDisposition,
						   dwFlagsAndAttributes,
						   NULL);

	m_dwLastError = GetLastError();

	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		TRACEERROR(_T("ERROR:  failed to open '%s'\n"), m_szFile);
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFile"),
			GetLastErrorString());
		m_hFile = NULL;
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenMapped()
//
// Purpose:     Open file for mapped reads
//
// Parameters:  lpszFile  - file name
//
// Returns:     BOOL - TRUE = success
//
BOOL CXFile::OpenMapped(LPCTSTR lpszFile)
{
	TRACE(_T("in CXFile::OpenMapped\n"));

	_ASSERTE(lpszFile);
	_ASSERTE(lpszFile[0] != _T('\0'));

	if (!lpszFile || lpszFile[0] == _T('\0'))
		return FALSE;

	Close();		// close file if open

	_tcsncpy(m_szFile, lpszFile, _MAX_PATH*2-2);
	m_szFile[_MAX_PATH*2-2] = _T('\0');

	TRACE(_T("opening '%s'"), m_szFile);

	m_bReadOnly = TRUE;
	m_bTruncate = FALSE;
	m_bUnicode  = FALSE;

	// open the input file
	m_hFile = ::CreateFile(m_szFile,
						   GENERIC_READ,
						   FILE_SHARE_READ,
						   NULL,
						   OPEN_EXISTING,
						   FILE_ATTRIBUTE_READONLY  | FILE_FLAG_SEQUENTIAL_SCAN,
						   NULL);

	m_dwLastError = GetLastError();

	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		TRACEERROR(_T("ERROR:  failed to open '%s'\n"), m_szFile);
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFile"),
			GetLastErrorString());
		m_hFile = NULL;
		return FALSE;
	}

	// get the file size
	m_dwMappedFileSize = ::GetFileSize(m_hFile, NULL);

	m_dwLastError = GetLastError();

	if (m_dwMappedFileSize == INVALID_FILE_SIZE)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("GetFileSize"),
			GetLastErrorString());
		Close();
		m_hFile = NULL;
		m_dwMappedFileSize = 0;
		return FALSE;
	}

	TRACE(_T("m_dwMappedFileSize = %d\n"), m_dwMappedFileSize);

	// create the file mapping
	m_hMappedFile = ::CreateFileMapping(m_hFile,
										NULL,
										PAGE_READONLY,
										0,
										0,
										NULL);

	m_dwLastError = GetLastError();

	if (m_hMappedFile == NULL)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFileMapping"),
			GetLastErrorString());
		Close();
		m_hFile = NULL;
		return FALSE;
	}

	m_dwMappedFileOffset = 0;
	m_bMappedFile = TRUE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// OutputPartialRecord()
//
// Purpose:     Copy byte data into caller's buffer.  No delimiter was
//              found, so as much of the buffer will be transferred as
//              will fit.
//
// Parameters:  lpszBuffer - pointer to byte buffer that byte data will be
//                           read into
//              dwBytes    - size of buffer in bytes
//
// Returns:     DWORD - number of bytes copied, or 0
//
DWORD CXFile::OutputPartialRecord(LPTSTR lpszBuffer, DWORD dwBytes)
{
	DWORD dwBytesReturned = 0;

	if (m_dwReadBufCount)
	{
		dwBytesReturned = m_dwReadBufCount - m_dwReadBufIndex;

		if (dwBytesReturned > dwBytes)
			dwBytesReturned = dwBytes;

		if (dwBytesReturned)
			memcpy(lpszBuffer, &m_pReadBuf[m_dwReadBufIndex], dwBytesReturned);

		m_dwReadBufCount -= dwBytesReturned;
		m_dwReadBufIndex += dwBytesReturned;

	}

	TRACE(_T("m_dwReadBufCount = %d\n"), m_dwReadBufCount);
	TRACE(_T("m_dwReadBufIndex = %d\n"), m_dwReadBufIndex);
	TRACE(_T("OutputPartialRecord returning %d =====\n"), dwBytesReturned);

	return dwBytesReturned;
}

///////////////////////////////////////////////////////////////////////////////
//
// Prepend()
//
// Purpose:     Write byte data to the beginning of an open file.  Data is
//              written to beginning of file, before the data that was in the
//              file.  The data that was in the file is preserved and begins
//              immediately after the new data.
//
// Parameters:  lpszBuffer - pointer to byte buffer containing data
//              dwBytes    - number of bytes in buffer
//
// Returns:     DWORD - number of bytes written, or (DWORD)-1 if error
//
DWORD CXFile::Prepend(LPTSTR lpszBuffer, DWORD dwBytes)
{
	TRACE(_T("in CXFile::Prepend\n"));

	if (!IsFileOpen())
		return XFILE_ERROR;

	if (m_bReadOnly)
		return XFILE_ERROR;

	if (dwBytes == 0)
		return 0;

	_ASSERTE(lpszBuffer);
	if (!lpszBuffer)
		return XFILE_ERROR;

	_ASSERTE(!IsBadReadPtr(lpszBuffer, dwBytes));
	if (IsBadReadPtr(lpszBuffer, dwBytes))
	{
		TRACEERROR(_T("ERROR: bad pointer\n"));
		return XFILE_ERROR;
	}

	// save file attributes for Open
	DWORD dwTotalBytesRead      = GetTotalBytesReadFromFile();
	DWORD dwTotalBytesWritten   = GetTotalBytesWrittenToFile();
	DWORD dwTotalNumberOfReads  = GetTotalNumberOfReads();
	DWORD dwTotalNumberOfWrites = GetTotalNumberOfWrites();

	BOOL bSavedUnicode           = GetUnicode();
	BOOL bSavedReadOnly          = GetReadOnly();
	DWORD dwLimitBytes           = GetSizeLimitBytes();
	FILESIZELIMITTYPE eLimitType = GetSizeLimitType();
	BYTE SizeLimitDelimiter[sizeof(m_SizeLimitDelimiter)];
	memcpy(SizeLimitDelimiter, GetSizeLimitDelimiter(), sizeof(m_SizeLimitDelimiter));
	DWORD dwLimitDelimiterSize = m_dwLimitDelimiterSize;

	// save original file name
	TCHAR szOriginalFile[_MAX_PATH*2];
	_tcscpy(szOriginalFile, m_szFile);

	Close();

	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = ::CreateFile(szOriginalFile,
						 GENERIC_READ | GENERIC_WRITE,
						 0,
						 NULL,
						 OPEN_ALWAYS,
						 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						 NULL);

	m_dwLastError = GetLastError();

	if (hFile == INVALID_HANDLE_VALUE)
	{
		TRACEERROR(_T("ERROR:  failed to open '%s'\n"), m_szFile);
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFile"),
			GetLastErrorString());
		return XFILE_ERROR;
	}

	// get the file size
	DWORD dwFileSize = ::GetFileSize(hFile, NULL);

	m_dwLastError = GetLastError();

	if (dwFileSize == INVALID_FILE_SIZE)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("GetFileSize"),
			GetLastErrorString());
		::CloseHandle(hFile);
		return XFILE_ERROR;
	}

	TRACE(_T("dwFileSize = %d\n"), dwFileSize);

	// Create a file mapping object that is the current size of
	// the  file plus the length of the additional data that
	// we're about to insert into it
	HANDLE hMappedFile = NULL;
	hMappedFile = ::CreateFileMapping(hFile,
									  NULL,
									  PAGE_READWRITE,
									  0,
									  dwBytes + dwFileSize,
									  NULL);

	m_dwLastError = GetLastError();

	if (hMappedFile == NULL)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFileMapping"),
			GetLastErrorString());
		::CloseHandle(hFile);
		return XFILE_ERROR;
	}

	LPBYTE lpMapAddress = (LPBYTE) ::MapViewOfFile(hMappedFile,		// handle to file-mapping object
											FILE_MAP_WRITE,			// access mode
											0,						// high-order DWORD of offset
											0,						// low-order DWORD of offset
											0);						// number of bytes to map

	m_dwLastError = GetLastError();

	if (lpMapAddress == NULL)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("MapViewOfFile"),
			GetLastErrorString());
		::CloseHandle(hMappedFile);
		::CloseHandle(hFile);
		return XFILE_ERROR;
	}

	// move everything down by amount of insert
	memmove(lpMapAddress + dwBytes, lpMapAddress, dwFileSize);

	LPBYTE lpSrc = (LPBYTE) lpszBuffer;

	// copy new data to beginning of file
	memcpy(lpMapAddress, lpSrc, dwBytes);

	BOOL bRet = ::UnmapViewOfFile(lpMapAddress);

	m_dwLastError = GetLastError();

	if (!bRet)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("UnmapViewOfFile"),
			GetLastErrorString());
	}

	::CloseHandle(hMappedFile);

	// set new eof
	DWORD dwFilePointer = ::SetFilePointer(hFile, dwBytes + dwFileSize, NULL, FILE_BEGIN);

	m_dwLastError = GetLastError();

	BOOL bSuccess = TRUE;

	if (dwFilePointer == INVALID_SET_FILE_POINTER)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("SetFilePointer"),
			GetLastErrorString());
		bSuccess = FALSE;
	}

	if (bSuccess)
	{
		bRet = ::SetEndOfFile(hFile);

		m_dwLastError = GetLastError();

		if (!bRet)
		{
			TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("SetEndOfFile"),
				GetLastErrorString());
			bSuccess = FALSE;
		}
	}

	::CloseHandle(hFile);

	// open new file
	if (bSuccess)
	{
		bSuccess = Open(szOriginalFile,
						bSavedReadOnly,
						FALSE,
						bSavedUnicode);

		// restore statistics
		m_dwTotalBytesReadFromFile  = dwTotalBytesRead;
		m_dwTotalBytesWrittenToFile = dwTotalBytesWritten + dwBytes;
		m_dwTotalNumberOfReads      = dwTotalNumberOfReads;
		m_dwTotalNumberOfWrites     = dwTotalNumberOfWrites + 1;

		// restore size limit
		SetSizeLimit(dwLimitBytes, eLimitType, SizeLimitDelimiter, dwLimitDelimiterSize);
	}

	if (!bSuccess)
	{
		dwBytes = XFILE_ERROR;
	}

	return dwBytes;
}

///////////////////////////////////////////////////////////////////////////////
//
// Printf()
//
// Purpose:     Write printf-formatted output to an open file
//
// Parameters:  lpszFmt - format specification (see printf)
//              ...     - variable number of args
//
// Returns:     int - number of characters actually written, or negative
//                    value if error occurs
//
// Notes:       A maximum of MAX_PRINTF_CHARACTERS characters can be
//              outputted.
//
int CXFile::Printf(LPCTSTR lpszFmt, ...)
{
	_ASSERTE(lpszFmt);
	_ASSERTE(lpszFmt[0] != _T('\0'));

	if (!lpszFmt || lpszFmt[0] == _T('\0'))
		return -1;

	// allocate buffer for TCHARs
	DWORD dwSize = MAX_PRINTF_CHARACTERS;
	LPTSTR buf = new TCHAR [dwSize];
	_ASSERTE(buf);
	if (!buf)
		return -1;

	buf[0] = _T('\0');

	// combine output string and variables
	va_list argptr;
	va_start(argptr, lpszFmt);
	int n = _vsntprintf(buf, dwSize-2, lpszFmt, argptr);
	va_end(argptr);

	_ASSERTE(n > 0);
	if (n < 0)
	{
		TRACEERROR(_T("ERROR: %s failed ==> buffer too small\n"), _T("_vsntprintf"));
	}
	else
	{
		DWORD dwRet = Write(buf, n*sizeof(TCHAR));	// write bytes, not TCHARs
		if (dwRet == XFILE_ERROR)
		{
			TRACEERROR(_T("ERROR: %s failed ==> Write returned error\n"), _T("Printf"));
			n = -1;
		}
	}

	if (buf)
		delete [] buf;

	return n;
}

///////////////////////////////////////////////////////////////////////////////
//
// Read()
//
// Purpose:     Read byte data from an open file.  Up to dwBytes of data are
//              read into buffer specified by lpszBuffer.
//
// Parameters:  lpszBuffer - pointer to byte buffer that byte data will be
//                           read into
//              dwBytes    - size of buffer in bytes
//
// Returns:     DWORD - number of bytes read, or (DWORD)-1 if error; EOF found
//                      if 0 returned.
//
// Notes:       For mapped files, Read will call ReadMapped.
//
DWORD CXFile::Read(LPTSTR lpszBuffer, DWORD dwBytes)
{
	if (m_bMappedFile)
		return ReadMapped(lpszBuffer, dwBytes);

	_ASSERTE(IsValidFileHandle(m_hFile));
	if (!IsValidFileHandle(m_hFile))
		return XFILE_ERROR;

	_ASSERTE(lpszBuffer);
	if (!lpszBuffer)
		return XFILE_ERROR;

	if (dwBytes == 0)
		return 0;

	_ASSERTE(!IsBadWritePtr(lpszBuffer, dwBytes));
	if (IsBadWritePtr(lpszBuffer, dwBytes))
	{
		TRACEERROR(_T("ERROR: bad pointer\n"));
		return XFILE_ERROR;
	}

	// if something in write buffer, flush now
	if (!IsBufferEmpty())
		Flush();

	DWORD dwBytesRead = 0;

	BOOL bRet = ::ReadFile(m_hFile, (LPVOID) lpszBuffer, dwBytes, &dwBytesRead, NULL);

	m_dwLastError = GetLastError();

	if (!bRet)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("ReadFile"),
			GetLastErrorString());
		return XFILE_ERROR;
	}

	m_dwTotalBytesReadFromFile += dwBytesRead;
	m_dwTotalNumberOfReads++;

	if (dwBytesRead == 0)
	{
		// Read ok, but nothing read
		TRACE(_T("Read ==> EOF reached.\n"));
	}

	return dwBytesRead;
}

///////////////////////////////////////////////////////////////////////////////
//
// ReadMapped()
//
// Purpose:     Read byte data from a file that has been opened with OpenMapped.
//              Up to dwBytes of data are copied into buffer specified by
//              lpszBuffer.
//
// Parameters:  lpszBuffer - pointer to byte buffer that byte data will be
//                           copied into
//              dwBytes    - size of buffer in bytes - MUST be a multiple of
//                           system's virtual memory allocation granularity,
//                           or the next call to MapViewOfFile() will fail.
//                           Use GetAllocationGranularity() to retrieve
//                           this value and allocate a buffer.
//
// Returns:     DWORD - number of bytes copied, or (DWORD)-1 if error;
//                      EOF found if 0 returned.
//
DWORD CXFile::ReadMapped(LPTSTR lpszBuffer, DWORD dwBytes)
{
	_ASSERTE(lpszBuffer);
	if (!lpszBuffer)
		return XFILE_ERROR;

	_ASSERTE(!IsBadWritePtr(lpszBuffer, dwBytes));
	if (IsBadWritePtr(lpszBuffer, dwBytes))
	{
		TRACEERROR(_T("ERROR: bad pointer\n"));
		return XFILE_ERROR;
	}

	if (!m_bMappedFile)
		return XFILE_ERROR;

	_ASSERTE(m_hMappedFile);
	if (!m_hMappedFile)
		return XFILE_ERROR;

	_ASSERTE(m_dwAllocationGranularity != 0);
	if (m_dwAllocationGranularity == 0)
		return XFILE_ERROR;

	_ASSERTE((m_dwMappedFileOffset % m_dwAllocationGranularity) == 0);
	if ((m_dwMappedFileOffset % m_dwAllocationGranularity) != 0)
	{
		TRACEERROR(_T("ERROR:  file offset is not a multiple of system's virtual memory\n")
			  _T("allocation granularity.  This will cause MapViewOfFile() to fail.\n"));
		return XFILE_ERROR;
	}

	// is file empty?
	if (m_dwMappedFileSize == 0)
		return 0;

	// is file at eof?
	if (m_dwMappedFileOffset >= m_dwMappedFileSize)
		return 0;

	DWORD dwBytesToRead = dwBytes;

	// ensure that we don't try to read more than what's in file
	if ((m_dwMappedFileOffset + dwBytesToRead) > m_dwMappedFileSize)
		dwBytesToRead = m_dwMappedFileSize - m_dwMappedFileOffset;

	if (dwBytesToRead == 0)
		return 0;

	LPBYTE lpMapAddress = (LPBYTE) ::MapViewOfFile(m_hMappedFile,	// handle to file-mapping object
											FILE_MAP_READ,			// access mode
											0,						// high-order DWORD of offset
											m_dwMappedFileOffset,	// low-order DWORD of offset
											dwBytesToRead);			// number of bytes to map

	m_dwLastError = GetLastError();

	if (lpMapAddress == NULL)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("MapViewOfFile"),
			GetLastErrorString());
		return XFILE_ERROR;
	}

	// copy data to caller's buffer - we do this to maintain
	// compatiblity with Read()
	memcpy(lpszBuffer, lpMapAddress, dwBytesToRead);

	BOOL bRet = ::UnmapViewOfFile(lpMapAddress);

	m_dwLastError = GetLastError();

	if (!bRet)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("UnmapViewOfFile"),
			GetLastErrorString());
	}

	m_dwMappedFileOffset += dwBytesToRead;

	m_dwTotalBytesReadFromFile += dwBytesToRead;
	m_dwTotalNumberOfReads++;

	return dwBytesToRead;
}

///////////////////////////////////////////////////////////////////////////////
//
// Rename()
//
// Purpose:     Rename existing file
//
// Parameters:  lpszExistingFileName - name of existing file
//              lpszNewFileName      - name of new file
//              bFailIfExists        - operation if file exists:
//                                     TRUE = if new file already exists, the
//                                     function fails
//                                     FALSE = if new file already exists, the
//                                     function overwrites the existing file
//                                     and succeeds
//
// Returns:     BOOL - TRUE = success
//
BOOL CXFile::Rename(LPCTSTR lpszExistingFileName,
					LPCTSTR lpszNewFileName,
					BOOL bFailIfExists /*= TRUE*/)
{
	_ASSERTE(lpszExistingFileName);
	_ASSERTE(lpszExistingFileName[0] != _T('\0'));

	if (!lpszExistingFileName || lpszExistingFileName[0] == _T('\0'))
		return FALSE;

	_ASSERTE(lpszNewFileName);
	_ASSERTE(lpszNewFileName[0] != _T('\0'));

	if (!lpszNewFileName || lpszNewFileName[0] == _T('\0'))
		return FALSE;

	BOOL bRet = FALSE;

	// does new file exist?
	if (IsFileAccessible(lpszNewFileName))
	{
		if (bFailIfExists)
		{
			TRACE(_T("file exists, Rename returning FALSE\n"));
			return FALSE;
		}
		else
		{
			TRACE(_T("file exists, Rename attempting to delete\n"));
			bRet = ::DeleteFile(lpszNewFileName);

			m_dwLastError = GetLastError();

			if (!bRet)
			{
				TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("DeleteFile"),
					GetLastErrorString());
				return FALSE;
			}
		}
	}

	bRet = ::MoveFile(lpszExistingFileName, lpszNewFileName);

	m_dwLastError = GetLastError();

	if (!bRet)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("MoveFile"),
			GetLastErrorString());
	}

	return bRet;
}

///////////////////////////////////////////////////////////////////////////////
//
// Rollover()
//
// Purpose:     Rollover file to new file and optionally zip, continue
//              with empty file
//
// Parameters:  lpszRolloverFileName     - name to use for new rollover file
//              lpszFileNameBuffer       - buffer for rollover file name;  if
//                                         not NULL, the rollover file name
//                                         will be copied into this buffer
//              dwFileNameBufferSize     - size of lpszFileNameBuffer in TCHARs;
//                                         if 0, rollover file name will not be
//                                         copied into lpszFileNameBuffer
//              bFailIfExists            - operation if file exists:
//                                         TRUE = if new file already exists,
//                                         the function fails
//                                         FALSE = if new file already exists,
//                                         the function overwrites the existing
//                                         file and succeeds
//              bZip                     - operation if Rollover() succeeds:
//                                         TRUE = zip rollover file; name of
//                                         archive will be same as rollover file,
//                                         with .zip extension; then delete
//                                         rollover file
//                                         FALSE - do not zip
//              bGenerateRolloverLogFile - create entry in rollover log file:
//                                         TRUE = create entry
//                                         FALSE = do not create entry
//
// Returns:     BOOL - TRUE = success
//
BOOL CXFile::Rollover(LPCTSTR lpszRolloverFileName /*= NULL*/,
					  LPTSTR lpszFileNameBuffer /*= NULL*/,
					  DWORD dwFileNameBufferSize /*= 0*/,
					  BOOL bFailIfExists /*= TRUE*/,
					  BOOL bZip /*= FALSE*/,
					  BOOL bGenerateRolloverLogFile /*= FALSE*/)
{
	TRACE(_T("in CXFile::Rollover\n"));

	///////////////////////////////////////////////////////////////////////////
	// initialize

	BOOL bSuccess = TRUE;

	_ASSERTE(IsValidFileHandle(m_hFile));
	if (!IsValidFileHandle(m_hFile))
		return FALSE;

	_ASSERTE(!m_bMappedFile);
	if (m_bMappedFile)
		return FALSE;

	// if something in write buffer, flush now
	if (!IsBufferEmpty())
		Flush();

	BOOL bRet = FALSE;

	// get full name of file to be rolled, incl. drive & dir
	TCHAR * lpszFullPathName = GetFullName(m_szFile);
	if (!lpszFullPathName)
		return FALSE;

	// save original file name
	TCHAR szOriginalFile[_MAX_PATH*2];
	memset(szOriginalFile, 0, _MAX_PATH*2*sizeof(TCHAR));
	_tcscpy(szOriginalFile, lpszFullPathName);

	delete [] lpszFullPathName;
	lpszFullPathName = NULL;

	TCHAR szNewFile[_MAX_PATH*2];
	memset(szNewFile, 0, _MAX_PATH*2*sizeof(TCHAR));

	///////////////////////////////////////////////////////////////////////////
	// get rollover file name - original file will be renamed to this

	// do we need to generate a rollover file name?
	if ((lpszRolloverFileName == NULL) || (lpszRolloverFileName[0] == _T('\0')))
	{
		// include count in rollover name to make unique
		static UINT nCount = 0;
		nCount++;
		if (nCount > 99999)
			nCount = 1;

		SYSTEMTIME systime;
		::GetLocalTime(&systime);

		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];

		_tsplitpath(szOriginalFile, drive, dir, fname, ext);

		// create rollover file name:
		//     <drive><dir><original file name>< 03042516120300001><ext>
		//                                       yymmddhhmmssNNNNN
		int n = _stprintf(szNewFile, _T("%s%s%s %02d%02d%02d%02d%02d%02d%05d%s"),
						  drive, dir, fname,
						  systime.wYear-2000, systime.wMonth, systime.wDay,
						  systime.wHour, systime.wMinute, systime.wSecond,
						  nCount, ext);

		if (n >= _MAX_PATH)
		{
			TRACEERROR(_T("ERROR: new rollover file path too long: %d\n"), n);
			_ASSERTE(n < _MAX_PATH);
		}
	}
	else		// rollover file name was specified
	{
		_tcscpy(szNewFile, lpszRolloverFileName);
	}

	TRACE(_T("rolling over %s to %s\n"), szOriginalFile, szNewFile);

	if (lpszFileNameBuffer && (dwFileNameBufferSize != 0))
	{
		// return rollover file name to user

		_ASSERTE(!IsBadWritePtr(lpszFileNameBuffer, dwFileNameBufferSize));
		if (IsBadWritePtr(lpszFileNameBuffer, dwFileNameBufferSize))
		{
			TRACEERROR(_T("ERROR: bad pointer\n"));
			return FALSE;
		}

		DWORD dwSize = (dwFileNameBufferSize > (_MAX_PATH*2-2)) ?
			_MAX_PATH*2-2 : dwFileNameBufferSize;

		memset(lpszFileNameBuffer, 0, dwSize*sizeof(TCHAR));
		_tcsncpy(lpszFileNameBuffer, szNewFile, dwSize);

		if (bZip)
		{
			// return name of zip file

			TCHAR *cp = _tcsrchr(lpszFileNameBuffer, _T('.'));

			if (cp)
				*cp = _T('\0');

			_tcscat(lpszFileNameBuffer, _T(".zip"));
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// final steps:
	//     1.  log this rollover
	//     2.  save file attributes for Open later
	//     3.  close original file
	//     4.  rename original file to rollover file
	//     5.  zip rollover file if requested
	//     6.  open new file with original file name
	//     7.  restore file attributes

	if (bGenerateRolloverLogFile)
	{
		// log this rollover
		bRet = GenerateRolloverLogFile(szOriginalFile);
	}

	// save file attributes for Open
	BOOL bSavedUnicode           = GetUnicode();
	BOOL bSavedReadOnly          = GetReadOnly();
	DWORD dwLimitBytes           = GetSizeLimitBytes();
	FILESIZELIMITTYPE eLimitType = GetSizeLimitType();
	BYTE SizeLimitDelimiter[sizeof(m_SizeLimitDelimiter)];
	memcpy(SizeLimitDelimiter, GetSizeLimitDelimiter(), sizeof(m_SizeLimitDelimiter));
	DWORD dwLimitDelimiterSize = m_dwLimitDelimiterSize;

	Close();

	// rename current file to new file name
	bRet = Rename(szOriginalFile, szNewFile, bFailIfExists);

	if (!bRet)
	{
		bSuccess = FALSE;
	}
	else
	{
		if (bZip)
		{
			// zip the rollover file, then delete it

			TCHAR szArchive[_MAX_PATH*2];
			memset(szArchive, 0, _MAX_PATH*2*sizeof(TCHAR));

			_tcscpy(szArchive, szNewFile);
			TCHAR *cp = _tcsrchr(szArchive, _T('.'));

			if (cp)
				*cp = _T('\0');

			_tcscat(szArchive, _T(".zip"));

			// zip the file - always create archive, delete source file
			bRet = Zip(szArchive, szNewFile, FALSE, TRUE);
			if (!bRet)
			{
				TRACEERROR(_T("ERROR: Zip failed after rollover for '%s'\n"),
					szNewFile);
			}
		}

		// open new file with old file name
		bSuccess = Open(szOriginalFile,
						bSavedReadOnly,
						TRUE,				// always truncate, should not exist
						bSavedUnicode);

		SetSizeLimit(dwLimitBytes, eLimitType, SizeLimitDelimiter, dwLimitDelimiterSize);
	}

	return bSuccess;
}

///////////////////////////////////////////////////////////////////////////////
//
// Search()
//
// Purpose:     Search for a sequence of bytes
//
// Parameters:  lpSearch         - byte array containing one or more values
//                                 that comprise the search string;  any value
//                                 permitted, including nul.
//              dwSearchSize     - size in bytes of search string
//              bCaseInsensitive - TRUE = search will be done ignoring case
//                                 (of those characters that fall in the ANSI
//                                 range a-z and A-Z);
//                                 FALSE - characters in the search string and
//                                 characters in the file will be compared
//                                 "as is", with no case conversion.
//
// Returns:     DWORD - >= 0 if lpSearch string was found; return value is the
//                      file position of the string found.  If the search failed,
//                      (DWORD)-1 is returned.
//
// Notes:       After a successful search, the file position will be set to the
//              first character position of the string found.  After an
//              unsuccessful search, the file position will be unchanged.
//
//              The search always starts at (or one byte past) the current file
//              position;  Seek() is not called prior to starting the search.
//              If the starting file position is past the beginning of the file
//              (i.e., not 0), then the search will start at one past the current
//              file position.  Otherwise, it will start at the current file
//              position (the beginning of the file).  This allows successive
//              searches to be done without having to move the file pointer past
//              a previous successful search.
//
//              Searches do not wrap.
//
DWORD CXFile::Search(LPBYTE lpSearch,
					 DWORD dwSearchSize,
					 BOOL bCaseInsensitive /*= FALSE*/)
{
	if (!IsFileOpen())
		return XFILE_ERROR;

	if (dwSearchSize == 0)
		return XFILE_ERROR;

	_ASSERTE(lpSearch);
	if (!lpSearch)
		return XFILE_ERROR;

	// save file attributes for Open
	BOOL bSavedUnicode           = GetUnicode();
	BOOL bSavedReadOnly          = GetReadOnly();
	DWORD dwLimitBytes           = GetSizeLimitBytes();
	FILESIZELIMITTYPE eLimitType = GetSizeLimitType();
	BYTE SizeLimitDelimiter[sizeof(m_SizeLimitDelimiter)];
	memcpy(SizeLimitDelimiter, GetSizeLimitDelimiter(), sizeof(m_SizeLimitDelimiter));
	DWORD dwLimitDelimiterSize = m_dwLimitDelimiterSize;

	// save original file name
	TCHAR szOriginalFile[_MAX_PATH*2];
	_tcscpy(szOriginalFile, m_szFile);

	DWORD dwOffset = Seek(0, FILE_CURRENT);
	if (dwOffset == XFILE_ERROR)
		return XFILE_ERROR;

	Close();

	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = ::CreateFile(szOriginalFile,
						 GENERIC_READ,// | GENERIC_WRITE,
						 0,
						 NULL,
						 OPEN_ALWAYS,
						 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						 NULL);

	m_dwLastError = GetLastError();

	if (hFile == INVALID_HANDLE_VALUE)
	{
		TRACEERROR(_T("ERROR:  failed to open '%s'\n"), m_szFile);
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFile"),
			GetLastErrorString());
		return XFILE_ERROR;
	}

	// get the file size
	DWORD dwFileSize = ::GetFileSize(hFile, NULL);

	m_dwLastError = GetLastError();

	if (dwFileSize == INVALID_FILE_SIZE)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("GetFileSize"),
			GetLastErrorString());
		::CloseHandle(hFile);
		return XFILE_ERROR;
	}

	TRACE(_T("dwFileSize = %d\n"), dwFileSize);

	// Create a file mapping object that is the current size of the file
	HANDLE hMappedFile = NULL;
	hMappedFile = ::CreateFileMapping(hFile,
									  NULL,
									  PAGE_READONLY, //PAGE_READWRITE,
									  0,
									  dwFileSize,
									  NULL);

	m_dwLastError = GetLastError();

	if (hMappedFile == NULL)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFileMapping"),
			GetLastErrorString());
		::CloseHandle(hFile);
		return XFILE_ERROR;
	}

	LPBYTE lpMapAddress = (LPBYTE) ::MapViewOfFile(hMappedFile,		// handle to file-mapping object
											FILE_MAP_READ,//FILE_MAP_WRITE,			// access mode
											0,						// high-order DWORD of offset
											0,						// low-order DWORD of offset
											0);						// number of bytes to map

	m_dwLastError = GetLastError();

	if (lpMapAddress == NULL)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("MapViewOfFile"),
			GetLastErrorString());
		::CloseHandle(hMappedFile);
		::CloseHandle(hFile);
		return XFILE_ERROR;
	}

	DWORD dwIndex = dwOffset;
	if (dwOffset)
		dwIndex++;

	//BOOL bFound = FALSE;
	//UINT c = lpSearch[0] & 0xFF;
	LPBYTE ptr = NULL;

	if (bCaseInsensitive)
		ptr = (LPBYTE) memimem(&lpMapAddress[dwIndex], dwFileSize - dwIndex, lpSearch, dwSearchSize);
	else
		ptr = (LPBYTE) memmem(&lpMapAddress[dwIndex], dwFileSize - dwIndex, lpSearch, dwSearchSize);


#if 0  // -----------------------------------------------------------
	for (;;)
	{
#pragma message("is there a memichr ????? ")

		ptr = (LPBYTE) memchr(&lpMapAddress[dwIndex], c, dwFileSize - dwIndex);

		if (ptr)
		{
			dwIndex = ptr - lpMapAddress;

			// will search string fit in what's left of file?
			if ((dwIndex + dwSearchSize) > dwFileSize)
				return XFILE_ERROR;

			bFound = TRUE;

#pragma message("use memcmp and memicmp ????? ")

			// loop to check rest of delimiter string
			for (UINT i = 1; i < dwSearchSize; i++)
			{
				if (ptr[i] != lpSearch[i])
				{
					bFound = FALSE;
					break;
				}
			}

			if (bFound)
				break;

			dwIndex++;
		}
		else
		{
			bFound = FALSE;
			break;
		}
	}
#endif // -----------------------------------------------------------

	if (!::UnmapViewOfFile(lpMapAddress))
	{
		m_dwLastError = GetLastError();

		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("UnmapViewOfFile"),
			GetLastErrorString());
	}

	if (!::CloseHandle(hMappedFile))
	{
		TRACEERROR(_T("ERROR: CloseHandle(hMappedFile) failed\n"));
	}

	if (!::CloseHandle(hFile))
	{
		TRACEERROR(_T("ERROR: CloseHandle(hFile) failed\n"));
	}

	dwIndex = ptr - lpMapAddress;
	if (ptr)
		dwOffset = dwIndex;			// set file pointer to position of byte sequence
	else
		dwIndex = XFILE_ERROR;		// leave file pointer unchanged

	Open(szOriginalFile,
		 bSavedReadOnly,
		 FALSE,
		 bSavedUnicode);

	// restore size limit
	SetSizeLimit(dwLimitBytes, eLimitType, SizeLimitDelimiter, dwLimitDelimiterSize);

	Seek(dwOffset, FILE_BEGIN);

	return dwIndex;
}


///////////////////////////////////////////////////////////////////////////////
//
// Seek()
//
// Purpose:     Move file pointer of an open file
//
// Parameters:  lOffset  - bytes to move pointer
//              dwOrigin - starting point:
//
//                    VALUE      |         STARTING POINT
//                 --------------|-----------------------------------
//                  FILE_BEGIN   | zero or the beginning of the file
//                  FILE_CURRENT | current value of the file pointer
//                  FILE_END     | current end-of-file position
//
// Returns:     DWORD - new file pointer, or (DWORD)-1 if error
//
// Notes:       Seek will flush the internal write to the file at the current
//              file pointer before moving the file pointer.
//
//              For mapped files, Seek only updates the file offset. The next
//              call to ReadMapped will use the new offset.  The offset MUST be
//              a multiple of system's virtual memory allocation granularity,
//              or the next call to MapViewOfFile() will fail.
//
DWORD CXFile::Seek(LONG lOffset, DWORD dwOrigin)
{
	TRACE(_T("in CXFile::Seek\n"));

	// if something in write buffer, flush now
	if (!IsBufferEmpty())
		Flush();

	DWORD dwPos = 0;

	DWORD dwOffset = m_dwMappedFileOffset;

	if (m_bMappedFile)
	{
		switch (dwOrigin)
		{
			case FILE_BEGIN:
				dwOffset = lOffset;
				break;

			case FILE_CURRENT:
				dwOffset += lOffset;
				break;

			case FILE_END:
				dwOffset = m_dwMappedFileSize + lOffset;
				break;

			default:
				TRACEERROR(_T("ERROR: unknown origin\n"));
				_ASSERTE(FALSE);
				return XFILE_ERROR;
				break;
		}

		if (dwOffset > m_dwMappedFileSize)
		{
			TRACE(_T("WARNING:  file offset is past end of file\n"));
			return XFILE_ERROR;
		}

		if ((dwOffset % m_dwAllocationGranularity) != 0)
		{
			TRACE(_T("WARNING:  file offset is not a multiple of system's virtual memory\n")
				  _T("allocation granularity.  This will cause MapViewOfFile() to fail.\n"));
			_ASSERTE((dwOffset % m_dwAllocationGranularity) == 0);
		}

		m_dwMappedFileOffset = dwOffset;
		dwPos = m_dwMappedFileOffset;
	}
	else
	{
		// not a mapped file

		_ASSERTE(IsValidFileHandle(m_hFile));
		if (!IsValidFileHandle(m_hFile))
			return XFILE_ERROR;

#ifdef _DEBUG
		TCHAR *pszOrigin = _T("unknown");
		switch (dwOrigin)
		{
			case FILE_BEGIN:	pszOrigin = _T("FILE_BEGIN"); break;
			case FILE_CURRENT:	pszOrigin = _T("FILE_CURRENT"); break;
			case FILE_END:		pszOrigin = _T("FILE_END"); break;
		}
		TRACE(_T("seeking to offset %d (0x%X) from %s\n"), lOffset, lOffset, pszOrigin);
#endif

		dwPos = ::SetFilePointer(m_hFile, lOffset, NULL, dwOrigin);

		m_dwLastError = GetLastError();

		if (dwPos == INVALID_SET_FILE_POINTER)	//0xFFFFFFFF)
		{
			TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("SetFilePointer"),
				GetLastErrorString());
			return XFILE_ERROR;
		}
	}

	return dwPos;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetSizeLimit()
//
// Purpose:     Set parameters to limit file size
//
// Parameters:  dwSizeLimitBytes - maximum file size in bytes;  if the limit
//                                 type is SHRINK, when dwSizeLimitBytes is
//                                 exceeded, the "shrink to" size will be set at
//                                 dwSizeLimitBytes / 2.
//              eType            - limit type:
//                                 TRUNCATE - file size will be limited by
//                                 discarding writes when the file has reached
//                                 dwSizeLimitBytes
//                                 SHRINK - file size will be limited by
//                                 discarding first half of file, and then
//                                 using lpDelimiter string to discard partial
//                                 record.  See Shrink() for more details.
//              lpDelimiter      - byte array containing one or more
//                                 characters that comprise line/record ending -
//                                 e.g., "\r\n"
//              dwDelimiterSize  - size in bytes of delimiter array
//
// Returns:     BOOL - TRUE = success
//
// Notes:       Setting a file size limit should only be done for files that
//              are being written sequentially - i.e., new data is written to
//              the end of the file.
//
//              The file size limit will be enforced when Flush() is called,
//              which typically happens when the internal CXFile write buffer
//              is full.  The first time Flush() is called, the data will always
//              be written to the file, since the file pointer is at the
//              beginning of the file and the max size hasn't been exceeded yet.
//              Therefore, the effect of the max size limit will only be seen
//              when it is larger than the internal buffer size, so that
//              multiple Flush()'s will occur, and the max size limit will be
//              triggered.
//
BOOL CXFile::SetSizeLimit(DWORD dwSizeLimitBytes /*= 0*/,
						  FILESIZELIMITTYPE eLimitType /*= TRUNCATE*/,
						  LPBYTE lpDelimiter /*= NULL*/,
						  DWORD dwDelimiterSize /*= 0*/)

{
	_ASSERTE(IsValidFileHandle(m_hFile));
	if (!IsValidFileHandle(m_hFile))
		return FALSE;

	if (m_bReadOnly)
		return FALSE;

	if (m_bMappedFile)
		return FALSE;

	m_dwSizeLimitBytes = dwSizeLimitBytes;
	m_eSizeLimitType = eLimitType;
	memset(m_SizeLimitDelimiter, 0, sizeof(m_SizeLimitDelimiter));

	if (dwDelimiterSize > sizeof(m_SizeLimitDelimiter))
		dwDelimiterSize = sizeof(m_SizeLimitDelimiter);

	if (lpDelimiter && dwDelimiterSize)
	{
		memcpy(m_SizeLimitDelimiter, lpDelimiter, dwDelimiterSize);
		m_dwLimitDelimiterSize = dwDelimiterSize;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetRolloverLogFile()
//
// Purpose:     Set name for rollover log file
//
// Parameters:  lpszLogFile - name of log file
//
// Returns:     none
//
void CXFile::SetRolloverLogFile(LPCTSTR lpszLogFile)
{
	_ASSERTE(lpszLogFile && lpszLogFile[0] != _T('\0'));
	memset(m_szRolloverLogFile, 0, sizeof(m_szRolloverLogFile));
	_tcscpy(m_szRolloverLogFile, lpszLogFile);
}

///////////////////////////////////////////////////////////////////////////////
//
// Shrink()
//
// Purpose:     Shrink an open file when it exceeds a size limit
//
// Parameters:  dwMaxFileSize   - maximum file size in bytes
//              dwShrinkToSize  - size in bytes to shrink file to
//              lpDelimiter     - byte array containing one or more
//                                characters that comprise line/record ending -
//                                e.g., "\r\n";  use NULL if partial record
//                                elimination is not desired
//              dwDelimiterSize - size in bytes of delimiter array
//
// Returns:     DWORD - Number of bytes file was shrunk.  0 = file was not
//                      shrunk, (DWORD)-1 = error occurred.
//
// Notes:       Shrink may be called anytime after a file has been opened.
//              Shrink will have no effect on files opened as readonly.  If
//              the file size exceeds dwMaxFileSize, it will be shrunk to
//              the size specified by dwShrinkToSize.  Regardless of the type
//              of file (text or binary), the first part of the file will be
//              discarded, leaving only the last dwShrinkToSize bytes.
//
//              Then, if lpDelimiter is non-NULL, this byte array will be
//              searched for in the first 64K bytes of the new file.  If found,
//              the new file will begin at the first byte past the lpDelimiter
//              array that was found.  This ensures that text files and other
//              record-oriented files will begin at the beginning of a line
//              or record.  Note that this may cause the new file to be smaller
//              than the specified dwShrinkToSize.
//
//              lpDelimiter is treated as a byte array by Shrink, whether the
//              app is compiled for Unicode or not.  For example, if you pass
//              _T("\r\n") as the delimiter array. and 2*sizeof(TCHAR) as the
//              delimiter size, Shrink will look for the sequential bytes
//                       0x0D 0x00 0x0A 0x00
//              in the file if your app is compiled for Unicode.  If it is
//              compiled for ANSI, Shrink will look for the sequential bytes
//                       0x0D 0x0A.
//              So it is up to you to use a delimiter string that matches what
//              is actually in the file, regardless of how your app is compiled.
//              Shrink does no conversion on the data it reads from the file.
//
//              Shrink will be useful to keep frequently appended-to files from
//              growing too large.  You should only use Shrink on files where
//              the most recent data is appended to the end of the file - for
//              example, log files that are written by server processes.
//
//              Shrink() will always attempt to position the file at EOF before
//              returning.
//
DWORD CXFile::Shrink(DWORD dwMaxFileSize,
					 DWORD dwShrinkToSize,
					 LPBYTE lpDelimiter /*= NULL*/,
					 DWORD dwDelimiterSize /*= 0*/)
{
	TRACE(_T("in CXFile::Shrink\n"));

	///////////////////////////////////////////////////////////////////////////
	// initialize

	_ASSERTE(IsValidFileHandle(m_hFile));
	if (!IsValidFileHandle(m_hFile))
		return XFILE_ERROR;

	_ASSERTE(dwMaxFileSize != 0);
	_ASSERTE(dwShrinkToSize != 0);
	if (dwMaxFileSize == 0 || dwShrinkToSize == 0)
		return XFILE_ERROR;

	_ASSERTE(dwMaxFileSize > dwShrinkToSize);
	if (dwMaxFileSize <= dwShrinkToSize)
		return XFILE_ERROR;

	if (m_bReadOnly)
		return XFILE_ERROR;

	if (m_bMappedFile)
		return XFILE_ERROR;

	// if something in write buffer, flush now
	if (!IsBufferEmpty())
		Flush();

	DWORD dwFileSize = ::GetFileSize(m_hFile, NULL);

	m_dwLastError = GetLastError();

	if (dwFileSize == INVALID_FILE_SIZE)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("GetFileSize"),
			GetLastErrorString());
		return XFILE_ERROR;
	}

	// is file too large?
	if (dwFileSize <= dwMaxFileSize)
		return 0;

	// file is too large - it must be shrunk

	BOOL bRet = FALSE;

	bRet = ::LockFile(m_hFile,			// handle to file
					  0,				// low-order word of offset
					  0,				// high-order word of offset
					  dwFileSize,		// low-order word of length
					  0);				// high-order word of length

	m_dwLastError = GetLastError();

	if (!bRet)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("LockFile"),
			GetLastErrorString());

		// we will continue without the lock
	}

	///////////////////////////////////////////////////////////////////////////
	// move file pointer past number of bytes that the file has to shrink

	TRACE(_T("dwFileSize=%d  dwShrinkToSize=%d  discard size=%d\n"),
		dwFileSize, dwShrinkToSize, dwFileSize - dwShrinkToSize);

	// position file pointer to start of what will be new shrunk file
	DWORD dwNewFileStart = dwFileSize - dwShrinkToSize;

	DWORD dwRet = Seek(dwNewFileStart, FILE_BEGIN);

	if (dwRet == XFILE_ERROR)
	{
		TRACEERROR(_T("ERROR:  Seek failed\n"));
		return XFILE_ERROR;
	}

	// this will be minimum amount of shrinkage
	DWORD dwAmountShrunk = dwFileSize - dwShrinkToSize;

	// allocate buffer that will be used for file copying
	// and also for optional delimiter search
	DWORD dwBufSize = SHRINK_BUF_SIZE;
	BYTE * pBuf = new BYTE [dwBufSize];
	_ASSERTE(pBuf);
	if (!pBuf)
		return XFILE_ERROR;

	DWORD dwBytesRead = 0;
	DWORD dwAdditionalBytesToDiscard = 0;

	///////////////////////////////////////////////////////////////////////////
	// look for delimiter and eliminate partial record if found

	if (lpDelimiter && dwDelimiterSize)
	{
		// look for delimiter in first 64K of new file

		dwBytesRead = Read((LPTSTR) pBuf, dwBufSize);

		if ((dwBytesRead != XFILE_ERROR) && (dwBytesRead != 0))
		{
#ifdef _DEBUG
			TCHAR szDelim[2000];
			int jj = 0;
			for (UINT ii = 0; ii < dwDelimiterSize; ii++)
			{
				jj += _stprintf(&szDelim[jj], _T("0x%2X "), (USHORT) lpDelimiter[ii]);
			}
			TRACE(_T("delim string:  %s\n"), szDelim);
#endif

			UINT i = 0, j = 0;

			BOOL bDelimiterFound = FALSE;

			// loop to look for delimiter string
			for (i = 0; i < dwBytesRead; i++)
			{
				if (pBuf[i] == lpDelimiter[0])
				{
					// might have found delimiter
					bDelimiterFound = TRUE;
					for (j = 1; j < dwDelimiterSize; j++)
					{
						if (pBuf[i+j] != lpDelimiter[j])
						{
							bDelimiterFound = FALSE;
							break;
						}
					}
					if (bDelimiterFound)
						break;
				}

			} // for (i = 0; i < dwBytesRead; i++)

			if (bDelimiterFound)
			{
				dwAdditionalBytesToDiscard = i + dwDelimiterSize;	// first byte after delimiter

				TRACE(_T("delimiter found, discarding additional %d bytes\n"),
					dwAdditionalBytesToDiscard);

				dwRet = Seek(dwNewFileStart + dwAdditionalBytesToDiscard,
							FILE_BEGIN);

				if (dwRet == XFILE_ERROR)
				{
					TRACEERROR(_T("ERROR:  Seek failed\n"));
					return XFILE_ERROR;
				}
			}
			else
			{
				TRACE(_T("delimiter not found, going back to %d\n"),
					dwNewFileStart);

				// delimiter not found - go back to where we were
				dwRet = Seek(dwNewFileStart, FILE_BEGIN);

				if (dwRet == XFILE_ERROR)
				{
					TRACEERROR(_T("ERROR:  Seek failed\n"));
					return XFILE_ERROR;
				}
			}
		}
	}

	dwAmountShrunk += dwAdditionalBytesToDiscard;

	///////////////////////////////////////////////////////////////////////////
	// copy file (from current file pointer to EOF) to a temp file

	TCHAR szPath[_MAX_PATH*2];

	// set path from original file
	_tcscpy(szPath, m_szFile);

	TCHAR *cp = _tcsrchr(szPath, _T('\\'));
	if (cp == NULL)
	{
		// no path, use current directory
		memset(szPath, 0, _MAX_PATH*2*sizeof(TCHAR));
		::GetCurrentDirectory(_MAX_PATH*2-2, szPath);
	}
	else
	{
		*cp = _T('\0');
	}
	TRACE(_T("szPath='%s'\n"), szPath);

	// szPath now contains drive + dir of shrunk file

	TCHAR szNewFile[_MAX_PATH*2];
	szNewFile[0] = _T('\0');

	// create new shrunk file to copy data to
	// note this actually creates temp file
	UINT u = ::GetTempFileName(szPath,		// dir. for temp. files
							   _T("_XF"),	// temp. file name prefix
							   0,			// create unique name
							   szNewFile);	// buffer for name

	m_dwLastError = GetLastError();

	if (u == 0)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("GetTempFileName"),
			GetLastErrorString());
		return XFILE_ERROR;
	}

	if (szNewFile[0] == _T('\0'))
	{
		_tcscpy(szNewFile, szPath);
		_tcscat(szNewFile, _T("\\_XFileTemp.tmp"));
	}

	TRACE(_T("temp file ='%s'\n"), szNewFile);

	// open the new file
	HANDLE hNewFile = NULL;
	hNewFile = ::CreateFile(szNewFile,						// file name
							 GENERIC_READ | GENERIC_WRITE,	// open for read/write
							 FILE_SHARE_READ,				// share for reading
							 NULL,							// no security
							 CREATE_ALWAYS,					// overwrite existing file
							 FILE_ATTRIBUTE_NORMAL,			// normal file
							 NULL);							// no attr. template

	m_dwLastError = GetLastError();

	if (!IsValidFileHandle(hNewFile))
	{
		TRACEERROR(_T("ERROR: failed to open temp file '%s'\n"), szNewFile);
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("CreateFile"),
			GetLastErrorString());
		return XFILE_ERROR;
	}

	_ASSERTE(dwShrinkToSize > dwAdditionalBytesToDiscard);
	DWORD dwBytesToCopy = dwShrinkToSize - dwAdditionalBytesToDiscard;

	BOOL bSuccess = TRUE;

	TRACE(_T("Copying %d bytes from file %s at offset %d to file %s\n"),
		dwBytesToCopy, m_szFile, Seek(0, FILE_CURRENT), szNewFile);

	while (dwBytesToCopy)
	{
		dwBytesRead = Read((LPTSTR) pBuf, dwBufSize);

		if (dwBytesRead == XFILE_ERROR)
		{
			bSuccess = FALSE;
			break;
		}

		if (dwBytesRead == 0)
			break;

		DWORD dwBytesWritten = 0;
		bRet = ::WriteFile(hNewFile,
						   pBuf,
						   dwBytesRead,
						   &dwBytesWritten,
						   NULL);

		m_dwLastError = GetLastError();

		if (!bRet)
		{
			TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("WriteFile"),
				GetLastErrorString());
			bSuccess = FALSE;
			break;
		}

		TRACE(_T("Wrote %d bytes to file %s\n"),
			dwBytesWritten, szNewFile);

		dwBytesToCopy -= dwBytesRead;
	}

	::FlushFileBuffers(hNewFile);
	TRACE(_T("new file size = %d =====\n"),
		::GetFileSize(hNewFile, NULL));

	::CloseHandle(hNewFile);

	if (pBuf)
		delete [] pBuf;
	pBuf = NULL;

	///////////////////////////////////////////////////////////////////////////
	// close original file, rename new file to original file name

	if (bSuccess)
	{
		TRACE(_T("file write ok\n"));

		// save original file name
		TCHAR szOriginalFile[_MAX_PATH*2];
		cp = _tcsrchr(m_szFile, _T('\\'));
		if (cp)
		{
			_tcscpy(szOriginalFile, m_szFile);
		}
		else
		{
			_tcscpy(szOriginalFile, szPath);
			_tcscat(szOriginalFile, _T("\\"));
			_tcscat(szOriginalFile, m_szFile);
		}

		// save file attributes for Open
		DWORD dwTotalBytesRead      = GetTotalBytesReadFromFile();
		DWORD dwTotalBytesWritten   = GetTotalBytesWrittenToFile();
		DWORD dwTotalNumberOfReads  = GetTotalNumberOfReads();
		DWORD dwTotalNumberOfWrites = GetTotalNumberOfWrites();

		BOOL bSavedUnicode           = GetUnicode();
		BOOL bSavedReadOnly          = GetReadOnly();
		BOOL bSavedTruncate          = FALSE;		// don't discard what we just wrote
		DWORD dwLimitBytes           = GetSizeLimitBytes();
		FILESIZELIMITTYPE eLimitType = GetSizeLimitType();
		BYTE SizeLimitDelimiter[sizeof(m_SizeLimitDelimiter)];
		memcpy(SizeLimitDelimiter, GetSizeLimitDelimiter(), sizeof(m_SizeLimitDelimiter));
		DWORD dwLimitDelimiterSize = m_dwLimitDelimiterSize;

		// unlock & close original file
		bRet = ::UnlockFile(m_hFile,		// handle to file
							0,				// low-order word of offset
							0,				// high-order word of offset
							dwFileSize,		// low-order word of length
							0);				// high-order word of length
		Close();

		TRACE(_T("szOriginalFile='%s'\n"), szOriginalFile);
		TRACE(_T("szNewFile='%s'\n"), szNewFile);

		// rename new file to original file
		TRACE(_T("Renaming %s ==> %s\n"), szNewFile, szOriginalFile);
		bRet = Rename(szNewFile, szOriginalFile, FALSE);	// don't fail if exists

		if (!bRet)
		{
			bSuccess = FALSE;
		}
		else
		{
			// open new file
			bSuccess = Open(szOriginalFile,
							bSavedReadOnly,
							bSavedTruncate,
							bSavedUnicode);

			// restore statistics
			m_dwTotalBytesReadFromFile  = dwTotalBytesRead;
			m_dwTotalBytesWrittenToFile = dwTotalBytesWritten;
			m_dwTotalNumberOfReads      = dwTotalNumberOfReads;
			m_dwTotalNumberOfWrites     = dwTotalNumberOfWrites;

			// restore size limit
			SetSizeLimit(dwLimitBytes, eLimitType, SizeLimitDelimiter, dwLimitDelimiterSize);
		}
	}

	if (!bSuccess)
	{
		TRACEERROR(_T("ERROR: Shrink failed\n"));
		return XFILE_ERROR;
	}

	if (IsFileOpen())
		Seek(0, FILE_END);

	return dwAmountShrunk;
}

///////////////////////////////////////////////////////////////////////////////
//
// Write()
//
// Purpose:     Write byte data to an open file.  Data is actually copied to
//              internal CXFile buffer, and flushed when buffer becomes full
//              or file is closed or Flush() is called.
//
// Parameters:  lpszBuffer - pointer to byte buffer containing data
//              dwBytes    - number of bytes in buffer
//
// Returns:     DWORD - number of bytes copied, or (DWORD)-1 if error
//
DWORD CXFile::Write(LPCTSTR lpszBuffer, DWORD dwBytes)
{
	_ASSERTE(IsValidFileHandle(m_hFile));
	if (!IsValidFileHandle(m_hFile))
		return XFILE_ERROR;

	if (m_bReadOnly)
		return 0;

	if (m_bMappedFile)
		return 0;

	if (dwBytes == 0)
		return 0;

	_ASSERTE(lpszBuffer);
	if (!lpszBuffer)
		return XFILE_ERROR;

	_ASSERTE(!IsBadReadPtr(lpszBuffer, dwBytes));
	if (IsBadReadPtr(lpszBuffer, dwBytes))
	{
		TRACEERROR(_T("ERROR: bad pointer\n"));
		return XFILE_ERROR;
	}

	DWORD dwBytesLeft = dwBytes;

	_ASSERTE(m_pBuffer);
	_ASSERTE(m_dwBufferSize);

	LPBYTE pByte = (LPBYTE) lpszBuffer;

	// loop to write data - it may be larger than buffer
	while (dwBytesLeft)
	{
		DWORD dwBytesToWrite = dwBytesLeft;

		// fill up buffer first
		if (dwBytesToWrite > (m_dwBufferSize - m_dwBufferIndex))
			dwBytesToWrite = m_dwBufferSize - m_dwBufferIndex;

		if (dwBytesToWrite == 0)
		{
			// buffer was already full, flush and try again
			Flush();
			continue;
		}

		// append new data to end of buffer
		memcpy(&m_pBuffer[m_dwBufferIndex], pByte, dwBytesToWrite);
		m_dwBufferIndex += dwBytesToWrite;

		dwBytesLeft -= dwBytesToWrite;

		// if there's more flush now - we just filled buffer
		if (dwBytesLeft)
			Flush();

		// advance buffer pointer
		pByte += dwBytesToWrite;
	}

	return dwBytes;
}

///////////////////////////////////////////////////////////////////////////////
//
// WriteUnicodeHeader()
//
// Purpose:     Write two-byte Unicode header (BOM)
//
// Parameters:  hFile - handle of open file to write Unicode header to
//
// Returns:     BOOL - TRUE = success
//
// Notes:       The Unicode header written by CXFile is known as a signature.
//              According to the Unicode Consortium (see "UTF & BOM", at
//              http://www.unicode.org/faq/utf_bom.html), the signature at the
//              beginning of certain data streams (such as unmarked plaintext
//              files). is referred to as the BOM character, for Byte Order Mark.
//              For little-endian systems such as those based on Intel x86
//              processors, the BOM is encoded as the two byte sequence FF FE
//              (hex values).  For big-endian systems, the BOM is FE FF.
//
//              Where a BOM is useful is with files that are typed as text, but
//              not known to be in either big- or little-endian format.  In that
//              situation, the BOM serves both as a hint that the text is Unicode,
//              and also what type of byte-ordering.was used to create the file.
//
//              Whenever the word "Unicode" is used in this program, it is meant
//              to refer to UTF-16, as defined at www.unicode.org.
//
BOOL CXFile::WriteUnicodeHeader(HANDLE hFile)
{
	TRACE(_T("in CXFile::WriteUnicodeHeader\n"));

	BOOL bRet = TRUE;

	_ASSERTE(IsValidFileHandle(hFile));
	if (!IsValidFileHandle(hFile))
		return FALSE;

	BYTE ByteOrderMark[2] = { 0xFF, 0xFE };		// BOM for little-endian machines

	DWORD dwBytesWritten = 0;

	bRet = ::WriteFile(hFile,
					   ByteOrderMark,
					   2,
					   &dwBytesWritten,
					   NULL);

	m_dwLastError = GetLastError();

	if (!bRet)
	{
		TRACEERROR(_T("ERROR: %s failed ==> %s\n"), _T("WriteFile"),
			GetLastErrorString());
	}

	return bRet;
}

///////////////////////////////////////////////////////////////////////////////
//
// Zip()
//
// Purpose:     Zip a file
//
// Parameters:  lpszZipArchive - name of zip archive to create
//              lpszSrcFile    - name of file to zip; the file name and
//                               extension from lpszSrcFile will be used as the
//                               entry name in the zip file
//              bFailIfExists  - operation if zip archive exists:
//                               TRUE = if zip archive already exists, the
//                               function fails
//                               FALSE = if zip archive already exists, the
//                               function overwrites the existing zip archive
//                               and succeeds
//              bDeleteSrcFile - operation if zip creation succeeds:
//                               TRUE = delete lpszSrcFile
//                               FALSE = do not delete lpszSrcFile
//
// Returns:     BOOL - TRUE = success
//
// Notes:       Zip() compresses one file and stores it in a new zip archive.
//              It does not handle more than one file per archive.
//
//              Zip() supports Unicode in the following way:  the names of the
//              zip archive and zip source file may be passed as Unicode
//              strings (if built with _UNICODE defined).  However, the source
//              file name is stored internally in the zip archive as ANSI. This
//              is a basic limitation of the zip engine.
//
BOOL CXFile::Zip(LPCTSTR lpszZipArchive,
				 LPCTSTR lpszSrcFile,
				 BOOL bFailIfExists /*= TRUE*/,
				 BOOL bDeleteSrcFile /*= FALSE*/)
{
	TRACE(_T("in CXFile::Zip\n"));

	BOOL bResult = TRUE;

#ifndef DO_NOT_INCLUDE_XZIP

	_ASSERTE(lpszZipArchive);
	_ASSERTE(lpszZipArchive[0] != _T('\0'));

	if (!lpszZipArchive || lpszZipArchive[0] == _T('\0'))
		return FALSE;

	_ASSERTE(lpszSrcFile);
	_ASSERTE(lpszSrcFile[0] != _T('\0'));

	if (!lpszSrcFile || lpszSrcFile[0] == _T('\0'))
		return FALSE;

	// should we overwrite existing zip file?
	if (bFailIfExists)
	{
		if (IsFileAccessible(lpszZipArchive))
		{
			TRACEERROR(_T("WARNING: zip archive '%s' exists, operation aborted\n"),
				lpszZipArchive);
			return FALSE;
		}
	}

	// does zip source file exist?
	if (!IsFileAccessible(lpszSrcFile))
	{
		TRACEERROR(_T("WARNING: zip source file '%s' cannot be found, operation aborted\n"),
			lpszSrcFile);
		return FALSE;
	}

	// use only the file name for zip file entry
	const TCHAR * cp = _tcsrchr(lpszSrcFile, _T('\\'));
	if (cp == NULL)
		cp = (TCHAR *) lpszSrcFile;
	else
		cp++;

	HZIP hz = CreateZip((void *)lpszZipArchive, 0, ZIP_FILENAME);

	if (hz)
	{
		ZRESULT zr = ZipAdd(hz, cp, (void *)lpszSrcFile, 0, ZIP_FILENAME);

		CloseZip(hz);

		// did add work?
		if (zr == ZR_OK)
		{
			TRACE(_T("added '%s' to zip file '%s'\n"),
				lpszSrcFile, lpszZipArchive);

			bResult = TRUE;

			// delete source file?
			if (bDeleteSrcFile)
			{
				bResult = Delete(lpszSrcFile);
			}
		}
		else
		{
			TRACEERROR(_T("WARNING: failed to add zip source file '%s'\n"),
				lpszSrcFile);
			bResult = FALSE;
		}
	}
	else
	{
		TRACEERROR(_T("ERROR: failed to create zip file '%s'\n"),
			lpszZipArchive);
		bResult = FALSE;
	}

#else

	TRACEERROR(_T("WARNING: \"DO_NOT_INCLUDE_XZIP\" defined, Zip() does nothing\n"));

	lpszZipArchive;
	lpszSrcFile;
	bFailIfExists;
	bDeleteSrcFile;

#endif

	return bResult;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//                 utility functions used by Search()


///////////////////////////////////////////////////////////////////////////////
// memichr - case-insensitive version of memchr
static
void *memichr(const void *buf, int c, size_t buf_len)
{
	BYTE *p = (BYTE *) buf;
	BYTE b_lower = (BYTE) c;
	BYTE b_upper = (BYTE) c;

	if ((b_lower >= 'A') && (b_lower <= 'Z'))
		b_lower = (BYTE) (b_lower + ('a' - 'A'));

	if ((b_upper >= 'a') && (b_upper <= 'z'))
		b_upper = (BYTE) (b_upper - ('a' - 'A'));

	for (UINT i = 0; i < buf_len; i++)
	{
		if ((*p == b_lower) || (*p == b_upper))
			return p;
		p++;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// memimem - like strstr, but for non-text buffers (case insensitive)
static
void *memimem(const void *buf,
			  size_t buf_len,
			  const void *byte_sequence,
			  size_t byte_sequence_len)
{
	BYTE *bf = (BYTE *)buf;
	BYTE *bs = (BYTE *)byte_sequence;
	BYTE *p  = bf;

	while (byte_sequence_len <= (buf_len - (p - bf)))
	{
		UINT b = *bs & 0xFF;
		if ((p = (BYTE *) memichr(p, b, buf_len - (p - bf))) != NULL)
		{
			if ((_memicmp(p, byte_sequence, byte_sequence_len)) == 0)
				return p;
			else
				p++;
		}
		else
		{
			break;
		}
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// memmem - like strstr, but for non-text buffers
static
void *memmem(const void *buf,
			 size_t buf_len,
			 const void *byte_sequence,
			 size_t byte_sequence_len)
{
	BYTE *bf = (BYTE *)buf;
	BYTE *bs = (BYTE *)byte_sequence;
	BYTE *p  = bf;

	while (byte_sequence_len <= (buf_len - (p - bf)))
	{
		UINT b = *bs & 0xFF;
		if ((p = (BYTE *) memchr(p, b, buf_len - (p - bf))) != NULL)
		{
			if ((memcmp(p, byte_sequence, byte_sequence_len)) == 0)
				return p;
			else
				p++;
		}
		else
		{
			break;
		}
	}
	return NULL;
}

