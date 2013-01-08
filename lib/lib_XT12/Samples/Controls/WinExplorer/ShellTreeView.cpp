// ShellTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "WinExplorer.h"
#include "ShellTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShellTreeView

IMPLEMENT_DYNCREATE(CShellTreeView, CXTShellTreeView)

CShellTreeView::CShellTreeView()
{
}

CShellTreeView::~CShellTreeView()
{
}


BEGIN_MESSAGE_MAP(CShellTreeView, CXTShellTreeView)
	//{{AFX_MSG_MAP(CShellTreeView)
 	ON_WM_NCCALCSIZE()
 	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShellTreeView drawing

void CShellTreeView::OnDraw(CDC* /*pDC*/)
{
}


void CShellTreeView::OnInitialUpdate()
{
	CXTShellTreeView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CShellTreeView diagnostics

#ifdef _DEBUG
void CShellTreeView::AssertValid() const
{
	CXTShellTreeView::AssertValid();
}

void CShellTreeView::Dump(CDumpContext& dc) const
{
	CXTShellTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShellTreeView message handlers

void CShellTreeView::SelectParentItem()
{
    if (::IsWindow(GetTreeCtrl().m_hWnd))
    {
        HTREEITEM htItem = GetTreeCtrl().GetSelectedItem();
        if (htItem != GetTreeCtrl().GetRootItem())
        {
            GetTreeCtrl().SelectItem(GetTreeCtrl().GetParentItem(htItem));
            GetTreeCtrl().SetFocus();
        }
    }
}

BOOL CShellTreeView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CXTShellTreeView::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_STATICEDGE;
	
	return TRUE;
}

#define CY_CAPTION	20

void CShellTreeView::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	lpncsp->rgrc[0].top += CY_CAPTION + 1;
	CXTShellTreeView::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CShellTreeView::OnNcPaint() 
{
	// code block: paint scrollbars first.
	{
		Default();
	}

	CWindowDC dc(this);

	CXTPWindowRect rWindow(this);
	rWindow.OffsetRect(-rWindow.TopLeft());

	dc.Draw3dRect(&rWindow, GetXtremeColor(COLOR_3DSHADOW), GetXtremeColor(COLOR_3DHIGHLIGHT));

	// draw psudo caption.
	rWindow.DeflateRect(1, 1);
	rWindow.bottom = rWindow.top + CY_CAPTION;

	dc.FillSolidRect(rWindow.left, rWindow.bottom, rWindow.Width(), 1, GetXtremeColor(COLOR_WINDOW));

	CXTPBufferDC memDC(dc, rWindow);

	memDC.FillSolidRect(rWindow, GetXtremeColor(COLOR_3DFACE));	
	memDC.Draw3dRect(&rWindow, GetXtremeColor(COLOR_3DHIGHLIGHT), GetXtremeColor(COLOR_3DSHADOW));

	CXTPFontDC fontDC(&memDC, &XTAuxData().font);

	rWindow.DeflateRect(4,2);
	memDC.SetBkMode(TRANSPARENT);
	memDC.DrawText(_T("Folders"), &rWindow, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
}
