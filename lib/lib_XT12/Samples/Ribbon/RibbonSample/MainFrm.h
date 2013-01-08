// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E6D95F91_FCF6_4C13_A74C_E25D863697E5__INCLUDED_)
#define AFX_MAINFRM_H__E6D95F91_FCF6_4C13_A74C_E25D863697E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PaneStyles.h"

class CMainFrame : public CXTPFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	CXTPControlGalleryItems* m_pItemsShapes;
	CXTPControlGalleryItems* m_pItemsStyles;
	CXTPControlGalleryItems* m_pItemsStyleSet;
	CXTPControlGalleryItems* m_pItemsThemeColors;
	CXTPControlGalleryItems* m_pItemsThemeFonts;
	
	CXTPControlGalleryItems* m_pItemsFontTextColor;
	CXTPControlGalleryItems* m_pItemsFontBackColor;
	CXTPControlGalleryItems* m_pItemsFontFace;
	CXTPControlGalleryItems* m_pItemsFontSize;
	CXTPControlGalleryItems* m_pItemsUndo;
	CXTPControlGalleryItems* m_pItemsColumns;

	void CreateGalleries();
	int m_nShape;
	int m_nStyle;
	int m_nColumns;

	int m_nStyleSet;
	int m_nThemeColors;
	int m_nThemeFonts;

	BOOL m_bAnimation;
	BOOL m_bLayoutRTL;

	CXTPMessageBar m_wndMessageBar;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

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

	BOOL CreateRibbonBar();
	BOOL CreateMiniToolBar();
	BOOL CreateStatusBar();
	BOOL CreateMessageBar();

	void OnGalleryColumns(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryColumns(CCmdUI* pCmdUI);


	void CreateDockingPane();

	CXTPDockingPaneManager m_paneManager;
	CPaneStyles m_paneStyles;


	CString m_csStylesPath;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnOptionsAnimation();
	afx_msg void OnUpdateOptionsAnimation(CCmdUI* pCmdUI);
	afx_msg void OnOptionsRighttoleft();
	afx_msg void OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI);
	afx_msg void OnOptionsStyle(UINT);
	afx_msg void OnUpdateOptionsStyle(CCmdUI* pCmdUI);
	afx_msg void OnToggleGroups();
	afx_msg void OnOptionsFont(UINT nID);
	afx_msg void OnUpdateOptionsFont(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnEmptyCommandRange(UINT);
	void OnEmptyCommand();

	void OnSwitchCommand();
	void OnUpdateSwitchCommand(CCmdUI* pCmdUI);
	void OnUpdateViewShowHide(CCmdUI* pCmdUI);
	void OnViewShowHide(UINT nID);
	
	void OnRibbonTabChanged(NMHDR* /*pNMHDR*/, LRESULT* /*pRes*/);
	void OnRibbonTabChanging(NMHDR* /*pNMHDR*/, LRESULT* /*pRes*/);

	void OnCustomize();
	void OnCustomizeQuickAccess();
	void ShowCustomizeDialog(int nSelectedPage);
	void OnAutoResizeIcons();
	void OnUpdateAutoResizeIcons(CCmdUI* pCmdUI);

	BOOL m_bChecked;
	BOOL m_bOptions[6];

	CString m_strIniFileName;
	UINT m_nRibbonStyle;

	void OnGalleryShapes(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryShapes(CCmdUI* pCmdUI);

	void OnGalleryStyles(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryStyles(CCmdUI* pCmdUI);

	void OnGalleryStyleSet(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryStyleSet(CCmdUI* pCmdUI);

	void OnGalleryThemeColors(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryThemeColors(CCmdUI* pCmdUI);

	void OnGalleryTable(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryTable(CCmdUI* pCmdUI);

	void OnGalleryThemeFonts(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryThemeFonts(CCmdUI* pCmdUI);

	int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);

	void OnFrameTheme();
	void OnUpdateFrameTheme(CCmdUI* pCmdUI);

	void OnStatusBarSwitchView(UINT nID);

	void LoadIcons();
	void OnMacroClick();

	void OnUpdateKeyIndicator(CCmdUI* pCmdUI);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E6D95F91_FCF6_4C13_A74C_E25D863697E5__INCLUDED_)
