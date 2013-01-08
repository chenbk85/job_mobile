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

#if !defined(AFX_MAINFRM_H__CC735978_9C75_11D3_9992_00500487D199__INCLUDED_)
#define AFX_MAINFRM_H__CC735978_9C75_11D3_9992_00500487D199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PropertiesDialog.h"


class CXTTrayIconEx : public CXTTrayIcon
{
	bool CreateMinimizeWnd(CWnd* /*pWndApp*/)
	{
		return true;
	}
};

#define CMainFrameBase CXTPFrameWnd


class CMainFrame : public CMainFrameBase
{

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void RestoreWindow();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	void SetTheme(int iTheme);

	CXTPStatusBar   m_wndStatusBar;

	CXTTrayIconEx           m_TrayIcon;
	CPropertiesDialog   m_propDlg;
	CXTRegistryManager m_regMgr;
	int            m_iTheme;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRestore();
	afx_msg void OnViewThemeOfficeXP();
	afx_msg void OnUpdateViewThemeOfficeXP(CCmdUI* pCmdUI);
	afx_msg void OnProperties();
	afx_msg void OnAppExit();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg void OnCustomize();
	afx_msg LRESULT OnTrayIconNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	friend class CPropertiesDialog;
	friend class CTrayIconDemoApp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CC735978_9C75_11D3_9992_00500487D199__INCLUDED_)
