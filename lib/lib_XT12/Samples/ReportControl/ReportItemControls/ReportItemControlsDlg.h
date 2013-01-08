// ReportItemControlsDlg.h : header file
//

#if !defined(AFX_REPORTITEMCONTROLSDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_)
#define AFX_REPORTITEMCONTROLSDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReportItemControlsDlg dialog


class CReportItemControlsDlg : public CXTResizeDialog
{
// Construction
public:
	CReportItemControlsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CReportItemControlsDlg)
	enum { IDD = IDD_REPORTITEMCONTROLS_DIALOG };
	//}}AFX_DATA
	CXTPReportControl m_wndReportCtrl;

	CImageList m_ilIcons;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportItemControlsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	afx_msg void OnItemButtonClick(NMHDR * pNotifyStruct, LRESULT*);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReportItemControlsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTITEMCONTROLSDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_)
