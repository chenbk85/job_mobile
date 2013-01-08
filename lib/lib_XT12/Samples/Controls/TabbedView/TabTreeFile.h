// TabTreeFile.h : header file
//
#if !defined(__TABTREEFILE_H__)
#define __TABTREEFILE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTabTreeFile window

class CTabTreeFile : public CXTTreeCtrl
{
// Construction
public:
	CTabTreeFile();

// Attributes
public:

// Operations
protected:
	CImageList	m_imageList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabTreeFile)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateTree();
	virtual ~CTabTreeFile();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabTreeFile)
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TABTREEFILE_H__)
