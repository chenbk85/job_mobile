// ExcelTabDoc.cpp : implementation of the CExcelTabDoc class
//

#include "stdafx.h"
#include "ExcelTab.h"

#include "ExcelTabDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExcelTabDoc

IMPLEMENT_DYNCREATE(CExcelTabDoc, CDocument)

BEGIN_MESSAGE_MAP(CExcelTabDoc, CDocument)
	//{{AFX_MSG_MAP(CExcelTabDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelTabDoc construction/destruction

CExcelTabDoc::CExcelTabDoc()
{
	// TODO: add one-time construction code here

}

CExcelTabDoc::~CExcelTabDoc()
{
}

BOOL CExcelTabDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExcelTabDoc serialization

void CExcelTabDoc::Serialize(CArchive& ar)
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
// CExcelTabDoc diagnostics

#ifdef _DEBUG
void CExcelTabDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExcelTabDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExcelTabDoc commands
