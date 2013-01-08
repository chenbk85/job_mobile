// TabbedViewView.cpp : implementation of the CTabbedViewView class
//
// This file is a part of the XTREME TOOLKIT MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO 
// BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED 
// WRITTEN CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS 
// OUTLINED IN THE XTREME TOOLKIT LICENSE AGREEMENT.  CODEJOCK SOFTWARE 
// GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE 
// THIS SOFTWARE ON A SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TabbedView.h"

#include "TabbedViewDoc.h"
#include "TabbedViewView.h"

#include "TabTreeClass.h"
#include "TabTreeFile.h"
#include "TabTreeResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabbedViewView

IMPLEMENT_DYNCREATE(CTabbedViewView, CXTTabView)

BEGIN_MESSAGE_MAP(CTabbedViewView, CXTTabView)
	//{{AFX_MSG_MAP(CTabbedViewView)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_RBUTTONDOWN()
	ON_WM_CANCELMODE()
    ON_COMMAND(ID_TAB_ACTIVATE, OnTabActivate)
	ON_COMMAND(ID_TAB_CLOSE, OnTabClose)
	ON_COMMAND(ID_TAB_SAVE, OnTabSave)
	ON_COMMAND(ID_TAB_SAVE_AS, OnTabSaveAs)
	ON_COMMAND(ID_TAB_PRINT, OnTabPrint)
	ON_COMMAND(ID_TAB_PRINT_PREVIEW, OnTabPrintPreview)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
	ON_COMMAND(XT_IDC_TAB_CLOSE, OnCloseTab)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabbedViewView construction/destruction

CTabbedViewView::CTabbedViewView()
{
	// TODO: add construction code here
	m_iHitTest = -1;
    m_nIDEvent = 20;

	m_bXPBorder = true;
}

CTabbedViewView::~CTabbedViewView()
{
}

BOOL CTabbedViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CXTTabView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTabbedViewView diagnostics

#ifdef _DEBUG
void CTabbedViewView::AssertValid() const
{
	CXTTabView::AssertValid();
}

void CTabbedViewView::Dump(CDumpContext& dc) const
{
	CXTTabView::Dump(dc);
}

CTabbedViewDoc* CTabbedViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabbedViewDoc)));
	return (CTabbedViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabbedViewView message handlers

int CTabbedViewView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Register as a drop target
	m_dropTarget.Register(this);
	DragAcceptFiles();

	// Create the image list used by the tab control.
	if (!m_imageList.Create( IDB_IMAGELIST, 16, 1, RGB( 0x00,0x80,0x80 )))
	{
		TRACE0("Failed to create image list.\n");
		return -1;
	}

	// Create the edit control for the edit tab.
	if (!m_editTab.Create(WS_CHILD|WS_VISIBLE,
		CRect(0,0,0,0), this, IDC_EDIT_TAB))
	{
		TRACE0("Failed to create edit control.\n");
		return -1;
	}

	// Create the tree control for the file tab
	if (!m_treeTabFile.Create(WS_CHILD|WS_VISIBLE,
		CRect(0,0,0,0), this, IDC_TREE_TAB_FILE))
	{
		TRACE0("Failed to create tree control.\n");
		return -1;
	}

	// Create the tree control for the class tab
	if (!m_treeTabClass.Create(WS_CHILD|WS_VISIBLE,
		CRect(0,0,0,0), this, IDC_TREE_TAB_CLASS))
	{
		TRACE0("Failed to create tree control.\n");
		return -1;
	}

	// Create the tree control for the resource tab
	if (!m_treeTabResource.Create(WS_CHILD|WS_VISIBLE,
		CRect(0,0,0,0), this, IDC_TREE_TAB_RESOURCE))
	{
		TRACE0("Failed to create tree control.\n");
		return -1;
	}

	// Insert the edit control into the tabbed view.
	AddControl(_T("Edit Control"), &m_editTab);

	// Insert the tree controls into the tabbed view.
	AddControl(_T("File Tree"),     &m_treeTabFile);
	AddControl(_T("Class Tree"),    &m_treeTabClass);
	AddControl(_T("Resource Tree"), &m_treeTabResource);

	// Set the tab controls image list.
	GetTabCtrl().SetImageList(&m_imageList);

	// TODO: uncomment this line if you want the tabs to appear on bottom. 
	//ModifyTabStyle(NULL, TCS_BOTTOM);

	// Set the active view to the second tab.
	SetActiveView(1);


	UpdateTabBorders();

    SetTabIcon(3, AfxGetApp()->LoadIcon(IDR_MDITABTYPE));

	return 0;
}

void CTabbedViewView::SetTabIcon(int iTab, int iImage)
{
	TC_ITEM tci;
	tci.mask = TCIF_IMAGE;

	GetTabCtrl().GetItem(iTab, &tci);
	tci.iImage = iImage;
	GetTabCtrl().SetItem(iTab, &tci);
}

void CTabbedViewView::SetTabIcon(int iTab, HICON hIcon)
{
    CImageList* pImageList = GetTabCtrl().GetImageList();
    SetTabIcon(iTab, pImageList->Add(hIcon));
}

void CTabbedViewView::OnSelChanging()
{
	CXTTabView::OnSelChanging();

	// TODO: Add your code to handle tab selection.

}

void CTabbedViewView::OnSelChange()
{
	CXTTabView::OnSelChange();

	// TODO: Add your code to handle tab selection.

}

void CTabbedViewView::OnInitialUpdate() 
{
	CXTTabView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}

void CTabbedViewView::OnFileOpen() 
{
	// TODO: Add your command handler code here

}

void CTabbedViewView::OnRButtonDown(UINT /*nFlags*/, CPoint point) 
{
	// Get the tab index based upon the cursor position.
	m_iHitTest = GetTabFromPoint(point);
	if (m_iHitTest == -1)
		return;

	CMenu popupMenu;
	VERIFY(popupMenu.CreatePopupMenu());
    popupMenu.AppendMenu(MF_STRING, ID_TAB_ACTIVATE, _T("Active View Tab"));
	popupMenu.AppendMenu(MF_SEPARATOR);
	popupMenu.AppendMenu(MF_STRING, ID_TAB_CLOSE, _T("&Close"));
	popupMenu.AppendMenu(MF_STRING, ID_TAB_SAVE, _T("&Save\tCtrl+S"));
	popupMenu.AppendMenu(MF_STRING, ID_TAB_SAVE_AS, _T("Save &As..."));
	popupMenu.AppendMenu(MF_SEPARATOR);
	popupMenu.AppendMenu(MF_STRING, ID_TAB_PRINT, _T("&Print\tCtrl+P"));
	popupMenu.AppendMenu(MF_STRING, ID_TAB_PRINT_PREVIEW, _T("Print Pre&view"));

    ::SetMenuDefaultItem(popupMenu.m_hMenu, 0, TRUE);

	CPoint pt = point;
	ClientToScreen(&pt);
	popupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		pt.x, pt.y, this);

	popupMenu.DestroyMenu();
}

void CTabbedViewView::OnCancelMode() 
{
	CXTTabView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CTabbedViewView::OnTabActivate()
{
//	TRACE0("CTabbedViewView::OnTabActivate()\n");
	SetActiveView(m_iHitTest);
}

void CTabbedViewView::OnTabClose()
{
//	TRACE0("CTabbedViewView::OnTabClose()\n");
	if (GetTabCtrl().GetItemCount() == 1)
	{
		AfxMessageBox( IDS_CANNOTDEL );
	}
	else
	{
		DeleteView(m_iHitTest);
	}
}

void CTabbedViewView::OnTabSave()
{
//	TRACE0("CTabbedViewView::OnTabSave()\n");
	GetView(m_iHitTest)->SendMessage(WM_COMMAND, ID_FILE_SAVE);
}

void CTabbedViewView::OnTabSaveAs()
{
//	TRACE0("CTabbedViewView::OnTabSaveAs()\n");
	GetView(m_iHitTest)->SendMessage(WM_COMMAND, ID_FILE_SAVE_AS);
}

void CTabbedViewView::OnTabPrint()
{
//	TRACE0("CTabbedViewView::OnTabPrint()\n");
	GetView(m_iHitTest)->SendMessage(WM_COMMAND, ID_FILE_PRINT);
}

void CTabbedViewView::OnTabPrintPreview()
{
//	TRACE0("CTabbedViewView::OnTabPrintPreview()\n");
	GetView(m_iHitTest)->SendMessage(WM_COMMAND, ID_FILE_PRINT_PREVIEW);
}

void CTabbedViewView::OnTimer(UINT_PTR nIDEvent) 
{
    if (m_nIDEvent == nIDEvent)
    {
        CPoint point;
        ::GetCursorPos(&point);
        ScreenToClient(&point);

        if (m_point == point)
        {
            CTabCtrl& tabCtrl = GetTabCtrl();

            CRect rcItem;
            int iItem;
			for (iItem = 0; iItem < tabCtrl.GetItemCount(); ++iItem )
            {
                tabCtrl.GetItemRect(iItem, &rcItem);

                if (rcItem.PtInRect(m_point) && tabCtrl.GetCurSel() != iItem)
                {
                    SetActiveView(iItem);
                    break;
                }
            }
        }
        
        KillTimer(m_nIDEvent);
    }
    else
    {
        CXTTabView::OnTimer(nIDEvent);
    }
}

void CTabbedViewView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CXTTabView::OnMouseMove(nFlags, point);

    m_point = point;
    SetTimer(m_nIDEvent, 2500, NULL);    
}

void CTabbedViewView::UpdateTabBorders()
{
	BOOL bIsOfficeTheme = XTThemeManager()->GetTheme() != xtThemeDefault;

	DWORD dwAdd    = bIsOfficeTheme ? 0 : WS_EX_CLIENTEDGE;
	DWORD dwRemove = bIsOfficeTheme ? WS_EX_CLIENTEDGE : 0;

	if (::IsWindow(m_editTab.m_hWnd)) {
		m_editTab.ModifyStyleEx(dwRemove, dwAdd);
	}
	if (::IsWindow(m_treeTabFile.m_hWnd)) {
		m_treeTabFile.ModifyStyleEx(dwRemove, dwAdd);
	}
	if (::IsWindow(m_treeTabClass.m_hWnd)) {
		m_treeTabClass.ModifyStyleEx(dwRemove, dwAdd);
	}
	if (::IsWindow(m_treeTabResource.m_hWnd)) {
		m_treeTabResource.ModifyStyleEx(dwRemove, dwAdd);
	}

	CRect r;
	GetWindowRect(&r);

	SetWindowPos(NULL, 0,0,r.Width()+1,r.Height(),
		SWP_FRAMECHANGED|SWP_NOMOVE);
	
	SetWindowPos(NULL, 0,0,r.Width(),r.Height(),
		SWP_FRAMECHANGED|SWP_NOMOVE);
}

void CTabbedViewView::OnCloseTab()
{
	if (GetTabCtrl().GetItemCount() == 1)
	{
		AfxMessageBox( IDS_CANNOTDEL );
	}
	else
	{
		DeleteView(GetTabCtrl().GetCurSel());
	}
}

DROPEFFECT CTabbedViewView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
    ::GetCursorPos(&point);
    ScreenToClient(&point);

	CTabCtrl& tabCtrl = GetTabCtrl();

	CRect rcItem;
	for (int iItem = 0; iItem < tabCtrl.GetItemCount(); ++iItem )
    {
		tabCtrl.GetItemRect(iItem, &rcItem);
		if (rcItem.PtInRect(point) && tabCtrl.GetCurSel() != iItem)
        {
			SetActiveView(iItem);
			break;
		}
	}

    return CXTTabView::OnDragOver(pDataObject, dwKeyState, point);
}

void CTabbedViewView::OnDropFiles(HDROP hDropInfo) 
{
    CPoint point;
    ::GetCursorPos(&point);
    ScreenToClient(&point);

	CTabCtrl& tabCtrl = GetTabCtrl();

	CRect rcItem;
	for (int iItem = 0; iItem < tabCtrl.GetItemCount(); ++iItem )
    {
		tabCtrl.GetItemRect(iItem, &rcItem);
		if (rcItem.PtInRect(point))
        {
			SetActiveView(iItem);
            CWnd* pView = GetView(iItem);
            if (pView && ::IsWindow(pView->m_hWnd))
			    pView->PostMessage(WM_DROPFILES, (WPARAM)hDropInfo, 0L);
			break;
		}
	}

	CXTTabView::OnDropFiles(hDropInfo);
}
