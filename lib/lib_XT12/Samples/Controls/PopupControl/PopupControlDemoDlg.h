// PopupControlDemoDlg.h : header file
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

#if !defined(AFX_POPUPWNDDEMODLG_H__375F8BC3_56DB_4F1F_9380_47F7460E9456__INCLUDED_)
#define AFX_POPUPWNDDEMODLG_H__375F8BC3_56DB_4F1F_9380_47F7460E9456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CPopupControlDemoDlg dialog

class CPopupControlDemoDlg : public CDialog
{

// Construction
public:
	CPopupControlDemoDlg(CWnd* pParent = NULL); // standard constructor
	~CPopupControlDemoDlg();

// Dialog Data
	//{{AFX_DATA(CPopupControlDemoDlg)
	enum { IDD = IDD_POPUPWNDDEMO_DIALOG };
	CXTPButton	m_btnMore;
	CSliderCtrl m_Slider;
	int     m_nTheme;
	int     m_nAnimation;
	UINT    m_uAnimDelay;
	UINT    m_uShowDelay;
	BOOL    m_bAllowMove;
	//}}AFX_DATA
	void SetTheme();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupControlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//init theme of popup window
	void SetMSNTheme();
	void SetOffice2003Theme();
	void SetOffice2007Theme();
	void SetDefaultTheme();
	void SetOfficeXPTheme();
	void SetBlueTheme();
	void SetBlackTheme();
	void SetGreenTheme();
	void SetRedTheme();
	void SetTooltipTheme();

	//enable/disable of dialog controls
	void EnableItems(BOOL bEnable);
	void SetDefaults();

// Implementation
protected:
	//handle to icon
	HICON m_hIcon;
	CPoint m_ptPopup;
	
	void FindBestPosition(CSize szPopup);


	//popup window object
	CList<CXTPPopupControl*, CXTPPopupControl*> m_lstPopupControl;
	CXTPPopupControl* m_pActivePopup;

	// Generated message map functions
	//{{AFX_MSG(CPopupControlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonShow();
	afx_msg void OnSelchangeComboTheme();
	afx_msg void OnReleasedcaptureSliderTransparent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboAnimation();
	afx_msg void OnChangeEditAnimationdelay();
	afx_msg void OnChangeEditShowdelay();
	afx_msg void OnCheckAllowMove();
	afx_msg void OnMoreRtfsample();
	afx_msg void OnMoreMarkupsample();
	afx_msg void OnMoreLayerSample();
	//}}AFX_MSG
	void OnMoreDropDown();

	afx_msg LRESULT OnPopUpNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPWNDDEMODLG_H__375F8BC3_56DB_4F1F_9380_47F7460E9456__INCLUDED_)
