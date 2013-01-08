// PropertySheetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PropertySheet.h"
#include "PropertySheetDlg.h"
#include "TabClientPage.h"
#include "TabSamplePage.h"
#include "TabListPage.h"
#include "TabTreePage.h"
#include "TabResizablePage.h"
#include "TabLongPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDlg dialog

CPropertySheetDlg::CPropertySheetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertySheetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertySheetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPropertySheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertySheetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPropertySheetDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertySheetDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_STANDARD, OnButtonStandard)
	ON_BN_CLICKED(IDC_BUTTON_LIST, OnButtonList)
	ON_BN_CLICKED(IDC_BUTTON_TREE, OnButtonTree)
	ON_BN_CLICKED(IDC_BUTTON_LIST2, OnButtonList2)
	ON_BN_CLICKED(IDC_BUTTON_TASKPANEL, OnButtonTaskPanel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDlg message handlers

BOOL CPropertySheetDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPropertySheetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPropertySheetDlg::OnPaint() 
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
HCURSOR CPropertySheetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPropertySheetDlg::OnButtonStandard() 
{
	CXTPPropertySheet ps(_T("Standard CXTPPRopertySheet Sample"));

	CTabControlPage pageProperties;
	CTabSamplePage pageSample;

	ps.AddPage(&pageProperties);
	ps.AddPage(&pageSample);


	ps.DoModal();
	
}

void CPropertySheetDlg::OnButtonList() 
{
	CXTPPropertySheet ps(_T("CXTPPropertyPageListNavigator Sample"));
	
	CXTPPropertyPageListNavigator* pList = new CXTPPropertyPageListNavigator();
	pList->SetListStyle(xtListBoxOffice2007);
	
	ps.SetNavigator(pList);

	CTabListPage pageProperties;
	CTabSamplePage pageSample;
	CTabResizablePage pageSize;

	ps.AddPage(&pageProperties);
	ps.AddPage(&pageSample);
	ps.AddPage(&pageSize);

	ps.SetResizable();

	ps.DoModal();
}

void CPropertySheetDlg::OnButtonList2() 
{
	CXTPPropertySheet ps(_T("CXTPPropertyPageListNavigator Sample"));
	
	CXTPPropertyPageListNavigator* pList = new CXTPPropertyPageListNavigator();	
	pList->SetListStyle(xtListBoxOffice2007);
	ps.SetNavigator(pList);

	CTabLongPage pageLong;
	ps.AddPage(&pageLong);

	ps.SetResizable();
	ps.SetPageSize(CSize(250, 180)); // in dialog units

	ps.DoModal();	
}


class CCategoriesTreeNavigator : public CXTPPropertyPageTreeNavigator
{
public:
	CCategoriesTreeNavigator()
		: CXTPPropertyPageTreeNavigator(TVS_SHOWSELALWAYS | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT)
	{
		
	}
	
	BOOL CreateTree()
	{
		ASSERT(m_pSheet->GetPageCount() == 2);
		if (m_pSheet->GetPageCount() != 2)
			return FALSE;
		
		HTREEITEM hItemGeneral = InsertItem(_T("General"));
		HTREEITEM hItemOptions = InsertItem(_T("Options"));
		
		for (int i = 0; i < m_pSheet->GetPageCount(); i++)
		{
			CXTPPropertyPage* pPage = m_pSheet->GetPage(i);
			
			CString strCaption = pPage->GetCaption();
			
			HTREEITEM hItem = InsertItem(strCaption, -1, -1, i == 0 ? hItemGeneral : hItemOptions);
			SetItemData(hItem, (DWORD_PTR)pPage);
			pPage->m_dwData = (DWORD_PTR)hItem;
		}
		
		return TRUE;
	}
	
};

void CPropertySheetDlg::OnButtonTree() 
{

#if 1
	CXTPPropertySheet ps(_T("CXTPPropertyPageTreeNavigator Sample"));
	ps.SetNavigator(new CCategoriesTreeNavigator());

	ps.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	CTabTreePage pageProperties;
	CTabSamplePage pageSample2;

	ps.AddPage(&pageProperties);
	ps.AddPage(&pageSample2);
	ps.SetResizable();

	ps.DoModal();
#else // Modeless
	class CSamplePropertySheet : public CXTPPropertySheet
	{
	public:
		CSamplePropertySheet()
			: CXTPPropertySheet(_T("CXTPPropertyPageTreeNavigator Sample"))
		{
			SetNavigator(new CCategoriesTreeNavigator());
			m_psh.dwFlags |= PSH_NOAPPLYNOW;

			AddPage(&pageProperties);
			AddPage(&pageSample2);

			SetResizable();
		}
		CTabTreePage pageProperties;
		CTabSamplePage pageSample2;

	};

	CSamplePropertySheet* ps = new CSamplePropertySheet();
	ps->Create();

#endif	
}

#ifdef _XTP_INCLUDE_TASKPANEL

//////////////////////////////////////////////////////////////////////////
// CPropertyPageTaskPanelNavigator

class CPropertyPageTaskPanelNavigator : public CXTPTaskPanel, public CXTPPropertyPageControlNavigator
{
public:
	CPropertyPageTaskPanelNavigator();

public:
	virtual BOOL Create();
	virtual void OnPageSelected(CXTPPropertyPage* pPage);
	virtual HWND GetSafeHwnd() const { return m_hWnd; }

protected:
	virtual void SetFocusedItem(CXTPTaskPanelItem* pItem, BOOL bDrawFocusRect = FALSE, BOOL bSetFocus = TRUE);
};

CPropertyPageTaskPanelNavigator::CPropertyPageTaskPanelNavigator()
{
}

BOOL CPropertyPageTaskPanelNavigator::Create()
{
	CFont* pFont = m_pSheet->GetFont();

	if (!CXTPTaskPanel::Create(WS_VISIBLE | WS_CHILD | WS_GROUP | WS_TABSTOP, CRect(0, 0, 0, 0), m_pSheet, 1000))
		return FALSE;

	SetBehaviour(xtpTaskPanelBehaviourList);
	SetTheme(xtpTaskPanelThemeShortcutBarOffice2003);
	SetSelectItemOnFocus(TRUE);

	SetIconSize(CSize(32, 32));

	SetFont(pFont);

	CXTPTaskPanelGroup* pGroup = AddGroup(0);
	pGroup->SetCaption(_T("Properties"));

	for (int i = 0; i < m_pSheet->GetPageCount(); i++)
	{
		CXTPPropertyPage* pPage = m_pSheet->GetPage(i);

		CString strCaption = pPage->GetCaption();

		CXTPTaskPanelGroupItem* pItem = pGroup->AddLinkItem(i, i);
		pItem->SetCaption(strCaption);
		pItem->SetItemData((DWORD_PTR)pPage);
		pPage->m_dwData = (DWORD_PTR)pItem;
	}

	GetImageManager()->SetIcon(IDI_CONTACTS, 0);
	GetImageManager()->SetIcon(IDI_TASKS, 1);
	GetImageManager()->SetIcon(IDI_NOTES, 2);


	m_pSheet->SetPageBorderStyle(xtpPageBorderBottomLine);

	return TRUE;
}

void CPropertyPageTaskPanelNavigator::OnPageSelected(CXTPPropertyPage* pPage)
{
	CXTPTaskPanelGroupItem* pItem = (CXTPTaskPanelGroupItem*)pPage->m_dwData;
	SetFocusedItem(pItem);
}

void CPropertyPageTaskPanelNavigator::SetFocusedItem(CXTPTaskPanelItem* pItem, BOOL bDrawFocusRect /*= FALSE*/, BOOL bSetFocus)
{
	if (m_pItemFocused != pItem && pItem && pItem->GetType() == xtpTaskItemTypeLink)
	{
		CXTPPropertyPage* pPage = (CXTPPropertyPage*)pItem->GetItemData();
		if (!m_pSheet->SetActivePage(pPage))
		{
			return;
		}
	}

	CXTPTaskPanel::SetFocusedItem(pItem, bDrawFocusRect, bSetFocus);

}


void CPropertySheetDlg::OnButtonTaskPanel()
{
	CXTPPropertySheet ps(_T("Custom Navigator Sample"));
	
	CPropertyPageTaskPanelNavigator* pList = new CPropertyPageTaskPanelNavigator();
	
	ps.SetNavigator(pList);

	CTabTreePage pageProperties;
	CTabSamplePage pageSample;
	CTabResizablePage pageSize;

	ps.AddPage(&pageProperties);
	ps.AddPage(&pageSample);
	ps.AddPage(&pageSize);

	ps.SetResizable();

	ps.DoModal();

}

#else // _XTP_INCLUDE_TASKPANEL

void CPropertySheetDlg::OnButtonTaskPanel()
{

}

#endif
