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

#if !defined(AFX_MAINFRM_H__6B68C149_453A_45A4_92F7_0BA6B47B0BE1__INCLUDED_)
#define AFX_MAINFRM_H__6B68C149_453A_45A4_92F7_0BA6B47B0BE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CMainFrameBase CXTPFrameWnd


class CMainFrame : public CMainFrameBase
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
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);


// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	void SetTheme(int iTheme);

	CXTPStatusBar   m_wndStatusBar;

	CXTToolBox    m_wndToolBox;
	CImageList    m_ilToolBox;
	CXTSplitterWnd  m_wndSplitter;
	CXTRegistryManager m_regMgr;
	int            m_iTheme;


// Generated message map functions
protected:
	void InitToolBoxBar();

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg void OnCustomize();
	afx_msg LRESULT OnToolBoxNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	friend class CToolBoxDemoView;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6B68C149_453A_45A4_92F7_0BA6B47B0BE1__INCLUDED_)
