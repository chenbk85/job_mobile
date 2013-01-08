// PopupControlDemoDlg.cpp : implementation file
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
#include "PopupControlDemo.h"
#include "PopupControlDemoDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_POPUP_CLOSE (-1)
#define ID_GOTO_SITE (-2)


/////////////////////////////////////////////////////////////////////////////
// CPopupControlDemoDlg dialog

CPopupControlDemoDlg::CPopupControlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPopupControlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPopupControlDemoDlg)
	m_nTheme = 2;
	m_nAnimation = 1;
	m_uAnimDelay = 500;
	m_uShowDelay = 3000;
	m_bAllowMove = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pActivePopup = NULL;
	m_ptPopup = CPoint(-1, -1);
}

CPopupControlDemoDlg::~CPopupControlDemoDlg()
{
	while (!m_lstPopupControl.IsEmpty()) 
	{
		delete m_lstPopupControl.RemoveTail();
	}
}

void CPopupControlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopupControlDemoDlg)
	DDX_Control(pDX, IDC_BUTTON_MORE, m_btnMore);
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENT, m_Slider);
	DDX_CBIndex(pDX, IDC_COMBO_THEME, m_nTheme);
	DDX_CBIndex(pDX, IDC_COMBO_ANIMATION, m_nAnimation);
	DDX_Text(pDX, IDC_EDIT_ANIMATIONDELAY, m_uAnimDelay);
	DDV_MinMaxUInt(pDX, m_uAnimDelay, 0, 60000);
	DDX_Text(pDX, IDC_EDIT_SHOWDELAY, m_uShowDelay);
	DDV_MinMaxUInt(pDX, m_uShowDelay, 0, 600000);
	DDX_Check(pDX, IDC_CHECK_ALLOWMOVE, m_bAllowMove);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPopupControlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CPopupControlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHOW, OnButtonShow)
	ON_CBN_SELCHANGE(IDC_COMBO_THEME, OnSelchangeComboTheme)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TRANSPARENT, OnReleasedcaptureSliderTransparent)
	ON_CBN_SELCHANGE(IDC_COMBO_ANIMATION, OnSelchangeComboAnimation)
	ON_EN_CHANGE(IDC_EDIT_ANIMATIONDELAY, OnChangeEditAnimationdelay)
	ON_EN_CHANGE(IDC_EDIT_SHOWDELAY, OnChangeEditShowdelay)
	ON_BN_CLICKED(IDC_CHECK_ALLOWMOVE, OnCheckAllowMove)
	ON_COMMAND(ID_MORE_RTFSAMPLE, OnMoreRtfsample)
	ON_COMMAND(ID_MORE_MARKUPSAMPLE, OnMoreMarkupsample)
	ON_COMMAND(ID_MORE_LAYERSAMPLE, OnMoreLayerSample)
	//}}AFX_MSG_MAP
	ON_CBN_DROPDOWN(IDC_BUTTON_MORE, OnMoreDropDown)

	ON_MESSAGE(XTPWM_POPUPCONTROL_NOTIFY, OnPopUpNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupControlDemoDlg message handlers

BOOL CPopupControlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	m_btnMore.SetPushButtonStyle(xtpButtonDropDown);
	//
	m_Slider.SetRange(0, 255, TRUE);
	m_Slider.SetPos(200);

	OnSelchangeComboTheme();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPopupControlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPopupControlDemoDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPopupControlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPopupControlDemoDlg::FindBestPosition(CSize szPopup)
{
	if (m_ptPopup != CPoint(-1, -1)) 
		m_pActivePopup->SetPopupPos(m_ptPopup);

	CPoint ptPopup = m_pActivePopup->GetPopupPos();

	CRect rcActivePopup(CPoint(ptPopup.x - szPopup.cx, ptPopup.y - szPopup.cy), szPopup);

	
	BOOL bIntersect = FALSE;
	do 
	{
		bIntersect = FALSE;
		POSITION pos = m_lstPopupControl.GetHeadPosition();

		while(pos)
		{
			CXTPPopupControl* pPopup = m_lstPopupControl.GetNext(pos);
			
			CRect rcPopup(CPoint(pPopup->GetPopupPos().x - pPopup->GetPopupSize().cx, 
				pPopup->GetPopupPos().y - pPopup->GetPopupSize().cy), pPopup->GetPopupSize());
			
			if (CRect().IntersectRect(rcPopup, rcActivePopup))
			{
				ptPopup.y =  rcPopup.top;
				rcActivePopup = CRect(CPoint(ptPopup.x - szPopup.cx, ptPopup.y - szPopup.cy), szPopup);
				bIntersect = TRUE;
			}
		}
	} while (bIntersect);

	m_pActivePopup->SetPopupPos(ptPopup);
}


void CPopupControlDemoDlg::OnButtonShow()
{
	m_pActivePopup = new CXTPPopupControl();

	UpdateData();

	CSize szPopup (170, 130);

	if (m_nTheme == xtpPopupThemeOffice2003 || m_nTheme == xtpPopupThemeOffice2007)
		szPopup = CSize(329, 74);
	if (m_nTheme == 9)
		szPopup = CSize(220, 90);

	SetTheme();

	m_pActivePopup->SetPopupAnimation((XTPPopupAnimation)m_nAnimation);
	m_pActivePopup->SetShowDelay(m_uShowDelay);
	m_pActivePopup->SetAnimateDelay(m_uAnimDelay);
	m_pActivePopup->SetTransparency((BYTE)m_Slider.GetPos());
	m_pActivePopup->SetPopupSize(szPopup);
	
	FindBestPosition(szPopup);

	m_pActivePopup->AllowMove(m_bAllowMove);


	m_pActivePopup->Show(this);

	m_lstPopupControl.AddTail(m_pActivePopup);
	EnableItems(FALSE);
}

void CPopupControlDemoDlg::EnableItems(BOOL bEnable)
{
	CWnd* pWnd = GetWindow(GW_CHILD);
	while (pWnd)
	{
		pWnd->EnableWindow(bEnable);
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}

	GetDlgItem(IDC_BUTTON_SHOW)->EnableWindow(TRUE);
}

void CPopupControlDemoDlg::SetDefaults()
{
	switch (m_nTheme)
	{
		case xtpPopupThemeOffice2000:
		case xtpPopupThemeOfficeXP:
			{
				m_nAnimation = 1;
				m_uAnimDelay = 500;
				m_uShowDelay = 3000;
				m_Slider.SetPos(255);
			}
			break;
		case xtpPopupThemeOffice2003:
		case xtpPopupThemeOffice2007:
			{
				m_nAnimation = 1;
				m_uAnimDelay = 500;
				m_uShowDelay = 3000;
				m_Slider.SetPos(200);
			}
			break;
		case xtpPopupThemeMSN:
		case 5:
		case 6:
		case 7:
		case 8:
			{
				m_nAnimation = 2;
				m_uAnimDelay = 350;
				m_uShowDelay = 3000;
				m_Slider.SetPos(255);
			}
			break;
		case 9:
			{
				m_nAnimation = 3;
				m_uAnimDelay = 500;
				m_uShowDelay = 3000;
				m_Slider.SetPos(255);
			}
			break;
	}

	UpdateData(FALSE);
}

void CPopupControlDemoDlg::SetDefaultTheme()
{
	m_pActivePopup->RemoveAllItems();

	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(25, 5, 170, 19), _T("Word 2000 Theme")));
	pItemText->SetTextAlignment(DT_LEFT);
	pItemText->CalculateHeight();
	pItemText->CalculateWidth();
	pItemText->SetHyperLink(FALSE);
	pItemText->SetTextColor(RGB(255,255,255));

	CXTPPopupItem * pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(4, 4, 20, 19)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_WORD2000), IMAGE_ICON, 16, 16, 0),xtpPopupItemIconNormal);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(14, 40, 20, 49)));
	pItemIcon->SetIcons(IDB_LOGOOFFICE, 0, xtpPopupItemIconNormal);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(109, 55, 132, 78)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_OPEN), IMAGE_ICON, 16, 16, 0),xtpPopupItemIconNormal);
	pItemIcon->CenterIcon();
	pItemIcon->SetButton(TRUE);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(133, 55, 156, 78)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_SAVE), IMAGE_ICON, 16, 16, 0),xtpPopupItemIconNormal);
	pItemIcon->CenterIcon();
	pItemIcon->SetButton(TRUE);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(151, 6, 164, 19)));
	pItemIcon->SetIcons(IDB_CLOSEOFFICE, 0,
		xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(104, 30, 170, 45), _T("Parameters")));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(65, 90, 105, 110), _T("OK")));
	pItemText->SetButton(TRUE);
	pItemText->SetTextAlignment(DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pItemText->SetHyperLink(FALSE);
	pItemText->SetID(IDOK);

	m_pActivePopup->SetTheme(xtpPopupThemeOffice2000);
	m_pActivePopup->RedrawControl();
}

void CPopupControlDemoDlg::SetOfficeXPTheme()
{
	m_pActivePopup->RemoveAllItems();

	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(25, 5, 170, 19), _T("Word XP Theme")));
	pItemText->SetTextAlignment(DT_LEFT);
	pItemText->CalculateHeight();
	pItemText->CalculateWidth();
	pItemText->SetHyperLink(FALSE);
	pItemText->SetTextColor(RGB(255,255,255));

	CXTPPopupItem * pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(4, 4, 20, 19)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_WORD2000), IMAGE_ICON, 16, 16, 0),xtpPopupItemIconNormal);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(14, 40, 20, 49)));
	pItemIcon->SetIcons(IDB_LOGOOFFICE, 0, xtpPopupItemIconNormal);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(109, 55, 132, 78)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_OPEN), IMAGE_ICON, 16, 16, 0),xtpPopupItemIconNormal);
	pItemIcon->CenterIcon();
	pItemIcon->SetButton(TRUE);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(133, 55, 156, 78)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_SAVE), IMAGE_ICON, 16, 16, 0),xtpPopupItemIconNormal);
	pItemIcon->CenterIcon();
	pItemIcon->SetButton(TRUE);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(151, 6, 164, 19)));
	pItemIcon->SetIcons(IDB_CLOSEOFFICE, 0,
		xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(104, 30, 170, 45), _T("Parameters")));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(65, 90, 105, 110), _T("OK")));
	pItemText->SetButton(TRUE);
	pItemText->SetTextAlignment(DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pItemText->SetHyperLink(FALSE);
	pItemText->SetID(IDOK);

	m_pActivePopup->SetTheme(xtpPopupThemeOfficeXP);
	m_pActivePopup->RedrawControl();

}

void CPopupControlDemoDlg::SetMSNTheme()
{
	m_pActivePopup->RemoveAllItems();

	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(25, 6, 170, 19), _T("PopupControlDemo")));
	pItemText->SetTextAlignment(DT_LEFT);
	pItemText->CalculateHeight();
	pItemText->CalculateWidth();
	pItemText->SetHyperLink(FALSE);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(104, 27, 160, 45), _T("Options")));
	pItemText->SetTextAlignment(DT_RIGHT);
	pItemText->CalculateHeight();
	pItemText->CalculateWidth();

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(0, 50, 170, 100), _T("Please visit our website for additional product information including registration details.")));
	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->CalculateHeight();
	pItemText->SetID(ID_GOTO_SITE);

	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(151, 6, 164, 19)));
	pItemIcon->SetIcons(IDB_CLOSEMSN, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(7, 6, 20, 19)));
	pItemIcon->SetIcons(IDB_CAPTIONMSN, 0, xtpPopupItemIconNormal);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(115, 102, 160, 120)));
	pItemIcon->SetIcons(IDB_LOGOMSN, 0, xtpPopupItemIconNormal);

	m_pActivePopup->SetTheme(xtpPopupThemeMSN);
	m_pActivePopup->RedrawControl();
}

void CPopupControlDemoDlg::SetOffice2003Theme()
{
	m_pActivePopup->RemoveAllItems();

	// add text items.
	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(46, 16, 270, 41), _T("Peter Parker")));
	pItemText->SetBold(TRUE);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(46, 29, 270, 54), _T("RE: Week reports 12/04/2004 - 17/04/2004")));
	pItemText->SetHyperLink(FALSE);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(46, 42, 270, 92), _T("See comments below.\nThanks.")));
	pItemText->SetHyperLink(FALSE);

	pItemText->SetTextColor(RGB(0, 61, 178));
	pItemText->SetTextAlignment(DT_LEFT|DT_WORDBREAK);

	// letter icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(5, 12, 17, 24)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_LETTER), IMAGE_ICON, 32, 32, 0));
	pItemIcon->SetButton(FALSE);

	// close icon.
	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(308, 14, 324, 30)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CLOSE), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	// flag icon.
	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(4, 49, 20, 65)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_FLAG), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);

	// cross icon.
	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(23, 49, 39, 65)));
	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_CROSS), IMAGE_ICON, 16, 16, 0));
	pItemIcon->SetButton(TRUE);

	m_pActivePopup->SetTheme(xtpPopupThemeOffice2003);
	m_pActivePopup->RedrawControl();
}

void CPopupControlDemoDlg::SetOffice2007Theme()
{
	SetOffice2003Theme();

	m_pActivePopup->SetTheme(xtpPopupThemeOffice2007);
	m_pActivePopup->RedrawControl();
}

void CPopupControlDemoDlg::SetBlueTheme()
{
	m_pActivePopup->RemoveAllItems();

	m_pActivePopup->AddItem(new CXTPPopupItem(
		CRect(0, 0, 170, 130), NULL,  RGB(50,50,255), RGB(255,255,255)));
	m_pActivePopup->AddItem(new CXTPPopupItem(
		CRect(5, 25, 170 - 5, 130 - 5), NULL, RGB(70,70,250), RGB(200,200,200)));

	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(104, 27, 170, 45), _T("more...")));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(0, 70, 170, 100), _T("Please visit our website for additional product information including registration details.")));
	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->SetTextColor(RGB(255,255,255));
	pItemText->CalculateHeight();
	pItemText->SetID(ID_GOTO_SITE);

	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(12, 30, 12, 47)));

	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_LETTER2), IMAGE_ICON, 32, 32, 0));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(5, 0, 170, 25), _T("Message for You")));
	pItemText->SetTextAlignment(DT_LEFT|DT_SINGLELINE| DT_VCENTER);
	pItemText->SetTextColor(RGB(255, 255, 255));
	pItemText->SetBold(TRUE);
	pItemText->SetHyperLink(FALSE);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(151, 6, 164, 19)));
	pItemIcon->SetIcons(IDB_CLOSEMSN, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	m_pActivePopup->SetTheme(new CXTPPopupPaintManager());
	m_pActivePopup->RedrawControl();
}

void CPopupControlDemoDlg::SetBlackTheme()
{
	m_pActivePopup->RemoveAllItems();

	m_pActivePopup->AddItem(new CXTPPopupItem(
		CRect(0, 0, 170, 130), NULL, RGB(10,10,10), RGB(255,255,255)));
	m_pActivePopup->AddItem(new CXTPPopupItem(
		CRect(5, 25, 170 - 5, 130 - 5), NULL, RGB(70,70,70), RGB(200,200,200)));

	CXTPPopupItem* pItemText = (CXTPPopupItem*)
		m_pActivePopup->AddItem(new CXTPPopupItem(CRect(104, 27, 170, 45),
		_T("more...")));
	pItemText->SetTextColor(RGB(150,150,150));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(0, 70, 170, 100), _T("Please visit our website for additional product information including registration details.")));
	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->SetTextColor(RGB(255,255,255));
	pItemText->CalculateHeight();
	pItemText->SetID(ID_GOTO_SITE);

	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(12, 30, 12, 47)));

	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_LETTER2), IMAGE_ICON, 32, 32, 0));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(5, 0, 170, 25), _T("Message for You")));
	pItemText->SetTextAlignment(DT_LEFT|DT_SINGLELINE| DT_VCENTER);
	pItemText->SetTextColor(RGB(255, 255, 255));
	pItemText->SetBold(TRUE);
	pItemText->SetHyperLink(FALSE);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(151, 6, 164, 19)));
	pItemIcon->SetIcons(IDB_CLOSEMSN, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	m_pActivePopup->SetTheme(new CXTPPopupPaintManager());
	m_pActivePopup->RedrawControl();
}

void CPopupControlDemoDlg::SetGreenTheme()
{
	m_pActivePopup->RemoveAllItems();

	m_pActivePopup->AddItem(new CXTPPopupItem(
		CRect(0, 0, 170, 130), NULL, RGB(30,120,30), RGB(255,255,0)));
	m_pActivePopup->AddItem(new CXTPPopupItem(
		CRect(5, 25, 170 - 5, 130 - 5), NULL, RGB(70,130,70), RGB(255,255,0)));

	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(104, 27, 170, 45), _T("more...")));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(0, 70, 170, 100), _T("Please visit our website for additional product information including registration details.")));
	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->SetTextColor(RGB(255,255,0));
	pItemText->CalculateHeight();
	pItemText->SetID(ID_GOTO_SITE);

	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(12, 30, 12, 47)));

	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_LETTER2), IMAGE_ICON, 32, 32, 0));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(5, 0, 170, 25), _T("Message for You")));
	pItemText->SetTextAlignment(DT_LEFT|DT_SINGLELINE| DT_VCENTER);
	pItemText->SetTextColor(RGB(255, 255, 255));
	pItemText->SetBold(TRUE);
	pItemText->SetHyperLink(FALSE);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(151, 6, 164, 19)));
	pItemIcon->SetIcons(IDB_CLOSEMSN, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	m_pActivePopup->SetTheme(new CXTPPopupPaintManager());
	m_pActivePopup->RedrawControl();
}

void CPopupControlDemoDlg::SetRedTheme()
{
	m_pActivePopup->RemoveAllItems();

	m_pActivePopup->AddItem(new CXTPPopupItem(
		CRect(0, 0, 170, 130), NULL, RGB(255,50,50), RGB(255,255,0)));
	m_pActivePopup->AddItem(new CXTPPopupItem(
		CRect(5, 25, 170 - 5, 130 - 5), NULL, RGB(230,70,70), RGB(255,255,0)));

	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(104, 27, 170, 45), _T("more...")));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(0, 70, 170, 100), _T("Please visit our website for additional product information including registration details.")));
	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->SetTextColor(RGB(255,255,0));
	pItemText->CalculateHeight();
	pItemText->SetID(ID_GOTO_SITE);

	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(12, 30, 12, 47)));

	pItemIcon->SetIcon((HICON)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_LETTER2), IMAGE_ICON, 32, 32, 0));

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(5, 0, 170, 25), _T("Message for You")));
	pItemText->SetTextAlignment(DT_LEFT|DT_SINGLELINE| DT_VCENTER);
	pItemText->SetTextColor(RGB(255, 255, 255));
	pItemText->SetBold(TRUE);
	pItemText->SetHyperLink(FALSE);

	pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(151, 6, 164, 19)));
	pItemIcon->SetIcons(IDB_CLOSEMSN, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	m_pActivePopup->SetTheme(new CXTPPopupPaintManager());
	m_pActivePopup->RedrawControl();
}

void CPopupControlDemoDlg::SetTooltipTheme()
{
	m_pActivePopup->RemoveAllItems();

	m_pActivePopup->AddItem(new CXTPPopupItem(
		CRect(0, 0, 220, 90), NULL, RGB(255,255,225), 0));

	CXTPPopupItem* pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(20, 30, 200, 100), _T("Please visit our website for additional product information including registration details.")));
	pItemText->SetTextAlignment(DT_CENTER|DT_WORDBREAK);
	pItemText->SetID(ID_GOTO_SITE);

	pItemText = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(5, 0, 170, 25), _T("Codejock Information")));
	pItemText->SetTextAlignment(DT_LEFT|DT_SINGLELINE| DT_VCENTER);
	pItemText->SetBold(TRUE);
	pItemText->SetHyperLink(FALSE);

	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)m_pActivePopup->AddItem(
		new CXTPPopupItem(CRect(220 - 20, 2, 220 - 2, 2 + 18)));
	pItemIcon->SetIcons(IDB_CLOSETOOLTIP, 0, xtpPopupItemIconNormal|xtpPopupItemIconSelected|xtpPopupItemIconPressed);
	pItemIcon->SetID(ID_POPUP_CLOSE);

	m_pActivePopup->SetTheme(new CXTPPopupPaintManager());
	m_pActivePopup->RedrawControl();
}

void CPopupControlDemoDlg::SetTheme()
{
	switch (m_nTheme)
	{
	case xtpPopupThemeOffice2000:
		SetDefaultTheme();
		break;
	case xtpPopupThemeOfficeXP:
		SetOfficeXPTheme();
		break;
	case xtpPopupThemeOffice2003:
		SetOffice2003Theme();
		break;
	case xtpPopupThemeOffice2007:
		SetOffice2007Theme();
		break;
	case xtpPopupThemeMSN:
		SetMSNTheme();
		break;
	case 5:
		SetBlueTheme();
		break;
	case 6:
		SetBlackTheme();
		break;
	case 7:
		SetGreenTheme();
		break;
	case 8:
		SetRedTheme();
		break;
	case 9:
		SetTooltipTheme();
		break;
	}
}

void CPopupControlDemoDlg::OnCheckAllowMove()
{
	UpdateData();
}

void CPopupControlDemoDlg::OnSelchangeComboTheme()
{
	UpdateData();

	SetDefaults();
}

void CPopupControlDemoDlg::OnReleasedcaptureSliderTransparent(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	*pResult = 0;
}

void CPopupControlDemoDlg::OnSelchangeComboAnimation()
{
	UpdateData();
}

void CPopupControlDemoDlg::OnChangeEditAnimationdelay()
{
	UpdateData();
}

void CPopupControlDemoDlg::OnChangeEditShowdelay()
{
	UpdateData();
}

void CPopupControlDemoDlg::OnMoreDropDown()
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_MORE));

	CXTPWindowRect rc(GetDlgItem(IDC_BUTTON_MORE));

	TrackPopupMenu(menu.GetSubMenu(0)->GetSafeHmenu(), 0, rc.left, rc.bottom, 0, m_hWnd, 0);
}

LRESULT CPopupControlDemoDlg::OnPopUpNotify(WPARAM wParam, LPARAM lParam)
{
	// process notify from popup wnd

	if(wParam == XTP_PCN_ITEMCLICK)
	{
		CXTPPopupItem* pItem = (CXTPPopupItem*)lParam;
		ASSERT(pItem);

		if(pItem->GetID() == ID_GOTO_SITE)
		{
			::ShellExecute(NULL, _T("open"), _T("http://www.codejock.com/"), NULL, NULL, SW_SHOW);
		}

		pItem->GetPopupControl()->Close();
	}
	else if(wParam == XTP_PCN_STATECHANGED)
	{
		CXTPPopupControl* pControl = (CXTPPopupControl*)lParam;
		ASSERT(pControl);

		if(pControl->GetPopupState() == xtpPopupStateClosed)
		{
			m_lstPopupControl.RemoveAt(m_lstPopupControl.Find(pControl));
			m_pActivePopup = NULL;

			if (m_lstPopupControl.IsEmpty())
			{
				EnableItems(TRUE);				
			}
			
			delete pControl;
		}
	}
	else if (wParam == XTP_PCN_POSCHANGED)
	{
		CXTPPopupControl* pControl = (CXTPPopupControl*)lParam;
		ASSERT(pControl);
		
		m_ptPopup = pControl->GetPopupPos();
	}
		
	return TRUE;
}

void CPopupControlDemoDlg::OnMoreRtfsample() 
{
	CXTPPopupControl* pPopup = new CXTPPopupControl();
	pPopup->SetTransparency(200);
	pPopup->SetTheme(xtpPopupThemeOffice2003);
	pPopup->AllowMove(TRUE);
	pPopup->SetAnimateDelay(500);
	pPopup->SetPopupAnimation();
	pPopup->SetShowDelay(5000);
	
	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(new CXTPPopupItem(CRect(8, 12, 500, 130)));
	pItemText->SetRTFText(IDR_MAINFRAME);
	pItemText->FitToContent();
	CSize sz(pItemText->GetRect().Size());

	// close icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(sz.cx + 2, 10, sz.cx + 2 + 16, 10 + 16)));
	
	pPopup->GetImageManager()->SetIcon(IDI_POPUP_CLOSE, IDI_POPUP_CLOSE);
	pItemIcon->SetIconIndex(IDI_POPUP_CLOSE);

	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(XTP_ID_POPUP_CLOSE);

	pPopup->SetPopupSize(CSize(sz.cx + 20, sz.cy + 20));
	pPopup->Show(this);

	m_lstPopupControl.AddTail(pPopup);
}

void CPopupControlDemoDlg::OnMoreMarkupsample() 
{
	CXTPPopupControl* pPopup = new CXTPPopupControl();
	pPopup->SetTransparency(200);
	pPopup->SetTheme(xtpPopupThemeOffice2003);
	pPopup->AllowMove(TRUE);
	pPopup->SetAnimateDelay(500);
	pPopup->SetPopupAnimation();
	pPopup->SetShowDelay(5000);
	
	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(new CXTPPopupItem(CRect(8, 12, 500, 130)));

	LPCTSTR lpszMarkup = 
	_T("<Grid VerticalAlignment='Center' HorizontalAlignment='Center'>")
    _T("    <Grid.ColumnDefinitions>")
    _T("        <ColumnDefinition/>")
    _T("        <ColumnDefinition/>")
    _T("        <ColumnDefinition/>")
    _T("        <ColumnDefinition/>")
    _T("    </Grid.ColumnDefinitions>")
    _T("    <Grid.RowDefinitions>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("     </Grid.RowDefinitions>")
    _T("    <Border Grid.Column='0' Grid.Row='0'><TextBlock><Hyperlink>FTSE 100</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='1'><TextBlock><Hyperlink>FTSE TechMark</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='2'><TextBlock><Hyperlink>Dow Jones</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='3'><TextBlock><Hyperlink>S&amp;P 500</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='4'><TextBlock><Hyperlink>Dollar</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='5'><TextBlock><Hyperlink>Euro</Hyperlink></TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='0'><TextBlock TextAlignment='Right'>5,990.12</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='1'><TextBlock TextAlignment='Right'>804.10</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='2'><TextBlock TextAlignment='Right'>8,322.12</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='3'><TextBlock TextAlignment='Right'>860</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='4'><TextBlock TextAlignment='Right'>1.56</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='5'><TextBlock TextAlignment='Right'>1.59</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='0'><TextBlock TextAlignment='Right' Foreground='Green'>+50.1</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='1'><TextBlock TextAlignment='Right' Foreground='Red'>-0.4</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='2'><TextBlock TextAlignment='Right' Foreground='Green'>+78</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='3'><TextBlock TextAlignment='Right' Foreground='Green'>+15.43</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='4'><TextBlock TextAlignment='Right' Foreground='Green'>+0.06</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='5'><TextBlock TextAlignment='Right' Foreground='Red'>-0.11</TextBlock></Border>")
    _T("</Grid>");
	
	
	
	pItemText->SetMarkupText(lpszMarkup);
	pItemText->FitToContent();
	CSize sz(pItemText->GetRect().Size());

	// close icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(sz.cx + 10, 10, sz.cx + 10 + 16, 10 + 16)));
	
	pPopup->GetImageManager()->SetIcon(IDI_POPUP_CLOSE, IDI_POPUP_CLOSE);
	pItemIcon->SetIconIndex(IDI_POPUP_CLOSE);

	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(XTP_ID_POPUP_CLOSE);

	pPopup->SetPopupSize(CSize(sz.cx + 30, sz.cy + 20));
	pPopup->Show(this);

	m_lstPopupControl.AddTail(pPopup);	
}

void CPopupControlDemoDlg::OnMoreLayerSample() 
{
	CXTPPopupControl* pPopup = new CXTPPopupControl();
	pPopup->AllowMove(TRUE);

	pPopup->SetAnimateDelay(500);
	pPopup->SetPopupAnimation();
	
	pPopup->SetShowDelay(5000);

	UINT nCommands[] = {100};
	VERIFY(pPopup->GetImageManager()->SetIcons(_T("IDB_PUSSLE"), nCommands, 1, CSize(0, 0)));
	pPopup->SetBackgroundBitmap(nCommands[0]);

	pPopup->SetPopupSize(CSize(156, 161));
	pPopup->Show(this);

	m_lstPopupControl.AddTail(pPopup);	
	
}
