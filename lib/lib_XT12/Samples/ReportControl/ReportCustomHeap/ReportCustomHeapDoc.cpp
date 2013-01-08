// ReportCustomHeapDoc.cpp : implementation of the CReportCustomHeapDoc class
//

#include "stdafx.h"
#include "ReportCustomHeap.h"

#include "ReportCustomHeapDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapDoc

IMPLEMENT_DYNCREATE(CReportCustomHeapDoc, CDocument)

BEGIN_MESSAGE_MAP(CReportCustomHeapDoc, CDocument)
	//{{AFX_MSG_MAP(CReportCustomHeapDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapDoc construction/destruction

CReportCustomHeapDoc::CReportCustomHeapDoc()
{
	// TODO: add one-time construction code here

}

CReportCustomHeapDoc::~CReportCustomHeapDoc()
{
}

BOOL CReportCustomHeapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapDoc serialization

void CReportCustomHeapDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapDoc diagnostics

#ifdef _DEBUG
void CReportCustomHeapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CReportCustomHeapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapDoc commands
