// PaneToolbars.cpp : implementation file
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
#include "CommandBarsDesigner.h"
#include "PaneToolbars.h"
#include "DialogNewToolbar.h"
#include "PropertyItemFlags.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



class CFloatingPopupBar : public CXTPToolBar
{
	DECLARE_XTP_COMMANDBAR(CFloatingPopupBar)
public:
	CFloatingPopupBar()
	{
		m_bBuiltIn = FALSE;
		m_barType = xtpBarTypePopup;
		SetWidth(0);
	}

};
IMPLEMENT_XTP_COMMANDBAR(CFloatingPopupBar, CXTPToolBar);



LRESULT CPaneToolbars::CToolbarsTree::WindowProc(UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_NCPAINT:
		{
			CTreeCtrl::WindowProc(message, wParam, lParam);

			CRect rc;
			GetWindowRect(&rc);
			CWindowDC dc(this);
			rc.OffsetRect(-rc.TopLeft());
			COLORREF clr = GetStaticFrameColor();
			dc.Draw3dRect(rc, clr, clr);
			return TRUE;
		}
	}
	return CTreeCtrl::WindowProc(message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CPaneToolbars

CPaneToolbars::CPaneToolbars()
{
	m_bLockSelected = FALSE;
}

CPaneToolbars::~CPaneToolbars()
{
}


BEGIN_MESSAGE_MAP(CPaneToolbars, CWnd)
	//{{AFX_MSG_MAP(CPaneToolbars)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_PANETOOLBARS_ADD, OnPanetoolbarsAdd)
	ON_COMMAND(ID_PANETOOLBARS_ADDMENU, OnPanetoolbarsAddMenu)
	ON_UPDATE_COMMAND_UI(ID_PANETOOLBARS_ADD, OnUpdatePanetoolbarsAdd)
	ON_UPDATE_COMMAND_UI(ID_PANETOOLBARS_DELETE, OnUpdatePanetoolbarsDelete)
	ON_COMMAND(ID_PANETOOLBARS_DELETE, OnPanetoolbarsDelete)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED, AFX_IDW_PANE_FIRST, OnTreeSelChanged)
	ON_NOTIFY(NM_SETFOCUS, AFX_IDW_PANE_FIRST, OnTreeSetFocus)

END_MESSAGE_MAP()

int CPaneToolbars::BuildToolbarsTree(HTREEITEM hItem, CXTPCommandBar* pCommandBar, BOOL bCheck)
{
	BOOL bToolbar = pCommandBar->GetType() != xtpBarTypePopup;
	int nImageIndex = bToolbar? 0: 1;
	HTREEITEM hItemChild = 0;

	int nTotalCount = 1;

	CString strTitle = pCommandBar->GetTitle();
	if (strTitle.IsEmpty()) strTitle = _T("[Untitled]");

	if (bCheck)
	{
		hItemChild = (HTREEITEM)pCommandBar->GetCommandBarData();

		TVITEM item;
		item.hItem = hItemChild;
		item.mask = TVIF_PARAM;

		if (hItemChild != 0 && m_wndTreeCtrl.SendMessage(TVM_GETITEM, 0, (LPARAM)&item) &&
			(DWORD_PTR)item.lParam == (DWORD_PTR)pCommandBar)
		{
			if (m_wndTreeCtrl.GetItemText(hItemChild) != strTitle)
			{
				m_wndTreeCtrl.SetItemText(hItemChild, strTitle);

			}

		} else
			return 0;

	} else
	{
		hItemChild = m_wndTreeCtrl.InsertItem(strTitle, nImageIndex, nImageIndex, hItem);
		m_wndTreeCtrl.SetItemData(hItemChild, (DWORD_PTR)pCommandBar);
		pCommandBar->SetCommandBarData((DWORD_PTR)hItemChild);

	}

	for (int i = 0; i < pCommandBar->GetControlCount(); i++)
	{
		CXTPControl* pControl = pCommandBar->GetControl(i);
		CXTPCommandBar* pPopupBar = pControl->GetCommandBar();

		if (pControl == NULL || pControl->GetID() == XTP_ID_TOOLBAR_EXPAND || pPopupBar == NULL)
			continue;

		int nCount = BuildToolbarsTree(hItemChild, pPopupBar, bCheck);
		if (bCheck && nCount == 0)
			return 0;

		nTotalCount += nCount;

	}

	if (!bCheck) m_wndTreeCtrl.Expand (hItemChild, TVE_EXPAND);

	return nTotalCount;
}

void CPaneToolbars::Refresh()
{

	if (!AfxGetMainWnd())
		return;

	if (!m_wndTreeCtrl.GetSafeHwnd())
		return;

	CXTPCommandBars* pCommandBars = ((CMainFrame*)AfxGetMainWnd())->GetActiveCommandBars();

	m_pActiveCommandBars = pCommandBars;

	if (!pCommandBars || pCommandBars->GetCount() == 0)
	{
		m_bLockSelected = TRUE;
		m_wndTreeCtrl.DeleteAllItems();
		m_bLockSelected = FALSE;
		return;
	}


	int nTotalCount = 0, i;

	for (i = 0; i < pCommandBars->GetCount(); i++)
	{
		CXTPToolBar* pCommandBar = pCommandBars->GetAt(i);

		if (!pCommandBar->IsBuiltIn())
			continue;

		int nCount = BuildToolbarsTree(TVI_ROOT, pCommandBar, TRUE);
		if (nCount == 0)
		{
			nTotalCount = 0;
			break;
		}
		nTotalCount += nCount;
	}

	for (i = 0; i < pCommandBars->GetContextMenus()->GetCount(); i++)
	{
		CXTPCommandBar* pCommandBar = pCommandBars->GetContextMenus()->GetAt(i);

		int nCount = BuildToolbarsTree(TVI_ROOT, pCommandBar, TRUE);
		if (nCount == 0)
		{
			nTotalCount = 0;
			break;
		}
		nTotalCount += nCount;
	}




	if (nTotalCount != (int)m_wndTreeCtrl.GetCount())
	{
		nTotalCount = 0;
	}

	if (nTotalCount == 0)
	{
		m_wndTreeCtrl.LockWindowUpdate();
		m_bLockSelected = TRUE;

		m_wndTreeCtrl.DeleteAllItems();

		for (i = 0; i < pCommandBars->GetCount(); i++)
		{
			CXTPToolBar* pCommandBar = pCommandBars->GetAt(i);
			if (!pCommandBar->IsBuiltIn())
				continue;

			BuildToolbarsTree(TVI_ROOT, pCommandBar, FALSE);
		}

		for (i = 0; i < pCommandBars->GetContextMenus()->GetCount(); i++)
		{
			CXTPCommandBar* pCommandBar = pCommandBars->GetContextMenus()->GetAt(i);
			
			 BuildToolbarsTree(TVI_ROOT, pCommandBar, FALSE);
		}

		m_wndTreeCtrl.UnlockWindowUpdate();


		((CMainFrame*)AfxGetMainWnd())->m_pActivePane = NULL;
		((CMainFrame*)AfxGetMainWnd())->RefreshPanes();
		m_bLockSelected = FALSE;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CPaneToolbars message handlers

int CPaneToolbars::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	XTPImageManager()->SetMaskColor(RGB(0, 0xFF, 0));
	VERIFY(m_wndToolBar.CreateToolBar(WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this));
	VERIFY(m_wndToolBar.LoadToolBar(IDR_PANE_TOOLBARS));

	m_ilTreeIcons.Create(16, 16, ILC_MASK|ILC_COLOR24, 0, 1);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_PANE_TOOLBARS_ICONS);

	m_ilTreeIcons.Add(&bmp, RGB(0, 255, 0));


	if (!m_wndTreeCtrl.Create(WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_VISIBLE|TVS_HASLINES|
		TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	m_wndTreeCtrl.ModifyStyleEx(0, WS_EX_STATICEDGE);

	m_wndTreeCtrl.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);


	Refresh();


	return 0;
}

void CPaneToolbars::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CSize sz(0);
	if (m_wndToolBar.GetSafeHwnd())
	{
		sz = m_wndToolBar.CalcDockingLayout(cx, /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);

		m_wndToolBar.MoveWindow(0, 0, cx, sz.cy);
		m_wndToolBar.Invalidate(FALSE);
	}
	if (m_wndTreeCtrl.GetSafeHwnd())
	{
		m_wndTreeCtrl.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	}

}

void CPaneToolbars::OnSetFocus(CWnd*)
{
	m_wndTreeCtrl.SetFocus();
}

void CPaneToolbars::OnPanetoolbarsAdd()
{
	CDialogNewToolbar dt(TRUE);

	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
	if (!pFrame)
		return;

	if (dt.DoModal() == IDOK)
	{
		CXTPToolBar* pCommandBar = (CXTPToolBar*)pFrame->GetCommandBars()->Add(dt.m_strCaption, xtpBarTop);


		pCommandBar->SetBarID(pFrame->ResourceManager()->GetStringID(dt.m_strId));

		Refresh();
	
		HTREEITEM hItem = (HTREEITEM)pCommandBar->GetCommandBarData();
		m_wndTreeCtrl.SelectItem(hItem);
	}
}

void CPaneToolbars::ShowContextMenu(HTREEITEM hItem)
{
	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
	if (!pFrame)
		return;
	
	
	CXTPCommandBars* pCommandBars = pFrame->GetCommandBars();

	CXTPCommandBar* pSelectedBar = (CXTPCommandBar*)m_wndTreeCtrl.GetItemData(hItem);

	pFrame->CommitContextMenu();

	if (!pSelectedBar->IsPopupBar() || !((CXTPPopupBar*)pSelectedBar)->IsContextMenu())
		return;

	CXTPPopupBar* pPopupBar = (CXTPPopupBar*)pSelectedBar;
	
	CXTPToolBar* pContextMenu = (CXTPToolBar*)pCommandBars->Add(pPopupBar->GetTitle(), xtpBarTop, RUNTIME_CLASS(CFloatingPopupBar));
	if (!pContextMenu)
	{
		TRACE0("Failed to create toolbar\n");
		return;
	}
	
	CXTPControls* pControls = pPopupBar->GetControls()->Duplicate();
	pContextMenu->SetControls(pControls);
	
	
	pContextMenu->SetBarID(pPopupBar->GetBarID());
	pContextMenu->SetCustomizeDialogPresent(FALSE);
	
	pContextMenu->SetPosition(xtpBarFloating);
	pContextMenu->EnableDocking(xtpFlagFloating);
	
	pContextMenu->OnRecalcLayout();
	
	CXTPWindowRect rcContext(pContextMenu);
	CXTPWindowRect rcParent(pFrame);
	CPoint pt = pFrame->m_ptContextMenu;
	if (pt == CPoint(0, 0))
		pt = CPoint(rcParent.right, rcParent.top);

	pContextMenu->MoveWindow(pt.x, pt.y, rcContext.Width(), rcContext.Height());

	pContextMenu->SetCommandBarData((DWORD_PTR)pPopupBar);
	pContextMenu->OnUpdateCmdUI();
	
	pFrame->m_pContextMenu = pContextMenu;
}

void CPaneToolbars::OnPanetoolbarsAddMenu()
{	
	CDialogNewToolbar dt(FALSE);

	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
	if (!pFrame)
		return;

	if (dt.DoModal() == IDOK)
	{
		pFrame->CommitContextMenu();
		
		CXTPCommandBars* pCommandBars = pFrame->GetCommandBars();

		CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(pCommandBars);
		pPopupBar->SetTitle(dt.m_strCaption);
		pPopupBar->SetBarID(pFrame->ResourceManager()->GetStringID(dt.m_strId));

		pFrame->GetCommandBars()->GetContextMenus()->Add(pPopupBar);
		Refresh();

		HTREEITEM hItem = (HTREEITEM)pPopupBar->GetCommandBarData();
		m_wndTreeCtrl.SelectItem(hItem);

		//ShowContextMenu(hItem);
	}
}

void CPaneToolbars::OnUpdatePanetoolbarsAdd(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pActiveCommandBars != NULL);

}

void CPaneToolbars::RefreshItem(HTREEITEM hItem)
{
	((CMainFrame*)AfxGetMainWnd())->m_pActivePane = this;
	((CMainFrame*)AfxGetMainWnd())->RefreshPanes();
}

void CPaneToolbars::OnTreeSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMTREEVIEW* pNMTreeView = (NMTREEVIEW *)pNMHDR;

	if (m_bLockSelected)
		return;

	RefreshItem(pNMTreeView->itemNew.hItem);
	
	ShowContextMenu(m_wndTreeCtrl.GetSelectedItem());

	
	*pResult = 0;
}

void CPaneToolbars::OnTreeSetFocus(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
	HTREEITEM hItem = m_wndTreeCtrl.GetSelectedItem();
	if (hItem) RefreshItem(hItem);
}

void CPaneToolbars::OnUpdatePanetoolbarsDelete(CCmdUI* pCmdUI)
{
	HTREEITEM hItem = m_wndTreeCtrl.GetSelectedItem();

	if (hItem)
	{
		CXTPCommandBar* pCommandBar = (CXTPCommandBar*)m_wndTreeCtrl.GetItemData(hItem);

		pCmdUI->Enable(((pCommandBar->GetType() == xtpBarTypeNormal) && (pCommandBar->GetPosition() != xtpBarPopup))
		|| (pCommandBar->IsPopupBar() && ((CXTPPopupBar*)pCommandBar)->IsContextMenu()));
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CPaneToolbars::OnPanetoolbarsDelete()
{
	HTREEITEM hItem = m_wndTreeCtrl.GetSelectedItem();

	if (hItem)
	{
		CXTPCommandBar* pCommandBar = (CXTPCommandBar*)m_wndTreeCtrl.GetItemData(hItem);

		if (pCommandBar->IsPopupBar() && ((CXTPPopupBar*)pCommandBar)->IsContextMenu())
		{
			CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
			if (!pFrame)
				return;

			pFrame->CommitContextMenu();
			
			((CMainFrame*)AfxGetMainWnd())->m_pActivePane = NULL;
			m_pActiveCommandBars->SetDragControl(NULL);

			pCommandBar->GetCommandBars()->GetContextMenus()->Remove(pCommandBar);

			Refresh();
		}
		else if ((pCommandBar->GetType() == xtpBarTypeNormal) && (pCommandBar->GetPosition() != xtpBarPopup))
		{

			((CMainFrame*)AfxGetMainWnd())->m_pActivePane = NULL;
			m_pActiveCommandBars->SetDragControl(NULL);

			pCommandBar->GetCommandBars()->Remove((CXTPToolBar*)pCommandBar);

			Refresh();
		}

	}
}


void CPaneToolbars::FillConstraintsToolbarsID(CXTPPropertyGridItem* pItem)
{
	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
	CXTPCommandBars* pCommandBars = GetMainFrame()->GetActiveCommandBars();

	ASSERT(pCommandBars);

	for (int i = 0; i < pCommandBars->GetCount(); i++)
	{
		CXTPCommandBar* pCommandBar = pCommandBars->GetAt(i);

		if (pCommandBar->GetType() == xtpBarTypeNormal)
		{
			pItem->GetConstraints()->AddConstraint(pFrame->ResourceManager()->GetStringID(pCommandBar->GetBarID()));
		}
	}
}

CObject* CPaneToolbars::RefreshPropertyGrid(CXTPPropertyGrid* pPropertyGrid) 
{
	LPCTSTR lpStyles[] = {_T("xtpButtonAutomatic"), _T("xtpButtonCaption"), _T("xtpButtonIcon"), _T("xtpButtonIconAndCaption"), _T("xtpButtonIconAndCaptionBelow"), _T("xtpButtonCaptionAndDescription") };

	HTREEITEM hItem = m_wndTreeCtrl.GetSelectedItem();

	if (!hItem)
		return NULL;

	CXTPCommandBar* pCommandBar = (CXTPCommandBar*)m_wndTreeCtrl.GetItemData(hItem);
	if (!pCommandBar)
		return NULL;

	CXTPToolBar* pToolBar = DYNAMIC_DOWNCAST(CXTPToolBar, pCommandBar);
	CXTPPopupBar* pPopupBar = DYNAMIC_DOWNCAST(CXTPPopupBar, pCommandBar);

	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();

	if (!pFrame)
		return NULL;


	CXTPPropertyGridItem* pCategoryAppearance = pPropertyGrid->AddCategory(ID_GRID_CATEGORY_APPEARANCE);
	CXTPPropertyGridItem* pCategoryBehavior = pPropertyGrid->AddCategory(ID_GRID_CATEGORY_BEHAVIOR);


	pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_COMMANDBAR_TITLE, pCommandBar->GetTitle()));

	CString strID = pFrame->ResourceManager()->GetStringID(pCommandBar->GetBarID());
	CXTPPropertyGridItem* pItemCommandBarId = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_COMMANDBAR_ID, strID));
	pItemCommandBarId->SetReadOnly(TRUE);

	CXTPPropertyGridItem* pItemCommandBarVisible = pCategoryBehavior->AddChildItem(
		new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_VISIBLE, pToolBar? pToolBar->IsVisible(): TRUE));
	if (!pCommandBar->IsKindOf(RUNTIME_CLASS(CXTPToolBar))) pItemCommandBarVisible->SetReadOnly(TRUE);

	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_CUSTOMIZABLE, pCommandBar->IsCustomizable()));

	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_ANIMATION, pCommandBar->IsAnimationEnabled()));

	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_SHOWGRIPPER, pCommandBar->GetShowGripper()));
		
	{
		CXTPPropertyGridItem* pItemCommandBarStyle = pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemEnum(ID_GRID_ITEM_COMMANDBAR_DEFAULTBUTTONSTYLE, pCommandBar->GetDefaultButtonStyle()));
		CXTPPropertyGridItemConstraints* pConstraints = pItemCommandBarStyle->GetConstraints();
		for (int i = 0; i < _countof(lpStyles); i++)
			pConstraints->AddConstraint(lpStyles[i], i);
	}

	if (pToolBar)
	{
		pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_CLOSEABLE, pToolBar->IsCloseable()));
		pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_CONTEXTMENUPRESENT, pToolBar->IsContextMenuPresent()));
		pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_CUSTOMIZEDIALOGPRESENT, pToolBar->IsCustomizeDialogPresent()));	

	}


	if (pCommandBar->IsKindOf(RUNTIME_CLASS(CXTPPopupBar)))
	{
		CString strCaption;
		UINT nID;
		int nWidth;
		BOOL bTearOff = pPopupBar->IsTearOffPopup(strCaption, nID, nWidth);

		CXTPPropertyGridItem* pItemCommandBarTearOff = pCategoryBehavior->AddChildItem(
			new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_TEAROFF, bTearOff));

		if (bTearOff)
		{
			CString strID = pFrame->ResourceManager()->GetStringID(nID);


			pItemCommandBarTearOff->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_COMMANDBAR_TEAROFF_CAPTION, strCaption));
			CXTPPropertyGridItem* pItemCommandBarTearOffId = pItemCommandBarTearOff->AddChildItem(
				new CXTPPropertyGridItem(ID_GRID_ITEM_COMMANDBAR_TEAROFF_ID, strID));
			pItemCommandBarTearOffId->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
			FillConstraintsToolbarsID(pItemCommandBarTearOffId);


			pItemCommandBarTearOff->AddChildItem(new CXTPPropertyGridItemNumber(ID_GRID_ITEM_COMMANDBAR_TEAROFF_WIDTH, nWidth));
			pItemCommandBarTearOff->Expand();
		}

		CXTPPropertyGridItem* pItemPopupToolBar = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_POPUPTOOLBAR, pCommandBar->GetType() !=xtpBarTypePopup));

		if (pCommandBar->GetType() != xtpBarTypePopup)
		{
			pItemPopupToolBar->AddChildItem(new CXTPPropertyGridItemNumber(ID_GRID_ITEM_COMMANDBAR_WIDTH, pCommandBar->GetWidth()));
		}

		if (pCommandBar->GetType() == xtpBarTypePopup)
		{
			pCategoryAppearance->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_DOUBLEGRIPPER, ((CXTPPopupBar*)pCommandBar)->IsDoubleGripper()));
		}
	}

///if (pCommandBar->GetType() != xtpBarTypePopup)
	{
		CSize sz = pCommandBar->GetIconSize();
		pCategoryAppearance->AddChildItem(new CXTPPropertyGridItemSize(ID_GRID_ITEM_COMMANDBAR_ICON_SIZE, sz));
	}

	if (pCommandBar->GetType() != xtpBarTypePopup)
	{
		CSize sz = pCommandBar->GetButtonSize();
		pCategoryAppearance->AddChildItem(new CXTPPropertyGridItemSize(ID_GRID_ITEM_COMMANDBAR_BUTTON_SIZE, sz));
	}

	if (pCommandBar->GetType() != xtpBarTypePopup)
	{
		pCategoryAppearance->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_COMMANDBAR_TEXTBELOWICONS, pCommandBar->IsTextBelowIcons()));
	}



	if (pCommandBar->IsKindOf(RUNTIME_CLASS(CXTPToolBar)))
	{
		pCategoryBehavior->AddChildItem(new CPropertyGridItemDockingFlags(ID_GRID_ITEM_COMMANDBAR_FLAGS, pCommandBar->GetFlags()));
		pCategoryBehavior->AddChildItem(new CPropertyGridItemStretchFlags(ID_GRID_ITEM_COMMANDBAR_STRETCH, pCommandBar->GetFlags()));
	}

	pCategoryAppearance->Expand();
	pCategoryBehavior->Expand();


	return pCommandBar;
}

BOOL CPaneToolbars::OnPropertyGridValueChanged(CObject* pActiveObject, CXTPPropertyGridItem* pItem)
{
	CXTPCommandBar* pCommandBar = DYNAMIC_DOWNCAST(CXTPCommandBar, pActiveObject);
	if (!pCommandBar)
		return FALSE;
	
	switch (pItem->GetID())
	{
	case ID_GRID_ITEM_COMMANDBAR_TITLE:
		pCommandBar->SetTitle(pItem->GetValue());
		Refresh();
		return TRUE;
	case  ID_GRID_ITEM_COMMANDBAR_ICON_SIZE:
		{
			CSize sz = ((CXTPPropertyGridItemSize*)pItem)->GetSize();
			pCommandBar->SetIconSize(sz);
			pCommandBar->DelayLayout();
			GetMainFrame()->RefreshPanes(TRUE);
			
		}
		return TRUE;
	case  ID_GRID_ITEM_COMMANDBAR_BUTTON_SIZE:
		{
			CSize sz = ((CXTPPropertyGridItemSize*)pItem)->GetSize();
			pCommandBar->SetButtonSize(sz);
			pCommandBar->DelayLayout();
			GetMainFrame()->RefreshPanes(TRUE);
			
		}
		return TRUE;
		
	case ID_GRID_ITEM_COMMANDBAR_TEXTBELOWICONS:
		pCommandBar->ShowTextBelowIcons(GetBoolValue(pItem));
		return TRUE;
		
	case ID_GRID_ITEM_COMMANDBAR_VISIBLE:
		pCommandBar->SetVisible(GetBoolValue(pItem));
		Refresh();
		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_CUSTOMIZABLE:
		pCommandBar->EnableCustomization(GetBoolValue(pItem));
		Refresh();
		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_ANIMATION:
		pCommandBar->EnableAnimation(GetBoolValue(pItem));
		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_SHOWGRIPPER:
		pCommandBar->SetShowGripper(GetBoolValue(pItem));
		pCommandBar->OnRecalcLayout();
		return TRUE;
		
	case ID_GRID_ITEM_COMMANDBAR_DEFAULTBUTTONSTYLE:
		pCommandBar->SetDefaultButtonStyle((XTPButtonStyle)GetEnumValue(pItem));
		pCommandBar->OnRecalcLayout();
		return TRUE;
		
	case ID_GRID_ITEM_COMMANDBAR_CLOSEABLE:
		((CXTPToolBar*)pCommandBar)->SetCloseable(GetBoolValue(pItem));
		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_CONTEXTMENUPRESENT:
		((CXTPToolBar*)pCommandBar)->SetContextMenuPresent(GetBoolValue(pItem));
		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_CUSTOMIZEDIALOGPRESENT:
		((CXTPToolBar*)pCommandBar)->SetCustomizeDialogPresent(GetBoolValue(pItem));
		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_STRETCH:
	case ID_GRID_ITEM_COMMANDBAR_FLAGS:
		{
			DWORD dwMask = pItem->GetID() == ID_GRID_ITEM_COMMANDBAR_STRETCH? xtpFlagHideWrap|xtpFlagStretched: xtpFlagAlignAny|xtpFlagFloating;
			DWORD dwFalgs = (pCommandBar->GetFlags() & ~dwMask) | GetFlagsValue(pItem);
			
			((CXTPToolBar*)pCommandBar)->EnableDocking(dwFalgs);
			pCommandBar->DelayLayout();
			Refresh();
		}
		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_POPUPTOOLBAR:
		((CXTPPopupBar*)pCommandBar)->SetPopupToolBar(GetBoolValue(pItem));
		pCommandBar->DelayLayout();
		
		Refresh();
		((CMainFrame*)AfxGetMainWnd())->m_paneProperties.Refresh(this);

		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_WIDTH:
		pCommandBar->SetWidth(GetNumberValue(pItem));
		pCommandBar->DelayLayout();
		Refresh();
		return TRUE;
	case  ID_GRID_ITEM_COMMANDBAR_DOUBLEGRIPPER:
		{
			CXTPPopupBar* pPopupBar = DYNAMIC_DOWNCAST(CXTPPopupBar, pCommandBar);
			ASSERT(pPopupBar);
			pPopupBar->SetDoubleGripper(GetBoolValue(pItem));
			break;
		}
		
	case ID_GRID_ITEM_COMMANDBAR_TEAROFF:
		{
			CXTPPopupBar* pPopupBar = DYNAMIC_DOWNCAST(CXTPPopupBar, pCommandBar);
			ASSERT(pPopupBar);
			
			if (GetBoolValue(pItem))
			{
				CString strCaption;
				UINT nID;
				int nWidth;
				pPopupBar->IsTearOffPopup(strCaption, nID, nWidth);
				if (nID == 0)
				{
					CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
					ASSERT(pFrame);
					
					nID = pFrame->ResourceManager()->GetStringID(_T("IDR_UNTITLED"));
					
					pPopupBar->SetTearOffPopup(_T("Untitled"), nID);
				}
				else  pPopupBar->SetTearOffPopup(strCaption, nID, nWidth);
			}
			else
			{
				pPopupBar->SetTearOffPopup(_T(""), 0);
			}
			((CMainFrame*)AfxGetMainWnd())->m_paneProperties.Refresh(this);
		}
		return TRUE;
		
	case ID_GRID_ITEM_COMMANDBAR_TEAROFF_ID:
		{
			CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
			ASSERT(pFrame);
			
			CXTPPopupBar* pPopupBar = DYNAMIC_DOWNCAST(CXTPPopupBar, pCommandBar);
			ASSERT(pPopupBar);
			
			CString strCaption;
			UINT nID;
			int nWidth;
			pPopupBar->IsTearOffPopup(strCaption, nID, nWidth);
			pPopupBar->SetTearOffPopup(strCaption, pFrame->ResourceManager()->GetStringID(pItem->GetValue()), nWidth);
		}
		
		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_TEAROFF_CAPTION:
		{
			CXTPPopupBar* pPopupBar = DYNAMIC_DOWNCAST(CXTPPopupBar, pCommandBar);
			ASSERT(pPopupBar);
			
			CString strCaption;
			UINT nID;
			int nWidth;
			pPopupBar->IsTearOffPopup(strCaption, nID, nWidth);
			pPopupBar->SetTearOffPopup(pItem->GetValue(), nID, nWidth);
		}
		
		return TRUE;
	case ID_GRID_ITEM_COMMANDBAR_TEAROFF_WIDTH:
		{
			CXTPPopupBar* pPopupBar = DYNAMIC_DOWNCAST(CXTPPopupBar, pCommandBar);
			ASSERT(pPopupBar);
			
			CString strCaption;
			UINT nID;
			int nWidth;
			pPopupBar->IsTearOffPopup(strCaption, nID, nWidth);
			pPopupBar->SetTearOffPopup(strCaption, nID, GetNumberValue(pItem));
		}
		
		return TRUE;
	}

	return FALSE;
}
