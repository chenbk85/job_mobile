// PaneAccelerators.cpp : implementation file
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
#include "commandbarsdesigner.h"
#include "PaneAccelerators.h"

#include "DialogAccelProperties.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneAccelerators

LRESULT CPaneAccelerators::CAcceleratorsList::WindowProc(UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_NCPAINT:
		{
			CListCtrl::WindowProc(message, wParam, lParam);

			CRect rc;
			GetWindowRect(&rc);
			CWindowDC dc(this);
			rc.OffsetRect(-rc.TopLeft());
			COLORREF clr = GetStaticFrameColor();
			dc.Draw3dRect(rc, clr, clr);
			return TRUE;
		}
	}
	return CListCtrl::WindowProc(message, wParam, lParam);
}

CPaneAccelerators::CPaneAccelerators()
{
	m_pActiveFrame = 0;
	m_pAccelTable = NULL;
}

CPaneAccelerators::~CPaneAccelerators()
{
}


BEGIN_MESSAGE_MAP(CPaneAccelerators, CWnd)
	//{{AFX_MSG_MAP(CPaneAccelerators)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_PANEACELLERATORS_NEW, OnPaneacelleratorsNew)
	ON_UPDATE_COMMAND_UI(ID_PANEACELLERATORS_NEW, OnUpdatePaneacelleratorsNew)
	ON_COMMAND(ID_PANEACELLERATORS_DELETE, OnPaneacelleratorsDelete)
	ON_UPDATE_COMMAND_UI(ID_PANEACELLERATORS_DELETE, OnUpdatePaneacelleratorsDelete)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, AFX_IDW_PANE_FIRST, OnDblClick)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPaneAccelerators message handlers

int CPaneAccelerators::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_wndToolBar.CreateToolBar(WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this));
	VERIFY(m_wndToolBar.LoadToolBar(IDR_PANE_ACCELERATORS));
	m_wndToolBar.GetControl(0)->SetStyle(xtpButtonIconAndCaption);
	m_wndToolBar.GetControl(1)->SetStyle(xtpButtonIconAndCaption);


	if (!m_wndListCtrl.CWnd::CreateEx(WS_EX_STATICEDGE, WC_LISTVIEW, NULL,
		WS_CHILD|WS_VISIBLE|LVS_REPORT|WS_VSCROLL|LVS_SINGLESEL|LVS_SHOWSELALWAYS,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create tree control.\n");
		return -1;
	}
	m_wndListCtrl.ModifyStyleEx(0, WS_EX_STATICEDGE);

	m_wndListCtrl.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 105);
	m_wndListCtrl.InsertColumn(1, _T("Key"), LVCFMT_LEFT, 84);

	ListView_SetExtendedListViewStyleEx(m_wndListCtrl.m_hWnd,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	return 0;
}

void CPaneAccelerators::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);


	int nTop = 0;

	if (m_wndToolBar.GetSafeHwnd())
	{
		CSize sz = m_wndToolBar.CalcDockingLayout(cx, /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);

		m_wndToolBar.MoveWindow(0, nTop, cx, sz.cy);
		m_wndToolBar.Invalidate(FALSE);
		nTop += sz.cy;
	}


	if (m_wndListCtrl.GetSafeHwnd())
	{
		m_wndListCtrl.MoveWindow(0, nTop, cx, cy - nTop);
	}

}

void CPaneAccelerators::RefreshAccels(CXTPShortcutManagerAccelTable* pAccelTable)
{
	CResourceManager* pResourceManager = ((CEmbeddedFrame*)m_pActiveFrame)->ResourceManager();

	m_pAccelTable = pAccelTable;

	m_wndListCtrl.DeleteAllItems();

	if (!pAccelTable)
		return;

	int nAccelSize = m_pAccelTable->GetCount();

	CString strFirst = _T("");

	for (int i = 0; i < nAccelSize; i ++)
	{
		CXTPShortcutManagerAccel* accel = m_pAccelTable->GetAt(i);
		CString strID = pResourceManager->GetStringID(accel->cmd);
		ASSERT(!strID.IsEmpty());

		CString strKey = GetMainFrame()->GetCommandBars()->GetShortcutManager()->Format(accel, NULL);

		int nIndex = m_wndListCtrl.InsertItem(m_wndListCtrl.GetItemCount(), strID, 0);
		m_wndListCtrl.SetItemText(nIndex, 1, strKey);
		m_wndListCtrl.SetItemData(nIndex, i);

	}

}

void CPaneAccelerators::Refresh(BOOL bForceAll /*= FALSE*/)
{
	if (bForceAll || (m_pActiveFrame != GetMainFrame()->GetActiveEmbeddedFrame()))
	{
		m_pActiveFrame = GetMainFrame()->GetActiveEmbeddedFrame();

		if (m_pActiveFrame)
		{
			CXTPShortcutManagerAccelTable* pAccel = GetActiveAccelTable();
			RefreshAccels(pAccel);
		}
		else
		{
			m_wndListCtrl.DeleteAllItems();
			m_pAccelTable = NULL;
		}
	}
}

BOOL CPaneAccelerators::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_CHAR || pMsg->message == WM_KEYUP)
	{
		if (pMsg->wParam == VK_INSERT) Insert();
		if (pMsg->wParam == VK_RETURN)
		{
			int nItem = m_wndListCtrl.GetNextItem(-1, LVNI_SELECTED);
			if (nItem != -1)
			{
				int nIndex = (int)m_wndListCtrl.GetItemData(nItem);
				Edit(nIndex);
			}
		}
		if (pMsg->wParam == VK_DELETE)
		{
			int nItem = m_wndListCtrl.GetNextItem(-1, LVNI_SELECTED);
			if (nItem != -1)
			{
				int nIndex = (int)m_wndListCtrl.GetItemData(nItem);
				Delete(nIndex);
			}
		}

		m_wndListCtrl.SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
		return TRUE;
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CPaneAccelerators::Edit(int nIndex)
{
	if (!m_pAccelTable)
		return;

	CResourceManager* pResourceManager = ((CEmbeddedFrame*)m_pActiveFrame)->ResourceManager();

	CXTPShortcutManagerAccel* accel = m_pAccelTable->GetAt(nIndex);

	CDialogAccelProperties ap;
	ap.m_strId = pResourceManager->GetStringID(accel->cmd);

	ap.m_lpAccel = accel;

	if (ap.DoModal() == IDOK)
	{
		*accel = *ap.m_wndAccel.GetAccel();
		accel->cmd = (WORD)pResourceManager->GetStringID(ap.m_strId);

		RefreshAccels(GetActiveAccelTable());
	}
}

CXTPShortcutManagerAccelTable* CPaneAccelerators::GetActiveAccelTable()
{
	ASSERT(m_pActiveFrame);
	return m_pActiveFrame->GetCommandBars()->GetShortcutManager()->GetDefaultAccelerator();
}

void CPaneAccelerators::Delete(int nIndex)
{
	if (!m_pAccelTable)
		return;

	if (nIndex < m_pAccelTable->GetCount())
	{
		m_pAccelTable->RemoveAt(nIndex);
	}

	RefreshAccels(GetActiveAccelTable());
}

void CPaneAccelerators::Insert()
{
	if (!m_pAccelTable)
		return;

	CResourceManager* pResourceManager = ((CEmbeddedFrame*)m_pActiveFrame)->ResourceManager();

	CDialogAccelProperties ap;
	if (ap.DoModal() == IDOK)
	{
		if (!m_pAccelTable)
			return;

		CXTPShortcutManagerAccel accel = *ap.m_wndAccel.GetAccel();
		accel.cmd = pResourceManager->GetStringID(ap.m_strId);

		m_pAccelTable->Add(accel);

		RefreshAccels(GetActiveAccelTable());
	}

}

void CPaneAccelerators::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMITEMACTIVATE * pNMItemActivate = (NMITEMACTIVATE  *)pNMHDR;

	if (!m_pActiveFrame)
		return;

	if (pNMItemActivate->iItem >= 0)
	{

		int nIndex = (int)m_wndListCtrl.GetItemData(pNMItemActivate->iItem);
		Edit(nIndex);
	}

	*pResult = 0;
}

void CPaneAccelerators::OnPaneacelleratorsNew()
{
	Insert();

}

void CPaneAccelerators::OnUpdatePaneacelleratorsNew(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pActiveFrame != NULL);
}

void CPaneAccelerators::OnPaneacelleratorsDelete()
{
	int nItem = m_wndListCtrl.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1)
	{
		int nIndex = (int)m_wndListCtrl.GetItemData(nItem);
		Delete(nIndex);
	}

}

void CPaneAccelerators::OnUpdatePaneacelleratorsDelete(CCmdUI* pCmdUI)
{
	int nItem = m_wndListCtrl.GetNextItem(-1, LVNI_SELECTED);
	pCmdUI->Enable(nItem != -1);

}
