#if !defined(AFX_EXCELTABPROPERTIES_H__F85EB7E8_88A6_4854_86CE_8F6AAF84DD4B__INCLUDED_)
#define AFX_EXCELTABPROPERTIES_H__F85EB7E8_88A6_4854_86CE_8F6AAF84DD4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExcelTabProperties.h : header file
//

class CExcelTabView;

/////////////////////////////////////////////////////////////////////////////
// CExcelTabProperties dialog

class CExcelTabProperties : public CDialog
{
// Construction
public:
	CExcelTabProperties(BOOL& bBottom, BOOL& bHasArrows, BOOL& bHasHomeEnd, BOOL& bHScroll, CExcelTabView* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExcelTabProperties)
	enum { IDD = IDD_EXCELTAB_PROPERTIES };
	CButton	m_btnModifyTab;
	CButton	m_btnDeleteTab;
	CButton	m_btnDeleteAll;
	CButton	m_btnAddTab;
	int		m_iTabNum;
	CString	m_csText;
	//}}AFX_DATA

	BOOL&	m_bBottom;
	BOOL&	m_bHasArrows;
	BOOL&	m_bHasHomeEnd;
	BOOL&	m_bHScroll;
	
	CExcelTabView* m_pParentWnd;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelTabProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateDlgStatus();

	// Generated message map functions
	//{{AFX_MSG(CExcelTabProperties)
	afx_msg void OnFtsXtBottom();
	afx_msg void OnFtsXtHasarrows();
	afx_msg void OnFtsXtHashomeend();
	afx_msg void OnFtsXtHscroll();
	afx_msg void OnAddTab();
	afx_msg void OnDeleteAll();
	afx_msg void OnDeleteTab();
	afx_msg void OnModifyTab();
	afx_msg void OnChangeText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELTABPROPERTIES_H__F85EB7E8_88A6_4854_86CE_8F6AAF84DD4B__INCLUDED_)
