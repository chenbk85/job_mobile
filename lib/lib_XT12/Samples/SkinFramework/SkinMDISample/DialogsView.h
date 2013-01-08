#if !defined(AFX_DIALOGSVIEW_H__9C7CF842_B011_410C_9A05_B05B8CFEE01A__INCLUDED_)
#define AFX_DIALOGSVIEW_H__9C7CF842_B011_410C_9A05_B05B8CFEE01A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogsView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDialogsView : public CFormView
{
protected:
	CDialogsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDialogsView)

// Form Data
public:
	//{{AFX_DATA(CDialogsView)
	enum { IDD = IDD_PANE_DIALOGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogsView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDialogsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDialogsView)
	afx_msg void OnButtonColordialog();
	afx_msg void OnButtonFontdialog();
	afx_msg void OnButtonPrintdialog();
	afx_msg void OnButtonOpendialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSVIEW_H__9C7CF842_B011_410C_9A05_B05B8CFEE01A__INCLUDED_)
