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
#include "ActivePaneView.h"

#include "MainFrm.h"
#include "ViewOne.h"
#include "ViewTwo.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static UINT uHideCmds[] =
{
	ID_FILE_PRINT,
	ID_FILE_PRINT_PREVIEW,
};
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
: m_pViewOne(NULL)
, m_pViewTwo(NULL)
, m_pActivePane(NULL)
{
	// TODO: add member initialization code here

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

	// Set Office 2003 Theme
	CXTPPaintManager::SetTheme(xtpThemeOfficeXP);

	// Hide array of commands
	pCommandBars->HideCommands(uHideCmds, _countof(uHideCmds));

	// Set "Always Show Full Menus" option to the FALSE
	pCommandBars->GetCommandBarsOptions()->bAlwaysShowFullMenus = FALSE;

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));


	// Initialize the docking pane manager and set the
	// initial them for the docking panes.  Do this only after all
	// control bars objects have been created and docked.
	m_paneManager.InstallDockingPanes(this);
	// Set Office 2003 Theme
	m_paneManager.SetTheme(xtpPaneThemeOffice);

	// Create docking panes.
	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(
		IDR_PANE_OPTIONS, CRect(0, 0,200, 120), xtpPaneDockLeft);
	CXTPDockingPane* pwndPane2 = m_paneManager.CreatePane(
		IDR_PANE_PROPERTIES, CRect(0, 0,200, 120), xtpPaneDockBottom, pwndPane1);
	m_paneManager.CreatePane(
		IDR_PANE_DIALOG, CRect(0, 0,200, 120), xtpPaneDockBottom, pwndPane2);

	m_paneManager.EnableKeyboardNavigate();

	// Set the icons for the docking pane tabs.
	int nIDIcons[] = {IDR_PANE_OPTIONS, IDR_PANE_PROPERTIES, IDR_PANE_DIALOG};
		m_paneManager.SetIcons(IDB_BITMAP_ICONS, nIDIcons,
		_countof(nIDIcons), RGB(0, 255, 0));

	// Load the previous state for docking panes.
	CXTPDockingPaneLayout layoutNormal(&m_paneManager);
	if (layoutNormal.Load(_T("NormalLayout")))
	{
		m_paneManager.SetLayout(&layoutNormal);
	}

	return 0;
}

void CMainFrame::OnClose()
{

	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars"));


	// Save the current state for docking panes.
	CXTPDockingPaneLayout layoutNormal(&m_paneManager);
	m_paneManager.GetLayout(&layoutNormal);
	layoutNormal.Save(_T("NormalLayout"));

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
			case IDR_PANE_DIALOG:
				if (!::IsWindow(m_dlgPane.m_hWnd))
				{
					m_dlgPane.Create(IDD_PANEDIALOG, this);
				}
				pPane->Attach(&m_dlgPane);
				break;

			case IDR_PANE_OPTIONS:
				{
					if (!m_pViewOne)
					{
						m_pViewOne = DYNAMIC_DOWNCAST(CViewOne,
							pPane->AttachView(this, RUNTIME_CLASS(CViewOne)));
					}
					else
					{
						pPane->Attach(m_pViewOne->GetParent());
					}
					break;
				}
			case IDR_PANE_PROPERTIES:
				{
					if (!m_pViewTwo)
					{
						m_pViewTwo = DYNAMIC_DOWNCAST(CViewTwo,
							pPane->AttachView(this, RUNTIME_CLASS(CViewTwo)));
					} 
					else
					{
						pPane->Attach(m_pViewTwo->GetParent());
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

// The following code will ensure that messages are correctly routed to
// the docking pane child views.

CXTPDockingPane* CMainFrame::GetActivePane()
{
	return m_paneManager.GetActivePane();
}

CWnd* CMainFrame::GetActivePaneView()
{
	CXTPDockingPane* pActivePane = GetActivePane();
	if (pActivePane)
		return pActivePane->GetChild();
	return NULL;
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// Use GetActivePane() to search the pane manager's list for the pane
	// with a view that has input focus.  If one is found, give the view an
	// opportunity to handle the OnCmdMsg first before we pass it to the base
	// class.

	CWnd* pView = GetActivePaneView();
	if (pView != NULL && pView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE; // handled.
	}

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);

// Toggle Docking Panes.
	m_paneManager.OnSetPreviewMode(bPreview);


	CFrameWnd::OnSetPreviewMode(bPreview, pState);
}
