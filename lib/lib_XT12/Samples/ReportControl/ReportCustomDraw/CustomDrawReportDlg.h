// CustomDrawReportDlg.h : header file
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

#if !defined(AFX_CUSTOMDRAWREPORTDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_)
#define AFX_CUSTOMDRAWREPORTDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "XTPCustomDrawReportPaintManager.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomDrawReportDlg dialog


class CCustomDrawReportDlg : public CXTResizeDialog
{
// Construction
public:
	CCustomDrawReportDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomDrawReportDlg)
	enum { IDD = IDD_CUSTOMDRAWREPORT_DIALOG };
	CXTPReportControl m_wndReportCtrl;
	//}}AFX_DATA

	CImageList m_ilControls;
	int m_nDrawingMethod;

	unsigned int GetControlsNumber(CXTPReportRecordItem* pItem);
	unsigned int GetControlsNumber(CXTPReportRow* pRow);
	int GetRowHeight(CDC* /*pDC*/, CXTPReportRow* pRow);
	BOOL DrawItem(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomDrawReportDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCustomDrawReportDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnUseDrawframecontrol();
	afx_msg void OnUseDrawstate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMDRAWREPORTDLG_H__6518CEDC_5B8C_44DD_A813_4B4E67DBB931__INCLUDED_)
