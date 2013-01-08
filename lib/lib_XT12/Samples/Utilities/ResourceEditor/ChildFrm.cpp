// ChildFrm.cpp : implementation of the CChildFrame class
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
#include "ResourceEditor.h"

#include "ChildFrm.h"
#include "ResourceViewRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED, 100, OnResourceSelectionChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndResourceTree.Create(WS_CHILD|WS_VISIBLE|TVS_HASLINES|TVS_HASBUTTONS , CRect(0, 0, 0, 0), this, 100);

	if (!m_ilResourceTree.Create(16, 16, ILC_MASK|ILC_COLOR24, 0, 1))
		return -1;
	
	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(IDB_RESTREE));

	m_ilResourceTree.Add(&bmp, CXTPImageManager::GetBitmapMaskColor(bmp, CPoint(0, 0)));
	m_wndResourceTree.SetImageList(&m_ilResourceTree, TVSIL_NORMAL);

	
	// Initialize the docking pane manager and set the
	// initial them for the docking panes.  Do this only after all
	// control bars objects have been created and docked.
	m_paneManager.InstallDockingPanes(this);
	// Set Office 2003 Theme
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);

	// Create docking panes.
	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(
		IDR_PANE_RESOURCES, CRect(0, 0,200, 120), xtpPaneDockLeft);
	pwndPane1->SetOptions(xtpPaneNoCloseable);


	return 0;
}


LRESULT CChildFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			pPane->Attach(&m_wndResourceTree);
		}

		return TRUE; // handled
	}
	return FALSE;
}


void CChildFrame::OnResourceSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if (pNMTreeView->itemNew.lParam)
	{
		CResourceViewRecord* pRecord = (CResourceViewRecord*)pNMTreeView->itemNew.lParam;
		
		CXTPReportView* pView = DYNAMIC_DOWNCAST(CXTPReportView, GetActiveView());
		
		if (pView && pRecord)
		{
			CXTPReportControl& wndReport = pView->GetReportCtrl();

			CXTPReportRow* pRow = wndReport.GetRows()->Find(pRecord);
			
			if (pRow)
			{
				wndReport.SetFocusedRow(pRow);
			}
		}
		
	
	}
	
	
	*pResult = 0;
}



CFrameWnd* CChildFrame::GetActiveFrame() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CMDIChildWnd::GetActiveFrame();
}
