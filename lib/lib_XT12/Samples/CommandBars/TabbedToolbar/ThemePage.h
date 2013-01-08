#if !defined(AFX_THEMEPAGE_H__6CBA42DA_6081_47A1_9B36_F67135EB3CA5__INCLUDED_)
#define AFX_THEMEPAGE_H__6CBA42DA_6081_47A1_9B36_F67135EB3CA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThemePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThemePage dialog

class CThemePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CThemePage)

// Construction
public:
	void Update();
	CThemePage();
	~CThemePage();

// Dialog Data
	//{{AFX_DATA(CThemePage)
	enum { IDD = IDD_PAGE_THEME };
	int m_nTheme;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CThemePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CThemePage)
	afx_msg void OnRadioTheme();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THEMEPAGE_H__6CBA42DA_6081_47A1_9B36_F67135EB3CA5__INCLUDED_)
