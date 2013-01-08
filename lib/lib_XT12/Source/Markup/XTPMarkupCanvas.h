// XTPMarkupCanvas.h: interface for the CXTPMarkupCanvas class.
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

#if !defined(__XTPMARKUPCANVAS_H__)
#define __XTPMARKUPCANVAS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupPanel.h"

class _XTP_EXT_CLASS CXTPMarkupCanvas : public CXTPMarkupPanel
{
	DECLARE_MARKUPCLASS(CXTPMarkupCanvas)
protected:
	CXTPMarkupCanvas();
	virtual ~CXTPMarkupCanvas();

public:
	static void AFX_CDECL SetLeft(CXTPMarkupUIElement* pElement, int nLeft);
	static void AFX_CDECL SetTop(CXTPMarkupUIElement* pElement, int nTop);
	static void AFX_CDECL SetRight(CXTPMarkupUIElement* pElement, int nRight);
	static void AFX_CDECL SetBottom(CXTPMarkupUIElement* pElement, int nBottom);

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize availableSize);
	virtual CSize ArrangeOverride(CSize arrangeSize);


public:
	static CXTPMarkupDependencyProperty* m_pTopProperty;
	static CXTPMarkupDependencyProperty* m_pLeftProperty;
	static CXTPMarkupDependencyProperty* m_pRightProperty;
	static CXTPMarkupDependencyProperty* m_pBottomProperty;

};

#endif // !defined(__XTPMARKUPCANVAS_H__)
