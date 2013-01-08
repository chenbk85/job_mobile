#if !defined(AFX_SAMPLEVIEW_H__8A05B26C_2A39_4658_916B_642343965F16__INCLUDED_)
#define AFX_SAMPLEVIEW_H__8A05B26C_2A39_4658_916B_642343965F16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SampleView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSampleView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSampleView : public CFormView
{
protected:
	CSampleView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSampleView)

// Form Data
public:
	//{{AFX_DATA(CSampleView)
	enum { IDD = IDD_VIEW_SAMPLE };
	int		m_nSkin;
	int		m_nTheme;
	CString	m_strFind;
	BOOL	m_bMatchCase;
	BOOL	m_bMatchWord;
	BOOL    m_bFlat;
	BOOL m_bShowGripper;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSampleView)
	afx_msg void OnButtonFind();
	afx_msg void OnButtonColordialog();
	afx_msg void OnButtonFontdialog();
	afx_msg void OnButtonPrintdialog();
	afx_msg void OnButtonOpendialog();
	afx_msg void OnSkinChanged();
	afx_msg void OnThemeChanged();
	afx_msg void OnChangeEditFind();
	afx_msg void OnCheckGripper();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEVIEW_H__8A05B26C_2A39_4658_916B_642343965F16__INCLUDED_)
