// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__CC110031_0C3B_4122_9822_5F0285B80A0B__INCLUDED_)
#define AFX_MAINFRM_H__CC110031_0C3B_4122_9822_5F0285B80A0B__INCLUDED_

#include "FindReplaceDlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Operations
public:
	void DisplayLineAndColumn ();
	void OnEditFind ();
	void OnEditReplace ();
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
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CFindReplaceDlg m_wndReplaceBar;
	CFindReplaceDlg m_wndFindBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnHelpFinder();
	afx_msg void OnUpdateOptionsDropFiles(CCmdUI* pCmdUI);
	afx_msg void OnOptionsDropFiles();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnHelpRegex();
	afx_msg LRESULT OnNotifyFindReplace (WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool m_bDropFiles;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CC110031_0C3B_4122_9822_5F0285B80A0B__INCLUDED_)
