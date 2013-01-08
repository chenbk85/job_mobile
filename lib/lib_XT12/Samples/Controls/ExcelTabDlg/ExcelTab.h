// ExcelTab.h : main header file for the EXCELTAB application
//

#if !defined(AFX_EXCELTAB_H__2AC462D9_4175_4E18_A52C_A4D33630B1DD__INCLUDED_)
#define AFX_EXCELTAB_H__2AC462D9_4175_4E18_A52C_A4D33630B1DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExcelTabApp:
// See ExcelTab.cpp for the implementation of this class
//

class CExcelTabApp : public CWinApp
{
public:
	CExcelTabApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelTabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExcelTabApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELTAB_H__2AC462D9_4175_4E18_A52C_A4D33630B1DD__INCLUDED_)
