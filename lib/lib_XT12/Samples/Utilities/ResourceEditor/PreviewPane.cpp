// PreviewPane.cpp : implementation file
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
#include "PreviewPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewPane

CPreviewPane::CPreviewPane()
{
	m_pPreviewDialog = 0;
}

CPreviewPane::~CPreviewPane()
{
	SAFE_DELETE(m_pPreviewDialog);
}


BEGIN_MESSAGE_MAP(CPreviewPane, CWnd)
	//{{AFX_MSG_MAP(CPreviewPane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPreviewPane message handlers

class CPreviewPaneDialog : public CDialog
{
public:
	CPreviewPaneDialog(LPCDLGTEMPLATE pTemplate, CWnd* pParent)
	{
		CreateIndirect(pTemplate, pParent);

	}

	virtual void OnCancel()
	{

	}

	virtual void OnOK()
	{

	}
};

void CPreviewPane::ClearPreview()
{
	if (m_pPreviewDialog)
	{
		m_pPreviewDialog->DestroyWindow();
	}
	
	SAFE_DELETE(m_pPreviewDialog);

	m_wndMenuBar.GetControls()->RemoveAll();
	m_wndMenuBar.MoveWindow(0, 0, 0, 0);
}

void CPreviewPane::ShowDialog(LPCDLGTEMPLATE pTemplate)
{
	ClearPreview();

	CWnd* pWnd = GetFocus();

	m_pPreviewDialog = new CPreviewPaneDialog(pTemplate, this);
	if (!m_pPreviewDialog->m_hWnd)
		return;

	m_pPreviewDialog->ModifyStyle(WS_POPUP, WS_CHILD);
	m_pPreviewDialog->SetParent(this);

	CXTPWindowRect rc(m_pPreviewDialog);
	m_pPreviewDialog->MoveWindow(0, 0, rc.Width(), rc.Height());
	m_pPreviewDialog->ShowWindow(SW_SHOWNA);

	if (pWnd && IsWindow(pWnd->GetSafeHwnd())) pWnd->SetFocus();
}

void CPreviewPane::ShowMenu(CMenu* pMenu, XTP_RESOURCEMANAGER_LANGINFO* pLangInfo)
{
	ClearPreview();

	
	m_wndMenuBar.LoadMenu(pMenu, TRUE);

	LOGFONT lfIcon;
	VERIFY(::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lfIcon), &lfIcon, 0));
	lfIcon.lfCharSet = pLangInfo->nFontCharSet;

	m_wndMenuBar.GetPaintManager()->SetCommandBarsFontIndirect(&lfIcon);

	CXTPClientRect rc(this);
	CSize sz = m_wndMenuBar.CalcDockingLayout(rc.Width(), LM_STRETCH | LM_HORZDOCK | LM_HORZ | LM_COMMIT);
	m_wndMenuBar.MoveWindow(0, 0, sz.cx, sz.cy);
	m_wndMenuBar.Invalidate(FALSE);
}

int CPreviewPane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CXTPPaintManager* pPaintManager = CXTPPaintManager::CreateTheme(xtpThemeOfficeXP);
	m_wndMenuBar.SetPaintManager(pPaintManager);
	
	m_wndMenuBar.CreateToolBar(WS_CHILD|WS_VISIBLE, this);
	
	return 0;
}

void CPreviewPane::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (m_wndMenuBar.GetControls()->GetCount() > 0)
	{	
		CSize sz = m_wndMenuBar.CalcDockingLayout(cx, LM_STRETCH | LM_HORZDOCK | LM_HORZ | LM_COMMIT);
		m_wndMenuBar.MoveWindow(0, 0, sz.cx, sz.cy);
		m_wndMenuBar.Invalidate(FALSE);
	}
	else
	{
		m_wndMenuBar.MoveWindow(0, 0, 0, 0);
	}
	
}
