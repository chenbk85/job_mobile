#if !defined(AFX_CALENDARDATASOURCEDIALOG_H__83F36B4A_5206_4724_A924_C84C79D121BD__INCLUDED_)
#define AFX_CALENDARDATASOURCEDIALOG_H__83F36B4A_5206_4724_A924_C84C79D121BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarDataSourceDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalendarDataSourceDialog dialog

class CCalendarDataSourceDialog : public CDialog
{
// Construction
public:
	CCalendarDataSourceDialog(CWnd* pParent = NULL);   // standard constructor

	CString	m_strConnectionString;

// Dialog Data
	//{{AFX_DATA(CCalendarDataSourceDialog)
	enum { IDD = IDD_DATA_SOURCE_DIALOG };
	CEdit	m_ctrlConnectionString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDataSourceDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalendarDataSourceDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDATASOURCEDIALOG_H__83F36B4A_5206_4724_A924_C84C79D121BD__INCLUDED_)
