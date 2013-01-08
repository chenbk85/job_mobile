// PageGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "PageGeneral.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageGeneral property page

IMPLEMENT_DYNCREATE(CPageGeneral, COptionsPage)

CPageGeneral::CPageGeneral() : COptionsPage(CPageGeneral::IDD)
{
	//{{AFX_DATA_INIT(CPageGeneral)
	m_bConfirmCloseAll = FALSE;
	m_bConfirmExit = FALSE;
	m_bOneInstance = FALSE;
	m_nDocking = -1;
	m_nStartup = -1;
	m_bRestoreWindowPos = FALSE;
	//}}AFX_DATA_INIT
}

CPageGeneral::~CPageGeneral()
{
}

void CPageGeneral::DoDataExchange(CDataExchange* pDX)
{
	COptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageGeneral)
	DDX_Control(pDX, IDC_COMBO_URLS, m_cmbUrls);
	DDX_Check(pDX, IDC_CHECK_CLOSEALL, m_bConfirmCloseAll);
	DDX_Check(pDX, IDC_CHECK_EXIT, m_bConfirmExit);
	DDX_Check(pDX, IDC_CHECK_RUN, m_bOneInstance);
	DDX_Radio(pDX, IDC_RADIO_DOCKING, m_nDocking);
	DDX_Radio(pDX, IDC_RADIO_STARTUP, m_nStartup);
	DDX_Check(pDX, IDC_CHECK_RESTORE, m_bRestoreWindowPos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageGeneral, COptionsPage)
	//{{AFX_MSG_MAP(CPageGeneral)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_DELETEALL, OnButtonDeleteall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageGeneral message handlers


BOOL CPageGeneral::OnInitDialog() 
{
	COptionsPage::OnInitDialog();

	//CComboBox& wndAddress = GetMainFrame()->m_wndAddress;
	CXTPControlComboBox* pCombo = GetAddressCombo();
	
	if (!pCombo)
		return TRUE;

	int nCount = pCombo->GetCount();

	CString str;
	for (int i = 0; i < nCount; i++)
	{
		 pCombo->GetLBText(i, str);
		 m_cmbUrls.AddString(str);
	}
	
	m_cmbUrls.SetCurSel(0);

	
	
	
	return TRUE;  	              
}

void CPageGeneral::OnButtonDelete() 
{
	int nSel = m_cmbUrls.GetCurSel();
	
	if (nSel != CB_ERR)
	{
		m_cmbUrls.DeleteString(nSel);
		m_cmbUrls.SetCurSel(nSel);
	}
	
}

void CPageGeneral::OnButtonDeleteall() 
{
	m_cmbUrls.ResetContent();
}

void CPageGeneral::OnOK() 
{
	CXTPControlComboBox* pCombo = GetAddressCombo();
	
	if (!pCombo)
		return;
	int nCount = m_cmbUrls.GetCount();

	if (nCount != pCombo->GetCount())
	{	
		CString strText;
		pCombo->ResetContent();

		CString str;
		for (int i = 0; i < nCount; i++)
		{
			m_cmbUrls.GetLBText(i, str);
			pCombo->AddString(str);
		}
	}
}



