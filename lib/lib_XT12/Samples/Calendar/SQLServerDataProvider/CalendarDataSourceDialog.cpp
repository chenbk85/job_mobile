// CalendarDataSourceDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SQLServerDataProvider.h"
#include "CalendarDataSourceDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarDataSourceDialog dialog


CCalendarDataSourceDialog::CCalendarDataSourceDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarDataSourceDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarDataSourceDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCalendarDataSourceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDataSourceDialog)
	DDX_Control(pDX, IDC_CONNECTION_STRING_EDIT, m_ctrlConnectionString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendarDataSourceDialog, CDialog)
	//{{AFX_MSG_MAP(CCalendarDataSourceDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDataSourceDialog message handlers

void CCalendarDataSourceDialog::OnOK() 
{
	m_ctrlConnectionString.GetWindowText(m_strConnectionString);
	
	CDialog::OnOK();
}

BOOL CCalendarDataSourceDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlConnectionString.SetWindowText(m_strConnectionString);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
