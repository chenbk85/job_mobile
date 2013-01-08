// notepadre.h : main header file for the NOTEPADRE application
//

#if !defined(AFX_NOTEPADRE_H__40872B48_B193_4751_9CED_B9C26B8435D8__INCLUDED_)
#define AFX_NOTEPADRE_H__40872B48_B193_4751_9CED_B9C26B8435D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNotepadreApp:
// See notepadre.cpp for the implementation of this class
//

class CNotepadreApp : public CWinApp
{
public:
	CNotepadreApp();
	int DoPrintDialog (CPrintDialog *pPD);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotepadreApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNotepadreApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void ParseCommandLine (CCommandLineInfo &rCmdInfo, bool &bReadOnly);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEPADRE_H__40872B48_B193_4751_9CED_B9C26B8435D8__INCLUDED_)
