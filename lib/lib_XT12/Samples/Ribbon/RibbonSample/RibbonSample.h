// RibbonSample.h : main header file for the RIBBONSAMPLE application
//

#if !defined(AFX_RIBBONSAMPLE_H__74489F48_E565_4B03_B8D5_A9D066133B66__INCLUDED_)
#define AFX_RIBBONSAMPLE_H__74489F48_E565_4B03_B8D5_A9D066133B66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRibbonSampleApp:
// See RibbonSample.cpp for the implementation of this class
//

class CRibbonSampleApp : public CWinApp
{
public:
	CRibbonSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRibbonSampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONSAMPLE_H__74489F48_E565_4B03_B8D5_A9D066133B66__INCLUDED_)
