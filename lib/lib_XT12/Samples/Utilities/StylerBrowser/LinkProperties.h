#if !defined(AFX_LINKPROPERTIES_H__7A94449F_7655_4E57_9D2B_6A0BF10E3D7F__INCLUDED_)
#define AFX_LINKPROPERTIES_H__7A94449F_7655_4E57_9D2B_6A0BF10E3D7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinkProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinkProperties dialog

class CLinkProperties : public CDialog
{
// Construction
public:
	CLinkProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLinkProperties)
	enum { IDD = IDD_DIALOG_LINKPROP };
	CString	m_strAddress;
	CString	m_strTitle;
	CString	m_strParent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinkProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinkProperties)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINKPROPERTIES_H__7A94449F_7655_4E57_9D2B_6A0BF10E3D7F__INCLUDED_)
