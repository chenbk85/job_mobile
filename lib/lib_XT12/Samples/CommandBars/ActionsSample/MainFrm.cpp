// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ActionsSample.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_MENUPOPUP_FILE 2000
#define ID_MENUPOPUP_ABOUT 2003
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_UPDATE_COMMAND_UI_RANGE(ID_MENUPOPUP_FILE, ID_MENUPOPUP_ABOUT, OnUpdatePopupMenu)
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	EnableActions();

	// Add the menu bar
	CXTPToolBar* pMenuBar = pCommandBars->SetMenu(
		_T("Menu Bar"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}
	
	// Create ToolBar
	CXTPToolBar* pToolBar = (CXTPToolBar*)
		pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pToolBar->EnableAnimation();

	CXTPDialogBar* pBar = (CXTPDialogBar*)pCommandBars->Add(_T("Actions"), xtpBarRight, RUNTIME_CLASS(CXTPDialogBar));
	pBar->SetBarID(200);
	pBar->EnableDocking(xtpFlagAlignAny|xtpFlagFloating|xtpFlagStretched);
	pBar->ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	m_wndActions.Create(CDialogActions::IDD, pBar);
	m_wndActions.ShowWindow(SW_SHOW);
	
	pBar->SetChild(&m_wndActions);

	pCommandBars->SetTheme(xtpThemeWhidbey);

	LoadCommandBars(_T("CommandBars"));

	return 0;
}


void CMainFrame::EnableActions()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	pCommandBars->EnableActions();

	// Optional:
	// Add standard actions, if you going to localize them.
	pCommandBars->GetActions()->Add(XTP_ID_CUSTOMIZE);
	pCommandBars->GetActions()->Add(XTP_ID_CUSTOMIZE_RESET);
	pCommandBars->GetActions()->Add(XTP_ID_CUSTOMIZE_ADDORREMOVE);
	pCommandBars->GetActions()->Add(XTP_ID_TOOLBAR_EXPAND);
	pCommandBars->GetActions()->Add(XTP_ID_TOOLBAR_HIDE);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return;

	// Instantiate the customize dialog.
	CXTPCustomizeSheet dlg(pCommandBars);

	// Add the options page to the customize dialog.
	CXTPCustomizeOptionsPage pageOptions(&dlg);
	dlg.AddPage(&pageOptions);

	// Add the commands page to the customize dialog.
	CXTPCustomizeCommandsPage* pPageCommands = dlg.GetCommandsPage();
	pPageCommands->AddCategories(IDR_MAINFRAME, TRUE);

	// Initialize the commands page page.
	pPageCommands->InsertAllCommandsCategory();
	pPageCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pPageCommands->InsertNewMenuCategory();

	// Display the customize dialog.
	dlg.DoModal();
}

void CMainFrame::OnClose()
{
	SaveCommandBars(_T("CommandBars"));

	CXTPFrameWnd::OnClose();
}

void CMainFrame::OnUpdatePopupMenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(1);
}

