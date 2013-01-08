// Styler.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Styler.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "StylerDoc.h"
#include "StylerView.h"
#include "FilterDialog.h"
#include "PopupFilter.h"
#include "CWebBrowser2.h"

#include "MouseManager.h"
#include "PageSearch.h"

//#include "CustSite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStylerApp

BEGIN_MESSAGE_MAP(CStylerApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CStylerApp construction

CStylerApp::CStylerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CStylerApp object

CStylerApp theApp;

// CStylerApp initialization

BOOL CStylerApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual xtps.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	CXTPWinDwmWrapper().SetProcessDPIAware();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Styler"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	
	
	CFilterDialog::LoadFilterList();
	CPopupFilter::LoadFilterList();

	CStylerView::Load();
	CMainFrame::Load();
	CPageSearch::Load();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CStylerDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CStylerView));
	AddDocTemplate(pDocTemplate);

	

	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!OneInstance(cmdInfo))
		return FALSE;

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;

	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	
	m_pMainWnd = pMainFrame;
	
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew &&
		(CMainFrame::m_nStartup == STARTUP_NOTHING || CMainFrame::m_nStartup == STARTUP_LASTVISITED))
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.	
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	
	if (!CMouseManager::Load())
	{
		ACCEL accel = {FCONTROL, 0, ID_FILE_CLOSE};
		CMouseManager::AddCommand(WM_LBUTTONDOWN, accel, MOUSE_AREA_TAB);
	}

	
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNothing && CMainFrame::m_nStartup == STARTUP_LASTVISITED)
		((CMainFrame*)pMainFrame)->OpenLastVisited();

	// The main window has been initialized, so show and update it
	//pMainFrame->ShowWindow(m_nCmdShow/*, CMainFrame::m_bRestoreWindowPos*/);
	CWindowPlacement(pMainFrame, _T("Main Frame")).ShowWindow(m_nCmdShow, CMainFrame::m_bRestoreWindowPos);
	
	pMainFrame->UpdateWindow();

	m_pMainWnd->DragAcceptFiles();


	
	


	return TRUE;
}


BOOL CStylerApp::ProcessShellCommand(CCommandLineInfo& cmdInfo)
{
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen)
	{
		CString strURL = cmdInfo.m_strFileName;
		if(strURL.Right(4).CompareNoCase(_T(".url")) == 0)
		{		
			TCHAR buf[2048];
			::GetPrivateProfileString(_T("InternetShortcut"), _T("URL"),
				_T(""), buf, 2048, strURL);

			OpenWindow(buf);
			return TRUE;
		}
		if (strURL.Find(_T("://")) != -1)
		{
			OpenWindow(strURL);
			return TRUE;
		}	
	} 

	return CWinApp::ProcessShellCommand(cmdInfo);	
}

BOOL CStylerApp::ExitInstance()
{
	CStylerView::Save();
	CMainFrame::Save();
	CMouseManager::Save();
	CPageSearch::Save();

	return CWinApp::ExitInstance();
}

BOOL CStylerApp::OneInstance(CCommandLineInfo& cmdInfo)
{
	HANDLE hSem = CreateSemaphore(NULL, 1, 1, m_pszAppName);

	if (GetLastError() == ERROR_ALREADY_EXISTS && CMainFrame::m_bOneInstance)
	{
		CloseHandle(hSem);

		HWND hWndPrevious = ::FindWindow(_T("StylerMainWindow"), NULL);
		if (hWndPrevious)
		{
			if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen )
			{
				//if (::GetLastActivePopup(hWndPrevious) == hWndPrevious)
				{
					LPTSTR lpData;
					
					//mutex
					HANDLE hMutex = CreateMutex(NULL, TRUE, _T("StylerMutex"));
					WaitForSingleObject(hMutex, INFINITE);
					
					HANDLE hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,
						PAGE_READWRITE, 0, 2560, _T("STYLERSHARE"));
					
					if (hMapping == NULL)
					{
						TRACE(_T("App:Fail to create share memory!"));
					}
					else
					{
						lpData = (LPTSTR) MapViewOfFile(hMapping,FILE_MAP_ALL_ACCESS,0,0,0);
						if (lpData == NULL)
						{
							TRACE(_T("App:MapViewOfFile Fail"));
						}
						else 
						{
							#if (_MSC_VER > 1310) // VS2005
							_stprintf_s(lpData, 2560, _T("%s"), cmdInfo.m_strFileName);
							#else
							_stprintf(lpData, _T("%s"), cmdInfo.m_strFileName);
							#endif
							::SendMessage(hWndPrevious,WM_USER_SHELL_OPEN,NULL,NULL);

							UnmapViewOfFile(lpData);
						}
						CloseHandle(hMapping);
					}
					ReleaseMutex(hMutex);
				}
			} 
			
			if (::IsIconic(hWndPrevious))
				::ShowWindow(hWndPrevious,SW_RESTORE);
			
			::SetForegroundWindow(::GetLastActivePopup(hWndPrevious));
			
			return FALSE;
		}	
	} 

	return TRUE;

}


// App command to run the dialog
void CStylerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CStylerApp message handlers




CString GetModuleDir()
{
	TCHAR lpszModule[MAX_PATH];
	if (!GetModuleFileName(AfxGetResourceHandle(), lpszModule, MAX_PATH))
		return _T("");
	
	CString strPath(lpszModule);

	int nIndex = strPath.ReverseFind('\\');
	
	if (nIndex != -1 && strPath.GetLength() != 3)
		return strPath.Left(nIndex + 1) + _T("Config\\");
	
	return _T("Config\\");

}

