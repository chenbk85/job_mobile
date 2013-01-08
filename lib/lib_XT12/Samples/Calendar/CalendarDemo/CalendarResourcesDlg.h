// CalendarResourcesDlg.h : header file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALENDARRESOURCESDLG_H__F27ED8D3_BCA4_430D_A121_D2F7259BC6DD__INCLUDED_)
#define AFX_CALENDARRESOURCESDLG_H__F27ED8D3_BCA4_430D_A121_D2F7259BC6DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

class CCheckListBox_withEvents : public CCheckListBox
{
public:
	CCheckListBox_withEvents();
	void setParentDlg(CCalendarResourcesDlg* pParentDlg);

	void AllSetCheck(int nCheck);

	void LockAllCheckBoxes(int nCheckLocked);
	void UnlockAllCheckBoxes(int nCheck = -1);
	
protected:
	int m_nCheckLocked;
	CCalendarResourcesDlg* m_pParentDlg;
	
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void _OnCheckChanged();
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCalendarResourcesDlg dialog
class CCalendarResourcesDlg : public CDialog
{
	friend class CCheckListBox_withEvents;
// Construction
public:
	CCalendarResourcesDlg(CXTPCalendarResourcesManager* pRCMan, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalendarResourcesDlg)
	enum { IDD = IDD_DIALOG_RESOURCES };
	CButton	m_ctrlResourcesMoveDown;
	CButton	m_ctrlResourcesMoveUp;
	CListCtrl	m_ctrlDataProviders;
	CButton		m_ctrlDataProviderDelete;
	CButton		m_ctrlDataProviderEdit;
	CButton		m_ctrlDataProviderAdd;	
	CCheckListBox	m_ctrlResources;
	CButton			m_ctrlResourcesDelete;
	CButton			m_ctrlResourcesAdd;
	CEdit		m_ctrlRCName;
	CButton		m_ctrlRCNameAuto;
	CComboBox	m_ctrlRCDataProvider;
	CCheckListBox_withEvents m_ctrlSchedules;
	CButton	m_ctrlSchedulesAll;
	CButton	m_ctrlSchedulesDelete;
	CButton	m_ctrlSchedulesAdd;
	CButton	m_ctrlScheduleChangeName;
	CEdit	m_ctrlScheduleNewName;		
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarResourcesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CXTPCalendarResourcesManager* m_pRCMan;
	BOOL m_bChangeEditRcName_internal;

	int m_nRcNameAuto_StoredState;

	void UpdateDataProvidersList();
	void UpdateResourcesList();

	void UpdateResourceInfoPane();
	void UpdateSchedulesList();
	void UpdateSchedulesList_saveState();

	void UpdateDataProviders_RCCombo();
	
	void EnableResourceInfoPane(BOOL bEnable);
	void EnableSchedulesInfoControls(BOOL bEnable);
	void UpdateSchedulesAll_DependsCtrls();

	void ApplySchedules();
	void ApplyUpdateRcNameAuto();
	
	void ProcessAutoName();
	CString _CalcAutoRCName();

	CXTPCalendarResourceDescription* GetSelRCDesc(int* pnIndex = NULL);

	// Generated message map functions
	//{{AFX_MSG(CCalendarResourcesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnDataProviderAdd();
	afx_msg void OnBtnDataProviderDelete();
	afx_msg void OnBtnDataProviderEdit();
	afx_msg void OnBtnResourcesAdd();
	afx_msg void OnBtnResourcesDelete();
	afx_msg void OnBtnSchedulesAdd();
	afx_msg void OnBtnSchedulesDelede();
	afx_msg void OnBtnSchedulesChange();
	afx_msg void OnChkRcNameAuto();
	afx_msg void OnChkSchedulesAll();
	afx_msg void OnChangeEditRcName();
	afx_msg void OnSelchangeListResources();
	afx_msg void OnSelchangeListSchedules();
	afx_msg void OnItemchangedListctrlDataProviders(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeCmbRcDataProvider();
	afx_msg void OnKillfocusListSchedules();
	afx_msg void OnBtnResourcesMoveDown();
	afx_msg void OnBtnResourcesMoveUp();
	//}}AFX_MSG

	void _OnSelchangeSchedules();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARRESOURCESDLG_H__F27ED8D3_BCA4_430D_A121_D2F7259BC6DD__INCLUDED_)
