// tool_GridView.cpp : implementation of the tool_GridView class
//

#include "stdafx.h"
#include "tool_Grid.h"

#include "tool_GridDoc.h"
#include "tool_GridView.h"

#include "UGXPthemes.h"

#include "EditStylesDlg.h"
#include "jU_Grid.h"
#include "grid/grid_Group.h"
#include "grid/jServerMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// tool_GridView

IMPLEMENT_DYNCREATE(tool_GridView, CView)

BEGIN_MESSAGE_MAP(tool_GridView, CView)
	//{{AFX_MSG_MAP(tool_GridView)
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_WM_ERASEBKGND()
	ON_COMMAND(ID_THEMES_CUSTOM, OnThemesCustom)
	ON_COMMAND(ID_THEMES_NONE, OnThemesNone)
	ON_UPDATE_COMMAND_UI(ID_THEMES_NONE, OnUpdateThemesNone)
	ON_COMMAND(ID_THEMES_STYLE1, OnThemesStyle1)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE1, OnUpdateThemesStyle1)
	ON_COMMAND(ID_THEMES_STYLE2, OnThemesStyle2)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE2, OnUpdateThemesStyle2)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// tool_GridView construction/destruction
tool_GridView* g_ptool_GridView=0;
tool_GridView::tool_GridView() : m_pGrid(0)
{
	// TODO: add construction code here
	g_ptool_GridView=this;

}

tool_GridView::~tool_GridView()
{
	SAFE_DELETE(m_pGrid);
	UGXPThemes::CleanUp();
}

BOOL tool_GridView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

int tool_GridView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	jID* pDoc = GetjIXml()->Load(_T("xml\\gridview\\grid_default.xml"));
	//cstr szGrid=jS(grid_Group);
	cstr szGrid=jS(jU_Grid);
	//cstr szGrid=jS(CXPThemeDemoGrid);
	//cstr szGrid = pv_GridView_RTTI_NAME->Get_cstr();
	jIE* pE = pDoc->BaseI()->FindByFirstAttr(jS(RTTI_NAME), jIVar::EDcstr,(void*)szGrid);
	jRETURN_ret(0,pE);

	if(jt_strcmp(jS(grid_Group), szGrid) ==0)	m_pGrid = new grid_Group(pE);
	else if(jt_strcmp(jS(jU_Grid), szGrid) ==0)	m_pGrid = new jU_Grid(pE);
	//else if(jt_strcmp(jS(CXPThemeDemoGrid), szGrid) ==0) m_pGrid = new CXPThemeDemoGrid;
	else m_pGrid = new jGridCtrl(pE);

	if(m_pGrid)
		m_pGrid->CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234322 );
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// tool_GridView drawing

void tool_GridView::OnDraw(CDC* pDC)
{
	CXPThemeDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// tool_GridView printing

BOOL tool_GridView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void tool_GridView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void tool_GridView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// tool_GridView diagnostics

#ifdef _DEBUG
void tool_GridView::AssertValid() const
{
	CView::AssertValid();
}

void tool_GridView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXPThemeDemoDoc* tool_GridView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXPThemeDemoDoc)));
	return (CXPThemeDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// tool_GridView message handlers

void tool_GridView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_pGrid)
		m_pGrid->MoveWindow( 0, 0, cx, cy );
}

BOOL tool_GridView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}

void tool_GridView::OnThemesCustom() 
{
	if (!UGXPThemes::UseThemes())
	{
		UGXPThemes::UseThemes(true);
	}

	CEditStylesDlg dlg;
	dlg.DoModal();
	Invalidate();
}

void tool_GridView::OnThemesNone() 
{
	UGXPThemes::UseThemes(false);
	Invalidate(FALSE);
}

void tool_GridView::OnUpdateThemesNone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}

void tool_GridView::OnThemesStyle1() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);
	Invalidate(FALSE);
}

void tool_GridView::OnUpdateThemesStyle1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style1);	
}

void tool_GridView::OnThemesStyle2() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);
	Invalidate(FALSE);
}

void tool_GridView::OnUpdateThemesStyle2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style2);	
}

void tool_GridView::toggle_view()
{
}
