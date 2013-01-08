// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog


COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nActive = 0;

}


void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	//{{AFX_MSG_MAP(COptionsDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_LIST_OPTIONS, OnSelectionChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog message handlers

BOOL COptionsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_wndList.SubclassDlgItem(IDC_LIST_OPTIONS, this);

	GetDlgItem(IDC_WORKSPACE)->GetWindowRect(m_rcWorkspace);
	ScreenToClient(m_rcWorkspace);

	for (int i = 0; i < m_arrPages.GetSize(); i++)
	{
	
		COptionsPage* pPage = m_arrPages[i];
		pPage->Create(pPage->m_psp.pszTemplate, this);

		
		HTREEITEM hItem = m_wndList.InsertItem(pPage->m_strTitle, 1, 0);

		m_wndList.SetItemData(hItem, (DWORD_PTR)pPage);

		pPage->MoveWindow(m_rcWorkspace);
		if (i == m_nActive) m_wndList.SelectItem(hItem);
	}


	return TRUE; 	             
}

void COptionsDialog::SetActivePage(int nPage)
{
	m_nActive = nPage;

}


void COptionsDialog::AddPage(COptionsPage *pPage)
{
	m_arrPages.Add(pPage);
}

void COptionsDialog::OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if (pNMTreeView->itemNew.hItem)
	{
	
		CPropertyPage* pPage = (CPropertyPage*)pNMTreeView->itemNew.lParam;
		ASSERT(pPage);
		ASSERT_KINDOF(CPropertyPage, pPage);
		
		pPage->ShowWindow(SW_SHOW);	  
		pPage->EnableWindow();
		pPage->ModifyStyle(0, WS_TABSTOP);
		
	}
	if (pNMTreeView->itemOld.hItem)
	{
	
		CPropertyPage* pPage = (CPropertyPage*)pNMTreeView->itemOld.lParam;
		ASSERT(pPage);
		ASSERT_KINDOF(CPropertyPage, pPage);
		
		pPage->ShowWindow(SW_HIDE);	  
	}
	
	*pResult = 0;
}


BOOL COptionsDialog::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB )
	{
		 if (GetKeyState(VK_CONTROL) < 0)
		 {
			 
			 HTREEITEM hItem = m_wndList.GetSelectedItem();
			 if (hItem)
			 {				 
				 hItem = GetKeyState(VK_SHIFT) < 0 ?
					 m_wndList.GetPrevVisibleItem(hItem): m_wndList.GetNextVisibleItem(hItem);			 
				 
				 if (hItem) m_wndList.SelectItem(hItem);
			 }				 
			 
			 return TRUE;
		 }
	}		
	
	return CDialog::PreTranslateMessage(pMsg);
}


void COptionsDialog::OnOK()
{
	
	for (int i = 0; i < m_arrPages.GetSize(); i++)
	{	
		m_arrPages[i]->UpdateData();
		m_arrPages[i]->OnOK();
	}

	CDialog::OnOK();

}
