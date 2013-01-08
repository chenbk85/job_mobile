// TabbedToolbar.h : main header file for the TABBEDTOOLBAR application
//

#if !defined(AFX_TABBEDTOOLBAR_H__3F4E7BA5_1974_4801_9E7A_1CF8E49E1DE0__INCLUDED_)
#define AFX_TABBEDTOOLBAR_H__3F4E7BA5_1974_4801_9E7A_1CF8E49E1DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarApp:
// See TabbedToolbar.cpp for the implementation of this class
//

class CTabbedToolbarApp : public CWinApp
{
public:
	CTabbedToolbarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabbedToolbarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTabbedToolbarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABBEDTOOLBAR_H__3F4E7BA5_1974_4801_9E7A_1CF8E49E1DE0__INCLUDED_)
