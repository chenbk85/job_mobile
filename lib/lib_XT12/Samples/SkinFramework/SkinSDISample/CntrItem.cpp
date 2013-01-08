// CntrItem.cpp : implementation of the CSkinSDISampleCntrItem class
//

#include "stdafx.h"
#include "SkinSDISample.h"

#include "SkinSDISampleDoc.h"
#include "SkinSDISampleView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleCntrItem implementation

IMPLEMENT_SERIAL(CSkinSDISampleCntrItem, CRichEditCntrItem, 0)

CSkinSDISampleCntrItem::CSkinSDISampleCntrItem(REOBJECT* preo, CSkinSDISampleDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here

}

CSkinSDISampleCntrItem::~CSkinSDISampleCntrItem()
{
	// TODO: add cleanup code here

}

/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleCntrItem diagnostics

#ifdef _DEBUG
void CSkinSDISampleCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CSkinSDISampleCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
