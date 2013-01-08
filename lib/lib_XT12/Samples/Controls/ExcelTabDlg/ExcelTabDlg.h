// ExcelTabDlg.h : header file
//

#if !defined(AFX_EXCELTABDLG_H__2DC6EEE5_2212_49E8_BB7C_C8D9DDEB18AC__INCLUDED_)
#define AFX_EXCELTABDLG_H__2DC6EEE5_2212_49E8_BB7C_C8D9DDEB18AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExcelTabDlg dialog

#include "ExcelListCtrl.h"
#include "ExcelEditCtrl.h"
#include "ExcelTreeCtrl.h"
#include "ExcelFormView.h"
#include "ExcelScrollView.h"

class CExcelTab
{
public:
	CExcelTab() : m_pWndTab(NULL) {}
	CString m_csTab;
	CWnd* m_pWndTab;
};

typedef CList<CExcelTab, CExcelTab&> CExcelTabArray;

class CExcelTabDlg : public CXTResizeDialog
{
// Construction
public:
	CExcelTabDlg(CWnd* pParent = NULL);	// standard constructor
	void UpdateExcelTab();

	//{{AFX_DATA(CExcelTabDlg)
	enum { IDD = IDD_EXCELTAB_DIALOG };
	CStatic	m_staticBorder;
	//}}AFX_DATA

protected:
	CRect m_rTabCtrl;
	CFont m_font;
	CXTPEmptyRect m_rcTabs;
	CXTExcelTabCtrl* m_pExcelTabCtrl;
	CExcelTabArray m_arExcelTabs;

	DWORD m_dwTabStyle;
	BOOL  m_bBottom;
	BOOL  m_bHasArrows;
	BOOL  m_bHasHomeEnd;
	BOOL  m_bHScroll;

	// use the flicker free template class, this will create the objects
	// making them flicker free!
	CXTNoFlickerWnd <CExcelListCtrl> m_sheet1;
	CXTNoFlickerWnd <CExcelEditCtrl> m_sheet2;
	CXTNoFlickerWnd <CExcelTreeCtrl> m_sheet3;
	CXTNoFlickerWnd <CXTListBox>      m_sheet4;
	CXTNoFlickerWnd <CXTListBox>      m_sheet5;
	CXTNoFlickerWnd <CXTListBox>      m_sheet6;
	CExcelFormView*                  m_pSheet7;
	CExcelScrollView*                m_pSheet8;

	void CalcTabRect();
	BOOL CreateExcelTab();
	void UpdateTabsStyle();
	BOOL CreateSheet1();
	BOOL CreateSheet2();
	BOOL CreateSheet3();
	BOOL CreateSheet4();
	BOOL CreateSheet5();
	BOOL CreateSheet6();
	BOOL CreateSheet7();
	BOOL CreateSheet8();

	//{{AFX_VIRTUAL(CExcelTabDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExcelTabDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnProperties();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CExcelTabProperties;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELTABDLG_H__2DC6EEE5_2212_49E8_BB7C_C8D9DDEB18AC__INCLUDED_)
