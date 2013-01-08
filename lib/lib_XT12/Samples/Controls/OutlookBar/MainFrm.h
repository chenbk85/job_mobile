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

#if !defined(AFX_MAINFRM_H__24817F4B_8A93_43E6_938E_9E2E60573FCD__INCLUDED_)
#define AFX_MAINFRM_H__24817F4B_8A93_43E6_938E_9E2E60573FCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CMainFrameBase CXTPFrameWnd


class COutlookBarView;
class CMainFrame : public CMainFrameBase
{

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:

	CXTSplitterWnd m_wndSplitter;
	CXTOutBarCtrl  m_wndOutlookBar;
	CImageList     m_ImageLarge;
	CImageList     m_ImageSmall;
	CImageList     m_ilTreeIcons;
	CImageList     m_ilCaption;
	CXTTreeCtrl    m_wndTreeCtrl;
	CXTRegistryManager m_regMgr;
	int            m_iTheme;

	void SetTheme(int nTheme);

	BOOL InitializeImageLists();
	BOOL InitilalizeTreeControl();

public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitializeOutlookBar();
	virtual ~CMainFrame();
	COutlookBarView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar   m_wndStatusBar;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewThemeOfficeXP();
	afx_msg void OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnViewThemeDefault();
	afx_msg void OnUpdateViewThemeDefault(CCmdUI* pCmdUI);
	afx_msg void OnViewThemeOffice2003();
	afx_msg void OnUpdateViewThemeOffice2003(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnCustomize();
	afx_msg LRESULT OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__24817F4B_8A93_43E6_938E_9E2E60573FCD__INCLUDED_)
