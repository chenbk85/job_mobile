// TabSamplePage.cpp : implementation file
//

#include "stdafx.h"
#include "PropertySheet.h"
#include "TabSamplePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabSamplePage property page

IMPLEMENT_DYNCREATE(CTabSamplePage, CXTPPropertyPage)

CTabSamplePage::CTabSamplePage() : CXTPPropertyPage(CTabSamplePage::IDD)
{
	//{{AFX_DATA_INIT(CTabSamplePage)
	m_nValue = 2;
	//}}AFX_DATA_INIT
}

CTabSamplePage::~CTabSamplePage()
{
}

void CTabSamplePage::DoDataExchange(CDataExchange* pDX)
{
	CXTPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabSamplePage)
	DDX_Text(pDX, IDC_EDIT_VALUE, m_nValue);
	DDV_MinMaxInt(pDX, m_nValue, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabSamplePage, CXTPPropertyPage)
	//{{AFX_MSG_MAP(CTabSamplePage)
	ON_EN_CHANGE(IDC_EDIT_VALUE, OnChangeEditValue)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabSamplePage message handlers

void CTabSamplePage::OnChangeEditValue() 
{
	SetModified();
}

void CTabSamplePage::OnCheck() 
{
	SetModified();
	
}
