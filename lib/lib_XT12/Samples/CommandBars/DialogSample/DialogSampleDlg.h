// DialogSampleDlg.h : header file
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

#if !defined(AFX_DIALOGSAMPLEDLG_H__0CF87B66_A664_47DA_B6D7_BF0D8BA051C2__INCLUDED_)
#define AFX_DIALOGSAMPLEDLG_H__0CF87B66_A664_47DA_B6D7_BF0D8BA051C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogSampleDlg dialog

#define CDialogSampleDlgBase CXTPDialogBase<CXTResizeDialog>

class CDialogSampleDlg : public CDialogSampleDlgBase
{
// Construction
public:
	CDialogSampleDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogSampleDlg)
	enum { IDD = IDD_DIALOGSAMPLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSampleDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CXTPStatusBar m_wndStatusBar;

	void RepositionControls();
	CRect m_rcBorders;
	BOOL m_bInRepositionControls, m_bInitDone;
	XTPPaintTheme m_eTheme;
	

	// Generated message map functions
	//{{AFX_MSG(CDialogSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHelpAbout();
	afx_msg void OnFileExit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM wp, LPARAM lCount);
	afx_msg void OnEmptyCommand();
	afx_msg void OnCustomize();
	void OnUpdateKeyIndicator(CCmdUI* pCmdUI);
	LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
	void GetMessageString(UINT nID, CString& rMessage) const;
	void OnEmptyCommandRange(UINT);
	afx_msg void OnTheme(UINT nTheme);
	afx_msg void OnUpdateTheme(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSAMPLEDLG_H__0CF87B66_A664_47DA_B6D7_BF0D8BA051C2__INCLUDED_)
