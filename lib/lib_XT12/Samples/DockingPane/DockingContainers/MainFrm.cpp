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
#include "DockingContainers.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class CComandBarsPaintManager : public CXTPOffice2003Theme
{
public:

	void FillCommandBarEntry(CDC* pDC, CXTPCommandBar* pBar)
	{
		if (DYNAMIC_DOWNCAST(CXTPToolBar, pBar) != 0 && pBar->GetCommandBars() == 0)
			pDC->FillSolidRect(CXTPClientRect(pBar), m_clrDockBar.clrLight);
		else
			CXTPOffice2003Theme::FillCommandBarEntry(pDC, pBar);
	}

	void RoundRect(CDC* pDC, CRect rc, COLORREF clr)
	{
		CXTPBrushDC brush(*pDC, clr);
		CXTPPenDC pen(*pDC, GetXtremeColor(XPCOLOR_MENUBAR_BORDER));
		pDC->RoundRect(rc.left, rc.top, rc.right, rc.bottom, 6, 6);

	}

	void DrawRectangle(CDC* pDC, CRect rc, BOOL bSelected, BOOL bPressed, BOOL bEnabled, BOOL bChecked, BOOL bPopuped, XTPBarType barType, XTPBarPosition barPosition)
	{
		if (bPopuped || !bEnabled || m_bLunaTheme)
		{
			CXTPOffice2003Theme::DrawRectangle(pDC, rc, bSelected, bPressed, bEnabled, bChecked, bPopuped, barType, barPosition);
			return;
		}
		if (bChecked && !bSelected && !bPressed) RoundRect(pDC, rc, GetXtremeColor(XPCOLOR_MENUBAR_FACE));
		else if (bChecked && bSelected && !bPressed) RoundRect(pDC, rc, m_clrDockBar.clrLight);
		else if (IsKeyboardSelected(bPressed) || (bSelected && bPressed))  RoundRect(pDC, rc, m_clrDockBar.clrLight);
		else if (bSelected || bPressed)  RoundRect(pDC, rc, m_clrDockBar.clrDark);
	}

};




/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_WM_CLOSE()

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

	XTPColorManager()->DisableLunaColors(TRUE);


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	XTPPaintManager()->SetCustomTheme(new CComandBarsPaintManager());
	XTPPaintManager()->m_bEnableAnimation = TRUE;

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




	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetCustomTheme(new CDockingPanePaintManager());

	// Create docking panes.
	CXTPDockingPane* pPaneExplorer = m_paneManager.CreatePane(
		IDR_PANE_EXPLORER, CRect(0, 0,250, 120), xtpPaneDockLeft);

	m_paneManager.CreatePane(
		IDR_PANE_ICONS, CRect(0, 0,200, 120), xtpPaneDockBottom, pPaneExplorer);

	CXTPDockingPane* pPaneTools = m_paneManager.CreatePane(
		IDR_PANE_TOOLS, CRect(0, 0,100, 200), xtpPaneDockRight);

	m_paneManager.CreatePane(
		IDR_PANE_COLORS, CRect(0, 0,100, 100), xtpPaneDockBottom, pPaneTools);


	m_paneManager.SetThemedFloatingFrames(TRUE);

		// Load the previous state for docking panes.
	CXTPDockingPaneLayout layoutNormal(&m_paneManager);
	if (layoutNormal.Load(_T("NormalLayout")))
	{
		m_paneManager.SetLayout(&layoutNormal);
	}

	return 0;
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


LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;

		if (!pPane->IsValid())
		{
			switch (pPane->GetID())
			{
				case IDR_PANE_EXPLORER:
					pPane->Attach(m_wndExplorerView.CreatePane(this));
					break;
				case IDR_PANE_ICONS:
					pPane->Attach(m_wndIconsView.CreatePane(this));
					break;
				case IDR_PANE_TOOLS:
					pPane->Attach(m_wndToolsView.CreatePane(this));
					break;
				case IDR_PANE_COLORS:
					pPane->Attach(m_wndColorsView.CreatePane(this));
					break;
			}
		}
		return 1;
	}
	return 0;
}

void CMainFrame::RefreshPanes()
{
	if (m_wndToolsView.GetSafeHwnd())
		m_wndToolsView.Refresh();

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

void CMainFrame::OnClose()
{
	CXTPDockingPaneLayout layoutNormal(&m_paneManager);
	m_paneManager.GetLayout(&layoutNormal);
	layoutNormal.Save(_T("NormalLayout"));


	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars"));
	CFrameWnd::OnClose();
}



void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{

// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);


// Toggle Docking Panes.
	m_paneManager.OnSetPreviewMode(bPreview);


	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}
