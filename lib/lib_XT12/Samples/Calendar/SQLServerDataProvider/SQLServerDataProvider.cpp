// SQLServerDataProvider.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SQLServerDataProvider.h"

#include "MainFrm.h"
#include "SQLServerDataProviderDoc.h"
#include "SQLServerDataProviderView.h"
#include "CalendarDataSourceDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderApp

BEGIN_MESSAGE_MAP(CSQLServerDataProviderApp, CWinApp)
	//{{AFX_MSG_MAP(CSQLServerDataProviderApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderApp construction

CSQLServerDataProviderApp::CSQLServerDataProviderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSQLServerDataProviderApp object

CSQLServerDataProviderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderApp initialization

BOOL CSQLServerDataProviderApp::InitInstance()
{
	VERIFY( AfxOleInit() );

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER <= 1200 //MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif


	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Codejock Software Sample Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSQLServerDataProviderDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSQLServerDataProviderView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// App command to run the dialog
void CSQLServerDataProviderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
 
/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderApp message handlers


void CSQLServerDataProviderApp::OnFileOpen() 
{
	CCalendarDataSourceDialog dlgDataSource;
	
	dlgDataSource.m_strConnectionString = AfxGetApp()->GetProfileString(csOptProfileSection, 
		csOptDataSourceSQLsrvProp, csOptDataSourceSQLsrvProp_default);
	//-----------------------------------------------------------------------

	if (dlgDataSource.DoModal() != IDOK) 
	{
		return;
	}
	//-----------------------------------------------------------------------
	AfxGetApp()->WriteProfileString(csOptProfileSection, csOptDataSourceSQLsrvProp, 
								    dlgDataSource.m_strConnectionString);

	OnFileNew();
}
