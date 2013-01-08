// XTPMarkupDrawingContext.cpp: implementation of the CXTPMarkupDrawingContext class.
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
#include <math.h>

#include "Common/XTPImageManager.h"
#include "Common/XTPvc80Helpers.h"

#include "XTPMarkupDrawingContext.h"
#include "XTPMarkupContext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXTPMarkupDrawingContext::CXTPMarkupDrawingContext(HDC hDC)
{
	m_hDC = hDC;
	m_bDeleteDC = FALSE;

	Init();
}

CXTPMarkupDrawingContext::CXTPMarkupDrawingContext()
{
	m_hDC = CreateCompatibleDC(0);
	m_bDeleteDC = TRUE;

	Init();
}


void CXTPMarkupDrawingContext::Init()
{
	m_hAttribDC = m_hDC;
	m_pSelectedFont = NULL;
	m_hOldFont = NULL;

	::GetWindowExtEx(m_hDC, &m_sizeWinExt);
	::GetViewportExtEx(m_hDC, &m_sizeVpExt);
	::GetViewportOrgEx(m_hDC, &m_ptViewortOrg);

	m_rcClipBox.SetRectEmpty();
	::GetClipBox(m_hDC, &m_rcClipBox);

	::SetBkMode(m_hDC, TRANSPARENT);
}

CXTPMarkupDrawingContext::~CXTPMarkupDrawingContext()
{
	SetFont(NULL);

	if (m_bDeleteDC)
	{
		DeleteDC(m_hDC);
	}
}

POINT CXTPMarkupDrawingContext::TranslatePoint(const POINT& ptVisualOffset) const
{
	POINT pt;
	pt.x = MulDiv(ptVisualOffset.x, abs(m_sizeVpExt.cx), abs(m_sizeWinExt.cx));
	pt.y = MulDiv(ptVisualOffset.y, abs(m_sizeVpExt.cy), abs(m_sizeWinExt.cy));
	return pt;
}


HDC CXTPMarkupDrawingContext::Detach()
{
	SetFont(NULL);

	HDC hDC = m_hDC;
	m_hDC = NULL;
	return hDC;
}

void CXTPMarkupDrawingContext::SetViewportOrg(const POINT& ptViewortOrg)
{
	SetViewportOrgEx(m_hDC, ptViewortOrg.x, ptViewortOrg.y, NULL);
}

POINT CXTPMarkupDrawingContext::OffsetViewport(const POINT& ptVisualOffset)
{
	POINT ptViewortOrg = m_ptViewortOrg;

	POINT pt = TranslatePoint(ptVisualOffset);

	m_ptViewortOrg.x += pt.x;
	m_ptViewortOrg.y += pt.y;

	::SetViewportOrgEx(m_hDC, m_ptViewortOrg.x, m_ptViewortOrg.y, NULL);

	::GetClipBox(m_hDC, &m_rcClipBox);

	return ptViewortOrg;
}

void CXTPMarkupDrawingContext::SetViewport(const POINT& ptViewortOrg)
{
	m_ptViewortOrg = ptViewortOrg;

	::SetViewportOrgEx(m_hDC, m_ptViewortOrg.x, m_ptViewortOrg.y, NULL);

	::GetClipBox(m_hDC, &m_rcClipBox);
}


HRGN CXTPMarkupDrawingContext::SaveClipRegion()
{
	HRGN hrgnClip = ::CreateRectRgn(0, 0, 0, 0);

	if (hrgnClip != NULL)
	{
		if (GetClipRgn(m_hDC, hrgnClip) != 1)
		{
			DeleteObject(hrgnClip);
			hrgnClip = (HRGN)-1;
		}
	}
	return hrgnClip;
}

void CXTPMarkupDrawingContext::IntersectClipRect(const RECT& rcLayoutClip)
{
	::IntersectClipRect(m_hDC, rcLayoutClip.left, rcLayoutClip.top, rcLayoutClip.right, rcLayoutClip.bottom);
	::GetClipBox(m_hDC, m_rcClipBox);
}

void CXTPMarkupDrawingContext::RestoreClipRegion(HRGN hrgnClip)
{
	if (hrgnClip != NULL)
	{
		if (hrgnClip == (HRGN)-1)
		{
			ExtSelectClipRgn(m_hDC, NULL, RGN_COPY);
		}
		else
		{
			ExtSelectClipRgn(m_hDC, hrgnClip, RGN_COPY);
			DeleteObject(hrgnClip);
		}

		::GetClipBox(m_hDC, m_rcClipBox);
	}
}


void CXTPMarkupDrawingContext::FillSolidRect(CRect rc, COLORREF clr)
{
	CXTPMarkupSolidColorBrush brush(clr);
	brush.FillRect(this, rc);

}
void CXTPMarkupDrawingContext::DrawRectangle(CXTPMarkupBrush* pBrush, CRect rc)
{
	pBrush->FillRect(this, rc);
}

void CXTPMarkupDrawingContext::DrawFrame(CXTPMarkupBrush* pBrush, CRect rc)
{
	pBrush->FillRect(this, CRect(rc.left, rc.top, rc.right, rc.top + 1));
	pBrush->FillRect(this, CRect(rc.left, rc.top, rc.left + 1, rc.bottom));
	pBrush->FillRect(this, CRect(rc.left, rc.bottom - 1, rc.right, rc.bottom));
	pBrush->FillRect(this, CRect(rc.right - 1, rc.top, rc.right, rc.bottom));
}

void CXTPMarkupDrawingContext::DrawTextLine(LPCWSTR lpszText, UINT nCount, LPCRECT lpRect)
{
	::ExtTextOutW(m_hDC, lpRect->left, lpRect->top, 0, lpRect, lpszText, nCount, 0);
}

void CXTPMarkupDrawingContext::SetFont(CXTPMarkupFont* pFont)
{
	if (!m_hDC)
		return;

	if (m_pSelectedFont == pFont)
		return;

	if (pFont == NULL && m_hOldFont)
	{
		SelectFontObject(m_hOldFont);
		m_hOldFont = NULL;
	}
	else if (pFont != NULL && m_hOldFont == NULL)
	{
		m_hOldFont = SelectFontObject(pFont->m_hFont);
	}
	else if (pFont != NULL)
	{
		SelectFontObject(pFont->m_hFont);
	}

	MARKUP_RELEASE(m_pSelectedFont);
	m_pSelectedFont = pFont;
	MARKUP_ADDREF(m_pSelectedFont);
}

SIZE CXTPMarkupDrawingContext::GetTextExtent(LPCWSTR lpszText, int nCount) const
{
	SIZE sz;
	VERIFY(::GetTextExtentPoint32W(m_hAttribDC, lpszText, nCount, &sz));
	return sz;
}


HFONT CXTPMarkupDrawingContext::SelectFontObject(HFONT hFont)
{
	HFONT hOldObj = 0;

	if (m_hDC != m_hAttribDC)
		hOldObj = (HFONT)::SelectObject(m_hDC, hFont);

	if (m_hAttribDC != NULL)
		hOldObj = (HFONT)::SelectObject(m_hAttribDC, hFont);

	return hOldObj;
}

CXTPMarkupPrintingContext::CXTPMarkupPrintingContext(HDC hDC, HDC hAttribDC)
	: CXTPMarkupDrawingContext(hDC)
{
	m_hAttribDC = hAttribDC;
}

void CXTPMarkupPrintingContext::DrawTextLine(LPCWSTR lpszString, UINT nCount, LPCRECT lpRect)
{
	if (m_hAttribDC == m_hDC)
	{
		::ExtTextOutW(m_hDC, lpRect->left, lpRect->top, 0, lpRect, lpszString, nCount, 0);
		return;
	}

	LPINT lpDxWidths = NULL;

	ASSERT(m_hDC != NULL);
	ASSERT(m_hAttribDC != NULL);
	ASSERT(lpszString != NULL);
	ASSERT(lpDxWidths == NULL ||
			AfxIsValidAddress(lpDxWidths, sizeof(int) * nCount, FALSE));
	ASSERT(AfxIsValidAddress(lpszString, nCount, FALSE));

	int* pDeltas = NULL;
	LPWSTR pOutputString = NULL;
	int nRightFixup = 0;

	if (nCount == 0)    // Do nothing
		return;

	pDeltas = new int[nCount];
	pOutputString = new WCHAR[nCount];

	int x = lpRect->left;

	ComputeDeltas(x, (LPWSTR)lpszString, nCount, FALSE, 0, NULL, 0,
		pOutputString, pDeltas, nRightFixup);

	lpDxWidths = pDeltas;
	lpszString = pOutputString;

	::ExtTextOutW(m_hDC, x, lpRect->top, 0, lpRect, lpszString, nCount, lpDxWidths);

	delete[] pDeltas;
	delete[] pOutputString;
}

int CXTPMarkupPrintingContext::ComputeNextTab(int x, UINT nTabStops, LPINT lpnTabStops,
										int nTabOrigin, int nTabWidth) const
{
	x -= nTabOrigin;        // normalize position to tab origin
	for (UINT i = 0; i < nTabStops; i++, lpnTabStops++)
	{
		if (*lpnTabStops > x)
			return *lpnTabStops + nTabOrigin;
	}
	return (x / nTabWidth + 1) * nTabWidth + nTabOrigin;
}

CSize CXTPMarkupPrintingContext::ComputeDeltas(int& x, LPCWSTR lpszString, UINT &nCount,
	BOOL bTabbed, UINT nTabStops, LPINT lpnTabStops, int nTabOrigin,
	LPWSTR lpszOutputString, int* pnDxWidths, int& nRightFixup) const
{
	TEXTMETRIC tmAttrib;
	TEXTMETRIC tmScreen;
	::GetTextMetrics(m_hAttribDC, &tmAttrib);
	::GetTextMetrics(m_hDC, &tmScreen);

	CSize sizeExtent;
	::GetTextExtentPoint32A(m_hAttribDC, "A", 1, &sizeExtent);

	CPoint ptCurrent;
	UINT nAlignment = ::GetTextAlign(m_hAttribDC);
	BOOL bUpdateCP = (nAlignment & TA_UPDATECP) != 0;
	if (bUpdateCP)
	{
		::GetCurrentPositionEx(m_hDC, &ptCurrent);
		x = ptCurrent.x;
	}

	LPCWSTR lpszCurChar = lpszString;
	LPCWSTR lpszStartRun = lpszString;
	int* pnCurDelta = pnDxWidths;
	int nStartRunPos = x;
	int nCurrentPos = x;
	int nStartOffset = 0;

	int nTabWidth = 0;
	if (bTabbed)
	{
		if (nTabStops == 1)
		{
			nTabWidth = lpnTabStops[0];
		}
		else
		{
			// Get default size of a tab
			nTabWidth = LOWORD(::GetTabbedTextExtentA(m_hAttribDC,
				"\t", 1, 0, NULL));
		}
	}

	for (UINT i = 0; i < nCount; i++)
	{
		BOOL bSpace = ((_TUCHAR)*lpszCurChar == (_TUCHAR)tmAttrib.tmBreakChar);
		if (bSpace || (bTabbed && *lpszCurChar == '\t'))
		{
			// bSpace will be either TRUE (==1) or FALSE (==0).  For spaces
			// we want the space included in the GetTextExtent, for tabs we
			// do not want the tab included
			int nRunLength = (int)(lpszCurChar - lpszStartRun) + (bSpace ? 1 : 0);

			CSize sizeExtent2;
			::GetTextExtentPoint32W(m_hAttribDC, lpszStartRun, nRunLength,
				&sizeExtent2);
			int nNewPos = nStartRunPos + sizeExtent2.cx
				- tmAttrib.tmOverhang;

			// now, if this is a Tab (!bSpace), compute the next tab stop
			if (!bSpace)
			{
				nNewPos = ComputeNextTab(nNewPos, nTabStops, lpnTabStops,
								nTabOrigin, nTabWidth);
			}

			// Add this width to previous width
			if (pnCurDelta == pnDxWidths)
				nStartOffset += nNewPos - nCurrentPos;
			else
				*(pnCurDelta-1) += nNewPos - nCurrentPos;

			nCurrentPos = nNewPos;

			nStartRunPos = nCurrentPos;     // set start of run
			// *lpszCurChar must be SBC: tmBreakChar or '\t'
			lpszStartRun = lpszCurChar + 1;
		}
		else
		{
			// For the non-tabbed or non-tab-character case
			int cxScreen;
			if (_istlead(*lpszCurChar))
			{
				cxScreen = tmScreen.tmAveCharWidth;
				*pnCurDelta = tmAttrib.tmAveCharWidth;
			}
			else
			{
				::GetCharWidth(m_hDC, (_TUCHAR)*lpszCurChar,
					(_TUCHAR)*lpszCurChar, &cxScreen);
				if (!::GetCharWidth(m_hAttribDC, (_TUCHAR)*lpszCurChar,
					(_TUCHAR)*lpszCurChar, pnCurDelta))
				{
					// If printer driver fails the above call, use the average width
					*pnCurDelta = tmAttrib.tmAveCharWidth;
				}
			}
			*pnCurDelta -= tmAttrib.tmOverhang;
			cxScreen -= tmScreen.tmOverhang;
			nCurrentPos += *pnCurDelta;     // update current position

			// Center character in allotted space
			if (pnCurDelta != pnDxWidths)
			{
				int diff = (*pnCurDelta - cxScreen) / 2;
				*pnCurDelta -= diff;
				*(pnCurDelta - 1) += diff;
			}
			*lpszOutputString++ = *lpszCurChar;
			if (_istlead(*lpszCurChar))
			{
				*lpszOutputString++ = *(lpszCurChar+1); // copy trailing byte
				*(pnCurDelta + 1) = *pnCurDelta;        // double wide
				nCurrentPos += *pnCurDelta;
				pnCurDelta++;
				i++;
			}
			pnCurDelta++;
		}
		lpszCurChar++;
	}

	nAlignment &= TA_CENTER|TA_RIGHT;
	sizeExtent.cx = nCurrentPos - x;
	nRightFixup = 0;

	if (nAlignment == TA_LEFT)
		x += nStartOffset;      // Full left side adjustment
	else if (nAlignment == TA_CENTER)
		x += nStartOffset/2;    // Adjust Center by 1/2 left side adjustment
	else if (nAlignment == TA_RIGHT)
		nRightFixup = nStartOffset; // Right adjust needed later if TA_UPDATECP

	if (bUpdateCP)
		::MoveToEx(m_hDC, x, ptCurrent.y, NULL);

	nCount = (UINT)(pnCurDelta - pnDxWidths);   // number of characters output
	return sizeExtent;
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupBrush

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupBrush, CXTPMarkupObject);

void CXTPMarkupBrush::RegisterMarkupClass()
{

}


void CXTPMarkupBrush::FillRect(CXTPMarkupDrawingContext* /*pDC*/, CRect /*rc*/)
{

}

COLORREF CXTPMarkupBrush::GetHintColor() const
{
	return 0;
}

CXTPMarkupObject* CXTPMarkupBrush::ConvertFrom(CXTPMarkupObject* pObject) const
{
	if (IsStringObject(pObject))
	{
		COLORREF clr;
		if (CXTPMarkupColor::ConvertFromString(*((CXTPMarkupString*)pObject), clr))
		{
			return new CXTPMarkupSolidColorBrush(clr);
		}
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupSolidColorBrush

CXTPMarkupDependencyProperty* CXTPMarkupSolidColorBrush::m_pColorProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"SolidColorBrush", CXTPMarkupSolidColorBrush, CXTPMarkupBrush);

void CXTPMarkupSolidColorBrush::RegisterMarkupClass()
{
	m_pColorProperty = CXTPMarkupDependencyProperty::Register(L"Color", MARKUP_TYPE(CXTPMarkupColor), MARKUP_TYPE(CXTPMarkupSolidColorBrush));
}

CXTPMarkupSolidColorBrush::CXTPMarkupSolidColorBrush()
{
}

CXTPMarkupSolidColorBrush::CXTPMarkupSolidColorBrush(COLORREF clr)
{
	SetValue(m_pColorProperty, new CXTPMarkupColor(clr));
}

BOOL CXTPMarkupSolidColorBrush::IsEqual(const CXTPMarkupObject* pObject) const
{
	if (!pObject)
		return FALSE;

	if (pObject->GetType() != MARKUP_TYPE(CXTPMarkupSolidColorBrush))
		return FALSE;

	return GetHintColor() == ((CXTPMarkupSolidColorBrush*)pObject)->GetHintColor();

}

void CXTPMarkupSolidColorBrush::FillRect(CXTPMarkupDrawingContext* pDC, CRect rc)
{
	CXTPMarkupColor* pColor = MARKUP_STATICCAST(CXTPMarkupColor, GetValue(m_pColorProperty));

	if (pColor)
	{
		COLORREF clrOld = ::SetBkColor(pDC->GetSafeHdc(), *pColor);
		::ExtTextOut(pDC->GetSafeHdc(), 0, 0, ETO_OPAQUE, rc, NULL, 0, NULL);
		::SetBkColor(pDC->GetSafeHdc(), clrOld);
	}
}

COLORREF CXTPMarkupSolidColorBrush::GetHintColor() const
{
	CXTPMarkupColor* pColor = MARKUP_STATICCAST(CXTPMarkupColor, GetValue(m_pColorProperty));

	if (pColor)
	{
		return *pColor;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPoint

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupPoint, CXTPMarkupObject);

void CXTPMarkupPoint::RegisterMarkupClass()
{

}

CXTPMarkupPoint::CXTPMarkupPoint()
{
	x = 0;
	y = 0;
}

CXTPMarkupPoint::CXTPMarkupPoint(double x, double y)
{
	this->x = x;
	this->y = y;
}

CXTPMarkupPoint& CXTPMarkupPoint::operator=(const CXTPMarkupPoint& srcPoint)
{
	x = srcPoint.x;
	y = srcPoint.y;
	return *this;
}

CXTPMarkupObject* CXTPMarkupPoint::ConvertFrom(CXTPMarkupObject* pObject) const
{
	if (IsStringObject(pObject))
	{
		LPCWSTR lpszValue = *(CXTPMarkupString*)pObject;

		float x = 0 , y = 0;
		if (WSCANF_S(lpszValue, L"%f,%f", &x, &y) != 2)
			return FALSE;

		return new CXTPMarkupPoint(x, y);
	}
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupGradientStop
CXTPMarkupDependencyProperty* CXTPMarkupGradientStop::m_pColorProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupGradientStop::m_pOffsetProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"GradientStop", CXTPMarkupGradientStop, CXTPMarkupObject);

void CXTPMarkupGradientStop::RegisterMarkupClass()
{
	m_pColorProperty = CXTPMarkupDependencyProperty::Register(L"Color", MARKUP_TYPE(CXTPMarkupColor), MARKUP_TYPE(CXTPMarkupGradientStop));
	m_pOffsetProperty = CXTPMarkupDependencyProperty::Register(L"Offset", MARKUP_TYPE(CXTPMarkupDouble), MARKUP_TYPE(CXTPMarkupGradientStop));
}

CXTPMarkupGradientStop::CXTPMarkupGradientStop()
{

}

CXTPMarkupGradientStop::CXTPMarkupGradientStop(COLORREF clr, double dOffset)
{
	SetValue(m_pColorProperty, new CXTPMarkupColor(clr));
	SetValue(m_pOffsetProperty, new CXTPMarkupDouble(dOffset));
}

COLORREF CXTPMarkupGradientStop::GetColor() const
{
	CXTPMarkupColor* pColor = MARKUP_STATICCAST(CXTPMarkupColor, GetValue(m_pColorProperty));
	return pColor != NULL ? (COLORREF)*pColor : 0;
}

double CXTPMarkupGradientStop::GetOffset() const
{
	CXTPMarkupDouble* pOffset = MARKUP_STATICCAST(CXTPMarkupDouble, GetValue(m_pOffsetProperty));
	return pOffset != NULL ? (double)*pOffset : 0.0;

}



CXTPMarkupGradientStops::CXTPMarkupGradientStops()
{
	m_pElementType = MARKUP_TYPE(CXTPMarkupGradientStop);
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupLinearGradientBrush

CXTPMarkupDependencyProperty* CXTPMarkupLinearGradientBrush::m_pStartPointProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupLinearGradientBrush::m_pEndPointProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"LinearGradientBrush", CXTPMarkupLinearGradientBrush, CXTPMarkupBrush);

void CXTPMarkupLinearGradientBrush::RegisterMarkupClass()
{
	m_pStartPointProperty = CXTPMarkupDependencyProperty::Register(L"StartPoint", MARKUP_TYPE(CXTPMarkupPoint), MARKUP_TYPE(CXTPMarkupLinearGradientBrush));
	m_pEndPointProperty = CXTPMarkupDependencyProperty::Register(L"EndPoint", MARKUP_TYPE(CXTPMarkupPoint), MARKUP_TYPE(CXTPMarkupLinearGradientBrush));
}


CXTPMarkupLinearGradientBrush::CXTPMarkupLinearGradientBrush()
{
	m_pGradientStops = new CXTPMarkupGradientStops();
}

CXTPMarkupLinearGradientBrush::CXTPMarkupLinearGradientBrush(CXTPMarkupGradientStops* pGradientStops)
{
	m_pGradientStops = pGradientStops;
}

CXTPMarkupLinearGradientBrush::~CXTPMarkupLinearGradientBrush()
{
	MARKUP_RELEASE(m_pGradientStops);
}

void CXTPMarkupLinearGradientBrush::SetStartPoint(double x, double y)
{
	SetValue(m_pStartPointProperty, new CXTPMarkupPoint(x, y));
}

void CXTPMarkupLinearGradientBrush::SetEndPoint(double x, double y)
{
	SetValue(m_pEndPointProperty, new CXTPMarkupPoint(x, y));
}

void CXTPMarkupLinearGradientBrush::SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent)
{
	m_pGradientStops->SetContentObject(pBuilder, pContent);
}

int _cdecl CXTPMarkupLinearGradientBrush::_GradientStopCompare(const void *arg1, const void *arg2)
{
	double& dOffset1 = ((GRADIENTSTOP*)arg1)->dOffset;
	double& dOffset2 = ((GRADIENTSTOP*)arg2)->dOffset;

	return dOffset1 > dOffset2 ? 1 : dOffset1 < dOffset2 ? -1 : ((GRADIENTSTOP*)arg1)->nIndex - ((GRADIENTSTOP*)arg2)->nIndex;
};

void CXTPMarkupLinearGradientBrush::FillRect(CXTPMarkupDrawingContext* pDC , CRect rc)
{
	HDC hDC = pDC->GetSafeHdc();
	int cx = rc.Width();
	int cy = rc.Height();

	if (m_pGradientStops->GetCount() == 0)
		return;

	if (cx <= 0 || cy <= 0)
		return;

	if (m_pGradientStops->GetCount() == 1)
	{
		COLORREF clr = m_pGradientStops->GetItem(0)->GetColor();
		COLORREF clrOld = ::SetBkColor(hDC, clr);
		::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, rc, NULL, 0, NULL);
		::SetBkColor(hDC, clrOld);
		return;
	}

	CXTPMarkupPoint ptStartPoint(0, 0);
	if (GetValue(m_pStartPointProperty)) ptStartPoint =  *MARKUP_STATICCAST(CXTPMarkupPoint, GetValue(m_pStartPointProperty));

	CXTPMarkupPoint ptEndPoint(1, 1);
	if (GetValue(m_pEndPointProperty)) ptEndPoint =  *MARKUP_STATICCAST(CXTPMarkupPoint, GetValue(m_pEndPointProperty));

	ptStartPoint.x *= cx;
	ptStartPoint.y *= cy;

	ptEndPoint.x *= cx;
	ptEndPoint.y *= cy;

	BOOL bHorizontal = ptStartPoint.y == ptEndPoint.y;
	BOOL bVertical = ptStartPoint.x == ptEndPoint.x;

	if (bHorizontal && bVertical)
		return;

	CRect rcClipBox = pDC->GetClipBox();

	if (pDC->IsPrinting())
		rcClipBox.InflateRect(1, 1);

	rcClipBox.OffsetRect(-rc.TopLeft());

	if (!rcClipBox.IntersectRect(&rcClipBox, CRect(0, 0, cx, cy)))
		return;

	LPDWORD lpBits;
	HBITMAP hBitmap = CXTPImageManager::Create32BPPDIBSection(0, cx, cy, (LPBYTE*)&lpBits);


	int nCount = m_pGradientStops->GetCount();
	GRADIENTSTOP* pStops = new GRADIENTSTOP[nCount];

	for (int i = 0; i < nCount; i++)
	{
		CXTPMarkupGradientStop* pItem = m_pGradientStops->GetItem(i);

		COLORREF clr = pItem->GetColor();
		pStops[i].clr.rgbRed = GetRValue(clr);
		pStops[i].clr.rgbGreen = GetGValue(clr);
		pStops[i].clr.rgbBlue = GetBValue(clr);
		pStops[i].clr.rgbReserved = 0;
		pStops[i].dOffset = pItem->GetOffset();
		pStops[i].nIndex = i;
	}

	GRADIENTSTOP *pStopFirst = pStops, *pStopLast = pStops + nCount - 1, *pStop;

	qsort(pStopFirst, nCount, sizeof(GRADIENTSTOP), _GradientStopCompare);

	for (pStop = pStopFirst + 1; pStop <= pStopLast; pStop++)
	{
		pStop->dDiff = pStop->dOffset - (pStop - 1)->dOffset;
	}

	CXTPMarkupPoint ptCenter((double)cx / 2, (double)cy /2);

	double len = sqrt(pow(ptStartPoint.x - ptEndPoint.x, 2) + pow(ptStartPoint.y - ptEndPoint.y, 2));
	double cosA = (ptEndPoint.x - ptStartPoint.x) / len;
	double sinA = (ptEndPoint.y - ptStartPoint.y) / len;

	double dDiff = - ptCenter.x * cosA  - ptCenter.y * sinA + ptCenter.x;
	double dStart = ptStartPoint.x * cosA + ptStartPoint.y * sinA + dDiff;
	double dEnd = ptEndPoint.x * cosA + ptEndPoint.y * sinA + dDiff;

	LPDWORD lpPixel = lpBits;

	double fDist = 1.0 / (dEnd - dStart);
	cosA = cosA * fDist;
	sinA = sinA * fDist;
	dDiff = (dDiff - dStart) * fDist;

	if (bVertical)
	{
		lpPixel += (cy - rcClipBox.bottom) * cx;

		for (int y = (cy - rcClipBox.bottom); y < (cy - rcClipBox.top); y++)
		{
			double fAmount = double(cy - y) * sinA + dDiff;

			DWORD dwPixel = 0;

			if (fAmount <= pStopFirst->dOffset)
			{
				dwPixel =  *((LPDWORD)&pStopFirst->clr);
			}
			else if(fAmount >= pStopLast->dOffset)
			{
				dwPixel =  *((LPDWORD)&pStopLast->clr);
			}
			else for (pStop = pStopFirst + 1; pStop <= pStopLast; pStop++)
			{
				if (fAmount < pStop->dOffset && pStop->dDiff != 0)
				{
					const RGBQUAD& clrFrom = (pStop - 1)->clr;
					const RGBQUAD& clrTo = pStop->clr;

					double fAmountA = (pStop->dOffset - fAmount) / pStop->dDiff;
					double fAmountB = (1.0 - fAmountA);

					((LPBYTE)&dwPixel)[2] = (BYTE)(clrFrom.rgbRed * fAmountA + clrTo.rgbRed * fAmountB);
					((LPBYTE)&dwPixel)[1] = (BYTE)(clrFrom.rgbGreen * fAmountA + clrTo.rgbGreen * fAmountB);
					((LPBYTE)&dwPixel)[0] = (BYTE)(clrFrom.rgbBlue * fAmountA + clrTo.rgbBlue * fAmountB);
					break;
				}
			}

			for (int x = 0; x < cx; x++)
			{
				*lpPixel = dwPixel;
				lpPixel++;
			}
		}

	}
	else if (bHorizontal)
	{
		dDiff += double(cy) * sinA;

		lpPixel += rcClipBox.left;

		for (int x = rcClipBox.left; x < rcClipBox.right; x++)
		{
			double fAmount = (double)x * cosA + dDiff;

			if (fAmount <= pStopFirst->dOffset)
			{
				*lpPixel =  *((LPDWORD)&pStopFirst->clr);
			}
			else if(fAmount >= pStopLast->dOffset)
			{
				*lpPixel =  *((LPDWORD)&pStopLast->clr);
			}
			else for (pStop = pStopFirst + 1; pStop <= pStopLast; pStop++)
			{
				if (fAmount < pStop->dOffset && pStop->dDiff != 0)
				{
					const RGBQUAD& clrFrom = (pStop - 1)->clr;
					const RGBQUAD& clrTo = pStop->clr;

					double fAmountA = (pStop->dOffset - fAmount) / pStop->dDiff;
					double fAmountB = (1.0 - fAmountA);

					((LPBYTE)lpPixel)[2] = (BYTE)(clrFrom.rgbRed * fAmountA + clrTo.rgbRed * fAmountB);
					((LPBYTE)lpPixel)[1] = (BYTE)(clrFrom.rgbGreen * fAmountA + clrTo.rgbGreen * fAmountB);
					((LPBYTE)lpPixel)[0] = (BYTE)(clrFrom.rgbBlue * fAmountA + clrTo.rgbBlue * fAmountB);
					break;
				}
			}

			lpPixel++;
		}

		lpPixel += (cx - rcClipBox.right);

		int y = max(1, cy - rcClipBox.bottom);

		if (y > 1)
		{
			lpPixel += cx * (cy - rcClipBox.bottom - 1);
		}

		for (; y < (cy - rcClipBox.top); y++)
		{
			memcpy(lpPixel, lpBits, sizeof(DWORD) * cx);
			lpPixel += cx;
		}
	}
	else
	{
		lpPixel += (cy - rcClipBox.bottom) * cx;

		for (int y = (cy - rcClipBox.bottom); y < (cy - rcClipBox.top); y++)
		{
			lpPixel += rcClipBox.left;

			for (int x = rcClipBox.left; x < rcClipBox.right; x++)
			{
				double fAmount = (double)x * cosA + double(cy - y) * sinA + dDiff;

				if (fAmount <= pStopFirst->dOffset)
				{
					*lpPixel =  *((LPDWORD)&pStopFirst->clr);
				}
				else if(fAmount >= pStopLast->dOffset)
				{
					*lpPixel =  *((LPDWORD)&pStopLast->clr);
				}
				else for (pStop = pStopFirst + 1; pStop <= pStopLast; pStop++)
				{
					if (fAmount < pStop->dOffset && pStop->dDiff != 0)
					{
						const RGBQUAD& clrFrom = (pStop - 1)->clr;
						const RGBQUAD& clrTo = pStop->clr;

						double fAmountA = (pStop->dOffset - fAmount) / pStop->dDiff;
						double fAmountB = (1.0 - fAmountA);

						((LPBYTE)lpPixel)[2] = (BYTE)(clrFrom.rgbRed * fAmountA + clrTo.rgbRed * fAmountB);
						((LPBYTE)lpPixel)[1] = (BYTE)(clrFrom.rgbGreen * fAmountA + clrTo.rgbGreen * fAmountB);
						((LPBYTE)lpPixel)[0] = (BYTE)(clrFrom.rgbBlue * fAmountA + clrTo.rgbBlue * fAmountB);
						break;
					}
				}

				lpPixel++;
			}

			lpPixel += (cx - rcClipBox.right);
		}
	}

	HDC hBitmapDC = ::CreateCompatibleDC(hDC);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hBitmapDC, hBitmap);

	BitBlt(hDC, rc.left + rcClipBox.left, rc.top + rcClipBox.top, rcClipBox.Width(), rcClipBox.Height(), hBitmapDC, rcClipBox.left, rcClipBox.top, SRCCOPY);

	SelectObject(hBitmapDC, hOldBitmap);
	DeleteDC(hBitmapDC);

	DeleteObject(hBitmap);
	delete[] pStops;
}
