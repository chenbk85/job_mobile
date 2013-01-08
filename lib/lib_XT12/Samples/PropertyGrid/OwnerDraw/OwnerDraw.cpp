// OwnerDraw.cpp : Defines the class behaviors for the application.
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OwnerDraw.h"

#include "DialogSheet.h"
#include "StandardGridPage.h"
#include "CoolGridPage.h"
#include "SimpleGridPage.h"
#include "DelphiGridPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawApp

BEGIN_MESSAGE_MAP(COwnerDrawApp, CWinApp)
	//{{AFX_MSG_MAP(COwnerDrawApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawApp construction

COwnerDrawApp::COwnerDrawApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COwnerDrawApp object

COwnerDrawApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawApp initialization

BOOL COwnerDrawApp::InitInstance()
{
	AfxEnableControlContainer();
	CXTPWinDwmWrapper().SetProcessDPIAware();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();         // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif
#endif // MFC 6.0 or earlier

	//COwnerDrawDlg dlg;
	CDialogSheet dlg(_T("Codejock Owner Draw Property Grid Sample"));
	dlg.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	dlg.m_psh.dwFlags &= ~PSH_HASHELP;

	CStandardGridPage pageStandard;
	pageStandard.m_psp.dwFlags &= ~PSP_HASHELP;
	dlg.AddPage(&pageStandard);

	CCoolGridPage pageIcons;
	pageIcons.m_psp.dwFlags &= ~PSP_HASHELP;
	dlg.AddPage(&pageIcons);

	CSimpleGridPage pageSimple;
	pageSimple.m_psp.dwFlags &= ~PSP_HASHELP;
	dlg.AddPage(&pageSimple);

	CDelphiGridPage pageDelphi;
	pageDelphi.m_psp.dwFlags &= ~PSP_HASHELP;
	dlg.AddPage(&pageDelphi);

	m_pMainWnd = &dlg;
	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
