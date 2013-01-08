// TreeCtrlDlg.cpp : implementation file
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
#include "TreeCtrl.h"
#include "TreeCtrlDlg.h"
#include "AboutDlg.h"
#include "PropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlDlg dialog

CTreeCtrlDlg::CTreeCtrlDlg(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CTreeCtrlDlg::IDD, pParent), m_pTreeFocus(NULL)
{
	//{{AFX_DATA_INIT(CTreeCtrlDlg)
	//}}AFX_DATA_INIT

	// Enable Ofice XP themes
	XTThemeManager()->SetTheme(xtThemeOfficeXP);

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeCtrlDlg)
	DDX_Control(pDX, IDC_BTN_PROPERTIES, m_btnProperties);
	DDX_Control(pDX, IDC_TREE_STATE, m_treeState);
	DDX_Control(pDX, IDC_TREE_SELECT, m_treeSelect);
	//}}AFX_DATA_MAP
}

IMPLEMENT_DYNAMIC(CTreeCtrlDlg, CXTResizeDialog)

BEGIN_MESSAGE_MAP(CTreeCtrlDlg, CXTResizeDialog)
	//{{AFX_MSG_MAP(CTreeCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RCLICK, IDC_TREE_SELECT, OnRclickTreeCtrl)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE_SELECT, OnEndlabeleditTreeCtrl)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_PROPERTIES, OnBtnProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlDlg message handlers

BOOL CTreeCtrlDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

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

	// Set control resizing.
	SetResize(IDC_TREE_SELECT,    SZ_TOP_LEFT,     SZ_BOTTOM_CENTER);
	SetResize(IDC_TREE_STATE,     SZ_TOP_CENTER,   SZ_BOTTOM_RIGHT);
	SetResize(IDC_TXT_STATE,      SZ_TOP_CENTER,   SZ_TOP_CENTER);
	SetResize(IDC_STATIC_SEP,     SZ_BOTTOM_LEFT,  SZ_BOTTOM_RIGHT);
	SetResize(IDC_BTN_PROPERTIES, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDCANCEL,           SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);

	// Load window placement
	LoadPlacement(_T("CTreeCtrlDlg"));

	m_treeSelect.EnableMultiSelect();

	HTREEITEM hItemSelect = m_treeSelect.InsertItem(_T("Root Item"), 0, 1);
	m_treeSelect.SetItemBold(hItemSelect);
	m_treeSelect.FocusItem(hItemSelect);

	HTREEITEM hItemState = m_treeState.InsertItemState(_T("Root Item"), 0, 1);
	m_treeState.SetItemBold(hItemState);

	int i, nState = STATE_UNCHECKED;
	for(i = 0; i < 10; ++i )
	{
		m_treeSelect.InsertItem(_T("Child Item"), 0, 1, hItemSelect);
		m_treeState.InsertItemState(_T("Child Item"), 0, 1, nState, hItemState);

		++nState;

		if (nState > STATE_INTERMEDIATE)
			nState = STATE_UNCHECKED;
	}

	m_treeSelect.Expand(hItemSelect, TVE_EXPAND);
	m_treeSelect.SetFont(&XTAuxData().font);

	m_treeState.Expand(hItemState, TVE_EXPAND);
	m_treeState.SetFont(&XTAuxData().font);

	EnableProperties();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTreeCtrlDlg::OnDestroy()
{
	// Save window placement
	SavePlacement(_T("CTreeCtrlDlg"));

	CXTResizeDialog::OnDestroy();
}

void CTreeCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CXTResizeDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTreeCtrlDlg::OnPaint()
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
		CXTResizeDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTreeCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTreeCtrlDlg::OnRclickTreeCtrl(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_TREE));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);

	*pResult = 0;
}

void CTreeCtrlDlg::OnEditCut()
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("You selected Cut!"));
}

void CTreeCtrlDlg::OnEditCopy()
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("You selected Copy!"));
}

void CTreeCtrlDlg::OnEditPaste()
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("You selected Paste!"));
}

void CTreeCtrlDlg::OnEndlabeleditTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	// TODO: Add your control notification handler code here
	if (pTVDispInfo->item.pszText)
	{
		m_treeSelect.SetItemText(pTVDispInfo->item.hItem,
			pTVDispInfo->item.pszText);
	}

	*pResult = 0;
}

BOOL CTreeCtrlDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN ||
		pMsg->wParam == VK_ESCAPE)
	{
		// don't allow dialog to process return or escape keys.
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);

		return TRUE;
	}

	return CXTResizeDialog::PreTranslateMessage(pMsg);
}

void CTreeCtrlDlg::SetTreeFocus(CXTTreeCtrl* pTreeFocus)
{
	ASSERT_VALID(pTreeFocus);
	m_pTreeFocus = pTreeFocus;

	m_treeState.SendMessage(WM_NCPAINT);
	m_treeSelect.SendMessage(WM_NCPAINT);

	EnableProperties();
}

void CTreeCtrlDlg::EnableProperties()
{
	if (m_pTreeFocus == &m_treeState) {
		m_btnProperties.EnableWindow(m_treeState.GetSelectedItem() != NULL);
	}
	else if (m_pTreeFocus == &m_treeSelect) {
		m_btnProperties.EnableWindow(m_treeSelect.GetFirstSelectedItem() != NULL);
	}
	else {
		m_btnProperties.EnableWindow(FALSE);
	}
}

void CTreeCtrlDlg::OnBtnProperties() 
{
	m_dlg.DoModalEx(m_pTreeFocus);
}
