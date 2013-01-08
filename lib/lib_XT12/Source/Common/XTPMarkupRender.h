// XTPMarkupRender.h: API interface for the markup.
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

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTPMARKUPRENDER_H__)
#define __XTPMARKUPRENDER_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXTPMarkupContext;
class CXTPMarkupUIElement;


_XTP_EXT_CLASS CXTPMarkupContext* AFX_CDECL XTPMarkupCreateContext(HWND hWnd = NULL);
_XTP_EXT_CLASS void AFX_CDECL XTPMarkupReleaseContext(CXTPMarkupContext*& pContext);
_XTP_EXT_CLASS CXTPMarkupUIElement* AFX_CDECL XTPMarkupParseText(CXTPMarkupContext* pContext, LPCTSTR lpszMarkup);
_XTP_EXT_CLASS void AFX_CDECL XTPMarkupReleaseElement(CXTPMarkupUIElement*& pElement);
_XTP_EXT_CLASS CSize AFX_CDECL XTPMarkupMeasureElement(CXTPMarkupUIElement* pElement, int cxAvail = INT_MAX, int cyAvail = INT_MAX);
_XTP_EXT_CLASS void AFX_CDECL XTPMarkupRenderElement(CXTPMarkupUIElement* pElement, HDC hDC, LPCRECT rc);
_XTP_EXT_CLASS void AFX_CDECL XTPMarkupSetDefaultFont(CXTPMarkupContext* pContext, HFONT hFont, COLORREF clrText);
_XTP_EXT_CLASS BOOL AFX_CDECL XTPMarkupRelayMessage(CXTPMarkupUIElement* pElement, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
_XTP_EXT_CLASS CXTPMarkupContext* AFX_CDECL XTPMarkupElementContext(CXTPMarkupUIElement* pElement);


#ifndef _XTP_INCLUDE_MARKUP

AFX_INLINE CXTPMarkupContext* XTPMarkupCreateContext(HWND /*hWnd*/) {
	return NULL;
}
AFX_INLINE void XTPMarkupReleaseContext(CXTPMarkupContext*& /*pContext*/) {
}
AFX_INLINE void XTPMarkupReleaseElement(CXTPMarkupUIElement*& /*pElement*/) {
}
AFX_INLINE CXTPMarkupUIElement* XTPMarkupParseText(CXTPMarkupContext* /*pContext*/, LPCTSTR /*lpszMarkup*/) {
	return NULL;
}
AFX_INLINE CXTPMarkupContext* XTPMarkupElementContext(CXTPMarkupUIElement* /*pElement*/) {
	return NULL;
}
AFX_INLINE CSize AFX_CDECL XTPMarkupMeasureElement(CXTPMarkupUIElement* /*pElement*/, int /*cxAvail = INT_MAX*/, int /*cyAvail = INT_MAX*/) {
	return CSize(0, 0);
}
AFX_INLINE void XTPMarkupRenderElement(CXTPMarkupUIElement* /*pElement*/, HDC /*hDC*/, LPCRECT /*lpRect*/) {
}
AFX_INLINE void XTPMarkupSetDefaultFont(CXTPMarkupContext* /*pContext*/, HFONT /*hFont*/, COLORREF /*clrText*/) {
}
AFX_INLINE BOOL XTPMarkupRelayMessage(CXTPMarkupUIElement* /*pElement*/, UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, LRESULT* /*pResult*/) {
	return FALSE;
}

#endif // _XTP_INCLUDE_MARKUP


#endif // !defined(__XTPMARKUPRENDER_H__)
