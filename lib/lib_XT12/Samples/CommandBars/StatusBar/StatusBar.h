// StatusBar.h : main header file for the STATUSBAR application
//

#if !defined(AFX_STATUSBAR_H__6BB192A8_ACF7_42DD_AD36_CE871F5593E8__INCLUDED_)
#define AFX_STATUSBAR_H__6BB192A8_ACF7_42DD_AD36_CE871F5593E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStatusBarApp:
// See StatusBar.cpp for the implementation of this class
//

class CStatusBarApp : public CWinApp
{
public:
	CStatusBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CStatusBarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSBAR_H__6BB192A8_ACF7_42DD_AD36_CE871F5593E8__INCLUDED_)
