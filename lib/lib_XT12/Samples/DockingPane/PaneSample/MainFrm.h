// MainFrm.h : interface of the CMainFrame class
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

#if !defined(AFX_STDAFX_H__B1F4ABBF_7DA1_43C1_A82B_5EB4405A5135__INCLUDED_)
#define AFX_STDAFX_H__B1F4ABBF_7DA1_43C1_A82B_5EB4405A5135__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CMainFrameBase CXTPMDIFrameWnd, CXTPOffice2007FrameHook

class CEditPane : public CXTPEdit
{
public:
	CEditPane();

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};


class CMainFrame : public CMainFrameBase
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CXTPDockingPaneManager m_paneManager;

// Operations
public:
	CXTPDockingPaneManager* GetDockingPaneManager() {
		return &m_paneManager;
	}

public:
	BOOL m_bEditor;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void SwitchLayout();

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	CXTPDockingPaneLayout* m_pEditorLayout;
	CXTPDockingPaneLayout* m_pRunLayout;

	CEditPane m_wndPanes[11];
	CFont m_fntEdit;
	
	UINT m_nSelectedTheme;

	void AdjustStyle(XTPDockingPanePaintTheme theme);
	void SetDockingPaneTheme(XTPDockingPanePaintTheme theme);

	void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowPane(UINT nID);
public:
	afx_msg void OnThemeDefault();
	afx_msg void OnThemeOffice();
	afx_msg void OnThemeWhidbey();
	afx_msg void OnThemeVisio();
	afx_msg void OnThemeOffice2003();
	afx_msg void OnThemeShortcutBar2003();
	afx_msg void OnThemeWinXP();
	afx_msg void OnThemeExplorer();
	afx_msg void OnThemeGrippered();
	afx_msg void OnThemeOffice2007();
	afx_msg void OnThemeWord2007();

	afx_msg void OnThemeVisio2003();
	afx_msg void OnThemeVisio2000();
	afx_msg void OnThemeCustom();
	afx_msg void OnThemeCustom2();
	afx_msg void OnThemeCustom3();
	afx_msg void OnThemeCustom4();

	afx_msg void OnUpdateTheme(CCmdUI *pCmdUI);

	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLayoutRun();
	afx_msg void OnLayoutEditor();

	afx_msg void OnUpdateLayoutEditor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLayoutRun(CCmdUI *pCmdUI);
	afx_msg void OnDestroy();

	afx_msg void OnLoadFromFile();
	afx_msg void OnSaveToFile();
	afx_msg void OnLoadFromResource();

	afx_msg void OnHideClient();
	afx_msg void OnUpdateHideClient(CCmdUI *pCmdUI);

	afx_msg void OnUseSplitterTracker();
	afx_msg void OnUpdateUseSplitterTracker(CCmdUI *pCmdUI);

	afx_msg void OnCustomize();
	afx_msg void OnClose();
	void SetCommandBarsTheme(XTPPaintTheme paintTheme);

	afx_msg void OnThemedFloatingFrames();
	afx_msg void OnUpdateThemedFloatingFrames(CCmdUI *pCmdUI);
	afx_msg void OnAlphaContext();
	afx_msg void OnUpdateAlphaContext(CCmdUI *pCmdUI);
	afx_msg void OnDockingStickers();
	afx_msg void OnUpdateDockingStickers(CCmdUI *pCmdUI);

	afx_msg void OnMinMaxSamlpe();
	afx_msg void OnUpdateMinMaxSamlpe(CCmdUI *pCmdUI);
	afx_msg void OnGetMinMaxInfo(LPMINMAXINFO pMinMaxInfo);

	afx_msg void OnCaptionButtonClose();
	afx_msg void OnUpdateCaptionButtonClose(CCmdUI* pCmdUI);
	afx_msg void OnCaptionButtonAutoHide();
	afx_msg void OnUpdateCaptionButtonAutoHide(CCmdUI* pCmdUI);
	afx_msg void OnCaptionButtonMenu();
	afx_msg void OnUpdateCaptionButtonMenu(CCmdUI* pCmdUI);
	afx_msg void OnCaptionButtonMaximize();
	afx_msg void OnUpdateCaptionButtonMaximize(CCmdUI* pCmdUI);

	void SwitchDefaultPaneOptions(XTPDockingPaneOptions dwOption);

	afx_msg void OnCaptionVisible();
	afx_msg void OnCaptionHorizontal();
	afx_msg void OnCaptionVertical();
	afx_msg void OnCaptionAutoBySize();
	afx_msg void OnCaptionAutoByPosition();

	afx_msg void OnUpdateCaptionVisible(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCaptionHorizontal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCaptionVertical(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCaptionAutoBySize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCaptionAutoByPosition(CCmdUI* pCmdUI);
	afx_msg void OnCloseButtonAffects();
	afx_msg void OnAutoHideButtonAffects();
	afx_msg void OnUpdateCloseButtonAffects(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAutoHideButtonAffects(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowContentsWhileDragging(CCmdUI* pCmdUI);
	afx_msg void OnShowContentsWhileDragging();
	afx_msg void OnStickyFloatingFrames();
	afx_msg void OnUpdateStickyFloatingFrames(CCmdUI* pCmdUI);
	afx_msg void OnTransparentFloatingFrames();
	afx_msg void OnUpdateTransparentFloatingFrames(CCmdUI* pCmdUI);
	afx_msg void OnEnableSideDocking();
	afx_msg void OnUpdateEnableSideDocking(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

#endif
