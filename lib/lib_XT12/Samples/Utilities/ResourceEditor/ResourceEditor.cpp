// ResourceEditor.cpp : Defines the class behaviors for the application.
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
#include "ResourceEditor.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ResourceEditorDoc.h"
#include "ResourceEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorApp

BEGIN_MESSAGE_MAP(CResourceEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CResourceEditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorApp construction

CResourceEditorApp::CResourceEditorApp()
{

}

BOOL IsXMLEngineAvailable() 
{
	CXTPDOMDocumentPtr xmlDocPtr;
	return SUCCEEDED(xmlDocPtr.CreateInstance(CLSID_XTPDOMDocument));
}



/////////////////////////////////////////////////////////////////////////////
// The one and only CResourceEditorApp object

CResourceEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorApp initialization

BOOL CResourceEditorApp::InitInstance()
{

	// get path of executable
	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));

	LPTSTR lpszExt = _tcsrchr(szBuff, '\\');
	if (lpszExt) 
	{
		lpszExt[1] = 0;
		m_strTranslatingPath = szBuff;
	}
	
	if (!FILEEXISTS_S(m_strTranslatingPath + "ToolkitPro.ResourceEn.xml"))
		m_strTranslatingPath += _T("Translations\\");

	
	AfxEnableControlContainer();
	CXTPWinDwmWrapper().SetProcessDPIAware();
	AfxOleInit();

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

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Codejock Software Sample Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_RESOURTYPE,
		RUNTIME_CLASS(CResourceEditorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CResourceEditorView));
	AddDocTemplate(pDocTemplate);

	if (!IsXMLEngineAvailable())
	{
		AfxMessageBox(_T("MSXML (msxml2.dll) is not installed on this computer"));
		return FALSE;
	}

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	{

		if (FILEEXISTS_S(m_strTranslatingPath + "ToolkitPro.ResourceEn.xml"))
		{
			cmdInfo.m_nShellCommand = CCommandLineInfo::FileOpen;
			cmdInfo.m_strFileName = m_strTranslatingPath + "ToolkitPro.ResourceEn.xml";
		}
		else
		{
			cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
		}
	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

// App command to run the dialog
void CResourceEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorApp message handlers

