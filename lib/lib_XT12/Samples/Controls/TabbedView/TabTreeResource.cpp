// TabTreeResource.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "TabTreeResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabTreeResource

CTabTreeResource::CTabTreeResource()
{
	m_bMultiSelect = true;
}

CTabTreeResource::~CTabTreeResource()
{
}


BEGIN_MESSAGE_MAP(CTabTreeResource, CXTTreeCtrl)
	//{{AFX_MSG_MAP(CTabTreeResource)
	ON_WM_NCHITTEST_EX()
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabTreeResource message handlers

BOOL CTabTreeResource::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CXTTreeCtrl::PreCreateWindow( cs ))
		return FALSE;

	// Set the style for the tree control.
	cs.style |= TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

LRESULT CTabTreeResource::OnNcHitTest(CPoint point) 
{
	UINT uFlag=0;

	// Get the cursor location in client coordinates.
	CPoint pt = point;	
	ScreenToClient(&pt);

	// Get a pointer to the tooltip control.
	CToolTipCtrl* pCtrl = (CToolTipCtrl*)CWnd::FromHandle(
		(HWND)::SendMessage(m_hWnd, TVM_GETTOOLTIPS, 0, 0L));

	// If we have a valid tooltip pointer and the cursor
	// is over a tree item, the bring the tooltip control
	// to the top of the Z-order.
	if (pCtrl && HitTest(pt, &uFlag)){
		pCtrl->SetWindowPos(&wndTop,0, 0, 0, 0,
			SWP_NOACTIVATE | SWP_NOSIZE |SWP_NOMOVE);
	}
	
	return (LRESULT)CXTTreeCtrl::OnNcHitTest(point);
}

void CTabTreeResource::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	// TODO: Add your control notification handler code here
	if (pTVDispInfo->item.pszText)
	{
		SetItemText(pTVDispInfo->item.hItem,
			pTVDispInfo->item.pszText);
	}
	
	*pResult = 0;
}

BOOL CTabTreeResource::PreTranslateMessage(MSG* pMsg) 
{
	// If the tree control has an edit control, don't allow
	// the framework to process accelerators, let the edit
	// control handle it instead...
	
	CEdit* pEditCtrl = GetEditControl();
	if (pEditCtrl && ::IsWindow(pEditCtrl->m_hWnd))
	{
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		
		return TRUE;
	}
	
	return CXTTreeCtrl::PreTranslateMessage(pMsg);
}

int CTabTreeResource::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the image list used by the tree control.
	if (!m_imageList.Create(IDB_IL_RSRC, 16, 1, RGB(0x00,0x80,0x80)))
		return -1;
	
	// Get a pointer to the tree control, and set its imagelist.
	SetImageList(&m_imageList, TVSIL_NORMAL);

	// Initialize the view.
	UpdateTree();
	
	return 0;
}

void CTabTreeResource::UpdateTree()
{
	// add the parent item
	HTREEITEM htItem = InsertItem(_T("XtremeDemo resources"), 9, 9);
	SetItemState(htItem, TVIS_BOLD, TVIS_BOLD);
	
	HTREEITEM hti = InsertItem(_T("Accelerator"), 0, 1, htItem);
	InsertItem(_T("IDR_MAINFRAME"), 2, 2, hti);
	Expand(hti, TVE_EXPAND);
	
	hti = InsertItem(_T("Dialog"), 0, 1, htItem);
	InsertItem(_T("IDD_ABOUTBOX"), 3, 3, hti);
	Expand(hti, TVE_EXPAND);
	
	hti = InsertItem(_T("Icon"), 0, 1, htItem);
	InsertItem(_T("IDR_MAINFRAME"), 4, 4, hti);
	InsertItem(_T("IDR_XTREMETYPE"), 4, 4, hti);
	Expand(hti, TVE_EXPAND);
	
	hti = InsertItem(_T("Menu"), 0, 1, htItem);
	InsertItem(_T("IDR_MAINFRAME"), 5, 5, hti);
	InsertItem(_T("IDR_XTREMETYPE"), 5, 5, hti);
	
	hti = InsertItem(_T("String Table"), 0, 1, htItem);
	InsertItem(_T("String Table"), 6, 6, hti);

	hti = InsertItem(_T("Toolbar"), 0, 1, htItem);
	InsertItem(_T("IDR_MAINFRAME"), 7, 7, hti);

	hti = InsertItem(_T("Version"), 0, 1, htItem);
	InsertItem(_T("VS_VERSION_INFO"), 8, 8, hti);

	Expand (htItem, TVE_EXPAND);
}
