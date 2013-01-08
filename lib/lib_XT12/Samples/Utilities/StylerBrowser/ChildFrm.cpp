// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Styler.h"

#include "ChildFrm.h"
#include "StylerView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	m_bActivate = TRUE;	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	//cs.xtp &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	if (!m_bActivate) 
	{
		nCmdShow = SW_SHOWNOACTIVATE;
		m_bActivate = TRUE;
	}
		
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


void CChildFrame::OnNcPaint() 
{
}

BOOL CChildFrame::OnNcActivate(BOOL /*bActive*/) 
{
	return TRUE;
}

LRESULT CChildFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_XTP_GETWINDOWTOOLTIP)
	{
		return OnGetToolTip(wParam, lParam);
	}
	if (message > WM_USER)
	{
		CStylerView* pView = (CStylerView*)GetActiveView();
		if (pView)
			return pView->SendMessage(message, wParam, lParam);

	}
	
	return CMDIChildWnd::WindowProc(message, wParam, lParam);
}


BOOL CChildFrame::PreTranslateMessage(MSG* pMsg) 
{
	// allow tooltip messages to be filtered
	if (CWnd::PreTranslateMessage(pMsg))
		return TRUE;

	return FALSE;
}

LRESULT CChildFrame::OnGetToolTip(WPARAM, LPARAM)
{
	CStylerDoc* pDoc = DYNAMIC_DOWNCAST(CStylerDoc, GetActiveDocument());
	if (!pDoc)
		return 0;
	
	LPCTSTR lpURL = pDoc->GetCurrentUrl();
	
	return (LRESULT)lpURL;
}
