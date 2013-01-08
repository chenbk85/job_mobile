// ScrollRichEditView.cpp : implementation file
//

#include "stdafx.h"
#include "ribbonsample.h"
#include "ScrollRichEditView.h"
#include "WorkspaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollRichEditView

CScrollRichEditView::CScrollRichEditView()
{
	m_nTextHeight = 0;
	m_nPageHeight = 1000;
	m_nTotalHeight = 0;
	m_nScrollPos = 0;

	m_bInScrollChanged = FALSE;

	TCHAR tchPath[MAX_PATH];
	m_hInstance = NULL;
	ExpandEnvironmentStrings(_T("%CommonProgramFiles%\\Microsoft Shared\\OFFICE12\\RICHED20.DLL"), tchPath, MAX_PATH);

	m_hInstance = LoadLibrary(tchPath);

	if (!m_hInstance)
	{
		m_hInstance = LoadLibrary(_T("RICHED20.DLL"));
	}
	else
	{
		ExpandEnvironmentStrings(_T("%CommonProgramFiles%\\Microsoft Shared\\OFFICE12\\MSPTLS.DLL"), tchPath, MAX_PATH);
		LoadLibrary(tchPath);
	}

	if (m_hInstance)
	{
	#ifdef _UNICODE
		m_strClass = _T("RichEdit20W");
	#else
		m_strClass = _T("RichEdit20A");
	#endif
	}
}

CScrollRichEditView::~CScrollRichEditView()
{
}


BEGIN_MESSAGE_MAP(CScrollRichEditView, CRichEditView)
	//{{AFX_MSG_MAP(CScrollRichEditView)
	ON_WM_SIZE()
	ON_WM_NCPAINT()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollRichEditView message handlers


#ifndef EM_GETSCROLLPOS
#define EM_GETSCROLLPOS         (WM_USER + 221)
#endif

#ifndef EM_SETSCROLLPOS
#define EM_SETSCROLLPOS         (WM_USER + 222)
#endif

#ifndef EM_SHOWSCROLLBAR
#define EM_SHOWSCROLLBAR		(WM_USER + 96)
#endif

void CScrollRichEditView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	m_nScrollPos = 0;

	SendMessage(EM_SHOWSCROLLBAR, SB_VERT, FALSE);
	SendMessage(EM_SHOWSCROLLBAR, SB_HORZ, FALSE);

	GetRichEditCtrl().SetEventMask(GetRichEditCtrl().GetEventMask()| ENM_SCROLL | ENM_REQUESTRESIZE);

	UpdateScrollInfo();
}

CScrollBar* CScrollRichEditView::GetScrollBarCtrl(int nBar) const
{
	ASSERT(nBar == SB_VERT); 
	UNUSED(nBar);

	if (!AfxGetMainWnd())
		return NULL;

	return &((CWorkspaceView*)GetParent())->m_wndScrollBar[nBar];

}

void CScrollRichEditView::UpdateScrollInfo()
{
	m_nTotalHeight = max(m_nPageHeight, m_nTextHeight + 40 + 10);


	CScrollBar* pScrollBar = GetScrollBarCtrl(SB_VERT);
	if (!pScrollBar)
		return;

	SCROLLINFO si;
	ZeroMemory(&si, sizeof(SCROLLINFO));

	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nPos = m_nScrollPos;

	si.nPage = GetPageSize();
	si.nMax = m_nTotalHeight;

	pScrollBar->SetScrollInfo(&si);

}

void CScrollRichEditView::OnEditScrollChanged()
{
	if (m_bInScrollChanged)	
		return;

	POINT pt;
	GetRichEditCtrl().SendMessage(EM_GETSCROLLPOS, 0, (LPARAM)&pt);

	m_nScrollPos = 40 + pt.y;

	UpdateScrollInfo();
	UpdatePosition();

}

void CScrollRichEditView::OnRequestResize(NMHDR * pNotifyStruct, LRESULT* /*result*/)
{
	REQRESIZE* rs = (REQRESIZE*)pNotifyStruct;

	m_nTextHeight = rs->rc.bottom - rs->rc.top - 3;

	UpdateScrollInfo();
}

void CScrollRichEditView::UpdatePosition()
{
	CRect rc = ((CWorkspaceView*)GetParent())->GetViewRect(CXTPClientRect(GetParent()));
	MoveWindow(rc, TRUE);

	SendMessage(WM_NCPAINT);
}

void CScrollRichEditView::SetScrollPos(int nScrollPos)
{
	int nMaxPos = m_nTotalHeight - GetPageSize() + 1;

	if (nScrollPos > nMaxPos)
		nScrollPos = nMaxPos;
	
	if (nScrollPos < 0)
		nScrollPos = 0;

	if (m_nScrollPos == nScrollPos)
		return;
	
	m_nScrollPos = nScrollPos;

	int nEditScroll = max(0, m_nScrollPos - 40);
	
	m_bInScrollChanged = TRUE;
	POINT pt = {0, nEditScroll};
	SendMessage(EM_SETSCROLLPOS, 0, (LPARAM)&pt);
	m_bInScrollChanged = FALSE;
	
	UpdateScrollInfo();
	UpdatePosition();
}

int CScrollRichEditView::GetPageSize()
{
	return CXTPClientRect(GetParent()).Height() - 50;
}

BOOL CScrollRichEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CRichEditView::PreCreateWindow(cs);
}

void CScrollRichEditView::OnVScroll(UINT nScrollCode, UINT nPos, CScrollBar* /*pScrollBar*/)
{
	int y = GetScrollPos(SB_VERT);

	switch (nScrollCode)
	{
	case SB_TOP:
		y = 0;
		break;
	case SB_BOTTOM:
		y = m_nTotalHeight;
		break;
	case SB_LINEUP:
		y -= 20;
		break;
	case SB_LINEDOWN:
		y += 20;
		break;
	case SB_PAGEUP:
		y -= GetPageSize();
		break;
	case SB_PAGEDOWN:
		y += GetPageSize();
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		y = nPos;
		break;
	}

	SetScrollPos(y);
}

void CScrollRichEditView::OnSize(UINT nType, int cx, int cy) 
{
	CRichEditView::OnSize(nType, cx, cy);
	
	UpdateScrollInfo();	 
}

void CScrollRichEditView::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CRichEditView::CalcWindowRect(lpClientRect, nAdjustType);

	int nWidth = 820;

	int nClientWidth = lpClientRect->right - lpClientRect->left;
	int nBorders = max(8, nClientWidth - nWidth);

	int nTopMargin = max(4, 40 - m_nScrollPos);

	int nBottomMargin = m_nScrollPos + GetPageSize() - m_nTotalHeight + 10;
	nBottomMargin = max(1, nBottomMargin);	

	
	lpClientRect->top += nTopMargin;
	lpClientRect->left += nBorders / 2;
	lpClientRect->right -= nBorders / 2;
	lpClientRect->bottom -= nBottomMargin;

}

void CScrollRichEditView::OnNcPaint() 
{
	CWindowDC dc(this);
	CXTPWindowRect rc(this);
	rc.OffsetRect(-rc.TopLeft());

	int nBottomMargin = m_nScrollPos + GetPageSize() - m_nTotalHeight + 10;

	dc.FillSolidRect(1, 0, rc.Width() - 2, 1, m_nScrollPos < 40 ? 0 : GetXtremeColor(COLOR_WINDOW));
	dc.FillSolidRect(0, 0, 1, rc.Height(), 0);
	dc.FillSolidRect(rc.Width() - 1, 0, 1, rc.Height(), 0);
	dc.FillSolidRect(1, rc.Height() - 1, rc.Width() - 2, 1, nBottomMargin > 0 ? 0 : GetXtremeColor(COLOR_WINDOW));
}

BOOL CScrollRichEditView::OnMouseWheel(UINT /*nFlags*/, short zDelta, CPoint /*pt*/) 
{
	SetScrollPos(m_nScrollPos + (zDelta < 0 ? 60 : -60));
	
	return TRUE;
}
