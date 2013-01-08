#if !defined(AFX_SHELLTREEVIEW_H__48775716_74D4_4EBE_8212_0C33AA271BB0__INCLUDED_)
#define AFX_SHELLTREEVIEW_H__48775716_74D4_4EBE_8212_0C33AA271BB0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ShellTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShellTreeView view

class CShellTreeView : public CXTShellTreeView
{
protected:
	CShellTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CShellTreeView)

// Attributes
public:

// Operations
public:
	void SelectParentItem();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellTreeView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CShellTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void CShellTreeView::OnInitialUpdate();

	// Generated message map functions
protected:
	//{{AFX_MSG(CShellTreeView)
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLTREEVIEW_H__48775716_74D4_4EBE_8212_0C33AA271BB0__INCLUDED_)
