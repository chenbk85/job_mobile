// MainFrm.cpp : implementation of the CMainFrame class
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Grep.h"
#include "GrepView.h"

#include "SearchOptions.h"
#include "MainFrm.h"
#include "SearchThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TID_REFRESH 100

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_OPTIONSPANE, OnViewOptionspane)
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_MESSAGE_VOID(WM_SEARCHFINISHED, OnFindDone)
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// get path of executable
	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));

	LPTSTR lpszExt = _tcsrchr(szBuff, '.');
	lstrcpy(lpszExt, _T(".xml"));

	m_strIniFileName = szBuff;

	m_pSearchThread = NULL;
	m_nTimer = 0;

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create Status bar.
	// Important: All control bars including the Status Bar
	// must be created before CommandBars....
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	// Add the menu bar
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(
		_T("Menu Bar"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}

	// Create ToolBar
	CXTPToolBar* pToolBar = (CXTPToolBar*)
		pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);

	// Set Office 2003 Theme
	CXTPPaintManager::SetTheme(xtpThemeWhidbey);

	if (pCommandBars->GetImageManager()->IsAlphaIconsSupported())
	{
		pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDB_TOOLBAR_ALPHA);
	}

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));

	// Initialize the docking pane manager and set the
	// initial them for the docking panes.  Do this only after all
	// control bars objects have been created and docked.
	m_paneManager.InstallDockingPanes(this);
	// Set Office 2003 Theme
	m_paneManager.SetTheme(xtpPaneThemeWhidbey);

	m_paneManager.SetAlphaDockingContext(TRUE);
	m_paneManager.SetShowDockingContextStickers(TRUE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);

	// Create docking panes.
	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(
		IDR_PANE_OPTIONS, CRect(0, 0,200, 120), xtpPaneDockLeft);

	pwndPane1->SetMinTrackSize(CSize(177, 0));

	// Set the icons for the docking pane tabs.
	int nIDIcons[] = {IDR_PANE_OPTIONS, IDR_PANE_PROPERTIES};
		m_paneManager.SetIcons(IDB_BITMAP_ICONS, nIDIcons,
		_countof(nIDIcons), RGB(0, 255, 0));

	CXTPPropExchangeXMLNode px(TRUE, 0, _T("Settings"));

	if (px.LoadFromFile(m_strIniFileName))
	{
		CXTPPropExchangeSection pxCommandBars(px.GetSection(_T("CommandBars")));
		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; param.bSerializeControls = TRUE;
		GetCommandBars()->DoPropExchange(&pxCommandBars, &param);

		CXTPPropExchangeSection pxDockingPane(px.GetSection(_T("DockingPane")));
		CXTPDockingPaneLayout layoutNormal(&m_paneManager);
		if (layoutNormal.DoPropExchange(&pxDockingPane))
		{
			m_paneManager.SetLayout(&layoutNormal);
		}

		CXTPPropExchangeSection pxOptions(px.GetSection(_T("Options")));
		GetSearchOptions()->DoPropExchange(&pxOptions);
	}

	return 0;
}

void CMainFrame::OnClose()
{
	if (m_pSearchThread)
	{
		m_pSearchThread->m_bCancel = TRUE;
		WaitForSingleObject(m_pSearchThread->m_hThread, INFINITE);

		m_pSearchThread = NULL;
	}


	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));

	if (px.OnBeforeExchange()) 
	{
		CXTPPropExchangeSection pxCommandBars(px.GetSection(_T("CommandBars")));
		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; param.bSerializeControls = TRUE; param.bSaveOriginalControls = FALSE;
		GetCommandBars()->DoPropExchange(&pxCommandBars, &param);

		CXTPPropExchangeSection pxDockingPane(px.GetSection(_T("DockingPane")));

		CXTPDockingPaneLayout layoutNormal(&m_paneManager);
		m_paneManager.GetLayout(&layoutNormal);
		layoutNormal.DoPropExchange(&pxDockingPane);

		CXTPPropExchangeSection pxOptions(px.GetSection(_T("Options")));
		GetSearchOptions()->DoPropExchange(&pxOptions);

		px.SaveToFile(m_strIniFileName);
	}


	CFrameWnd::OnClose();
}

void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instanciate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

		// Add the options page to the customize dialog.
		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		// Add the commands page to the customize dialog.
		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_MAINFRAME);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
}

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;

		if (!pPane->IsValid())
		{
			switch (pPane->GetID())
			{
			case IDR_PANE_OPTIONS:
				{
					CWnd* pView = pPane->AttachView(this, RUNTIME_CLASS(CSearchOptionsView));
					if (pView && ::IsWindow(pView->m_hWnd))
					{
						pView->SendMessage(WM_INITIALUPDATE);
					}
					break;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
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

void AddComboHistory(CComboBox& cmb, CString strText, CStringList& lstHistory)
{
	if (strText.IsEmpty())
		return;
	
	int nIndex = cmb.FindString(-1, strText);
	if (nIndex == -1)
	{
		cmb.InsertString(0, strText);
		lstHistory.AddHead(strText);
	}
}

void CMainFrame::OnFindDone()
{
	if (m_nTimer != NULL)
	{
		KillTimer(TID_REFRESH);
		m_nTimer = 0;
	}
	
	m_pSearchThread = NULL;

	CSearchOptionsView* pOptionsView = GetSearchOptionsView();
	pOptionsView->SetSearchMode(FALSE);

	CXTPReportView* pView = DYNAMIC_DOWNCAST(CXTPReportView, GetDescendantWindow(AFX_IDW_PANE_FIRST));
	ASSERT(pView);

	if (!pView)
		return;

	pOptionsView->GetDlgItem(IDC_BUTTON_REPLACEALL)->EnableWindow(pView->GetReportCtrl().GetRecords()->GetCount() > 0);

	pView->GetReportCtrl().Populate();
}

void CMainFrame::OnCancelFind()
{
	if (m_nTimer != NULL)
	{
		KillTimer(TID_REFRESH);
		m_nTimer = 0;
	}
	
	ASSERT(m_pSearchThread != NULL);
	
	m_pSearchThread->m_bCancel = TRUE;

	m_pSearchThread = NULL;

	CSearchOptionsView* pOptionsView = GetSearchOptionsView();
	pOptionsView->GetDlgItem(IDC_BUTTON_REPLACEALL)->EnableWindow(FALSE);

	pOptionsView->SetSearchMode(FALSE);

	CXTPReportView* pView = DYNAMIC_DOWNCAST(CXTPReportView, GetDescendantWindow(AFX_IDW_PANE_FIRST));
	ASSERT(pView);

	if (!pView)
		return;

	pView->GetReportCtrl().Populate();

	SetMessageText(_T("Canceled"));
}

void CMainFrame::DelayPopulate()
{
	if (m_nTimer == 0)
	{
		m_nTimer = SetTimer(TID_REFRESH, 100, NULL);
	}
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	CFrameWnd::OnTimer(nIDEvent);

	if ((nIDEvent == TID_REFRESH) && (m_nTimer != 0))
	{
		CXTPReportView* pView = DYNAMIC_DOWNCAST(CXTPReportView, GetDescendantWindow(AFX_IDW_PANE_FIRST));
		ASSERT(pView);
		
		if (!pView)
			return;
		
		pView->GetReportCtrl().Populate();

		KillTimer(TID_REFRESH);
		m_nTimer = 0; 
	}
}

void CMainFrame::OnFindAll()
{
	CSearchOptions* pOptions = GetSearchOptions();
	ASSERT(pOptions);

	CXTPReportView* pView = DYNAMIC_DOWNCAST(CXTPReportView, GetDescendantWindow(AFX_IDW_PANE_FIRST));
	ASSERT(pView);

	if (!pView)
		return;

	pView->GetReportCtrl().GetRecords()->RemoveAll();
	pView->GetReportCtrl().Populate();

	//////////////////////////////////////////////////////////////////////////

	m_pSearchThread = (CSearchThread*)AfxBeginThread(RUNTIME_CLASS(CSearchThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);	
	m_pSearchThread->m_pMainFrame = this;
	m_pSearchThread->m_pReportControl = &pView->GetReportCtrl();
	m_pSearchThread->ResumeThread();
	
	CSearchOptionsView* pOptionsView = GetSearchOptionsView();
	pOptionsView->SetSearchMode(TRUE);


	AddComboHistory(pOptionsView->m_cmbFind, pOptions->m_strFind, pOptions->m_lstFindHistory);
	AddComboHistory(pOptionsView->m_cmbReplace, pOptions->m_strReplace, pOptions->m_lstReplaceHistory);
	AddComboHistory(pOptionsView->m_cmbPath, pOptions->m_strPath, pOptions->m_lstPathHistory);
	AddComboHistory(pOptionsView->m_cmbFileTypes, pOptions->m_strFileTypes, pOptions->m_lstFileTypesHistory);

}

void CMainFrame::OnReplaceAll()
{
	USES_CONVERSION;

	CXTPReportView* pView = DYNAMIC_DOWNCAST(CXTPReportView, GetDescendantWindow(AFX_IDW_PANE_FIRST));
	ASSERT(pView);

	if (!pView)
		return;

	CXTPReportRecords* pRecords = pView->GetReportCtrl().GetRecords();
	if (!pRecords)
		return;

	int nFiles = 0;
	int nChanges = 0;

	int i;
	for (i = 0; i < pRecords->GetCount(); i++)
	{
		CString strPath = ((CGrepRecord*)pRecords->GetAt(i))->m_strPath;

		BOOL bChanged = FALSE;
		int nSamePathCount = 0;

		while (i + nSamePathCount < pRecords->GetCount() && ((CGrepRecord*)pRecords->GetAt(i + nSamePathCount))->m_strPath ==
			strPath)
		{
			CGrepRecord* pRecord = ((CGrepRecord*)pRecords->GetAt(i + nSamePathCount));

			nSamePathCount++;
			if (pRecord->IsChanged() && pRecord->IsChecked())
			{
				bChanged = TRUE;
				nChanges++;
			}
		}

		if (!bChanged)
		{
			i += nSamePathCount - 1;
			continue;
		}
		i += nSamePathCount - 1;
		nFiles++;
	}

	if (nFiles == 0)
	{
		AfxMessageBox(_T("There are no selected records"));
		return;
	}


	CString str;
	str.Format(_T("Are you sure you want make %i replacement(s) in %i file(s)?"), nChanges, nFiles);
	if (AfxMessageBox(str, MB_YESNO) != IDYES)
		return;


	for (i = 0; i < pRecords->GetCount(); i++)
	{
		CString strPath = ((CGrepRecord*)pRecords->GetAt(i))->m_strPath;

		int nSamePathCount = 0;
		BOOL bChanged = FALSE;

		while (i + nSamePathCount < pRecords->GetCount() && ((CGrepRecord*)pRecords->GetAt(i + nSamePathCount))->m_strPath ==
			strPath)
		{
			CGrepRecord* pRecord = ((CGrepRecord*)pRecords->GetAt(i + nSamePathCount));

			nSamePathCount++;
			if (pRecord->IsChanged() && pRecord->IsChecked())
			{
				bChanged = TRUE;
			}
		}

		CFile file;
		if (!bChanged || !file.Open(strPath, CFile::modeRead))
		{
			i += nSamePathCount - 1;
			continue;
		}

		DWORD dwCount = (DWORD)file.GetLength();
		char* lpszFileBuffer = new char[dwCount];
		file.Read(lpszFileBuffer, dwCount);
		file.Close();

		//CFile::Rename(pRecord->m_strPath, pRecord->m_strPath + _T(".bak"));
		if (!file.Open(strPath, CFile::modeWrite|CFile::modeCreate))
		{
			i += nSamePathCount - 1;

			delete[] lpszFileBuffer;
			continue;
		}

		long nTail = 0;

		int k = 0;
		for  (int j = 0; j < nSamePathCount; j++)
		{
			CGrepRecord* pRecord = ((CGrepRecord*)pRecords->GetAt(i + j - k ));

			if (pRecord->IsChecked())
			{
				file.Write(lpszFileBuffer + nTail, pRecord->m_nIndex - nTail);

				if (!pRecord->m_strReplace.IsEmpty())
				{
					file.Write(T2A((LPTSTR)(LPCTSTR)(pRecord->m_strReplace)), pRecord->m_strReplace.GetLength());
				}
				nTail = pRecord->m_nIndex + pRecord->m_nLength;

				pRecords->RemoveAt(i + j - k);
				k++;
			}

		}
		i += nSamePathCount - k - 1;

		file.Write(lpszFileBuffer + nTail, dwCount - nTail);
		file.Close();



		delete[] lpszFileBuffer;
	}

	pView->GetReportCtrl().Populate();
}


CSearchOptionsView* CMainFrame::GetSearchOptionsView()
{
	CXTPDockingPane* pPane = m_paneManager.FindPane(IDR_PANE_OPTIONS);
	if (!pPane)
		return 0;
	CWnd* pWnd = pPane->GetChild();
	if (!pWnd)
		return 0;

	return (CSearchOptionsView*)pWnd->GetDescendantWindow(AFX_IDW_PANE_FIRST);

}


void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{

// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);

// Toggle Docking Panes.
	m_paneManager.OnSetPreviewMode(bPreview);


	CFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainFrame::OnViewOptionspane() 
{
	m_paneManager.ShowPane(IDR_PANE_OPTIONS);
	
}
