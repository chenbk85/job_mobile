// XTPMiniToolBar.h : interface for the CXTPMiniToolBar class.
//
// This file is a part of the XTREME COMMANDBARS MFC class library.
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

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTPMINITOOLBAR_H__)
#define __XTPMINITOOLBAR_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPPopupBar.h"

/////////////////////////////////////////////////////////////////////////////
// CXTPMiniToolBar window
class _XTP_EXT_CLASS CXTPMiniToolBar : public CXTPPopupToolBar
{
	DECLARE_XTP_COMMANDBAR(CXTPMiniToolBar);

public:
	static CXTPMiniToolBar* AFX_CDECL CreateMiniToolBar(CXTPCommandBars* pCommandBars);

protected:
	CXTPMiniToolBar();
	virtual ~CXTPMiniToolBar();

public:
	BOOL TrackMiniBar(UINT nFlags, int x, int y);
	BOOL TrackPopupMenu(CXTPPopupBar* pPopupMenu, UINT nFlags, int x, int y);

	virtual BOOL OnHookKeyDown(UINT nChar, LPARAM lParam);

protected:
	void PumpMessage();
	void UpdateOpacity();
	BOOL CursorInWindow() const;



//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()

	//{{AFX_VIRTUAL(CXTPMiniToolBar)
	virtual void Animate();
	virtual BOOL SetTrackingMode(int bMode, BOOL bSelectFirst = TRUE, BOOL bKeyboard = FALSE);
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	virtual int OnHookMessage(HWND hWnd, UINT nMessage, WPARAM& wParam, LPARAM& lParam, LRESULT& lResult);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTPMiniToolBar)
	//}}AFX_MSG

//}}AFX_CODEJOCK_PRIVATE


protected:
	typedef BOOL(WINAPI* LPFNUPDATELAYEREDWINDOW) (HWND hwnd, HDC hdcDst, POINT *pptDst, SIZE *psize, HDC hdcSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
	typedef BOOL (WINAPI *PFNSETLAYEREDWINDOWATTRIBUTES) (HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);

	PFNSETLAYEREDWINDOWATTRIBUTES m_pfnSetLayeredWindowAttributes;    // point to Transparency proc in USER32.dll module
	LPFNUPDATELAYEREDWINDOW m_pfnUpdateLayeredWindow;

	BOOL m_bActivated;
	int m_nOpacity;
	BOOL m_bTracking;
	CXTPPopupBar* m_pContextMenu;
};

#endif // !defined(__XTPMINITOOLBAR_H__)
