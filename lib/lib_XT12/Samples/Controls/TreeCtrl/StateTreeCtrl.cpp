// StateTreeCtrl.cpp : implementation file
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
#include "treectrl.h"
#include "SelectTreeCtrl.h"
#include "StateTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStateTreeCtrl

CStateTreeCtrl::CStateTreeCtrl()
{
	m_hCursor = theApp.LoadCursor(IDC_CHECK);
	m_hCursorNone = theApp.LoadCursor(IDC_CHECK_NONE);
}

CStateTreeCtrl::~CStateTreeCtrl()
{
	if (m_hCursor != NULL) {
		::DestroyCursor(m_hCursor);
	}
	if (m_hCursorNone != NULL) {
		::DestroyCursor(m_hCursorNone);
	}
}

BEGIN_MESSAGE_MAP(CStateTreeCtrl, CSelectTreeCtrl)
	//{{AFX_MSG_MAP(CStateTreeCtrl)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStateTreeCtrl message handlers

void CStateTreeCtrl::PreSubclassWindow() 
{
	CSelectTreeCtrl::PreSubclassWindow();

	m_ilStateImages.Create(IDB_STATE_IMAGES, 13, 1, RGB(255,255,255));
	SetImageList(&m_ilStateImages, TVSIL_STATE);
}

HTREEITEM CStateTreeCtrl::InsertItemState(LPCTSTR lpszItem, int nImage, int nSelectedImage, int nState/*=STATE_DISABLED*/, HTREEITEM hParent/*=TVI_ROOT*/, HTREEITEM hInsertAfter/*=TVI_LAST*/)
{
	TV_INSERTSTRUCT tvis;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hInsertAfter;
	tvis.item.mask = TVIF_TEXT | TVIF_STATE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvis.item.stateMask = TVIS_STATEIMAGEMASK;
	tvis.item.state = INDEXTOSTATEIMAGEMASK(1);
	tvis.item.pszText = (TCHAR*)lpszItem;
	tvis.item.cchTextMax = (int)_tcslen(lpszItem);
	tvis.item.iImage = nImage;
	tvis.item.iSelectedImage = nSelectedImage;
	HTREEITEM hItem = CTreeCtrl::InsertItem(&tvis);

	SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

	return hItem;
}

int CStateTreeCtrl::GetItemCheck(HTREEITEM hItem) const
{
	return (hItem == NULL)? STATE_NONE: (GetItemState(hItem, TVIS_STATEIMAGEMASK)>>12);
}

BOOL CStateTreeCtrl::SetItemCheck(HTREEITEM hItem, int nState)
{
	return SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);
}

BOOL CStateTreeCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);
	
	UINT uFlags;
	HTREEITEM hItem = HitTest(point, &uFlags);
	if (hItem && TVHT_ONITEMSTATEICON == uFlags)
	{
		int iImage = GetItemCheck(hItem);

		if (iImage == STATE_DISABLED || iImage == STATE_NONE) {
			::SetCursor(m_hCursorNone);
		}
		else {
			::SetCursor(m_hCursor);
		}
		return TRUE;
	}
	return CSelectTreeCtrl::OnSetCursor(pWnd, nHitTest, message);
}

void CStateTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
    TVHITTESTINFO tvHitTest;
    tvHitTest.pt = point;

    HTREEITEM hItem = HitTest(&tvHitTest);
    if (hItem != NULL)
    {
		if (ToggleCheckState(hItem, tvHitTest.flags))
		{
			return;
		}
    }	
	
	CSelectTreeCtrl::OnLButtonDown(nFlags, point);
}

void CStateTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if (nChar == VK_SPACE) {
		ToggleCheckState(GetSelectedItem(), TVHT_ONITEMSTATEICON);
	}	
	CSelectTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CStateTreeCtrl::ToggleCheckState(HTREEITEM hItem, UINT uFlags)
{
	BOOL bOnStateIcon = ((uFlags & TVHT_ONITEMSTATEICON) == TVHT_ONITEMSTATEICON);

    if ((bOnStateIcon == FALSE) || (hItem == NULL)) {
		return FALSE;
    }

	int nState = GetItemCheck(hItem)+1;

	if (nState > STATE_INTERMEDIATE)
		nState = STATE_UNCHECKED;

	return SetItemCheck(hItem, nState);
}
