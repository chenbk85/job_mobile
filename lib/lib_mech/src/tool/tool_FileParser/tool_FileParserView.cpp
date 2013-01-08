// tool_FileParserView.cpp : implementation of the Ctool_FileParserView class
//

#include "stdafx.h"
#include "tool_FileParser.h"

#include "tool_FileParserDoc.h"
#include "tool_FileParserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctool_FileParserView

IMPLEMENT_DYNCREATE(Ctool_FileParserView, CView)

BEGIN_MESSAGE_MAP(Ctool_FileParserView, CView)
END_MESSAGE_MAP()

// Ctool_FileParserView construction/destruction

Ctool_FileParserView::Ctool_FileParserView()
{
	// TODO: add construction code here

}

Ctool_FileParserView::~Ctool_FileParserView()
{
}

BOOL Ctool_FileParserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ctool_FileParserView drawing

void Ctool_FileParserView::OnDraw(CDC* /*pDC*/)
{
	Ctool_FileParserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Ctool_FileParserView diagnostics

#ifdef _DEBUG
void Ctool_FileParserView::AssertValid() const
{
	CView::AssertValid();
}

void Ctool_FileParserView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctool_FileParserDoc* Ctool_FileParserView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctool_FileParserDoc)));
	return (Ctool_FileParserDoc*)m_pDocument;
}
#endif //_DEBUG


// Ctool_FileParserView message handlers
