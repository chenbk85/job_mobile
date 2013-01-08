// tool_Grid.h : main header file for the tool_Grid application
//

#if !defined(AFX_XPTHEMEDEMO_H__2BAE785C_4385_40B3_80F7_9E437D33F1FB__INCLUDED_)
#define AFX_XPTHEMEDEMO_H__2BAE785C_4385_40B3_80F7_9E437D33F1FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// tool_GridApp:
// See tool_Grid.cpp for the implementation of this class
//

class tool_GridApp : public CWinApp
{
public:
	tool_GridApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tool_GridApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(tool_GridApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	afx_msg void OnViewShowcmddlg();
};
extern tool_GridApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPTHEMEDEMO_H__2BAE785C_4385_40B3_80F7_9E437D33F1FB__INCLUDED_)
