#if !defined(AFX_FILTERSDIALOG_H__491A15D4_A820_4C87_8E3B_4B3890956490__INCLUDED_)
#define AFX_FILTERSDIALOG_H__491A15D4_A820_4C87_8E3B_4B3890956490__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FiltersDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFiltersDialog dialog

class CFiltersDialog : public CDialog
{
// Construction
public:
	CFiltersDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFiltersDialog)
	enum { IDD = IDD_DIALOG_FILTERS };
	CSliderCtrl	m_wndBlue;
	CSliderCtrl	m_wndGreen;
	CSliderCtrl	m_wndRed;
	CSliderCtrl	m_wndSaturation;
	CSliderCtrl	m_wndHue;
	CSliderCtrl	m_wndBlend;
	int		m_nHue;
	int		m_nSaturation;
	int		m_nBlend;
	BOOL    m_bColorize;
	BOOL    m_bColorShift;
	BOOL    m_bCustom;
	int		m_nBlue;
	int		m_nGreen;
	int		m_nRed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFiltersDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void UpdateFilters();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFiltersDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERSDIALOG_H__491A15D4_A820_4C87_8E3B_4B3890956490__INCLUDED_)
