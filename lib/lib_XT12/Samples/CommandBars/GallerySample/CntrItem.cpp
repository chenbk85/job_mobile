// CntrItem.cpp : implementation of the CGallerySampleCntrItem class
//

#include "stdafx.h"
#include "GallerySample.h"

#include "GallerySampleDoc.h"
#include "GallerySampleView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGallerySampleCntrItem implementation

IMPLEMENT_SERIAL(CGallerySampleCntrItem, CRichEditCntrItem, 0)

CGallerySampleCntrItem::CGallerySampleCntrItem(REOBJECT* preo, CGallerySampleDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CGallerySampleCntrItem::~CGallerySampleCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CGallerySampleCntrItem diagnostics

#ifdef _DEBUG
void CGallerySampleCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CGallerySampleCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
