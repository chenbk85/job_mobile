#if !defined(AFX_FINDREPLACEDLG_H__8AD1BA41_D1EB_4C41_ACAC_DDE7C860D1C9__INCLUDED_)
#define AFX_FINDREPLACEDLG_H__8AD1BA41_D1EB_4C41_ACAC_DDE7C860D1C9__INCLUDED_

#include "resource.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindReplaceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindReplaceDlg dialog

class CFindReplaceDlg : public CDialogBar
{
// Construction
public:
	CFindReplaceDlg ();
	void SetInitial (CWnd *pParentWnd, const int IDD);
	int GetIDD () const { return m_IDD; }
	void SetWholeWordOnly (const bool bWholeWordOnly);
	void SetMatchCase (const bool bMatchCase);
	void SetRegEx (const bool bRegEx);
	void SetSearchUp (const bool bUp);
	void SetCloseOnMatch (const bool bCloseOnMatch);
	void SetReplaceAllLikeNotepad (const bool bReplaceAllLikeNotepad);
	const CString &GetFindText ();
	const CString &GetReplaceText ();
	void SetFindText (const CString &strFind);
	void SetReplaceText (const CString &strReplace);

// Dialog Data
	//{{AFX_DATA(CFindReplaceDlg)
	enum { IDD = IDD_FIND_REPLACE };
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindReplaceDlg)
	protected:
	virtual void DoDataExchange (CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindReplaceDlg)
	afx_msg LONG OnInitDialog (UINT wParam, LONG lParam);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnCheckWholeWord();
	afx_msg void OnCheckMatchCase ();
	afx_msg void OnCheckRegex ();
	afx_msg void OnCheckLikeNotepad();
	afx_msg void OnRadioUp ();
	afx_msg void OnRadioDown ();
	afx_msg void OnCheckCloseOnMatch();
	afx_msg void OnOk();
	afx_msg void OnButtonReplace ();
	afx_msg void OnButtonReplaceAll ();
	virtual void OnCancel ();
	afx_msg void OnButtonHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//	virtual BOOL OnInitDialog ();

private:
	CWnd *m_pParentWnd;
	int m_IDD;
	CButton m_CheckWholeWordOnly;
	CButton m_CheckMatchCase;
	CButton m_CheckRegEx;
	CButton m_CheckReplaceAllLikeNotepad;
	CButton m_RadioUp;
	CButton m_RadioDown;
	CButton m_CheckCloseOnMatch;
	CButton m_ButtonReplace;
	CEdit m_EditFindText;
	CEdit m_EditReplaceText;
	const CString m_strInitialFind;
	const bool m_bInitialWholeWordOnly;
	const bool m_bInitialMatchCase;
	const bool m_bInitialRegEx;
	CString m_strFindText;
	CString m_strReplaceText;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDREPLACEDLG_H__8AD1BA41_D1EB_4C41_ACAC_DDE7C860D1C9__INCLUDED_)
