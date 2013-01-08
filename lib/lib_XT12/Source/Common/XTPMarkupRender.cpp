// XTPMarkupRender.cpp: implementation.
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

#ifdef _XTP_INCLUDE_MARKUP

#include "Markup/XTPMarkupContext.h"
#include "Markup/XTPMarkupUIElement.h"
#include "Markup/XTPMarkupDrawingContext.h"

#include "XTPMarkupRender.h"


CXTPMarkupContext* AFX_CDECL XTPMarkupCreateContext(HWND hWnd /*= NULL*/)
{
	CXTPMarkupContext* pContext = new CXTPMarkupContext();
	pContext->m_hContextWnd = hWnd;
	return pContext;
}

void AFX_CDECL XTPMarkupReleaseContext(CXTPMarkupContext*& pContext)
{
	if (pContext)
	{
		pContext->Release();
		pContext = NULL;
	}
}

void AFX_CDECL XTPMarkupReleaseElement(CXTPMarkupUIElement*& pElement)
{
	if (pElement)
	{
		pElement->Release();
		pElement = NULL;
	}
}

CXTPMarkupUIElement* AFX_CDECL XTPMarkupParseText(CXTPMarkupContext* pContext, LPCTSTR lpszMarkup)
{
	if (!pContext)
		return NULL;

	return pContext->Parse(lpszMarkup);
}

CXTPMarkupContext* AFX_CDECL XTPMarkupElementContext(CXTPMarkupUIElement* pElement) {
	return pElement ? pElement->GetMarkupContext() : NULL;
}

CSize AFX_CDECL XTPMarkupMeasureElement(CXTPMarkupUIElement* pElement, int cxAvail /*= INT_MAX*/, int cyAvail /*= INT_MAX*/)
{
	if (!pElement)
		return CSize(0, 0);

	CXTPMarkupDrawingContext dc;
	pElement->Measure(&dc, CSize(cxAvail, cyAvail));

	return pElement->GetDesiredSize();
}

void AFX_CDECL XTPMarkupRenderElement(CXTPMarkupUIElement* pElement, HDC hDC, LPCRECT lpRect)
{
	if (!pElement)
		return;

	if (!hDC || !lpRect)
		return;

	CRect rc(lpRect);

	CXTPMarkupDrawingContext dc(hDC);
	pElement->Arrange(rc);
	pElement->Render(&dc);
}

void AFX_CDECL XTPMarkupSetDefaultFont(CXTPMarkupContext* pContext, HFONT hFont, COLORREF clrText)
{
	if (!pContext)
		return;

	if (hFont)
	{
		pContext->SetDefaultFont(hFont);
	}

	if (clrText != (COLORREF)-1)
	{
		pContext->SetDefaultTextColor(clrText);
	}
}

BOOL AFX_CDECL XTPMarkupRelayMessage(CXTPMarkupUIElement* pElement, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (pElement && pElement->GetMarkupContext())
		return pElement->GetMarkupContext()->OnWndMsg(pElement, message, wParam, lParam, pResult);
	return FALSE;
}

#endif
