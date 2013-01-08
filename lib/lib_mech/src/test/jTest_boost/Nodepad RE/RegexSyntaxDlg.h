#if !defined(AFX_REGEXSYNTAXDLG_H__5A7736E1_55F2_4242_AD34_CADA03B708AF__INCLUDED_)
#define AFX_REGEXSYNTAXDLG_H__5A7736E1_55F2_4242_AD34_CADA03B708AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegexSyntaxDlg.h : header file
//
#pragma warning (disable:4786)

#include <boost/regex.hpp>

/////////////////////////////////////////////////////////////////////////////
// CRegexSyntaxDlg dialog

class CRegexSyntaxDlg : public CDialog
{
// Construction
public:
	CRegexSyntaxDlg (const boost::regbase::flag_type tSyntax,
		const unsigned int uiMatchFlags, CWnd* pParent = NULL);

	boost::regbase::flag_type m_tSyntax;
	unsigned int m_uiMatchFlags;

// Dialog Data
	//{{AFX_DATA(CRegexSyntaxDlg)
	enum { IDD = IDD_REGEX_SYNTAX };
	int		m_iSyntax;
	BOOL	m_bescape_in_lists;
	BOOL	m_bchar_classes;
	BOOL	m_bintervals;
	BOOL	m_blimited_ops;
	BOOL	m_bnewline_alt;
	BOOL	m_bbk_plus_qm;
	BOOL	m_bbk_braces;
	BOOL	m_bbk_parens;
	BOOL	m_bbk_refs;
	BOOL	m_bbk_vbar;
	BOOL	m_bliteral;
	BOOL	m_bcollate;
	BOOL	m_bperlex;
	BOOL	m_bnosubs;
	BOOL	m_bmatch_not_dot_newline;
	BOOL	m_bmatch_not_dot_null;
	BOOL	m_bmatch_any;
	BOOL	m_bmatch_not_null;
	BOOL	m_bmatch_continuous;
	BOOL	m_bmatch_extra;
	BOOL	m_bmatch_single_line;
	BOOL	m_bformat_perl;
	BOOL	m_bformat_sed;
	BOOL	m_bformat_all;
	BOOL	m_bformat_first_only;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegexSyntaxDlg)
	protected:
	virtual void DoDataExchange (CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegexSyntaxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioNone();
	afx_msg void OnRadioBasic();
	afx_msg void OnRadioExtended();
	afx_msg void OnRadioPerl();
	afx_msg void OnRadioEmacs();
	afx_msg void OnRadioAwk();
	afx_msg void OnRadioGrep();
	afx_msg void OnRadioEgrep();
	afx_msg void OnOk ();
	afx_msg BOOL OnHelpInfo (HELPINFO *pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void ClearDisabledSyntaxFlags ();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGEXSYNTAXDLG_H__5A7736E1_55F2_4242_AD34_CADA03B708AF__INCLUDED_)
