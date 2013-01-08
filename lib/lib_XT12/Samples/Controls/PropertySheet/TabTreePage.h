#if !defined(AFX_TABTREEPAGE_H__B74B8606_E260_4C31_B83D_6533C12DA733__INCLUDED_)
#define AFX_TABTREEPAGE_H__B74B8606_E260_4C31_B83D_6533C12DA733__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabTreePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabTreePage dialog

class CTabTreePage : public CXTPPropertyPage
{
	DECLARE_DYNCREATE(CTabTreePage)

// Construction
public:
	CTabTreePage();
	~CTabTreePage();

// Dialog Data
	//{{AFX_DATA(CTabTreePage)
	enum { IDD = IDD_PAGE_TREECONTROL };
	int		m_nBorderStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTabTreePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTabTreePage)
	afx_msg void OnSelchangeComboBorder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABTREEPAGE_H__B74B8606_E260_4C31_B83D_6533C12DA733__INCLUDED_)
