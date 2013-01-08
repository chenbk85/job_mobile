// CommandBarControlsView.cpp : implementation of the CCommandBarControlsView class
//

#include "stdafx.h"
#include "CommandBarControls.h"

#include "CommandBarControlsDoc.h"
#include "CommandBarControlsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView

IMPLEMENT_DYNCREATE(CCommandBarControlsView, CView)

BEGIN_MESSAGE_MAP(CCommandBarControlsView, CView)
	//{{AFX_MSG_MAP(CCommandBarControlsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

	ON_COMMAND(ID_EDIT_COPY, OnEmptyCommand)
	ON_COMMAND(ID_EDIT_CUT, OnEmptyCommand)
	ON_COMMAND(ID_EDIT_PASTE, OnEmptyCommand)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEmptyCommand)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView construction/destruction

CCommandBarControlsView::CCommandBarControlsView()
{
	// TODO: add construction code here

}

CCommandBarControlsView::~CCommandBarControlsView()
{
}

BOOL CCommandBarControlsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView drawing

void CCommandBarControlsView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView printing

BOOL CCommandBarControlsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCommandBarControlsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCommandBarControlsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView diagnostics

#ifdef _DEBUG
void CCommandBarControlsView::AssertValid() const
{
	CView::AssertValid();
}

void CCommandBarControlsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommandBarControlsDoc* CCommandBarControlsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommandBarControlsDoc)));
	return (CCommandBarControlsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsView message handlers


void CCommandBarControlsView::OnEmptyCommand()
{

}
