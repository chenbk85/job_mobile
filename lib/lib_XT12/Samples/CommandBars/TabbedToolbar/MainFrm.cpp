// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TabbedToolbar.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_COMMAND_RANGE(IDR_ICO7511, IDR_ICO9611, OnEmptyCommand)
	ON_COMMAND_RANGE(IDR_ICO9621, IDR_ICO9807, OnEmptyCommand)
	ON_COMMAND_RANGE(ID_BUTTON32771, ID_BUTTON_DELETE, OnEmptyCommand)
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


static UINT StandardIcons[] =
{
	IDR_ICO20513,
	IDR_ICO11056,
	IDR_ICO9809,
	IDR_ICO9807,
	IDR_ICO9806,	
	IDR_ICO9805,	
	IDR_ICO9803,	
	IDR_ICO9802,
	IDR_ICO9801,	
	ID_SEPARATOR,
	IDR_ICO9800,	
	IDR_ICO9746,	
	IDR_ICO9720,	
	IDR_ICO9718,	
	IDR_ICO9717,	
	IDR_ICO9710,	
	IDR_ICO9704,	
	IDR_ICO9703,	
	IDR_ICO9683,	
	IDR_ICO9673	
	
};

static UINT AdvancedIcons[] =
{
	IDR_ICO9673,
	IDR_ICO9621,
	IDR_ICO9619,
	ID_SEPARATOR,
	IDR_ICO9618,
	IDR_ICO9617,
	IDR_ICO9611,
	IDR_ICO9609,
	IDR_ICO9608,
	IDR_ICO9607,
	ID_SEPARATOR,
	IDR_ICO9606,
	IDR_ICO9600,
	IDR_ICO9505,
	IDR_ICO9504
	
};

static UINT OtherIcons[] =
{
	IDR_ICO9502,
	IDR_ICO9410,
	IDR_ICO9409,
	IDR_ICO9403,
	IDR_ICO8536,
	ID_SEPARATOR,
	IDR_ICO8044,
	IDR_ICO7721,
	IDR_ICO7612,
	IDR_ICO7611,
	IDR_ICO7610,
	IDR_ICO7519,
	IDR_ICO7518,
	ID_SEPARATOR,
	IDR_ICO7513,
	IDR_ICO7511		
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
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create Status bar.
	// Important: All control bars including the Status Bar
	// must be created before CommandBars....
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

	// Add the menu bar
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(
		_T("Menu Bar"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}
	pMenuBar->SetFlags(xtpFlagAddMDISysPopup);

	// Create ToolBar
	CXTPTabToolBar* pToolBar = (CXTPTabToolBar*)
		pCommandBars->Add(_T("Standard"), xtpBarTop, RUNTIME_CLASS(CXTPTabToolBar));

	pToolBar->SetBarID(IDR_MAINFRAME);

	CXTPTabManagerItem* pItem = pToolBar->InsertCategory(0, _T("Standard"), StandardIcons, _countof(StandardIcons));
	pItem->SetImageIndex(IDR_MAINFRAME);
	pItem = pToolBar->InsertCategory(1, _T("Advanced"), AdvancedIcons, _countof(AdvancedIcons));
	pItem->SetImageIndex(IDR_MAINFRAME);
	pItem = pToolBar->InsertCategory(2, _T("Other"), OtherIcons, _countof(OtherIcons));
	pItem->SetImageIndex(IDR_MAINFRAME);
	pItem->SetTooltip(_T("Other icons"));
	
	if (pCommandBars->GetImageManager()->IsAlphaIconsSupported())
		pToolBar->InsertCategory(4, _T("User Tools"), IDR_TOOLBAR_USER);


	pCommandBars->GetImageManager()->SetIcon(IDR_MAINFRAME, IDR_MAINFRAME);
	pToolBar->GetPaintManager()->m_bShowIcons = FALSE;
	pToolBar->GetPaintManager()->EnableToolTips(xtpTabToolTipAlways);
	pToolBar->SetMinimumWidth(300);


	
	

	// Set Office 2003 Theme
	CXTPPaintManager::SetTheme(xtpThemeOffice2003);
	//CXTPPaintManager::SetTheme(xtpThemeWhidbey);

	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);
	pCommandBars->GetCommandBarsOptions()->bLargeIcons = TRUE;

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));

	pToolBar->UpdateTabs(pToolBar->GetItem(0));

	return 0;
}

void CMainFrame::OnClose()
{
	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars"));

	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instanciate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

		// Add the keyboard page to the customize dialog.
		CXTPCustomizeKeyboardPage pageKeyboard(&dlg);
		dlg.AddPage(&pageKeyboard);
		pageKeyboard.AddCategories(IDR_TABBEDTYPE);

		// Add the options page to the customize dialog.
		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		// Add the commands page to the customize dialog.
		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_TABBEDTYPE);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_TABBEDTYPE);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
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
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnEmptyCommand(UINT)
{

}

