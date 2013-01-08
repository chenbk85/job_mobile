// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MDITextEditor.h"

#include "MainFrm.h"
#include "MDITextEditorDoc.h"
#include "MDITextEditorView.h"

#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_MESSAGE(WM_COPYDATA, OnAppInstance)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateKeyIndicator)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ROWCOL, OnUpdateRowColIndicator)
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_ROWCOL,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_OVR,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// set the current user locale
	// to allow some text functions (like isleadbyte) works correctly
	//
	_tsetlocale(LC_ALL, _T(""));	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	XTPPaintManager()->SetTheme(xtpThemeWhidbey);

	CXTPCommandBars* pCommandBars = GetCommandBars();

	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pMenuBar->SetFlags(xtpFlagAddMDISysPopup);

	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));


	VERIFY(m_MTIClientWnd.Attach(this));
	m_MTIClientWnd.EnableToolTips();
	m_MTIClientWnd.GetPaintManager()->m_bShowIcons = FALSE;
	m_MTIClientWnd.SetNewTabPosition(xtpWorkspaceNewTabLeftMost);
	m_MTIClientWnd.SetFlags(xtpWorkspaceHideArrowsAlways | xtpWorkspaceHideClose | xtpWorkspaceShowActiveFiles);


	// Initialize row, col indicator.
	m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(
		ID_INDICATOR_ROWCOL), ID_INDICATOR_ROWCOL, SBPS_NORMAL, 75);

	SetRowCol(0,0);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;


    // Set the class name to be the app's single instance class name 
	cs.lpszClass = CLASSNAME_APPINSTANCE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

LRESULT CMainFrame::OnAppInstance(WPARAM wParam, LPARAM lParam)
{
	COPYDATASTRUCT* pCopyData = (COPYDATASTRUCT*)lParam;
	if (pCopyData->dwData == cdwData_FileName)
	{
		theApp.OpenDocumentFile((LPCTSTR)pCopyData->lpData);

		return TRUE;
	}

	return FALSE;
}

void CMainFrame::OnUpdateKeyIndicator(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(theApp.m_bInsertKey);
}

void CMainFrame::OnUpdateRowColIndicator(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		// Ctrl + Tab key pressed.
		if ((::GetKeyState(VK_CONTROL) & 0x8000) && (pMsg->wParam == VK_TAB))
		{
			if (theApp.m_pDocManager->GetOpenDocumentCount() < 2)
			{
				MessageBeep((UINT)-1);				
			}
		}
	}
	
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::SetRowCol(int nRow, int nCol)
{
	CString csRowCol;
	csRowCol.Format(_T("Ln %d, Col %d"), nRow, nCol);

	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(
		ID_INDICATOR_ROWCOL), csRowCol);
}

void CMainFrame::UpdateMenuPopups(int nIndex)
{
	CMenu *pMainMenu = GetMenu();
	ASSERT_VALID(pMainMenu);

	CMenu *pSubMenu = pMainMenu->GetSubMenu(nIndex);
	OnInitMenuPopup(pSubMenu, 0, FALSE);
	
	CMenu *pAdvSubMenu = pSubMenu->GetSubMenu(16);
	OnInitMenuPopup(pAdvSubMenu, 0, FALSE);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CMDIFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	if (nState != WA_INACTIVE)
	{
		POSITION pos = theApp.m_pDocTemplate->GetFirstDocPosition();
		while(pos)
		{
			CMDITextEditorDoc* pDoc = DYNAMIC_DOWNCAST(CMDITextEditorDoc,
				theApp.m_pDocTemplate->GetNextDoc(pos));

			if (pDoc)
				pDoc->CheckFileModified(pDoc->GetPathName());
		}
	}
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
		pCommands->AddCategories(IDR_MDITEXTYPE);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_MDITEXTYPE);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
}

void CMainFrame::OnClose() 
{
	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars"));
	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState) 
{
// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);

// Toggle Tab Client
	m_MTIClientWnd.ShowWorkspace(!bPreview);

	
	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

