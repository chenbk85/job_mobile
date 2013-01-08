#if !defined(AFX_TABSAMPLEPAGE_H__0E1972D9_CE03_49F2_B15B_AC57FBE3836C__INCLUDED_)
#define AFX_TABSAMPLEPAGE_H__0E1972D9_CE03_49F2_B15B_AC57FBE3836C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabSamplePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabSamplePage dialog

class CTabSamplePage : public CXTPPropertyPage
{
	DECLARE_DYNCREATE(CTabSamplePage)

// Construction
public:
	CTabSamplePage();
	~CTabSamplePage();

// Dialog Data
	//{{AFX_DATA(CTabSamplePage)
	enum { IDD = IDD_PAGE_SAMPLE1 };
	int		m_nValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTabSamplePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTabSamplePage)
	afx_msg void OnChangeEditValue();
	afx_msg void OnCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABSAMPLEPAGE_H__0E1972D9_CE03_49F2_B15B_AC57FBE3836C__INCLUDED_)
