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
#include "GUI_VisualStudio.h"

#include "MainFrm.h"
#include "DynamicHelpView.h"

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
	ON_COMMAND(ID_WINDOW_AUTOHIDEALL, OnWindowAutohideall)
	ON_COMMAND(ID_WINDOW_MORE, OnWindowMore)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)

	ON_COMMAND(ID_VIEW_FULLSCREEN, OnFullScreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateFullScreen)

	ON_COMMAND_RANGE(ID_VIEW_SOLUTIONEXPLORER, ID_HELP_DYNAMICHELP, OnShowView)
	ON_COMMAND_RANGE(ID_FILE_NEW_PROJECT + 1, 200, OnEmptyCommandRange)

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_XTP_CREATECONTROL()

	ON_COMMAND_RANGE(ID_THEME_VC6, ID_THEME_VC9, OnTheme)
	ON_UPDATE_COMMAND_UI_RANGE(ID_THEME_VC6, ID_THEME_VC9, OnUpdateTheme)

#ifdef _XTP_INCLUDE_SKINFRAMEWORK
	ON_COMMAND_RANGE(ID_SKINFRAMEWORK_VISTABLUE, ID_SKINFRAMEWORK_SYSTEM, OnSkinFramework)
	ON_COMMAND_RANGE(ID_THEME_SKINFRAMEWORK, ID_THEME_SKINFRAMEWORK, OnEmptyCommandRange)
#endif

	ON_XTP_EXECUTE(ID_EDIT_STATE, OnEditState)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STATE, OnUpdateEditState)

	ON_XTP_EXECUTE(ID_EDIT_PLATFORM, OnEditPlatform)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PLATFORM, OnUpdateEditPlatform)
	ON_WM_ACTIVATE()
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
	m_nState = 1;
	m_nPlatform = 0;
	m_bFullScreen = FALSE;

	// get path of executable
	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));

	LPTSTR lpszExt = _tcsrchr(szBuff, '.');
	lstrcpy(lpszExt, _T(".xml"));

	m_strIniFileName = szBuff;

	m_pFullScreenLayout = NULL;
	m_rcMainFrame.SetRectEmpty();

	m_nTheme = ID_THEME_VC9;

#ifdef _XTP_INCLUDE_SKINFRAMEWORK
	XTPSkinManager()->GetResourceFile()->SetModuleHandle(AfxGetInstanceHandle());
#endif
}

CMainFrame::~CMainFrame()
{
	if (m_pFullScreenLayout)
	{
		delete m_pFullScreenLayout;
	}
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

	CXTPPaintManager::SetTheme(xtpThemeVisualStudio2008);

	CXTPCommandBars* pCommandBars = GetCommandBars();

	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pMenuBar->SetFlags(xtpFlagIgnoreSetMenuMessage);

	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CXTPToolBar* pWebBar = (CXTPToolBar*)pCommandBars->Add(_T("Web"), xtpBarTop);
	if (!pWebBar ||
		!pWebBar->LoadToolBar(IDR_TOOLBAR_WEB))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CXTPToolBar* pThemeBar = (CXTPToolBar*)pCommandBars->Add(_T("Theme"), xtpBarTop);
	if (!pThemeBar ||
		!pThemeBar->LoadToolBar(IDR_TOOLBAR_THEME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	DockRightOf(pThemeBar, pWebBar);

	CXTPToolBar* pFullScreenBar = (CXTPToolBar*)pCommandBars->Add(_T("Full Screen"), xtpBarTop);
	if (!pFullScreenBar ||
		!pFullScreenBar->LoadToolBar(IDR_TOOLBAR_FULLSCREEN))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pFullScreenBar->SetVisible(FALSE);

	XTPPaintManager()->GetIconsInfo()->bUseDisabledIcons = TRUE;
	XTPImageManager()->SetIcons(IDR_TOOLBAR_EXT);

	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
	pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice);
	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	CreateToolBox();

	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);
	
	m_paneManager.CreatePane(
		ID_WINDOWS_OUTPUT, CRect(0, 0, 150, 120), xtpPaneDockBottom);
	
	CXTPDockingPane* paneToolBox = m_paneManager.CreatePane(
		ID_VIEW_TOOLBOX, CRect(0, 0, 200, 120), xtpPaneDockRight);
	
	CXTPDockingPane* paneClassView = m_paneManager.CreatePane(
		ID_VIEW_CLASSVIEW, CRect(0, 0, 230, 140), xtpPaneDockLeft);
	
	CXTPDockingPane* paneSolutionExplorer = m_paneManager.CreatePane(
		ID_VIEW_SOLUTIONEXPLORER, CRect(0, 0, 230, 140), xtpPaneDockLeft);
	
	CXTPDockingPane* paneResourceView = m_paneManager.CreatePane(
		ID_VIEW_RESOURCEVIEW, CRect(0, 0, 230, 140), xtpPaneDockLeft);

	CXTPDockingPane* paneHelpView =m_paneManager.CreatePane(
		ID_HELP_DYNAMICHELP, CRect(0, 0, 210, 140), xtpPaneDockBottom, paneToolBox);

	paneHelpView->Close();

	m_paneManager.AttachPane(paneClassView, paneSolutionExplorer);
	m_paneManager.AttachPane(paneResourceView, paneClassView);

	paneClassView->Select();
	
	m_paneManager.CreatePane(
		ID_VIEW_PROPERTIESWINDOW, CRect(0, 0, 180, 140), xtpPaneDockBottom, paneClassView);

	m_paneManager.EnableKeyboardNavigate();
	

	//CXTPPropExchangeIniFile px(TRUE, 0, _T("Settings")); // To serialize to ini file
	CXTPPropExchangeXMLNode px(TRUE, 0, _T("Settings"));   // To serialize to XML file

	if (px.LoadFromFile(m_strIniFileName))
	{
		CXTPPropExchangeSection pxTaskPanel(px.GetSection(_T("TaskPanel")));
		m_wndTaskPanel.GetGroups()->DoPropExchange(&pxTaskPanel);

		CXTPPropExchangeSection pxNormalLayout(px.GetSection(_T("NormalLayout")));
		ExchangeLayout(&pxNormalLayout);

		m_pFullScreenLayout = DYNAMIC_DOWNCAST(CXTPPropExchangeXMLNode, px.GetSection(_T("FullScreenLayout")));
		ASSERT(m_pFullScreenLayout);
	}
	else
	{
		ResetToolboxItems();		
	}

	CXTPImageManager* pImageManager = pCommandBars->GetImageManager();

	pImageManager->InternalAddRef();
	m_paneManager.SetImageManager(pImageManager);

	m_paneManager.SetAlphaDockingContext(TRUE);
	m_paneManager.SetShowDockingContextStickers(TRUE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.SetDefaultPaneOptions(xtpPaneHasMenuButton);

	VERIFY(m_MTIClientWnd.Attach(this, TRUE));
	m_MTIClientWnd.EnableToolTips();

	m_MTIClientWnd.GetPaintManager()->m_bShowIcons = FALSE;
	m_MTIClientWnd.SetNewTabPosition(xtpWorkspaceNewTabLeftMost);
	m_MTIClientWnd.SetFlags(xtpWorkspaceHideArrowsAlways | xtpWorkspaceShowActiveFiles);

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


CXTPTaskPanelGroup* CMainFrame::CreateToolboxGroup(UINT nID)
{
	CXTPTaskPanelGroup* pFolder = m_wndTaskPanel.AddGroup(nID);

	CXTPTaskPanelGroupItem* pPointer = pFolder->AddLinkItem(ID_TOOLBOXITEM_POINTER, 0);
	pPointer->SetItemSelected(TRUE);
	pPointer->AllowDrag(FALSE);
	pPointer->AllowDrop(FALSE);

	return pFolder;
}

void CMainFrame::ResetToolboxItems()
{
	m_wndTaskPanel.GetGroups()->Clear(FALSE);

	CXTPTaskPanelGroup* pFolderPropertyPanes = CreateToolboxGroup(ID_TOOLBOXFOLDER_PROPERTYPANES);

	CXTPTaskPanelGroup* pFolderData = CreateToolboxGroup(ID_TOOLBOXFOLDER_DATA);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_DATASET                 ,26);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_OLEDBDATAADAPTER        ,27);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_OLEDBCONNECTION         ,28);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_OLEDBCOMMAND            ,29);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_SQLDATAADAPTER          ,30);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_SQLCONNECTION           ,31);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_SQLCOMMAND              ,32);
	pFolderData->AddLinkItem(ID_TOOLBOXITEM_DATAVIEW                ,33);

	CXTPTaskPanelGroup* pFolderComponents = CreateToolboxGroup(ID_TOOLBOXFOLDER_COMPONENTS);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_FILESYSTEMWATCHER     ,34);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_EVENTLOG              ,35);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_DIRECTORYENTRY        ,36);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_DIRECTORYSEARCHER     ,37);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_MESSAGEQUEUE          ,38);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_PERFORMANCECOUNTER    ,39);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_PROCESS               ,40);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_SERVICECONTROLLER     ,41);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_TIMER                 ,42);


	CXTPTaskPanelGroup* pFolderWindowsForms = CreateToolboxGroup(ID_TOOLBOXFOLDER_WINDOWSFORMS);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_BUTTON,             1);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_CHECK_BOX,              2);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_EDIT_CONTROL,           3);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_COMBO_BOX,              4);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_LIST_BOX,               5);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_GROUP_BOX,              6);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_RADIO_BUTTON,           7);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_STATIC_TEXT,            8);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_PICTURE_CONTROL,        9);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_HORIZONTAL_SCROLL_BAR,  10);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_VERTICAL_SCROLL_BAR,    11);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_SLIDER_CONTROL,     12);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_SPIN_CONTROL,           13);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_PROGRESS_CONTROL,       14);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_HOT_KEY,                15);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_LIST_CONTROL,           16);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_TREE_CONTROL,           17);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_TAB_CONTROL,            18);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_ANIMATION_CONTROL,      19);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_RICH_EDIT_CONTROL,      20);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_DATE_TIME_PICKER,       21);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_MONTH_CALENDAR_CONTROL,22);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_IP_ADDRESS_CONTROL, 23);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_EXTENDED_COMBO_BOX, 24);
	pFolderWindowsForms->AddLinkItem(ID_TOOLBOXITEM_CUSTOM_CONTROL,     25);

	CreateToolboxGroup(ID_TOOLBOXFOLDER_CLIPBOARDRING);
	CreateToolboxGroup(ID_TOOLBOXFOLDER_GENERAL);

	pFolderPropertyPanes->SetExpanded(TRUE);

}

CWnd* CMainFrame::CreateToolBox()
{
	if (!m_wndTaskPanel.GetSafeHwnd())
	{
		if (!m_wndTaskPanel.Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, CRect(0, 0, 0, 0), this, 0))
			return FALSE;
		
		m_wndTaskPanel.SetOwner(this);
		
		m_wndTaskPanel.GetImageManager()->SetIcons(IDB_TOOLBOXICONS, 0, 0, CSize(16, 16));
		m_wndTaskPanel.SetBehaviour(xtpTaskPanelBehaviourExplorer);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolboxWhidbey);
		m_wndTaskPanel.SetHotTrackStyle(xtpTaskPanelHighlightItem);
		m_wndTaskPanel.SetSelectItemOnFocus(TRUE);
		m_wndTaskPanel.SetSingleSelection();
		m_wndTaskPanel.AllowDrag(TRUE);		
	}
	
	return &m_wndTaskPanel;
}


void CMainFrame::ShowDockingPanePopupMenu(CXTPDockingPane* pPopupPane, CPoint pt, LPRECT lprcExclude)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_PANES));
	CMenu* pPopup = menu.GetSubMenu(0);
	
	
	if (pPopupPane->IsHidden())
	{
		pPopup->CheckMenuItem(ID_POPUP_AUTOHIDE, MF_BYCOMMAND|MF_CHECKED);
		pPopup->EnableMenuItem(ID_POPUP_FLOATING, MF_BYCOMMAND|MF_DISABLED);
		pPopup->EnableMenuItem(ID_POPUP_DOCKABLE, MF_BYCOMMAND|MF_DISABLED);
	}
	else if (pPopupPane->GetOptions() & xtpPaneNoDockable)
	{
		pPopup->CheckMenuItem(ID_POPUP_FLOATING, MF_BYCOMMAND|MF_CHECKED);
	}
	else
	{
		pPopup->CheckMenuItem(ID_POPUP_DOCKABLE, MF_BYCOMMAND|MF_CHECKED);
	}

	TPMPARAMS tpm;
	tpm.cbSize = sizeof(TPMPARAMS);
	tpm.rcExclude = lprcExclude ? *lprcExclude : CRect(0, 0, 0, 0);

	int nCommand = GetCommandBars()->TrackPopupMenuEx(pPopup, TPM_RIGHTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD, pt.x, pt.y, NULL, &tpm);
	
	switch (nCommand)
	{
	case ID_POPUP_HIDE:
		pPopupPane->Close();
		break;		
		
	case ID_POPUP_AUTOHIDE:
		m_paneManager.ToggleAutoHide(pPopupPane);
		break;

	case ID_POPUP_DOCKABLE:
		if (pPopupPane->GetOptions() & xtpPaneNoDockable)
		{
			pPopupPane->SetOptions(pPopupPane->GetOptions() & ~xtpPaneNoDockable);
		}
		break;

	case ID_POPUP_FLOATING:
		if ((pPopupPane->GetOptions() & xtpPaneNoDockable) == 0)
		{
			if (!pPopupPane->IsFloating())
				m_paneManager.ToggleDocking(pPopupPane);
			
			pPopupPane->SetOptions(pPopupPane->GetOptions() | xtpPaneNoDockable);
		}

		break;
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
				case ID_VIEW_TOOLBOX:					
					pPane->Attach(CreateToolBox());
					break;

				case ID_VIEW_CLASSVIEW:
					if (!m_wndClassView.GetSafeHwnd())
					{
						m_wndClassView.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndClassView);
					break;

				case ID_VIEW_RESOURCEVIEW:
					if (!m_wndResourceView.GetSafeHwnd())
					{
						m_wndResourceView.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndResourceView);
					break;

				case ID_VIEW_SOLUTIONEXPLORER:
					if (!m_wndSolutionExplorer.GetSafeHwnd())
					{
						m_wndSolutionExplorer.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndSolutionExplorer);
					break;

				case ID_VIEW_PROPERTIESWINDOW:
					if (!m_wndProperties.GetSafeHwnd())
					{
						m_wndProperties.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndProperties);
					break;

				case ID_WINDOWS_OUTPUT:
					if (!m_wndOutput.GetSafeHwnd())
					{
						m_wndOutput.Create(WS_HSCROLL|ES_AUTOHSCROLL|ES_MULTILINE|WS_VISIBLE, CXTPEmptyRect(), this, 0);
					}
					pPane->Attach(&m_wndOutput);
					break;

				case ID_HELP_DYNAMICHELP:
					{
						// attach the dynamic help view to the pane.
						CWnd* pView = pPane->AttachView(this, RUNTIME_CLASS(CDynamicHelpView));
						pView;
						break;
					}
	
			}
		}
		return 1;
	}

	if (wParam == XTP_DPN_CONTEXTMENU)
	{
		XTP_DOCKINGPANE_CLICK* pClick = (XTP_DOCKINGPANE_CLICK*)lParam;

		CXTPDockingPane* pPopupPane = pClick->pPane;
		if (!pPopupPane) 
			return FALSE;

		ShowDockingPanePopupMenu(pPopupPane, pClick->pt, pClick->rcExclude);

		return TRUE;
	}
	
	return 0;
}

void CMainFrame::OnShowView(UINT nID)
{
	m_paneManager.ShowPane(nID);
}

void CMainFrame::OnEmptyCommandRange(UINT)
{

}

void CMainFrame::OnWindowAutohideall()
{
	CXTPDockingPaneInfoList& lstPanes = m_paneManager.GetPaneList();
	POSITION pos = lstPanes.GetHeadPosition();
	while (pos)
	{
		CXTPDockingPane* pPane = lstPanes.GetNext(pos);
		if (!pPane->IsClosed() && !pPane->IsHidden())
			m_paneManager.HidePane(pPane);
	}
}

void CMainFrame::OnWindowMore()
{
	CXTWindowList dlg(this);
	dlg.DoModal();
}


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->bToolBar)
	{
		CXTPToolBar* pToolBar = DYNAMIC_DOWNCAST(CXTPToolBar, lpCreateControl->pCommandBar);
		if (!pToolBar)
			return FALSE;

		if (lpCreateControl->nID == ID_VIEW_CLASSVIEW && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_VIEW_FULLSCREEN)
		{
			lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_THEME_SKINFRAMEWORK)
		{
			lpCreateControl->controlType = xtpControlPopup;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_FILE_NEW_PROJECT && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_PROJECT_ADDNEWITEM && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_FIND_EX && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboFind = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboFind->SetDropDownListStyle();

			pComboFind->AddString(_T("Line1"));
			pComboFind->AddString(_T("Line2"));
			pComboFind->AddString(_T("Line3"));

			pComboFind->SetWidth(180);
			pComboFind->SetCaption(_T("Find"));
			pComboFind->SetStyle(xtpComboLabel);

			lpCreateControl->pControl = pComboFind;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_STATE && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboState = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboState->AddString(_T("Debug"));
			pComboState->AddString(_T("Release"));
			pComboState->AddString(_T("Configuration Manager"));
			pComboState->SetDropDownWidth(150);
			lpCreateControl->pControl = pComboState;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_PLATFORM && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			CXTPControlComboBox* pComboState = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboState->AddString(_T("Win32"));
			pComboState->AddString(_T("Configuration Manager"));
			pComboState->SetDropDownWidth(150);
			lpCreateControl->pControl = pComboState;
			return TRUE;
		}


		if (lpCreateControl->nID == ID_GOTO_URL && pToolBar->GetBarID() == IDR_TOOLBAR_WEB)
		{
			CXTPControlComboBox* pComboUrl = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboUrl->AddString(_T("http://www.codejock.com"));
			pComboUrl->AddString(_T("ms-help://MS.VSCC/vsccCommon/html/vsccCommon_Start_Page.htm"));
			pComboUrl->SetWidth(200);
			pComboUrl->SetDropDownWidth(300);
			pComboUrl->SetDropDownListStyle();
			pComboUrl->SetFlags(xtpFlagManualUpdate);
			pComboUrl->SetEditText(_T("http://www.codejock.com"));
			pComboUrl->EnableShellAutoComplete();

			lpCreateControl->pControl = pComboUrl;
			return TRUE;
		}


	}
	return FALSE;

}

void CMainFrame::OnCustomize()
{
	CXTPCustomizeSheet cs(GetCommandBars());

	CXTPCustomizeKeyboardPage pageKeyboard(&cs);
	cs.AddPage(&pageKeyboard);
	pageKeyboard.AddCategories(IDR_MAINFRAME, TRUE);

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_MAINFRAME, TRUE);

	pCommands->InsertAllCommandsCategory();
	pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pCommands->InsertNewMenuCategory();

	cs.DoModal();
}

void CMainFrame::OnEditState(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox)
	{
		int nState = pControl->GetCurSel();
		if (nState != 2)
		{
			m_nState = nState;
		}
		else
		{
			MessageBox(_T("Configuration Manager"));
			pControl->SetCurSel(m_nState);
		}
		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateEditState(CCmdUI* pCmdUI)
{
	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmdUI->m_pOther;
	if (pToolBar && !XTPMouseManager()->IsTrackedLock())
	{
		CXTPControlComboBox* pStateCombo = (CXTPControlComboBox*)pToolBar->GetControls()->GetAt(pCmdUI->m_nIndex);

		if (pStateCombo->GetType() == xtpControlComboBox)
		{
			pStateCombo->SetCurSel(m_nState);
		}
	}

	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnEditPlatform(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox)
	{
		int nState = pControl->GetCurSel();
		if (nState != 1)
		{
			m_nPlatform = nState;
		}
		else
		{
			MessageBox(_T("Configuration Manager"));
			pControl->SetCurSel(m_nPlatform);
		}
		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateEditPlatform(CCmdUI* pCmdUI)
{
	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmdUI->m_pOther;
	if (pToolBar && !XTPMouseManager()->IsTrackedLock())
	{
		CXTPControlComboBox* pStateCombo = (CXTPControlComboBox*)pToolBar->GetControls()->GetAt(pCmdUI->m_nIndex);

		if (pStateCombo->GetType() == xtpControlComboBox)
		{
			pStateCombo->SetCurSel(m_nPlatform);
		}
	}

	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnClose()
{
	//CXTPPropExchangeIniFile px(FALSE, 0, _T("Settings"));    // To serialize to ini file
	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));      // To serialize to XML file

	if (px.OnBeforeExchange()) 
	{
		CXTPPropExchangeSection pxTaskPanel(px.GetSection(_T("TaskPanel")));
		m_wndTaskPanel.GetGroups()->DoPropExchange(&pxTaskPanel);

		// Reset Full Screen Mode
		if (m_bFullScreen)
		{
			OnFullScreen();
		}

		CXTPPropExchangeSection pxNormalLayout(px.GetSection(_T("NormalLayout")));
		ExchangeLayout(&pxNormalLayout);
	
		px.PutSection(m_pFullScreenLayout);

		px.SaveToFile(m_strIniFileName);
	}

	CMDIFrameWnd::OnClose();
}


void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{

// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);
// Toggle Tab Client
	m_MTIClientWnd.ShowWorkspace(!bPreview);

// Toggle Docking Panes.
	m_paneManager.OnSetPreviewMode(bPreview);


	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	static HWND hFocus = 0;

	if (nState == WA_INACTIVE)
	{
		hFocus = m_paneManager.GetActivePane() != NULL ? ::GetFocus() : NULL;
	}
	
	CMDIFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	if (nState != WA_INACTIVE && hFocus)
	{
		::SetFocus(hFocus);		
		hFocus = NULL;		
	}
}

void CMainFrame::ExchangeLayout(CXTPPropExchange* pPX, BOOL bSerializeControls /*= TRUE*/)
{
	XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; param.bSerializeControls = bSerializeControls; 

	CXTPPropExchangeSection pxCommandBars(pPX->GetSection(_T("CommandBars")));
	GetCommandBars()->DoPropExchange(&pxCommandBars, &param);

	CXTPPropExchangeSection secShortcuts(pPX->GetSection(_T("Shortcuts")));
	GetCommandBars()->GetShortcutManager()->DoPropExchange(&secShortcuts);

	CXTPPropExchangeSection secOptions(pPX->GetSection(_T("Options")));	
	GetCommandBars()->GetCommandBarsOptions()->DoPropExchange(&secOptions, TRUE);

	CXTPPropExchangeSection pxDockingPane(pPX->GetSection(_T("DockingPane")));	
	m_paneManager.DoPropExchange(&pxDockingPane);
}

void CMainFrame::OnFullScreen()
{
	m_bFullScreen ^= 1;

	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));
	CXTPPropExchangeXMLNode* pxLayoutSave = DYNAMIC_DOWNCAST(CXTPPropExchangeXMLNode, px.GetSection(_T("FullScreenLayout")));
	ASSERT(pxLayoutSave);

	// Save current layout
	if (pxLayoutSave != 0)
	{	
		ExchangeLayout(pxLayoutSave, FALSE);
	}

	// If Full screen layout exists
	if (m_pFullScreenLayout && m_pFullScreenLayout->IsSectionExists(_T("CommandBars")))
	{
		// Set it
		m_pFullScreenLayout->SetLoading(TRUE);
		ExchangeLayout(m_pFullScreenLayout, FALSE);
	}
	// Else create new fullscreen layout. Hide all toolbars and DockingPanes.
	else
	{		
		for (int i = 0; i < GetCommandBars()->GetCount(); i++)
		{
			CXTPToolBar* pToolBar = GetCommandBars()->GetAt(i);
			pToolBar->SetVisible((pToolBar->GetType() == xtpBarTypeMenuBar) || (pToolBar->GetBarID() == IDR_TOOLBAR_FULLSCREEN));
		}
		m_paneManager.CloseAll();
	}
	
	// Save old layout
	if (m_pFullScreenLayout)
	{
		delete m_pFullScreenLayout;
	}
	m_pFullScreenLayout = pxLayoutSave;


	if (m_bFullScreen)
	{
		GetWindowRect(&m_rcMainFrame);

		ModifyStyle(WS_CAPTION|WS_THICKFRAME, 0);
		
		// Now resize the main window
		CRect rcScreen = XTPMultiMonitor()->GetScreenArea(this);
		
		int cxBorder = ::GetSystemMetrics(SM_CXBORDER);
		int cyBorder = ::GetSystemMetrics(SM_CYBORDER);

		SetWindowPos(NULL, rcScreen.left - cxBorder, rcScreen.top - cyBorder, 
			rcScreen.Width() + cxBorder * 2, rcScreen.Height() + cyBorder * 2, SWP_NOZORDER);

		m_wndStatusBar.ShowWindow(SW_HIDE);

	} 
	else
	{
		ModifyStyle(0, WS_CAPTION|WS_THICKFRAME);
		MoveWindow(&m_rcMainFrame);
		m_wndStatusBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout(TRUE);
}

void CMainFrame::OnUpdateFullScreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bFullScreen);

}

class CVisualStudio6Theme : public CXTPDefaultTheme
{
	CSize DrawCommandBarGripper(CDC* pDC, CXTPCommandBar* pBar, BOOL bDraw)
	{
		if (pBar->IsDialogBar() || pBar->GetPosition() == xtpBarFloating)
			return CXTPDefaultTheme::DrawCommandBarGripper(pDC, pBar, bDraw);
		
		CRect rc;
		pBar->GetClientRect(&rc);
		
		if (pBar->GetPosition() == xtpBarRight || pBar->GetPosition() == xtpBarLeft)
		{
			if (pDC && bDraw)
			{
				Draw3dRect(pDC, CRect(3, 3, rc.right - 3, 6), COLOR_BTNHILIGHT, COLOR_3DSHADOW);
				Draw3dRect(pDC, CRect(3, 7, rc.right - 3, 10), COLOR_BTNHILIGHT, COLOR_3DSHADOW);
			}
			return CSize(0, 10);
		}
		else if (pBar->GetPosition() == xtpBarTop || pBar->GetPosition() == xtpBarBottom)
		{
			if (pDC && bDraw)
			{
				Draw3dRect(pDC, CRect(3, 3, 6, rc.bottom - 3), COLOR_BTNHILIGHT, COLOR_3DSHADOW);
				Draw3dRect(pDC, CRect(7, 3, 10, rc.bottom - 3), COLOR_BTNHILIGHT, COLOR_3DSHADOW);
			}
			return CSize(10, 0);
		}
		return 0;
	}
};

void CMainFrame::OnSkinFramework(UINT nID)
{
#ifdef _XTP_INCLUDE_SKINFRAMEWORK
	switch (nID)
	{
	case ID_SKINFRAMEWORK_VISTABLUE:
		XTPSkinManager()->LoadSkin(NULL, _T("NORMALBLUE.INI"));
		break;

	case ID_SKINFRAMEWORK_VISTABLACK:
		XTPSkinManager()->LoadSkin(NULL, _T("NORMALBLACK.INI"));
		break;

	default:
		XTPSkinManager()->LoadSkin(NULL);
		break;
	}
#endif
}

void CMainFrame::OnTheme(UINT nID)
{
	m_nTheme = nID;

	switch (nID)
	{
	case ID_THEME_VC6:
		XTPPaintManager()->SetCustomTheme(new CVisualStudio6Theme);
		m_paneManager.SetTheme(xtpPaneThemeGrippered);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolbox);
		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeDefault);
		break;

	case ID_THEME_VC7:
		XTPPaintManager()->SetTheme(xtpThemeOfficeXP);
		m_paneManager.SetTheme(xtpPaneThemeOffice);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolbox);
		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeOfficeXP);
		break;

	case ID_THEME_VC8:
		XTPPaintManager()->SetTheme(xtpThemeWhidbey);
		m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolboxWhidbey);
		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeWhidbey);
		break;

	case ID_THEME_VC9:
		XTPPaintManager()->SetTheme(xtpThemeVisualStudio2008);
		m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);
		m_wndTaskPanel.SetTheme(xtpTaskPanelThemeToolboxWhidbey);
		m_wndProperties.m_wndPropertyGrid.SetTheme(xtpGridThemeWhidbey);
		break;
	}

	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateTheme(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nTheme ? TRUE : FALSE);
}
