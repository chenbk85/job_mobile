// XTColorPopup.cpp : implementation file
//
// This file is a part of the XTREME CONTROLS MFC class library.
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

#include "Common/XTPDrawHelpers.h"
#include "Common/XTPWinThemeWrapper.h"
#include "Common/XTPColorManager.h"
#include "Common/XTPSystemHelpers.h"
#include "Common/XTPHookManager.h"

#include "Resource.h"
#include "XTDefines.h"
#include "XTColorSelectorCtrl.h"
#include "XTColorPopup.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXTColorPopup

CXTColorPopup::CXTColorPopup(BOOL bAutoDelete/*= FALSE*/, LPARAM callerParam /*= 0*/)
: m_callerParam(callerParam)
{
	m_bAutoDelete = bAutoDelete;
	m_bDisplayShadow = TRUE;

	m_pShadowManager = new CXTPShadowManager();
}

CXTColorPopup::~CXTColorPopup()
{
	CMDTARGET_RELEASE(m_pShadowManager);
}

BEGIN_MESSAGE_MAP(CXTColorPopup, CXTColorSelectorCtrl)
	//{{AFX_MSG_MAP(CXTColorPopup)
	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXTColorPopup message handlers

BOOL CXTColorPopup::Create(CRect& rect, CWnd* pParentWnd, DWORD dwPopup, COLORREF clrColor,
	COLORREF clrDefault/*= CLR_DEFAULT*/)
{
	BOOL bOfficeTheme = GetTheme()->GetTheme() != xtThemeDefault;

	if (bOfficeTheme)
	{
		SetBorders(4, 4, 6, 6);
	}
	else
	{
		SetBorders(4, 4, 10, 10);
	}

	m_rcExclude = rect;

	return CXTColorSelectorCtrl::Create(rect, pParentWnd, dwPopup | WS_POPUP, clrColor, clrDefault);
}

void CXTColorPopup::PostNcDestroy()
{
	CXTPMouseMonitor::SetupHook(NULL);

	if (m_bAutoDelete)
	{
		delete this;
	}
}

void CXTColorPopup::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);

	// If we lose activation (other than to the color dialog) post
	// a close message...

	if (nState == WA_INACTIVE && !IsColorDlgVisible())
	{
		PostMessage(WM_CLOSE);
	}
}

void CXTColorPopup::OnDestroy()
{
	CWnd::OnDestroy();

	// Inform the parent that we are closing up.
	m_pParentWnd->SendMessage(CPN_XT_CLOSEUP,
		(WPARAM)m_clrColor, m_callerParam);

}


int CXTColorPopup::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTColorSelectorCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bOfficeTheme = GetTheme()->GetTheme() != xtThemeDefault;

	if (bOfficeTheme)
	{
		ModifyStyle(WS_DLGFRAME | WS_THICKFRAME | WS_BORDER, 0, SWP_FRAMECHANGED);
		ModifyStyleEx(WS_EX_STATICEDGE | WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME, 0, SWP_FRAMECHANGED);
	}
	else
	{
		ModifyStyle(0, WS_DLGFRAME, SWP_FRAMECHANGED);
	}

	CRect rcWork = XTPMultiMonitor()->GetWorkArea(m_rcWnd);

	CSize size = m_rcWnd.Size();

	// move right
	if (m_rcWnd.left < rcWork.left)
	{
		m_rcWnd.left = rcWork.left;
		m_rcWnd.right = m_rcWnd.left + size.cx;
	}

	// move left
	else if (m_rcWnd.right > rcWork.right)
	{
		m_rcWnd.right = rcWork.right;
		m_rcWnd.left = m_rcWnd.right - size.cx;
	}

	// move up
	if (m_rcWnd.bottom > rcWork.bottom)
	{
		if (m_rcExclude.IsRectEmpty())
			m_rcWnd.bottom = rcWork.top;
		else
			m_rcWnd.bottom = m_rcExclude.top;

		m_rcWnd.top = m_rcWnd.bottom - size.cy;
	}

	SetFocus();

	SetWindowLongPtr(m_hWnd, GWLP_HWNDPARENT, 0);
	ModifyStyle(WS_CHILD, WS_POPUP);
	SetWindowLongPtr(m_hWnd, GWLP_HWNDPARENT, (LONG_PTR)m_pParentWnd->m_hWnd);

	SetWindowPos(&CWnd::wndTop, m_rcWnd.left, m_rcWnd.top, m_rcWnd.Width(), m_rcWnd.Height(), SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOOWNERZORDER);

	if (bOfficeTheme && m_bDisplayShadow)
	{
		m_pShadowManager->SetShadowOptions(xtpShadowOfficeAlpha);
		m_pShadowManager->SetShadow(this);
	}

	CXTPMouseMonitor::SetupHook(this);

	m_pParentWnd->SendMessage(CPN_XT_DROPDOWN,
		(WPARAM)m_clrColor, m_callerParam);

	return 0;
}

// Adds a window to send color picker notifications to.
void CXTColorPopup::AddListener(HWND hwndListener)
{
	m_listeners.Add(hwndListener);
}

void CXTColorPopup::EndSelection(int nCurSel)
{
	CXTPMouseMonitor::SetupHook(NULL);

	OnEndSelection(nCurSel, m_callerParam);

	PostMessage(WM_CLOSE);

}

void CXTColorPopup::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	if (!m_pColorDlg)
	{
		EndSelection(-1);
	}
}

void CXTColorPopup::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rc;
	GetClientRect(&rc);

	if (!rc.PtInRect(point) && !IsColorDlgVisible())
	{
		EndSelection(-1);
		return;
	}
	CXTColorSelectorCtrl::OnLButtonDown(nFlags, point);
}

void CXTColorPopup::OnNcPaint()
{
	BOOL bOfficeTheme = GetTheme()->GetTheme() != xtThemeDefault;

	if (bOfficeTheme)
	{
		CWindowDC dc(this);
		const COLORREF clrFrame = GetXtremeColor(XPCOLOR_MENUBAR_BORDER);
		CRect rc;
		GetWindowRect(&rc);
		int cx = rc.Width(); // for right border is exclusive
		int cy = rc.Height() ; // see above
		dc.Draw3dRect(0, 0, cx, cy, clrFrame, clrFrame);

	}
	else
	{
		Default();
	}
}

void CXTColorPopup::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	BOOL bOfficeTheme = GetTheme()->GetTheme() != xtThemeDefault;

	if (bOfficeTheme)
	{
		// adjust non-client area for border space
		lpncsp->rgrc[0].left += 1;
		lpncsp->rgrc[0].top += 1;
		lpncsp->rgrc[0].right += -1;
		lpncsp->rgrc[0].bottom += -1;
	}
	else
	{
		CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
	}
}
