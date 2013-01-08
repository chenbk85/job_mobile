// XTPMarkupDrawingContext.h: interface for the CXTPMarkupDrawingContext class.
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

#if !defined(__XTPMARKUPDRAWINGCONTEXT_H__)
#define __XTPMARKUPDRAWINGCONTEXT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupObject.h"

class CXTPMarkupContext;

class _XTP_EXT_CLASS CXTPMarkupBrush : public CXTPMarkupObject
{
	DECLARE_MARKUPCLASS(CXTPMarkupBrush);

public:
	CXTPMarkupObject* ConvertFrom(CXTPMarkupObject* pObject) const;

public:
	virtual void FillRect(CXTPMarkupDrawingContext* pDC, CRect rc);
	virtual COLORREF GetHintColor() const;
};

class _XTP_EXT_CLASS CXTPMarkupSolidColorBrush : public CXTPMarkupBrush
{
	DECLARE_MARKUPCLASS(CXTPMarkupSolidColorBrush);

public:
	CXTPMarkupSolidColorBrush();
	CXTPMarkupSolidColorBrush(COLORREF clr);

public:
	void FillRect(CXTPMarkupDrawingContext* pDC, CRect rc);
	COLORREF GetHintColor() const;

public:
	BOOL IsEqual(const CXTPMarkupObject* pObject) const;


protected:
	static CXTPMarkupDependencyProperty* m_pColorProperty;
};


class _XTP_EXT_CLASS CXTPMarkupGradientStop : public CXTPMarkupObject
{
	DECLARE_MARKUPCLASS(CXTPMarkupGradientStop);
public:
	CXTPMarkupGradientStop();
	CXTPMarkupGradientStop(COLORREF clr, double dOffset = 0);

public:
	COLORREF GetColor() const;
	double GetOffset() const;
protected:

protected:
	static CXTPMarkupDependencyProperty* m_pColorProperty;
	static CXTPMarkupDependencyProperty* m_pOffsetProperty;
};

class _XTP_EXT_CLASS CXTPMarkupGradientStops : public CXTPMarkupCollection
{
public:
	CXTPMarkupGradientStops();

public:
	CXTPMarkupGradientStop* GetItem(int nIndex) const;
};

class _XTP_EXT_CLASS CXTPMarkupPoint : public CXTPMarkupObject
{
	DECLARE_MARKUPCLASS(CXTPMarkupPoint);
public:
	CXTPMarkupPoint();
	CXTPMarkupPoint(double x, double y);

public:
	CXTPMarkupPoint& operator=(const CXTPMarkupPoint& srcPoint);
protected:
	CXTPMarkupObject* ConvertFrom(CXTPMarkupObject* pObject) const;

public:
	double x;
	double y;
};


class _XTP_EXT_CLASS CXTPMarkupLinearGradientBrush : public CXTPMarkupBrush
{
public:
	struct GRADIENTSTOP
	{
		RGBQUAD clr;
		double dOffset;
		double dDiff;
		int nIndex;
	};

	DECLARE_MARKUPCLASS(CXTPMarkupLinearGradientBrush);
public:
	CXTPMarkupLinearGradientBrush();
	CXTPMarkupLinearGradientBrush(CXTPMarkupGradientStops* pGradientStops);
	~CXTPMarkupLinearGradientBrush();

public:
	CXTPMarkupGradientStops* GetGradientStops() const;
	void SetStartPoint(double x, double y);
	void SetEndPoint(double x, double y);

public:
	void FillRect(CXTPMarkupDrawingContext* pDC, CRect rc);

protected:
	void SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent);

private:
	static int _cdecl _GradientStopCompare(const void *arg1, const void *arg2);

protected:
	CXTPMarkupGradientStops* m_pGradientStops;

public:
	static CXTPMarkupDependencyProperty* m_pStartPointProperty;
	static CXTPMarkupDependencyProperty* m_pEndPointProperty;
};


class _XTP_EXT_CLASS CXTPMarkupFont : public CXTPMarkupObject
{
public:
	CXTPMarkupFont();
	~CXTPMarkupFont();
public:
	HFONT m_hFont;
	LOGFONT m_lf;
	CXTPMarkupFont* m_pNextChain;
	CXTPMarkupContext* m_pMarkupContext;
};

class _XTP_EXT_CLASS CXTPMarkupDrawingContext
{
public:
	CXTPMarkupDrawingContext(HDC hDC);
	CXTPMarkupDrawingContext();

public:
	virtual ~CXTPMarkupDrawingContext();

protected:
	void Init();
public:
	void DrawRectangle(CXTPMarkupBrush* pBrush, CRect rc);
	void DrawFrame(CXTPMarkupBrush* pBrush, CRect rc);
	void FillSolidRect(CRect rc, COLORREF clr);

	void SetFont(CXTPMarkupFont* pFont);

	HDC GetSafeHdc() const;

	CXTPMarkupContext* GetMarkupContext() const;

	HDC Detach();

	POINT TranslatePoint(const POINT& ptVisualOffset) const;

	void SetViewport(const POINT& ptVisualOffset);
	POINT OffsetViewport(const POINT& ptViewortOrg);

	RECT GetClipBox() const;
	HRGN SaveClipRegion();
	void RestoreClipRegion(HRGN hrgnClip);
	void IntersectClipRect(const RECT& rcLayoutClip);

	virtual BOOL IsPrinting() const;

	SIZE GetTextExtent(LPCWSTR lpszText, int nCount) const;
	virtual void DrawTextLine(LPCWSTR lpszText, UINT nCount, LPCRECT lpRect);


protected:
	virtual HFONT SelectFontObject(HFONT hFont);
	virtual void SetViewportOrg(const POINT& ptViewortOrg);

protected:
	HDC m_hDC;
	HDC m_hAttribDC;

	CXTPMarkupFont* m_pSelectedFont;
	HFONT m_hOldFont;
	SIZE m_sizeWinExt;
	SIZE m_sizeVpExt;
	POINT m_ptViewortOrg;
	CRect m_rcClipBox;
	BOOL m_bDeleteDC;
};

class _XTP_EXT_CLASS CXTPMarkupPrintingContext : public CXTPMarkupDrawingContext
{
public:
	CXTPMarkupPrintingContext(HDC hDC, HDC hAttribDC);

public:
	virtual BOOL IsPrinting() const;
	virtual void DrawTextLine(LPCWSTR lpszText, UINT nCount, LPCRECT lpRect);

protected:
	CSize ComputeDeltas(int& x, LPCWSTR lpszString, UINT &nCount,
		BOOL bTabbed, UINT nTabStops, LPINT lpnTabStops, int nTabOrigin,
		LPWSTR lpszOutputString, int* pnDxWidths, int& nRightFixup) const;

	int ComputeNextTab(int x, UINT nTabStops, LPINT lpnTabStops, int nTabOrigin, int nTabWidth) const;

protected:
};


AFX_INLINE HDC CXTPMarkupDrawingContext::GetSafeHdc() const {
	return m_hDC;
}

AFX_INLINE BOOL CXTPMarkupDrawingContext::IsPrinting() const {
	return FALSE;
}

AFX_INLINE BOOL CXTPMarkupPrintingContext::IsPrinting() const {
	return TRUE;
}

AFX_INLINE RECT CXTPMarkupDrawingContext::GetClipBox() const {
	return m_rcClipBox;
}

AFX_INLINE CXTPMarkupGradientStops* CXTPMarkupLinearGradientBrush::GetGradientStops() const {
	return m_pGradientStops;
}
AFX_INLINE CXTPMarkupGradientStop* CXTPMarkupGradientStops::GetItem(int nIndex) const {
	return nIndex >= 0 && nIndex < m_arrItems.GetSize() ? (CXTPMarkupGradientStop*)m_arrItems[nIndex] : NULL;
}

#endif // !defined(__XTPMARKUPDRAWINGCONTEXT_H__)
