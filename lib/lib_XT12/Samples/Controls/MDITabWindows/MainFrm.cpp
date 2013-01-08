// MainFrm.cpp : implementation of the CMainFrame class
//
// This file is a part of the XTREME TOOLKIT MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO 
// BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED 
// WRITTEN CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS 
// OUTLINED IN THE XTREME TOOLKIT LICENSE AGREEMENT.  CODEJOCK SOFTWARE 
// GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE 
// THIS SOFTWARE ON A SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MDITabWindows.h"

#include "MainFrm.h"

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
	ON_COMMAND(IDC_ACTIVATE, OnActivate)
	ON_COMMAND(IDC_CLOSEDOCUMENT, OnClosedocument)
	ON_COMMAND(IDC_HIDETABS, OnHidetabs)
	ON_COMMAND(IDC_ALIGNTABLEFT, OnAligntableft)
	ON_COMMAND(IDC_ALIGNTABTOP, OnAligntabtop)
	ON_COMMAND(IDC_ALIGNTABRIGHT, OnAligntabright)
	ON_COMMAND(IDC_ALIGNTABBOTTOM, OnAligntabbottom)
	ON_UPDATE_COMMAND_UI(IDC_ALIGNTABLEFT, OnUpdateAligntableft)
	ON_UPDATE_COMMAND_UI(IDC_ALIGNTABTOP, OnUpdateAligntabtop)
	ON_UPDATE_COMMAND_UI(IDC_ALIGNTABRIGHT, OnUpdateAligntabright)
	ON_UPDATE_COMMAND_UI(IDC_ALIGNTABBOTTOM, OnUpdateAligntabbottom)
	ON_COMMAND(ID_SHOW_MDITABS, OnShowMditabs)
	ON_UPDATE_COMMAND_UI(ID_SHOW_MDITABS, OnUpdateShowMditabs)
	ON_COMMAND(ID_VIEW_THEME_OFFICEXP, OnViewThemeOfficeXP)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME_OFFICEXP, OnUpdateViewThemeOfficeXP)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_CASCADE, OnUpdateWindowCascade)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_HORZ, OnUpdateWindowTileHorz)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_ARRANGE, OnUpdateWindowArrange)
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

static UINT toolbars[] =
{
	IDR_MAINFRAME,
	IDR_TAB_POPUP,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bMDIActive    = TRUE;
	m_bAlignment[0] = FALSE; // left
	m_bAlignment[1] = TRUE;  // top
	m_bAlignment[2] = FALSE; // right
	m_bAlignment[3] = FALSE; // bottom

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
	if (CMainFrameBase::OnCreate(lpCreateStruct) == -1)
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
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

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

	// Install the MDI tab window and set the popup menu id.
	m_wndMDITabWindow.Install(this, NULL, (m_iTheme == xtThemeOfficeXP));

	// Set the menu id for the tab control, make IDC_ACTIVATE the
	// default menu item.
	m_wndMDITabWindow.SetMenuID(IDR_TAB_POPUP, 0, IDC_ACTIVATE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMainFrameBase::PreCreateWindow(cs) )
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
	CMainFrameBase::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMainFrameBase::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::ToggleMDITabs()
{
	m_bMDIActive = !m_bMDIActive;

	if ( m_bMDIActive )
	{
		SetMDITabStyle();

		// make sure the MDI child is maximized.
		CFrameWnd* pChild = GetActiveFrame();
		if ( pChild && ::IsWindow( pChild->m_hWnd ) )
		{
			DWORD dwStyle = ::GetWindowLong( pChild->m_hWnd, GWL_STYLE );
			if ( ( dwStyle & WS_MAXIMIZE ) != WS_MAXIMIZE )
			{
				pChild->ShowWindow( SW_MAXIMIZE );
			}
		}
	}
	else
	{
		m_wndMDITabWindow.UnInstall( );
	}
}

void CMainFrame::HideMDITabs()
{
	// TODO: Add your command handler code here
	m_wndMDITabWindow.UnInstall();
	m_bMDIActive = FALSE;
}

void CMainFrame::SetMDITabStyle()
{
	DWORD dwStyle = TCS_HOTTRACK;
	
	// left align
	if (m_bAlignment[0]) {
		dwStyle |= TCS_VERTICAL;
	}
	
	// right align
	else if (m_bAlignment[2]) {
		dwStyle |= TCS_VERTICAL|TCS_RIGHT;
	}
	
	// bottom align
	else if (m_bAlignment[3]) {
		dwStyle |= TCS_BOTTOM;
	}
	
	// Update the tab control.
	m_wndMDITabWindow.UnInstall( );
	m_wndMDITabWindow.Install(this, dwStyle, FALSE);
	
	// TODO: Uncomment this line if you want to change the border size between
	// the client and tab control.
	// m_wndMDITabWindow.SetBorderGap(10);
}

void CMainFrame::OnShowMditabs() 
{
    ToggleMDITabs();
}

void CMainFrame::OnUpdateShowMditabs(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bMDIActive);	
}

void CMainFrame::OnActivate() 
{
	// TODO: Add your command handler code here
	CMDIChildWnd* pChildFrame = (CMDIChildWnd *)m_wndMDITabWindow.GetFrameWnd();
	ASSERT_VALID(pChildFrame);
	MDIActivate(pChildFrame);
}

void CMainFrame::OnClosedocument() 
{
	// TODO: Add your command handler code here
	CMDIChildWnd* pChildFrame = (CMDIChildWnd *)m_wndMDITabWindow.GetFrameWnd();
	ASSERT_VALID(pChildFrame);
	pChildFrame->SendMessage(WM_CLOSE);
}

void CMainFrame::OnHidetabs() 
{
    HideMDITabs();
}

void CMainFrame::SetAlignment(ALIGNMENT eAlign)
{
	if (!m_bAlignment[eAlign])
	{
		int i;
		for (i = 0; i < _countof(m_bAlignment); ++i)
			m_bAlignment[i] = FALSE;

		m_bAlignment[eAlign] = TRUE;
		m_wndMDITabWindow.UnInstall();
		SetMDITabStyle();
	}
}

void CMainFrame::OnAligntableft() 
{
	SetAlignment(left);
}

void CMainFrame::OnUpdateAligntableft(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_bAlignment[left]);
}

void CMainFrame::OnAligntabtop() 
{
	SetAlignment(top);
}

void CMainFrame::OnUpdateAligntabtop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_bAlignment[top]);
}

void CMainFrame::OnAligntabright() 
{
	SetAlignment(right);
}

void CMainFrame::OnUpdateAligntabright(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_bAlignment[right]);
}

void CMainFrame::OnAligntabbottom() 
{
	SetAlignment(bottom);
}

void CMainFrame::OnUpdateAligntabbottom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_bAlignment[bottom]);
}

void CMainFrame::SetTheme(int iTheme)
{
	m_iTheme = iTheme;
	XTThemeManager()->SetTheme((XTThemeStyle)m_iTheme);
	XTPPaintManager()->SetTheme((XTPPaintTheme)m_iTheme);
    
	if ( ::IsWindow( m_wndMDITabWindow.m_hWnd ) )
	{
		if (m_iTheme == xtThemeOfficeXP)
		{
			m_wndMDITabWindow.SetBorderGap( 1 );
		}
		else
		{
			m_wndMDITabWindow.SetBorderGap( 5 );
		}
	}
	
    CRect r;
    GetWindowRect(&r);

    r.InflateRect(0,0,1,0);
    SetWindowPos(NULL, 0,0,r.Width(), r.Height(),
        SWP_NOMOVE|SWP_FRAMECHANGED);
    
    r.InflateRect(0,0,-1,0);
    SetWindowPos(NULL, 0,0,r.Width(), r.Height(),
        SWP_NOMOVE|SWP_FRAMECHANGED);


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

void CMainFrame::OnUpdateWindowCascade(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateWindowTileHorz(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateWindowArrange(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

BEGIN_MESSAGE_MAP(CMDIWndTab, CXTMDIWndTab)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

void CMDIWndTab::OnRButtonDown(UINT /*nFlags*/, CPoint point) 
{
	// Get the tab index based upon the cursor position.
	m_iHitTest = TabFromPoint(point);
	if (m_iHitTest != -1)
	{
		if (m_popupMenuID != 0)
		{
			CPoint pt = point;
			ClientToScreen(&pt);

			CMenu popupMenu;
			VERIFY(popupMenu.LoadMenu(m_popupMenuID));

			CMenu* pPopup = popupMenu.GetSubMenu(m_nPos);
			ASSERT(pPopup != NULL);

			if (m_nDefCmd != 0) {
				::SetMenuDefaultItem(pPopup->m_hMenu, m_nDefCmd, FALSE);
			}

			CWnd* pWndPopupOwner = GetOwner();
			ASSERT_VALID(pWndPopupOwner);

			CXTPCommandBars::TrackPopupMenu(pPopup, TPM_RIGHTBUTTON,
				pt.x, pt.y, AfxGetMainWnd(), 0, 0, ((CXTPMDIFrameWnd*)AfxGetMainWnd())->GetCommandBars());
		}
	}
}

void CMainFrame::OnCustomize()
{
    // Get a pointer to the Command Bar object.
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
        pCommands->AddCategories(IDR_MDITABTYPE);

        // Use the command bar manager to initialize the 
        // customize dialog.
        pCommands->InsertAllCommandsCategory();
        pCommands->InsertBuiltInMenus(IDR_MDITABTYPE);
        pCommands->InsertNewMenuCategory();

        // Dispaly the dialog.
        dlg.DoModal();
    }
}

void CMainFrame::OnClose() 
{
    // Save the current state for toolbars and menus.
    SaveCommandBars(_T("CommandBars"));
    CMainFrameBase::OnClose();
}

