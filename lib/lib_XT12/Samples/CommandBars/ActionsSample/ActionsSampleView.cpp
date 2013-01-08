// ActionsSampleView.cpp : implementation of the CActionsSampleView class
//

#include "stdafx.h"
#include "ActionsSample.h"

#include "ActionsSampleDoc.h"
#include "CntrItem.h"
#include "ActionsSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView

IMPLEMENT_DYNCREATE(CActionsSampleView, CRichEditView)

BEGIN_MESSAGE_MAP(CActionsSampleView, CRichEditView)
	//{{AFX_MSG_MAP(CActionsSampleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)

	ON_NOTIFY_REFLECT(EN_SELCHANGE, OnSelChange)

	ON_COMMAND(ID_CHAR_BOLD, OnCharBold)
	ON_COMMAND(ID_CHAR_ITALIC, OnCharItalic)
	ON_COMMAND(ID_CHAR_UNDERLINE, OnCharUnderline)

	ON_COMMAND(ID_PARA_CENTER, CRichEditView::OnParaCenter)
	ON_UPDATE_COMMAND_UI(ID_PARA_CENTER, CRichEditView::OnUpdateParaCenter)
	ON_COMMAND(ID_PARA_LEFT, CRichEditView::OnParaLeft)
	ON_UPDATE_COMMAND_UI(ID_PARA_LEFT, CRichEditView::OnUpdateParaLeft)
	ON_COMMAND(ID_PARA_RIGHT, CRichEditView::OnParaRight)
	ON_UPDATE_COMMAND_UI(ID_PARA_RIGHT, CRichEditView::OnUpdateParaRight)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView construction/destruction

CActionsSampleView::CActionsSampleView()
{
	// TODO: add construction code here

}

CActionsSampleView::~CActionsSampleView()
{
}

BOOL CActionsSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CActionsSampleView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	USES_CONVERSION;

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));

	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	
	CString strDefFont = _T("Tahoma");
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD |CFM_ITALIC | CFM_UNDERLINE | CFM_STRIKEOUT | CFM_SIZE |
		CFM_COLOR | CFM_OFFSET | CFM_PROTECTED | CFM_FACE;
	cf.dwEffects = CFE_AUTOCOLOR;
	cf.yHeight = 200; //10pt
	cf.bPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

#if (_RICHEDIT_VER >= 0x0200)
	lstrcpyn(cf.szFaceName, strDefFont, LF_FACESIZE);
#else
	lstrcpynA(cf.szFaceName, T2A((LPTSTR) (LPCTSTR) strDefFont), LF_FACESIZE);
#endif

	GetRichEditCtrl().SetDefaultCharFormat(cf);

}

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView printing

BOOL CActionsSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CActionsSampleView::OnDestroy()
{
   CRichEditView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView diagnostics

#ifdef _DEBUG
void CActionsSampleView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CActionsSampleView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CActionsSampleDoc* CActionsSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CActionsSampleDoc)));
	return (CActionsSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleView message handlers

void CActionsSampleView::OnCharBold()
{
	CRichEditView::OnCharBold();
	UpdateActionsState();
}

void CActionsSampleView::OnCharItalic()
{
	CRichEditView::OnCharItalic();
	UpdateActionsState();
}

void CActionsSampleView::OnCharUnderline()
{
	CRichEditView::OnCharUnderline();
	UpdateActionsState();
}


void CActionsSampleView::OnSelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	CRichEditView::OnSelChange(pNMHDR, pResult);

	UpdateActionsState();
}

void CActionsSampleView::UpdateActionsState()
{
	CHARFORMAT& cfm = GetCharFormatSelection();

	CXTPCommandBars* pCommandBars = ((CXTPFrameWnd*)GetParentFrame())->GetCommandBars();

	pCommandBars->GetActions()->FindAction(ID_CHAR_BOLD)->SetChecked(
		(cfm.dwMask & CFM_BOLD ? (cfm.dwEffects & CFE_BOLD ? 1 : 0) : 2));
	
	pCommandBars->GetActions()->FindAction(ID_CHAR_ITALIC)->SetChecked(
		(cfm.dwMask & CFM_ITALIC ? (cfm.dwEffects & CFE_ITALIC ? 1 : 0) : 2));

	pCommandBars->GetActions()->FindAction(ID_CHAR_UNDERLINE)->SetChecked(
		(cfm.dwMask & CFM_UNDERLINE ? (cfm.dwEffects & CFE_UNDERLINE ? 1 : 0) : 2));

}
