// SmartLayout.h : main header file for the SMARTLAYOUT application
//

#if !defined(AFX_SMARTLAYOUT_H__CA0D0A31_0926_4D3D_870D_99B4F7FB2C81__INCLUDED_)
#define AFX_SMARTLAYOUT_H__CA0D0A31_0926_4D3D_870D_99B4F7FB2C81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutApp:
// See SmartLayout.cpp for the implementation of this class
//

class CSmartLayoutApp : public CWinApp
{
public:
	CSmartLayoutApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmartLayoutApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSmartLayoutApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMARTLAYOUT_H__CA0D0A31_0926_4D3D_870D_99B4F7FB2C81__INCLUDED_)
