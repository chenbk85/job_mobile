// ResourceEditorView.cpp : implementation of the CResourceEditorView class
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

#include "ResourceEditorDoc.h"
#include "ResourceEditorView.h"
#include "ChildFrm.h"
#include "ResourceViewRecord.h"
#include "MainFrm.h"
#include "ResourceExport.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorView

IMPLEMENT_DYNCREATE(CResourceEditorView, CXTPReportView)

BEGIN_MESSAGE_MAP(CResourceEditorView, CXTPReportView)
	//{{AFX_MSG_MAP(CResourceEditorView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_NOTIFY(XTP_NM_REPORT_VALUECHANGED, XTP_ID_REPORT_CONTROL, OnReportValueChanged)
	ON_NOTIFY(XTP_NM_REPORT_SELCHANGED, XTP_ID_REPORT_CONTROL, OnReportSelectionChanged)

	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorView construction/destruction

CResourceEditorView::CResourceEditorView()
{
	// TODO: add construction code here

}

CResourceEditorView::~CResourceEditorView()
{
}

BOOL CResourceEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	//cs.style &= ~WS_BORDER;

	return CXTPReportView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CResourceEditorView diagnostics

#ifdef _DEBUG
void CResourceEditorView::AssertValid() const
{
	CXTPReportView::AssertValid();
}

void CResourceEditorView::Dump(CDumpContext& dc) const
{
	CXTPReportView::Dump(dc);
}

CResourceEditorDoc* CResourceEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CResourceEditorDoc)));
	return (CResourceEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResourceEditorView message handlers

int CResourceEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CResourceEditorView::LoadXMLString(CXTPPropExchange* pPX, LPCTSTR pszPropName, CString& strValue)
{
#ifdef _UNICODE
	PX_String(pPX, pszPropName, strValue);
#else

	BSTR bstrValue = 0;
	PX_Bstr(pPX, pszPropName, bstrValue, 0);

	ASSERT(!bstrValue || wcslen(bstrValue) < 1024);

	if (bstrValue)
	{
		WideCharToMultiByte(GetDocument()->m_pLanguageInfo->nCodePage, 0, bstrValue, -1, strValue.GetBuffer(1024), 1024, 0, 0);
		strValue.ReleaseBuffer();
		SysFreeString(bstrValue);
	}
#endif
	CXTPPropExchangeXMLNode::PreformatString(strValue, FALSE);
}

void CResourceEditorView::PopulateStringResources(CTreeCtrl& wndResourceTree, CXTPPropExchange* pResources, HTREEITEM hItemStrings)
{
	CXTPReportControl& wndReport = GetReportCtrl();

	
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(pResources->GetEnumerator(_T("string")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeXMLNode* ptrSectionString = (CXTPPropExchangeXMLNode*)ptrEnumeratorStrings->GetNext(pos);
		CString strValue;
		DWORD dwId = 0;
		
		PX_DWord(ptrSectionString, _T("id"), dwId);
		LoadXMLString(ptrSectionString, _T("value"), strValue);
		
		CResourceViewRecord* pRecord = new CResourceViewRecord(_T("String"), resString, dwId, strValue);
		wndReport.GetRecords()->Add(pRecord);			
		pRecord->m_pSection = ptrSectionString;		
		
		HTREEITEM hItemString = wndResourceTree.InsertItem(GetResourceName(dwId), 6, 6, hItemStrings);
		
		wndResourceTree.SetItemData(hItemString, (DWORD_PTR)pRecord);
	}
}


void CResourceEditorView::PopulateMenuItemsResources(CXTPReportRecord* pMenuBase, CXTPReportRecord* pMenuRecord, CXTPPropExchange* pResourceMenu)
{
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(pResourceMenu->GetEnumerator(_T("menuitem")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeXMLNode* ptrSectionMenuItem = (CXTPPropExchangeXMLNode*)ptrEnumeratorStrings->GetNext(pos);
		CString strValue;
		DWORD dwId = 0;
		
		PX_DWord(ptrSectionMenuItem, _T("id"), dwId);
		LoadXMLString(ptrSectionMenuItem, _T("caption"), strValue);
	
		CResourceViewRecord* pRecord = new CResourceViewRecord(_T("Menuitem"), resMenu, dwId, strValue);
		pMenuRecord->GetChilds()->Add(pRecord);			
		pRecord->m_pSection = ptrSectionMenuItem;	
		
		PopulateMenuItemsResources(pMenuBase, pRecord, ptrSectionMenuItem);
	}
}


void CResourceEditorView::PopulateDialogControlsResources(CResourceViewRecord* pDialogRecord, CXTPPropExchange* pResourceDialog)
{
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(pResourceDialog->GetEnumerator(_T("control")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeXMLNode* ptrSectionDialogControl = (CXTPPropExchangeXMLNode*)ptrEnumeratorStrings->GetNext(pos);
		CString strValue;
		DWORD dwId = 0;
		
		PX_DWord(ptrSectionDialogControl, _T("id"), dwId);
		LoadXMLString(ptrSectionDialogControl, _T("caption"), strValue);
		
		CResourceViewRecord* pRecord = new CResourceViewRecord(_T("Control"), resDialog, dwId, strValue);
		pDialogRecord->GetChilds()->Add(pRecord);			
		pRecord->m_pSection = ptrSectionDialogControl;	
		pRecord->m_pBaseRecord = pDialogRecord;
	}
}

void CResourceEditorView::PopulateDialogResources(CTreeCtrl& wndResourceTree, CXTPPropExchange* pResources, HTREEITEM hItemDialogs)
{
	CXTPReportControl& wndReport = GetReportCtrl();

	
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(pResources->GetEnumerator(_T("dialog")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeXMLNode* ptrSectionDialog = (CXTPPropExchangeXMLNode*)ptrEnumeratorStrings->GetNext(pos);
		DWORD dwId = 0;
		CString strValue;
		
		PX_DWord(ptrSectionDialog, _T("id"), dwId);
		LoadXMLString(ptrSectionDialog, _T("caption"), strValue);
		
		CResourceViewRecord* pRecord = new CResourceViewRecord(_T("Dialog"), resDialog, dwId, strValue);
		wndReport.GetRecords()->Add(pRecord);			
		pRecord->m_pSection = ptrSectionDialog;				
		
		HTREEITEM hItemDialog = wndResourceTree.InsertItem(GetResourceName(dwId), 3, 3, hItemDialogs);
		
		wndResourceTree.SetItemData(hItemDialog, (DWORD_PTR)pRecord);

		PopulateDialogControlsResources(pRecord, ptrSectionDialog);
	}
}


void CResourceEditorView::PopulateMenuResources(CTreeCtrl& wndResourceTree, CXTPPropExchange* pResources, HTREEITEM hItemMenus)
{
	CXTPReportControl& wndReport = GetReportCtrl();

	
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(pResources->GetEnumerator(_T("menu")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeXMLNode* ptrSectionMenu = (CXTPPropExchangeXMLNode*)ptrEnumeratorStrings->GetNext(pos);
		DWORD dwId = 0;
		
		PX_DWord(ptrSectionMenu, _T("id"), dwId);
		
		CResourceViewRecord* pRecord = new CResourceViewRecord(_T("Menu"), resMenu, dwId, _T(""));
		wndReport.GetRecords()->Add(pRecord);			
		pRecord->m_pSection = ptrSectionMenu;		
		pRecord->SetEditable(FALSE);
		
		HTREEITEM hItemMenu = wndResourceTree.InsertItem(GetResourceName(dwId), 5, 5, hItemMenus);
		
		wndResourceTree.SetItemData(hItemMenu, (DWORD_PTR)pRecord);

		PopulateMenuItemsResources(pRecord, pRecord, ptrSectionMenu);
	}
}

void CResourceEditorView::PopulateResources()
{
	CXTPReportControl& wndReport = GetReportCtrl();
	wndReport.GetRecords()->RemoveAll();

	CResourceEditorDoc* pDocument = GetDocument();
	CXTPPropExchangeXMLNode* pResources = pDocument->m_pResources;

	CTreeCtrl& wndResourceTree = ((CChildFrame*)GetParentFrame())->m_wndResourceTree;
	wndResourceTree.DeleteAllItems();


	HTREEITEM hItemResources = wndResourceTree.InsertItem(_T("Resources"));
	HTREEITEM hItemStrings = wndResourceTree.InsertItem(_T("String Table"), 6, 6, hItemResources);
	HTREEITEM hItemMenus = wndResourceTree.InsertItem(_T("Menus"), 5, 5, hItemResources);
	HTREEITEM hItemDialogs = wndResourceTree.InsertItem(_T("Dialogs"), 3, 3, hItemResources);

	
	if (pResources)
	{
		CString strLanguage;
		PX_String(pResources, _T("Language"), strLanguage);	
		wndReport.GetColumns()->Find(3)->SetCaption(strLanguage);
		
	
		PopulateStringResources(wndResourceTree, pResources, hItemStrings);
		PopulateMenuResources(wndResourceTree, pResources, hItemMenus);
		PopulateDialogResources(wndResourceTree, pResources, hItemDialogs);
	}

	wndResourceTree.Expand(hItemResources, TVE_EXPAND);


	wndReport.Populate();
}

void CResourceEditorView::OnInitialUpdate() 
{
	CXTPReportView::OnInitialUpdate();

	XTP_RESOURCEMANAGER_LANGINFO* pLanguageInfo = GetDocument()->m_pLanguageInfo;
	ASSERT(pLanguageInfo);
	
	CXTPReportControl& wndReport = GetReportCtrl();
	wndReport.GetImageManager()->SetIcons(IDB_RESTREE, 0, 10, 0);
	wndReport.GetPaintManager()->m_treeStructureStyle = xtpReportTreeStructureDots;

	CXTPReportColumn* pColumn;


	pColumn = new CXTPReportColumn(4, _T("Resource"), 180, TRUE);
	pColumn->SetEditable(FALSE);
	wndReport.GetColumns()->Add(pColumn);
	wndReport.GetColumns()->GetGroupsOrder()->Add(pColumn, FALSE);
	pColumn->SetTreeColumn(TRUE);

	pColumn = new CXTPReportColumn(0, _T("Module"), 130, TRUE);
	pColumn->SetEditable(FALSE);
	wndReport.GetColumns()->Add(pColumn);
	wndReport.GetColumns()->GetGroupsOrder()->Add(pColumn);
	pColumn->SetVisible(FALSE);
	
	pColumn = new CXTPReportColumn(1, _T("ID"), 40, FALSE);
	pColumn->SetEditable(FALSE);
	wndReport.GetColumns()->Add(pColumn);

	pColumn = new CXTPReportColumn(2, _T("English US (Original Resources)"), 300, TRUE);
	pColumn->SetEditable(FALSE);
	wndReport.GetColumns()->Add(pColumn);
	
	pColumn = new CXTPReportColumn(3, _T("Tranlated"), 300, TRUE);
	pColumn->SetAlignment(pLanguageInfo->nCodePage == 1256 || pLanguageInfo->nCodePage == 1255 ? DT_RIGHT : DT_LEFT);
	wndReport.GetColumns()->Add(pColumn);
	
	wndReport.GetPaintManager()->SetColumnStyle(xtpReportColumnExplorer);
	wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	wndReport.AllowEdit(TRUE);
	wndReport.EditOnClick(FALSE);
	wndReport.ShowGroupBy();


	LOGFONT lfIcon;
	VERIFY(::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lfIcon), &lfIcon, 0));
	lfIcon.lfCharSet = pLanguageInfo->nFontCharSet;

	GetReportCtrl().GetPaintManager()->SetTextFont(lfIcon);

	
	PopulateResources();

}

void CResourceEditorView::OnReportValueChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify->pItem);

	CResourceEditorDoc* pDocument = GetDocument();
	CXTPPropExchangeXMLNode* pResources = pDocument->m_pResources;


	if (pItemNotify->pItem && pResources)
	{
		CResourceViewRecord* pRecord = (CResourceViewRecord*)pItemNotify->pItem->GetRecord();
	
		CXTPPropExchangeXMLNode* ptrSectionString = pRecord->m_pSection;

		if (ptrSectionString)
		{
			ptrSectionString->SetLoading(FALSE);

			CString strValue = pItemNotify->pItem->GetCaption(0);

			CString strSection = pRecord->m_resType == resString ? _T("value"): _T("caption");

#ifdef _UNICODE
			CXTPPropExchangeXMLNode::PreformatString(strValue, TRUE);		
			PX_String(ptrSectionString, strSection, strValue);
#else
			WCHAR lpszValue[1024];
			lpszValue[0] = 0;
			MultiByteToWideChar(GetDocument()->m_pLanguageInfo->nCodePage, 0,
				strValue, -1, lpszValue, 1024);
			
			BSTR bstrVal = (BSTR)&lpszValue;	
			PX_Bstr(ptrSectionString, strSection, bstrVal, NULL);	
#endif
		}
	}

	GetDocument()->SetModifiedFlag();


}

void CResourceEditorView::OnReportSelectionChanged(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	CXTPReportControl& wndReport = GetReportCtrl();
	CXTPReportRow* pRow = wndReport.GetFocusedRow();

	CResourceEditorDoc* pDocument = GetDocument();
	CXTPPropExchangeXMLNode* pResources = pDocument->m_pResources;


	if (pRow && pRow->GetRecord() && pResources)
	{
		CResourceViewRecord* pRecord = (CResourceViewRecord*)pRow->GetRecord();
		if (pRecord->m_pBaseRecord) pRecord = pRecord->m_pBaseRecord;

		DWORD dwId = pRecord->GetId();

		if (pRecord->m_resType == resMenu && dwId)
		{
			((CMainFrame*)AfxGetMainWnd())->ShowMenuPreview(pResources, dwId, pDocument->m_pLanguageInfo);
				
		}
		else if (pRecord->m_resType == resDialog && dwId)
		{			
			((CMainFrame*)AfxGetMainWnd())->ShowDialogPreview(pResources, dwId);
				
		}
		else
		{
			((CMainFrame*)AfxGetMainWnd())->ClearPreview();
		}

	}
	else
	{
		((CMainFrame*)AfxGetMainWnd())->ClearPreview();
	}
}



void CResourceEditorView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if (!bActivate)
	{
		((CMainFrame*)AfxGetMainWnd())->ClearPreview();

	}
	
	CXTPReportView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
