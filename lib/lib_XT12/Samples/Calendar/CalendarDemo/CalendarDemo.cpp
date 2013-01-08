// CalendarDemo.cpp : Defines the class behaviors for the application.
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
#include "CalendarDemo.h"

#include "MainFrm.h"
#include "CalendarDemoDoc.h"
#include "CalendarDemoView.h"
#include "DataProvidersOptions.h"
#include "CalendarResourcesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL IsFileExist(LPCTSTR pcszFile)
{
	return FILEEXISTS_S(pcszFile);
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoApp

BEGIN_MESSAGE_MAP(CCalendarDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CCalendarDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)

	// Multiple schedules menu items
	ON_COMMAND(ID_FILE_MULTISCHEDULES_CFG, OnMultiSchedulesCfg)
	ON_COMMAND(ID_FILE_LOAD_SAMPLE_MULTISCHEDULES_SIMPLE, OnMultiSchedulesSample)
	ON_COMMAND(ID_FILE_LOAD_SAMPLE_MULTISCHEDULES_EXTENDED, OnMultiSchedulesSampleExt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoApp construction

CCalendarDemoApp::CCalendarDemoApp()
{
	m_bOnOpenFile_AppStarting = TRUE;

	m_bOnOpenFile_CreateNewIfNotExist = FALSE;
	
	m_pCalRCman = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CCalendarDemoApp object

CCalendarDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoApp initialization

BOOL CCalendarDemoApp::InitInstance()
{
	VERIFY( AfxOleInit() );

	AfxEnableControlContainer();
	CXTPWinDwmWrapper().SetProcessDPIAware();

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
		RUNTIME_CLASS(CCalendarDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CCalendarDemoView));
	AddDocTemplate(pDocTemplate);
    

/*	BOOL bIsShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
	CString strUseDP = GetProfileString(cstrDP_Opt_section, cstrUseDP_opt);	
	
	BOOL bPostShowOpenNewDialog = strUseDP.IsEmpty() || bIsShift;
	BOOL nNoFile = FALSE;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	if(strUseDP.CompareNoCase(cstrUseDP_Mem_optval) == 0) {
		cmdInfo.m_strFileName = GetProfileString(cstrDP_Opt_section, cstrUseDP_Mem_File_opt);
	} 
	else if(strUseDP.CompareNoCase(cstrUseDP_DB_optval) == 0) {		
		cmdInfo.m_strFileName = GetProfileString(cstrDP_Opt_section, cstrUseDP_DB_File_opt);
	} 
	else if(strUseDP.CompareNoCase(cstrUseDP_MAPI_optval) == 0) {		
		cmdInfo.m_strFileName = _T("mapi:");
		nNoFile = TRUE;
	} 
	else {
		ASSERT(strUseDP.IsEmpty());		
	}

	BOOL bFileExist = !cmdInfo.m_strFileName.IsEmpty() && 
						IsFileExist(cmdInfo.m_strFileName);
	

	if(!bPostShowOpenNewDialog && bFileExist) 
	{
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileOpen;
	}
	else {
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;
		cmdInfo.m_strFileName = _T("");

		m_bOnOpenFile_CreateNewIfNotExist = TRUE;
		bPostShowOpenNewDialog = TRUE;
		CCalendarDemoDoc::ms_bFileNew_CreateEmptyDocument = TRUE;
	}
	*/

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;
	cmdInfo.m_strFileName = _T("");

	m_bOnOpenFile_AppStarting = TRUE;
	BOOL bPostShowOpenNewDialog = TRUE;
	CCalendarDemoDoc::ms_bFileNew_CreateEmptyDocument = TRUE;
	
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	if(m_pMainWnd) 
	{
		m_pMainWnd->SetForegroundWindow();

		if(bPostShowOpenNewDialog) 
		{
			m_pMainWnd->PostMessage(WM_COMMAND, ID_FILE_OPEN);
		}

		m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
		m_pMainWnd->UpdateWindow();				
	}

	return TRUE;
}

int CCalendarDemoApp::ExitInstance()
{
	CMDTARGET_RELEASE(m_pCalRCman);

	return CWinApp::ExitInstance();
}

// Choose a new Calendar Data Provider and set its options.
void CCalendarDemoApp::OnFileOpen()
{
	BOOL bAppStarting = m_bOnOpenFile_AppStarting;

	if (m_bOnOpenFile_AppStarting)
	{
		m_bOnOpenFile_AppStarting = FALSE;
		
		int nDlgRes = AfxMessageBox(_T("Would you like to populate the calendar with sample data? \nSelect No to open an existing data provider."), MB_YESNOCANCEL);
		if (nDlgRes == IDYES)
		{
			CCalendarDemoDoc::ms_bFileNew_CreateEmptyDocument = TRUE;
			CCalendarDemoDoc::ms_bEmptyDocument_AddSampleData = TRUE;
			OnFileNew();			
			return;
		}
		else if (nDlgRes == IDCANCEL)
		{
			CCalendarDemoDoc::ms_bFileNew_CreateEmptyDocument = TRUE;
			OnFileNew();
			return;
		}
		else 
		{
			CCalendarDemoDoc::ms_bFileNew_CreateEmptyDocument = FALSE;
		}
	}
	else 
	{
		// Open Data Providers choice dialog
		CDataProvidersOptions optDlg;
		optDlg.m_strTitle = _T("Open file");
		optDlg.m_bOpenMode = TRUE;

		int nDlgRes = (int)optDlg.DoModal();

		if(nDlgRes != IDOK) {
			return;
		}
	}

	CString strUseDP = GetProfileString(cstrDP_Opt_section, cstrUseDP_opt);

	CString strFileName;

	if(strUseDP.CompareNoCase(cstrUseDP_Mem_optval) == 0) {
		strFileName = GetProfileString(cstrDP_Opt_section, cstrUseDP_Mem_File_opt);
	} 
	else if(strUseDP.CompareNoCase(cstrUseDP_DB_optval) == 0) {		
		strFileName = GetProfileString(cstrDP_Opt_section, cstrUseDP_DB_File_opt);
	} 
	else if(strUseDP.CompareNoCase(cstrUseDP_MAPI_optval) == 0) 
	{
		CCalendarDemoDoc::ms_bFileNew_ShowDialog = bAppStarting;
		OnFileNew();
		return;
	}
	else if (strUseDP.IsEmpty())
	{
		CCalendarDemoDoc::ms_bFileNew_ShowDialog = TRUE;
		OnFileNew();
		return;
	}
	else
	{
		ASSERT(FALSE);
		return;
	}

	// If you're trying to open an existing file into data provider
	if(IsFileExist(strFileName)) 
	{
		OpenDocumentFile(strFileName);
	}
	else 
	{
		// Otherwise, you're creating a new data file
		int nRes = AfxMessageBox(_T("The events data file is not exist.\nWould You like to create it?"), MB_YESNO);
		if(nRes == IDYES) {			
			CCalendarDemoDoc::ms_bFileNew_ShowDialog = FALSE;
			OnFileNew();
		} 
		else {
			OnFileOpen();
		}
	}	
}

CCalendarDemoView* CCalendarDemoApp::GetCalendarDemoView()
{
	// for single doc template only
	POSITION posDOCTempl = GetFirstDocTemplatePosition();
	CDocTemplate* pDocTemplate = GetNextDocTemplate(posDOCTempl);
			
	POSITION posDOC = pDocTemplate ? pDocTemplate->GetFirstDocPosition() : NULL;
	CDocument* pDocument = pDocTemplate ? pDocTemplate->GetNextDoc(posDOC) : NULL;
			
	POSITION posView = pDocument ? pDocument->GetFirstViewPosition() : NULL;
	CView* pView = pDocument ? pDocument->GetNextView(posView) : NULL;
		    
	CCalendarDemoView* pDemoView = pView ? DYNAMIC_DOWNCAST(CCalendarDemoView, pView) : NULL;

	return pDemoView;
}

// App command to run the dialog
void CCalendarDemoApp::OnAppAbout()
{
	if((GetKeyState(VK_SHIFT)&0x8000) && (GetKeyState(VK_CONTROL)&0x8000)) 
	{
		CCalendarDemoView* pDemoView = GetCalendarDemoView();		
		ASSERT(pDemoView);

		if(pDemoView) 
		{
			CXTPCalendarData* pCData = pDemoView->GetCalendarCtrl().GetDataProvider();		
			CCalendarInternalOptions optInternal(pCData);
			optInternal.DoModal();
			return;
		}
	}	

	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CCalendarDemoApp::OnMultiSchedulesCfg()
{	
	// Get Calendar pointer
	CCalendarDemoView* pDemoView = GetCalendarDemoView();		
	ASSERT(pDemoView);
	if(!pDemoView)
		return;
	CXTPCalendarControl* pCalendar = &pDemoView->GetCalendarCtrl();
	
	// Prepare Resource Manager
	CString strCfgFile = GetModulePath() +_T("CalendarMultiResourcesConfigCustom.xml");

	if (!m_pCalRCman)
	{
		m_pCalRCman = new CXTPCalendarResourcesManager();
		if (!m_pCalRCman) {
			return;
		}
		m_pCalRCman->LoadCfg(strCfgFile);
	}

	// Show Resource Manager dialog
	CCalendarResourcesDlg dlgCalRC(m_pCalRCman);

	int nDlgRes = (int)dlgCalRC.DoModal();

	if (nDlgRes != IDOK)
		return;

	// Save and apply changed resources configuration
	m_pCalRCman->SaveCfg(strCfgFile);
	m_pCalRCman->ApplyToCalendar(pCalendar);
	pCalendar->Populate();
	pCalendar->RedrawControl();

	// Update Sample caption
	CString strTitle = _T("Multiple Schedules configuration: ") + strCfgFile;
	pDemoView->GetDocument()->CDocument::SetTitle(strTitle);
}

CString CCalendarDemoApp::GetModulePath()
{
	TCHAR szCurPath[_MAX_PATH + 2];
	::GetModuleFileName(AfxGetInstanceHandle(), szCurPath, _MAX_PATH);

	CString strCurPath(szCurPath);
	strCurPath = strCurPath.Left(strCurPath.ReverseFind('\\')+1);

	return strCurPath;
}

// Create Multiple Schedules sample configuration without 
// using Calendar Resources Manager.
void CCalendarDemoApp::OnMultiSchedulesSample()
{
	
	// Get Calendar pointer
	CCalendarDemoView* pDemoView = GetCalendarDemoView();		
	if(!pDemoView)
		return;
	CXTPCalendarControl* pCalendar = &pDemoView->GetCalendarCtrl();

	// Setup sample configuration
	// ** data provider
	CString strConnectionString = _T("Provider=XML;Data Source=") + 
		GetModulePath() + _T("CalendarMultipleSchedulesSample.xtp_cal");
	CXTPCalendarData* pData = CXTPCalendarControl::CreateDataProvider(strConnectionString);
	if (!pData)
		return;
	if (!pData->Open()) 
	{
		VERIFY( pData->Create() );
	}
	// ** schedules
	CXTPCalendarSchedules* pSchedules = pData->GetSchedules();
	if (!pSchedules)
		return;
	if (pSchedules->GetCount() < 1)
	{
		pSchedules->AddNewSchedule(_T("John"));
		pSchedules->AddNewSchedule(_T("Jane"));
	}
	// ** resources
	CXTPCalendarResources arResources;
	CXTPCalendarResource* pRes0 = new CXTPCalendarResource(pCalendar);
	if (pRes0)
	{
		pRes0->SetName(_T("John"));
		pRes0->SetDataProvider(pData, TRUE);
		pRes0->GetSchedules()->Add(pSchedules->GetAt(0)->GetID());
		arResources.Add(pRes0);
	}
	CXTPCalendarResource* pRes1 = new CXTPCalendarResource(pCalendar);
	if (pRes1)
	{
		pRes1->SetName(_T("Jane (TimeZone: +8)"));
		pRes1->SetDataProvider(pData);
		pRes1->GetSchedules()->Add(pSchedules->GetAt(1)->GetID());
		arResources.Add(pRes1);
	}
	pCalendar->SetResources(&arResources);
	// Add sample events
	int nRes = AfxMessageBox(_T("Would You like to add default test events set?"), MB_YESNO);
	if (nRes == IDYES) 
	{
		pData->RemoveAllEvents();
		CCalendarDemoDoc::AddTestEvents(pData, COleDateTimeSpan(0), pSchedules->GetAt(0)->GetID());
		CCalendarDemoDoc::AddTestEvents(pData, COleDateTimeSpan(0, 8, 0, 0), pSchedules->GetAt(1)->GetID());
		
		if (!pData->Save()) 
			AfxMessageBox(_T("Memory data provider cannot save document"));
	}
	// Save and apply changed resources configuration
	pCalendar->Populate();
	pCalendar->RedrawControl();
	
	// Update Sample caption
	pDemoView->GetDocument()->CDocument::SetTitle(_T("Multiple Schedules sample N1"));
	
	// Cleanup
	CMDTARGET_RELEASE(pData);
	
}


// Create an extended Multiple Schedules sample configuration using 
// a sample CXTPCalendarResourcesManager class.
void CCalendarDemoApp::OnMultiSchedulesSampleExt()
{	
	
	// Get Calendar pointer
	CCalendarDemoView* pDemoView = GetCalendarDemoView();		
	if(!pDemoView)
		return;
	
	CXTPCalendarControl* pCalendar = &pDemoView->GetCalendarCtrl();
	// Prepare resource manager
	CString strCfgFile = GetModulePath() +_T("CalendarMultipleSchedulesSample.xml");
	if (!m_pCalRCman)
	{
		m_pCalRCman = new CXTPCalendarResourcesManager();
		if (!m_pCalRCman)
			return;
		//m_pCalRCman->LoadCfg(strCfgFile);
	}
	
	// Setup sample configuration
	// ** data provider
	CString strConnectionString = _T("Provider=XML;Data Source=") + 
		GetModulePath() + _T("CalendarMultipleSchedulesExt.xtp_cal");
	m_pCalRCman->AddDataProvider(strConnectionString, 
		CXTPCalendarResourcesManager::xtpCalendarDPF_CreateIfNotExists |
		CXTPCalendarResourcesManager::xtpCalendarDPF_SaveOnDestroy |
		CXTPCalendarResourcesManager::xtpCalendarDPF_CloseOnDestroy);

	if (m_pCalRCman->GetDataProvidersCount() < 1)
		return;
	CXTPCalendarData* pData = m_pCalRCman->GetDataProvider(0);
	if (!pData)
		return;
	// ** schedules
	CXTPCalendarSchedules* pSchedules = pData->GetSchedules();
	if (!pSchedules)
		return;
	if (pSchedules->GetCount() == 0)
	{
		pSchedules->AddNewSchedule(_T("John"));
		pSchedules->AddNewSchedule(_T("Peter"));
		pSchedules->AddNewSchedule(_T("Conference Room N1"));
		pSchedules->AddNewSchedule(_T("Conference Room N2"));
	}
	
	// ** resources
	m_pCalRCman->AddResource(_T("John"), TRUE);
	m_pCalRCman->AddResource(_T("Peter"), TRUE);
	m_pCalRCman->AddResource(_T("Rooms"), TRUE);
	CXTPCalendarResourceDescription* pRCDesc = m_pCalRCman->GetResource(0);
	if (pRCDesc && pRCDesc->m_ptrResource)
	{
		pRCDesc->m_ptrResource->SetDataProvider(pData);
		pRCDesc->m_ptrResource->GetSchedules()->Add(pSchedules->GetAt(0)->GetID());
		pRCDesc->m_bGenerateName = TRUE;
	}
	pRCDesc = m_pCalRCman->GetResource(1);
	if (pRCDesc && pRCDesc->m_ptrResource)
	{
		pRCDesc->m_ptrResource->SetDataProvider(pData);
		pRCDesc->m_ptrResource->GetSchedules()->Add(pSchedules->GetAt(1)->GetID());
		pRCDesc->m_bGenerateName = TRUE;
	}
	pRCDesc = m_pCalRCman->GetResource(2);
	if (pRCDesc && pRCDesc->m_ptrResource)
	{
		pRCDesc->m_ptrResource->SetDataProvider(pData);
		pRCDesc->m_ptrResource->GetSchedules()->Add(pSchedules->GetAt(2)->GetID());
		pRCDesc->m_ptrResource->GetSchedules()->Add(pSchedules->GetAt(3)->GetID());
		pRCDesc->m_bGenerateName = FALSE;
	}
	// Save and apply changed resources configuration
	m_pCalRCman->SaveCfg(strCfgFile);
	m_pCalRCman->ApplyToCalendar(pCalendar);
	pCalendar->Populate();
	pCalendar->RedrawControl();
	
	// Update Sample caption
	pDemoView->GetDocument()->CDocument::SetTitle(_T("Multiple Schedules sample N2"));

	// Cleanup
	
}

////////////////////////////////////////////////////////////////////////////
// CCalendarInternalOptions dialog
//

IMPLEMENT_DYNAMIC(CCalendarInternalOptions, CDialog)
CCalendarInternalOptions::CCalendarInternalOptions(CXTPCalendarData* pCData, CWnd* pParent /*=NULL*/)
: CDialog(CCalendarInternalOptions::IDD, pParent)
{
	ASSERT(pCData);
	m_ptrCData = pCData;
}

CCalendarInternalOptions::~CCalendarInternalOptions()
{
}

void CCalendarInternalOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DBDP_CACHE_MODE_CB, m_ctrlDBDPCacheModeCb);
	DDX_Control(pDX, IDC_DBDP_CACHE_MODE_COMMENT, m_ctrlDBDPCacheModeComment);
}


BEGIN_MESSAGE_MAP(CCalendarInternalOptions, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CCalendarInternalOptions::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_ptrCData) 
	{
		ASSERT(FALSE);
		return FALSE;
	}

	//===========================================================================
	BOOL bSupported_DBDPCacheMode = m_ptrCData->GetType() != xtpCalendarDataProviderMemory;
	int eDBDPCacheMode = m_ptrCData->GetCacheMode();

	int nIdx = m_ctrlDBDPCacheModeCb.AddString(_T("OFF"));
	m_ctrlDBDPCacheModeCb.SetItemData(nIdx, xtpCalendarDPCacheModeOff);
	
	nIdx = m_ctrlDBDPCacheModeCb.AddString(_T("ON, Repeat manipulations (Default)"));
	m_ctrlDBDPCacheModeCb.SetItemData(nIdx, xtpCalendarDPCacheModeOnRepeat);

	nIdx = m_ctrlDBDPCacheModeCb.AddString(_T("ON, Clear after manipulations"));
	m_ctrlDBDPCacheModeCb.SetItemData(nIdx, xtpCalendarDPCacheModeOnClear);

	for(int i = 0; i < m_ctrlDBDPCacheModeCb.GetCount(); i++) 
	{
		if((int)m_ctrlDBDPCacheModeCb.GetItemData(i) == eDBDPCacheMode) 
		{
			m_ctrlDBDPCacheModeCb.SetCurSel(i);
			break;
		}
	}
    	
	m_ctrlDBDPCacheModeCb.EnableWindow(bSupported_DBDPCacheMode);
	//if(GetDlgItem(IDC_DBDP_CACHE_MODE_FRAME)) {
	//	GetDlgItem(IDC_DBDP_CACHE_MODE_FRAME)->EnableWindow(bSupported_DBDPCacheMode);
	//}
	if(GetDlgItem(IDC_DBDP_CACHE_MODE_LABEL)) {
		GetDlgItem(IDC_DBDP_CACHE_MODE_LABEL)->EnableWindow(bSupported_DBDPCacheMode);
	}
	if(GetDlgItem(IDOK)) {
		GetDlgItem(IDOK)->EnableWindow(bSupported_DBDPCacheMode);
	}
	if(!bSupported_DBDPCacheMode) {
		m_ctrlDBDPCacheModeComment.SetWindowText(_T("Is not supported. Switch to DB Data provider"));
	}	
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoApp message handlers



void CCalendarInternalOptions::OnBnClickedOk()
{
	ASSERT(m_ptrCData);
	if(m_ptrCData) 
	{
		int nSel = m_ctrlDBDPCacheModeCb.GetCurSel();
		if(nSel != CB_ERR) 
		{
			int eCMode = (int)m_ctrlDBDPCacheModeCb.GetItemData(nSel);
			
			ASSERT(	eCMode == xtpCalendarDPCacheModeOff ||
					eCMode == xtpCalendarDPCacheModeOnRepeat ||
					eCMode == xtpCalendarDPCacheModeOnClear );

			m_ptrCData->SetCacheMode(eCMode);
		}		
	}

	OnOK();
}

