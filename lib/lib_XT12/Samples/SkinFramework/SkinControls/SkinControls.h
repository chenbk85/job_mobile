// SkinControls.h : main header file for the SKINCONTROLS application
//

#if !defined(AFX_SKINCONTROLS_H__46375DD6_5208_44CC_B451_9FB8556713BD__INCLUDED_)
#define AFX_SKINCONTROLS_H__46375DD6_5208_44CC_B451_9FB8556713BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkinControlsApp:
// See SkinControls.cpp for the implementation of this class
//

class CSkinControlsApp : public CWinApp
{
public:
	CSkinControlsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinControlsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSkinControlsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINCONTROLS_H__46375DD6_5208_44CC_B451_9FB8556713BD__INCLUDED_)
