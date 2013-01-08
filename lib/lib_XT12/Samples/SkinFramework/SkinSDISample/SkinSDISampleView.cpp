// SkinSDISampleView.cpp : implementation of the CSkinSDISampleView class
//

#include "stdafx.h"
#include "SkinSDISample.h"

#include "SkinSDISampleDoc.h"
#include "CntrItem.h"
#include "SkinSDISampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleView

IMPLEMENT_DYNCREATE(CSkinSDISampleView, CRichEditView)

BEGIN_MESSAGE_MAP(CSkinSDISampleView, CRichEditView)
	//{{AFX_MSG_MAP(CSkinSDISampleView)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleView construction/destruction

CSkinSDISampleView::CSkinSDISampleView()
{
	// TODO: add construction code here

}

CSkinSDISampleView::~CSkinSDISampleView()
{
}

BOOL CSkinSDISampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CSkinSDISampleView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));	

	static BOOL bFirstRun = TRUE;
	
	if (bFirstRun)
	{		
		for (int i = 0; i < 50; i++)
		{
			CString str;
			str.Format(_T("Line %i\n"), i);
			
			GetRichEditCtrl().ReplaceSel(str);
		}
		bFirstRun = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleView printing

BOOL CSkinSDISampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CSkinSDISampleView::OnDestroy()
{
	CRichEditView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleView diagnostics

#ifdef _DEBUG
void CSkinSDISampleView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CSkinSDISampleView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CSkinSDISampleDoc* CSkinSDISampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSkinSDISampleDoc)));
	return (CSkinSDISampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkinSDISampleView message handlers

int CSkinSDISampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
