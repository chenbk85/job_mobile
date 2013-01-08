// PageMouse.cpp : implementation file
//

#include "stdafx.h"
#include "styler.h"
#include "pagemouse.h"

#include "MouseManager.h"
#include "StylerView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageMouse property page

IMPLEMENT_DYNCREATE(CPageMouse, COptionsPage)

CPageMouse::CPageMouse() 
: COptionsPage(CPageMouse::IDD), m_wndAssign(GetMainFrame()->GetCommandBars()->GetShortcutManager())

{
	m_wndAssign.m_bAllowDoubleKeyShortcuts = FALSE;

	//{{AFX_DATA_INIT(CPageMouse)
	//}}AFX_DATA_INIT
}

CPageMouse::~CPageMouse()
{
}

void CPageMouse::DoDataExchange(CDataExchange* pDX)
{
	COptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageMouse)
	DDX_Control(pDX, IDC_EDIT_ASSIGN, m_wndAssign);
	DDX_Control(pDX, IDC_LIST_CURRENT, m_wndCurrent);
	DDX_Control(pDX, IDC_COMBO_MOUSE, m_cmbMouse);
	DDX_Control(pDX, IDC_COMBO_COMMAND, m_cmbCommands);
	DDX_Control(pDX, IDC_COMBO_AREA, m_cmbArea);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageMouse, COptionsPage)
	//{{AFX_MSG_MAP(CPageMouse)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageMouse message handlers

BOOL CPageMouse::OnInitDialog() 
{
	COptionsPage::OnInitDialog();
	
	
	CXTPCommandBar* pMenuBar = GetMainFrame()->GetCommandBars()->GetMenuBar();
	ASSERT(pMenuBar);	
	
	if (pMenuBar)
	{
		GetMenuStrings(pMenuBar, _T(""));
		m_mapCommands[ID_VIEW_LOCK] = "View.Lock";

	}

	UINT nID;
	CString strTitle;
	POSITION pos = m_mapCommands.GetStartPosition();
	while (pos != NULL)
	{
		m_mapCommands.GetNextAssoc( pos, nID, strTitle);		
		m_cmbCommands.AddStringData(strTitle, nID);
	}
	
	m_cmbMouse.AddStringData(CMouseManager::GetMouseString(WM_LBUTTONDOWN), WM_LBUTTONDOWN);//"Left Button Click"
	m_cmbMouse.AddStringData(CMouseManager::GetMouseString(WM_RBUTTONDOWN), WM_RBUTTONDOWN);
	m_cmbMouse.AddStringData(CMouseManager::GetMouseString(WM_MBUTTONDOWN), WM_MBUTTONDOWN);
	m_cmbMouse.AddStringData(CMouseManager::GetMouseString(WM_LBUTTONDBLCLK), WM_LBUTTONDBLCLK);
	m_cmbMouse.AddStringData(CMouseManager::GetMouseString(WM_RBUTTONDBLCLK), WM_RBUTTONDBLCLK);

	m_cmbArea.AddStringData(_T("Tab"), MOUSE_AREA_TAB);
	m_cmbArea.AddStringData(_T("Tabbar"), MOUSE_AREA_TABBAR);
	m_cmbArea.AddStringData(_T("WebBrowser"), MOUSE_AREA_BROWSER);

	m_wndCurrent.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_wndCurrent.SetExtendedStyle(m_wndCurrent.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	
	m_wndCurrent.InsertColumn(0, _T("Mouse"), LVCFMT_LEFT, 100);
	m_wndCurrent.InsertColumn(1, _T("Key"), LVCFMT_LEFT, 60);
	m_wndCurrent.InsertColumn(2, _T("Area"), LVCFMT_LEFT, 50);
	m_wndCurrent.InsertColumn(3, _T("Command"), LVCFMT_LEFT, 123);

	m_wndAssign.m_bExtendedOnly = TRUE;
	
	RefreshList();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPageMouse::GetMenuStrings(CXTPCommandBar* pBar, CString strPrefix)
{
	int nCount = pBar->GetControls()->GetCount();
	
	for (int i = 0; i < nCount; i++)
	{	

		CXTPControl* pControl = pBar->GetControls()->GetAt(i);
		CString strTitle = pControl->GetCaption();		
		ConvertMenuItem(strTitle);		

		if (!strTitle.IsEmpty())
		{			
			if (IsPopupControlType(pControl->GetType()))
			{
				GetMenuStrings(((CXTPControlPopup*)pControl)->GetCommandBar(), strPrefix + strTitle + '.');
			} 
			else if (pControl->GetID())
			{
				int nId = pControl->GetID();

				if (! (nId >= AFX_IDM_FIRST_MDICHILD && nId < AFX_IDM_FIRST_MDICHILD + 10))
				if (! (	
						nId == ID_FAVORITES_EX ||
						nId == ID_OPENALLFOLDERITEMS ||
						nId == ID_ADDPAGEHERE ||
						nId == ID_FAVORITE_LINK ||
						nId == ID_FAVORITE_FOLDER))
				{
					CString strCommand = strPrefix + strTitle;
					m_mapCommands.SetAt(nId, strCommand);
				}				
			}
		}
	}	 	
}

void CPageMouse::RefreshList()
{	
	CString strKey;
	CString strArea;
	m_wndCurrent.DeleteAllItems();


	CMouseManager::CMouseClicksArray& mca = CMouseManager::GetArray();
	
	for (int i = 0; i < mca.GetSize(); i++)
	{
		MOUSECLICKS& mc = mca[i];

		CXTPShortcutManagerAccel accel(&mc.accel);
		CXTPShortcutManager::CKeyHelper kh(&accel, GetMainFrame()->GetCommandBars()->GetShortcutManager());
		kh.Format(strKey);
		
		int nIndex = m_wndCurrent.InsertItem(0, CMouseManager::GetMouseString(mc.dwMouse));
		m_wndCurrent.SetItemText(nIndex, 1, strKey);

		m_cmbArea.GetLBText(mc.nArea, strArea);
		m_wndCurrent.SetItemText(nIndex, 2, strArea);		
		m_wndCurrent.SetItemText(nIndex, 3, m_mapCommands[mc.accel.cmd]);

		m_wndCurrent.SetItemData(nIndex, i);


	}
}

void CPageMouse::OnButtonRemove() 
{
	UINT i, nSelectedCount = m_wndCurrent.GetSelectedCount();
	int  nItem = -1;

	CMouseManager::CMouseClicksArray& mca = CMouseManager::GetArray();

	if (nSelectedCount > 0)
	{
		BOOL bUpdate = FALSE;
		for (i = 0; i < nSelectedCount; i++)
		{
			nItem = m_wndCurrent.GetNextItem(nItem, LVNI_SELECTED);
			ASSERT(nItem != -1);
			if (nItem != -1)
			{
				int dwData = (int)m_wndCurrent.GetItemData(nItem);
				
				if (dwData >= 0 && dwData < mca.GetSize())
				{
					mca.RemoveAt(dwData);
					bUpdate = TRUE;
				}				   
			}
		}
		if (bUpdate)
			RefreshList();
	}
		
		
}


void CPageMouse::OnButtonAdd() 
{
	MOUSECLICKS mc;
	if (m_cmbMouse.GetCurSel() == CB_ERR)
		return;
	
	mc.dwMouse =  (DWORD)m_cmbMouse.GetItemData(m_cmbMouse.GetCurSel());
	CXTPShortcutManagerAccel* pAccel = m_wndAssign.GetAccel();
	
	mc.accel.fVirt = pAccel->key[0].fVirt;

	if (m_cmbCommands.GetCurSel() == CB_ERR)
		return;

	mc.accel.cmd = (WORD)m_cmbCommands.GetItemData(m_cmbCommands.GetCurSel());
	
	if (m_cmbArea.GetCurSel() == CB_ERR)
		return;
	
	mc.nArea =  (int)m_cmbArea.GetItemData(m_cmbArea.GetCurSel());

	CMouseManager::CMouseClicksArray& mca = CMouseManager::GetArray();
	
	mca.Add(mc);
	RefreshList();	
}
