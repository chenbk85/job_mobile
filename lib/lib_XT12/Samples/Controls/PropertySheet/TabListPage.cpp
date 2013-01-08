// TabListPage.cpp : implementation file
//

#include "stdafx.h"
#include "PropertySheet.h"
#include "TabListPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabListPage property page

IMPLEMENT_DYNCREATE(CTabListPage, CXTPPropertyPage)

CTabListPage::CTabListPage() : CXTPPropertyPage(CTabListPage::IDD)
{
	//{{AFX_DATA_INIT(CTabListPage)
	m_bFlatPage = FALSE;
	m_nStyle = 2;
	//}}AFX_DATA_INIT
}

CTabListPage::~CTabListPage()
{
}

void CTabListPage::DoDataExchange(CDataExchange* pDX)
{
	CXTPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabListPage)
	DDX_Check(pDX, IDC_CHECK_FLAT, m_bFlatPage);
	DDX_CBIndex(pDX, IDC_COMBO_STYLE, m_nStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabListPage, CXTPPropertyPage)
	//{{AFX_MSG_MAP(CTabListPage)
	ON_BN_CLICKED(IDC_CHECK_FLAT, OnCheckFlat)
	ON_CBN_SELCHANGE(IDC_COMBO_STYLE, OnSelchangeComboStyle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabListPage message handlers

void CTabListPage::OnCheckFlat() 
{
	UpdateData();

	m_pSheet->SetPageBorderStyle(m_bFlatPage ? xtpPageBorderBottomLine : xtpPageBorderFrame);
	m_pSheet->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_ERASE);
}

void CTabListPage::OnSelchangeComboStyle() 
{
	UpdateData();

	CXTPPropertyPageNavigator* pNavigator = m_pSheet->GetNavigator();
	((CXTPPropertyPageListNavigator*)pNavigator)->SetListStyle((XTListBoxStyle)m_nStyle);
}
