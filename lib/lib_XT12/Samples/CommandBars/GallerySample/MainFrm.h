// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__13B87AED_B4C8_4C74_B02E_38C2DDFC5AF8__INCLUDED_)
#define AFX_MAINFRM_H__13B87AED_B4C8_4C74_B02E_38C2DDFC5AF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CXTPFrameWnd, CXTPOffice2007FrameHook
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;

	CXTPControlGalleryItems* m_pItemsShapes;
	CXTPControlGalleryItems* m_pItemsStyles;
	CXTPControlGalleryItems* m_pItemsStyleSet;
	CXTPControlGalleryItems* m_pItemsThemeColors;
	CXTPControlGalleryItems* m_pItemsThemeFonts;
	
	CXTPControlGalleryItems* m_pItemsTable;
	CXTPControlGalleryItems* m_pItemsFontTextColor;
	CXTPControlGalleryItems* m_pItemsFontBackColor;
	CXTPControlGalleryItems* m_pItemsFontFace;
	CXTPControlGalleryItems* m_pItemsFontSize;
	CXTPControlGalleryItems* m_pItemsUndo;
	void CreateGalleries();

	int m_nShape;
	int m_nStyle;

	int m_nStyleSet;
	int m_nThemeColors;
	int m_nThemeFonts;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnStylesChange();
	afx_msg void OnViewAnimate();
	afx_msg void OnUpdateViewAnimate(CCmdUI* pCmdUI);
	//}}AFX_MSG
	int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	void OnCustomize();

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

	void OnViewTheme(UINT nTheme);
	void OnUpdateViewTheme(CCmdUI* pCmdUI);

	void OnStylesPreviewStart(NMHDR* pHdr, LRESULT* presult);
	void OnStylesPreviewCancel(NMHDR* pHdr, LRESULT* presult);
	void OnStylesPreviewApply(NMHDR* pHdr, LRESULT* presult);
	void OnStylesPreviewChange(NMHDR* pHdr, LRESULT* presult);


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__13B87AED_B4C8_4C74_B02E_38C2DDFC5AF8__INCLUDED_)
