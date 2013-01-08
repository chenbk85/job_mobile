// TabTreeClass.h : header file
//
#if !defined(__TABTREECLASS_H__)
#define __TABTREECLASS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTabTreeClass window

class CTabTreeClass : public CXTTreeCtrl
{
// Construction
public:
	CTabTreeClass();

// Attributes
public:

// Operations
protected:
	CImageList	m_imageList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabTreeClass)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateTree();
	virtual ~CTabTreeClass();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabTreeClass)
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TABTREECLASS_H__)
