// ServerMonitorView.cpp : implementation of the ServerMonitorView class
//

#include "stdafx.h"
#include "ServerMonitor.h"

#include "ServerMonitorDoc.h"
#include "ServerMonitorView.h"

#include "UGXPthemes.h"

#include "EditStylesDlg.h"
#include "grid/jServerMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ServerMonitorView

IMPLEMENT_DYNCREATE(ServerMonitorView, CView)

BEGIN_MESSAGE_MAP(ServerMonitorView, CView)
	//{{AFX_MSG_MAP(ServerMonitorView)
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
// ServerMonitorView construction/destruction
ServerMonitorView* g_pServerMonitorView=0;
ServerMonitorView::ServerMonitorView() : m_pGrid(0)
{
	// TODO: add construction code here
	g_pServerMonitorView=this;

}

ServerMonitorView::~ServerMonitorView()
{
	SAFE_DELETE(m_pGrid);
	UGXPThemes::CleanUp();
}

BOOL ServerMonitorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

int ServerMonitorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	jID* pDoc = GetjIXml()->Load(_T("xml\\gridview\\grid_ServerMonitor.xml"));
	//cstr szGrid=jS(jU_Grid);
	cstr szGrid = pv_GridView_RTTI_NAME->Get_cstr();
	jIE* pE = pDoc->BaseI()->FindByFirstAttr(jS(RTTI_NAME), jIVar::EDcstr,(void*)szGrid);
	jRETURN_ret(0,pE);

	if(jt_strcmp(jS(grid_ServerMonitor), szGrid) ==0)	m_pGrid = new jServerMonitor(pE);
	else 
		m_pGrid = new jGridCtrl(pE);

	if(m_pGrid)
		m_pGrid->CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234322 );
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// ServerMonitorView drawing

void ServerMonitorView::OnDraw(CDC* pDC)
{
	CXPThemeDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// ServerMonitorView printing

BOOL ServerMonitorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void ServerMonitorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void ServerMonitorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// ServerMonitorView diagnostics

#ifdef _DEBUG
void ServerMonitorView::AssertValid() const
{
	CView::AssertValid();
}

void ServerMonitorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXPThemeDemoDoc* ServerMonitorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXPThemeDemoDoc)));
	return (CXPThemeDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ServerMonitorView message handlers

void ServerMonitorView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_pGrid)
		m_pGrid->MoveWindow( 0, 0, cx, cy );
}

BOOL ServerMonitorView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}

void ServerMonitorView::OnThemesCustom() 
{
	if (!UGXPThemes::UseThemes())
	{
		UGXPThemes::UseThemes(true);
	}

	CEditStylesDlg dlg;
	dlg.DoModal();
	Invalidate();
}

void ServerMonitorView::OnThemesNone() 
{
	UGXPThemes::UseThemes(false);
	Invalidate(FALSE);
}

void ServerMonitorView::OnUpdateThemesNone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}

void ServerMonitorView::OnThemesStyle1() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);
	Invalidate(FALSE);
}

void ServerMonitorView::OnUpdateThemesStyle1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style1);	
}

void ServerMonitorView::OnThemesStyle2() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);
	Invalidate(FALSE);
}

void ServerMonitorView::OnUpdateThemesStyle2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style2);	
}

void ServerMonitorView::toggle_view()
{
}
