// FontComboDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FontCombo.h"
#include "FontComboDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CFontComboDlg dialog

CFontComboDlg::CFontComboDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontComboDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontComboDlg)
	m_bBold = FALSE;
	m_bItalic = FALSE;
	m_bUnderline = FALSE;
	//}}AFX_DATA_INIT

	m_crCurrent = COLORREF_NULL;

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	CXTRegistryManager regMgr;
    m_bBold       = regMgr.GetProfileInt   (_T("Settings"), _T("m_bBold"),       TRUE        );
    m_bItalic     = regMgr.GetProfileInt   (_T("Settings"), _T("m_bItalic"),     FALSE       );
    m_bUnderline  = regMgr.GetProfileInt   (_T("Settings"), _T("m_bUnderline"),  FALSE       );
	m_strFontSize = regMgr.GetProfileString(_T("Settings"), _T("m_strFontSize"), _T("36")    );
	m_strFontName = regMgr.GetProfileString(_T("Settings"), _T("m_strFontName"), _T("Verdana"));
	m_crCurrent   = regMgr.GetProfileInt   (_T("Settings"), _T("m_crCurrent"),   CLR_DEFAULT );

	// Set the theme for the application.
	XTThemeManager()->SetTheme(xtThemeOffice2003);
}

CFontComboDlg::~CFontComboDlg()
{
	CXTRegistryManager regMgr;
    regMgr.WriteProfileInt   (_T("Settings"), _T("m_bBold"),       m_bBold      );
    regMgr.WriteProfileInt   (_T("Settings"), _T("m_bItalic"),     m_bItalic    );
    regMgr.WriteProfileInt   (_T("Settings"), _T("m_bUnderline"),  m_bUnderline );
	regMgr.WriteProfileString(_T("Settings"), _T("m_strFontSize"), m_strFontSize);
	regMgr.WriteProfileString(_T("Settings"), _T("m_strFontName"), m_strFontName);
	regMgr.WriteProfileInt   (_T("Settings"), _T("m_crCurrent"),   m_crCurrent  );
}

void CFontComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontComboDlg)
	DDX_Control(pDX, IDC_TXT_SAMPLE, m_txtSample);
	DDX_Control(pDX, IDC_COMBO_SIZE, m_wndComboSize);
	DDX_Control(pDX, IDC_COMBO_FONT, m_wndComboFont);
	DDX_Control(pDX, IDC_COLOR_FONT, m_wndColorPicker);
	DDX_Check(pDX, IDC_CHK_BOLD, m_bBold);
	DDX_Check(pDX, IDC_CHK_ITALIC, m_bItalic);
	DDX_Check(pDX, IDC_CHK_UNDERLINE, m_bUnderline);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFontComboDlg, CDialog)
	//{{AFX_MSG_MAP(CFontComboDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELENDOK(IDC_COMBO_SIZE, OnSelendokComboSize)
	ON_BN_CLICKED(IDC_CHK_BOLD, OnChkBold)
	ON_BN_CLICKED(IDC_CHK_ITALIC, OnChkItalic)
	ON_BN_CLICKED(IDC_CHK_UNDERLINE, OnChkUnderline)
	//}}AFX_MSG_MAP
	ON_CPN_XT_SELENDOK(IDC_COLOR_FONT, OnSelEndOKColor)
	ON_CBN_SELENDOK(IDC_COMBO_FONT, OnSelEndOKFontCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontComboDlg message handlers

BOOL CFontComboDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// select the font and set the drop width for the combo.
	m_wndComboFont.InitControl(m_strFontName, 285);

	// insert strings into the size combo box.
	m_wndComboSize.AddString(_T("8"));
	m_wndComboSize.AddString(_T("10"));
	m_wndComboSize.AddString(_T("12"));
	m_wndComboSize.AddString(_T("14"));
	m_wndComboSize.AddString(_T("18"));
	m_wndComboSize.AddString(_T("24"));
	m_wndComboSize.AddString(_T("36"));

	// set the selection.
	if (m_wndComboSize.SelectString(-1, m_strFontSize) == CB_ERR)
	{
		m_wndComboSize.SetWindowText(m_strFontSize);
	}

	m_wndColorPicker.SetColor( m_crCurrent );

	// initialize the text sample display
	UpdateFont();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFontComboDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFontComboDlg::OnPaint() 
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
HCURSOR CFontComboDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFontComboDlg::OnSelEndOKColor()
{
	m_crCurrent = m_wndColorPicker.GetColor();
	m_txtSample.UpdateFont(m_lf, m_crCurrent);
}

void CFontComboDlg::OnSelEndOKFontCombo()
{
	UpdateFont();
}

void CFontComboDlg::UpdateFont()
{
	UpdateData();
	m_wndComboFont.GetSelFont(m_lf);
	m_strFontName = m_lf.lfFaceName;

	int iSel = m_wndComboSize.GetCurSel();
	if (iSel != CB_ERR)
	{
		m_wndComboSize.GetLBText(iSel, m_strFontSize);
		m_lf.lfHeight = -(_ttoi(m_strFontSize));
	}
	else
	{
		m_wndComboSize.GetWindowText(m_strFontSize);
		m_lf.lfHeight = -(_ttoi(m_strFontSize));
	}

	m_lf.lfWeight    = m_bBold      ? FW_BOLD : FW_NORMAL;
	m_lf.lfItalic    = m_bItalic    ? (BYTE)1 : (BYTE)0;
	m_lf.lfUnderline = m_bUnderline ? (BYTE)1 : (BYTE)0;

	m_txtSample.UpdateFont(m_lf, m_crCurrent);
}

void CFontComboDlg::OnSelendokComboSize() 
{
	UpdateFont();
}

void CFontComboDlg::OnChkBold() 
{
	UpdateFont();
}

void CFontComboDlg::OnChkItalic() 
{
	UpdateFont();
}

void CFontComboDlg::OnChkUnderline() 
{
	UpdateFont();
}
