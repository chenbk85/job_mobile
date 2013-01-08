// VistaTaskDialog.h : main header file for the VISTATASKDIALOG application
//

#if !defined(AFX_VISTATASKDIALOG_H__8E713BA4_026A_4783_9B5F_2E11207CD531__INCLUDED_)
#define AFX_VISTATASKDIALOG_H__8E713BA4_026A_4783_9B5F_2E11207CD531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVistaTaskDialogApp:
// See VistaTaskDialog.cpp for the implementation of this class
//

class CVistaTaskDialogApp : public CWinApp
{
public:
	CVistaTaskDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVistaTaskDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVistaTaskDialogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CVistaTaskDialogApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISTATASKDIALOG_H__8E713BA4_026A_4783_9B5F_2E11207CD531__INCLUDED_)
