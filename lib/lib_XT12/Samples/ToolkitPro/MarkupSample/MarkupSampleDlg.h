// MarkupSampleDlg.h : header file
//

#if !defined(AFX_MARKUPSAMPLEDLG_H__E6161FD9_6D1A_4018_B00E_6AA977CAB4BF__INCLUDED_)
#define AFX_MARKUPSAMPLEDLG_H__E6161FD9_6D1A_4018_B00E_6AA977CAB4BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MarkupListCtrl.h"
#include "MarkupStatic.h"
#include "MarkupTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMarkupSampleDlg dialog

class CMarkupSampleDlg : public CXTResizeDialog
{
// Construction
public:
	CMarkupSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMarkupSampleDlg)
	enum { IDD = IDD_MARKUPSAMPLE_DIALOG };
	CMarkupTreeCtrl	m_wndTree;
	CXTPButton	m_btnMore;
	CXTPButton	m_wndCheckBox;
	CXTPButton	m_wndButton;
	CXTPButton	m_wndRadio;
	CMarkupStatic	m_wndStatic;
	CMarkupListCtrl	m_wndList;
	CXTPTabControl m_wndTabControl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void AddListItem(LPCTSTR lpszMarkup);	


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMarkupSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMorePopupcontrol();
	afx_msg void OnMoreUnicodesupport();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMoreTaskdialog();
	//}}AFX_MSG
	
	void OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);

	void OnMoreDropDown();
	void OnTabControlSelChanged(NMHDR* pHeader, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPSAMPLEDLG_H__E6161FD9_6D1A_4018_B00E_6AA977CAB4BF__INCLUDED_)
