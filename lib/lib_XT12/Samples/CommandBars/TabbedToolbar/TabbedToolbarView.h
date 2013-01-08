// TabbedToolbarView.h : interface of the CTabbedToolbarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABBEDTOOLBARVIEW_H__0D1B9940_9785_4479_949E_1BBE4A3617CB__INCLUDED_)
#define AFX_TABBEDTOOLBARVIEW_H__0D1B9940_9785_4479_949E_1BBE4A3617CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabClientPage.h"
#include "ThemePage.h"

class CTabbedToolbarView : public CFormView
{
protected: // create from serialization only
	CTabbedToolbarView();
	DECLARE_DYNCREATE(CTabbedToolbarView)

public:
	//{{AFX_DATA(CTabbedToolbarView)
	enum{ IDD = IDD_TABBEDTOOLBAR_FORM };
	//}}AFX_DATA

// Attributes
public:
	CTabbedToolbarDoc* GetDocument();

	CXTPTabControl m_wndTabControl;

	CTabControlPage m_pageTabControl;
	CThemePage m_pageTheme;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabbedToolbarView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabbedToolbarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabbedToolbarView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TabbedToolbarView.cpp
inline CTabbedToolbarDoc* CTabbedToolbarView::GetDocument()
   { return (CTabbedToolbarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABBEDTOOLBARVIEW_H__0D1B9940_9785_4479_949E_1BBE4A3617CB__INCLUDED_)
