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
#include "CustomThemes.h"

#include "MainFrm.h"

#include "CustomControls.h"
#include "Themes.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_SCROLL_ITEM1, ID_MULTICOLUMN_COLUMN2, OnScrollItem)
	ON_COMMAND_RANGE(ID_BUTTON32799, ID_BUTTON32818, OnScrollItem)
	ON_COMMAND_RANGE(ID_BACK, ID_VIEWS, OnScrollItem)

	
	ON_UPDATE_COMMAND_UI_RANGE(ID_THEME_DEFAULT, ID_THEME_RIBBON, OnUpdateTheme)
	ON_COMMAND_RANGE(ID_THEME_DEFAULT, ID_THEME_RIBBON, OnSwitchTheme)
	ON_COMMAND(ID_THEME_CUSTOM, OnThemeCustom)

	ON_COMMAND(ID_VIEW_OFFICE2007FRAME, OnViewOffice2007Frame)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OFFICE2007FRAME, OnUpdateViewOffice2007Frame)

	ON_COMMAND(ID_VIEW_TEXTBELOWICONS, OnTextBelow)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TEXTBELOWICONS, OnUpdateTextBelow)

	ON_COMMAND(ID_VIEW_RIGHTTOLEFT, OnOptionsRighttoleft)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RIGHTTOLEFT, OnUpdateOptionsRighttoleft)


	ON_COMMAND_EX(ID_VIEW_MESSAGE_BAR, CFrameWnd::OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MESSAGE_BAR, CFrameWnd::OnUpdateControlBarMenu)

	ON_WM_CLOSE()

	ON_COMMAND_RANGE(ID_SAVEAS_XML, ID_SAVEAS_BINARY, OnSaveAs)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SAVEAS_XML, ID_SAVEAS_BINARY, OnUpdateSaveAs)


	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)

	ON_XTP_EXECUTE(ID_EDIT_STATE, OnEditState)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STATE, OnUpdateEditState)
	ON_XTP_EXECUTE(ID_FILE_NEW, OnFileNew)

	ON_XTP_CREATECONTROL()
	ON_XTP_CREATECOMMANDBAR()

	ON_XTP_EXECUTE_RANGE(ID_TASKPANEL_NEWDOCUMENT, ID_TASKPANEL_SEARCH, OnTaskPanelCaption)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TASKPANEL_NEWDOCUMENT, ID_TASKPANEL_SEARCH, OnUpdateTaskPanelCaption)
	ON_MESSAGE(WM_XTP_CONTROLRBUTTONUP, OnControlRButtonUp)


	ON_XTP_EXECUTE(ID_COMBO_DATE, OnComboDate)
	ON_UPDATE_COMMAND_UI(ID_COMBO_DATE, OnUpdateComboDate)	


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
	ID_FILE_CLOSE,
	ID_FILE_SAVE_AS,
	ID_FILE_PRINT_PREVIEW,
	ID_FILE_PRINT_SETUP,
	ID_WINDOW_CASCADE,
	ID_WINDOW_TILE_HORZ,
	ID_WINDOW_ARRANGE,
	ID_SCROLL_ITEM21,
	ID_SCROLL_ITEM22,
	ID_SCROLL_ITEM23,
	ID_SCROLL_ITEM24,
	ID_SCROLL_ITEM25,
	ID_SCROLL_ITEM26
};

LPCTSTR lpszProfileName = _T("CommandBars_ver13");

#define IDR_COLORTEXT_POPUP 1000
#define IDR_COLORBACK_POPUP 1001

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nState = 0;
	m_nIDSaveAs = ID_SAVEAS_XML;
	m_dt = COleDateTime::GetCurrentTime();
	m_nCurrentTheme = ID_THEME_OFFICE_XP;

	m_bOffice2007Frame = 2;
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

	// Initialize command bars.  Command bars must be created and initialized
	// after all standard MFC control bars have been created.
	if (!InitCommandBars())
		return -1;

	// Set the default theme to Office XP.
	CXTPPaintManager::SetTheme(xtpThemeOfficeXP);

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();

	// create the menubar.
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_CUSTOMTYPE);
	pMenuBar->SetFlags(xtpFlagIgnoreSetMenuMessage);

	// create the standard toolbar.
	CXTPToolBar* pStandardBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pStandardBar || !pStandardBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// create the left docked toolbar.
	CXTPToolBar* pLeftBar = (CXTPToolBar*)pCommandBars->Add(_T("Left Bar"), xtpBarLeft);
	if (!pLeftBar || !pLeftBar->LoadToolBar(IDR_LEFT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// create the combo box toolbar.
	CXTPToolBar* pComboBoxBar = (CXTPToolBar*)pCommandBars->Add(_T("ComboBox Bar"), xtpBarBottom);
	if (!pComboBoxBar || !pComboBoxBar->LoadToolBar(IDR_COMBOBOX_BAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}


	// create the theme toolbar.
	CXTPToolBar* pThemeBar = (CXTPToolBar*)pCommandBars->Add(_T("Theme Bar"), xtpBarTop);
	if (!pThemeBar || !pThemeBar->LoadToolBar(IDR_SWITCH))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// create the custom toolbar.
	CXTPToolBar* pCustomBar = (CXTPToolBar*)pCommandBars->Add(_T("Custom Bar"), xtpBarTop);
	if (!pCustomBar || !pCustomBar->LoadToolBar(IDR_CUSTOM))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// Dock to the right of...
	DockRightOf(pCustomBar, pStandardBar);




	// create the 24 bit icon toolbar.
	CXTPToolBar* p24BitIconBar = (CXTPToolBar*)pCommandBars->Add(_T("26bit Icons Bar"), xtpBarTop);
	if (!p24BitIconBar || !p24BitIconBar->LoadToolBar(IDR_EXPLORER_BAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// Dock to the right of...
	DockRightOf(p24BitIconBar, pThemeBar);

	CXTPDialogBar* pBar = (CXTPDialogBar*)pCommandBars->Add(_T("Task Panel"), xtpBarRight, RUNTIME_CLASS(CXTPDialogBar));
	pBar->SetBarID(200);
	pBar->EnableDocking(xtpFlagAlignAny|xtpFlagFloating|xtpFlagStretched);
	pBar->SetCaption(_T("&New Document"));
	pBar->ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	m_wndTaskPanel.Create(pBar);
	pBar->SetChild(&m_wndTaskPanel);
	pBar->SetCaptionPopup(IDR_MENU_TASKPANEL);
	m_wndTaskPanel.SetTheme(XTPPaintManager()->BaseTheme());

	pCommandBars->GetCommandBarsOptions()->animationType = xtpAnimateWindowsDefault;
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);

	CXTPControlWindowList::m_bShowRadioButtons = TRUE;

	pCommandBars->GetContextMenus()->Add(IDR_CONTEXT_MENU);
	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	// Load the saved toolbar layout.
	LoadCommandBars(lpszProfileName);

	
	if (!m_wndMessageBar.Create(GetCommandBars()))
		return -1;

	m_wndMessageBar.AddButton(SC_CLOSE, NULL, _T("Close Message Bar"));
	m_wndMessageBar.AddButton(XTP_ID_CUSTOMIZE, _T("Options..."));
	m_wndMessageBar.SetMessage(_T("Security Warning. Certain content has been disabled"));
	m_wndMessageBar.ShowWindow(SW_HIDE);


	// Initialize intelligent menus.
	pCommandBars->GetCommandBarsOptions()->bAlwaysShowFullMenus = FALSE;
	pCommandBars->HideCommands(uHideCmds, _countof(uHideCmds));

	// Toggle floating by double click
	pCommandBars->GetCommandBarsOptions()->bDblClickFloat = TRUE;
	
	pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipOffice);

	// Change size of popup icons.
	// pCommandBars->GetCommandBarsOptions()->szPopupIcons = CSize(20, 20);

	m_wndClient.Attach(this);
	
	return 0;
}

void CMainFrame::DockRightOf(CXTPToolBar* pBarToDock, CXTPToolBar* pBarOnLeft)
{
	RecalcLayout(TRUE);
	CXTPWindowRect rcBar(pBarOnLeft);
	rcBar.OffsetRect(rcBar.Width(), 0);
	GetCommandBars()->DockCommandBar(pBarToDock, rcBar, pBarOnLeft->GetDockBar());
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


// CMainFrame message handlers


void CMainFrame::SetCustomTheme(CXTPPaintManager* pTheme)
{
	CXTPPaintManager::SetCustomTheme(pTheme);

	if ((pTheme->BaseTheme() == xtpThemeOffice2007 || pTheme->BaseTheme() == xtpThemeRibbon) &&
		(m_bOffice2007Frame == 2 || m_bOffice2007Frame == 1))
	{
		EnableOffice2007Frame(GetCommandBars());
	}
	else
	{
		EnableOffice2007Frame(0);
	}

	m_wndTaskPanel.SetTheme(XTPPaintManager()->BaseTheme());
	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnThemeCustom()
{

}

void CMainFrame::OnUpdateTheme(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrentTheme ? TRUE : FALSE);
}
void CMainFrame::OnSwitchTheme(UINT nTheme)
{
	switch (nTheme)
	{
		case ID_THEME_DEFAULT: SetCustomTheme(new CXTPDefaultTheme()); break;
		case ID_THEME_OFFICE_XP: SetCustomTheme(new CXTPOfficeTheme()); break;
		case ID_THEME_OFFICE_2003: SetCustomTheme(new CXTPOffice2003Theme()); break;
		case ID_THEME_WINDOWS_XP: SetCustomTheme(new CXTPNativeXPTheme()); break;
		case ID_THEME_RIBBON: SetCustomTheme(new CXTPRibbonTheme()); break;
		case ID_THEME_OFFICE2007: SetCustomTheme(new CXTPOffice2007Theme()); break;
		case ID_THEME_VISUALSTUDIO2008: SetCustomTheme(new CXTPVisualStudio2008Theme()); break;

		case ID_THEME_MAC: SetCustomTheme(new CCustomMacTheme()); break;
		case ID_THEME_GRAY: SetCustomTheme(new CCustomGrayTheme()); break;
		case ID_THEME_ICY: SetCustomTheme(new CCustomIcyTheme()); break;
		case ID_THEME_GRAD: SetCustomTheme(new CCustomGradientTheme()); break;
		case ID_THEME_BEVEL: SetCustomTheme(new CCustomBevelTheme()); break;
		case ID_THEME_FANCY: SetCustomTheme(new CCustomFancyTheme()); break;
		case ID_THEME_ACD: SetCustomTheme(new CCustomBackgroundTheme()); break;
	}

	m_nCurrentTheme = nTheme;
}

void CMainFrame::OnViewOffice2007Frame()
{
	m_bOffice2007Frame = m_bOffice2007Frame + 1;
	if (m_bOffice2007Frame == 3) m_bOffice2007Frame = 0;

	OnSwitchTheme(m_nCurrentTheme);
}

void CMainFrame::OnUpdateViewOffice2007Frame(CCmdUI* pCmdUI)
{
	if (m_nCurrentTheme == ID_THEME_RIBBON || m_nCurrentTheme == ID_THEME_OFFICE2007)
	{
		pCmdUI->Enable(TRUE);
		pCmdUI->SetCheck(m_bOffice2007Frame);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CMainFrame::OnScrollItem(UINT)
{
	// TODO: Add your command handler code here
}

BOOL GetAppDataFolder(CString& strAppDataFolder)
{
	OSVERSIONINFO versionInfo = { sizeof(OSVERSIONINFO) };
	if (!(GetVersionEx(&versionInfo) && versionInfo.dwPlatformId >= VER_PLATFORM_WIN32_NT && versionInfo.dwMajorVersion >= 5))
		return FALSE;

	LPITEMIDLIST pidlAppData = NULL;
	IMalloc * pMalloc = NULL;
	BOOL bResult = FALSE;

	HRESULT hr = SHGetMalloc(&pMalloc);
	if (SUCCEEDED(hr))
	{
		TCHAR   szPath[MAX_PATH];
		if (SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidlAppData) == NOERROR )
		{
			if (SHGetPathFromIDList( pidlAppData, szPath))
			{
				strAppDataFolder = szPath;
				bResult = TRUE;
			}
		}

		pMalloc->Free(pidlAppData);
		pMalloc->Release();

	}
	return TRUE;
}

void CMainFrame::OnClose()
{
	CString strAppDataFolder;

	if (GetAppDataFolder(strAppDataFolder))
	{
		CreateDirectory(strAppDataFolder + _T("\\") + AfxGetApp()->m_pszAppName, NULL);

		// Set customization path as "\Documents and Settings\user\Application Data\CustomThemes\CommandBars_ver6"
		GetCommandBars()->SetCustomizationDataFileName(strAppDataFolder + _T("\\") + AfxGetApp()->m_pszAppName + _T("\\") + lpszProfileName);
	}


	SaveCommandBars(lpszProfileName);

	CMDIFrameWnd::OnClose();
}





void CMainFrame::OnCustomize()
{
	CXTPCustomizeSheet cs(GetCommandBars());
	
	CXTPCustomizeKeyboardPage pageKeyboard(&cs);
	pageKeyboard.AddCategories(IDR_CUSTOMTYPE);
	cs.AddPage(&pageKeyboard);

	CXTPCustomizeMenusPage pageMenus(&cs);
	cs.AddPage(&pageMenus);

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_CUSTOMTYPE);
	pCommands->GetControls(_T("File"))->Add(xtpControlButton, ID_FILE_OPEN, _T(""), 1);

	pCommands->AddToolbarCategory(_T("Themes"), IDR_SWITCH);

	pCommands->InsertAllCommandsCategory();
	pCommands->InsertBuiltInMenus(IDR_CUSTOMTYPE);
	pCommands->InsertNewMenuCategory();

	CXTPControls* pControls = pCommands->GetControls(_T("Test"));
	ASSERT(pControls);
	pControls->Add(xtpControlButton, ID_FILE_NEW);
	pControls->Add(xtpControlPopup, ID_TOOLS_HEX);
	pControls->Add(xtpControlButtonPopup, ID_TOOLS_HEX);
	pControls->Add(xtpControlSplitButtonPopup, ID_TOOLS_HEX);

	CXTPControl* pControlState = GetCommandBars()->FindControl(xtpControlComboBox, ID_EDIT_STATE, FALSE, TRUE);
	if (pControlState) pControls->AddClone(pControlState, 4);

	CXTPControl* pControlNew = GetCommandBars()->FindControl(xtpControlEdit, ID_FILE_NEW, FALSE, TRUE);
	if (pControlNew) pControls->AddClone(pControlNew, 6);

	cs.DoModal();
}


int CMainFrame::OnCreateCommandBar(LPCREATEBARSTRUCT lpCreatePopup)
{
	if (lpCreatePopup->bTearOffBar && (lpCreatePopup->nID == IDR_COLORTEXT_POPUP || lpCreatePopup->nID == IDR_COLORBACK_POPUP))
	{
		CXTPToolBar* pToolBar = DYNAMIC_DOWNCAST(CXTPToolBar, lpCreatePopup->pCommandBar);
		ASSERT(pToolBar);

		// Prevent docking.
		pToolBar->EnableDocking(xtpFlagFloating);
		// Prevent customization
		pToolBar->EnableCustomization(FALSE);
		return TRUE;
	}
	return FALSE;
}

int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->bToolBar == FALSE)
	{
		if (lpCreateControl->controlType == xtpControlPopup && lpCreateControl->strCaption == _T("&Open..."))
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			lpCreateControl->nID = ID_FILE_OPEN;
			return TRUE;
		}
		if (lpCreateControl->controlType == xtpControlButton && lpCreateControl->nID == ID_TOOLS_HEX)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}
		
		if (lpCreateControl->nID == ID_MULTICOLUMN_COLUMN1 || lpCreateControl->nID == ID_MULTICOLUMN_COLUMN2)
		{
			lpCreateControl->pControl = new CXTPControlLabel();
			lpCreateControl->pControl->SetItemDefault(TRUE);
			lpCreateControl->pControl->SetStyle(xtpButtonCaption);

			return TRUE;
		}

		if (lpCreateControl->controlType == xtpControlButton && lpCreateControl->nID == ID_EDIT_FIND)
		{
			CXTPControlComboBox* pComboFind = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboFind->SetDropDownListStyle();
			pComboFind->SetEditHint(_T("Click to find string"));

			pComboFind->AddString(_T("Line1"));
			pComboFind->AddString(_T("Line2"));
			pComboFind->AddString(_T("Line3"));

			pComboFind->SetWidth(150);
			pComboFind->SetCaption(_T("Find"));
			pComboFind->SetStyle(xtpComboLabel);

			lpCreateControl->pControl = pComboFind;
			return TRUE;

		}
		if (lpCreateControl->nID == ID_PARA_INDENT)
		{
			CXTPControlEdit* pControl = new CXTPControlEdit();
			pControl->SetWidth(133);
			pControl->ShowSpinButtons();

			lpCreateControl->pControl = pControl;
			return TRUE;

		}
	}
	else
	{
		CXTPToolBar* pToolBar = DYNAMIC_DOWNCAST(CXTPToolBar, lpCreateControl->pCommandBar);
		if (!pToolBar)
			return FALSE;

		if (lpCreateControl->nID == ID_FILE_PRINT_EX && pToolBar->GetBarID() == IDR_LEFT)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
			return TRUE;
		}
		if (lpCreateControl->nID == IDR_MENU_POPUP && pToolBar->GetBarID() == IDR_LEFT)
		{
			lpCreateControl->controlType = xtpControlPopup;
			lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_TOOLS_HEX && pToolBar->GetBarID() == IDR_MAINFRAME)
		{
			lpCreateControl->controlType = xtpControlSplitButtonPopup;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_FILE_NEW && pToolBar->GetBarID() == IDR_COMBOBOX_BAR)
		{
			lpCreateControl->controlType = xtpControlEdit;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_THEME_CUSTOM)
		{
			lpCreateControl->buttonStyle = xtpButtonIconAndCaption;
			lpCreateControl->controlType = xtpControlPopup;
			return TRUE;
		}
		if (lpCreateControl->nID == ID_VIEW_OFFICE2007FRAME)
		{
			lpCreateControl->controlType = xtpControlCheckBox;
			return TRUE;
		}

		if (pToolBar->GetBarID() == IDR_SWITCH && (lpCreateControl->nID >= ID_THEME_DEFAULT && lpCreateControl->nID <= ID_THEME_RIBBON))
		{
			lpCreateControl->buttonStyle = xtpButtonCaption;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_FIND && pToolBar->GetBarID() == IDR_COMBOBOX_BAR)
		{
			CXTPControlComboBox* pComboFind = new CXTPControlComboBox(GetCommandBars());
			pComboFind->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

			//pComboFind->SetListIconId(ID_FILE_NEW);

			pComboFind->SetDropDownListStyle();
			pComboFind->SetEditHint(_T("Click to find string"));

			pComboFind->AddString(_T("Line1"));
			pComboFind->AddString(_T("Line2"));
			pComboFind->AddString(_T("Line3"));

			pComboFind->SetWidth(150);
			pComboFind->SetStyle(xtpButtonIconAndCaption);

			lpCreateControl->pControl = pComboFind;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_COMBO_MASKED)
		{
			CXTPControlComboBox* pComboMasked = (CXTPControlComboBox*)CControlComboBoxEx::CreateObject();

			//pComboMasked->GetCommandBar()->SetCommandBars(GetCommandBars()); // Require to find Site.
			//pComboMasked->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

			pComboMasked->SetDropDownListStyle();

			pComboMasked->AddString(_T("12:00:20:30"));
			pComboMasked->AddString(_T("11:03:12:30"));
			pComboMasked->AddString(_T("00:00:12:30"));
			pComboMasked->AddString(_T("10:00:30:30"));

			pComboMasked->SetWidth(130);
			pComboMasked->SetStyle(xtpComboLabel);
			pComboMasked->SetFlags(xtpFlagManualUpdate);

			lpCreateControl->pControl = pComboMasked;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_COMBO_OWNERDRAW)
		{
			CXTPControlComboBox* pComboCustomDraw = new CControlComboBoxCustomDraw(GetCommandBars());

			pComboCustomDraw->SetDropDownListStyle();
			pComboCustomDraw->SetWidth(130);
			pComboCustomDraw->SetDropDownWidth(230);
			pComboCustomDraw->SetStyle(xtpComboLabel);

			lpCreateControl->pControl = pComboCustomDraw;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_COMBO_POPUP)
		{
			CXTPControlComboBox* pComboPopup = (CXTPControlComboBox*)CControlComboBoxPopup::CreateObject();

			CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
			CMenu menu;
			menu.LoadMenu(IDR_MENU_SAVEAS);

			pPopupBar->LoadMenu(menu.GetSubMenu(0));

			pComboPopup->SetCommandBar(pPopupBar);

			pPopupBar->InternalRelease();



			pComboPopup->SetWidth(130);
			pComboPopup->SetStyle(xtpComboLabel);
			pComboPopup->SetFlags(xtpFlagManualUpdate);

			lpCreateControl->pControl = pComboPopup;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_COMBO_DATE)
		{
			CXTPControlComboBox* pCombo = new CControlComboBoxDatePicker();
			pCombo->SetWidth(100);
			lpCreateControl->pControl = pCombo;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_EDIT_STATE && pToolBar->GetBarID() == IDR_COMBOBOX_BAR)
		{
			CXTPControlComboBox* pComboState = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboState->AddString(_T("Debug"));
			pComboState->AddString(_T("Release"));
			pComboState->AddString(_T("Configuration Manager"));
			pComboState->SetDropDownWidth(150);
			lpCreateControl->pControl = pComboState;
			return TRUE;
		}

		if (lpCreateControl->nID == ID_COMBO_DISABLED && pToolBar->GetBarID() == IDR_COMBOBOX_BAR)
		{
			CXTPControlComboBox* pComboDisable = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboDisable->SetStyle(xtpComboLabel);
			lpCreateControl->pControl = pComboDisable;
			return TRUE;

		}

		if (lpCreateControl->nID == ID_BUTTONLINE && pToolBar->GetBarID() == IDR_CUSTOM)
		{
			CXTPControlPopup* pButtonLine = CXTPControlPopup::CreateControlPopup(xtpControlButtonPopup);
			pButtonLine->SetFlags(xtpFlagManualUpdate);

			CXTPPopupBar* pLineBar = (CXTPPopupBar*)CXTPPopupToolBar::CreateObject();

			pLineBar->GetControls()->Add(new CControlButtonLine(0.25), 0, _T(""), -1, FALSE);
			pLineBar->GetControls()->Add(new CControlButtonLine(0.5), 0, _T(""), -1, FALSE);
			pLineBar->GetControls()->Add(new CControlButtonLine(0.75), 0, _T(""), -1, FALSE);
			pLineBar->GetControls()->Add(new CControlButtonLine(1), 0, _T(""), -1, FALSE);
			pLineBar->GetControls()->Add(new CControlButtonLine(1.5), 0, _T(""), -1, FALSE);
			pLineBar->GetControls()->Add(new CControlButtonLine(2.25), 0, _T(""), -1, FALSE);
			pLineBar->GetControls()->Add(new CControlButtonLine(3), 0, _T(""), -1, FALSE);
			pLineBar->GetControls()->Add(new CControlButtonLine(4.5), 0, _T(""), -1, FALSE);
			pLineBar->GetControls()->Add(new CControlButtonLine(6), 0, _T(""), -1, FALSE);

			pButtonLine->SetCommandBar(pLineBar);
			pLineBar->InternalRelease();

			lpCreateControl->pControl = pButtonLine;

			return TRUE;

		}

		if (lpCreateControl->nID == ID_BUTTONSTYLE && pToolBar->GetBarID() == IDR_CUSTOM)
		{
			CXTPControlPopup* pButtonStyle = CXTPControlPopup::CreateControlPopup(xtpControlButtonPopup);
			pButtonStyle->SetFlags(xtpFlagManualUpdate);

			CXTPPopupBar* pStyleBar = (CXTPPopupBar*)CXTPPopupToolBar::CreateObject();

			pStyleBar->GetControls()->Add(new CControlButtonStyle(0), 0, _T(""), -1, FALSE);
			pStyleBar->GetControls()->Add(new CControlButtonStyle(1), 0, _T(""), -1, FALSE);
			pStyleBar->GetControls()->Add(new CControlButtonStyle(2), 0, _T(""), -1, FALSE);
			pStyleBar->GetControls()->Add(new CControlButtonStyle(3), 0, _T(""), -1, FALSE);
			pStyleBar->GetControls()->Add(new CControlButtonStyle(4), 0, _T(""), -1, FALSE);
			pStyleBar->GetControls()->Add(new CControlButtonStyle(5), 0, _T(""), -1, FALSE);

			pButtonStyle->SetCommandBar(pStyleBar);
			pStyleBar->InternalRelease();

			lpCreateControl->pControl = pButtonStyle;

			return TRUE;
		}

		if (lpCreateControl->nID == ID_BUTTONARROW && pToolBar->GetBarID() == IDR_CUSTOM)
		{
			CXTPControlPopup* pButtonArrow = CXTPControlPopup::CreateControlPopup(xtpControlButtonPopup);
			pButtonArrow->SetFlags(xtpFlagManualUpdate);

			CXTPPopupBar* pArrowBar = (CXTPPopupBar*)CXTPPopupToolBar::CreateObject();

			pArrowBar->GetControls()->Add(new CControlButtonArrow(1), 0, _T(""), -1, FALSE);
			pArrowBar->GetControls()->Add(new CControlButtonArrow(2), 0, _T(""), -1, FALSE);
			pArrowBar->GetControls()->Add(new CControlButtonArrow(3), 0, _T(""), -1, FALSE);
			pArrowBar->GetControls()->Add(new CControlButtonArrow(4), 0, _T(""), -1, FALSE);
			CXTPControlButton* pOther =
				(CXTPControlButton*)pArrowBar->GetControls()->Add(new CControlButtonArrow(0), 0, _T(""), -1, FALSE);


			pOther->SetCaption(_T("Other Arrow..."));
			pOther->SetBeginGroup(TRUE);
			pOther->SetStyle(xtpButtonCaption);

			pButtonArrow->SetCommandBar(pArrowBar);
			pArrowBar->InternalRelease();

			lpCreateControl->pControl = pButtonArrow;

			return TRUE;
		}

		if (lpCreateControl->nID == ID_BUTTON_TEXT && pToolBar->GetBarID() == IDR_CUSTOM)
		{
			CXTPControlPopupColor* pPopupColor = new CXTPControlPopupColor();

			CXTPPopupBar* pColorBar = (CXTPPopupBar*)CXTPPopupToolBar::CreateObject();

			CXTPControlButtonColor* pButtonAutomatic = (CXTPControlButtonColor*)pColorBar->GetControls()->Add(new CXTPControlButtonColor(), ID_TEXT_AUTO);
			pButtonAutomatic->SetColor(GetSysColor(COLOR_BTNTEXT));

			pColorBar->GetControls()->Add(new CXTPControlColorSelector(), ID_SELECTOR_TEXT);
			pColorBar->GetControls()->Add(new CXTPControlButtonColor(), ID_TEXT_MORE);

			pPopupColor->SetCommandBar(pColorBar);
			pColorBar->InternalRelease();

			pColorBar->SetTearOffPopup(_T("Text Color"), IDR_COLORTEXT_POPUP, 0);
			pColorBar->EnableCustomization(FALSE);

			lpCreateControl->pControl = pPopupColor;

			return TRUE;
		}

		if (lpCreateControl->nID == ID_BUTTON_BACK && pToolBar->GetBarID() == IDR_CUSTOM)
		{
			CXTPControlPopupColor* pPopupColorBack = new CXTPControlPopupColor();

			CXTPPopupBar* pColorBar = (CXTPPopupBar*)CXTPPopupToolBar::CreateObject();

			CXTPControlButtonColor* pButtonAutomatic = (CXTPControlButtonColor*)pColorBar->GetControls()->Add(new CXTPControlButtonColor(), ID_BACK_NONE);
			pButtonAutomatic->SetColor(GetSysColor(COLOR_WINDOW));

			pColorBar->GetControls()->Add(new CXTPControlColorSelector(), ID_SELECTOR_BACK);
			pColorBar->GetControls()->Add(new CXTPControlButtonColor(), ID_BACK_MORE);

			pPopupColorBack->SetCommandBar(pColorBar);
			pColorBar->InternalRelease();

			pColorBar->SetTearOffPopup(_T("Back Color"), IDR_COLORBACK_POPUP, 0);
			pColorBar->EnableCustomization(FALSE);

			lpCreateControl->pControl = pPopupColorBack;

			return TRUE;
		}
	}
	return FALSE;

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
	CXTPControlComboBox* pStateCombo = DYNAMIC_DOWNCAST(CXTPControlComboBox, CXTPControl::FromUI(pCmdUI));

	if (pStateCombo && !pStateCombo->HasFocus())
	{
		pStateCombo->SetCurSel(m_nState);
	}

	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnFileNew(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlEdit)
	{
		CString str = ((CXTPControlEdit*)pControl)->GetEditText();

		CDocument* pDocument = ((CCustomThemesApp*)AfxGetApp())->m_pDocTemplate->OpenDocumentFile(NULL);
		if (pDocument != NULL && str.GetLength() > 0)
		{
			pDocument->SetTitle(str);
		}

		*pResult = TRUE; // Handled
	}
}


BOOL CMainFrame::OnTaskPanelCaption(UINT /*nID*/, NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	CXTPControl* pControl = ((NMXTPCONTROL*)pNMHDR)->pControl;
	CXTPDialogBar* pBar = DYNAMIC_DOWNCAST(CXTPDialogBar, GetCommandBars()->GetToolBar(200));
	ASSERT(pBar);

	pBar->SetCaption(pControl->GetCaption());
	return 1;
}

void CMainFrame::OnUpdateTaskPanelCaption(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);

	CXTPDialogBar* pBar = DYNAMIC_DOWNCAST(CXTPDialogBar, GetCommandBars()->GetToolBar(200));
	ASSERT(pBar);

	CXTPControl* pControl = CXTPControl::FromUI(pCmdUI);
	if (pControl)
	{
		pCmdUI->SetCheck(pControl->GetCaption() == pBar->GetCaption()? TRUE: FALSE);
	}

}



void CMainFrame::OnTextBelow()
{
	GetCommandBars()->GetCommandBarsOptions()->bShowTextBelowIcons =
		!GetCommandBars()->GetCommandBarsOptions()->bShowTextBelowIcons;

	// or
	// GetCommandBars()->GetAt(1)->ShowTextBelowIcons(TRUE);

	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateTextBelow(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetCommandBars()->GetCommandBarsOptions()->bShowTextBelowIcons);
}


void CMainFrame::OnSaveAs(UINT nID)
{
	m_nIDSaveAs = nID;
}

void CMainFrame::OnUpdateSaveAs(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nIDSaveAs? TRUE: FALSE);
}

LRESULT CMainFrame::OnControlRButtonUp(WPARAM, LPARAM lParam)
{	
	CXTPControl* pControl = (CXTPControl*)lParam;

	UNUSED_ALWAYS(pControl);

	return FALSE;
}

void CMainFrame::OnOptionsRighttoleft() 
{
	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		GetCommandBars()->SetLayoutRTL(FALSE);
		ModifyStyleEx(WS_EX_LAYOUTRTL, 0);

	}
	else
	{
		GetCommandBars()->SetLayoutRTL(TRUE);
		ModifyStyleEx(0, WS_EX_LAYOUTRTL);
	}	
}

void CMainFrame::OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI) 
{
	if (XTPSystemVersion()->IsLayoutRTLSupported())
	{
		pCmdUI->SetCheck(GetExStyle() & WS_EX_LAYOUTRTL ? TRUE : FALSE);	
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnComboDate(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CControlComboBoxDatePicker* pControl = DYNAMIC_DOWNCAST(CControlComboBoxDatePicker, tagNMCONTROL->pControl);
	if (pControl)
	{
		m_dt = pControl->GetDate();
	}
}

void CMainFrame::OnUpdateComboDate(CCmdUI* pCmdUI)
{
	CControlComboBoxDatePicker* pControl = DYNAMIC_DOWNCAST(CControlComboBoxDatePicker, CXTPControl::FromUI(pCmdUI));

	if (pControl)
	{
		pControl->SetDate(m_dt);
	}

	pCmdUI->Enable(TRUE);
}
