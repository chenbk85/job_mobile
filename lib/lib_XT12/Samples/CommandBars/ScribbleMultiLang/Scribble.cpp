// Scribble.cpp : Defines the class behaviors for the application.
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
#include <locale.h>
#include "winnls.h"
#include "Scribble.h"

#include "MainFrm.h"
#include "ChildFrm.h"
//#include "IpFrame.h"
#include "ScribDoc.h"
#include "ScribVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleApp

BEGIN_MESSAGE_MAP(CScribbleApp, CWinApp)
	//{{AFX_MSG_MAP(CScribbleApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_LANGUAGE_ENGLISH, OnLanguageEnglish)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_ENGLISH, OnUpdateLanguageEnglish)
	ON_COMMAND(ID_LANGUAGE_RUSSIAN, OnLanguageRussian)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_RUSSIAN, OnUpdateLanguageRussian)
	ON_COMMAND(ID_LANGUAGE_GERMAN, OnLanguageGerman)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_GERMAN, OnUpdateLanguageGerman)
	ON_COMMAND(ID_LANGUAGE_JAPANESE, OnLanguageJapanese)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_JAPANESE, OnUpdateLanguageJapanese)
	ON_COMMAND(ID_LANGUAGE_ARABIC, OnLanguageArabic)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_ARABIC, OnUpdateLanguageArabic)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribbleApp construction

CScribbleApp::CScribbleApp()
: m_curLanguage(0)
{
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	VERIFY(GetVersionEx(&osvi));

	m_bIsWinNT = (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT);
	m_bIsWin2000OrLater = (m_bIsWinNT && osvi.dwMajorVersion > 4);

	m_bIsRTL = FALSE;	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CScribbleApp object

CScribbleApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {7559FD90-9B93-11CE-B0F0-00AA006C28B3}
static const CLSID clsid =
{ 0x7559fd90, 0x9b93, 0x11ce, { 0xb0, 0xf0, 0x0, 0xaa, 0x0, 0x6c, 0x28, 0xb3 } };

/////////////////////////////////////////////////////////////////////////////
// CScribbleApp initialization

BOOL CScribbleApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}


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

	SetRegistryKey(_T("Codejock Software Sample Applications"));


	LoadStdProfileSettings();  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_SCRIBBTYPE,
		RUNTIME_CLASS(CScribbleDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CScribbleView));


	AddDocTemplate(pDocTemplate);
	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open.  We don't call this in Win32, since a
	//  document file extension wasn't chosen while running AppWizard.
	m_pMainWnd->DragAcceptFiles();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	UINT curLanguage = GetProfileInt(_T("Settings"), _T("Current Language"), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	switch (curLanguage & 0xFF)
	{
		case LANG_GERMAN:
			OnLanguageGerman();
			break;

		case LANG_JAPANESE:
			OnLanguageJapanese();
			break;

		case LANG_ARABIC:
			OnLanguageArabic();
			break;

		case LANG_RUSSIAN:
			OnLanguageRussian();
			break;

		default:
			OnLanguageEnglish();
			break;
	}

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CScribbleApp::ExitInstance()
{
	WriteProfileInt(_T("Settings"), _T("Current Language"), m_curLanguage);

	XTPResourceManager()->Close();

	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleApp commands

BOOL CScribbleApp::IsUnicodeAndLayoutSupport()
{
#ifdef _UNICODE
	return m_bIsWin2000OrLater;
#else
	return FALSE;
#endif
	
}

BOOL CScribbleApp::SetLocale(LCID Locale, LPCTSTR szLocale, LPCTSTR szFileName, BOOL bIsRTL)
{
	if (szFileName)
	{
		if (CXTPPropExchangeXMLNode::IsXMLSupported())  // Try to load from XML. Needs IE 4.0 installed
		{
			CString strPath;
			VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, strPath.GetBufferSetLength(_MAX_PATH), _MAX_PATH));
			strPath.ReleaseBuffer();
			
			int nIndex  = strPath.ReverseFind(_T('\\'));
			if (nIndex > 0) strPath = strPath.Left(nIndex + 1); else strPath.Empty();
			
			strPath = strPath + _T("Translations\\") + szFileName + _T(".xml");
			
			if (!XTPResourceManager()->SetResourceManager(new CXTPResourceManagerXML(strPath)))
				return FALSE;
		}
		else
		{
			CString strPath;
			VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, strPath.GetBufferSetLength(_MAX_PATH), _MAX_PATH));
			strPath.ReleaseBuffer();
			
			int nIndex  = strPath.ReverseFind(_T('\\'));
			if (nIndex > 0) strPath = strPath.Left(nIndex + 1); else strPath.Empty();
			
			strPath = strPath + _T("Translations\\") + szFileName + _T(".dll");
			
			XTPResourceManager()->SetResourceManager(new CXTPResourceManager());
			XTPResourceManager()->SetResourceFile(strPath);
			

		}
	}
	else
	{
		if (!XTPResourceManager()->SetResourceManager(new CXTPResourceManager()))
			return FALSE;
	}

	::SetThreadLocale(MAKELCID(Locale, SORT_DEFAULT)); 
	::_tsetlocale(LC_ALL, szLocale); 

	m_curLanguage = Locale;
	SetRTLLayout(bIsRTL);
	ReloadDefaultMenu();
	return TRUE;
}

void CScribbleApp::OnLanguageEnglish()
{
	SetLocale(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		_T("English.1252"), NULL, FALSE);
}

void CScribbleApp::OnUpdateLanguageEnglish(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_curLanguage == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
}

void CScribbleApp::OnLanguageGerman()
{
	SetLocale(MAKELANGID(LANG_GERMAN,SUBLANG_GERMAN),
		_T("German.1252"), _T("Scribble.ResourceDe"), FALSE);
}

void CScribbleApp::OnUpdateLanguageGerman(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_curLanguage == MAKELANGID(LANG_GERMAN,SUBLANG_GERMAN));
}

void CScribbleApp::OnLanguageJapanese()
{
	SetLocale(MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT),
		_T("Japanese.932"), _T("Scribble.ResourceJa"), FALSE);
}

void CScribbleApp::OnUpdateLanguageJapanese(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_curLanguage == MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT));
	pCmdUI->Enable((IsUnicodeAndLayoutSupport() && m_bIsWinNT) || (GetSystemDefaultLangID() == 0x411));
}

void CScribbleApp::OnLanguageArabic()
{
	SetLocale(MAKELANGID(LANG_ARABIC, SUBLANG_ARABIC_SAUDI_ARABIA),
		_T("Arabic.1256"), _T("Scribble.ResourceArSa"), TRUE);
}

void CScribbleApp::OnUpdateLanguageArabic(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_curLanguage == MAKELANGID(LANG_ARABIC, SUBLANG_ARABIC_SAUDI_ARABIA));
	pCmdUI->Enable((IsUnicodeAndLayoutSupport() && m_bIsWinNT) || (GetSystemDefaultLangID() == 0x401));
}

void CScribbleApp::OnLanguageRussian()
{
	SetLocale(MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT),
		_T("Russian"), _T("Scribble.ResourceRu"), FALSE);
}

void CScribbleApp::OnUpdateLanguageRussian(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_curLanguage == MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT));
	pCmdUI->Enable(IsUnicodeAndLayoutSupport() || (GetSystemDefaultLangID() == 0x419));
}

void CScribbleApp::ReloadDefaultMenu()
{
	CMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CMainFrame, m_pMainWnd);
	if (pMainFrame)
	{
		pMainFrame->ResetCommandBars();
	}
}

void SetRTLLayout(CWnd* pWnd, BOOL bRTLLayout)
{
	pWnd->ModifyStyleEx(bRTLLayout? 0: WS_EX_LAYOUTRTL, !bRTLLayout? 0: WS_EX_LAYOUTRTL, SWP_FRAMECHANGED);

	// walk through HWNDs to avoid creating temporary CWnd objects
	// unless we need to call this function recursively
	for (CWnd* pChild = pWnd->GetWindow(GW_CHILD); pChild != NULL;
		pChild = pChild->GetWindow(GW_HWNDNEXT))
	{

		// send to child windows after parent
		SetRTLLayout(pChild, bRTLLayout);
	}
}


void CScribbleApp::SetRTLLayout(BOOL bRTLLayout)
{
	if ((BYTE)::GetVersion() < 4)
		return;

	if (m_bIsRTL == bRTLLayout)
		return;

	m_bIsRTL = bRTLLayout;


	if (m_pMainWnd)
	{
		::SetRTLLayout(m_pMainWnd, bRTLLayout);

		// then update the state of all floating windows owned by the parent
		HWND hWnd = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
		while (hWnd != NULL)
		{
			if (m_pMainWnd->m_hWnd == ::GetParent(hWnd))
				::SetRTLLayout(CWnd::FromHandle(hWnd), bRTLLayout);

			hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
		}
	}

	XTPImageManager()->DrawReverted(bRTLLayout);
}


CDocument* CScribbleApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	CDocument* pDoc = CWinApp::OpenDocumentFile(lpszFileName);
	return pDoc;
}

void CScribbleApp::OnFileNew()
{
	CWinApp::OnFileNew();
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlgLoc dialog used for App About

class CAboutDlgLoc : public CDialog
{
public:
	CAboutDlgLoc();

// Dialog Data
	//{{AFX_DATA(CAboutDlgLoc)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlgLoc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlgLoc)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CFont m_DlgFont;
};

CAboutDlgLoc::CAboutDlgLoc()
{
	InitModalIndirect(XTPResourceManager()->LoadDialogTemplate(IDD_ABOUTBOX));

	//{{AFX_DATA_INIT(CAboutDlgLoc)
	//}}AFX_DATA_INIT
}

void CAboutDlgLoc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlgLoc)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlgLoc, CDialog)
	//{{AFX_MSG_MAP(CAboutDlgLoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CScribbleApp::OnAppAbout()
{
	CAboutDlgLoc aboutDlg;
	aboutDlg.DoModal();
}


BOOL CAboutDlgLoc::OnInitDialog()
{
	CDialog::OnInitDialog();

	LCID lcid = GetThreadLocale();

	if ( lcid == MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT))
	{ // set the characterset explicitly
		// -> to run the applicatin in Japanese on a non Japanges Windows
		CFont* pFont = GetFont();
		LOGFONT lf;
		if ( pFont != NULL  )
		{
			pFont->GetLogFont(&lf);
			lf.lfCharSet = SHIFTJIS_CHARSET;
			m_DlgFont.CreateFontIndirect(&lf);
			GetDlgItem(IDC_STATIC_LANGUAGE)->SetFont(&m_DlgFont);
			GetDlgItem(IDC_STATIC_MULLANG)->SetFont(&m_DlgFont);
			GetDlgItem(IDC_STATIC_SCRIBBLE)->SetFont(&m_DlgFont);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
