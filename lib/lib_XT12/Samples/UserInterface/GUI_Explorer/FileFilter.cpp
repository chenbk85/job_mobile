// FileFilter.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_Explorer.h"
#include "FileFilter.h"


// CFileFilter dialog

IMPLEMENT_DYNCREATE(CFileFilter, CDialog)

CFileFilter::CFileFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CFileFilter::IDD,pParent)
	, m_csFilter(_T(""))
{
}

CFileFilter::~CFileFilter()
{
}

void CFileFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILTER, m_csFilter);
}

BOOL CFileFilter::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CFileFilter, CDialog)
END_MESSAGE_MAP()


