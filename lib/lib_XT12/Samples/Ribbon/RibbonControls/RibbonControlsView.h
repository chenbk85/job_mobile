// RibbonControlsView.h : interface of the CRibbonControlsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIBBONCONTROLSVIEW_H__D9FF0CE1_4694_4617_B227_8AC1923A3724__INCLUDED_)
#define AFX_RIBBONCONTROLSVIEW_H__D9FF0CE1_4694_4617_B227_8AC1923A3724__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRibbonControlsView : public CView
{
protected: // create from serialization only
	CRibbonControlsView();
	DECLARE_DYNCREATE(CRibbonControlsView)

// Attributes
public:
	CRibbonControlsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonControlsView)
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
	virtual ~CRibbonControlsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRibbonControlsView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RibbonControlsView.cpp
inline CRibbonControlsDoc* CRibbonControlsView::GetDocument()
   { return (CRibbonControlsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONCONTROLSVIEW_H__D9FF0CE1_4694_4617_B227_8AC1923A3724__INCLUDED_)
