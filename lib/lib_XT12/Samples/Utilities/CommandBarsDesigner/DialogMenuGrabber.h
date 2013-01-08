#if !defined(AFX_DIALOGMENUGRABBER_H__217E239C_6E16_4AE9_9463_DEC56A58B22E__INCLUDED_)
#define AFX_DIALOGMENUGRABBER_H__217E239C_6E16_4AE9_9463_DEC56A58B22E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogMenuGrabber.h : header file
//
class CEmbeddedFrame;
#include "StaticMenuGrabber.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogMenuGrabber dialog

class CDialogMenuGrabber : public CDialog
{
// Construction
public:
	CDialogMenuGrabber(CEmbeddedFrame* pFrame, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogMenuGrabber)
	enum { IDD = IDD_DIALOG_MENUGRABBER };
	CStaticMenuGrabber	m_wndGrabber;
	//}}AFX_DATA

	CXTPMenuBar m_wndMenuBar;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogMenuGrabber)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEmbeddedFrame* m_pFrame;

	// Generated message map functions
	//{{AFX_MSG(CDialogMenuGrabber)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGMENUGRABBER_H__217E239C_6E16_4AE9_9463_DEC56A58B22E__INCLUDED_)
