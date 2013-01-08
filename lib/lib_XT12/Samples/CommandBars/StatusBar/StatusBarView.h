// StatusBarView.h : interface of the CStatusBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSBARVIEW_H__FD81C154_425F_404B_89EA_69A1D7627549__INCLUDED_)
#define AFX_STATUSBARVIEW_H__FD81C154_425F_404B_89EA_69A1D7627549__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStatusBarView : public CView
{
protected: // create from serialization only
	CStatusBarView();
	DECLARE_DYNCREATE(CStatusBarView)

// Attributes
public:
	CStatusBarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusBarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStatusBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CFont m_font;

	void OnZoomIndicator();
	void OnZoomSliderScroll(NMHDR* pNMHDR, LRESULT* pResult);
	int m_nZoom;



// Generated message map functions
protected:
	//{{AFX_MSG(CStatusBarView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StatusBarView.cpp
inline CStatusBarDoc* CStatusBarView::GetDocument()
   { return (CStatusBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSBARVIEW_H__FD81C154_425F_404B_89EA_69A1D7627549__INCLUDED_)
