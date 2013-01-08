// CntrItem.cpp : implementation of the CActionsSampleCntrItem class
//

#include "stdafx.h"
#include "ActionsSample.h"

#include "ActionsSampleDoc.h"
#include "ActionsSampleView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleCntrItem implementation

IMPLEMENT_SERIAL(CActionsSampleCntrItem, CRichEditCntrItem, 0)

CActionsSampleCntrItem::CActionsSampleCntrItem(REOBJECT* preo, CActionsSampleDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CActionsSampleCntrItem::~CActionsSampleCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleCntrItem diagnostics

#ifdef _DEBUG
void CActionsSampleCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CActionsSampleCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
