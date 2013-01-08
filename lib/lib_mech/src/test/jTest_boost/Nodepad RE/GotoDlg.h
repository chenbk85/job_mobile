#if !defined(AFX_GOTODLG_H__61471EF4_0E4B_4C05_AA86_F000DA332AFF__INCLUDED_)
#define AFX_GOTODLG_H__61471EF4_0E4B_4C05_AA86_F000DA332AFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GotoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGotoDlg dialog

class CGotoDlg : public CDialog
{
// Construction
public:
	CGotoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGotoDlg)
	enum { IDD = IDD_GOTO };
	UINT	m_uiLine;
	UINT	m_uiColumn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGotoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGotoDlg)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTODLG_H__61471EF4_0E4B_4C05_AA86_F000DA332AFF__INCLUDED_)
