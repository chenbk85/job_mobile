// SkinSDISampleView.h : interface of the CSkinSDISampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINSDISAMPLEVIEW_H__8D17416C_4E89_4942_ADE0_AD4AD2AF479C__INCLUDED_)
#define AFX_SKINSDISAMPLEVIEW_H__8D17416C_4E89_4942_ADE0_AD4AD2AF479C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkinSDISampleCntrItem;

class CSkinSDISampleView : public CRichEditView
{
protected: // create from serialization only
	CSkinSDISampleView();
	DECLARE_DYNCREATE(CSkinSDISampleView)

// Attributes
public:
	CSkinSDISampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinSDISampleView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinSDISampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkinSDISampleView)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SkinSDISampleView.cpp
inline CSkinSDISampleDoc* CSkinSDISampleView::GetDocument()
	{ return (CSkinSDISampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSDISAMPLEVIEW_H__8D17416C_4E89_4942_ADE0_AD4AD2AF479C__INCLUDED_)
