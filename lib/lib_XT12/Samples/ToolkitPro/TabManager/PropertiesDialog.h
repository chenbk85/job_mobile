// PropertiesDialog.h : header file
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

#if !defined(AFX_PROPERTIESDIALOG_H__BBDED013_07FE_4BB0_92D1_E08684838EDD__INCLUDED_)
#define AFX_PROPERTIESDIALOG_H__BBDED013_07FE_4BB0_92D1_E08684838EDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabClientPage.h"
#include "TabMarginsPage.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDialog dialog

class CPropertiesDialog : public CXTPPropertySheet
{
// Construction
public:
	CPropertiesDialog(CWnd* pParent = NULL);   // standard constructor

	CTabClientPage m_pageTabClient;
	CTabControlPage m_pageTabControl;
	CTabDockingPanePage m_pageDockingPane;
	CTabPanelPage m_pagePanel;
	CTabMarginsPage m_pageMargins;

	CImageList m_ilTabCtrl;

	void UpdateAll();
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesDialog)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertiesDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESDIALOG_H__BBDED013_07FE_4BB0_92D1_E08684838EDD__INCLUDED_)
