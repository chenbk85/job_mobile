// DialogRowsCount.cpp : implementation file
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
#include "VirtualList.h"
#include "DialogRowsCount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogRowsCount dialog


CDialogRowsCount::CDialogRowsCount(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRowsCount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogRowsCount)
	m_nRowsCount = 0;
	//}}AFX_DATA_INIT
}


void CDialogRowsCount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogRowsCount)
	DDX_Text(pDX, IDC_EDIT_ROWSCOUNT, m_nRowsCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogRowsCount, CDialog)
	//{{AFX_MSG_MAP(CDialogRowsCount)
	ON_EN_UPDATE(IDC_EDIT_ROWSCOUNT, OnUpdateEditRowscount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogRowsCount message handlers

void CDialogRowsCount::OnUpdateEditRowscount() 
{
	UpdateData(TRUE);
	UpdateData(FALSE);	
}
