// WinExplorer.h : main header file for the WINEXPLORER application
//

#if !defined(AFX_WINEXPLORER_H__C47715EC_F0DC_48FA_8915_E32F8CBC4D9A__INCLUDED_)
#define AFX_WINEXPLORER_H__C47715EC_F0DC_48FA_8915_E32F8CBC4D9A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerApp:
// See WinExplorer.cpp for the implementation of this class
//

class CWinExplorerApp : public CWinApp
{
public:
	CWinExplorerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinExplorerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinExplorerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINEXPLORER_H__C47715EC_F0DC_48FA_8915_E32F8CBC4D9A__INCLUDED_)
