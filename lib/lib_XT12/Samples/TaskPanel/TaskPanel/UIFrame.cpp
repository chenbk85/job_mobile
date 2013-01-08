// UIFrame.cpp : implementation file
//

#include "stdafx.h"
#include "taskpanel.h"
#include "UIFrame.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CXTPClientRect rc(this);
	dc.FillSolidRect(rc, GetSysColor(COLOR_WINDOW));
}

/////////////////////////////////////////////////////////////////////////////
// CUIFrame

IMPLEMENT_DYNCREATE(CUIFrame, CFrameWnd)

CUIFrame::CUIFrame()
{
}

CUIFrame::~CUIFrame()
{
}


BEGIN_MESSAGE_MAP(CUIFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CUIFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_THEME_OFFICE2000, OnThemeOffice2000)
	ON_UPDATE_COMMAND_UI(ID_THEME_OFFICE2000, OnUpdateThemeOffice2000)
	ON_COMMAND(ID_THEME_OFFICE2003, OnThemeOffice2003)
	ON_UPDATE_COMMAND_UI(ID_THEME_OFFICE2003, OnUpdateThemeOffice2003)
	ON_COMMAND(ID_THEME_NATIVEWINXP, OnThemeNativewinxp)
	ON_UPDATE_COMMAND_UI(ID_THEME_NATIVEWINXP, OnUpdateThemeNativewinxp)
	ON_COMMAND(ID_THEME_OFFICE2000PLAIN, OnThemeOffice2000plain)
	ON_UPDATE_COMMAND_UI(ID_THEME_OFFICE2000PLAIN, OnUpdateThemeOffice2000plain)
	ON_COMMAND(ID_THEME_OFFICEXPPLAIN, OnThemeOfficexpplain)
	ON_UPDATE_COMMAND_UI(ID_THEME_OFFICEXPPLAIN, OnUpdateThemeOfficexpplain)
	ON_COMMAND(ID_THEME_OFFICE2003PLAIN, OnThemeOffice2003plain)
	ON_UPDATE_COMMAND_UI(ID_THEME_OFFICE2003PLAIN, OnUpdateThemeOffice2003plain)
	ON_COMMAND(ID_THEME_NATIVEWINXPPLAIN, OnThemeNativewinxpplain)
	ON_UPDATE_COMMAND_UI(ID_THEME_NATIVEWINXPPLAIN, OnUpdateThemeNativewinxpplain)
	ON_COMMAND(ID_TASKPANEL_ANIMATION, OnTaskpanelAnimation)
	ON_UPDATE_COMMAND_UI(ID_TASKPANEL_ANIMATION, OnUpdateTaskpanelAnimation)

	ON_MESSAGE(XTPWM_TASKPANEL_NOTIFY, OnTaskPanelNotify)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUIFrame message handlers

int CUIFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	
	return 0;
}

void CUIFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
	
	// forward focus to the view window
	m_wndView.SetFocus();
	
}

BOOL CUIFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CUIFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnClose();

	CMainFrame* pFrameWnd = (CMainFrame*)AfxGetMainWnd();
	if (pFrameWnd != NULL)
	{
		pFrameWnd->m_pUIFrame = NULL;
	}

}

BOOL CUIFrame::CreateTaskPanel()
{

	if (!m_wndTaskPanel.Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP, CRect(0, 0, 0, 0), &m_wndSplitter, m_wndSplitter.IdFromRowCol(0, 0)))
		return FALSE;

	m_wndTaskPanel.SetOwner(this);

	m_wndSplitter.SetColumnInfo(0, 210, 0);

	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	m_wndTaskPanel.CreateFromMenu(&menu);
	m_wndTaskPanel.m_bUIMode = TRUE;

	m_wndTaskPanel.SetHotTrackStyle(xtpTaskPanelHighlightItem);
	
	m_wndTaskPanel.GetImageManager()->SetIcons(IDR_MAINFRAME, 
		XTPImageManager()->IsAlphaIconsSupported() ?  IDR_TOOLBAR_A : IDR_MAINFRAME);

	

	return TRUE;
}

BOOL CUIFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* /*pContext*/) 
{
	m_wndSplitter.CreateStatic(this, 1, 2);

	if (!CreateTaskPanel())
		return FALSE;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
		CRect(0, 0, 0, 0), &m_wndSplitter, m_wndSplitter.IdFromRowCol(0, 1), NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	m_wndSplitter.ShowTopBorder(FALSE, 0);
	return TRUE;

}


LRESULT CUIFrame::OnTaskPanelNotify(WPARAM wParam, LPARAM lParam)
{
	switch(wParam) {
	case XTP_TPN_CLICK:
		{
			CXTPTaskPanelGroupItem* pItem = (CXTPTaskPanelGroupItem*)lParam;
			TRACE(_T("Click Event: pItem.Caption = %s, pItem.ID = %i\n"), pItem->GetCaption(), pItem->GetID());

			if (m_wndTaskPanel.m_bUIMode)
			{
				SendMessage(WM_COMMAND, pItem->GetID());
			}
		}
		break;	
	}

	return 0;
}



void CUIFrame::SetTheme(XTPTaskPanelPaintTheme taskPanelTheme)
{
	m_wndTaskPanel.SetTheme(taskPanelTheme);
	RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
}

void CUIFrame::OnThemeOffice2000()
{
	SetTheme(xtpTaskPanelThemeOffice2000);
}

void CUIFrame::OnUpdateThemeOffice2000(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPanel.GetCurrentTheme() == xtpTaskPanelThemeOffice2000);

}

void CUIFrame::OnThemeOffice2003()
{
	SetTheme(xtpTaskPanelThemeOffice2003);
}

void CUIFrame::OnUpdateThemeOffice2003(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPanel.GetCurrentTheme() == xtpTaskPanelThemeOffice2003);

}

void CUIFrame::OnThemeNativewinxp()
{
	SetTheme(xtpTaskPanelThemeNativeWinXP);
}

void CUIFrame::OnUpdateThemeNativewinxp(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPanel.GetCurrentTheme() == xtpTaskPanelThemeNativeWinXP);

}

void CUIFrame::OnThemeOffice2000plain()
{
	SetTheme(xtpTaskPanelThemeOffice2000Plain);
}

void CUIFrame::OnUpdateThemeOffice2000plain(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPanel.GetCurrentTheme() == xtpTaskPanelThemeOffice2000Plain);

}

void CUIFrame::OnThemeOfficexpplain()
{
	SetTheme(xtpTaskPanelThemeOfficeXPPlain);
}

void CUIFrame::OnUpdateThemeOfficexpplain(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPanel.GetCurrentTheme() == xtpTaskPanelThemeOfficeXPPlain);

}

void CUIFrame::OnThemeOffice2003plain()
{
	SetTheme(xtpTaskPanelThemeOffice2003Plain);
}

void CUIFrame::OnUpdateThemeOffice2003plain(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPanel.GetCurrentTheme() == xtpTaskPanelThemeOffice2003Plain);

}

void CUIFrame::OnThemeNativewinxpplain()
{
	SetTheme(xtpTaskPanelThemeNativeWinXPPlain);
}

void CUIFrame::OnUpdateThemeNativewinxpplain(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPanel.GetCurrentTheme() == xtpTaskPanelThemeNativeWinXPPlain);

}

void CUIFrame::OnTaskpanelAnimation()
{
	m_wndTaskPanel.SetAnimation(m_wndTaskPanel.GetAnimation() == xtpTaskPanelAnimationNo? xtpTaskPanelAnimationYes: xtpTaskPanelAnimationNo);
}

void CUIFrame::OnUpdateTaskpanelAnimation(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndTaskPanel.GetAnimation() == xtpTaskPanelAnimationYes);
}
