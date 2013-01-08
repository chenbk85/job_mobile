// ShellListView.cpp : implementation file
//

#include "stdafx.h"
#include "WinExplorer.h"
#include "ShellListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShellListView

IMPLEMENT_DYNCREATE(CShellListView, CXTShellListView)

CShellListView::CShellListView()
{
	m_bSortColor = true;

	CXTColorRef crSortBack(GetXtremeColor(COLOR_WINDOW));
	crSortBack.subtract(RGB(8,8,8));

	SetSortTextColor(GetXtremeColor(COLOR_WINDOWTEXT));
	SetSortBackColor(crSortBack);
}

CShellListView::~CShellListView()
{
}


BEGIN_MESSAGE_MAP(CShellListView, CXTShellListView)
	//{{AFX_MSG_MAP(CShellListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShellListView drawing

void CShellListView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CShellListView diagnostics

#ifdef _DEBUG
void CShellListView::AssertValid() const
{
	CXTShellListView::AssertValid();
}

void CShellListView::Dump(CDumpContext& dc) const
{
	CXTShellListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShellListView message handlers

BOOL CShellListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CXTShellListView::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_STATICEDGE;
	
	return TRUE;
}
