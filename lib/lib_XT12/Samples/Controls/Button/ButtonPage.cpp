// ButtonDlg.cpp : implementation file
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
#include "Button.h"
#include "ButtonPage.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonPage dialog

CButtonPage::CButtonPage()
	: CXTResizePropertyPage(CButtonPage::IDD)
{
	//{{AFX_DATA_INIT(CButtonPage)
	m_nTheme = 5;
	m_bFlatStyle = FALSE;
	m_bUseVisualStyle = FALSE;
	m_bEnable = TRUE;
	m_bAlphaIcons = FALSE;
	m_bToggleButtons = FALSE;
	m_bShowFocus = TRUE;
	m_nRelation = 1;
	m_nPushButtonStyle = 0;
	m_nImageAlignment = 2;
	m_nTextAlignment = 2;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CButtonPage::DoDataExchange(CDataExchange* pDX)
{
	CXTResizePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButtonPage)
	DDX_Radio(pDX, IDC_RADIO_CLASSIC, m_nTheme);
	DDX_Check(pDX, IDC_CHECK_FLATSTYLE, m_bFlatStyle);
	DDX_Check(pDX, IDC_CHECK_WINXP_THEMES, m_bUseVisualStyle);
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_bEnable);
	DDX_Check(pDX, IDC_CHECK_ALPHA, m_bAlphaIcons);
	DDX_Check(pDX, IDC_CHECK_TOGGLE, m_bToggleButtons);
	DDX_Check(pDX, IDC_CHECK_FOCUS, m_bShowFocus);
	DDX_CBIndex(pDX, IDC_COMBO_RELATION, m_nRelation);
	DDX_CBIndex(pDX, IDC_COMBO_STYLE, m_nPushButtonStyle);
	DDX_Control(pDX, IDC_BUTTON_RUN, m_btnRun);
	DDX_Control(pDX, IDC_BUTTON_SETTINGS, m_btnSettings);
	DDX_Control(pDX, IDC_BUTTON_HELP, m_btnHelp);
	DDX_Control(pDX, IDC_BUTTON_FIND, m_btnFind);
	DDX_Control(pDX, IDC_CHECK_STATE1, m_btnState1);
	DDX_Control(pDX, IDC_CHECK_STATE2, m_btnState2);
	DDX_Control(pDX, IDC_RADIO_OPTION1, m_btnOption1);
	DDX_Control(pDX, IDC_RADIO_OPTION2, m_btnOption2);
	DDX_Control(pDX, IDC_GBOX_REGULAR, m_frmRegular);
	DDX_Control(pDX, IDC_GBOX_TWOROWS, m_frmTwoRows);
	DDX_Control(pDX, IDC_GBOX_CHECKBOXES, m_frmCheckboxes);
	DDX_Control(pDX, IDC_GBOX_RADIO, m_frmRadio);
	DDX_Control(pDX, IDC_GBOX_JUSTIFICATION, m_frmJustification);
	DDX_CBIndex(pDX, IDC_COMBO_IMAGEALIGNMENT, m_nImageAlignment);
	DDX_CBIndex(pDX, IDC_COMBO_TEXTALIGNMENT, m_nTextAlignment);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CButtonPage, CXTResizePropertyPage)
	//{{AFX_MSG_MAP(CButtonPage)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_CLASSIC, OnRadTheme)
	ON_BN_CLICKED(IDC_CHECK_FLATSTYLE, OnCheckFlatstyle)
	ON_BN_CLICKED(IDC_CHECK_WINXP_THEMES, OnCheckWinxpThemes)
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	ON_BN_CLICKED(IDC_CHECK_ALPHA, OnCheckAlpha)
	ON_BN_CLICKED(IDC_CHECK_TOGGLE, OnCheckToggle)
	ON_BN_CLICKED(IDC_CHECK_FOCUS, OnCheckFocus)
	ON_CBN_SELCHANGE(IDC_COMBO_RELATION, OnSelchangeComboRelation)
	ON_CBN_SELCHANGE(IDC_COMBO_STYLE, OnSelchangeComboStyle)
	ON_BN_CLICKED(IDC_RADIO_FLAT, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2000, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2007, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICEXP, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_ULTRAFLAT, OnRadTheme)
	ON_CBN_SELCHANGE(IDC_COMBO_IMAGEALIGNMENT, OnSelchangeComboImagealignment)
	ON_CBN_SELCHANGE(IDC_COMBO_TEXTALIGNMENT, OnSelchangeComboTextalignment)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_SETTINGS, IDC_BUTTON_RUN, OnButtonClicked)
	ON_CONTROL_RANGE(CBN_DROPDOWN, IDC_BUTTON_SETTINGS, IDC_BUTTON_RUN, OnButtonDropDown)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonPage message handlers

BOOL CButtonPage::OnInitDialog()
{
	CXTResizePropertyPage::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	/*
	// Set control resizing.



	// Load window placement
	LoadPlacement(_T("CButtonPage"));

	//------------------------------------
	// TODO: Add extra initialization here
	//------------------------------------

	m_bitmap.LoadBitmap(IDB_IMAGELIST);
	m_imageList.Create(24, 24, ILC_COLOR24|ILC_MASK, 4, 1);
	m_imageList.Add(&m_bitmap, RGB(0,255,0));

	UpdateIcons(FALSE);

	m_btnOK.SetTheme(xtThemeDefault);
	m_btnOK.SetBitmap(CSize(16, 16), IDB_OK);
	m_btnOK.SetXButtonStyle(BS_XT_WINXP_COMPAT);

	OnRadOffice2003();
	UpdateXTStyle();*/

	m_frmCheckboxes.SetBorderStyle(xtpGroupBoxSingleLine);
	m_frmRadio.SetBorderStyle(xtpGroupBoxSingleLine);
	m_frmJustification.SetBorderStyle(xtpGroupBoxSingleLine);

	int i;
	for (i = IDC_GBOX_REGULAR; i <= IDC_COMBO_STYLE; i++)
		SetResize(i, SZ_TOP_LEFT, CXTResizePoint((float)(1.0/3.0), 0));

	for (i = IDC_GBOX_CHECKBOXES; i <= IDC_COMBO_RELATION; i++)
		SetResize(i, CXTResizePoint((float)(1.0/3.0), 0), CXTResizePoint((float)(2.0/3.0), 0));


	for (i = IDC_GBOX_THEME; i <= IDC_CHECK_ALPHA; i++)
		SetResize(i, CXTResizePoint((float)(2.0/3.0), 0), SZ_TOP_RIGHT);

	m_bitmap.LoadBitmap(IDB_IMAGELIST);
	m_imageList.Create(24, 24, ILC_COLOR24|ILC_MASK, 4, 1);
	m_imageList.Add(&m_bitmap, RGB(0,255,0));

	UpdateIcons(FALSE);


	OnRadTheme();
	OnCheckWinxpThemes();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CButtonPage::OnDestroy()
{
	// Save window placement
	SavePlacement(_T("CButtonPage"));

	CXTResizePropertyPage::OnDestroy();
}

void CButtonPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CXTResizePropertyPage::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CButtonPage::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CXTResizePropertyPage::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CButtonPage::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CButtonPage::OnRadTheme() 
{
	UpdateData();

	m_btnRun.SetTheme((XTPButtonTheme)m_nTheme);
	m_btnFind.SetTheme((XTPButtonTheme)m_nTheme);
	m_btnSettings.SetTheme((XTPButtonTheme)m_nTheme);
	m_btnHelp.SetTheme((XTPButtonTheme)m_nTheme);

	m_btnState1.SetTheme((XTPButtonTheme)m_nTheme);
	m_btnState2.SetTheme((XTPButtonTheme)m_nTheme);
	m_btnOption1.SetTheme((XTPButtonTheme)m_nTheme);
	m_btnOption2.SetTheme((XTPButtonTheme)m_nTheme);

	m_frmRegular.SetTheme((XTPButtonTheme)m_nTheme);
	m_frmTwoRows.SetTheme((XTPButtonTheme)m_nTheme);
	m_frmCheckboxes.SetTheme((XTPButtonTheme)m_nTheme);
	m_frmRadio.SetTheme((XTPButtonTheme)m_nTheme);
	m_frmJustification.SetTheme((XTPButtonTheme)m_nTheme);
}

void CButtonPage::UpdateIcons(BOOL bAlpha)
{
	if (!bAlpha)
	{
		HICON hIcon = m_imageList.ExtractIcon(0);
		m_btnSettings.SetIcon(CSize(24,24), hIcon);
		DestroyIcon(hIcon);

		hIcon = m_imageList.ExtractIcon(1); 
		HICON hIconHot = m_imageList.ExtractIcon(2);
		m_btnFind.SetIcon(CSize(24,24), hIcon, hIconHot);
		DestroyIcon(hIcon); DestroyIcon(hIconHot);

		hIcon = m_imageList.ExtractIcon(3); 
		m_btnHelp.SetIcon(CSize(24,24), hIcon);
		DestroyIcon(hIcon);

		hIcon = m_imageList.ExtractIcon(4); 
		m_btnRun.SetIcon(CSize(24,24),hIcon);
		DestroyIcon(hIcon);
	} 
	else
	{
		m_btnSettings.SetBitmap(0, IDB_ALPHA_SETTINGS);
		m_btnFind.SetBitmap(0, IDB_ALPHA_FIND);
		m_btnHelp.SetBitmap(0, IDB_ALPHA_HELP);
		m_btnRun.SetBitmap(0, IDB_ALPHA_RUN);
	}
}

void CButtonPage::OnCheckFlatstyle() 
{
	UpdateData();
	
	m_btnSettings.SetFlatStyle(m_bFlatStyle);	
	m_btnFind.SetFlatStyle(m_bFlatStyle);	
	m_btnHelp.SetFlatStyle(m_bFlatStyle);	
	m_btnRun.SetFlatStyle(m_bFlatStyle);	
}

void CButtonPage::OnCheckWinxpThemes() 
{
	UpdateData();

	m_btnSettings.SetUseVisualStyle(m_bUseVisualStyle);	
	m_btnFind.SetUseVisualStyle(m_bUseVisualStyle);	
	m_btnHelp.SetUseVisualStyle(m_bUseVisualStyle);	
	m_btnRun.SetUseVisualStyle(m_bUseVisualStyle);		

	m_btnState1.SetUseVisualStyle(m_bUseVisualStyle);		
	m_btnState2.SetUseVisualStyle(m_bUseVisualStyle);		
	m_btnOption1.SetUseVisualStyle(m_bUseVisualStyle);		
	m_btnOption2.SetUseVisualStyle(m_bUseVisualStyle);		

	m_frmRegular.SetUseVisualStyle(m_bUseVisualStyle);		
	m_frmTwoRows.SetUseVisualStyle(m_bUseVisualStyle);		
	m_frmCheckboxes.SetUseVisualStyle(m_bUseVisualStyle);		
	m_frmRadio.SetUseVisualStyle(m_bUseVisualStyle);		
	
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_ERASE);
}

void CButtonPage::OnCheckEnabled() 
{
	UpdateData();

	m_btnSettings.EnableWindow(m_bEnable);
	m_btnFind.EnableWindow(m_bEnable);
	m_btnHelp.EnableWindow(m_bEnable);
	m_btnRun.EnableWindow(m_bEnable);
	
	m_btnState1.EnableWindow(m_bEnable);	
	m_btnState2.EnableWindow(m_bEnable);		
	m_btnOption1.EnableWindow(m_bEnable);
	m_btnOption2.EnableWindow(m_bEnable);
}

void CButtonPage::OnCheckAlpha() 
{
	UpdateData();
	UpdateIcons(m_bAlphaIcons);	
}

void CButtonPage::OnCheckToggle() 
{
	UpdateData();

	if (!m_bToggleButtons)
	{
		m_btnSettings.SetChecked(FALSE);
		m_btnFind.SetChecked(FALSE);
		m_btnHelp.SetChecked(FALSE);
		m_btnRun.SetChecked(FALSE);
	}
}


void CButtonPage::OnButtonClicked(UINT nID)
{
	CXTPButton* pButton = DYNAMIC_DOWNCAST(CXTPButton, GetDlgItem(nID));
	ASSERT(pButton);

	if (m_bToggleButtons)
	{
		pButton->SetChecked(!pButton->GetChecked());
	}
}

void CButtonPage::OnButtonDropDown(UINT nID)
{
	// loading a user resource.
	CMenu menu;
	menu.LoadMenu(IDR_MENU_DROPDOWN);

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CXTPButton* pButton = DYNAMIC_DOWNCAST(CXTPButton, GetDlgItem(nID));
	ASSERT(pButton);

	DWORD dwStyle = pButton->GetPushButtonStyle();
	ASSERT(pButton->IsDropDownStyle());

	CXTPWindowRect rect(pButton);

	int nCmd = TrackPopupMenu(pPopup->GetSafeHmenu(), TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL |TPM_RETURNCMD,
		dwStyle == xtpButtonDropDownRight ? rect.right : rect.left, dwStyle == xtpButtonDropDownRight ? rect.top : rect.bottom, 0, m_hWnd, 0);

	if (nCmd > 0)
	{
	}


}

void CButtonPage::OnCheckFocus() 
{
	UpdateData();

	m_btnSettings.SetShowFocus(m_bShowFocus);
	m_btnFind.SetShowFocus(m_bShowFocus);
	m_btnHelp.SetShowFocus(m_bShowFocus);
	m_btnRun.SetShowFocus(m_bShowFocus);
	
	m_btnState1.SetShowFocus(m_bShowFocus);
	m_btnState2.SetShowFocus(m_bShowFocus);		
	m_btnOption1.SetShowFocus(m_bShowFocus);
	m_btnOption2.SetShowFocus(m_bShowFocus);
	
}

void CButtonPage::OnSelchangeComboRelation() 
{
	UpdateData();

	m_btnHelp.SetTextImageRelation((XTPButtonTextImageRelation)m_nRelation);
	m_btnRun.SetTextImageRelation((XTPButtonTextImageRelation)m_nRelation);

	if (m_nRelation != xtpButtonTextAboveImage && m_nRelation != xtpButtonImageAboveText)
	{
		m_btnSettings.SetTextImageRelation((XTPButtonTextImageRelation)m_nRelation);
		m_btnFind.SetTextImageRelation((XTPButtonTextImageRelation)m_nRelation);
	}	
}

void CButtonPage::OnSelchangeComboStyle() 
{
	UpdateData();	

	m_btnHelp.SetPushButtonStyle((XTPPushButtonStyle)m_nPushButtonStyle);
	m_btnRun.SetPushButtonStyle((XTPPushButtonStyle)m_nPushButtonStyle);
	m_btnSettings.SetPushButtonStyle((XTPPushButtonStyle)m_nPushButtonStyle);
	m_btnFind.SetPushButtonStyle((XTPPushButtonStyle)m_nPushButtonStyle);
}

void CButtonPage::OnSelchangeComboTextalignment() 
{
	UpdateData();	

	int nVert = m_nTextAlignment >= 6 ? BS_BOTTOM : m_nTextAlignment >= 3 ? BS_TOP : BS_VCENTER;
	int nHorz = m_nTextAlignment % 3 == 0 ? BS_LEFT : m_nTextAlignment % 3 == 1 ? BS_RIGHT : BS_CENTER;

	m_btnRun.SetTextAlignment(nVert | nHorz);
	m_btnHelp.SetTextAlignment(nVert | nHorz);
	m_btnSettings.SetTextAlignment(nVert | nHorz);
	m_btnFind.SetTextAlignment(nVert | nHorz);
}

void CButtonPage::OnSelchangeComboImagealignment() 
{
	UpdateData();	

	int nVert = m_nImageAlignment >= 6 ? BS_BOTTOM : m_nImageAlignment >= 3 ? BS_TOP : BS_VCENTER;
	int nHorz = m_nImageAlignment % 3 == 0 ? BS_LEFT : m_nImageAlignment % 3 == 1 ? BS_RIGHT : BS_CENTER;
	
	m_btnRun.SetImageAlignment(nVert | nHorz);
	m_btnHelp.SetImageAlignment(nVert | nHorz);
	m_btnSettings.SetImageAlignment(nVert | nHorz);
	m_btnFind.SetImageAlignment(nVert | nHorz);
	
}
