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
#include "CommandBarsDesigner.h"
#include "CommandBarsDesignerView.h"


#include "ChildFrm.h"

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
	//}}AFX_MSG_MAP
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
	cs.x = cs.y = -50;

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;


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


void CChildFrame::ActivateFrame(int /*nCmdShow*/)
{
	CMDIChildWnd::ActivateFrame(SW_MAXIMIZE);

}

LRESULT CChildFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCPAINT)
	{
		// prevent caption blinking
		return TRUE;
	}

	return CMDIChildWnd::WindowProc(message, wParam, lParam);
}

void CChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);

	CCommandBarsDesignerView* pView = DYNAMIC_DOWNCAST(CCommandBarsDesignerView, GetActiveView());

	if (pView)
	{
		pView->OnUpdateFrameTitle();
	}
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CMenu* pMenu = GetSystemMenu(FALSE);

	pMenu->RemoveMenu(SC_RESTORE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_MINIMIZE, MF_BYCOMMAND);
	pMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);
	
	return 0;
}
