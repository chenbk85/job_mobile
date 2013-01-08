// CommandBarControlsView.h : interface of the CCommandBarControlsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDBARCONTROLSVIEW_H__AEDD6FC7_C8B2_4023_B231_3E29B938C8FC__INCLUDED_)
#define AFX_COMMANDBARCONTROLSVIEW_H__AEDD6FC7_C8B2_4023_B231_3E29B938C8FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCommandBarControlsView : public CView
{
protected: // create from serialization only
	CCommandBarControlsView();
	DECLARE_DYNCREATE(CCommandBarControlsView)

// Attributes
public:
	CCommandBarControlsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandBarControlsView)
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
	virtual ~CCommandBarControlsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCommandBarControlsView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	void OnEmptyCommand();

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CommandBarControlsView.cpp
inline CCommandBarControlsDoc* CCommandBarControlsView::GetDocument()
   { return (CCommandBarControlsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDBARCONTROLSVIEW_H__AEDD6FC7_C8B2_4023_B231_3E29B938C8FC__INCLUDED_)
