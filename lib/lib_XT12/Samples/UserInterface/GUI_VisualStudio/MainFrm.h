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

#if !defined(AFX_MAINFRM_H__57DF813D_6BDB_4AA1_A29E_0AAA116BC4D5__INCLUDED_)
#define AFX_MAINFRM_H__57DF813D_6BDB_4AA1_A29E_0AAA116BC4D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClassViewPane.h"
#include "ResourceViewPane.h"
#include "SolutionExplorerPane.h"
#include "PropertiesPane.h"
#include "OutputPane.h"

class CMainFrame : public CXTPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CXTPDockingPaneManager m_paneManager;
	CXTPTabClientWnd m_MTIClientWnd;

	CClassViewPane m_wndClassView;
	CResourceViewPane m_wndResourceView;
	CSolutionExplorerPane m_wndSolutionExplorer;
	CPropertiesPane m_wndProperties;
	COutputPane m_wndOutput;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);
	//}}AFX_VIRTUAL	
	
	void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	void ShowDockingPanePopupMenu(CXTPDockingPane* pPopupPane, CPoint pt, LPRECT lprcExclude);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowAutohideall();
	afx_msg void OnWindowMore();
	afx_msg void OnClose();
	//}}AFX_MSG

	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowView(UINT nID);
	afx_msg void OnEmptyCommandRange(UINT);
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	afx_msg void OnCustomize();

	afx_msg void OnEditState(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEditState(CCmdUI* pCmdUI);

	afx_msg void OnEditPlatform(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEditPlatform(CCmdUI* pCmdUI);
	afx_msg void OnFullScreen();
	afx_msg void OnUpdateFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnTheme(UINT nID);
	afx_msg void OnUpdateTheme(CCmdUI* pCmdUI);
	afx_msg void OnSkinFramework(UINT nID);

	void ExchangeLayout(CXTPPropExchange* pPX, BOOL bSerializeControls = TRUE);
	
	CWnd* CreateToolBox();
	void ResetToolboxItems();

	int m_nState;
	int m_nPlatform;
	CString m_strIniFileName;
	BOOL m_bFullScreen;
	CRect m_rcMainFrame;
	UINT m_nTheme;
	
	CXTPPropExchangeXMLNode* m_pFullScreenLayout;

	CXTPTaskPanelGroup* CreateToolboxGroup(UINT nID);
	CXTPOfficeBorder<CXTPTaskPanel> m_wndTaskPanel;


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__57DF813D_6BDB_4AA1_A29E_0AAA116BC4D5__INCLUDED_)
