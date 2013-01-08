// ReportSampleView.cpp : implementation of the CReportSampleView class
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportSample.h"

#include "MainFrm.h"
#include "ReportSampleDoc.h"
#include "TreeViewDlg.h"

#include "MessageRecord.h"

#include "float.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum
{
	COLUMN_IMPORTANCE,
	COLUMN_ICON,
	COLUMN_ATTACHMENT,
	COLUMN_FROM,
	COLUMN_SUBJECT,
	COLUMN_SENT,
	COLUMN_SIZE,
	COLUMN_CHECK,
	COLUMN_PRICE,
	COLUMN_CREATED,
	COLUMN_RECEIVED,
	COLUMN_CONVERSATION,
	COLUMN_CONTACTS,
	COLUMN_MESSAGE,
	COLUMN_CC,
	COLUMN_CATEGORIES,
	COLUMN_AUTOFORWARD,
	COLUMN_DO_NOT_AUTOARCH,
	COLUMN_DUE_BY,
};

const int COLUMN_MAIL_ICON   =  0;
const int COLUMN_CHECK_ICON  =  2;

/////////////////////////////////////////////////////////////////////////////
// CTreeViewDlg dialog


CTreeViewDlg::CTreeViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeViewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTreeViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeViewDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeViewDlg, CDialog)
	//{{AFX_MSG_MAP(CTreeViewDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportRClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeViewDlg message handlers

BOOL CTreeViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	VERIFY(m_ilIcons.Create(16,16, ILC_COLOR24|ILC_MASK, 0, 1));
	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(IDB_BMREPORT));
	m_ilIcons.Add(&bmp, RGB(255, 0, 255));

	m_wndReport.SetImageList(&m_ilIcons);


	m_wndReport.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);



	//
	//  Add sample columns
	//
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_ICON, _T(""), 18, FALSE, COLUMN_MAIL_ICON));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_CHECK, _T(""), 18, FALSE, COLUMN_CHECK_ICON));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_SUBJECT, _T("Subject"), 280));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_FROM, _T("From"), 180));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_SENT, _T("Sent"), 150));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_SIZE, _T("Size"), 50));
	m_wndReport.AddColumn(new CXTPReportColumn(COLUMN_PRICE, _T("Price"), 80));

	//
	//  Add sample records in tree
	//

	COleDateTime odtSent(COleDateTime::GetCurrentTime());
	COleDateTime odtCreated(COleDateTime::GetCurrentTime());
	COleDateTime odtReceived(COleDateTime::GetCurrentTime());
	CString strMessage(" ");
	CString strEmpty(" ");

	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	CMessageRecord *pParentRec1 = new CMessageRecord(msgImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_wndReport.AddRecord(pParentRec1);
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, TRUE, FALSE, _T("Peter Parker [pparker@codetoolbox.com]"), _T("Re: it's me again"), odtSent, 14, TRUE, 12.2,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceLow, FALSE, TRUE, _T("QueryReply"), _T("Re: it's me again"), odtSent, 13, FALSE, 1.345,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	CMessageRecord *pParentRec2 = new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Bruce Wayne"), _T("I don't understand:"), odtSent, 24, FALSE, 5.4321,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(pParentRec2);
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, FALSE, FALSE, _T("Programmers - www.codetoolbox.com"), _T("Am I a programmer?"), odtSent, 14, TRUE, 45,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Oswald Cobblepot"), _T("Yeah I know"), odtSent, 13, TRUE, 0.5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;

//

	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1 = new CMessageRecord(msgImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_wndReport.AddRecord(pParentRec1);
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, TRUE, FALSE, _T("Peter Parker [pparker@codetoolbox.com]"), _T("Re: it's me again"), odtSent, 14, TRUE, 12.2,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceLow, FALSE, TRUE, _T("QueryReply"), _T("Re: it's me again"), odtSent, 13, FALSE, 1.345,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec2 = new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Bruce Wayne"), _T("I don't understand:"), odtSent, 24, FALSE, 5.4321,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(pParentRec2);
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, FALSE, FALSE, _T("Programmers - www.codetoolbox.com"), _T("Am I a programmer?"), odtSent, 14, TRUE, 45,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Oswald Cobblepot"), _T("Yeah I know"), odtSent, 13, TRUE, 0.5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;

	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1 = new CMessageRecord(msgImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_wndReport.AddRecord(pParentRec1);
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, TRUE, FALSE, _T("Peter Parker [pparker@codetoolbox.com]"), _T("Re: it's me again"), odtSent, 14, TRUE, 12.2,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(new CMessageRecord(msgImportanceLow, FALSE, TRUE, _T("QueryReply"), _T("Re: it's me again"), odtSent, 13, FALSE, 1.345,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec2 = new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Bruce Wayne"), _T("I don't understand:"), odtSent, 24, FALSE, 5.4321,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	pParentRec1->GetChilds()->Add(pParentRec2);
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceHigh, FALSE, FALSE, _T("Programmers - www.codetoolbox.com"), _T("Am I a programmer?"), odtSent, 14, TRUE, 45,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	pParentRec2->GetChilds()->Add(new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Oswald Cobblepot"), _T("Yeah I know"), odtSent, 13, TRUE, 0.5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;
	m_wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;



//


	m_wndReport.GetColumns()->Find(COLUMN_SUBJECT)->SetTreeColumn(TRUE);

	// Populate all data on control
	m_wndReport.Populate();

	return FALSE;
}

void CTreeViewDlg::OnOK()
{
	CDialog::OnOK();
}

void CTreeViewDlg::OnReportRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	
	if (pItemNotify->pRow)
	{
		TRACE(_T("Right click on row %d\n"), pItemNotify->pRow->GetIndex());
	}

}
