// SkinMDISampleDoc.cpp : implementation of the CSkinMDISampleDoc class
//

#include "stdafx.h"
#include "SkinMDISample.h"

#include "SkinMDISampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleDoc

IMPLEMENT_DYNCREATE(CSkinMDISampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CSkinMDISampleDoc, CDocument)
	//{{AFX_MSG_MAP(CSkinMDISampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleDoc construction/destruction

CSkinMDISampleDoc::CSkinMDISampleDoc()
{
	// TODO: add one-time construction code here

}

CSkinMDISampleDoc::~CSkinMDISampleDoc()
{
}

BOOL CSkinMDISampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleDoc serialization

void CSkinMDISampleDoc::Serialize(CArchive& ar)
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
// CSkinMDISampleDoc diagnostics

#ifdef _DEBUG
void CSkinMDISampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSkinMDISampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkinMDISampleDoc commands
