// jClipboard Class
// ----------------
// Written by David Terracino <davet@lycosemail.com>
//
// http://www.codeguru.com/clipboard/simple_clipboard.shtml
//
// This code is released into the public domain, because
// it's silly easy. If you want to use and expand it, go
// ahead; fine by me. If you do expand this class's
// functionality, please consider sending it back up to
// the MFC Programmer's Sourcebook at www.codeguru.com.
//
// And as always, please give credit where credit is
// due. Don't remove my name from the source.
///////////////////////////////////////////////////////////////////////////////
// Modified by Hans Dietrich  hdietrich@gmail.com
///////////////////////////////////////////////////////////////////////////////

#ifndef CCLIPBOARD_HSDFSEFF989SDF890SD8F
#define CCLIPBOARD_HSDFSEFF989SDF890SD8F

namespace nMech
{
	namespace nHEADER
	{

		class jClipboard
		{
		public:

			static void GetText(std::vector<TCHAR>& );
			static BOOL GetText(LPTSTR lpszBuffer, int nBufSize);
			static DWORD GetTextLength();
			static BOOL SetText(LPCTSTR lpszBuffer);
		};

		inline void jClipboard::GetText(std::vector<TCHAR>& buff)
		{
			// First, open the clipboard. OpenClipboard() takes one
			// parameter, the handle of the window that will temporarily
			// be it's owner. If NULL is passed, the current process
			// is assumed.
			if (::OpenClipboard(NULL))
			{
				// Request a pointer to the text on the clipboard.
#ifdef UNICODE
				HGLOBAL hGlobal = ::GetClipboardData(CF_UNICODETEXT);
#else
				HGLOBAL hGlobal = ::GetClipboardData(CF_TEXT);
#endif

				// If there was no text on the clipboard, we have
				// been returned a NULL handle.
				if (hGlobal)
				{
					// Now we have a global memory handle to the text
					// stored on the clipboard. We have to lock this global
					// handle so that we have access to it.
					LPTSTR lpszData = (LPTSTR) ::GlobalLock(hGlobal);

					if (lpszData)
					{
						size_t iLen = jt_strlen(lpszData);
						buff.resize(iLen+1);
						jt_strcpy(&buff[0] ,lpszData );
						// Now, simply unlock the global memory pointer
						// and close the clipboard.
						::GlobalUnlock(hGlobal);
					}
				}
				::CloseClipboard();
			}
		}

		///////////////////////////////////////////////////////////////////////////////
		// GetText - Retrieves text from the clipboard
		///////////////////////////////////////////////////////////////////////////////
		//
		// Parameters:
		//    lpszBuffer - pointer to a string where the text is to be put
		//    nBufSize   - allocated length of lpszBuffer
		//
		// Return Values:
		//    TRUE       - Text was successfully retrieved
		//    FALSE      - No text returned
		//
		///////////////////////////////////////////////////////////////////////////////

		inline BOOL jClipboard::GetText(LPTSTR lpszBuffer, int nBufSize)
		{
			assert(lpszBuffer);
			if (lpszBuffer == NULL)
				return FALSE;

			if (nBufSize == 0)
				return FALSE;

			lpszBuffer[0] = 0;

			BOOL bSuccess = FALSE;

			// First, open the clipboard. OpenClipboard() takes one
			// parameter, the handle of the window that will temporarily
			// be it's owner. If NULL is passed, the current process
			// is assumed.
			if (::OpenClipboard(NULL))
			{
				// Request a pointer to the text on the clipboard.
#ifdef UNICODE
				HGLOBAL hGlobal = ::GetClipboardData(CF_UNICODETEXT);
#else
				HGLOBAL hGlobal = ::GetClipboardData(CF_TEXT);
#endif

				// If there was no text on the clipboard, we have
				// been returned a NULL handle.
				if (hGlobal)
				{
					// Now we have a global memory handle to the text
					// stored on the clipboard. We have to lock this global
					// handle so that we have access to it.
					LPTSTR lpszData = (LPTSTR) ::GlobalLock(hGlobal);

					if (lpszData)
					{
						// Now get the size of the text on the clipboard.
						DWORD nSize = ::GlobalSize(hGlobal);

						// Make sure the text on the clipboard is not longer
						// that the buffer that was allocated for it. If it was
						// snip the text on the clipboard so that it fits.
						if (nSize >= (UINT)nBufSize)
							nSize = nBufSize - 1;

						// Now, copy the text into the return buffer. Note that
						// there will be at least one nul at the end
						ZeroMemory(lpszBuffer, nBufSize);
						CopyMemory(lpszBuffer, lpszData, nSize);

						// Now, simply unlock the global memory pointer
						// and close the clipboard.
						::GlobalUnlock(hGlobal);
						bSuccess = TRUE;
					}
				}
				::CloseClipboard();
			}

			return bSuccess;
		}

		///////////////////////////////////////////////////////////////////////////////
		// GetTextLength - Retrieves length of text on the clipboard
		///////////////////////////////////////////////////////////////////////////////
		//
		// Parameters:
		//
		// Return Values:
		//	> 0    - Text length was successfully returned.
		//	0      - No text on the clipboard
		//
		///////////////////////////////////////////////////////////////////////////////

		inline DWORD jClipboard::GetTextLength()
		{
			DWORD nSize = 0;		// Size of clipboard data

			// First, open the clipboard. OpenClipboard() takes one
			// parameter, the handle of the window that will temporarily
			// be it's owner. If NULL is passed, the current process
			// is assumed.
			if (::OpenClipboard(NULL))
			{
				// Request a pointer to the text on the clipboard.
				HGLOBAL hGlobal = ::GetClipboardData(CF_TEXT);

				// If there was no text on the clipboard, we have
				// been returned a NULL handle.
				if (hGlobal)
				{
					// Now we have a global memory handle to the text
					// stored on the clipboard. We have to lock this global
					// handle so that we have access to it.
					LPSTR lpszData = (LPSTR) ::GlobalLock(hGlobal);

					if (lpszData)
					{
						// Now get the size of the text on the clipboard.
						nSize = ::GlobalSize(hGlobal);

						// Now, simply unlock the global memory pointer
						// and close the clipboard.
						::GlobalUnlock(hGlobal);
					}
				}
				::CloseClipboard();
			}

			return nSize;
		}

		///////////////////////////////////////////////////////////////////////////////
		// SetText - Places text on the clipboard
		///////////////////////////////////////////////////////////////////////////////
		//
		// Parameters:
		//	lpszBuffer - pointer to a string to put on the clipboard
		//
		// Return Values:
		//	TRUE       - Text was successfully copied onto clipboard
		//	FALSE      - Text not copied
		//
		///////////////////////////////////////////////////////////////////////////////

		inline BOOL jClipboard::SetText(LPCTSTR lpszBuffer)
		{
			BOOL bSuccess = FALSE;

			// First, open the clipboard. OpenClipboard() takes one
			// parameter, the handle of the window that will temporarily
			// be it's owner. If NULL is passed, the current process
			// is assumed. After opening, empty the clipboard so we
			// can put our text on it.
			if (::OpenClipboard(NULL))
			{
				::EmptyClipboard();

				// Get the size of the string in the buffer that was
				// passed into the function, so we know how much global
				// memory to allocate for the string.
				size_t nSize = _tcslen(lpszBuffer);

				// Allocate the memory for the string.
				HGLOBAL hGlobal = ::GlobalAlloc(GMEM_ZEROINIT, (nSize+1)*sizeof(TCHAR));

				// If we got any error during the memory allocation,
				// we have been returned a NULL handle.
				if (hGlobal)
				{
					// Now we have a global memory handle to the text
					// stored on the clipboard. We have to lock this global
					// handle so that we have access to it.
					LPTSTR lpszData = (LPTSTR) ::GlobalLock(hGlobal);

					if (lpszData)
					{
						// Now, copy the text from the buffer into the allocated
						// global memory pointer
						_tcscpy(lpszData, lpszBuffer);

						// Now, simply unlock the global memory pointer,
						// set the clipboard data type and pointer,
						// and close the clipboard.
						::GlobalUnlock(hGlobal);
#ifdef _UNICODE
						::SetClipboardData(CF_UNICODETEXT, hGlobal);
#else
						::SetClipboardData(CF_TEXT, hGlobal);
#endif
						bSuccess = TRUE;
					}
				}
				::CloseClipboard();
			}

			return bSuccess;
		}

	}//nHEADER
}//nMech


#endif //CCLIPBOARD_HSDFSEFF989SDF890SD8F