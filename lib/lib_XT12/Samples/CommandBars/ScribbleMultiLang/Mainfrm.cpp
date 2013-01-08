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
#include "Scribble.h"

#include "MainFrm.h"

extern CScribbleApp theApp;

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
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)

	// menu and command bar customization.
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)

	ON_UPDATE_COMMAND_UI_RANGE(ID_POPUP_FILE, ID_POPUP_HELP, OnUpdatePopup)

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
	// TODO: add member initialization code here

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


	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	GetCommandBars()->EnableActions();

	SetCommandBarMenu();

	// Set Office 2003 Theme
	CXTPPaintManager::SetTheme(xtpThemeOffice2003);

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars2"));

	return 0;
}

BOOL CMainFrame::SetCommandBarMenu()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return FALSE;      // fail to create
	}

	// Load menu bar caption.
	CString strCapt;
	strCapt.LoadString(IDS_MENUBAR);

	// Add the menu bar
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(
		strCapt, IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return FALSE;      // fail to create
	}

	// Load command bar caption.
	strCapt.LoadString(IDS_STANDARD);

	// Create ToolBar
	CXTPToolBar* pToolBar = (CXTPToolBar*)
		pCommandBars->Add(strCapt, xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;      // fail to create
	}

	CMenu menu;
	menu.LoadMenu(IDR_SCRIBBTYPE);

	pCommandBars->GetActions()->CreateFromMenu(&menu);

	return TRUE;
}


void CMainFrame::ResetCommandBars()
{
	m_bInRecalcLayout = TRUE;

	CXTPCommandBars* pCommandBars = GetCommandBars();	

	CMenu menu;
	XTPResourceManager()->LoadMenu(&menu, IDR_SCRIBBTYPE);

	pCommandBars->GetActions()->CreateFromMenu(&menu);


	CString strTitle;
	XTPResourceManager()->LoadString(&strTitle, IDS_MENUBAR);
	pCommandBars->GetMenuBar()->SetTitle(strTitle);

	XTPResourceManager()->LoadString(&strTitle, IDS_STANDARD);
	pCommandBars->GetToolBar(IDR_MAINFRAME)->SetTitle(strTitle);


	m_bInRecalcLayout = FALSE;
	RecalcLayout();
	AfxGetApp()->OnIdle(0);
	UpdateWindow();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

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
		pCommands->AddCategories(IDR_SCRIBBTYPE);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_SCRIBBTYPE);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
}

void CMainFrame::OnClose()
{
	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars2"));

	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnUpdatePopup(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}
