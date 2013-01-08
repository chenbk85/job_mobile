#include "stdafx.h"

#include <htmlhelp.h>

#include "MyDocManager.h"
#include "MainFrm.h"
#include "notepadreDoc.h"

#include "resource.h"

#include <DLGS.H>

#ifdef _UNICODE
struct OFN
{
   DWORD        lStructSize;
   HWND         hwndOwner;
   HINSTANCE    hInstance;
   LPCWSTR      lpstrFilter;
   LPWSTR       lpstrCustomFilter;
   DWORD        nMaxCustFilter;
   DWORD        nFilterIndex;
   LPWSTR       lpstrFile;
   DWORD        nMaxFile;
   LPWSTR       lpstrFileTitle;
   DWORD        nMaxFileTitle;
   LPCWSTR      lpstrInitialDir;
   LPCWSTR      lpstrTitle;
   DWORD        Flags;
   WORD         nFileOffset;
   WORD         nFileExtension;
   LPCWSTR      lpstrDefExt;
   LPARAM       lCustData;
   LPOFNHOOKPROC lpfnHook;
   LPCWSTR      lpTemplateName;
   void *		pvReserved;
   DWORD        dwReserved;
   DWORD        FlagsEx;
};

#else
struct OFN
{
   DWORD        lStructSize;
   HWND         hwndOwner;
   HINSTANCE    hInstance;
   LPCSTR       lpstrFilter;
   LPSTR        lpstrCustomFilter;
   DWORD        nMaxCustFilter;
   DWORD        nFilterIndex;
   LPSTR        lpstrFile;
   DWORD        nMaxFile;
   LPSTR        lpstrFileTitle;
   DWORD        nMaxFileTitle;
   LPCSTR       lpstrInitialDir;
   LPCSTR       lpstrTitle;
   DWORD        Flags;
   WORD         nFileOffset;
   WORD         nFileExtension;
   LPCSTR       lpstrDefExt;
   LPARAM       lCustData;
   LPOFNHOOKPROC lpfnHook;
   LPCSTR       lpTemplateName;
   void *		pvReserved;
   DWORD        dwReserved;
   DWORD        FlagsEx;
};
#endif

CNotepadreFile::e_FileType CMyDocManager::m_eFileType =
	CNotepadreFile::e_FileType::eANSI;
CNotepadreFile::e_FileFormat CMyDocManager::m_eFileFormat =
	CNotepadreFile::e_FileFormat::eWindows;

CMyDocManager::CMyDocManager () :
	CDocManager ()
{
}

CMyDocManager::~CMyDocManager ()
{
}

UINT CALLBACK CMyDocManager::OFNSaveHookProc (HWND hdlg, UINT uiMsg,
	WPARAM wParam, LPARAM lParam)
{
	UINT uiProcessed = 0;

	switch (uiMsg)
	{
		case WM_INITDIALOG :
		{
			HWND hCtrl = ::GetDlgItem (hdlg, IDC_COMBO_ENCODING);
			CString strEntry;

			strEntry.LoadString (IDS_ANSI);
			::SendMessage (hCtrl, CB_ADDSTRING, 0,
				(WPARAM) (const TCHAR *) strEntry);
			strEntry.LoadString (IDS_UNICODE);
			::SendMessage (hCtrl, CB_ADDSTRING, 0,
				(WPARAM) (const TCHAR *) strEntry);
			strEntry.LoadString (IDS_UNICODE_BIG_ENDIAN);
			::SendMessage (hCtrl, CB_ADDSTRING, 0,
				(WPARAM) (const TCHAR *) strEntry);
			strEntry.LoadString (IDS_UTF_8);
			::SendMessage (hCtrl, CB_ADDSTRING, 0,
				(WPARAM) (const TCHAR *) strEntry);
			::SendMessage (hCtrl, CB_SETCURSEL, m_eFileType, 0);

			hCtrl = ::GetDlgItem (hdlg, IDC_COMBO_FORMAT);
			strEntry.LoadString (IDS_WINDOWS);
			::SendMessage (hCtrl, CB_ADDSTRING, 0,
				(WPARAM) (const TCHAR *) strEntry);
			strEntry.LoadString (IDS_UNIX);
			::SendMessage (hCtrl, CB_ADDSTRING, 0,
				(WPARAM) (const TCHAR *) strEntry);
			strEntry.LoadString (IDS_MACINTOSH);
			::SendMessage (hCtrl, CB_ADDSTRING, 0,
				(WPARAM) (const TCHAR *) strEntry);
			::SendMessage (hCtrl, CB_SETCURSEL, m_eFileFormat, 0);
			uiProcessed = 1;
			break;
		}
		case WM_COMMAND :
		{
			if (HIWORD (wParam) == CBN_SELCHANGE)
			{
				if (LOWORD (wParam) == IDC_COMBO_ENCODING)
				{
					m_eFileType = (CNotepadreFile::e_FileType)
					::SendMessage ((HWND) lParam, CB_GETCURSEL, 0, 0);
				}
				else
				{
					m_eFileFormat = (CNotepadreFile::e_FileFormat)
					::SendMessage ((HWND) lParam, CB_GETCURSEL, 0, 0);
				}

				uiProcessed = 1;
			}

			break;
		}
		case WM_HELP :
			{
				LPHELPINFO pHelpInfo = (LPHELPINFO) lParam;
				HWND hWnd =0;
				HH_POPUP popup;
				RECT rect;
				CString strArial8;

				switch (pHelpInfo->iCtrlId)
				{
					case IDC_COMBO_ENCODING :
						hWnd = ::GetDlgItem (hdlg, IDC_COMBO_ENCODING);
						popup.idString = IDS_ENCODING_HELP;
						break;
					case IDC_COMBO_FORMAT :
						hWnd = ::GetDlgItem (hdlg, IDC_COMBO_FORMAT);
						popup.idString = IDS_FORMAT_HELP;
						break;
				}

				if (hWnd)
				{
					::GetWindowRect (hWnd, &rect);
					popup.cbStruct = sizeof (popup);
					popup.hinst = AfxGetResourceHandle ();
					popup.pszText = 0;
					popup.pt.x = rect.left;
					popup.pt.y = rect.top;
					popup.clrForeground = -1;
					popup.clrBackground = -1;
					popup.rcMargins.top = 7;
					popup.rcMargins.left = 20;
					popup.rcMargins.bottom = 7;
					popup.rcMargins.right = 7;
					strArial8.LoadString (IDS_ARIAL_8);
					popup.pszFont = strArial8;
					::HtmlHelp (0, 0, HH_DISPLAY_TEXT_POPUP, (DWORD) &popup);
					uiProcessed = 1;
				}

				break;
			}
		default : ;
	}

	return uiProcessed;
}

BOOL CMyDocManager::DoPromptFileName (CString& fileName, UINT nIDSTitle,
	DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
	LPCTSTR lpcstrFilter =
		_T("Text Documents (*.txt)\0*.txt\0")
		_T("All Files\0*.*\0")
		_T("");
	OFN ofn;
	BOOL bFileSelected = FALSE;
	CString title;

	VERIFY(title.LoadString(nIDSTitle));

	memset (&ofn, 0, sizeof (ofn));
	ofn.lStructSize = sizeof (ofn);
	ofn.lpstrTitle = title;
	ofn.hwndOwner = ::GetFocus ();
	ofn.lpstrFilter = lpcstrFilter;
	ofn.lpstrFile = fileName.GetBuffer (_MAX_PATH);
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = lFlags | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = _T(".txt");

	if (bOpenFileDialog)
	{
		CMainFrame *pFrame = static_cast<CMainFrame *> (AfxGetMainWnd ());
		CNotepadreDoc *pDoc = static_cast<CNotepadreDoc *>
			(static_cast<CMainFrame *>(pFrame)->GetActiveDocument ());

		m_bReadOnly = pDoc->GetReadOnly ();
		ofn.Flags &= ~OFN_HIDEREADONLY;
		ofn.Flags |= OFN_EXPLORER | OFN_ENABLESIZING;
		_tcscpy (ofn.lpstrFile, _T("*.txt"));
		ofn.hInstance = AfxGetResourceHandle ();

		if (m_bReadOnly) ofn.Flags |= OFN_READONLY;

#ifdef _UNICODE
		bFileSelected = ::GetOpenFileName ((struct tagOFNW *) &ofn);
#else
		bFileSelected = ::GetOpenFileName ((struct tagOFNA *) &ofn);
#endif

		m_bReadOnly = ofn.Flags & OFN_READONLY;
	}
	else
	{
		CMainFrame *pFrame = static_cast<CMainFrame *> (AfxGetMainWnd ());
		CNotepadreDoc *pDoc = static_cast<CNotepadreDoc *>
			(static_cast<CMainFrame *>(pFrame)->GetActiveDocument ());

		pDoc->GetFileType (m_eFileType, m_eFileFormat);
		ofn.Flags |= OFN_EXPLORER | OFN_ENABLEHOOK | OFN_ENABLETEMPLATE |
			OFN_ENABLESIZING;
		ofn.hInstance = AfxGetResourceHandle ();
		ofn.lpTemplateName = MAKEINTRESOURCE (IDD_ENCODING_FILE_DLG);
		ofn.lpfnHook = OFNSaveHookProc;

#ifdef _UNICODE
		bFileSelected = ::GetSaveFileName ((struct tagOFNW *) &ofn);
#else
		bFileSelected = ::GetSaveFileName ((struct tagOFNA *) &ofn);
#endif
	}

	fileName.ReleaseBuffer ();

	if (bFileSelected)
	{
		CMainFrame *pFrame = static_cast<CMainFrame *> (AfxGetMainWnd ());
		CNotepadreDoc *pDoc = static_cast<CNotepadreDoc *>
			(static_cast<CMainFrame *>(pFrame)->GetActiveDocument ());

		if (bOpenFileDialog)
		{
			pDoc->SetReadOnly (m_bReadOnly);
		}
		else
		{
			pDoc->SetFileType (m_eFileType, m_eFileFormat);
		}
	}

	return bFileSelected;
}
