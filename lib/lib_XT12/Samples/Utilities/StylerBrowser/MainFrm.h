// MainFrm.h : interface of the CMainFrame class
//


#pragma once


#define ABOUTBLANK _T("about:blank")

class CWindowPlacement
{
public:
	CWindowPlacement(CWnd* pOwner, CString strEntry);

	void ShowWindow(int nCmdShow, BOOL bRestore = TRUE);
	void SaveWindowPos();

private:
	CWnd* m_pOwner;
	CString m_strEntry;
};


#include "IndicatorStatusbar.h"

#include "ExplorerBar.h"
#include "FilterContent.h"

#define ID_VIEW_ENCODING_AUTOSELECT	0x2000
#define ID_VIEW_ENCODING_FIRST		0x2001
#define ID_VIEW_ENCODING_LAST		0x2100

#define WM_USER_SHELL_OPEN			(WM_USER + 0x1000) 

#define STARTUP_BLANK				0
#define STARTUP_HOME				1
#define STARTUP_LASTVISITED			2
#define STARTUP_NOTHING				3

#include "NotepadCtrl.h"
#include "CWebBrowser2.h"
#include "HistoryTree.h"
#include "SourceCtrl.h"


struct DOCKING_BARS
{
	CHistoryTree wndHistory;
	CXTShellTreeCtrl wndShell;
	CNotepadCtrl wndNotepad;
	CSourceCtrl wndSource;
	CExplorerBar wndSearch;
};


class CMainFrame : public CXTPMDIFrameWnd, CXTPOffice2007FrameHook
{
	DECLARE_DYNAMIC(CMainFrame)

public:

	static CStringArray m_arrEncodingPage;

	CMainFrame();

	CSourceCtrl* GetSourceCtrl() { 
		return &m_bars.wndSource;
	}
	
	CXTPDockingPaneManager m_paneManager;

// Attributes
protected:
	DOCKING_BARS m_bars;

	CIndicatorStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	
	BOOL m_bFullScreen;
	CRect m_rcMainFrame;
	HMENU m_hEncoding;
	HMENU m_hFavorites;
	IInternetSession* m_pSession;
	CFilterContent* m_pFilter;

	CStringArray m_astrFavoriteURLs;

	BOOL m_bAutoSelect;
	BOOL m_bShowStructure;

public:
	static BOOL	m_bConfirmCloseAll;
	static BOOL	m_bConfirmExit;
	static BOOL	m_bOneInstance;
	static BOOL m_bRestoreWindowPos;
	static int m_nStartup;
	static XTPPaintTheme m_themeCurrent;

public:
	//CComboBoxXP  m_wndAddress;
//	CComboSearch m_wndSearch;

	//CTabControl m_wndTabs;
	CXTPTabClientWnd m_MTIClientWnd;

	//CExplorerBar m_wndExplorer;

	CStringArray m_astrFavoriteDirs;

// Operations
public:
	void SetAddress(LPCTSTR lpszUrl);
	static void Load();
	static void Save();

	void OpenLastVisited();


protected:
	void InitialNameSpace();
	void UninitialNameSpace();
	void BuildEncodingMenu();

// Overrides
public:

// Generated message map functions
protected:
	void Properties(int nPage);
	
public:

	// Implementation
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	
	afx_msg void OnAddressSel();
	afx_msg void OnGotoUrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileWorkoffline();
	afx_msg void OnUpdateFileWorkoffline(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGotoUrl(CCmdUI *pCmdUI);
	
	afx_msg void OnWindowCloseAll();
	afx_msg void OnEmptyCommand();
	afx_msg void OnUpdateWindowCloseAll(CCmdUI *pCmdUI);
	afx_msg void OnDisableMenu(CCmdUI *pCmdUI);
	afx_msg void OnFavorite(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOpenAllItems(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnOrganizeFavorites();
	afx_msg void OnToolsImagesfilter();
	afx_msg void OnToolsPopupfilter();

	afx_msg void OnToggleDock(void);

	afx_msg void OnViewFullscreen();
	afx_msg void OnUpdateViewFullscreen(CCmdUI *pCmdUI);
	
	afx_msg void OnFileNewBlank();
	afx_msg void OnFileNewCurrent();
	afx_msg void OnUpdateFileNewCurrent(CCmdUI *pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	afx_msg void OnExploreSearch();
	afx_msg void OnUpdateExploreSearch(CCmdUI *pCmdUI);

	afx_msg void OnExploreHistory();
	afx_msg void OnUpdateExploreHistory(CCmdUI *pCmdUI);

	afx_msg void OnExploreFolder();
	afx_msg void OnUpdateExploreFolder(CCmdUI *pCmdUI);

	afx_msg void OnExploreSource();
	afx_msg void OnUpdateExploreSource(CCmdUI *pCmdUI);

	afx_msg void OnExploreNotepad();
	afx_msg void OnUpdateExploreNotepad(CCmdUI *pCmdUI);

	afx_msg void OnCustomize();

	afx_msg void OnToolsStructure();
	afx_msg void OnUpdateToolsStructure(CCmdUI *pCmdUI);

	afx_msg void OnGotoSearch(NMHDR* pNMHDR, LRESULT* pResult);
	
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	


	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnViewEncodingAuto();
	afx_msg void OnUpdateViewEncodingAuto(CCmdUI *pCmdUI);

	afx_msg LRESULT OnToolBarContextMenu(WPARAM, LPARAM);
	afx_msg void OnClose();
	
	afx_msg void OnSetDefault();
	afx_msg void OnStylerOptions();

	afx_msg LRESULT OnShellOpen(WPARAM wParam,LPARAM);
	afx_msg void OnUpdateIndicator(CCmdUI *pCmdUI);
	afx_msg LRESULT OnTabbarMouseMsg(WPARAM wParam,LPARAM);
	
	void SetTheme(XTPPaintTheme theme);
	void RefreshIcons();

	afx_msg LRESULT OnControlRButtonUp(WPARAM, LPARAM lParam);
	afx_msg void OnSwitchTheme();

	afx_msg void OnTheme(UINT);
	afx_msg void OnUpdateTheme(CCmdUI *pCmdUI);


	void SetDockingPaneIcon(UINT nIDPane, UINT nIDIcon);


	afx_msg void OnSearchList();
	
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnDestroy();
protected:

	CString m_strStylesPath;

protected:
	DECLARE_MESSAGE_MAP()
};


void OpenWindow(CString strUrl, BOOL bActivate = TRUE, BOOL bReplaceBlank = FALSE);


inline CMainFrame* GetMainFrame()
{
	return ((CMainFrame*)AfxGetMainWnd());
}

inline CExplorerBar* GetExplorer()
{
	/*
	CExplorerBar& pBar = ((CMainFrame*)AfxGetMainWnd())->m_wndExplorer;

	if (pBar.GetSafeHwnd() && pBar.GetStyle() & WS_VISIBLE)
	{
		return &pBar;
	}*/
	return NULL;
}

CXTPControlComboBox* GetAddressCombo();
