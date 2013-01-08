// XTPMarkupStackPanel.h: interface for the CXTPMarkupStackPanel class.
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

#if !defined(__XTPMARKUPSTACKPANEL_H__)
#define __XTPMARKUPSTACKPANEL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupPanel.h"

class _XTP_EXT_CLASS CXTPMarkupStackPanel : public CXTPMarkupPanel
{
	DECLARE_MARKUPCLASS(CXTPMarkupStackPanel)
protected:
	CXTPMarkupStackPanel();
	virtual ~CXTPMarkupStackPanel();

public:
	XTPMarkupOrientation GetOrientation() const;
	void SetOrientation(XTPMarkupOrientation orientation);

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual CSize ArrangeOverride(CSize szFinalSize);

protected:
	static CXTPMarkupDependencyProperty* m_pOrientationProperty;
};

class _XTP_EXT_CLASS CXTPMarkupWrapPanel : public CXTPMarkupPanel
{
	DECLARE_MARKUPCLASS(CXTPMarkupWrapPanel)
protected:
	CXTPMarkupWrapPanel();
	virtual ~CXTPMarkupWrapPanel();

public:
	XTPMarkupOrientation GetOrientation() const;
	void SetOrientation(XTPMarkupOrientation orientation);

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual CSize ArrangeOverride(CSize szFinalSize);

protected:
	void ArrangeLine(int nPanelHeight, int nLineHeight, int nFirstElement, int nCount);


protected:
	static CXTPMarkupDependencyProperty* m_pOrientationProperty;
	static CXTPMarkupDependencyProperty* m_pItemHeightProperty;
	static CXTPMarkupDependencyProperty* m_pItemWidthProperty;

};


#endif // !defined(__XTPMARKUPSTACKPANEL_H__)
