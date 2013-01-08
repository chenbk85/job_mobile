// ServerAgent.h : main header file for the ServerAgent application
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
// ServerAgentApp:
// See ServerAgent.cpp for the implementation of this class
//

class ServerAgentApp : public CWinApp
{
public:
	ServerAgentApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ServerAgentApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(ServerAgentApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	afx_msg void OnViewShowcmddlg();
};
extern ServerAgentApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#define var_enum(func)\
	func(ServerAgent,GridView_RTTI_NAME,_T("grid_ServerAgent"),0,"grid_default.xml rtti name")\

var_enum(jCV_DECLARE);


#endif // !defined(AFX_XPTHEMEDEMO_H__2BAE785C_4385_40B3_80F7_9E437D33F1FB__INCLUDED_)
