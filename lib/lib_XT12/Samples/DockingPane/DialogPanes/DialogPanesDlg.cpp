// DialogPanesDlg.cpp : implementation file
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
#include "DialogPanes.h"
#include "DialogPanesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDialogPanesDlg dialog

CDialogPanesDlg::CDialogPanesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPanesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPanesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// get path of executable
	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));

	LPTSTR lpszExt = _tcsrchr(szBuff, '.');
	lstrcpy(lpszExt, _T(".xml"));

	m_strIniFileName = szBuff;

}

void CDialogPanesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPanesDlg)
	DDX_Control(pDX, IDC_LIST_VIEW, m_wndView);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogPanesDlg, CDialog)
	//{{AFX_MSG_MAP(CDialogPanesDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LIST_VIEW, OnClickListView)
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)

	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CAPS, OnUpdateKeyIndicator)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_NUM, OnUpdateKeyIndicator)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SCRL, OnUpdateKeyIndicator)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPanesDlg message handlers

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


BOOL CDialogPanesDlg::OnInitDialog()
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

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndView.InsertColumn(0, _T("Themes"), LVCFMT_LEFT, 200);

	m_wndView.InsertItem(0, _T("xtpPaneThemeDefault"));
	m_wndView.InsertItem(1, _T("xtpPaneThemeOffice"));
	m_wndView.InsertItem(2, _T("xtpPaneThemeOffice2003"));
	m_wndView.InsertItem(3, _T("xtpPaneThemeNativeWinXP"));
	m_wndView.InsertItem(4, _T("xtpPaneThemeGrippered"));
	m_wndView.InsertItem(5, _T("xtpPaneThemeVisio"));
	m_wndView.InsertItem(6, _T("xtpPaneThemeWhidbey"));
	m_wndView.InsertItem(7, _T("xtpPaneThemeShortcutBar2003"));
	m_wndView.InsertItem(8, _T("xtpPaneThemeExplorer"));
	m_wndView.InsertItem(9, _T("xtpPaneThemeVisualStudio2005"));
	
	m_wndView.ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);



	VERIFY(m_paneManager.InstallDockingPanes(this));
	m_paneManager.SetTheme(xtpPaneThemeOffice2003);
	m_paneManager.UseSplitterTracker(FALSE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.SetAlphaDockingContext(TRUE);


	// Create docking panes.
	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(
		IDR_PANE1, CRect(0, 0,200, 120), xtpPaneDockBottom);
	m_paneManager.CreatePane(
		IDR_PANE2, CRect(0, 0,200, 120), xtpPaneDockLeft, pwndPane1);
	m_paneManager.CreatePane(
		IDR_PANE3, CRect(0, 0,200, 120), xtpPaneDockLeft);

	
	LOGFONT lfIcon;
	VERIFY( ::SystemParametersInfo( SPI_GETICONTITLELOGFONT, sizeof( lfIcon ), &lfIcon, 0 ) );
	m_fntEdit.CreateFontIndirect(&lfIcon);

	CXTPDockingPaneLayout layout(&m_paneManager);
	if (layout.Load(_T("NormalLayout"))) 
	{
		m_paneManager.SetLayout(&layout);
	}


	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDialogPanesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDialogPanesDlg::OnPaint() 
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
HCURSOR CDialogPanesDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDialogPanesDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect rcClient(0, 0, cx, cy);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, 0, 0, &rcClient);

	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rcClient, &rcClient);

	if (m_wndView.GetSafeHwnd())
	{	
		m_wndView.MoveWindow(rcClient);
	}	
}

LRESULT CDialogPanesDlg::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			int nIndex = pPane->GetID() - IDR_PANE1;
			ASSERT(nIndex >=0 &&  nIndex < sizeof(m_wndEdit) / sizeof(m_wndEdit[0]));
			CEdit& wndEdit = m_wndEdit[nIndex];

			// create and attach the edit control for this pane.
			if (!::IsWindow(wndEdit.m_hWnd))
			{
				if (!wndEdit.CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""),
					WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE|ES_WANTRETURN, CRect(0, 0,200, 120), this, pPane->GetID()))
				{
					TRACE0( "Error creating pane edit control.\n" );
				}
				wndEdit.SetFont(&m_fntEdit);
			}

			pPane->Attach(&wndEdit);
		}

		return TRUE; // handled
	}

	return FALSE;
}

LRESULT CDialogPanesDlg::OnKickIdle(WPARAM, LPARAM)
{
	m_paneManager.UpdatePanes();
	m_wndStatusBar.SendMessage(WM_IDLEUPDATECMDUI, TRUE);
	return 0;
}

void CDialogPanesDlg::OnClose() 
{

	CXTPDockingPaneLayout layout(&m_paneManager);
	m_paneManager.GetLayout(&layout);
	layout.Save(_T("NormalLayout"));

	
	CDialog::OnClose();
}

void CDialogPanesDlg::OnUpdateKeyIndicator(CCmdUI* pCmdUI)
{
	UINT nVK;
	UINT flag = 0x0001;

	switch (pCmdUI->m_nID)
	{
	case ID_INDICATOR_CAPS:
		nVK = VK_CAPITAL;
		break;

	case ID_INDICATOR_NUM:
		nVK = VK_NUMLOCK;
		break;

	case ID_INDICATOR_SCRL:
		nVK = VK_SCROLL;
		break;

	default:
		TRACE1("Warning: OnUpdateKeyIndicator - unknown indicator 0x%04X.\n",
			pCmdUI->m_nID);
		pCmdUI->ContinueRouting();
		return; // not for us
	}

	pCmdUI->Enable(::GetKeyState(nVK) & flag);
		// enable static text based on toggled key state
	ASSERT(pCmdUI->m_bEnableChanged);
}

void CDialogPanesDlg::OnClickListView(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLISTVIEW lpnmlv = (LPNMLISTVIEW)pNMHDR;

	m_paneManager.SetTheme((XTPDockingPanePaintTheme)lpnmlv->iItem);
	*pResult = 0;
}
