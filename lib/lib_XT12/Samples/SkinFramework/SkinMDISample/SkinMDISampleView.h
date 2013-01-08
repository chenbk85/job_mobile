// SkinMDISampleView.h : interface of the CSkinMDISampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINMDISAMPLEVIEW_H__E6D00929_AC45_4AFB_A491_3BCAB890EBB7__INCLUDED_)
#define AFX_SKINMDISAMPLEVIEW_H__E6D00929_AC45_4AFB_A491_3BCAB890EBB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSkinMDISampleView : public CScrollView
{
protected: // create from serialization only
	CSkinMDISampleView();
	DECLARE_DYNCREATE(CSkinMDISampleView)

// Attributes
public:
	CSkinMDISampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinMDISampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinMDISampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkinMDISampleView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SkinMDISampleView.cpp
inline CSkinMDISampleDoc* CSkinMDISampleView::GetDocument()
   { return (CSkinMDISampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINMDISAMPLEVIEW_H__E6D00929_AC45_4AFB_A491_3BCAB890EBB7__INCLUDED_)
