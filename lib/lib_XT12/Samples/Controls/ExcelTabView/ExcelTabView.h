// ExcelTabView.h : interface of the CExcelTabView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELTABVIEW_H__CD07EB0B_7DC7_4DD3_AAB6_0A468DDC6C2C__INCLUDED_)
#define AFX_EXCELTABVIEW_H__CD07EB0B_7DC7_4DD3_AAB6_0A468DDC6C2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExcelListCtrl.h"
#include "ExcelEditCtrl.h"
#include "ExcelTreeCtrl.h"
#include "ExcelFormView.h"
#include "ExcelScrollView.h"

class CExcelTab
{
public:
	CExcelTab() : m_pWndTab(NULL) {}
	CString m_csTab;
	CWnd* m_pWndTab;
};

typedef CList<CExcelTab, CExcelTab&> CExcelTabArray;

class CExcelTabView : public CView
{
protected: // create from serialization only
	CExcelTabView();
	DECLARE_DYNCREATE(CExcelTabView)

// Attributes
public:
	CExcelTabDoc* GetDocument();
	void UpdateExcelTab();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelTabView)
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
	virtual ~CExcelTabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFont m_font;
	CXTPEmptyRect m_rcTabs;
	CXTExcelTabCtrl* m_pExcelTabCtrl;
	CExcelTabArray m_arExcelTabs;

	DWORD m_dwTabStyle;
	BOOL  m_bBottom;
	BOOL  m_bHasArrows;
	BOOL  m_bHasHomeEnd;
	BOOL  m_bHScroll;

	// use the flicker free template class, this will create the objects
	// making them flicker free!
	CXTNoFlickerWnd <CExcelListCtrl> m_sheet1;
	CXTNoFlickerWnd <CExcelEditCtrl> m_sheet2;
	CXTNoFlickerWnd <CExcelTreeCtrl> m_sheet3;
	CXTNoFlickerWnd <CXTListBox>      m_sheet4;
	CXTNoFlickerWnd <CXTListBox>      m_sheet5;
	CXTNoFlickerWnd <CXTListBox>      m_sheet6;
	CExcelFormView*                  m_pSheet7;
	CExcelScrollView*                m_pSheet8;

	BOOL CreateExcelTab();
	void UpdateTabsStyle();
	BOOL CreateSheet1();
	BOOL CreateSheet2();
	BOOL CreateSheet3();
	BOOL CreateSheet4();
	BOOL CreateSheet5();
	BOOL CreateSheet6();
	BOOL CreateSheet7();
	BOOL CreateSheet8();

// Generated message map functions
protected:
	//{{AFX_MSG(CExcelTabView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnExceltabProperties();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CExcelTabProperties;
};

#ifndef _DEBUG  // debug version in ExcelTabView.cpp
inline CExcelTabDoc* CExcelTabView::GetDocument()
   { return (CExcelTabDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELTABVIEW_H__CD07EB0B_7DC7_4DD3_AAB6_0A468DDC6C2C__INCLUDED_)
