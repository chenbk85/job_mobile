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

#if !defined(AFX_MAINFRM_H__4FA08078_1069_44D7_8380_47F9D64AA544__INCLUDED_)
#define AFX_MAINFRM_H__4FA08078_1069_44D7_8380_47F9D64AA544__INCLUDED_

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

	void AddEdit();

	void AddLogo();

	void AddAnimation();

	void AddButton(int nIcon, int nID);
	
	void AddSwitchButtons();

	void AddZoomButton();
	void AddZoomSlider();

	void AddProgress();

	void TestProgress();

	CString m_strMessage;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CEdit         m_wndEditCtrl;
	CAnimateCtrl  m_wndAnimCtrl;
	CProgressCtrl m_wndProgCtrl;

	BOOL m_bPlayAnimation;

	UINT m_nPaneID;
	XTPPaintTheme m_eOfficeTheme;
	void SetOfficeTheme(XTPPaintTheme eOfficeTheme);
	BOOL UpdateThemeCombo(XTPPaintTheme eOfficeTheme, CXTPControlComboBox* pComboTheme = NULL);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnStatusBarShowButtons();
	afx_msg void OnUpdateStatusBarShowButtons(CCmdUI* pCmdUI);
	afx_msg void OnStatusBarShowAviAnimation();
	afx_msg void OnUpdateStatusBarShowAviAnimation(CCmdUI* pCmdUI);
	afx_msg void OnStatusBarShowProgressBar();
	afx_msg void OnUpdateStatusBarShowProgressBar(CCmdUI* pCmdUI);
	afx_msg void OnStatusBarShowEditControl();
	afx_msg void OnUpdateStatusBarShowEditControl(CCmdUI* pCmdUI);
	afx_msg void OnStatusBarShowCompanyLogo();
	afx_msg void OnUpdateStatusBarShowCompanyLogo(CCmdUI* pCmdUI);
	afx_msg void OnStatusBarPlayAnimation();
	afx_msg void OnUpdateStatusBarPlayAnimation(CCmdUI* pCmdUI);
	afx_msg void OnStatusBarTestProgress();
	afx_msg void OnUpdateStatusBarTestProgress(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	afx_msg void OnOfficeThemeChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomize();
	afx_msg void OnViewTheme(UINT nID);
	afx_msg void OnUpdateViewTheme(CCmdUI* pCmdUI);
	afx_msg void OnIndicatorButton(UINT nID);
	afx_msg void OnUpdateIndicatorButton(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4FA08078_1069_44D7_8380_47F9D64AA544__INCLUDED_)
