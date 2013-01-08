// MainFrm.cpp : implementation of the CMainFrame class
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
#include "ToolTipContext.h"

#include "MainFrm.h"
#include "ExplorerTheme.h"
#include "ControlFavorites.h"

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
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_FAVORITES_ADDTOFAVORITES, OnFavoritesAddtofavorites)
	//}}AFX_MSG_MAP
	ON_XTP_CREATECONTROL()
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
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
	srand((unsigned)time(NULL));
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
	
	pCommandBars->EnableActions();

	// Add the menu bar

	CXTPToolBar* pMenuBar = pCommandBars->SetMenu(
		_T("Menu Bar"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}
	//pMenuBar->ModifyBarStyle(CBRS_GRIPPER, 0);

	// Create ToolBar
	CXTPToolBar* pToolBar = (CXTPToolBar*)
		pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CXTPPaintManager::SetCustomTheme(new CExplorerTheme());
	
	if (pCommandBars->GetImageManager()->IsAlphaIconsSupported())
	{
		pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDR_TOOLBAR_ALPHA);
	
		UINT uFavorites[] = {ID_FAVORITE_LINK, ID_FAVORITE_FOLDER};
		pCommandBars->GetImageManager()->SetIcons(ID_FAVORITES, uFavorites, 2, CSize(16, 16));
	}

	XTPPaintManager()->GetIconsInfo()->bUseFadedIcons = FALSE;
	
	m_wndProperties.Create(IDD_DIALOG_PROPERTIES, this);
	m_wndProperties.CenterWindow(this);
	m_wndProperties.ShowWindow(SW_SHOW);

	pCommandBars->GetCommandBarsOptions()->bShowPopupBarToolTips = TRUE;
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);

	pCommandBars->GetContextMenus()->Add(IDR_CONTEXT_MENU);

	m_wndClient.Attach(this, FALSE);
	m_wndClient.EnableToolTips();

	if (pCommandBars->GetToolTipContext()->IsBalloonStyleSupported())
	{
		pCommandBars->GetToolTipContext()->SetStyle(xtpToolTipBalloon);
		pCommandBars->GetToolTipContext()->ShowTitleAndDescription(TRUE);

		m_wndClient.GetToolTipContext()->SetStyle(xtpToolTipBalloon);
		m_wndClient.GetToolTipContext()->ShowTitleAndDescription(TRUE);
	}

	LoadCommandBars(_T("CommandBars"));

	return 0;
}

void CMainFrame::OnClose()
{
	SaveCommandBars(_T("CommandBars"));

	CMDIFrameWnd::OnClose();
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


BOOL CMainFrame::GetFavoriteFolder(CString& strFav)
{
	LPITEMIDLIST pidlFavorites = NULL;
	IMalloc * pMalloc = NULL;
	BOOL bResult = FALSE;
	TCHAR   szPath[MAX_PATH];

	HRESULT hr = SHGetMalloc(&pMalloc);
	if (SUCCEEDED(hr))
	{
		HRESULT hr = SHGetSpecialFolderLocation(NULL, CSIDL_FAVORITES, &pidlFavorites);
		if (hr == NOERROR )
		{
			if (SHGetPathFromIDList( pidlFavorites,szPath))
			{
				strFav = szPath;
				bResult = TRUE;
			}

		}

		pMalloc->Free(pidlFavorites);
		pMalloc->Release();

	}

	if (!bResult)
	{
		HKEY hKey;
		TCHAR sz[MAX_PATH];

		// find out from the registry where the favorites are located.
		if(RegOpenKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders"), &hKey) == ERROR_SUCCESS)
		{
			DWORD dwSize = MAX_PATH;
			RegQueryValueEx(hKey, _T("Favorites"), NULL, NULL, (LPBYTE)sz, &dwSize);
			ExpandEnvironmentStrings(sz, szPath, MAX_PATH);
			RegCloseKey(hKey);
			strFav = szPath;
			bResult = dwSize != 0;
		}

	}
	if (!bResult)
	{
		GetWindowsDirectory (szPath, MAX_PATH);
		strFav = szPath;
		strFav += "\\Favorites";
	}
	return TRUE;
}


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->nID == ID_FAVORITES)
	{
		CString strFav;
		GetFavoriteFolder(strFav);

		lpCreateControl->pControl = new CControlFavorites(strFav);
		return TRUE;

	}

	return FALSE;
}

void CMainFrame::OnFavoritesAddtofavorites() 
{
	IShellUIHelper* pShell = NULL;
	HRESULT hr = CoCreateInstance(CLSID_ShellUIHelper, NULL, CLSCTX_SERVER,
		IID_IShellUIHelper, (void**)&pShell);
	
	if (hr == S_OK)
	{
		COleVariant vtTitle(_T("Codejock Software"));
		
		pShell->AddFavorite(L"http://www.codejock.com", &vtTitle);
		pShell->Release();
	}	
}

void CMainFrame::OnCustomize()
{
	CXTPCustomizeSheet cs(GetCommandBars());

	CXTPCustomizeMenusPage pageMenus(&cs);
	cs.AddPage(&pageMenus);

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_TOOLTITYPE);

	pCommands->InsertAllCommandsCategory();
	pCommands->InsertBuiltInMenus(IDR_TOOLTITYPE);
	pCommands->InsertNewMenuCategory();


	cs.DoModal();
}
