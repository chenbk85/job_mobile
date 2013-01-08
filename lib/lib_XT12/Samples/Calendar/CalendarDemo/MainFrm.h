// MainFrm.h : interface of the CMainFrame class
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

#if !defined(AFX_MAINFRM_H__6EF5FD88_874F_4508_B332_F53B60A56122__INCLUDED_)
#define AFX_MAINFRM_H__6EF5FD88_874F_4508_B332_F53B60A56122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OptionsDialogBar.h"

	#ifdef _XTP_INCLUDE_RIBBON
		#define CMainFrameBase CXTPFrameWnd, CXTPOffice2007FrameHook
	#else
		#define CMainFrameBase CXTPFrameWnd
	#endif

class CDatePickerDialogBar : public CDialogBar
{
public:
	CDatePickerDialogBar();   // standard constructor	
	~CDatePickerDialogBar(){};

	CXTPDatePickerControl m_wndDatePicker;

protected:
	afx_msg void OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

class CMainFrame : public CMainFrameBase
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CDatePickerDialogBar m_dlgDatePicker;
	COptionsDialogBar m_dlgOptions;	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	CString _GetTheme2007Style_file(int nTheme2007Style);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	afx_msg void OnOfficeThemeChanged(NMHDR* pNMHDR, LRESULT* pResult);
	
	//}}AFX_MSG

	void SetOfficeTheme(int nTheme);
	int m_nOfficeTheme;
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6EF5FD88_874F_4508_B332_F53B60A56122__INCLUDED_)
