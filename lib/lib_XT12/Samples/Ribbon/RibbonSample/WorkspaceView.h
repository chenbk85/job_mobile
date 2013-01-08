#if !defined(AFX_WORKSPACEVIEW_H__8B9758DA_BD65_4E68_BC3C_8C98B2419838__INCLUDED_)
#define AFX_WORKSPACEVIEW_H__8B9758DA_BD65_4E68_BC3C_8C98B2419838__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkspaceView.h : header file
//

class CRibbonSampleView;
/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView view

class CWorkspaceView : public CView
{
protected:
	CWorkspaceView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWorkspaceView)

// Attributes
public:

// Operations
public:
	void SetLayoutRTL(BOOL bRTLLayout);
	void Reposition(CSize sz);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWorkspaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CXTPScrollBar m_wndScrollBar[2];
	CRect GetViewRect(CRect rc);

protected:
	CRibbonSampleView* m_pView;


	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACEVIEW_H__8B9758DA_BD65_4E68_BC3C_8C98B2419838__INCLUDED_)
