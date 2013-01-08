// MainFrm.cpp : implementation of the CMainFrame class
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
#include "ResourceExport.h"
#include "ResourceImport.h"
#include "ResourceEditorDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_FILE_CHANGELOCATION, OnFileChangelocation)
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)

	ON_XTP_CREATECONTROL()
	ON_XTP_EXECUTE(ID_FILE_OPEN, OnFileOpen)

	ON_COMMAND(ID_FILE_IMPORT_DLL, OnFileImportDll)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	ScanResources();

	// Create Status bar.
	// Important: All control bars including the Status Bar
	// must be created before CommandBars....
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	XTPImageManager()->SetMaskColor(XTPImageManager()->GetBitmapMaskColor(IDR_MAINFRAME));
	CXTPImageManager::m_bAutoResample = TRUE;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	// Add the menu bar
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(
		_T("Menu Bar"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}

	// Create ToolBar
	CXTPToolBar* pToolBar = (CXTPToolBar*)
		pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	m_MTIClientWnd.Attach(this, TRUE);

	// Set Office 2003 Theme
	CXTPPaintManager::SetTheme(xtpThemeWhidbey);

	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);


	m_wndPreview.Create(_T("STATIC"), 0, WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), this, 100);


	// Initialize the docking pane manager and set the
	// initial them for the docking panes.  Do this only after all
	// control bars objects have been created and docked.
	m_paneManager.InstallDockingPanes(this);
	// Set Office 2003 Theme
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);

	// Create docking panes.
	m_paneManager.CreatePane(
		IDR_PANE_PREVIEW, CRect(0, 0, 200, 150), xtpPaneDockBottom);

	return 0;
}

void CMainFrame::ScanResources()
{
	m_arrResources.RemoveAll();
	
	CFileFind finder;
	
	BOOL bWorking = finder.FindFile(theApp.m_strTranslatingPath + "*.xml");
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		
		CXTPPropExchangeXMLNode xmlNode(TRUE, 0, _T("resource"));
		
		if (xmlNode.LoadFromFile(finder.GetFilePath()))
		{
			CString strLanguage;
			PX_String(&xmlNode, _T("Language"), strLanguage);	

			if (!strLanguage.IsEmpty())
			{
				
				CResourceInfo resInfo;
				resInfo.strLanguage = strLanguage;
				resInfo.strPath = finder.GetFilePath();

				int nInsert = 0;
				for (; nInsert < (int)m_arrResources.GetSize(); nInsert++)
				{
					if (m_arrResources[nInsert].strLanguage > strLanguage)
						break;
				}
				m_arrResources.InsertAt(nInsert, resInfo);

			}			
		}
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			pPane->Attach(&m_wndPreview);
		}

		return TRUE; // handled
	}
	return FALSE;
}


void CMainFrame::ShowDialogPreview(CXTPPropExchangeXMLNode* pResource, DWORD dwId)
{
	pResource->InternalAddRef();
	XTPResourceManager()->SetResourceManager(new CXTPResourceManagerXML(pResource));
	
	LPCDLGTEMPLATE pTemplate = XTPResourceManager()->LoadDialogTemplate(dwId);
	
	if (pTemplate)
	{	 
		m_wndPreview.ShowDialog(pTemplate);
	}	

	XTPResourceManager()->SetResourceManager(new CXTPResourceManager());
}

void CMainFrame::ClearPreview()
{
	m_wndPreview.ClearPreview();

}

void CMainFrame::ShowMenuPreview(CXTPPropExchangeXMLNode* pResource, DWORD dwId, XTP_RESOURCEMANAGER_LANGINFO* pLangInfo)
{
	pResource->InternalAddRef();
	XTPResourceManager()->SetResourceManager(new CXTPResourceManagerXML(pResource));

	CMenu menu;
	if (XTPResourceManager()->LoadMenu(&menu, dwId))
	{
		m_wndPreview.ShowMenu(&menu, pLangInfo);
	}	



	XTPResourceManager()->SetResourceManager(new CXTPResourceManager());
}


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->bToolBar)
	{
		if (lpCreateControl->nID == ID_FILE_OPEN)
		{
			CXTPControlComboBox* pComboOpen = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();

			pComboOpen->SetWidth(150);
			pComboOpen->SetStyle(xtpComboLabel);

			lpCreateControl->pControl = pComboOpen;
			return TRUE;
		}

	}

	return FALSE;

}

void CMainFrame::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	CXTPControlComboBox* pControl = DYNAMIC_DOWNCAST(CXTPControlComboBox, CXTPControl::FromUI(pCmdUI));

	if (pControl && !pControl->HasFocus())
	{
		if (pControl->GetCount() != m_arrResources.GetSize())
		{
			pControl->ResetContent();

			for (int i = 0; i < m_arrResources.GetSize(); i++)
			{			
				pControl->AddString(m_arrResources[i].strLanguage);
			}
		}

		int nCurSel = -1;
		CDocument* pDocument = GetActiveFrame()->GetActiveDocument();
		
		if (pDocument)
		{
			CString strPath = pDocument->GetPathName();
			for (int i = 0; i < m_arrResources.GetSize(); i++)
			{
				if (m_arrResources[i].strPath == strPath)
				{
					nCurSel = i;
					break;
				}			
			}
		}
		pControl->SetCurSel(nCurSel);
	}	
}


void CMainFrame::OnFileOpen(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = DYNAMIC_DOWNCAST(CXTPControlComboBox, tagNMCONTROL->pControl);
	
	if (pControl)
	{
		int nCurSel = pControl->GetCurSel();

		if (nCurSel >= 0 && nCurSel < m_arrResources.GetSize())
		{
			theApp.OpenDocumentFile(m_arrResources[nCurSel].strPath);
		}

		*pResult = 1; // Handled;
	}
}

void CMainFrame::OnFileChangelocation() 
{
	// Get the current (if any) text that is displayed in
	// the edit control, this will be the initial path for the
	// browse dialog to start from.
	CString strPath = theApp.m_strTranslatingPath;
	

	// Instantiate a browse for folder dialog object
	CXTBrowseDialog browseDlg;
	browseDlg.SetOwner(m_hWnd);
	browseDlg.SetTitle(_T("Choose translation directory"));
	browseDlg.SetSelPath((TCHAR*)(LPCTSTR)strPath);

	if( browseDlg.DoModal() == IDOK ) 
	{
		theApp.m_strTranslatingPath = browseDlg.GetSelPath();
		theApp.m_strTranslatingPath += _T("\\");
		
		ScanResources();
	}

}

void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
	m_paneManager.OnSetPreviewMode(bPreview);
	CXTPMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}


void CMainFrame::OnFileExportAll() 
{
	for (int i = 0; i < m_arrResources.GetSize(); i++)
	{
		const CResourceInfo& ri = m_arrResources[i];
	
		CXTPPropExchangeXMLNode* pResources = new CXTPPropExchangeXMLNode(TRUE, 0, _T("resource"));
		pResources->LoadFromFile(ri.strPath);

		CString strOutput = ri.strPath;
		strOutput.Replace(_T(".xml"), _T(".rc"));

		CResourceExport re;
		re.ExportRc(pResources, strOutput);

		delete pResources;
	}
}

void CMainFrame::OnFileImportAll() 
{
	CFileFind finder;
	BOOL bWorking = finder.FindFile(theApp.m_strTranslatingPath + _T("*.dll"));
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		CString strPath = finder.GetFilePath();
			
		CResourceImport ri;
		if (ri.Import(strPath))
		{
			CString strOutput = strPath;
			strOutput.Replace(_T(".dll"), _T(".xml"));

			ri.m_pResources->SaveToFile(strOutput);
		}
	}
}

void CMainFrame::OnFileImportDll() 
{
	CString strFilter = _T("Executable Files (*.exe;*.dll;*.ocx)|*.dll;*.exe;*.ocx|All files (*.*)|*.*||");
	
	CFileDialog fd(TRUE, _T("dll"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, strFilter);
	if (fd.DoModal() != IDOK)
		return;

	CResourceImport ri;
	if (!ri.Import(fd.GetPathName()))
		return;

	
	POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
	CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate(pos);

	CResourceEditorDoc* pDocument = (CResourceEditorDoc*)pTemplate->CreateNewDocument();
	CFrameWnd* pFrame = pTemplate->CreateNewFrame(pDocument, NULL);

	pTemplate->SetDefaultTitle(pDocument);

	if (!pDocument->AssignResource(ri.m_pResources))
	{
		pFrame->DestroyWindow();
		return;
	}
	ri.m_bDelete = FALSE;
		
	pTemplate->InitialUpdateFrame(pFrame, pDocument, TRUE);

}
