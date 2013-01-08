// MarkupSample.h : main header file for the MARKUPSAMPLE application
//

#if !defined(AFX_MARKUPSAMPLE_H__9D1AED5D_9EC2_4647_89BA_A3FE7EF7623B__INCLUDED_)
#define AFX_MARKUPSAMPLE_H__9D1AED5D_9EC2_4647_89BA_A3FE7EF7623B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMarkupSampleApp:
// See MarkupSample.cpp for the implementation of this class
//

class CMarkupSampleApp : public CWinApp
{
public:
	CMarkupSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMarkupSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPSAMPLE_H__9D1AED5D_9EC2_4647_89BA_A3FE7EF7623B__INCLUDED_)
