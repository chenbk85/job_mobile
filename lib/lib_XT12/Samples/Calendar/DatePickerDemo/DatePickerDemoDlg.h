// DatePickerDemoDlg.h : header file
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

#if !defined(AFX_EE95B23A_1234_4ABB_B336_2C161F0CB650__INCLUDED_)
#define AFX_EE95B23A_1234_4ABB_B336_2C161F0CB650__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DatePickerCombo.h"

// CDatePickerDemoDlg dialog
class CDatePickerDemoDlg : public CDialog
{
// Construction
public:
	CDatePickerDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDatePickerDemoDlg)
	enum { IDD = IDD_DATEPICKERDEMO_DIALOG };
	CDatePickerCombo	m_cmbDatePicker;
	CXTPDatePickerControl m_wndDatePicker;
	CComboBox m_cmbFirstWeekDay;
	CComboBox m_cmbMaxSelDays;
	//}}AFX_DATA

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
	HICON m_hIcon;
	CToolTipCtrl m_ToolTip;

	// Generated message map functions
	//{{AFX_MSG(CDatePickerDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCbnChangeFirstWeekDay();
	afx_msg void OnCbnChangeMaxSelDays();
	afx_msg void OnCbnEditMaxSelDays();
	afx_msg void OnBnClickedSelTextFont();
	afx_msg void OnCheckThemeOffice2007();
	//}}AFX_MSG
	afx_msg void OnButtonPressed(NMHDR * pNotifyStruct, LRESULT * result);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeEditGridSize();
	
	int m_nRows;// Rows count
	int m_nCols;// Number of columns

	void UpdateRowsColsControls();

	BOOL m_bShowWeekNumbers;
	afx_msg void OnBnClickedCheckShowWeekNumbers();

	BOOL m_bHighlightToday;
	afx_msg void OnBnClickedCheckHighlightToday();

	BOOL m_bShowTodayBtn;
	afx_msg void OnBnClickedCheckShowTodayBtn();

	BOOL m_bShowNoneBtn;
	afx_msg void OnBnClickedCheckShowNoneBtn();

	BOOL m_bIsAutoSize;
	afx_msg void OnClickedCheckAutoSize();

	BOOL m_bShowNonMonthDays;
	afx_msg void OnBnClickedCheckNonMonthDays();

	BOOL m_bShow3DBorder;
	afx_msg void OnBnClickedCheckShow3dBorder();

	CString m_strPopup;
	afx_msg void OnBnClickedBtnPopup();

	CEdit m_edtCols;
	CEdit m_edtRows;

	afx_msg void OnClickedTheme();

	BOOL m_bTheme;
	BOOL m_bThemeOffice2007;
};

#endif
