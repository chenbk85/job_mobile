#if !defined(AFX_PAGEKEYBOARD_H__FA5C0CB8_E878_4C38_866B_7ED540C6A918__INCLUDED_)
#define AFX_PAGEKEYBOARD_H__FA5C0CB8_E878_4C38_866B_7ED540C6A918__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageKeyboard.h : header file
//

#include <afxtempl.h>

#include "resource.h"
#include "OptionsPage.h"
//#include "KeyAssign.h"
/////////////////////////////////////////////////////////////////////////////
// CPageKeyboard dialog

class CPageKeyboard : public COptionsPage
{
	DECLARE_DYNCREATE(CPageKeyboard)

// Construction
public:
	void Filter();
	CPageKeyboard();
	~CPageKeyboard();

// Dialog Data
	//{{AFX_DATA(CPageKeyboard)
	enum { IDD = IDD_PAGE_KEYBOARD };
	CComboBox	m_cmbUsed;
	CComboBox	m_cmbShortcuts;
	CListBox	m_wndList;
	CString	m_strFilter;
	//}}AFX_DATA

	CXTPShortcutManager::CKeyAssign m_wndAssign;

	struct LISTINFO
	{
		CString strTitle;
		UINT nID;
	};
	CArray<LISTINFO, LISTINFO&> m_arrMenu ;

	CXTPShortcutManager* m_pShortcutManager;

// Operations

protected:
	void GetMenuStrings(CXTPCommandBar* pBar, CString strPrefix);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageKeyboard)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageKeyboard)
	virtual BOOL OnInitDialog();
	afx_msg void OnFilterChange();
	afx_msg void OnListChange();
	afx_msg void OnAssignChange();
	afx_msg void OnButtonAssign();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonResetAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEKEYBOARD_H__FA5C0CB8_E878_4C38_866B_7ED540C6A918__INCLUDED_)
