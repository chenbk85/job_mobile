// ActionsSample.h : main header file for the ACTIONSSAMPLE application
//

#if !defined(AFX_ACTIONSSAMPLE_H__9DF2AE05_1713_4657_AC0E_71DE91D2C7C7__INCLUDED_)
#define AFX_ACTIONSSAMPLE_H__9DF2AE05_1713_4657_AC0E_71DE91D2C7C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CActionsSampleApp:
// See ActionsSample.cpp for the implementation of this class
//

class CActionsSampleApp : public CWinApp
{
public:
	CActionsSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActionsSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CActionsSampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIONSSAMPLE_H__9DF2AE05_1713_4657_AC0E_71DE91D2C7C7__INCLUDED_)
