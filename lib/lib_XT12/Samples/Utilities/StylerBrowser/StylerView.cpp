// StylerView.cpp : implementation of the CStylerView class
//

#include "stdafx.h"
#include "Styler.h"

#include "StylerDoc.h"
#include "StylerView.h"

#include "MainFrm.h"
#include "PopupFilter.h"
#include "ComboBoxSearch.h"

#include "MouseManager.h"

#include "FilterDialog.h"
#include "ChildFrm.h"
#include <Mshtml.h>

#include "LinkProperties.h"
#include <intshcut.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BOOL CStylerView::m_bShowImages = TRUE;
long CStylerView::m_nFontSize = 2;

BOOL CStylerView::m_bFilterAll = FALSE;
BOOL CStylerView::m_bFilterList = TRUE;

//CImageList CStylerView::m_lstTabImages;
HICON CStylerView::m_arrIcons[5];

IMPLEMENT_DYNCREATE(CStylerView, CHtmlView)

BEGIN_MESSAGE_MAP(CStylerView, CHtmlView)
//{{AFX_MSG_MAP(CChildFrame)	
	ON_WM_SIZE()
	ON_WM_PARENTNOTIFY()
	

	ON_COMMAND(ID_ADD_TO_FAV, OnAddToFavorites)

	ON_COMMAND(ID_FILE_PROPERTIES, OnFileProperties)
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)

	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)


	ON_COMMAND(ID_GOTO_BACK, CHtmlView::GoBack)
	ON_COMMAND(ID_GOTO_FORWARD, CHtmlView::GoForward)
	ON_COMMAND(ID_GOTO_HOME, CHtmlView::GoHome)
	ON_COMMAND(ID_VIEW_REFRESH, CHtmlView::Refresh)
	ON_COMMAND(ID_VIEW_STOP, CHtmlView::Stop)


	ON_COMMAND(ID_VIEW_SOURCE, OnViewSource)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)

	ON_COMMAND(ID_SHOWIMAGES, OnShowImages)
	ON_UPDATE_COMMAND_UI(ID_SHOWIMAGES, OnUpdateShowImages)


	ON_UPDATE_COMMAND_UI(ID_GOTO_BACK, OnUpdateGotoBack)
	ON_UPDATE_COMMAND_UI(ID_GOTO_FORWARD, OnUpdateGotoForward)

	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	

	ON_COMMAND(ID_TEXTSIZE, OnTextSize)
	ON_COMMAND_RANGE(ID_TEXTSIZE_LARGEST, ID_TEXTSIZE_SMALLEST, OnTextSizeRange)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TEXTSIZE_LARGEST, ID_TEXTSIZE_SMALLEST, OnUpdateTextSizeRange)

	ON_COMMAND_RANGE(ID_VIEW_ENCODING_FIRST, ID_VIEW_ENCODING_LAST, OnViewEncodingRange)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_ENCODING_FIRST, ID_VIEW_ENCODING_LAST, OnUpdateViewEncodingRange)

	ON_MESSAGE(WM_XTP_GETTABICON, OnGetTabIcon)


	ON_COMMAND(ID_VIEW_LOCK, OnViewLock)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LOCK, OnUpdateViewLock)
	
	ON_UPDATE_COMMAND_UI(ID_INDICATOR, OnUpdateIndicator)

	ON_NOTIFY(ID_LINK_STARTDRAG, ID_GOTO_URL, OnLinkStartDrag)



//}}AFX_MSG_MAP
	ON_XTP_EXECUTE(ID_ADDPAGEHERE, OnAddPageHere)

	ON_UPDATE_COMMAND_UI(ID_ADDPAGEHERE, OnUpdateAddPageHere)

END_MESSAGE_MAP()



CStylerView::CStylerView()
{
	EnableAutomation();

	
	/*if (!m_lstTabImages.GetSafeHandle())
	{
		m_lstTabImages.Create(16, 16, ILC_COLORDDB | ILC_MASK, 5, 1);
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITMAP_TABS);
		m_lstTabImages.Add(&bmp, RGB(255,0,255));
	}*/
	if (m_arrIcons[0] == 0)
	{
		CImageList il;
		il.Create(16, 16, ILC_COLORDDB | ILC_MASK, 5, 1);
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITMAP_TABS);
		il.Add(&bmp, RGB(255,0,255));
		for (int i = 0; i < 5; i++)
			m_arrIcons[i] = il.ExtractIcon(i);


	}

	m_nLoadingState = -1;
	m_nProgress = 0;
	m_bPopup = FALSE;
	m_bLock = FALSE;

	m_lpDisp = NULL;
	m_bActive = FALSE;
	
	m_infMouse.Clear();
}

CStylerView::~CStylerView()
{
}


// CStylerView diagnostics

#ifdef _DEBUG
void CStylerView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CStylerView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CStylerDoc* CStylerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStylerDoc)));
	return (CStylerDoc*)m_pDocument;
}
#endif //_DEBUG


// CStylerView Commons

void CStylerView::Load()
{
	m_nFontSize = AfxGetApp()->GetProfileInt(_T("StylerView"), _T("FontSize"), 2);
	m_bShowImages = AfxGetApp()->GetProfileInt(_T("StylerView"), _T("ShowImages"), 1);
	
	m_bFilterAll = AfxGetApp()->GetProfileInt(_T("StylerView"), _T("FilterAll"), 0);
	m_bFilterList = AfxGetApp()->GetProfileInt(_T("StylerView"), _T("FilterList"), 1);


}
void CStylerView::Save()
{
	AfxGetApp()->WriteProfileInt(_T("StylerView"), _T("FontSize"), m_nFontSize);
	AfxGetApp()->WriteProfileInt(_T("StylerView"), _T("ShowImages"), m_bShowImages);
	
	AfxGetApp()->WriteProfileInt(_T("StylerView"), _T("FilterAll"), m_bFilterAll);
	AfxGetApp()->WriteProfileInt(_T("StylerView"), _T("FilterList"), m_bFilterList);

}

CComPtr<IHTMLDocument2> CStylerView::GetHtmlDocument2()
{
	LPDISPATCH lpDisp = GetHtmlDocument();
	CComQIPtr<IHTMLDocument2> spDoc = lpDisp;
	if (lpDisp)	lpDisp->Release();
	
	return spDoc;
}

void CStylerView::SetAddress()
{
	if (m_nLoadingState == -1)
		return;

	try
	{
		CString strUrl = GetLocationURL();
		if (GetDocument() &&  !strUrl.IsEmpty() && strUrl != GetDocument()->GetCurrentUrl())
		{
			GetDocument()->SetUrl(strUrl);	
			if (m_bActive)		
			{
				GetMainFrame()->SetAddress(strUrl);
			}
		}
	}
	catch (...)
	{
	}
}

void CStylerView::RefreshExplorer()
{
	CSourceCtrl* pBar = GetMainFrame()->GetSourceCtrl();
	if (pBar && pBar->m_hWnd && pBar->IsWindowVisible())
	{
		pBar->Refresh(this, FALSE);		
	}
}

EXTERN_C const GUID CGID_MSHTML;
#define CMDSETID_Forms3 CGID_MSHTML

void CStylerView::ExecFormsCommand(DWORD dwCommandID)
{
	CComQIPtr<IOleCommandTarget> spCmdTarget(m_pBrowserApp);
	if (spCmdTarget)
	{
		spCmdTarget->Exec(&CMDSETID_Forms3, dwCommandID, OLECMDEXECOPT_DONTPROMPTUSER, 0, 0);
	}
}

BOOL CStylerView::QueryFormsCommand(DWORD dwCommandID)
{
	try
	{
		CComQIPtr<IOleCommandTarget> spCmdTarget(m_pBrowserApp);
		
		if (spCmdTarget)
		{
			OLECMD cmdInfo = {dwCommandID, 0};		
			if (SUCCEEDED(spCmdTarget->QueryStatus(&CMDSETID_Forms3, 1, &cmdInfo, NULL)))
				return cmdInfo.cmdf & OLECMDF_ENABLED;
		}
	}
	catch(...)
	{
	}

	return FALSE;
}

void CStylerView::SetLoading(BOOL bLoading)
{
	int nState = bLoading ? -1 : 3;

	if (m_nLoadingState != nState)
	{
		m_nLoadingState = nState;
		GetMainFrame()->m_MTIClientWnd.Invalidate(FALSE);
	}
}


BOOL CStylerView::PopupFilter(CString str)
{	

	for (int i = 0; i < CPopupFilter::m_lstFilter.GetSize(); i++)
	{		
		if (str.Find(CPopupFilter::m_lstFilter[i]) != -1)
		{
			return TRUE;
		}
	}
	return FALSE;
}




// CStylerView virtuals

BOOL CStylerView::Create(LPCTSTR /*lpszClassName*/, LPCTSTR lpszWindowName,
						DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
						UINT nID, CCreateContext* pContext)
{
	static CString strClassName;
	if (strClassName.IsEmpty())
	{

		strClassName = AfxRegisterWndClass(
			CS_DBLCLKS,                       // if you need double-clicks
			NULL,                             // no cursor (use default)
			NULL,                             // no background brush
			AfxGetApp()->LoadIcon(IDR_MAINFRAME)); // app icon
		ASSERT(strClassName);
	}
 
    



	// create the view window itself
	m_pCreateContext = pContext;
	if (!CView::Create(strClassName, lpszWindowName,
				dwStyle, rect, pParentWnd,  nID, pContext))
	{
		return FALSE;
	}

	AfxEnableControlContainer();

	RECT rectClient;
	GetClientRect(&rectClient);

	// create the control window
	// AFX_IDW_PANE_FIRST is a safe but arbitrary ID
	if (!m_wndBrowser.CreateControl(CLSID_WebBrowser, lpszWindowName,
				WS_VISIBLE | WS_CHILD, rectClient, this, AFX_IDW_PANE_FIRST))
	{
		DestroyWindow();
		return FALSE;
	}

	LPUNKNOWN lpUnk = m_wndBrowser.GetControlUnknown();
	HRESULT hr = lpUnk->QueryInterface(IID_IWebBrowser2, (void**) &m_pBrowserApp);
	if (!SUCCEEDED(hr))
	{
		m_pBrowserApp = NULL;
		m_wndBrowser.DestroyWindow();
		DestroyWindow();
		return FALSE;
	}

	if (m_pBrowserApp)
	{
		CComPtr<IOleObject> spOleObj;
		
		m_pBrowserApp->QueryInterface(IID_IOleObject, (void**)&spOleObj);
		if (spOleObj)
			spOleObj->SetClientSite((IOleClientSite*)GetInterface(&IID_IOleClientSite));
	}


	return TRUE;
}


BOOL CStylerView::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg == NULL || m_hWnd == NULL)
		return TRUE;


	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		m_infMouse.nLClick = GetTickCount();
		m_infMouse.nRClick = 0;
	}

	if (pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_RBUTTONDOWN ||
		pMsg->message == WM_MBUTTONDOWN ||
		pMsg->message == WM_LBUTTONDBLCLK ||
		pMsg->message == WM_RBUTTONDBLCLK)
	{

		int nCommand = CMouseManager::FindMouseCommand(MOUSE_AREA_BROWSER, pMsg->message);
		if (nCommand != -1)
		{
			AfxGetMainWnd()->PostMessage(WM_COMMAND, nCommand);
			return TRUE;
		}

	}


	if (CView::PreTranslateMessage(pMsg))
		return TRUE;

	// don't translate dialog messages when in Shift+F1 help mode
	CFrameWnd* pFrameWnd = GetTopLevelFrame();
	if (pFrameWnd != NULL && pFrameWnd->m_bHelpMode)
		return FALSE;

	if (pFrameWnd->PreTranslateMessage(pMsg))
			return TRUE;

	if (pMsg->message == WM_KEYDOWN && m_pBrowserApp)
	{		
		CComQIPtr<IOleInPlaceActiveObject> spActiveObj(m_pBrowserApp);
		if (spActiveObj && spActiveObj->TranslateAccelerator(pMsg) == S_OK)
			return TRUE;

	}

	return FALSE;

}



BOOL CStylerView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~WS_BORDER;

	return CHtmlView::PreCreateWindow(cs);
}

void CStylerView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	COleVariant vaZoomFactor(m_nFontSize);
	ExecWB(OLECMDID_ZOOM , OLECMDEXECOPT_DONTPROMPTUSER,  &vaZoomFactor, NULL);	

	if (GetDocument()->GetCurrentUrl().IsEmpty())
	{	
		if (CMainFrame::m_nStartup == STARTUP_HOME)	GoHome(); else
		if (CMainFrame::m_nStartup == STARTUP_BLANK) Navigate(ABOUTBLANK);
	}
}

void CStylerView::PostNcDestroy() 
{
	CHtmlView::PostNcDestroy();
}

void CStylerView::OnActivateView( BOOL bActivate, CView* pActivateView, 
	CView* pDeactiveView )
{

	if (bActivate && !m_bActive)
	{
		GetMainFrame()->SetAddress(GetDocument()->GetCurrentUrl());
		RefreshExplorer();		

	}
	m_bActive = bActivate;
	
	CHtmlView:: OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CStylerView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
{

	if(ppDisp == NULL || Cancel == NULL)
		return;



	if(m_bFilterAll)
	{
	
		double secs = (double)(GetTickCount() - m_infMouse.nLClick)/(double)1000;
		double Rsecs = (double)(GetTickCount() - m_infMouse.nRClick)/(double)1000;

		BSTR bstrTag = NULL;


		if((secs > 0.7 && secs < 4.0) && !IsLoading())
		{
			//get click point
			IHTMLElement* pElem = NULL;
			try
			{
				CComPtr<IHTMLDocument2> spDoc = GetHtmlDocument2();
				if(spDoc)
				{
					if(SUCCEEDED(spDoc->elementFromPoint(m_infMouse.ptClick.x, m_infMouse.ptClick.y, &pElem)))
					{
						if(pElem)
						{
							pElem->get_tagName(&bstrTag);
							pElem->Release();
						}
					}
				}
				
			}catch(...)
			{
			}

				
		}
		
		if( !(m_infMouse.nLClick && ((secs >= 0 && secs <= 0.7) || (bstrTag && wcscmp(bstrTag, L"A") == 0) /*|| !IsLoading()*/)) 
			&& !((Rsecs >= 0 && Rsecs <= 10 && m_infMouse.nRClick) /*|| !IsLoading()*/))
		{
			*ppDisp = NULL;
			*Cancel = TRUE;

			TRACE(_T("Filter Popup\n"));
			
			m_infMouse.Clear();
				
			if(bstrTag)	SysFreeString(bstrTag);
				
			return;
		}
			
		if(bstrTag)	SysFreeString(bstrTag);				
			
		
	}

	


	CWinApp* pApp = AfxGetApp();
	
	// Get the correct document template.
	POSITION pos = pApp->GetFirstDocTemplatePosition();
	CDocTemplate* pDocTemplate = pApp->GetNextDocTemplate( pos );
	
	
	CStylerDoc* pDoc = (CStylerDoc*)pDocTemplate->CreateNewDocument();
	pDoc->SetUrl(GetDocument()->GetCurrentUrl());
	
	// Create a new frame.
	CFrameWnd* pFrame = pDocTemplate->CreateNewFrame(pDoc, (CFrameWnd*)AfxGetMainWnd() );
	
	// Activate the frame.
	
	if (m_bLock) ((CChildFrame*)pFrame)->m_bActivate = FALSE;	
	pDocTemplate->InitialUpdateFrame( pFrame, NULL );
	CStylerView* pView = (CStylerView*)pFrame->GetActiveView();
	
	// Pass pointer of WebBrowser object.
	pView->SetRegisterAsBrowser( TRUE );   
	*ppDisp = pView->GetApplication();   
	
	pView->m_bPopup = TRUE;
	
}

void CStylerView::OnTitleChange(LPCTSTR lpszText)
{
	if (m_pDocument != NULL)
		m_pDocument->SetTitle(lpszText);

	SetAddress();
}



void CStylerView::NavigateComplete2(LPDISPATCH pDisp, VARIANT* /*URL*/)
{
	if (!m_lpDisp) m_lpDisp = pDisp;	
}

void CStylerView::DocumentComplete(LPDISPATCH /*pDisp*/, VARIANT* /*URL*/)
{

	if (m_lpDisp && m_lpDisp == m_lpDisp)
	{
		m_lpDisp = NULL;
		TRACE(_T("Document is done downloading\n"));
		try
		{
			SetLoading(FALSE);
		
			RefreshExplorer();		

			CComPtr<IHTMLDocument2> spDoc = GetHtmlDocument2();

			SetAddress();		
			
			if( spDoc )
			{	
				
				BSTR bstr = NULL;		
				spDoc->get_charset( &bstr );
				CString strCharset(bstr);
				SysFreeString(bstr);
				
				for (int i = 0; i < CMainFrame::m_arrEncodingPage.GetSize(); i++)
				{
					if (CMainFrame::m_arrEncodingPage[i] == strCharset)
					{
						m_nEncoding = i + ID_VIEW_ENCODING_FIRST;
						
						break;
					}
				}
			}
			m_bPopup = FALSE;
		}
		catch(...)
		{
		}	
		
		m_infMouse.Clear();
		
	}
	
}

void CStylerView::OnProgressChange(long nProgress, long nProgressMax)
{
	if (nProgressMax && nProgress >= 0)
	{
		long nIndex = nProgress * 4 / nProgressMax;
		if (nIndex > 3) nIndex = 3;

		m_nProgress = nProgress * 100 / nProgressMax;

		if (m_nLoadingState != nIndex)
		{
			m_nLoadingState = nIndex;
			GetMainFrame()->m_MTIClientWnd.Invalidate(FALSE);
		}			
	} else m_nProgress = 0;
}


void CStylerView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD /*nFlags*/,
		LPCTSTR /*lpszTargetFrameName*/, CByteArray& baPostedData,
		LPCTSTR /*lpszHeaders*/, BOOL* pbCancel)
{
	if (m_bFilterList && m_bPopup && PopupFilter(lpszURL))
	{
		if (pbCancel) *pbCancel = TRUE;
		GetParentFrame()->PostMessage(WM_CLOSE);
		return;
	}

	if (m_bLock && !baPostedData.GetSize() && GetTickCount() - m_infMouse.nLClick < 600)
	{
		if(_tcsstr(lpszURL, _T("mailto:")) == NULL && _tcsstr(lpszURL, _T("javascript:")) == NULL)
		{
			if (pbCancel)
			{
				OpenWindow(lpszURL, FALSE);

				 *pbCancel = TRUE;
			}
		}
	}

}


void CStylerView::OnCommandStateChange(long nCommand, BOOL bEnable)
{
	if (nCommand == CSC_NAVIGATEFORWARD) m_bForward = bEnable;
	if (nCommand == CSC_NAVIGATEBACK) m_bBack = bEnable;
}




// CStylerView message handlers

void CStylerView::OnSize(UINT nType, int cx, int cy)
{
	
	CFormView::OnSize(nType, cx, cy);

	if (::IsWindow(m_wndBrowser.m_hWnd))
	{
		HDWP wp = BeginDeferWindowPos(1);
		wp = DeferWindowPos(wp, m_wndBrowser.m_hWnd, 0, 0, 0, cx, cy, 
			SWP_NOZORDER | SWP_NOREPOSITION);	
		EndDeferWindowPos(wp);
		//m_wndBrowser.MoveWindow(0, 0, cx, cy);
	}	
}

void CStylerView::OnParentNotify(UINT message, LPARAM lParam) 
{
	if(message == WM_LBUTTONDOWN )
	{	
		m_infMouse.nLClick = GetTickCount();
		m_infMouse.nRClick = 0;
		m_infMouse.ptClick = CPoint(LOWORD((DWORD)lParam), HIWORD((DWORD)lParam));
	}
	else if(message == WM_RBUTTONDOWN ) 
	{
		m_infMouse.nRClick = GetTickCount();
		m_infMouse.nLClick = 0;
	
	} else if(message == WM_DESTROY)
	{		
		GetParentFrame()->PostMessage(WM_CLOSE);
	}

	
	CHtmlView::OnParentNotify(message, lParam);
}


LRESULT CStylerView::OnGetTabIcon(WPARAM /*lParam*/, LPARAM /*wParam*/)
{
	int nIndex = m_bLock ? 4 : m_nLoadingState < 0 ? 3 : m_nLoadingState;

	if (nIndex < 5)
		return (LRESULT)m_arrIcons[nIndex];

	return 0;
}

void CStylerView::OnUpdateGotoBack(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bBack);	
}

void CStylerView::OnUpdateGotoForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bForward);	
}


void CStylerView::OnFileProperties()
{
	ExecWB(OLECMDID_PROPERTIES, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}

void CStylerView::OnEditSelectall()
{
	ExecWB(OLECMDID_SELECTALL, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}

void CStylerView::OnFilePrintPreview()
{
	ExecWB(OLECMDID_PRINTPREVIEW, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
}

void CStylerView::OnFileSaveAs()
{
	ExecWB(OLECMDID_SAVEAS, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	
}

void CStylerView::OnEditFind()
{
	CComQIPtr<IOleCommandTarget> spCmdTarget = m_pBrowserApp;
	spCmdTarget->Exec(&CGID_IWebBrowser, HTMLID_FIND, 0, NULL, NULL);
 }

void CStylerView::OnViewSource()
{
	CComQIPtr<IOleCommandTarget> spCmdTarget = m_pBrowserApp;
	spCmdTarget->Exec(&CGID_IWebBrowser, HTMLID_VIEWSOURCE, 0, NULL, NULL);
}


void CStylerView::OnToolsOptions()
{
	CComQIPtr<IOleCommandTarget> spCmdTarget = m_pBrowserApp;
	spCmdTarget->Exec(&CGID_IWebBrowser, HTMLID_OPTIONS, 0, NULL, NULL);
}


void CStylerView::OnAddToFavorites()
{
	IShellUIHelper* pShell = NULL;
	HRESULT hr = CoCreateInstance(CLSID_ShellUIHelper, NULL, CLSCTX_SERVER,
		IID_IShellUIHelper, (void**)&pShell);
	if (hr == S_OK)
	{
		COleVariant vtTitle(GetDocument()->GetTitle());
		BSTR bstrUrl = GetDocument()->GetCurrentUrl().AllocSysString();
		
		pShell->AddFavorite(bstrUrl, &vtTitle);
		
		SysFreeString(bstrUrl);
		pShell->Release();
	}
}


void CStylerView::OnShowImages()
{
	m_bShowImages = !m_bShowImages;
	
	IOleControl* pControl;
	m_pBrowserApp->QueryInterface( IID_IOleControl, (void**)&pControl );
	if( pControl != NULL )
	{
		pControl->OnAmbientPropertyChange( DISPID_AMBIENT_DLCONTROL );
		pControl->Release();
	}

	Navigate2(GetDocument()->GetCurrentUrl());
}

void CStylerView::OnUpdateShowImages(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!m_bShowImages);
}



void CStylerView::OnEditCopy() 
{
	ExecFormsCommand(IDM_COPY);
}

void CStylerView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{

	pCmdUI->Enable(QueryFormsCommand(IDM_COPY));
}

void CStylerView::OnEditCut() 
{
	ExecFormsCommand(IDM_CUT);
}

void CStylerView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(QueryFormsCommand(IDM_CUT));
}

void CStylerView::OnEditPaste() 
{
	ExecFormsCommand(IDM_PASTE);
}

void CStylerView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(QueryFormsCommand(IDM_PASTE));
}
			  

void CStylerView::OnTextSize()
{
	m_nFontSize = (m_nFontSize + 1) % 5;
	ASSERT(m_nFontSize >=0 && m_nFontSize < 5);

	if (m_pBrowserApp)
	{	
		COleVariant vaZoomFactor(m_nFontSize);
		ExecWB(OLECMDID_ZOOM , OLECMDEXECOPT_DONTPROMPTUSER,  &vaZoomFactor, NULL);	
	}

}


void CStylerView::OnTextSizeRange(UINT nID)
{
	m_nFontSize = ID_TEXTSIZE_SMALLEST - nID;
	ASSERT(m_nFontSize >=0 && m_nFontSize < 5);
	
	if (m_pBrowserApp)
	{	
		COleVariant vaZoomFactor(m_nFontSize);
		ExecWB(OLECMDID_ZOOM , OLECMDEXECOPT_DONTPROMPTUSER,  &vaZoomFactor, NULL);	
	}
}

void CStylerView::OnUpdateTextSizeRange(CCmdUI* pCmdUI) 
{	
	pCmdUI->SetCheck(long(ID_TEXTSIZE_SMALLEST - pCmdUI->m_nID) == m_nFontSize);
}




void CStylerView::OnUpdateViewEncodingRange(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nEncoding == pCmdUI->m_nID);
}
void CStylerView::OnViewEncodingRange(UINT nID)
{

	CComPtr<IHTMLDocument2> spDoc = GetHtmlDocument2();

	if( spDoc )
	{
		int nIndex = nID - ID_VIEW_ENCODING_FIRST;
		ASSERT(nIndex < CMainFrame::m_arrEncodingPage.GetSize());

		BSTR bstr;
		bstr = CMainFrame::m_arrEncodingPage[nIndex].AllocSysString();

		spDoc->put_charset( bstr );
		SysFreeString(bstr);
		Refresh2(1);

		m_nEncoding = nID;
	}

}

void CStylerView::OnLinkStartDrag(NMHDR* /*pNMHDR*/, LRESULT* /*pRes*/)
{
	USES_CONVERSION;

	CString strTitle = GetDocument()->GetTitle();
	CString strAddress = GetDocument()->GetCurrentUrl();
	
	strTitle.Replace(_T('\\'), _T('-'));
	strTitle.Replace(_T('/'), _T('-'));
	strTitle.Replace(_T(':'), _T(' '));
	strTitle.Replace(_T('|'), _T(' '));
	
	CString strDirectory;
	GetTempPath (MAX_PATH, strDirectory.GetBuffer(MAX_PATH));
	strDirectory.ReleaseBuffer();
	
	CString strPath = strDirectory + strTitle + _T(".url");
	
	WritePrivateProfileString(_T("InternetShortcut"), _T("URL"), strAddress,  strPath);
	
	TCHAR chFilePath[_MAX_PATH];
	ZeroMemory(chFilePath, sizeof(chFilePath));

	STRCPY_S(chFilePath, _MAX_PATH, (LPCTSTR)strPath);

	COleDataSource ds;
	
	CSharedFile sharedFile;
	CArchive ar (&sharedFile, CArchive::store);

	DROPFILES df;
	df.pFiles = sizeof(DROPFILES);
	df.pt = CPoint(0, 0);
	df.fNC = 0;
#ifdef _UNICODE
	df.fWide = TRUE;
#else
	df.fWide = FALSE;
#endif

	ar.Write(&df, sizeof(DROPFILES));
	ar.Write(chFilePath, (strPath.GetLength() + 2) * sizeof(TCHAR));

	ar.Close();
	
	HGLOBAL hGlobal = sharedFile.Detach();


	ds.CacheGlobalData(CF_HDROP, hGlobal);
	ds.DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_LINK);

	return;
}

void CStylerView::OnViewLock()
{
	m_bLock = !m_bLock;
	GetMainFrame()->m_MTIClientWnd.Invalidate(FALSE);
}
void CStylerView::OnUpdateViewLock(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bLock);
}

void CStylerView::OnUpdateAddPageHere(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CStylerView::OnAddPageHere(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CString strDirectory = tagNMCONTROL->pControl->GetParameter();
	CString strParent = strDirectory.Left(strDirectory.GetLength() - 1);
	if (strParent.Find('\\') != -1)
	{
		strParent.Delete(0, strParent.ReverseFind('\\') + 1);
	}
	
	
	
	CLinkProperties lp;
	lp.m_strTitle = GetDocument()->GetTitle();
	lp.m_strAddress = GetDocument()->GetCurrentUrl();
	lp.m_strParent = strParent;
	
	lp.m_strTitle.Replace('\\', '-');
	lp.m_strTitle.Replace('/', '-');
	lp.m_strTitle.Replace(':', ' ');
	lp.m_strTitle.Replace('|', ' ');
	
	
	if (lp.DoModal() == IDOK)
	{
		WritePrivateProfileString(_T("InternetShortcut"), _T("URL"), lp.m_strAddress, 
			strDirectory + lp.m_strTitle + _T(".url"));
	
	}
}

void CStylerView::OnUpdateIndicator(CCmdUI *pCmdUI)
{
	ASSERT_KINDOF(CXTPStatusBar, pCmdUI->m_pOther);
	CIndicatorStatusBar* bar =(CIndicatorStatusBar*) pCmdUI->m_pOther;
	
	int nProgress = (m_nLoadingState != -1 && m_nLoadingState != 3) ? m_nProgress : 0;
	bar->SetProgress(nProgress);

}
