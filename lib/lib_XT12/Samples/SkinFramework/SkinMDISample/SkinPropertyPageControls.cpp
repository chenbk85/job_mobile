// SkinPropertyPageControls.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SkinPropertyPageControls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinPropertyPageControls property page

CSkinPropertyPageControls::CSkinPropertyPageControls() : CPropertyPage(CSkinPropertyPageControls::IDD)
{
	//{{AFX_DATA_INIT(CSkinPropertyPageControls)
	m_radioSelected = 0;
	m_bSelected = TRUE;
	m_csNormal = _T("Normal");
	m_csDisabled = _T("Disabled");
	m_csSample = _T("Multiline\r\nEdit");
	//}}AFX_DATA_INIT
}

CSkinPropertyPageControls::~CSkinPropertyPageControls()
{
}

IMPLEMENT_DYNCREATE(CSkinPropertyPageControls, CPropertyPage)

BEGIN_MESSAGE_MAP(CSkinPropertyPageControls, CPropertyPage)
	//{{AFX_MSG_MAP(CSkinPropertyPageControls)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSkinPropertyPageControls::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkinPropertyPageControls)
	DDX_Control(pDX, IDC_PROGRESS1, m_wndProgress);
	DDX_Control(pDX, IDC_SLIDER_NORMAL, m_wndSlider);
	DDX_Control(pDX, IDC_LISTBOX_SAMPLE, m_wndListBox);
	DDX_Control(pDX, IDC_COMBO_NORMAL, m_comboNormal);
	DDX_Control(pDX, IDC_COMBO_DISABLED, m_comboDisabled);
	DDX_Control(pDX, IDC_SCROLLBAR_NORMAL, m_sbarNormal);
	DDX_Control(pDX, IDC_TREE_SAMPLE, m_wndTreeCtrl);
	DDX_Control(pDX, IDC_LIST_SAMPLE, m_wndListCtrl);
	DDX_Control(pDX, IDC_TAB_SAMPLE, m_wndTabControl);
	DDX_Radio(pDX, IDC_RADIO_SELECTED, m_radioSelected);
	DDX_Check(pDX, IDC_CHK_SELECTED, m_bSelected);
	DDX_Text(pDX, IDC_EDIT_NORMAL, m_csNormal);
	DDX_Text(pDX, IDC_EDIT_DISABLED, m_csDisabled);
	DDX_Text(pDX, IDC_EDIT_SAMPLE, m_csSample);
	//}}AFX_DATA_MAP
}

BOOL CSkinPropertyPageControls::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// CListBox
	int i;
	for (i = 0; i < 20; i++)
	{
		CString strItem;
		strItem.Format(_T("Item%i"), i);
		m_wndListBox.AddString(strItem);
	}
	
	
	// CListCtrl
	m_wndListCtrl.InsertColumn(0, _T("Column One"),   LVCFMT_LEFT, 100);
	m_wndListCtrl.InsertColumn(1, _T("Column Two"),   LVCFMT_LEFT, 100);
	m_wndListCtrl.InsertColumn(2, _T("Column Three"), LVCFMT_LEFT, 100);
	
	for (i = 0; i < 100; ++i)
	{
		CString strItem;
		CString strSubA;
		CString strSubB;
		
		strItem.Format(_T("Item %d"), i);
		strSubA.Format(_T("Sub A %d"), i);
		strSubB.Format(_T("Sub B %d"), i);
		
		m_wndListCtrl.InsertItem(i, strItem, 0);
		m_wndListCtrl.SetItem(i, 1, LVIF_TEXT, strSubA, 0, NULL, NULL, NULL);
		m_wndListCtrl.SetItem(i, 2, LVIF_TEXT, strSubB, 0, NULL, NULL, NULL);
	}
	
	// CTreeCtrl
	for (i = 0; i < 2; i++)
	{
		HTREEITEM hItem1 = m_wndTreeCtrl.InsertItem(_T("Expanded Node"));
		HTREEITEM hItem2 = m_wndTreeCtrl.InsertItem(_T("Expanded Node"), 0,0, hItem1);
		m_wndTreeCtrl.InsertItem(_T("Leaf"), 0,0, hItem1);
		m_wndTreeCtrl.InsertItem(_T("Leaf"), 0,0, hItem2);
		m_wndTreeCtrl.InsertItem(_T("Leaf"), 0,0, hItem2);
		m_wndTreeCtrl.Expand(hItem1, TVE_EXPAND);
		m_wndTreeCtrl.Expand(hItem2, TVE_EXPAND);
	}
	
	// CScrollBar
	SCROLLINFO info;
	info.cbSize = sizeof(SCROLLINFO);     
	info.fMask = SIF_ALL;     
	info.nMin = 0;     
	info.nMax = 2; 
	info.nPage = 1;     
	info.nPos = 1;    
	info.nTrackPos = 2; 
	m_sbarNormal.SetScrollInfo(&info);
	int cx = CXTPWindowRect(&m_sbarNormal).Width();
	int cy = ::GetSystemMetrics(SM_CYVTHUMB);
	m_sbarNormal.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE|SWP_FRAMECHANGED);
	
	// CComboBox
	m_comboNormal.SetCurSel(0);
	m_comboDisabled.SetCurSel(0);

	m_wndSlider.SetPos(30);
	m_wndProgress.SetPos(30);

	// CTabCtrl
	TCITEM item;
	item.mask = TCIF_TEXT;	
	item.pszText = _T("Item");	
	m_wndTabControl.InsertItem(0, &item);
	m_wndTabControl.InsertItem(1, &item);
	m_wndTabControl.InsertItem(2, &item);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSkinPropertyPageControls::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar == (CScrollBar*)&m_wndSlider)
	{
		m_wndProgress.SetPos(m_wndSlider.GetPos());
	}
	
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
