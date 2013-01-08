// TaskPageRadioButtons.h : header file
//
#if !defined(__TASKPAGERADIOBUTTONS_H__)
#define __TASKPAGERADIOBUTTONS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTaskPageRadioButtons dialog

class CTaskSheetProperties;
class CTaskPageRadioButtons : public CPropertyPage
{
	DECLARE_DYNCREATE(CTaskPageRadioButtons)

public:
	CTaskPageRadioButtons();
	~CTaskPageRadioButtons();

	//{{AFX_DATA(CTaskPageRadioButtons)
	enum { IDD = IDD_TASKDIALOG_RADIOBUTTONS };
	CStatic	m_txtDefault;
	CButton	m_btnRemove;
	CButton	m_btnEdit;
	CButton	m_btnAdd;
	CXTListCtrl	m_listCustom;
	CComboBox	m_comboDefault;
	BOOL	m_bNoDefault;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTaskPageRadioButtons)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

	void EnableButtons();
	void InsertItem(UINT nString, UINT nID);
	void InsertItem(CString strText, UINT nID);

protected:
	CTaskSheetProperties* m_pDlgParent;

	//{{AFX_MSG(CTaskPageRadioButtons)
	afx_msg void OnChkNoDefault();
	afx_msg void OnSelEndOkDefault();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnRemove();
	afx_msg void OnItemChangedListCustom(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TASKPAGERADIOBUTTONS_H__)
