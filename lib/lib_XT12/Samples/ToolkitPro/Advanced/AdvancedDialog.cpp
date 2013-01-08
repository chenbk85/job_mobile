// AdvancedDialog.cpp : implementation file
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
#include "advanced.h"
#include "AdvancedDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedDialog dialog


CAdvancedDialog::CAdvancedDialog(CWnd* pParent /*=NULL*/)
	: CXTPDialog(CAdvancedDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdvancedDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdvancedDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvancedDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdvancedDialog, CXTPDialog)
	//{{AFX_MSG_MAP(CAdvancedDialog)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE,       OnKickIdle)
	ON_COMMAND_RANGE(ID_DEBUG_RESTART, ID_DEBUG_DISASSEMBLY, OnDebug)
	ON_COMMAND(ID_POPFRAME_EXIT, OnExitModal)
	ON_WM_SIZE()

	ON_COMMAND(ID_VIEW_STATUS_BAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, OnUpdateControlBarMenu)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedDialog message handlers
static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


LRESULT CAdvancedDialog::OnKickIdle(WPARAM, LPARAM)
{
	SendMessageToDescendants(WM_IDLEUPDATECMDUI);
	return 0;
}

void CAdvancedDialog::OnExitModal()
{
	OnCancel();
}


BOOL CAdvancedDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(0, ID_SEPARATOR, SBPS_STRETCH, 100);

	VERIFY(InitCommandBars());

	CXTPCommandBars* pCommandBars = GetCommandBars();
	pCommandBars->SetMenu(_T("Menu Bar"), IDR_POPOUTFRAME);

	CXTPToolBar* pToolBar = pCommandBars->Add(_T("Debug"), xtpBarTop);
	pToolBar->LoadToolBar(IDR_DEBUG);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CAdvancedDialog::OnDebug(UINT)
{
	AfxMessageBox(_T("Clicked!"));

}


void CAdvancedDialog::OnSize(UINT nType, int cx, int cy)
{
	CXTPDialog::OnSize(nType, cx, cy);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

void CAdvancedDialog::OnUpdateControlBarMenu(CCmdUI* pCmdUI)
{
	ASSERT(ID_VIEW_STATUS_BAR == AFX_IDW_STATUS_BAR);
	ASSERT(ID_VIEW_TOOLBAR == AFX_IDW_TOOLBAR);
	ASSERT(ID_VIEW_REBAR == AFX_IDW_REBAR);

	pCmdUI->SetCheck((m_wndStatusBar.GetStyle() & WS_VISIBLE) != 0);
}

void CAdvancedDialog::OnBarCheck()
{
	ASSERT(ID_VIEW_STATUS_BAR == AFX_IDW_STATUS_BAR);
	ASSERT(ID_VIEW_TOOLBAR == AFX_IDW_TOOLBAR);
	ASSERT(ID_VIEW_REBAR == AFX_IDW_REBAR);

	m_wndStatusBar.ShowWindow( (m_wndStatusBar.GetStyle() & WS_VISIBLE) == 0 ? SW_SHOWNA : SW_HIDE );
}
