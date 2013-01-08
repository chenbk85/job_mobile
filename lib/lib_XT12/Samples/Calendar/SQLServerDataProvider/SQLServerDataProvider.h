// SQLServerDataProvider.h : main header file for the SQLSERVERDATAPROVIDER application
//

#if !defined(AFX_SQLSERVERDATAPROVIDER_H__984C5863_6D59_486D_AE44_BF9EB40F74DE__INCLUDED_)
#define AFX_SQLSERVERDATAPROVIDER_H__984C5863_6D59_486D_AE44_BF9EB40F74DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

static const LPCTSTR csOptProfileSection		= _T("CalendarSQLServerDataProviderSample");
static const LPCTSTR csOptDataSourceSQLsrvProp	= _T("DataSource_SQLsrv");
	static const LPCTSTR csOptDataSourceSQLsrvProp_default	= _T("Provider=SQLOLEDB.1;...");

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderApp:
// See SQLServerDataProvider.cpp for the implementation of this class
//

class CSQLServerDataProviderApp : public CWinApp
{
public:
	CSQLServerDataProviderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQLServerDataProviderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSQLServerDataProviderApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQLSERVERDATAPROVIDER_H__984C5863_6D59_486D_AE44_BF9EB40F74DE__INCLUDED_)
