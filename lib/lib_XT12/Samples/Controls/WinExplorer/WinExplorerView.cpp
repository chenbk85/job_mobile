// WinExplorerView.cpp : implementation of the CWinExplorerView class
//

#include "stdafx.h"
#include "WinExplorer.h"

#include "WinExplorerDoc.h"
#include "WinExplorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerView

IMPLEMENT_DYNCREATE(CWinExplorerView, CView)

BEGIN_MESSAGE_MAP(CWinExplorerView, CView)
	//{{AFX_MSG_MAP(CWinExplorerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerView construction/destruction

CWinExplorerView::CWinExplorerView()
{
	// TODO: add construction code here

}

CWinExplorerView::~CWinExplorerView()
{
}

BOOL CWinExplorerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerView drawing

void CWinExplorerView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerView printing

BOOL CWinExplorerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWinExplorerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWinExplorerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerView diagnostics

#ifdef _DEBUG
void CWinExplorerView::AssertValid() const
{
	CView::AssertValid();
}

void CWinExplorerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinExplorerDoc* CWinExplorerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinExplorerDoc)));
	return (CWinExplorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerView message handlers
