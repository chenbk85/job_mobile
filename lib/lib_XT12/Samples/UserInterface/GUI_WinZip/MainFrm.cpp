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
#include "GUI_WinZip.h"

#include "MainFrm.h"

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
	ON_COMMAND(ID_THEME_NATIVEWINXP, OnThemeNativewinxp)
	ON_COMMAND(ID_THEME_OFFICE2003, OnThemeOffice2003)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP

	ON_UPDATE_COMMAND_UI(ID_THEME_NATIVEWINXP, OnUpdateThemeNativewinxp)
	ON_UPDATE_COMMAND_UI(ID_THEME_OFFICE2003, OnUpdateThemeOffice2003)

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)

	ON_COMMAND(ID_FILE_NEW_ARCHIVE, OnEmptyCommand)
	ON_COMMAND(ID_FILE_OPEN_ARCHIVE, OnEmptyCommand)
	ON_COMMAND(ID_FILE_FAVORITES, OnEmptyCommand)
	ON_COMMAND(ID_FILE_CLOSE_ARCHIVE, OnEmptyCommand)
	ON_COMMAND(ID_FILE_WIZARD, OnEmptyCommand)
	ON_COMMAND(ID_FILE_PROPERTIES, OnEmptyCommand)
	ON_COMMAND_RANGE(ID_ACTIONS_ADD, ID_ACTIONS_UUENCODE, OnEmptyCommandRange)
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
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
	{
		return -1;      // fail to create
	}

	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);

	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	XTPImageManager()->SetIcons(IDR_MAINFRAME, IDR_ICONS_TOOLBAR_32);

	pCommandBars->SetTheme(xtpThemeNativeWinXP);


	pCommandBars->GetCommandBarsOptions()->szLargeIcons = CSize(42, 35);
	pCommandBars->GetCommandBarsOptions()->bLargeIcons = TRUE;

	pCommandBar->ShowTextBelowIcons();


	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars2"));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
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
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnEmptyCommand()
{

}
void CMainFrame::OnEmptyCommandRange(UINT)
{

}

void CMainFrame::OnThemeNativewinxp()
{
	GetCommandBars()->SetTheme(xtpThemeNativeWinXP);
}

void CMainFrame::OnUpdateThemeNativewinxp(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetCommandBars()->GetPaintManager()->GetCurrentTheme() == xtpThemeNativeWinXP);
}

void CMainFrame::OnThemeOffice2003()
{
	GetCommandBars()->SetTheme(xtpThemeOffice2003);
}

void CMainFrame::OnUpdateThemeOffice2003(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetCommandBars()->GetPaintManager()->GetCurrentTheme() == xtpThemeOffice2003);
}

void CMainFrame::OnClose()
{
	// Save the current state for command bars.
	SaveCommandBars(_T("CommandBars2"));
	// TODO: Add your message handler code here and/or call default

	CFrameWnd::OnClose();
}

void CMainFrame::OnCustomize()
{
	// get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return;

	// instanciate the customize dialog
	CXTPCustomizeSheet dlg(pCommandBars);

	// add the options page to the customize dialog.
	CXTPCustomizeOptionsPage pageOptions(&dlg);
	dlg.AddPage(&pageOptions);

	// add the commands page to the customize dialog.
	CXTPCustomizeCommandsPage* pPageCommands = dlg.GetCommandsPage();
	pPageCommands->AddCategories(IDR_MAINFRAME);

	// initialize the commands page page.
	pPageCommands->InsertAllCommandsCategory();
	pPageCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pPageCommands->InsertNewMenuCategory();

	// display the customize dialog.
	dlg.DoModal();
}
