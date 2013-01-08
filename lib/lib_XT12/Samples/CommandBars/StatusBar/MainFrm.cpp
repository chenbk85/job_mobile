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
#include "StatusBar.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define INT2THEME(i) (XTPPaintTheme)(i)

AFX_STATIC XTPPaintTheme ThemeFromCommand(UINT nID)
{
	switch (nID)
	{
	case ID_VIEW_THEME_OFFICE2000: return xtpThemeOffice2000;
	case ID_VIEW_THEME_OFFICEXP:   return xtpThemeOfficeXP;
	case ID_VIEW_THEME_OFFICE2003: return xtpThemeOffice2003;
	case ID_VIEW_THEME_OFFICE2007: return xtpThemeRibbon;
	}
	return xtpThemeOffice2000;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_STATUSBAR_SHOWBUTTONS, OnStatusBarShowButtons)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_SHOWBUTTONS, OnUpdateStatusBarShowButtons)
	ON_COMMAND(ID_STATUSBAR_SHOWAVIANIMATION, OnStatusBarShowAviAnimation)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_SHOWAVIANIMATION, OnUpdateStatusBarShowAviAnimation)
	ON_COMMAND(ID_STATUSBAR_SHOWPROGRESSBAR, OnStatusBarShowProgressBar)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_SHOWPROGRESSBAR, OnUpdateStatusBarShowProgressBar)
	ON_COMMAND(ID_STATUSBAR_SHOWEDITCONTROL, OnStatusBarShowEditControl)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_SHOWEDITCONTROL, OnUpdateStatusBarShowEditControl)
	ON_COMMAND(ID_STATUSBAR_SHOWCOMPANYLOGO, OnStatusBarShowCompanyLogo)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_SHOWCOMPANYLOGO, OnUpdateStatusBarShowCompanyLogo)
	ON_COMMAND(ID_STATUSBAR_PLAYANIMATION, OnStatusBarPlayAnimation)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_PLAYANIMATION, OnUpdateStatusBarPlayAnimation)
	ON_COMMAND(ID_STATUSBAR_TESTPROGRESS, OnStatusBarTestProgress)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_TESTPROGRESS, OnUpdateStatusBarTestProgress)
	//}}AFX_MSG_MAP

	ON_XTP_CREATECONTROL()
	ON_XTP_EXECUTE(ID_VIEW_OFFICE_THEME, OnOfficeThemeChanged)

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)

	ON_COMMAND_RANGE(ID_VIEW_THEME_OFFICE2000, ID_VIEW_THEME_OFFICE2007, OnViewTheme)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_THEME_OFFICE2000, ID_VIEW_THEME_OFFICE2007, OnUpdateViewTheme)

	ON_COMMAND_RANGE(ID_INDICATOR_PRINT, ID_INDICATOR_DRAFT, OnIndicatorButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_INDICATOR_PRINT, ID_INDICATOR_DRAFT, OnUpdateIndicatorButton)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
: m_bPlayAnimation(FALSE)
{
	m_eOfficeTheme = INT2THEME(AfxGetApp()->GetProfileInt(
		_T("Settings"), _T("OfficeTheme"), xtpThemeOffice2007));

	m_nPaneID = 0;
}

CMainFrame::~CMainFrame()
{
	AfxGetApp()->WriteProfileInt(
		_T("Settings"), _T("OfficeTheme"), m_eOfficeTheme);
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
	
	pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDR_TOOLBAR_ALPHA);
	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	m_wndStatusBar.GetPane(0)->SetBeginGroup(FALSE);
	AddLogo();

	m_wndStatusBar.SetRibbonDividerIndex(m_wndStatusBar.GetPaneCount() - 1);
	AddEdit();
	AddProgress();
	AddAnimation();

	AddSwitchButtons();
	AddZoomButton();
	AddZoomSlider();

	m_wndStatusBar.EnableCustomization();

	
	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));

	SetOfficeTheme(xtpThemeRibbon);


	return 0;
}

int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->nID == ID_VIEW_OFFICE_THEME)
	{
		CXTPControlComboBox* pComboTheme = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
		if (pComboTheme != NULL)
		{
			pComboTheme->SetWidth(200);
			pComboTheme->SetCaption(_T("Theme:"));
			pComboTheme->SetStyle(xtpComboLabel);
			pComboTheme->SetFlags(xtpFlagManualUpdate);
			
			pComboTheme->SetItemData(pComboTheme->AddString(_T("Office 2007")), xtpThemeRibbon);
			pComboTheme->SetItemData(pComboTheme->AddString(_T("Office 2003")), xtpThemeOffice2003);
			pComboTheme->SetItemData(pComboTheme->AddString(_T("Office XP")),   xtpThemeOfficeXP);
			pComboTheme->SetItemData(pComboTheme->AddString(_T("Office 2000")), xtpThemeOffice2000);
			
			lpCreateControl->pControl = pComboTheme;
			UpdateThemeCombo(xtpThemeRibbon, pComboTheme);
			
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL CMainFrame::UpdateThemeCombo(XTPPaintTheme eOfficeTheme, CXTPControlComboBox* pComboTheme /*=NULL*/)
{
	if (pComboTheme == NULL)
	{
		CXTPCommandBars* pCommandBars = GetCommandBars();
		if (pCommandBars)
		{
			pComboTheme = (CXTPControlComboBox*)pCommandBars->FindControl(
				xtpControlComboBox, ID_VIEW_OFFICE_THEME, TRUE, FALSE);
		}
		
		if (pComboTheme == NULL)
			return FALSE;
	}
	
	switch (eOfficeTheme)
	{
	case xtpThemeOffice2000: pComboTheme->SetCurSel(3); break;
	case xtpThemeOfficeXP:   pComboTheme->SetCurSel(2); break;
	case xtpThemeOffice2003: pComboTheme->SetCurSel(1); break;
	case xtpThemeRibbon:     pComboTheme->SetCurSel(0); break;
	}

	return TRUE;
}

void CMainFrame::OnOfficeThemeChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;
	
	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	ASSERT(pControl->GetType() == xtpControlComboBox);
	if (pControl->GetType() != xtpControlComboBox)
	{
		ASSERT(FALSE);
		return;
	}

	int nCurSel = pControl->GetCurSel();
	if (nCurSel < 0 || nCurSel >= pControl->GetCount())
	{
		ASSERT(FALSE);
		return;
	}

	SetOfficeTheme(INT2THEME(pControl->GetItemData(nCurSel)));
	
	*pResult = 1;
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

void CMainFrame::AddAnimation()
{
	if (!m_wndAnimCtrl.Create(WS_CHILD|WS_VISIBLE|ACS_CENTER,
		CRect(0,0,0,0), &m_wndStatusBar, 0))
	{
		TRACE0("Failed to create avi control.\n");
		return;
	}

	m_wndAnimCtrl.Open(IDR_HEARTBEAT);

	// add the indicator to the status bar.
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_ANIM);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_ANIM);
	ASSERT (nIndex != -1);

	m_wndStatusBar.SetPaneWidth(nIndex, 14);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_POPOUT);
	m_wndStatusBar.AddControl(&m_wndAnimCtrl, ID_INDICATOR_ANIM, FALSE);

	pPane->SetCustomizationVisible(FALSE);
}

void CMainFrame::AddZoomButton()
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_ZOOM);
	pPane->SetText(_T("100%"));
	pPane->SetWidth(pPane->GetBestFit());
	pPane->SetButton();
	pPane->SetTextAlignment(DT_CENTER);
	pPane->SetTooltip(_T("Zoom level. Click to open the Zoom dialog box."));
	pPane->SetBeginGroup(FALSE);

	pPane->SetCaption(_T("&Zoom"));

}

void CMainFrame::AddZoomSlider()
{
	CXTPStatusBarSliderPane* pZoomPane = (CXTPStatusBarSliderPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSliderPane(), ID_INDICATOR_ZOOMSLIDER);
	pZoomPane->SetWidth(130);
	
	pZoomPane->SetPos(100);
	pZoomPane->SetRange(0, 200);
	pZoomPane->SetStyle(SBPS_NOBORDERS);

	pZoomPane->SetBeginGroup(FALSE);

	pZoomPane->SetCaption(_T("&Zoom Slider"));
	pZoomPane->SetTooltip(_T("Zoom"));

}

void CMainFrame::AddSwitchButtons()
{
	static UINT switches[] =
	{
		ID_INDICATOR_PRINT,
		ID_INDICATOR_FULLSCREEN,
		ID_INDICATOR_WEB,
		ID_INDICATOR_OUTLINE,
		ID_INDICATOR_DRAFT,
	};

	CXTPStatusBarSwitchPane* pSwitchPane = (CXTPStatusBarSwitchPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSwitchPane(), ID_INDICATOR_VIEW);
	pSwitchPane->SetSwitches(switches, sizeof(switches)/sizeof(UINT));
	pSwitchPane->SetChecked(ID_INDICATOR_PRINT);

	for (int i = 0; i < sizeof(switches)/sizeof(UINT); i++)
	{
		m_wndStatusBar.GetImageManager()->SetIcon(switches[i], switches[i]);
	}

	pSwitchPane->BestFit();

	m_wndStatusBar.UpdateAllPanes(TRUE, FALSE);

	m_strMessage.LoadString(ID_INDICATOR_PRINT);

}

void CMainFrame::AddEdit()
{
	// Create the edit control and add it to the status bar
	if (!m_wndEditCtrl.CreateEx(WS_EX_STATICEDGE, _T("edit"), _T("Hello World"),
		WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), &m_wndStatusBar, 0))
	{
		TRACE0("Failed to create edit control.\n");
		return;
	}

	m_wndEditCtrl.SetFont(m_wndStatusBar.GetFont());

	// add the indicator to the status bar.
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_EDIT);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_EDIT);
	ASSERT (nIndex != -1);

	m_wndStatusBar.SetPaneWidth(nIndex, 75);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_NOBORDERS);
	m_wndStatusBar.AddControl(&m_wndEditCtrl, ID_INDICATOR_EDIT, FALSE);

	pPane->SetCustomizationVisible(FALSE);
}

void CMainFrame::AddLogo()
{
#if 0 // Obsolete 

	if (!m_wndLogoPane.Create(_T("Codejock Software"), &m_wndStatusBar))
	{
		TRACE0("Failed to create logo control.\n");
		return;
	}

	int nWidth = m_wndLogoPane.GetTextSize().cx;

	// add the indicator to the status bar.
	m_wndStatusBar.AddIndicator(ID_INDICATOR_LOGO, 0);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_LOGO);
	ASSERT (nIndex != -1);

	m_wndStatusBar.SetPaneWidth(nIndex, nWidth);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_POPOUT);
	m_wndStatusBar.AddControl(&m_wndLogoPane, ID_INDICATOR_LOGO, FALSE);
#else
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_LOGO, 0);
	
#ifndef _XTP_INCLUDE_MARKUP
	pPane->SetText(_T("Codejock Software"));
	pPane->SetTextColor(0x915f36);
	CXTPPaintManager::CNonClientMetrics ncm;
	ncm.lfMenuFont.lfWeight = FW_BOLD;
	pPane->SetTextFont(&ncm.lfMenuFont);
#else
	m_wndStatusBar.EnableMarkup(TRUE);
	pPane->SetText(_T("<TextBlock VerticalAlignment='Center'><Bold><Run Foreground='#365f91'>Codejock</Run> <Run Foreground='Black'>Software</Run></Bold></TextBlock>"));
#endif

	pPane->SetCaption(_T("Application Logo"));

	pPane->SetStyle(pPane->GetStyle() | SBPS_POPOUT);

#endif
}

void CMainFrame::AddProgress()
{
	// Create the edit control and add it to the status bar
	if (!m_wndProgCtrl.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,
		CRect(0,0,0,0), &m_wndStatusBar, 0))
	{
		TRACE0("Failed to create edit control.\n");
		return;
	}

	// add the indicator to the status bar.
	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_PROG);

	// Initialize the pane info and add the control.
	int nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_PROG);
	ASSERT (nIndex != -1);

	pPane->SetCaption(pPane->GetText());
	pPane->SetText(_T(""));

	m_wndStatusBar.SetPaneWidth(nIndex, 150);
	m_wndStatusBar.SetPaneStyle(nIndex, m_wndStatusBar.GetPaneStyle(nIndex) | SBPS_NOBORDERS);
	m_wndStatusBar.AddControl(&m_wndProgCtrl, ID_INDICATOR_PROG, FALSE);

	// initialize progress control.
	m_wndProgCtrl.SetRange (0, 5000);
	m_wndProgCtrl.SetPos (0);
	m_wndProgCtrl.SetStep (1);

	pPane->SetCustomizationVisible(FALSE);
}


void CMainFrame::TestProgress()
{
	m_wndProgCtrl.SetPos (0);

	int i;
	for (i = 0; i <= 5000; i++)
	{
		m_wndProgCtrl.StepIt();
	}
}

void CMainFrame::SetOfficeTheme(XTPPaintTheme eOfficeTheme)
{
	m_eOfficeTheme = eOfficeTheme;

	XTPPaintManager()->SetTheme(eOfficeTheme);

	EnableOffice2007Frame((eOfficeTheme == xtpThemeRibbon)?
		GetCommandBars(): NULL);
	
	GetCommandBars()->RedrawCommandBars();

	RedrawWindow( NULL, NULL,
		RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN );
}

void CMainFrame::OnViewTheme(UINT nID)
{
	SetOfficeTheme(
		ThemeFromCommand(nID));

	UpdateThemeCombo(
		ThemeFromCommand(nID));
}

void CMainFrame::OnUpdateViewTheme(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_eOfficeTheme == 
		ThemeFromCommand(pCmdUI->m_nID));
}

void CMainFrame::OnIndicatorButton(UINT nID)
{
	m_nPaneID = nID;
	m_strMessage.LoadString(nID);

	CView* pView = GetActiveView();
	if (pView)
	{
		pView->RedrawWindow();
	}

	CXTPStatusBarSwitchPane* pSwitchPane = (CXTPStatusBarSwitchPane*)m_wndStatusBar.FindPane(ID_INDICATOR_VIEW);
	pSwitchPane->SetChecked(nID);

};

void CMainFrame::OnUpdateIndicatorButton(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nPaneID);
};

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
	pPageCommands->AddCategories(IDR_STATUSTYPE);

	// initialize the commands page page.
	pPageCommands->InsertAllCommandsCategory();
	pPageCommands->InsertBuiltInMenus(IDR_STATUSTYPE);
	pPageCommands->InsertNewMenuCategory();

	// display the customize dialog.
	dlg.DoModal();
}

void CMainFrame::OnStatusBarShowButtons() 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_VIEW);

	pPane->SetCustomizationVisible(!pPane->GetCustomizationVisible());
}

void CMainFrame::OnUpdateStatusBarShowButtons(CCmdUI* pCmdUI) 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_VIEW);

	pCmdUI->SetCheck(pPane->GetCustomizationVisible());
}

void CMainFrame::OnStatusBarShowAviAnimation() 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_ANIM);

	pPane->SetCustomizationVisible(!pPane->GetCustomizationVisible());
	
}

void CMainFrame::OnUpdateStatusBarShowAviAnimation(CCmdUI* pCmdUI) 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_ANIM);

	pCmdUI->SetCheck(pPane->GetCustomizationVisible());
}

void CMainFrame::OnStatusBarShowProgressBar() 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_PROG);

	pPane->SetCustomizationVisible(!pPane->GetCustomizationVisible());
}

void CMainFrame::OnUpdateStatusBarShowProgressBar(CCmdUI* pCmdUI) 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_PROG);

	pCmdUI->SetCheck(pPane->GetCustomizationVisible());
}

void CMainFrame::OnStatusBarShowEditControl() 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_EDIT);

	pPane->SetCustomizationVisible(!pPane->GetCustomizationVisible());

}

void CMainFrame::OnUpdateStatusBarShowEditControl(CCmdUI* pCmdUI) 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_EDIT);

	pCmdUI->SetCheck(pPane->GetCustomizationVisible());
}

void CMainFrame::OnStatusBarShowCompanyLogo() 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_LOGO);

	pPane->SetCustomizationVisible(!pPane->GetCustomizationVisible());
}

void CMainFrame::OnUpdateStatusBarShowCompanyLogo(CCmdUI* pCmdUI) 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_LOGO);

	pCmdUI->SetCheck(pPane->GetCustomizationVisible());
}

void CMainFrame::OnStatusBarPlayAnimation() 
{
	m_bPlayAnimation = !m_bPlayAnimation;

	if (m_bPlayAnimation)
	{
		m_wndAnimCtrl.Play(0, (UINT)-1, (UINT)-1);
	}
	else
	{
		m_wndAnimCtrl.Stop();
	}
}

void CMainFrame::OnUpdateStatusBarPlayAnimation(CCmdUI* pCmdUI) 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_ANIM);

	pCmdUI->Enable(pPane->GetCustomizationVisible());
	pCmdUI->SetText(m_bPlayAnimation? _T("S&top Animation"): _T("P&lay Animation"));
}

void CMainFrame::OnStatusBarTestProgress() 
{
	TestProgress();
}

void CMainFrame::OnUpdateStatusBarTestProgress(CCmdUI* pCmdUI) 
{
	CXTPStatusBarPane* pPane = m_wndStatusBar.FindPane(ID_INDICATOR_PROG);
	
	pCmdUI->Enable(pPane->GetCustomizationVisible());
}
