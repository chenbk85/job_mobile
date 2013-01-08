// notepadre.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "notepadre.h"

#include "MainFrm.h"
#include "notepadreDoc.h"
#include "notepadreView.h"

#include "MyDocManager.h"

#include "WebClick.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct tagPRINTPAGERANGE {
   DWORD  nFromPage;
   DWORD  nToPage;
} PRINTPAGERANGE, *LPPRINTPAGERANGE;

typedef struct tagPDEXA {
   DWORD                 lStructSize;          // size of structure in bytes
   HWND                  hwndOwner;            // caller's window handle
   HGLOBAL               hDevMode;             // handle to DevMode
   HGLOBAL               hDevNames;            // handle to DevNames
   HDC                   hDC;                  // printer DC/IC or NULL
   DWORD                 Flags;                // PD_ flags
   DWORD                 Flags2;               // reserved
   DWORD                 ExclusionFlags;       // items to exclude from driver pages
   DWORD                 nPageRanges;          // number of page ranges
   DWORD                 nMaxPageRanges;       // max number of page ranges
   LPPRINTPAGERANGE      lpPageRanges;         // array of page ranges
   DWORD                 nMinPage;             // min page number
   DWORD                 nMaxPage;             // max page number
   DWORD                 nCopies;              // number of copies
   HINSTANCE             hInstance;            // instance handle
   LPCSTR                lpPrintTemplateName;  // template name for app specific area
   LPUNKNOWN             lpCallback;           // app callback interface
   DWORD                 nPropertyPages;       // number of app property pages in lphPropertyPages
   HPROPSHEETPAGE       *lphPropertyPages;     // array of app property page handles
   DWORD                 nStartPage;           // start page id
   DWORD                 dwResultAction;       // result action if S_OK is returned
} PRINTDLGEXA, *LPPRINTDLGEXA;
//
//  PrintDlgEx structure.
//
typedef struct tagPDEXW {
   DWORD                 lStructSize;          // size of structure in bytes
   HWND                  hwndOwner;            // caller's window handle
   HGLOBAL               hDevMode;             // handle to DevMode
   HGLOBAL               hDevNames;            // handle to DevNames
   HDC                   hDC;                  // printer DC/IC or NULL
   DWORD                 Flags;                // PD_ flags
   DWORD                 Flags2;               // reserved
   DWORD                 ExclusionFlags;       // items to exclude from driver pages
   DWORD                 nPageRanges;          // number of page ranges
   DWORD                 nMaxPageRanges;       // max number of page ranges
   LPPRINTPAGERANGE      lpPageRanges;         // array of page ranges
   DWORD                 nMinPage;             // min page number
   DWORD                 nMaxPage;             // max page number
   DWORD                 nCopies;              // number of copies
   HINSTANCE             hInstance;            // instance handle
   LPCWSTR               lpPrintTemplateName;  // template name for app specific area
   LPUNKNOWN             lpCallback;           // app callback interface
   DWORD                 nPropertyPages;       // number of app property pages in lphPropertyPages
   HPROPSHEETPAGE       *lphPropertyPages;     // array of app property page handles
   DWORD                 nStartPage;           // start page id
   DWORD                 dwResultAction;       // result action if S_OK is returned
} PRINTDLGEXW, *LPPRINTDLGEXW;

extern "C"
{
DECLSPEC_IMPORT HRESULT APIENTRY PrintDlgExA(LPPRINTDLGEXA);
DECLSPEC_IMPORT HRESULT APIENTRY PrintDlgExW(LPPRINTDLGEXW);
}
#ifdef UNICODE
#define PRINTDLGEX PRINTDLGEXW
#define PrintDlgEx  PrintDlgExW
#else
#define PRINTDLGEX PRINTDLGEXA
#define PrintDlgEx  PrintDlgExA
#endif // !UNICODE

#define PD_RESULT_CANCEL               0
#define PD_RESULT_PRINT                1
#define PD_RESULT_APPLY                2

#define PD_CURRENTPAGE                 0x00400000
#define PD_NOCURRENTPAGE               0x00800000
#define PD_EXCLUSIONFLAGS              0x01000000
#define PD_USELARGETEMPLATE            0x10000000

#define START_PAGE_GENERAL 0xffffffff

/////////////////////////////////////////////////////////////////////////////
// CNotepadreApp

BEGIN_MESSAGE_MAP(CNotepadreApp, CWinApp)
	//{{AFX_MSG_MAP(CNotepadreApp)
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
// CNotepadreApp construction

CNotepadreApp::CNotepadreApp()
{
}

void AFXAPI AfxGlobalFree(HGLOBAL hGlobal)
{
	if (hGlobal == NULL)
		return;

	// avoid bogus warning error messages from various debugging tools
	ASSERT(GlobalFlags(hGlobal) != GMEM_INVALID_HANDLE);
	UINT nCount = GlobalFlags(hGlobal) & GMEM_LOCKCOUNT;
	while (nCount--)
		GlobalUnlock(hGlobal);

	// finally, really free the handle
	GlobalFree(hGlobal);
}

int CNotepadreApp::DoPrintDialog (CPrintDialog *pPD)
{
	PRINTDLGEX pdex;
	PRINTPAGERANGE ppr;
	HRESULT hResult = S_OK;

	UpdatePrinterSelection(FALSE);
	::memset (&pdex, 0, sizeof (pdex));
	::memset (&ppr, 0, sizeof (ppr));
	pdex.lStructSize = sizeof (pdex);
	pdex.hwndOwner = ::GetFocus ();
	pdex.hDevMode = m_hDevMode;
	pdex.hDevNames = m_hDevNames;
	pdex.hDC = NULL;
	pdex.Flags = PD_RETURNDC | PD_NOCURRENTPAGE | PD_NOSELECTION;
	pdex.Flags2 = 0;
	pdex.ExclusionFlags = 0;
	pdex.nPageRanges = 1;
	pdex.nMaxPageRanges = 1;
	pdex.lpPageRanges = &ppr;
	pdex.nMinPage = pPD->m_pd.nMinPage;
	pdex.nMaxPage = pPD->m_pd.nMaxPage;
	pdex.nCopies = 1;
	pdex.hInstance = 0;
	pdex.lpPrintTemplateName = NULL;
	pdex.lpCallback = NULL;
	pdex.nPropertyPages = 0;
	pdex.lphPropertyPages = NULL;
	pdex.nStartPage = START_PAGE_GENERAL;
	pdex.dwResultAction = 0;

	ppr.nFromPage = pPD->m_pd.nFromPage;
	ppr.nToPage = pPD->m_pd.nToPage;
	hResult = ::PrintDlgEx (&pdex);

	while (hResult != S_OK)
	{
		if (pPD->m_pd.hDevNames != NULL)
		{
			ASSERT(m_hDevNames == pdex.hDevNames);
			AfxGlobalFree (pdex.hDevNames);
			pdex.hDevNames = NULL;
			m_hDevNames = NULL;
		}

		if (pPD->m_pd.hDevMode)
		{
			ASSERT(m_hDevMode == pdex.hDevMode);
			AfxGlobalFree(pdex.hDevMode);
			pdex.hDevMode = NULL;
			m_hDevMode = NULL;
		}

		hResult = ::PrintDlgEx (&pdex);
	}

	if (pdex.dwResultAction == PD_RESULT_PRINT)
	{
		pPD->m_pd.hDC = pdex.hDC;
		pPD->m_pd.Flags = pdex.Flags;
		pPD->m_pd.nCopies = pdex.nCopies;
		pPD->m_pd.nFromPage = pdex.lpPageRanges->nFromPage;
		pPD->m_pd.nToPage = pdex.lpPageRanges->nToPage;
		// refresh current CWinApp cache of printer device information
		m_hDevMode = pdex.hDevMode;
		m_hDevNames = pdex.hDevNames;
	}

	return pdex.dwResultAction == PD_RESULT_PRINT ? IDOK : IDCANCEL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNotepadreApp object

CNotepadreApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNotepadreApp initialization

BOOL CNotepadreApp::InitInstance ()
{
	CString strBenHanson;

	AfxOleInit (); // Needed for drag and drop support!

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	strBenHanson.LoadString (IDS_BEN_HANSON);
	SetRegistryKey (strBenHanson);
	LoadStdProfileSettings(); // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	CSingleDocTemplate *pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CNotepadreDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CNotepadreView));

	m_pDocManager = new CMyDocManager;// CDocManager
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	bool bReadOnly = false;

	ParseCommandLine(cmdInfo, bReadOnly);

	BOOL bFound = TRUE;
	BOOL bRet = TRUE;

	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen)
	{
		CFileFind finder;
		
		// Double-clicking a file causes it to be in double quotes...
		cmdInfo.m_strFileName.Replace (_T("\""), _T(""));
		// Check that the file we want to open exists...
		bFound = finder.FindFile (cmdInfo.m_strFileName);

		// If not then start Notepad RE with an empty document
		if (!bFound) cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;
	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles ();

	// If we were asked to open a non-existent file
	// then there is unfinished business.
	if (!bFound)
	{
		CString msg;

		msg.Format (_T("Cannot find the %s file.\r\n\r\nDo you want to")
			_T(" create a new file?"), cmdInfo.m_strFileName);

		// Prompt the user as to whether they really want to create a new file
		int iCreate = m_pMainWnd->MessageBox (msg, _T("Notepad RE"),
			MB_YESNOCANCEL | MB_ICONEXCLAMATION);

		if (iCreate == IDYES)
		{
			// The user really wants to create a new file
			TRY
			{
				CFile File (cmdInfo.m_strFileName, CFile::modeCreate |
					CFile::modeWrite);

				File.Close ();
				OpenDocumentFile (cmdInfo.m_strFileName);
			}
			CATCH_ALL(e)
			{
				// If we fail to create the file, just ignore the error
				bReadOnly = false;
			}
			END_CATCH_ALL
		}
		else if (iCreate == IDCANCEL)
		{
			// User chose to exit application
			bRet = FALSE;
		}
	}

	CNotepadreView *pView = static_cast<CNotepadreView *>
			(static_cast<CMainFrame *>(m_pMainWnd)->GetActiveView ());

	if (bReadOnly)
	{
		pView->ToggleReadOnly ();
	}

	// Explicitly set focus to the view, so that the dockable dialogs
	// don't accidently get it first (edge case).
	pView->SetFocus ();
	return bRet;
}

void CNotepadreApp::ParseCommandLine (CCommandLineInfo &rCmdInfo,
	bool &bReadOnly)
{
	LPTSTR lpCmdLine = m_lpCmdLine;

	while (*lpCmdLine)
	{
		CString strParam;
		BOOL bFlag = FALSE;
		BOOL bLast = FALSE;

		// Remove whitepace separating parameters
		while (*lpCmdLine && (*lpCmdLine == ' ' ||
			*lpCmdLine == '\t'))
		{
			lpCmdLine++;
		}

		if (*lpCmdLine == '-' || *lpCmdLine == '/')
		{
			// remove flag specifier
			bFlag = TRUE;
			lpCmdLine++;

			// if retrieving a flag, terminate on end of string or
			// whitespace
			while (*lpCmdLine && *lpCmdLine != ' ' &&
			*lpCmdLine != '\t')
			{
				strParam += *lpCmdLine++;
			}

			bReadOnly = !strParam.CompareNoCase (_T("r"));
		}
		else
		{
			// if parsing a filename, terminate on end of string
			while (*lpCmdLine)
			{
				strParam += *lpCmdLine++;
			}
		}

		bLast = !*lpCmdLine;
		rCmdInfo.ParseParam (strParam, bFlag, bLast);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CWebClick m_ButtonWebLink;
};

CAboutDlg::CAboutDlg () : CDialog(CAboutDlg::IDD),
	m_ButtonWebLink (_T("http://www.codeproject.com/cpp/notepadre.asp"),
	_T("http://www.codeproject.com/cpp/notepadre.asp"))
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange (CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CNotepadreApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CAboutDlg::OnInitDialog ()
{
	CDialog::OnInitDialog();
	m_ButtonWebLink.SubclassDlgItem (IDC_BUTTON_URL, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadreApp message handlers


BOOL CNotepadreApp::OnIdle(LONG lCount)
{
	if (m_pMainWnd)
	{
		static_cast<CMainFrame *>(m_pMainWnd)->DisplayLineAndColumn ();
	}

	return CWinApp::OnIdle(lCount);
}

CDocument *CNotepadreApp::OpenDocumentFile (LPCTSTR lpszFileName)
{
	// Over-ride default behaviour
	// by allowing the user to re-open an already open document...
	if (m_pMainWnd)
	{
		CNotepadreDoc *pDoc = static_cast<CNotepadreDoc *>
			(static_cast<CMainFrame *>(m_pMainWnd)->GetActiveDocument ());
		CString strPathName;

		strPathName = pDoc->GetPathName ();

		if (strPathName == lpszFileName)
		{
			BOOL bContinue = TRUE;

			if (pDoc->IsModified ())
			{
				CString prompt;
				CString name = pDoc->GetTitle ();
				int ret;

				AfxFormatString1(prompt, AFX_IDP_ASK_TO_SAVE, name);
				ret = AfxMessageBox(prompt, MB_YESNOCANCEL,
					AFX_IDP_ASK_TO_SAVE);
				bContinue = ret == IDYES || ret == IDNO;

				if (ret == IDYES)
				{
					bContinue = pDoc->DoSave (0);
				}
			}

			// Close the current document (if bContinue is true)
			// before re-opening.  Otherwise the document is not closed
			// and CWinApp::OpenDocumentFile will ignore the
			// request to re-load.
			if (bContinue)
			{
				pDoc->OnNewDocument ();
			}
		}
	}

	return CWinApp::OpenDocumentFile (lpszFileName);
}
