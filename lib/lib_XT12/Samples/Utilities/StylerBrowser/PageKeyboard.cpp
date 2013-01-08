// PageKeyboard.cpp : implementation file
//

#include "stdafx.h"
#include "PageKeyboard.h"

#include "StylerView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageKeyboard property page

IMPLEMENT_DYNCREATE(CPageKeyboard, CPropertyPage)

CPageKeyboard::CPageKeyboard() 
: COptionsPage(CPageKeyboard::IDD), m_wndAssign(GetMainFrame()->GetCommandBars()->GetShortcutManager())
{
	//{{AFX_DATA_INIT(CPageKeyboard)
	m_strFilter = _T("");
	//}}AFX_DATA_INIT

	m_pShortcutManager = GetMainFrame()->GetCommandBars()->GetShortcutManager();
	
}

CPageKeyboard::~CPageKeyboard()
{
}

void CPageKeyboard::DoDataExchange(CDataExchange* pDX)
{
	COptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageKeyboard)
	DDX_Control(pDX, IDC_COMBO_USED, m_cmbUsed);
	DDX_Control(pDX, IDC_COMBO_SHORTCUTS, m_cmbShortcuts);
	DDX_Control(pDX, IDC_LIST_ALL, m_wndList);
	DDX_Text(pDX, IDC_EDIT_FILTER, m_strFilter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageKeyboard, COptionsPage)
	//{{AFX_MSG_MAP(CPageKeyboard)
	ON_EN_CHANGE(IDC_EDIT_FILTER, OnFilterChange)
	ON_LBN_SELCHANGE(IDC_LIST_ALL, OnListChange)
	ON_EN_CHANGE(IDC_EDIT_ASSIGN, OnAssignChange)
	ON_BN_CLICKED(IDC_BUTTON_ASSIGN, OnButtonAssign)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_RESETALL, OnButtonResetAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageKeyboard message handlers

BOOL CPageKeyboard::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return COptionsPage::PreTranslateMessage(pMsg);
}



BOOL CPageKeyboard::OnInitDialog() 
{
	COptionsPage::OnInitDialog();
	
	m_wndAssign.SubclassDlgItem(IDC_EDIT_ASSIGN, this);


	CXTPCommandBar* pMenuBar = GetMainFrame()->GetCommandBars()->GetMenuBar();
	ASSERT(pMenuBar);	
	
	if (pMenuBar)
	{
		GetMenuStrings(pMenuBar, _T(""));
	}
	

	Filter();

	GetDlgItem(IDC_BUTTON_ASSIGN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REMOVE)->EnableWindow(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPageKeyboard::GetMenuStrings(CXTPCommandBar* pBar, CString strPrefix)
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
			else
			if (pControl->GetID())
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
				
					LISTINFO linfo;
					linfo.strTitle = strPrefix + strTitle;
					linfo.nID = nId; 
					
					m_arrMenu.Add(linfo);			
				}				
			}
		}
	}	 	
}

void CPageKeyboard::Filter()
{
	UpdateData();
	CString strFilter(m_strFilter);
	strFilter.MakeLower();
	
	m_wndList.ResetContent();
	for(int i = 0; i < m_arrMenu.GetSize(); i++)
	{
		
		CString strTitle = m_arrMenu[i].strTitle;
		strTitle.MakeLower();
		
		if (strFilter.IsEmpty() || strTitle.Find(strFilter) != -1)
		{
			int nIndex = m_wndList.AddString(m_arrMenu[i].strTitle);
			m_wndList.SetItemData(nIndex, m_arrMenu[i].nID);
			
		}
	}

}

void CPageKeyboard::OnFilterChange() 
{
	Filter();	
}

void CPageKeyboard::OnListChange() 
{
	m_cmbShortcuts.ResetContent();

	int nSlected = m_wndList.GetCurSel();
	if (nSlected == LB_ERR)
		return;
	DWORD nID = (DWORD)m_wndList.GetItemData(nSlected);

	
	CXTPShortcutManagerAccelTable* pAccelTable = m_pShortcutManager->GetDefaultAccelerator();

	BOOL bFound = FALSE;
	for (int i = 0; i < pAccelTable->GetCount(); i ++)
	{
		CXTPShortcutManagerAccel* accel = pAccelTable->GetAt(i);
		if (accel->cmd == (int)nID)
		{
			CString str;
			CXTPShortcutManager::CKeyHelper helper (accel, m_pShortcutManager);
			helper.Format (str);
			
			int nIndex = m_cmbShortcuts.AddString(str);
			m_cmbShortcuts.SetItemData(nIndex, i);
			bFound = TRUE;
		}
	}  

	if (bFound)
		m_cmbShortcuts.SetCurSel(0);

	GetDlgItem(IDC_BUTTON_REMOVE)->EnableWindow(bFound);

}

void CPageKeyboard::OnAssignChange() 
{

	GetDlgItem(IDC_BUTTON_ASSIGN)->EnableWindow(m_wndAssign.IsKeyDefined());

	m_cmbUsed.ResetContent();

	if (!m_wndAssign.IsKeyDefined())
		return;
	
	const CXTPShortcutManagerAccel* pAccel = m_wndAssign.GetAccel();
	

	CXTPShortcutManagerAccelTable* pAccelTable = m_pShortcutManager->GetDefaultAccelerator();
	
	for (int i = 0; i < pAccelTable->GetCount(); i ++)
	{
		CXTPShortcutManagerAccel* accel = pAccelTable->GetAt(i);

		if (CXTPShortcutManager::CKeyHelper::EqualAccels(accel, pAccel))
		{
	
			for (int j = 0; j < m_arrMenu.GetSize(); j++)
			{
				if (m_arrMenu[j].nID == (UINT)accel->cmd)
				{		  
					m_cmbUsed.AddString(m_arrMenu[j].strTitle);
					m_cmbUsed.SetCurSel(0);
					break;
				}

			}
		}
	}  
	
}

void CPageKeyboard::OnButtonAssign() 
{		

	int nSlected = m_wndList.GetCurSel();
	int i;
	
	if (nSlected == LB_ERR && !m_wndAssign.IsKeyDefined())
	{
		ASSERT(FALSE);
		return;
	}

	CXTPShortcutManagerAccel newAccel = *m_wndAssign.GetAccel();

	CXTPShortcutManagerAccelTable* pAccelTable = m_pShortcutManager->GetDefaultAccelerator();
	
	for (i = 0; i < pAccelTable->GetCount(); i++)
	{
		if (CXTPShortcutManager::CKeyHelper::EqualAccels(pAccelTable->GetAt(i), &newAccel))
		{
			pAccelTable->RemoveAt(i);
			break;
		}
	}

	UINT nID = (UINT)m_wndList.GetItemData(nSlected);  	
	newAccel.cmd = (WORD)nID;

	pAccelTable->Add(newAccel);

	m_cmbShortcuts.ResetContent();

	BOOL bFound = FALSE;
	
	for (i = 0; i < pAccelTable->GetCount(); i ++)
	{
		CXTPShortcutManagerAccel* accel = pAccelTable->GetAt(i);
		if (accel->cmd == (int)nID)
		{
			CString str;
			CXTPShortcutManager::CKeyHelper helper (accel, m_pShortcutManager);
			helper.Format (str);
			
			int nIndex = m_cmbShortcuts.AddString(str);
			m_cmbShortcuts.SetItemData(nIndex, i);

			if (CXTPShortcutManager::CKeyHelper::EqualAccels(accel, &newAccel))
			{
				m_cmbShortcuts.SetCurSel(nIndex);
			}
			bFound = TRUE;
		}
	}  		
	
	ASSERT(bFound);
	GetDlgItem(IDC_BUTTON_REMOVE)->EnableWindow(bFound);

	m_wndAssign.ResetKey();
	GetDlgItem(IDC_BUTTON_ASSIGN)->EnableWindow(FALSE);

}

void CPageKeyboard::OnButtonRemove() 
{
	int nIndex = m_cmbShortcuts.GetCurSel();
	ASSERT(nIndex != CB_ERR);

	if (nIndex == CB_ERR)
		return;

	int nAccelSize = m_pShortcutManager->GetDefaultAccelerator()->GetCount();
	
	int j = (int)m_cmbShortcuts.GetItemData(nIndex);
	ASSERT( j >= 0 && j < nAccelSize );

	if (j >= 0 && j < nAccelSize)
	{
		m_pShortcutManager->GetDefaultAccelerator()->RemoveAt(j);
	}

	OnListChange();

}

void CPageKeyboard::OnButtonResetAll() 
{
	m_pShortcutManager->Reset();

	OnListChange();
}
