// ToolTipContextView.cpp : implementation of the CToolTipContextView class
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
#include "ToolTipContext.h"

#include "ToolTipContextDoc.h"
#include "ToolTipContextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipContextView

IMPLEMENT_DYNCREATE(CToolTipContextView, CView)

BEGIN_MESSAGE_MAP(CToolTipContextView, CView)
	//{{AFX_MSG_MAP(CToolTipContextView)
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipContextView construction/destruction

CToolTipContextView::CToolTipContextView()
{
	m_pTooltipContext = new CXTPToolTipContext();
#ifdef _HTML
	m_pTooltipContext->SetStyle(xtpToolTipHTML);
#else
	m_pTooltipContext->SetStyle(xtpToolTipMarkup);
#endif
	m_pTooltipContext->SetTipBkColor(0xFFFFFF);
	m_pTooltipContext->SetMargin(CRect(-3, -3, -3, -3));
}

CToolTipContextView::~CToolTipContextView()
{
	for (int i = 0; i < m_arrCircles.GetSize(); i++)
	{
		delete m_arrCircles[i];
	}
	m_arrCircles.RemoveAll();

	delete m_pTooltipContext;
}

BOOL CToolTipContextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CToolTipContextView drawing

void CToolTipContextView::OnDraw(CDC* pDC)
{
	for (int i = 0; i < (int)m_arrCircles.GetSize(); i++)
	{
		m_arrCircles[i]->Draw(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToolTipContextView printing

BOOL CToolTipContextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CToolTipContextView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CToolTipContextView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CToolTipContextView diagnostics

#ifdef _DEBUG
void CToolTipContextView::AssertValid() const
{
	CView::AssertValid();
}

void CToolTipContextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolTipContextDoc* CToolTipContextView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolTipContextDoc)));
	return (CToolTipContextDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolTipContextView message handlers

void CToolTipContextView::OnRButtonDown(UINT /*nFlags*/, CPoint point) 
{
	ClientToScreen(&point);
	
	((CXTPMDIFrameWnd*)AfxGetMainWnd())->GetCommandBars()->
		TrackPopupMenu(IDR_CONTEXT_MENU, TPM_RIGHTBUTTON , point.x, point.y);
}

BOOL CToolTipContextView::OnEraseBkgnd(CDC* /*pDC*/) 
{	
	return TRUE;
}

void CToolTipContextView::OnPaint() 
{
	CPaintDC dcPaint(this); // device context for painting
	
	CXTPBufferDC dc(dcPaint);
	dc.FillSolidRect(CXTPClientRect(this), GetSysColor(COLOR_WINDOW));

	OnDraw(&dc);
}

void CToolTipContextView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	CXTPClientRect rc(this);

	for (int i = 0; i < 8; i++)
	{
		CPoint ptCenter(rand() % rc.Width(), rand() % rc.Height());
		int nRadius = 20 + rand() % 200;
		COLORREF clr = CXTPTabPaintManager::GetOneNoteColor((XTPTabOneNoteColor)(xtpTabColorBlue + i));
	
		CCircle* pCircle = new CCircle(ptCenter, nRadius, clr);
		m_arrCircles.Add(pCircle);
	}
	
}


CCircle* CToolTipContextView::HitTest(const CPoint& Point) const
{
     for (int n = (int)m_arrCircles.GetSize() - 1; n >= 0; n--)
     {
         if (m_arrCircles[n]->HitTest(Point))
         {
             return m_arrCircles[n];
         }
     }
     return NULL;
 }

BOOL CToolTipContextView::PreTranslateMessage(MSG* pMsg) 
{
	m_pTooltipContext->FilterToolTipMessage(this, pMsg);
	
	return CView::PreTranslateMessage(pMsg);
}

CString ColorToHtml(COLORREF clr)
{
	CString str;
	str.Format(_T("#%0.2x%0.2x%0.2x"), GetRValue(clr), GetGValue(clr), GetBValue(clr));
	return str;
}

CString CCircle::GetTooltip()
{
	CString strCenter; strCenter.Format(_T("(%i, %i)"), m_ptCenter.x, m_ptCenter.y);
	CString strRadius; strRadius.Format(_T("%i"), m_nRadius);
	CString strColor; strColor.Format(_T("(%i, %i, %i)"), GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
	
	CString strHTML;
#ifdef _HTML
	strHTML.Format(
		_T("<table cellpadding=4 cellspacing=0 border=1 bordercolor=#808080>")
		_T("<tr><td bgColor=#e0e0e0>Center:</td><td>%s</td></tr>")
		_T("<tr><td bgColor=#e0e0e0>Radius:</td><td>%s</td></tr>")
		_T("<tr><td bgColor=#e0e0e0>Color:</td><td bgcolor=%s>%s</td></tr></table>"), 
		(LPCTSTR)strCenter, (LPCTSTR)strRadius, (LPCTSTR)ColorToHtml(m_clr), (LPCTSTR)strColor);
#else
	strHTML.Format(
		_T("<Border BorderThickness='1' BorderBrush='#808080'>")
		_T("<Grid>")
		_T("<Grid.ColumnDefinitions><ColumnDefinition Width='Auto'/><ColumnDefinition Width='Auto'/></Grid.ColumnDefinitions>")
		_T("<Grid.RowDefinitions><RowDefinition/><RowDefinition/><RowDefinition/></Grid.RowDefinitions>")
		_T("<Border Padding='3' Grid.Column='0' Grid.Row='0' BorderThickness='1' Background='#e0e0e0' BorderBrush='#808080'><TextBlock Text='Center:'/></Border>")
		_T("<Border Padding='3' Grid.Column='0' Grid.Row='1' BorderThickness='1' Background='#e0e0e0' BorderBrush='#808080'><TextBlock Text='Radius:'/></Border>")
		_T("<Border Padding='3' Grid.Column='0' Grid.Row='2' BorderThickness='1' Background='#e0e0e0' BorderBrush='#808080'><TextBlock Text='Color:'/></Border>")
		_T("<Border Padding='3' Grid.Column='1' Grid.Row='0' BorderThickness='1' Background='White' BorderBrush='#808080'><TextBlock Text='%s'/></Border>")
		_T("<Border Padding='3' Grid.Column='2' Grid.Row='1' BorderThickness='1' Background='White' BorderBrush='#808080'><TextBlock Text='%s'/></Border>")
		_T("<Border Padding='3' Grid.Column='3' Grid.Row='2' BorderThickness='1' Background='%s' BorderBrush='#808080'><TextBlock Text='%s'/></Border>")
		_T("</Grid>")
		_T("</Border>"),
		
		(LPCTSTR)strCenter, (LPCTSTR)strRadius, (LPCTSTR)ColorToHtml(m_clr), (LPCTSTR)strColor);

#endif
	
	return strHTML;
}

INT_PTR CToolTipContextView::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{

	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));

	// check child windows first by calling CControlBar
	INT_PTR nHit = CWnd::OnToolHitTest(point, pTI);
	if (nHit != -1)
		return nHit;

	CCircle* pCircle = HitTest(point);
	if (pCircle)
	{
		nHit = (INT_PTR)pCircle;
		
		CString strTip = pCircle->GetTooltip();
		if (strTip.GetLength() == 0)
			return -1;
		
		CXTPToolTipContext::FillInToolInfo(pTI, m_hWnd, pCircle->GetRect(),
			nHit, strTip);
		
		return nHit;
	}
	return -1;
}
