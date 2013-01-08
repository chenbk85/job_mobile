#if !defined(AFX_MARKUPPADEDIT_H__BCE9D291_92E3_46A3_9669_13F398601812__INCLUDED_)
#define AFX_MARKUPPADEDIT_H__BCE9D291_92E3_46A3_9669_13F398601812__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkupPadEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadEdit view

class CMarkupPadEdit : public CEditView
{
protected:
	CMarkupPadEdit();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMarkupPadEdit)

// Attributes
public:

// Operations
public:
	HINSTANCE m_hInstance;

	LPWSTR GetUnicodeText();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupPadEdit)
	public:
	virtual void OnInitialUpdate();
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMarkupPadEdit();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CFont m_fnt;
	void UpdateViews();
	BOOL m_bFirstDoc;
	BOOL m_bError;

	void OnStatusBarHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);


	// Generated message map functions
protected:
	//{{AFX_MSG(CMarkupPadEdit)
	afx_msg void OnChange();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPPADEDIT_H__BCE9D291_92E3_46A3_9669_13F398601812__INCLUDED_)
