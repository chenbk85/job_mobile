// FontCombo.h : main header file for the FONTCOMBO application
//

#if !defined(AFX_FONTCOMBO_H__9F650632_939A_49AD_A3D9_09B6BC60A05E__INCLUDED_)
#define AFX_FONTCOMBO_H__9F650632_939A_49AD_A3D9_09B6BC60A05E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFontComboApp:
// See FontCombo.cpp for the implementation of this class
//

class CFontComboApp : public CWinApp
{
public:
	CFontComboApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontComboApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFontComboApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTCOMBO_H__9F650632_939A_49AD_A3D9_09B6BC60A05E__INCLUDED_)
