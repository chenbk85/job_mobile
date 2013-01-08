// ReportCustomHeap.h : main header file for the REPORTCUSTOMHEAP application
//

#if !defined(AFX_REPORTCUSTOMHEAP_H__F240C66F_4D1B_4CB7_95CD_955E35E55FE1__INCLUDED_)
#define AFX_REPORTCUSTOMHEAP_H__F240C66F_4D1B_4CB7_95CD_955E35E55FE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapApp:
// See ReportCustomHeap.cpp for the implementation of this class
//

class CReportCustomHeapApp : public CWinApp
{
public:
	CReportCustomHeapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCustomHeapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CReportCustomHeapApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCUSTOMHEAP_H__F240C66F_4D1B_4CB7_95CD_955E35E55FE1__INCLUDED_)
