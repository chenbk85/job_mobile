// XTPMarkupStackPanel.cpp: implementation of the CXTPMarkupStackPanel class.
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
#include "XTPMarkupStackPanel.h"
#include "XTPMarkupBuilder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXTPMarkupDependencyProperty* CXTPMarkupStackPanel::m_pOrientationProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"StackPanel", CXTPMarkupStackPanel, CXTPMarkupPanel)

void CXTPMarkupStackPanel::RegisterMarkupClass()
{
	m_pOrientationProperty = CXTPMarkupDependencyProperty::Register(L"Orientation", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupStackPanel),
		new CXTPMarkupPropertyMetadata(NULL, &CXTPMarkupBuilder::ConvertOrientation, CXTPMarkupPropertyMetadata::flagAffectsMeasure));
}

CXTPMarkupStackPanel::CXTPMarkupStackPanel()
{
}

CXTPMarkupStackPanel::~CXTPMarkupStackPanel()
{

}

XTPMarkupOrientation CXTPMarkupStackPanel::GetOrientation() const
{
	CXTPMarkupEnum* pOrientation = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pOrientationProperty));
	return pOrientation ? (XTPMarkupOrientation)(int)(*pOrientation) : xtpMarkupOrientationVertical;
}

void CXTPMarkupStackPanel::SetOrientation(XTPMarkupOrientation orientation)
{
	SetValue(m_pOrientationProperty, CXTPMarkupEnum::CreateValue(orientation));
}

CSize CXTPMarkupStackPanel::MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize constraint)
{
	CSize size(0, 0);
	CSize availableSize = constraint;

	bool bHorizontal = GetOrientation() == xtpMarkupOrientationHorizontal;

	if (bHorizontal)
	{
		availableSize.cx = INT_MAX;
	}
	else
	{
		availableSize.cy = INT_MAX;
	}

	int nCount = m_pChildren->GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CXTPMarkupUIElement* pElement = m_pChildren->GetItem(i);
		if (pElement == NULL)
			continue;

		pElement->Measure(pDC, availableSize);
		CSize desiredSize = pElement->GetDesiredSize();

		if (bHorizontal)
		{
			size.cx += desiredSize.cx;
			size.cy = max(size.cy, desiredSize.cy);
		}
		else
		{
			size.cx = max(size.cx, desiredSize.cx);
			size.cy += desiredSize.cy;
		}
	}

	return size;
}

CSize CXTPMarkupStackPanel::ArrangeOverride(CSize arrangeSize)
{
	bool bHorizontal = GetOrientation() == xtpMarkupOrientationHorizontal;

	CRect finalRect(CPoint(0), arrangeSize);
	int width = 0;

	int nCount = m_pChildren->GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CXTPMarkupUIElement* pElement = m_pChildren->GetItem(i);
		if (pElement == NULL)
			continue;

		if (bHorizontal)
		{
			finalRect.left += width;
			width = pElement->GetDesiredSize().cx;
			finalRect.right = finalRect.left + width;
			finalRect.bottom = max(arrangeSize.cy, pElement->GetDesiredSize().cy);
		}
		else
		{
			finalRect.top += width;
			width = pElement->GetDesiredSize().cy;
			finalRect.bottom = finalRect.top + width;
			finalRect.right = max(arrangeSize.cx, pElement->GetDesiredSize().cx);
		}

		pElement->Arrange(finalRect);
	}

	return arrangeSize;
}

//////////////////////////////////////////////////////////////////////////
//

CXTPMarkupDependencyProperty* CXTPMarkupWrapPanel::m_pOrientationProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupWrapPanel::m_pItemHeightProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupWrapPanel::m_pItemWidthProperty = NULL;


IMPLEMENT_MARKUPCLASS(L"WrapPanel", CXTPMarkupWrapPanel, CXTPMarkupPanel)

void CXTPMarkupWrapPanel::RegisterMarkupClass()
{
	m_pOrientationProperty = CXTPMarkupDependencyProperty::Register(L"Orientation", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupWrapPanel),
		new CXTPMarkupPropertyMetadata(NULL, &CXTPMarkupBuilder::ConvertOrientation, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pItemHeightProperty = CXTPMarkupDependencyProperty::Register(L"ItemHeight", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupWrapPanel),
		new CXTPMarkupPropertyMetadata(NULL,CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pItemWidthProperty = CXTPMarkupDependencyProperty::Register(L"ItemWidth", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupWrapPanel),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

}

CXTPMarkupWrapPanel::CXTPMarkupWrapPanel()
{
}

CXTPMarkupWrapPanel::~CXTPMarkupWrapPanel()
{

}

XTPMarkupOrientation CXTPMarkupWrapPanel::GetOrientation() const
{
	CXTPMarkupEnum* pOrientation = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pOrientationProperty));
	return pOrientation ? (XTPMarkupOrientation)(int)(*pOrientation) : xtpMarkupOrientationHorizontal;
}

void CXTPMarkupWrapPanel::SetOrientation(XTPMarkupOrientation orientation)
{
	SetValue(m_pOrientationProperty, CXTPMarkupEnum::CreateValue(orientation));
}

inline int OrientationWidth(BOOL bHorizontal, const CSize& sz) { return bHorizontal ? sz.cx : sz.cy;};
inline int OrientationHeight(BOOL bHorizontal, const CSize& sz) { return bHorizontal ? sz.cy : sz.cx;};

CSize CXTPMarkupWrapPanel::MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize constraint)
{
	BOOL bHorizontal = GetOrientation() == xtpMarkupOrientationHorizontal;

	CXTPMarkupInt* pItemWidth = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pItemWidthProperty));
	CXTPMarkupInt* pItemHeight = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pItemHeightProperty));

	CSize availableSize(pItemWidth != NULL ? (int)*pItemWidth : constraint.cx, pItemHeight != NULL ? (int)*pItemHeight : constraint.cy);

	int nTotalWidth = OrientationWidth(bHorizontal, constraint);

	int nLineWidth = 0;
	int nLineHeight = 0;

	int nPanelWidth = 0;
	int nPanelHeight = 0;

	int nCount = m_pChildren->GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CXTPMarkupUIElement* pElement = m_pChildren->GetItem(i);
		if (pElement == NULL)
			continue;

		pElement->Measure(pDC, availableSize);
		CSize desiredSize(pItemWidth != NULL ? (int)*pItemWidth : pElement->GetDesiredSize().cx, pItemHeight != NULL ? (int)*pItemHeight : pElement->GetDesiredSize().cy);

		int nDesiredWidth = OrientationWidth(bHorizontal, desiredSize);
		int nDesiredHeight = OrientationHeight(bHorizontal, desiredSize);

		if (nLineWidth + nDesiredWidth > nTotalWidth)
		{
			nPanelWidth = max(nPanelWidth, nLineWidth);
			nPanelHeight += nLineHeight;

			nLineWidth = nDesiredWidth;
			nLineHeight = nDesiredHeight;
		}
		else
		{
			nLineWidth += nDesiredWidth;
			nLineHeight = max(nLineHeight, nDesiredHeight);
		}
	}

	nPanelWidth = max(nPanelWidth, nLineWidth);
	nPanelHeight += nLineHeight;

	return bHorizontal ? CSize(nPanelWidth, nPanelHeight) : CSize(nPanelHeight, nPanelWidth);
}

void CXTPMarkupWrapPanel::ArrangeLine(int nPanelHeight, int nLineHeight, int nFirstElement, int nLastElement)
{
	BOOL bHorizontal = GetOrientation() == xtpMarkupOrientationHorizontal;

	CXTPMarkupInt* pItemWidth = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(bHorizontal ? m_pItemWidthProperty : m_pItemHeightProperty));

	int nTotalWidth = 0;

	for (int i = nFirstElement; i < nLastElement; i++)
	{
		CXTPMarkupUIElement* pElement = m_pChildren->GetItem(i);
		if (pElement == NULL)
			continue;

		int nWidth = pItemWidth != NULL ? (int)*pItemWidth : (bHorizontal ? pElement->GetDesiredSize().cx : pElement->GetDesiredSize().cy);

		if (bHorizontal)
		{
			pElement->Arrange(CRect(nTotalWidth, nPanelHeight, nTotalWidth + nWidth, nPanelHeight + nLineHeight));
		}
		else
		{
			pElement->Arrange(CRect(nPanelHeight, nTotalWidth, nPanelHeight + nLineHeight, nTotalWidth + nWidth));
		}

		nTotalWidth += nWidth;
	}
}

CSize CXTPMarkupWrapPanel::ArrangeOverride(CSize arrangeSize)
{
	BOOL bHorizontal = GetOrientation() == xtpMarkupOrientationHorizontal;

	CXTPMarkupInt* pItemWidth = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pItemWidthProperty));
	CXTPMarkupInt* pItemHeight = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pItemHeightProperty));

	int nTotalWidth = OrientationWidth(bHorizontal, arrangeSize);

	int nLineWidth = 0;
	int nLineHeight = 0;

	int nPanelHeight = 0;

	int nFirstElement = 0;

	int nCount = m_pChildren->GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CXTPMarkupUIElement* pElement = m_pChildren->GetItem(i);
		if (pElement == NULL)
			continue;

		CSize desiredSize(pItemWidth != NULL ? (int)*pItemWidth : pElement->GetDesiredSize().cx, pItemHeight != NULL ? (int)*pItemHeight : pElement->GetDesiredSize().cy);

		int nDesiredWidth = OrientationWidth(bHorizontal, desiredSize);
		int nDesiredHeight = OrientationHeight(bHorizontal, desiredSize);

		if (nLineWidth + nDesiredWidth > nTotalWidth)
		{
			ArrangeLine(nPanelHeight, nLineHeight, nFirstElement, i);

			nPanelHeight += nLineHeight;

			nLineWidth = nDesiredWidth;
			nLineHeight = nDesiredHeight;

			nFirstElement = i;
		}
		else
		{
			nLineWidth += nDesiredWidth;
			nLineHeight = max(nLineHeight, nDesiredHeight);
		}
	}

	ArrangeLine(nPanelHeight, nLineHeight, nFirstElement, nCount);

	return arrangeSize;
}
