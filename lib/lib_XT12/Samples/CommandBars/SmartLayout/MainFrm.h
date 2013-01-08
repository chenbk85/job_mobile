// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BCA4362C_5281_4C39_A10F_7482CB07608F__INCLUDED_)
#define AFX_MAINFRM_H__BCA4362C_5281_4C39_A10F_7482CB07608F__INCLUDED_

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

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnViewThemeOffice2003();
	afx_msg void OnViewThemeOffice2000();
	afx_msg void OnUpdateViewThemeOffice2000(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewThemeOffice2003(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnCustomize();
	afx_msg void OnAfterCreateControl(LPCREATECONTROLSTRUCT lp);
	int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BCA4362C_5281_4C39_A10F_7482CB07608F__INCLUDED_)
