// MarkupPadView.cpp : implementation of the CMarkupPadView class
//

#include "stdafx.h"
#include "MarkupPad.h"

#include "MarkupPadDoc.h"
#include "MarkupPadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadView

IMPLEMENT_DYNCREATE(CMarkupPadView, CView)

BEGIN_MESSAGE_MAP(CMarkupPadView, CView)
	//{{AFX_MSG_MAP(CMarkupPadView)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadView construction/destruction


void StaticSetText2(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	((CXTPMarkupTextBlock*)pSender)->SetText(L"Column4");
}


CMarkupPadView::CMarkupPadView()
{
	m_pUIElement = NULL;
	m_bInRender = FALSE;

	AddHandler(CXTPMarkupHyperlink::m_pClickEvent, CreateMarkupClassDelegate(this, &CMarkupPadView::OnHyperlinkClick));

	SetDelegate(L"Border_MouseLeftButtonUp", CreateMarkupClassDelegate(this, &CMarkupPadView::OnBorderMouseLeftButtonUp));
	SetDelegate(L"TextBlock_MouseLeftButtonUp", CreateMarkupClassDelegate(this, &CMarkupPadView::OnTextBlockMouseLeftButtonUp));
	SetDelegate(L"Run_MouseLeftButtonUp", CreateMarkupClassDelegate(this, &CMarkupPadView::OnRunMouseLeftButtonUp));

	SetDelegate(L"MakeShapeRed", CreateMarkupClassDelegate(this, &CMarkupPadView::OnMakeShapeRed));
	SetDelegate(L"MakeShapeGreen", CreateMarkupClassDelegate(this, &CMarkupPadView::OnMakeShapeGreen));

	SetDelegate(L"MakeTextBold", CreateMarkupClassDelegate(this, &CMarkupPadView::OnMakeTextBold));
	SetDelegate(L"MakeTextNormal", CreateMarkupClassDelegate(this, &CMarkupPadView::OnMakeTextNormal));
	SetDelegate(L"MakeTextYellow", CreateMarkupClassDelegate(this, &CMarkupPadView::OnMakeTextYellow));
	SetDelegate(L"MakeTextGreen", CreateMarkupClassDelegate(this, &CMarkupPadView::OnMakeTextGreen));
	SetDelegate(L"MoveColumn3", CreateMarkupClassDelegate(this, &CMarkupPadView::OnMoveColumn3));
	SetDelegate(L"HideColumn4", CreateMarkupClassDelegate(this, &CMarkupPadView::OnHideColumn4));
	SetDelegate(L"ShowColumn4", CreateMarkupClassDelegate(this, &CMarkupPadView::OnShowColumn4));
	SetDelegate(L"SetText1", CreateMarkupClassDelegate(this, &CMarkupPadView::OnSetText1));
	SetDelegate(L"ToggleNextControl", CreateMarkupClassDelegate(this, &CMarkupPadView::ToggleNextControl));
	
	SetDelegate(L"SetText2", CreateMarkupClassDelegate(this, &CMarkupPadView::OnSetText2));

	//SetDelegate(L"SetText2", CreateMarkupFunctionDelegate(&StaticSetText2));
}

CMarkupPadView::~CMarkupPadView()
{
	MARKUP_RELEASE(m_pUIElement);
}

BOOL CMarkupPadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadView drawing

void CMarkupPadView::CreateCodeMarkup()
{
	_int64 nPerfomanceEnd;
	_int64 nPerfomanceStart;

	QueryPerformanceCounter((LARGE_INTEGER*)&nPerfomanceStart);


	CXTPMarkupPage* pPage = MARKUP_CREATE(CXTPMarkupPage, this);

	CXTPMarkupBorder* pBorder = MARKUP_CREATE(CXTPMarkupBorder, this);


	pBorder->SetMargin(5);
	pBorder->SetPadding(5);
	pBorder->SetBorderThickness(10);
	pBorder->SetBackground(new CXTPMarkupSolidColorBrush(RGB(0, 0, 0xFF)));
	pBorder->SetBorderBrush(new CXTPMarkupSolidColorBrush(RGB(0, 0xFF, 00)));

	CXTPMarkupBorder* pBorder2 = MARKUP_CREATE(CXTPMarkupBorder, this);
	pBorder2->SetMargin(1);
	pBorder2->SetPadding(8);
	pBorder2->SetBorderThickness(1);
	pBorder2->SetBackground(new CXTPMarkupSolidColorBrush(0xFFFFFF));
	pBorder2->SetBorderBrush(new CXTPMarkupSolidColorBrush(RGB(0xFF, 0, 0 )));
	pBorder->SetChild(pBorder2);
	
	pPage->SetContent(pBorder);

	CXTPMarkupBorder* pBorder3 = MARKUP_CREATE(CXTPMarkupBorder, this);
	pBorder3->SetBackground(new CXTPMarkupSolidColorBrush(0));
	pBorder3->SetHorizontalAlignment(xtpMarkupHorizontalAlignmentRight);
	//pBorder3->SetPadding(CXTPMarkupThickness(10));
	pBorder3->SetVerticalAlignment(xtpMarkupVerticalAlignmentBottom);
	//pBorder3->SetWidth(40);
	//pBorder3->SetHeight(40);
	pBorder2->SetChild(pBorder3);
	pBorder3->SetPadding(10);

	CXTPMarkupStackPanel* pStack = MARKUP_CREATE(CXTPMarkupStackPanel, this);
	CXTPMarkupTextElement::SetForeground(pPage, new CXTPMarkupSolidColorBrush(RGB(0x80, 0x80, 0x80)));


	CXTPMarkupTextBlock* pTextBlock1 = MARKUP_CREATE(CXTPMarkupTextBlock, this);
	pTextBlock1->SetTextWrapping(1);
	pTextBlock1->SetText(L"You can increment or decrement the value of this"  
                 L"textbox by simply clicking the mouse, hold and drag"
                 L"up or down, right or left. Release when happy,with the value.");
	pTextBlock1->SetMargin(5, 0, 5, 0);
	pTextBlock1->SetBackground(new CXTPMarkupSolidColorBrush(RGB(0xFF, 0, 0)));
	pTextBlock1->SetForeground(new CXTPMarkupSolidColorBrush(RGB(0xFF, 0xFF, 0xFF)));

	pStack->GetChildren()->Add(pTextBlock1);

	CXTPMarkupTextBlock* pTextBlock2 = MARKUP_CREATE(CXTPMarkupTextBlock, this);
	pTextBlock2->SetText(L"Hi!");

	pTextBlock2->SetBackground(new CXTPMarkupSolidColorBrush(RGB(0xFF, 0, 0)));
	pTextBlock2->SetForeground(new CXTPMarkupSolidColorBrush(RGB(0xFF, 0xFF, 0)));

	pStack->GetChildren()->Add(pTextBlock2);

	CXTPMarkupTextBlock* pTextBlock3 = MARKUP_CREATE(CXTPMarkupTextBlock, this);
	pTextBlock3->SetTextAlignment(xtpMarkupTextAlignmentCenter);
	pTextBlock3->SetTextWrapping(1);

	CXTPMarkupRun* pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L"1234");
	pRun->SetForeground(new CXTPMarkupSolidColorBrush(RGB(0xFF, 0xFF, 0)));
	pTextBlock3->GetInlines()->Add(pRun);
	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L" ");
	pTextBlock3->GetInlines()->Add(pRun);
	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L"345");
	pRun->SetForeground(new CXTPMarkupSolidColorBrush(RGB(0xFF, 0xFF, 0xFF)));
	pTextBlock3->GetInlines()->Add(pRun);
	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L" ");
	pTextBlock3->GetInlines()->Add(pRun);
	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L"What?");
	pTextBlock3->GetInlines()->Add(pRun);
	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L"Big Link Object HAHAHA?");
	pTextBlock3->GetInlines()->Add(pRun);
	pRun->SetForeground(new CXTPMarkupSolidColorBrush(RGB(0, 0, 0xFF)));

	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L" 1234");
	pRun->SetForeground(new CXTPMarkupSolidColorBrush(RGB(0xFF, 0xFF, 0)));
	pRun->SetBackground(new CXTPMarkupSolidColorBrush(RGB(0, 0xFF, 0)));
	pTextBlock3->GetInlines()->Add(pRun);

	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L" 345\n");
	pRun->SetForeground(new CXTPMarkupSolidColorBrush(RGB(0xFF, 0xFF, 0xFF)));
	pTextBlock3->GetInlines()->Add(pRun);

	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L"Hi\nEEEE ew");
	pTextBlock3->GetInlines()->Add(pRun);

	pTextBlock3->GetInlines()->Add(MARKUP_CREATE(CXTPMarkupLineBreak, this));
	
	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L"Hi");
	pTextBlock3->GetInlines()->Add(pRun);
	
	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L"edede");
	pRun->SetFontSize(20);
	pTextBlock3->GetInlines()->Add(pRun);

	pStack->GetChildren()->Add(pTextBlock3);

	CXTPMarkupStackPanel* pStack2 = MARKUP_CREATE(CXTPMarkupStackPanel, this);
	CXTPMarkupTextElement::SetForeground(pStack2, new CXTPMarkupSolidColorBrush(RGB(0x30, 0x30, 0x30)));

	CXTPMarkupBorder* pBorder4 = MARKUP_CREATE(CXTPMarkupBorder, this);
	pBorder4->SetBackground(new CXTPMarkupSolidColorBrush(0xFF00FF));
	pBorder4->SetBorderBrush(new CXTPMarkupSolidColorBrush(0));
	pBorder4->SetBorderThickness(1);

	CXTPMarkupTextBlock* pTextBlock4 = MARKUP_CREATE(CXTPMarkupTextBlock, this);
	pTextBlock4->SetTextWrapping(1);

	CXTPMarkupBold* pBoldInline = MARKUP_CREATE(CXTPMarkupBold, this);

	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L"Test Size!!!");
	pRun->SetBackground(0xFF);
	pRun->SetFontSize(30);
	pBoldInline->GetInlines()->Add(pRun);
	
	//pBoldInline->GetInlines()->Add(new CXTPMarkupLineBreak());

	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L" Test Family!!!");
	pRun->SetFontFamily(L"Courier New");
	pBoldInline->GetInlines()->Add(pRun);

	CXTPMarkupInlineUIContainer* pInlineContainer = MARKUP_CREATE(CXTPMarkupInlineUIContainer, this);
	
	CXTPMarkupBorder* pBorder5 = MARKUP_CREATE(CXTPMarkupBorder, this);
	pBorder5->SetBackground(new CXTPMarkupSolidColorBrush(0xFFFF00));
	pBorder5->SetBorderBrush(new CXTPMarkupSolidColorBrush(0xFF));
	pBorder5->SetWidth(10);
	pBorder5->SetHeight(10);
	//pBorder5->SetMargin(8);
	pBorder5->SetBorderThickness(1);	
	
	pInlineContainer->SetChild(pBorder5);


	pBoldInline->GetInlines()->Add(pInlineContainer);

	CXTPMarkupItalic* pItalicInline = MARKUP_CREATE(CXTPMarkupItalic, this);

	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L" Test Italic!!!");
	
	pItalicInline->GetInlines()->Add(pRun);

	pBoldInline->GetInlines()->Add(pItalicInline);



	pTextBlock4->GetInlines()->Add(pBoldInline);

	CXTPMarkupUnderline* pUnderlineInline = MARKUP_CREATE(CXTPMarkupUnderline, this);
	pRun = MARKUP_CREATE(CXTPMarkupRun, this);
	pRun->SetText(L" Test Underline!!!");
	pUnderlineInline->GetInlines()->Add(pRun);

	pTextBlock4->GetInlines()->Add(pUnderlineInline);

	pBorder4->SetChild(pTextBlock4);

	pStack2->GetChildren()->Add(pBorder4);

	pStack2->GetChildren()->Add(pStack); 

	pBorder3->SetChild(pStack2);

	QueryPerformanceCounter((LARGE_INTEGER*)&nPerfomanceEnd);
	TRACE(_T("Parse   = %i \n"), int(nPerfomanceEnd - nPerfomanceStart));

	MARKUP_RELEASE(m_pUIElement);
	m_pUIElement = pPage;
}

BOOL CMarkupPadView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (m_pUIElement)
	{
		if (CXTPMarkupContext::OnWndMsg(m_pUIElement, message, wParam, lParam, pResult))
			return TRUE;
	}

	return CView::OnWndMsg(message, wParam, lParam, pResult);
}

void CMarkupPadView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//MARKUP_RELEASE(m_pUIElement);
	m_hContextWnd = m_hWnd;
}


void CMarkupPadView::OnDraw(CDC* /*pDC*/)
{
	ASSERT(FALSE);
}

void CMarkupPadView::DrawMarkup(CXTPMarkupDrawingContext* pDC, CRect rc)
{
	CXTPMarkupUIElement* pElement = m_pUIElement;
	
	if (!pElement)
		return;	

	if (m_bInRender)
		return;

	m_bInRender = TRUE;

	_int64 nPerfomanceEnd;
	_int64 nPerfomanceStart;

	QueryPerformanceCounter((LARGE_INTEGER*)&nPerfomanceStart);
	
	pElement->Measure(pDC, rc.Size());
	pElement->Arrange(rc);

	QueryPerformanceCounter((LARGE_INTEGER*)&nPerfomanceEnd);
	int nArrange = int(nPerfomanceEnd - nPerfomanceStart);

	nPerfomanceStart = nPerfomanceEnd;


	pElement->Render(pDC);

	QueryPerformanceCounter((LARGE_INTEGER*)&nPerfomanceEnd);
	int nRender = int(nPerfomanceEnd - nPerfomanceStart);

	TRACE(_T("Arrange = %i \n"), nArrange);
	TRACE(_T("Render  = %i \n"), nRender);

	if (pElement->FindName(L"Test"))
	{
		TRACE(_T("Name Found \n"));
	}

	m_bInRender = FALSE;
}


void CMarkupPadView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CXTPMarkupPrintingContext dc(pDC->m_hDC, pDC->m_hAttribDC);
	DrawMarkup(&dc, pInfo->m_rectDraw);
}


/////////////////////////////////////////////////////////////////////////////
// CMarkupPadView printing

BOOL CMarkupPadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->m_nNumPreviewPages = 1;
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);


	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMarkupPadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMarkupPadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadView diagnostics

#ifdef _DEBUG
void CMarkupPadView::AssertValid() const
{
	CView::AssertValid();
}

void CMarkupPadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMarkupPadDoc* CMarkupPadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMarkupPadDoc)));
	return (CMarkupPadDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadView message handlers

BOOL CMarkupPadView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

void CMarkupPadView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CXTPClientRect rc(this);

	CXTPBufferDC dcMem(dc);
	dcMem.FillSolidRect(rc, GetSysColor(COLOR_WINDOW));

	CXTPMarkupDrawingContext dcMarkup(dcMem);
	DrawMarkup(&dcMarkup, rc);
}

void CMarkupPadView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT(pInfo != NULL);  // overriding OnPaint -- never get this.
	if (!pInfo)
		return;

	pDC->SetMapMode(MM_ANISOTROPIC);

	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
		pDC->GetDeviceCaps(LOGPIXELSY));

	pDC->SetWindowExt(100, 100);

	// ptOrg is in logical coordinates
	pDC->OffsetWindowOrg(0, 0);

}

void CMarkupPadView::OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs)
{
	if (pSender->IsKindOf(MARKUP_TYPE(CXTPMarkupHyperlink)))
	{
		AfxMessageBox(_T("Hyperlink Clicked"));

		//CXTPMarkupString* pTag = STATIC_DOWNCAST(CXTPMarkupString, ((CXTPMarkupHyperlink*)pSender)->GetTag());
		
		//((CXTPMarkupHyperlink*)pSender)->SetBackground(RGB(0, 255, 255));

		pArgs->SetHandled();
	}
}

void CMarkupPadView::OnRunMouseLeftButtonUp(CXTPMarkupObject* /*pSender*/, CXTPMarkupMouseButtonEventArgs* pArgs)
{
	TRACE(_T("RunMouseLeftButtonUp\n"));
	pArgs->SetHandled();
}

void CMarkupPadView::OnBorderMouseLeftButtonUp(CXTPMarkupObject* /*pSender*/, CXTPMarkupMouseButtonEventArgs* /*pArgs*/)
{
	TRACE(_T("BorderMouseLeftButtonUp\n"));
}

void CMarkupPadView::OnTextBlockMouseLeftButtonUp(CXTPMarkupObject* /*pSender*/, CXTPMarkupMouseButtonEventArgs* /*pArgs*/)
{
	TRACE(_T("TextBlockMouseLeftButtonUp\n"));
}

void CMarkupPadView::OnMakeShapeRed(CXTPMarkupObject* /*pSender*/, CXTPMarkupMouseEventArgs* pArgs)
{
	if (pArgs->GetSource()->IsKindOf(MARKUP_TYPE(CXTPMarkupShape)))
	{
		((CXTPMarkupShape*)pArgs->GetSource())->SetFill(new CXTPMarkupSolidColorBrush(RGB(255, 0, 0)));
	}
}

void CMarkupPadView::OnMakeShapeGreen(CXTPMarkupObject* /*pSender*/, CXTPMarkupMouseEventArgs* pArgs)
{
	if (pArgs->GetSource()->IsKindOf(MARKUP_TYPE(CXTPMarkupShape)))
	{
		((CXTPMarkupShape*)pArgs->GetSource())->SetFill(new CXTPMarkupSolidColorBrush(RGB(0, 255, 0)));
	}
}

void CMarkupPadView::OnMakeTextBold(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	pSender->SetValue(CXTPMarkupTextElement::m_pFontWeightProperty, new CXTPMarkupEnum(FW_BOLD));
}

void CMarkupPadView::OnMakeTextNormal(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	pSender->SetValue(CXTPMarkupTextElement::m_pFontWeightProperty, NULL);
}

void CMarkupPadView::OnMakeTextYellow(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	pSender->SetValue(CXTPMarkupTextElement::m_pBackgroundProperty, new CXTPMarkupSolidColorBrush(RGB(255, 255, 0)));
}

void CMarkupPadView::OnMakeTextGreen(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	pSender->SetValue(CXTPMarkupTextElement::m_pBackgroundProperty, new CXTPMarkupSolidColorBrush(RGB(0, 128, 0)));
}

void CMarkupPadView::OnHideColumn4(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	((CXTPMarkupFrameworkElement*)pSender)->SetVisibility(xtpMarkupVisibilityCollapsed);
}

void CMarkupPadView::OnShowColumn4(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	CXTPMarkupGrid* pGrid = MARKUP_DYNAMICCAST(CXTPMarkupGrid, ((CXTPMarkupFrameworkElement*)pSender));
	if (!pGrid)
		return;

	pGrid->GetChildren()->GetItem(3)->SetVisibility(xtpMarkupVisibilityVisible);
}

void CMarkupPadView::OnMoveColumn3(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	CXTPMarkupGrid* pGrid = MARKUP_DYNAMICCAST(CXTPMarkupGrid, ((CXTPMarkupFrameworkElement*)pSender)->GetVisualParent()->GetVisualParent());
	if (!pGrid)
		return;

	if (CXTPMarkupGrid::GetColumn(pGrid->GetChildren()->GetItem(2)) == 2)
	{
		CXTPMarkupGrid::SetColumn(pGrid->GetChildren()->GetItem(2), 3);
		CXTPMarkupGrid::SetColumn(pGrid->GetChildren()->GetItem(3), 2);
	}
	else
	{
		CXTPMarkupGrid::SetColumn(pGrid->GetChildren()->GetItem(2), 2);
		CXTPMarkupGrid::SetColumn(pGrid->GetChildren()->GetItem(3), 3);
	}
}

void CMarkupPadView::OnSetText1(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	((CXTPMarkupTextBlock*)pSender)->SetText(L"New Text");
}

void CMarkupPadView::OnSetText2(CXTPMarkupObject* pSender, CXTPMarkupMouseEventArgs* /*pArgs*/)
{
	((CXTPMarkupTextBlock*)pSender)->SetText(L"Column5");
}

void CMarkupPadView::ToggleNextControl(CXTPMarkupObject* pSender, CXTPMarkupMouseButtonEventArgs* /*pArgs*/)
{
	CXTPMarkupUIElement* pElement = MARKUP_DYNAMICCAST(CXTPMarkupUIElement, pSender);
	if (!pElement)
		return;

	CXTPMarkupPanel* pPanel = MARKUP_DYNAMICCAST(CXTPMarkupPanel, pElement->GetVisualParent());
	if (!pPanel)
		return;

	int nIndex = pPanel->GetChildren()->IndexOf(pElement);

	
	CXTPMarkupUIElement* pNextElement = pPanel->GetChildren()->GetItem(nIndex + 1);
	if (!pNextElement)
		return;

	pNextElement->SetVisibility(pNextElement->GetVisibility() == xtpMarkupVisibilityVisible ? 
		xtpMarkupVisibilityCollapsed : xtpMarkupVisibilityVisible);
}

void CMarkupPadView::OnFilePrintPreview() 
{
	// replace the default print preview with ours!

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
	
	if (!DoPrintPreview(XTP_IDD_PREVIEW_DIALOGBAR, this, RUNTIME_CLASS(CXTPPreviewView), pState))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		
		TRACE0("Error: DoPrintPreview failed.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;      // preview failed to initialize, delete State now
		pState = NULL;
	}
}

