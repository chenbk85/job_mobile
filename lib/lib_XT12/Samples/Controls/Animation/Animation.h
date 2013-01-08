// Animation.h : main header file for the ANIMATION application
//

#if !defined(AFX_ANIMATION_H__BFEF9CD2_5D4A_4A24_B769_4A0330B1A70A__INCLUDED_)
#define AFX_ANIMATION_H__BFEF9CD2_5D4A_4A24_B769_4A0330B1A70A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnimationApp:
// See Animation.cpp for the implementation of this class
//

class CAnimationApp : public CWinApp
{
public:
	CAnimationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnimationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATION_H__BFEF9CD2_5D4A_4A24_B769_4A0330B1A70A__INCLUDED_)
