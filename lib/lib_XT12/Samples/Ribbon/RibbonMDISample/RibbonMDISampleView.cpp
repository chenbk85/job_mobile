// RibbonMDISampleView.cpp : implementation of the CRibbonMDISampleView class
//

#include "stdafx.h"
#include "RibbonMDISample.h"

#include "RibbonMDISampleDoc.h"
#include "CntrItem.h"
#include "RibbonMDISampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView

IMPLEMENT_DYNCREATE(CRibbonMDISampleView, CRichEditView)

BEGIN_MESSAGE_MAP(CRibbonMDISampleView, CRichEditView)
	//{{AFX_MSG_MAP(CRibbonMDISampleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView construction/destruction

CRibbonMDISampleView::CRibbonMDISampleView()
{
	// TODO: add construction code here

}

CRibbonMDISampleView::~CRibbonMDISampleView()
{
}

BOOL CRibbonMDISampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CRibbonMDISampleView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView printing

BOOL CRibbonMDISampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CRibbonMDISampleView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView diagnostics

#ifdef _DEBUG
void CRibbonMDISampleView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CRibbonMDISampleView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CRibbonMDISampleDoc* CRibbonMDISampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRibbonMDISampleDoc)));
	return (CRibbonMDISampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleView message handlers

void CRibbonMDISampleView::OnFilePrintPreview()
{
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.

	// must not create this on the frame.  Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;

	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.

	if ( !DoPrintPreview( XTP_IDD_PREVIEW_DIALOGBAR, this,
		RUNTIME_CLASS( CXTPPreviewView ), pState ))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		TRACE0( "Error: DoPrintPreview failed.\n" );
		AfxMessageBox( AFX_IDP_COMMAND_FAILURE );
		delete pState;      // preview failed to initialize, delete State now

	}
}
