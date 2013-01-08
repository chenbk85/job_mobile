// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SkinMDISample.h"

#include "SkinPropertySheet.h"
#include "MainFrm.h"
#include "DialogsView.h"


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
	ON_COMMAND(ID_VIEW_THEME_DIALOG, OnViewThemeDialog)
	ON_COMMAND(ID_VIEW_THEME, OnViewTheme)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME, OnUpdateViewTheme)
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_XTP_CREATECONTROL()
	ON_COMMAND_RANGE(ID_THEME_OFFICE2000, ID_THEME_WINXP, OnViewThemePopup)
	ON_UPDATE_COMMAND_UI_RANGE(ID_THEME_OFFICE2000, ID_THEME_WINXP, OnUpdateViewTheme)
	
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify) 
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CString CMainFrame::GetStylesPath()
{
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		
	
	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}

	return csStylesPath + _T("\\Styles\\");
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	OnShemaChanged(3);
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
	
	CXTPCommandBars* pCommandBars = GetCommandBars();
	
	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	
	
	CXTPToolBar* pStandardBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pStandardBar ||
		!pStandardBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
	}
	
	pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice);
	
	// Load the previous state for command bars.
	//LoadCommandBars(_T("CommandBars"));

	m_paneManager.InstallDockingPanes(this);

	// Create docking panes.
	m_paneManager.CreatePane(
		IDD_PANE_DIALOGS, CRect(0, 0,120, 120), xtpPaneDockRight);

	SetTheme(xtpThemeNativeWinXP);


	ShowThemesDialog();

	m_MTIClientWnd.Attach(this);

	return 0;
}

void CMainFrame::ShowThemesDialog()
{
	if (!::IsWindow(m_dlgThemes.GetSafeHwnd()))
	{
		m_dlgThemes.Create(this);
		m_dlgThemes.CenterWindow(this);
	}
	else
	{
		m_dlgThemes.SetFocus();
	}
	
	m_dlgThemes.ShowWindow(SW_SHOW);
}

void CMainFrame::OnClose() 
{
    // Save the current state for toolbars and menus.
    SaveCommandBars(_T("CommandBars"));

    CMDIFrameWnd::OnClose();
}

void CMainFrame::OnCustomize()
{
    // Get a pointer to the command bars object.
    CXTPCommandBars* pCommandBars = GetCommandBars();
    if(pCommandBars != NULL)
    {
        // Instantiate the customize dialog object.
        CXTPCustomizeSheet dlg(pCommandBars);

        // Add the options page to the customize dialog.
        CXTPCustomizeOptionsPage pageOptions(&dlg);
        dlg.AddPage(&pageOptions);

        // Add the commands page to the customize dialog.
        CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
        pCommands->AddCategories(IDR_SKINMDTYPE);

        // Use the command bar manager to initialize the 
        // customize dialog.
        pCommands->InsertAllCommandsCategory();
        pCommands->InsertBuiltInMenus(IDR_SKINMDTYPE);
        pCommands->InsertNewMenuCategory();

        // Display the dialog.
        dlg.DoModal();
    }
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


void CMainFrame::RedrawFrame(CWnd* pWnd)
{
	pWnd->RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);		
}

void CMainFrame::OnSkinChanged()
{
	if (m_nTheme == xtpThemeOffice2003)
	{
		if (XTPSkinManager()->GetResourceFile() &&
			XTPSkinManager()->GetResourceFile()->GetResourcePath().Find(_T("Office2007")) > 0)
		{
			XTPPaintManager()->SetTheme(xtpThemeOffice2007);
		}
		else
		{		
			XTPPaintManager()->SetTheme(xtpThemeOffice2003);
		}
	}
	XTPPaintManager()->RefreshMetrics();

	RedrawFrame(this);	
	
	if (::IsWindow(m_dlgThemes.m_hWnd))
		RedrawFrame(&m_dlgThemes);
	
	m_wndStatusBar.Invalidate();

	CWnd* pWnd = CWnd::FromHandle(m_hWndMDIClient)->GetWindow(GW_CHILD);
	while(pWnd)
	{
		RedrawFrame(pWnd);
		
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}

	GetCommandBars()->GetPaintManager()->RefreshMetrics();

	GetCommandBars()->RedrawCommandBars();

}

void CMainFrame::OnShemaChanged(int nSchema)
{
	switch (nSchema)
	{
	case 0:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("Office2007.cjstyles"));
		break;
	case 1:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("WinXP.Luna.cjstyles"), _T("NormalBlue.INI"));
		break;
	case 2:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("WinXP.Royale.cjstyles"), _T("NormalRoyale.INI"));
		break;
	case 3:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("Vista.cjstyles"), _T("NormalBlack2.INI"));
		break;
	default:
		XTPSkinManager()->LoadSkin(_T(""), _T(""));
	}

	if (m_hWnd) OnSkinChanged();
}


void CMainFrame::OnViewThemeDialog() 
{
	ShowThemesDialog();
}



void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);

// Toggle Tab Client
	m_MTIClientWnd.ShowWorkspace(!bPreview);


	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

 
void CMainFrame::OnViewTheme() 
{
	SetTheme((m_nTheme + 1) % 4);
}

void CMainFrame::OnUpdateViewTheme(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();	
	pCmdUI->SetCheck((int)pCmdUI->m_nID == m_nTheme + ID_THEME_OFFICE2000 ? TRUE : FALSE);
}


void CMainFrame::OnViewThemePopup(UINT nCommand)
{
	SetTheme(nCommand - ID_THEME_OFFICE2000);
}

void CMainFrame::SetTheme(int nTheme)
{

	m_nTheme = nTheme;

	if (m_nTheme == xtpThemeOffice2003)
	{
		if (XTPSkinManager()->GetResourceFile() &&
			XTPSkinManager()->GetResourceFile()->GetResourcePath().Find(_T("Office2007")) > 0)
		{
			nTheme = xtpThemeOffice2007;
		}
	}

	CXTPPaintManager::SetTheme((XTPPaintTheme)nTheme);
	XTPPaintManager()->GetIconsInfo()->bUseFadedIcons = FALSE;
	XTPPaintManager()->GetIconsInfo()->bIconsWithShadow = FALSE;

	m_paneManager.SetTheme((XTPDockingPanePaintTheme)nTheme);
	GetCommandBars()->RedrawCommandBars();

	m_MTIClientWnd.GetPaintManager()->RefreshMetrics();	
	
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);

}


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->nID == ID_VIEW_THEME)
	{
		lpCreateControl->controlType = xtpControlSplitButtonPopup;
		lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
		return TRUE;
	}
	
	return FALSE;
}


LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			pPane->AttachView(this, RUNTIME_CLASS(CDialogsView));
		}

		return TRUE; // handled
	}
	
	return FALSE;
}
 
