// PrintPreviewView.cpp : implementation of the CPrintPreviewView class
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PrintPreview.h"

#include "PrintPreviewDoc.h"
#include "PrintPreviewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintPreviewView

IMPLEMENT_DYNCREATE(CPrintPreviewView, CRichEditView)

BEGIN_MESSAGE_MAP(CPrintPreviewView, CRichEditView)
	//{{AFX_MSG_MAP(CPrintPreviewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintPreviewView construction/destruction

CPrintPreviewView::CPrintPreviewView()
{
	// TODO: add construction code here

}

CPrintPreviewView::~CPrintPreviewView()
{
}

BOOL CPrintPreviewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CRichEditView::PreCreateWindow(cs);

	return bPreCreated;
}

void CPrintPreviewView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();
	SetMargins(CRect(720, 720, 720, 720));

	static BOOL bLoadOnce = FALSE;
	if (!bLoadOnce)
	{
		bLoadOnce = TRUE;

		HINSTANCE hInstance = AfxGetInstanceHandle();
		LPCTSTR lpszResourceName = _T("PRINTPREVIEW.RTF");
		LPCTSTR lpszResourceType = _T("RTF");
		
		HRSRC hRsrc = ::FindResource(hInstance, lpszResourceName, lpszResourceType);
		if (hRsrc == NULL)
			return;
		
		HGLOBAL hGlobal = LoadResource(hInstance, hRsrc);
		if (hGlobal == NULL)
			return;
		
		LPCSTR pData = (LPCSTR)LockResource(hGlobal);
		if (pData == NULL)
			return;
		
		DWORD dwSize = (DWORD)SizeofResource(hInstance, hRsrc);
		if (dwSize == 0)
			return;

		CMemFile memRTF((BYTE*)pData, dwSize, 0);
		CArchive ar(&memRTF, CArchive::load | CArchive::bNoFlushOnDelete | CArchive::bNoByteSwap);

		Serialize(ar);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CPrintPreviewView drawing

void CPrintPreviewView::OnDraw(CDC* /*pDC*/)
{
	CPrintPreviewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPrintPreviewView printing

BOOL CPrintPreviewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CRichEditView preparation
	return CRichEditView::DoPreparePrinting(pInfo);
}

void CPrintPreviewView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CRichEditView begin printing.
	CRichEditView::OnBeginPrinting(pDC, pInfo);
}

void CPrintPreviewView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CRichEditView end printing
	CRichEditView::OnEndPrinting(pDC, pInfo);
}

void CPrintPreviewView::OnFilePrintPreview()
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

/////////////////////////////////////////////////////////////////////////////
// CPrintPreviewView diagnostics

#ifdef _DEBUG
void CPrintPreviewView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CPrintPreviewView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CPrintPreviewDoc* CPrintPreviewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrintPreviewDoc)));
	return (CPrintPreviewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrintPreviewView message handlers
