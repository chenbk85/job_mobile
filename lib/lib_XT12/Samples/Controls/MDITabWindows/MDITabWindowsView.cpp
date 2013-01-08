// MDITabWindowsView.cpp : implementation of the CMDITabWindowsView class
//
// This file is a part of the XTREME TOOLKIT MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO 
// BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED 
// WRITTEN CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS 
// OUTLINED IN THE XTREME TOOLKIT LICENSE AGREEMENT.  CODEJOCK SOFTWARE 
// GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE 
// THIS SOFTWARE ON A SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MDITabWindows.h"

#include "MDITabWindowsDoc.h"
#include "MDITabWindowsView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDITabWindowsView

IMPLEMENT_DYNCREATE(CMDITabWindowsView, CEditView)

BEGIN_MESSAGE_MAP(CMDITabWindowsView, CEditView)
	//{{AFX_MSG_MAP(CMDITabWindowsView)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	//}}AFX_MSG_MAP
    // Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDITabWindowsView construction/destruction

CMDITabWindowsView::CMDITabWindowsView()
{
	// TODO: add construction code here

}

CMDITabWindowsView::~CMDITabWindowsView()
{
}

BOOL CMDITabWindowsView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CEditView::PreCreateWindow(cs))
		return FALSE;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMDITabWindowsView drawing

void CMDITabWindowsView::OnDraw(CDC* pDC)
{
	CMDITabWindowsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	CRect r;
	GetClientRect(&r);
	pDC->Draw3dRect(r.left,r.top,r.Width(),r.Height(),0,0);
}

/////////////////////////////////////////////////////////////////////////////
// CMDITabWindowsView printing

BOOL CMDITabWindowsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CMDITabWindowsView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMDITabWindowsView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CMDITabWindowsView::OnFilePrintPreview() 
{
    CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
    ASSERT_VALID(pMainFrame);

	// show print preview.
    pMainFrame->HideMDITabs();
	//_xtAfxShowPrintPreview( this );
    pMainFrame->ToggleMDITabs();
}

/////////////////////////////////////////////////////////////////////////////
// CMDITabWindowsView diagnostics

#ifdef _DEBUG
void CMDITabWindowsView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMDITabWindowsView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMDITabWindowsDoc* CMDITabWindowsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDITabWindowsDoc)));
	return (CMDITabWindowsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDITabWindowsView message handlers

int CMDITabWindowsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	DragAcceptFiles();
	
//    SetFont(&XTAuxData().fontBold);
    SetWindowText(_T("Right click on tab to see more options..."));
    
	// TODO: Remove this line if you don't want cool
	// menus for this view.
//	m_coolMenu.HookWindow(GetEditCtrl().m_hWnd);
//	m_coolMenu.LoadToolbar(IDR_MAINFRAME);
	
	return 0;
}

void CMDITabWindowsView::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	UINT nFiles = DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

	TCHAR szFileName[_MAX_PATH + 1];
	UINT nNames;
	for(nNames = 0; nNames < nFiles; nNames++)
	{
		::ZeroMemory(szFileName, _MAX_PATH + 1);
		::DragQueryFile(hDropInfo, nNames, (LPTSTR)szFileName, _MAX_PATH + 1);

		AfxGetApp()->OpenDocumentFile(szFileName);
	}

	CEditView::OnDropFiles(hDropInfo);
}

void CMDITabWindowsView::OnRButtonDown(UINT /*nFlags*/, CPoint point) 
{
	CPoint pt = point;
	ClientToScreen(&pt);

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_EDIT_POPUP));

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	
	CMenu* pPopup = menu.GetSubMenu(0);
	CXTPCommandBars::TrackPopupMenu(pPopup, TPM_RIGHTBUTTON,
		pt.x, pt.y, AfxGetMainWnd(), 0, 0, ((CXTPMDIFrameWnd*)AfxGetMainWnd())->GetCommandBars());
}
