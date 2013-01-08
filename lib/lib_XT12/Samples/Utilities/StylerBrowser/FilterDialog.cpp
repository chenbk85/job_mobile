// FilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Styler.h"
#include "FilterDialog.h"
#include "Shlwapi.h"

CStringArray CFilterDialog::m_lstFilter;

// CFilterDialog dialog

IMPLEMENT_DYNAMIC(CFilterDialog, CDialog)
CFilterDialog::CFilterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterDialog::IDD, pParent)
{
}

CFilterDialog::~CFilterDialog()
{
}

void CFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFilterDialog, CDialog)
END_MESSAGE_MAP()


// CFilterDialog message handlers

BOOL CFilterDialog::OnInitDialog()
{
	CDialog::OnInitDialog();


	CListBox* pLB = (CListBox*)GetDlgItem(IDC_LIST);
	for (int i = 0; i < m_lstFilter.GetSize(); i++)
	{
		pLB->AddString(m_lstFilter[i]);
	}

	m_LBEditor.SubclassDlgItem(IDC_LIST, this);
	m_LBEditor.SetListEditStyle(_T(" &Items:"), LBS_XT_DEFAULT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CFilterDialog::LoadFilterList(void)
{
	CString strPath = GetModuleDir();
			
	TCHAR chReturn[100];
	CString strUrl;
	int nIndex = 0;
	strUrl.Format(_T("url%i"), nIndex);
	while (GetPrivateProfileString(_T("Filter"), strUrl, _T(""), chReturn, 100, strPath + _T("urlfilter.ini")) > 0)
	{
		CString strReturn(chReturn);
		if (!strReturn.IsEmpty())
		{
			m_lstFilter.Add(strReturn);
		}
		strUrl.Format(_T("url%i"), ++nIndex);
	}

}
void CFilterDialog::OnOK()
{
	CListBox* pLB = (CListBox*)GetDlgItem(IDC_LIST);
	
	m_lstFilter.RemoveAll();
	for (int i = 0; i < pLB->GetCount(); i++)
	{
		CString str;
		pLB->GetText(i, str);
		if (!str.IsEmpty())
		m_lstFilter.Add(str);
	}	

	SaveFilterList();

	CDialog::OnOK();
}

void CFilterDialog::SaveFilterList(void)
{
	CString strPath = GetModuleDir();

	CString strUrl;
	if (PathFileExists(strPath + _T("urlfilter.ini")))
		DeleteFile(strPath + _T("urlfilter.ini"));

	for (int i = 0; i < m_lstFilter.GetSize(); i++)
	{
		strUrl.Format(_T("url%i"), i);
		WritePrivateProfileString(_T("Filter"), strUrl, m_lstFilter[i], strPath + _T("urlfilter.ini"));
	}
}
