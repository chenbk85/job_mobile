// ServerAgentView.cpp : implementation of the ServerAgentView class
//

#include "stdafx.h"
#include "ServerAgent.h"

#include "ServerAgentDoc.h"
#include "ServerAgentView.h"

#include "UGXPthemes.h"

#include "EditStylesDlg.h"
#include "grid/jServerAgent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ServerAgentView

IMPLEMENT_DYNCREATE(ServerAgentView, CView)

BEGIN_MESSAGE_MAP(ServerAgentView, CView)
	//{{AFX_MSG_MAP(ServerAgentView)
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
// ServerAgentView construction/destruction
ServerAgentView* g_pServerAgentView=0;
ServerAgentView::ServerAgentView() : m_pGrid(0)
{
	// TODO: add construction code here
	g_pServerAgentView=this;

}

ServerAgentView::~ServerAgentView()
{
	SAFE_DELETE(m_pGrid);
	UGXPThemes::CleanUp();
}

BOOL ServerAgentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

int ServerAgentView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	jID* pDoc = GetjIXml()->Load(_T("xml\\gridview\\grid_ServerAgent.xml"));
	//cstr szGrid=jS(jU_Grid);
	cstr szGrid = pv_GridView_RTTI_NAME->Get_cstr();
	jIE* pE = pDoc->BaseI()->FindByFirstAttr(jS(RTTI_NAME), jIVar::EDcstr,(void*)szGrid);
	jRETURN_ret(0,pE);

	//else if(jt_strcmp(jS(jU_Grid), szGrid) ==0)	m_pGrid = new jU_Grid(pE);
	//else 
		m_pGrid = new jGridCtrl(pE);

	if(m_pGrid)
		m_pGrid->CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234322 );
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// ServerAgentView drawing

void ServerAgentView::OnDraw(CDC* pDC)
{
	CXPThemeDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// ServerAgentView printing

BOOL ServerAgentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void ServerAgentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void ServerAgentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// ServerAgentView diagnostics

#ifdef _DEBUG
void ServerAgentView::AssertValid() const
{
	CView::AssertValid();
}

void ServerAgentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXPThemeDemoDoc* ServerAgentView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXPThemeDemoDoc)));
	return (CXPThemeDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ServerAgentView message handlers

void ServerAgentView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_pGrid)
		m_pGrid->MoveWindow( 0, 0, cx, cy );
}

BOOL ServerAgentView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}

void ServerAgentView::OnThemesCustom() 
{
	if (!UGXPThemes::UseThemes())
	{
		UGXPThemes::UseThemes(true);
	}

	CEditStylesDlg dlg;
	dlg.DoModal();
	Invalidate();
}

void ServerAgentView::OnThemesNone() 
{
	UGXPThemes::UseThemes(false);
	Invalidate(FALSE);
}

void ServerAgentView::OnUpdateThemesNone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}

void ServerAgentView::OnThemesStyle1() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);
	Invalidate(FALSE);
}

void ServerAgentView::OnUpdateThemesStyle1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style1);	
}

void ServerAgentView::OnThemesStyle2() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);
	Invalidate(FALSE);
}

void ServerAgentView::OnUpdateThemesStyle2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style2);	
}

void ServerAgentView::toggle_view()
{
}
