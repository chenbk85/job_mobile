// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "notepadre.h"

// Required for CControlBarInfo definition
#include <afxpriv.h>

#include "enums.h"
#include <htmlhelp.h>
#include "MainFrm.h"
#include "messages.h"
#include "NotepadreDoc.h"
#include "NotepadreView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DROP_FILES, OnUpdateOptionsDropFiles)
	ON_COMMAND(ID_OPTIONS_DROP_FILES, OnOptionsDropFiles)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_HELP_REGEX, OnHelpRegex)
	ON_MESSAGE (WM_NOTIFY_FIND_REPLACE, OnNotifyFindReplace)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_EDIT_REPLACE, OnEditReplace)
	ON_COMMAND(IDOK, OnEditFind)
	ON_COMMAND(IDC_BUTTON_REPLACE, OnEditReplace)
	ON_COMMAND(IDC_BUTTON_REPLACE_ALL, OnEditReplace)
	ON_COMMAND(IDCANCEL, OnEditReplace)
	ON_COMMAND(IDC_BUTTON_HELP, OnHelpRegex)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	// Global help commands
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	0,						// Display Line and Column
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame () :
	m_bDropFiles (true)
{
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::DisplayLineAndColumn ()
{
	CEditView *pView =
		static_cast<CEditView *> (GetActiveView ());

	if (pView)
	{
		int iLine = pView->GetEditCtrl().LineFromChar ();
		int iStart = 0, iEnd = 0;
		CString strLnColFmt;
		CString strLine;

		strLnColFmt.LoadString (IDS_LN_COL_FMT);
		pView->GetEditCtrl().GetSel (iStart, iEnd);
		strLine.Format (strLnColFmt, iLine + 1,
			iStart - pView->GetEditCtrl().LineIndex (iLine) + 1);
		m_wndStatusBar.SetPaneText (1, strLine);
	}
}

int CMainFrame::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
	HKEY hKey = 0;
	CString strNotepadRegKey;
	CString strEntry;
	LONG lRet = 0;
	ULONG ulSize = 4;
	DWORD dwType = 0;
	DWORD dwViewStatusBar = 1;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	strNotepadRegKey.LoadString (IDS_NOTEPAD_REG_KEY);
	lRet =::RegOpenKey (HKEY_CURRENT_USER, strNotepadRegKey, &hKey);

	if (lRet == ERROR_SUCCESS)
	{
		int iWidth = 0, iHeight = 0, iX = 0, iY = 0;

		strEntry.LoadString (IDS_WINDOW_POS_DX);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) (&iWidth), &ulSize);
		strEntry.LoadString (IDS_WINDOW_POS_DY);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &iHeight, &ulSize);
		strEntry.LoadString (IDS_WINDOW_POS_X);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &iX, &ulSize);
		strEntry.LoadString (IDS_WINDOW_POS_Y);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &iY, &ulSize);
		MoveWindow (iX, iY, iWidth, iHeight);
		strEntry.LoadString (IDS_VIEW_STATUS_BAR);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwViewStatusBar, &ulSize);
		::RegCloseKey (hKey);
	}

	if (!m_wndToolBar.CreateEx (this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE |
		CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY |
		CBRS_SIZE_DYNAMIC) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		CString strFailedToCreateToolbar;

		strFailedToCreateToolbar.LoadString (IDS_FAILED_TO_CREATE_TOOLBAR);
		TRACE(strFailedToCreateToolbar);
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		CString strFailedToCreateStatusBar;

		strFailedToCreateStatusBar.
			LoadString (IDS_FAILED_TO_CREATE_STATUS_BAR);
		TRACE(strFailedToCreateStatusBar);
		return -1;      // fail to create
	}

	// Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking (CBRS_ALIGN_ANY);
	DockControlBar (&m_wndToolBar);

	UINT uiID;
	UINT uiStyle;
	int iWidth;
	CDC *pDC = 0;
	CString strLnColMax;
	CRect rectArea;

	m_wndStatusBar.GetPaneInfo (1, uiID, uiStyle, iWidth);
	pDC = m_wndStatusBar.GetDC ();
	pDC->SelectObject (m_wndStatusBar.GetFont ());
	strLnColMax.LoadString (IDS_LN_COL_MAX);
	pDC->DrawText(strLnColMax, -1,
		&rectArea, DT_SINGLELINE | DT_CALCRECT);
	m_wndStatusBar.ReleaseDC (pDC);
	m_wndStatusBar.SetPaneInfo (1, uiID, uiStyle, rectArea.Width ());

	// Process after toolbar and status bar created.
	strNotepadRegKey.LoadString (IDS_NOTEPADRE_REG_KEY);
	lRet = ::RegCreateKey (HKEY_CURRENT_USER, strNotepadRegKey, &hKey);

	DWORD dwFindDocked = 0;
	DWORD dwFindDockId = 0;
	DWORD dwReplaceDocked = 0;
	DWORD dwReplaceDockId = 0;

	if (lRet == ERROR_SUCCESS)
	{
		DWORD dwDropFiles = 1;
		DWORD dwViewToolBar = 1;
		CString strEntry;

		strEntry.LoadString (IDS_DROP_FILES);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwDropFiles, &ulSize);
		m_bDropFiles = dwDropFiles != 0;
		strEntry.LoadString (IDS_VIEW_TOOL_BAR);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwViewToolBar, &ulSize);
		m_wndToolBar.ShowWindow (dwViewToolBar ? SW_SHOW : SW_HIDE);
		strEntry.LoadString (IDS_FIND_DOCKED);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwFindDocked, &ulSize);
		strEntry.LoadString (IDS_FIND_DOCK_ID);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwFindDockId, &ulSize);
		strEntry.LoadString (IDS_REPLACE_DOCKED);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwReplaceDocked, &ulSize);
		strEntry.LoadString (IDS_REPLACE_DOCK_ID);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwReplaceDockId, &ulSize);
		::RegCloseKey (hKey);
	}

	m_wndStatusBar.ShowWindow (dwViewStatusBar ? SW_SHOW : SW_HIDE);

	m_wndFindBar.SetInitial (this, IDD_FIND);
	m_wndFindBar.Create (this, IDD_FIND, CBRS_ALIGN_BOTTOM/*CBRS_FLOATING*/ |
		CBRS_BORDER_3D | CBRS_GRIPPER, IDD_FIND);
	ShowControlBar (&m_wndFindBar, FALSE, FALSE);
	m_wndFindBar.EnableDocking (CBRS_ALIGN_ANY);

	if (dwFindDocked)
	{
		DockControlBar (&m_wndFindBar, dwFindDockId);

		CRect rect;
		CPoint pt;

		m_wndFindBar.GetDockingFrame ()->GetClientRect (&rect);
		pt = rect.CenterPoint ();

		if (dwFindDockId == AFX_IDW_DOCKBAR_TOP ||
			dwFindDockId == AFX_IDW_DOCKBAR_BOTTOM)
		{
			m_wndFindBar.MoveWindow (pt.x -
				m_wndFindBar.m_sizeDefault.cx / 2, 0, 0, 0);
		}
		else
		{
			m_wndFindBar.MoveWindow (0,
				pt.y - m_wndFindBar.m_sizeDefault.cy / 2, 0, 0);
		}
	}
	else
	{
		FloatControlBar (&m_wndFindBar, CPoint (0, 0));
	}

	m_wndReplaceBar.SetInitial (this, IDD_FIND_REPLACE);
	m_wndReplaceBar.Create (this, IDD_FIND_REPLACE, CBRS_FLOATING |
		CBRS_BORDER_3D | CBRS_GRIPPER, IDD_FIND_REPLACE);
	ShowControlBar (&m_wndReplaceBar, FALSE, FALSE);
	m_wndReplaceBar.EnableDocking (CBRS_ALIGN_ANY);

	if (dwReplaceDocked)
	{
		DockControlBar (&m_wndReplaceBar, dwReplaceDockId);

		CRect rect;
		CPoint pt;

		m_wndReplaceBar.GetDockingFrame ()->GetClientRect (&rect);
		pt = rect.CenterPoint ();
		m_wndReplaceBar.MoveWindow (pt.x -
			m_wndReplaceBar.m_sizeDefault.cx / 2, 0, 0, 0);

		if (dwReplaceDockId == AFX_IDW_DOCKBAR_TOP ||
			dwReplaceDockId == AFX_IDW_DOCKBAR_BOTTOM)
		{
			m_wndReplaceBar.MoveWindow (pt.x -
				m_wndReplaceBar.m_sizeDefault.cx / 2, 0, 0, 0);
		}
		else
		{
			m_wndReplaceBar.MoveWindow (0,
				pt.y - m_wndReplaceBar.m_sizeDefault.cy / 2, 0, 0);
		}
	}
	else
	{
		FloatControlBar (&m_wndReplaceBar, CPoint (0, 0));
	}

	return 0;
}

void CMainFrame::OnDestroy()
{
	WINDOWPLACEMENT wp;

	if (GetWindowPlacement (&wp))
	{
		LONG lDX = wp.rcNormalPosition.right - wp.rcNormalPosition.left;
		LONG lDY = wp.rcNormalPosition.bottom - wp.rcNormalPosition.top;
		LONG lX = wp.rcNormalPosition.left;
		LONG lY = wp.rcNormalPosition.top;
		CString strNotepadRegKey;
		CString strEntry;
		HKEY hKey = 0;
		DWORD dwType = REG_DWORD;
		ULONG ulSize = sizeof (REG_DWORD);
		LONG lRet = 0;

		strNotepadRegKey.LoadString (IDS_NOTEPAD_REG_KEY);
		lRet = ::RegOpenKey (HKEY_CURRENT_USER, strNotepadRegKey, &hKey);

		if (lRet == ERROR_SUCCESS)
		{
			CControlBar* pBar = 0;
			DWORD dwViewStatusBar = 0;

			strEntry.LoadString (IDS_WINDOW_POS_DX);
			lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
				(unsigned char *) &lDX, ulSize);
			strEntry.LoadString (IDS_WINDOW_POS_DY);
			lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
				(unsigned char *) &lDY, ulSize);
			strEntry.LoadString (IDS_WINDOW_POS_X);
			lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
				(unsigned char *) &lX, ulSize);
			strEntry.LoadString (IDS_WINDOW_POS_Y);
			lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
				(unsigned char *) &lY, ulSize);
			pBar = GetControlBar (AFX_IDW_STATUS_BAR);
			dwViewStatusBar = (pBar->GetStyle() & WS_VISIBLE) != 0;
			strEntry.LoadString (IDS_VIEW_STATUS_BAR);
			lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
				(unsigned char *) &dwViewStatusBar, ulSize);
			::RegCloseKey (hKey);
		}

		strNotepadRegKey.LoadString (IDS_NOTEPADRE_REG_KEY);
		lRet = ::RegCreateKey (HKEY_CURRENT_USER, strNotepadRegKey, &hKey);

		if (lRet == ERROR_SUCCESS)
		{
			DWORD dwDropFiles = m_bDropFiles ? 1 : 0;
			DWORD dwViewToolBar = 0;
			CControlBar* pBar = 0;

			strEntry.LoadString (IDS_DROP_FILES);
			lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
				(unsigned char *) &dwDropFiles, ulSize);
			strEntry.LoadString (IDS_VIEW_TOOL_BAR);
			pBar = GetControlBar (AFX_IDW_TOOLBAR);
			dwViewToolBar = (pBar->GetStyle() & WS_VISIBLE) != 0;
			lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
				(unsigned char *) &dwViewToolBar, ulSize);
			::RegCloseKey (hKey);
		}
	}

	CFrameWnd::OnDestroy ();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnHelpFinder()
{
	CString strNotepadChm;

	strNotepadChm.LoadString (IDS_NOTEPAD_CHM);
	::HtmlHelp (0/*GetActiveView ()->m_hWnd*/, strNotepadChm, HH_DISPLAY_TOPIC,
		0);
}

void CMainFrame::OnHelpRegex ()
{
	CString strHelpFile;

#ifdef _DEBUG
	strHelpFile.LoadString (IDS_RELEASE_NOTEPADRE_CHM);
#else
	CString strHlp;
	CString strChm;

	strHlp.LoadString (IDS_DOT_HLP);
	strChm.LoadString (IDS_DOT_CHM);
	strHelpFile	= AfxGetApp ()->m_pszHelpFilePath;
	strHelpFile.Replace (strHlp, strChm);
#endif

	::HtmlHelp (0/*GetActiveView ()->m_hWnd*/, strHelpFile,
		HH_DISPLAY_TOPIC, 0);
}

void CMainFrame::OnEditFind ()
{
	if (m_wndReplaceBar.IsWindowVisible ())
	{
		ShowControlBar (&m_wndReplaceBar, FALSE, FALSE);
	}

	if (!m_wndFindBar.IsWindowVisible ())
	{
		CNotepadreDoc *pDoc = static_cast<CNotepadreView *>
			(GetActiveView ())->GetDocument ();

		m_wndFindBar.SetFindText (pDoc->GetFindText ());
		m_wndFindBar.SetWholeWordOnly (pDoc->GetWholeWordOnly ());
		m_wndFindBar.SetMatchCase (pDoc->GetMatchCase ());
		m_wndFindBar.SetRegEx (pDoc->GetRegEx ());
		m_wndFindBar.SetSearchUp (!pDoc->GetSearchForward ());
		m_wndFindBar.SetCloseOnMatch (pDoc->GetCloseOnMatch ());

		if (m_wndFindBar.IsFloating ())
		{
			CRect rect;
			CPoint pt;
			CPoint ptDlg;

			GetWindowRect (rect);
			pt = rect.CenterPoint ();
			ptDlg = m_wndFindBar.m_sizeDefault;
			FloatControlBar (&m_wndFindBar,
				CPoint (pt.x - ptDlg.x / 2, pt.y - ptDlg.y / 2));
		}

		ShowControlBar (&m_wndFindBar, TRUE, FALSE);
	}

	m_wndFindBar.SetFocus ();
}

void CMainFrame::OnEditReplace ()
{
	CNotepadreDoc *pDoc = static_cast<CNotepadreView *>
		(GetActiveView ())->GetDocument ();

	if (m_wndFindBar.IsWindowVisible ())
	{
		ShowControlBar (&m_wndFindBar, FALSE, FALSE);
	}

	pDoc->SetSearchForward (true);

	if (!m_wndReplaceBar.IsWindowVisible ())
	{
		m_wndReplaceBar.SetFindText (pDoc->GetFindText ());
		m_wndReplaceBar.SetReplaceText (pDoc->GetReplaceText ());
		m_wndReplaceBar.SetWholeWordOnly (pDoc->GetWholeWordOnly ());
		m_wndReplaceBar.SetMatchCase (pDoc->GetMatchCase ());
		m_wndReplaceBar.SetRegEx (pDoc->GetRegEx ());
		m_wndReplaceBar.SetReplaceText (pDoc->GetReplaceText ());
		m_wndReplaceBar.SetReplaceAllLikeNotepad (pDoc->
			GetReplaceAllLikeNotepad ());

		if (m_wndReplaceBar.IsFloating ())
		{
			CRect rect;
			CPoint pt;
			CPoint ptDlg;

			GetWindowRect (rect);
			pt = rect.CenterPoint ();
			ptDlg = m_wndReplaceBar.m_sizeDefault;
			FloatControlBar (&m_wndReplaceBar,
				CPoint (pt.x - ptDlg.x / 2, pt.y - ptDlg.y / 2));
		}

		ShowControlBar (&m_wndReplaceBar, TRUE, FALSE);
	}

	m_wndReplaceBar.SetFocus ();
}

LRESULT CMainFrame::OnNotifyFindReplace (WPARAM wParam, LPARAM lParam)
{
	if (wParam == eClose)
	{
		SetFocus ();

		if (m_wndFindBar.IsWindowVisible ())
		{
			ShowControlBar (&m_wndFindBar, FALSE, FALSE);
		}
		else
		{
			ShowControlBar (&m_wndReplaceBar, FALSE, FALSE);
		}
	}
	else
	{
		static_cast<CNotepadreView *> (GetActiveView ())->GetDocument ()->
			OnNotifyFindReplace (wParam, lParam);
	}

	return 0;
}

void CMainFrame::OnUpdateOptionsDropFiles(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_bDropFiles);
}

void CMainFrame::OnOptionsDropFiles()
{
	m_bDropFiles = !m_bDropFiles;
}

void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
	if (m_bDropFiles)
	{
		CFrameWnd::OnDropFiles(hDropInfo);
	}
	else
	{
		CEditView *pView =
			static_cast<CEditView *> (GetActiveView ());

		if (pView)
		{
			SetActiveWindow();      // activate us first !

			UINT uiFiles = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);
			CWinApp* pApp = AfxGetApp();
			CString strCRLF;
			CString strFileName;

			strCRLF.LoadString (IDS_CR_LF);
			ASSERT(pApp != NULL);

			for (UINT uiFile = 0; uiFile < uiFiles; uiFile++)
			{
				UINT uiLen = ::DragQueryFile(hDropInfo, uiFile, 0, 0);
				TCHAR *pszFileName = new TCHAR[uiLen + 1];

				::DragQueryFile(hDropInfo, uiFile, pszFileName, uiLen + 1);
				strFileName += pszFileName;
				strFileName += strCRLF;
				delete[] pszFileName;
			}

			pView->GetEditCtrl ().ReplaceSel (strFileName, TRUE);
			::DragFinish(hDropInfo);
		}
	}
}

void CMainFrame::OnClose() 
{
	CString strNotepadreRegKey;
	LONG lRet = 0;
	HKEY hKey = 0;

	strNotepadreRegKey.LoadString (IDS_NOTEPADRE_REG_KEY);
	lRet = ::RegOpenKey (HKEY_CURRENT_USER, strNotepadreRegKey, &hKey);

	if (lRet == ERROR_SUCCESS)
	{
		CString strEntry;
		DWORD dwType = REG_DWORD;
		ULONG ulSize = sizeof (REG_DWORD);
		DWORD dwDocked = 0;
		DWORD dwDockId = 0;

		strEntry.LoadString (IDS_FIND_DOCKED);
		dwDocked = !m_wndFindBar.IsFloating ();
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwDocked, ulSize);

		if (dwDocked)
		{
			CControlBarInfo info;

			m_wndFindBar.GetBarInfo (&info);
			dwDockId = info.m_uMRUDockID;

			if (info.m_uMRUDockID != 0)
			{
				strEntry.LoadString (IDS_FIND_DOCK_ID);
				lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
					(unsigned char *) &dwDockId, ulSize);
			}
		}
		else
		{
			dwDockId = 0;
			strEntry.LoadString (IDS_FIND_DOCK_ID);
			lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
				(unsigned char *) &dwDockId, ulSize);
		}

		strEntry.LoadString (IDS_REPLACE_DOCKED);
		dwDocked = !m_wndReplaceBar.IsFloating ();
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwDocked, ulSize);

		if (dwDocked)
		{
			CControlBarInfo info;

			m_wndReplaceBar.GetBarInfo (&info);
			dwDockId = info.m_uMRUDockID;

			if (info.m_uMRUDockID != 0)
			{
				strEntry.LoadString (IDS_REPLACE_DOCK_ID);
				lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
					(unsigned char *) &dwDockId, ulSize);
			}
		}
		else
		{
			dwDockId = 0;
			strEntry.LoadString (IDS_REPLACE_DOCK_ID);
			lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
				(unsigned char *) &dwDockId, ulSize);
		}

		::RegCloseKey (hKey);
	}

	CFrameWnd::OnClose();
}
