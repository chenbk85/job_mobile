// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__80941DC7_4E2C_448D_9EFB_39D39517AF9C__INCLUDED_)
#define AFX_MAINFRM_H__80941DC7_4E2C_448D_9EFB_39D39517AF9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrame : public CXTPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	BOOL CreateRibbonBar();
	void LoadIcons();

	void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	CXTPTabClientWnd m_wndClient;

	void ShowCustomizeDialog(int nSelectedPage);
	void OnCustomize();
	void OnCustomizeQuickAccess();



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
	afx_msg void OnViewFullscreen();
	afx_msg void OnViewNormal();
	afx_msg void OnUpdateViewNormal(CCmdUI* pCmdUI);
	afx_msg void OnWindowArrange();
	afx_msg void OnUpdateWindowSwitch(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	//}}AFX_MSG
	void OnViewWorkspace();
	void OnUpdateViewWorkspace(CCmdUI* pCmdUI);
	void OnUpdateRibbonTab(CCmdUI* pCmdUI);

	
	afx_msg void OnOptionsRighttoleft();
	afx_msg void OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyle(UINT nStyle);
	afx_msg void OnUpdateOptionsStyle(CCmdUI* pCmdUI);
	UINT m_nRibbonStyle;


	BOOL m_bShowWorkspace;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__80941DC7_4E2C_448D_9EFB_39D39517AF9C__INCLUDED_)
