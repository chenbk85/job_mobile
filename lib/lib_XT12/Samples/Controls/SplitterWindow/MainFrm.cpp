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
#include "SplitterWindow.h"
#include "MainFrm.h"
#include "View1.h"
#include "View2.h"
#include "View3.h"
#include "View4.h"
#include "View5.h"

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
	ON_COMMAND(ID_VIEW_THEME_OFFICEXP, OnViewThemeOfficeXP)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME_OFFICEXP, OnUpdateViewThemeOfficeXP)
	ON_COMMAND(ID_SPLIT_SWAPVIEWS, OnSwapViews)
	ON_COMMAND(ID_SPLIT_REPLACEVIEW, OnReplaceView)
	ON_UPDATE_COMMAND_UI(ID_SPLIT_REPLACEVIEW, OnUpdateReplaceView)
	ON_UPDATE_COMMAND_UI(ID_SPLIT_SWAPVIEWS, OnUpdateSwapViews)
	ON_COMMAND(ID_SPLIT_HIDEFIRSTROW, OnHideFirstRow)
	ON_UPDATE_COMMAND_UI(ID_SPLIT_HIDEFIRSTROW, OnUpdateHideFirstRow)
	ON_COMMAND(ID_SPLIT_HIDEFIRSTCOL, OnHideFirstCol)
	ON_UPDATE_COMMAND_UI(ID_SPLIT_HIDEFIRSTCOL, OnUpdateHideFirstCol)
	ON_COMMAND(ID_SPLIT_FULLDRAG, OnSplitNofulldrag)
	ON_UPDATE_COMMAND_UI(ID_SPLIT_FULLDRAG, OnUpdateSplitNofulldrag)
	ON_COMMAND(ID_SPLIT_DOTTRACKER, OnSplitDottracker)
	ON_UPDATE_COMMAND_UI(ID_SPLIT_DOTTRACKER, OnUpdateSplitDottracker)
	ON_COMMAND(ID_SPLIT_NOSIZE, OnSplitNosize)
	ON_UPDATE_COMMAND_UI(ID_SPLIT_NOSIZE, OnUpdateSplitNosize)
	ON_COMMAND(ID_SPLIT_FLATSPLITTER, OnSplitFlatsplitter)
	ON_UPDATE_COMMAND_UI(ID_SPLIT_FLATSPLITTER, OnUpdateSplitFlatsplitter)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)

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
: m_pView1(0)
, m_pView2(0)
, m_pView3(0)
, m_pView4(0)
{
	m_bRowHidden = FALSE;
	m_bColHidden = FALSE;
	m_bSwapped   = FALSE;
	m_bReplaced  = FALSE;
	m_bFullDrag  = TRUE;
	m_bDotTrack  = FALSE;
	m_bNoSizing  = FALSE;
	m_bFlatSplit = TRUE;

	// initialize themes.
	m_iTheme = m_regMgr.GetProfileInt(
		_T("Settings"), _T("Theme"), xtThemeOfficeXP);
}

CMainFrame::~CMainFrame()
{
	m_regMgr.WriteProfileInt(
		_T("Settings"), _T("Theme"), m_iTheme);
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
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);

	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));
	SetTheme(m_iTheme);

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

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	// Create the splitter window with two columns
	if (!m_wndSplitter.CreateStatic(this, 2, 2))
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(0,0, RUNTIME_CLASS(CView1),
		CSize(0, 0), pContext))
	{
		TRACE0("Failed to create CView1\n");
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(0,1, RUNTIME_CLASS(CView2),
		CSize(0, 0), pContext))
	{
		TRACE0("Failed to create CView2\n");
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(1,0, RUNTIME_CLASS(CView3),
		CSize(0, 0), pContext))
	{
		TRACE0("Failed to create CView3\n");
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(1,1, RUNTIME_CLASS(CView4),
		CSize(0, 0), pContext))
	{
		TRACE0("Failed to create CView4\n");
		return FALSE;
	}

	CRect r;
	GetClientRect(&r);

	m_wndSplitter.SetRowInfo( 0, r.Height()/2, 0 );
	m_wndSplitter.SetColumnInfo( 0, r.Width()/2, 0 );

	return TRUE;
}

void CMainFrame::OnSwapViews()
{
	m_wndSplitter.SwitchView(0,0, (CView*)m_wndSplitter.GetPane(0,1));
	m_bSwapped = !m_bSwapped;
}

void CMainFrame::OnUpdateSwapViews(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bSwapped);
	pCmdUI->Enable(!m_bRowHidden && !m_bColHidden);
}

void CMainFrame::OnReplaceView()
{
	if (m_wndSplitter.GetPane(1,0)->IsKindOf(RUNTIME_CLASS(CView3))) {
		m_wndSplitter.ReplaceView(1,0, RUNTIME_CLASS(CView5));
	}
	else {
		m_wndSplitter.ReplaceView(1,0, RUNTIME_CLASS(CView3));
	}
	m_bReplaced = !m_bReplaced;
}

void CMainFrame::OnUpdateReplaceView(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bReplaced);
	pCmdUI->Enable(!m_bRowHidden && !m_bColHidden);
}

void CMainFrame::OnHideFirstRow()
{
	m_bRowHidden = !m_bRowHidden;

	if (m_bRowHidden) {
		m_wndSplitter.HideRow(1);
	}
	else {
		m_wndSplitter.ShowRow();
	}
}

void CMainFrame::OnUpdateHideFirstRow(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bRowHidden);
}

void CMainFrame::OnHideFirstCol()
{
	m_bColHidden = !m_bColHidden;

	if (m_bColHidden) {
		m_wndSplitter.HideColumn(1);
	}
	else {
		m_wndSplitter.ShowColumn();
	}
}

void CMainFrame::OnUpdateHideFirstCol(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bColHidden);
}

void CMainFrame::OnSplitNofulldrag()
{
	m_bFullDrag = !m_bFullDrag;

	DWORD dw = m_wndSplitter.GetSplitterStyle();

	if (m_bFullDrag)
		dw &= ~XT_SPLIT_NOFULLDRAG;
	else
		dw |= XT_SPLIT_NOFULLDRAG;

	m_wndSplitter.SetSplitterStyle(dw);
}

void CMainFrame::OnUpdateSplitNofulldrag(CCmdUI* pCmdUI)
{
	BOOL bEnable = FALSE;

	// Get system settings for full drag.
	::SystemParametersInfo(SPI_GETDRAGFULLWINDOWS,
		0, &bEnable, 0);

	pCmdUI->SetCheck(m_bFullDrag);
	pCmdUI->Enable(bEnable && !m_bDotTrack);
}

void CMainFrame::OnSplitDottracker()
{
	m_bDotTrack = !m_bDotTrack;

	DWORD dw = m_wndSplitter.GetSplitterStyle();

	if (m_bDotTrack)
		dw |= XT_SPLIT_DOTTRACKER;
	else
		dw &= ~XT_SPLIT_DOTTRACKER;

	m_wndSplitter.SetSplitterStyle(dw);
}

void CMainFrame::OnUpdateSplitDottracker(CCmdUI* pCmdUI)
{
	BOOL bEnable = FALSE;

	// Get system settings for full drag.
	::SystemParametersInfo(SPI_GETDRAGFULLWINDOWS,
		0, &bEnable, 0);

	pCmdUI->SetCheck(m_bDotTrack);

	if (bEnable)
		pCmdUI->Enable(!m_bFullDrag);
}

void CMainFrame::OnSplitNosize()
{
	m_bNoSizing = !m_bNoSizing;

	DWORD dw = m_wndSplitter.GetSplitterStyle();

	if (m_bNoSizing)
		dw |= XT_SPLIT_NOSIZE;
	else
		dw &= ~XT_SPLIT_NOSIZE;

	m_wndSplitter.SetSplitterStyle(dw);
}

void CMainFrame::OnUpdateSplitNosize(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNoSizing);
}

void CMainFrame::OnSplitFlatsplitter()
{
	m_bFlatSplit = !m_bFlatSplit;
	m_wndSplitter.EnableFlatLook(m_bFlatSplit);
}

void CMainFrame::OnUpdateSplitFlatsplitter(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bFlatSplit);
}

void CMainFrame::SetTheme(int iTheme)
{
	m_iTheme = iTheme;
	XTThemeManager()->SetTheme((XTThemeStyle)m_iTheme);
	XTPPaintManager()->SetTheme((XTPPaintTheme)m_iTheme);

	RedrawWindow( NULL, NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN );

	RecalcLayout();
}

void CMainFrame::OnViewThemeOfficeXP()
{
	SetTheme((m_iTheme == xtThemeOfficeXP)? xtThemeDefault: xtThemeOfficeXP);
}

void CMainFrame::OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_iTheme == xtThemeOfficeXP);
}

void CMainFrame::OnClose()
{
	// Save the current state for command bars.
	SaveCommandBars(_T("CommandBars"));
	CFrameWnd::OnClose();
}

void CMainFrame::OnCustomize()
{
	// get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return;

	// instantiate the customize dialog
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
