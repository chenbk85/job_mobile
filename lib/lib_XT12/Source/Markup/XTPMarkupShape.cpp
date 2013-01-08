// XTPMarkupShape.cpp: implementation of the CXTPMarkupShape class.
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

#include "XTPMarkupShape.h"
#include "XTPMarkupDrawingContext.h"
#include "XTPMarkupBuilder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupShape


CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pFillProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStrokeProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStrokeThicknessProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStretchProperty = NULL;

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupShape, CXTPMarkupFrameworkElement)

void CXTPMarkupShape::RegisterMarkupClass()
{
	m_pFillProperty = CXTPMarkupDependencyProperty::Register(L"Fill", MARKUP_TYPE(CXTPMarkupBrush), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pStrokeProperty = CXTPMarkupDependencyProperty::Register(L"Stroke", MARKUP_TYPE(CXTPMarkupBrush), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pStrokeThicknessProperty = CXTPMarkupDependencyProperty::Register(L"StrokeThickness", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pStretchProperty = CXTPMarkupDependencyProperty::Register(L"Stretch", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(CXTPMarkupEnum::CreateValue(xtpMarkupStretchNone), &CXTPMarkupBuilder::ConvertStretch, CXTPMarkupPropertyMetadata::flagAffectsRender));
}

CXTPMarkupShape::CXTPMarkupShape()
{
}

CXTPMarkupShape::~CXTPMarkupShape()
{

}

CXTPMarkupBrush* CXTPMarkupShape::GetFill() const
{
	return MARKUP_STATICCAST(CXTPMarkupBrush, GetValue(m_pFillProperty));
}

void CXTPMarkupShape::SetFill(CXTPMarkupBrush* brush)
{
	SetValue(m_pFillProperty, brush);
}

CXTPMarkupBrush* CXTPMarkupShape::GetStroke() const
{
	return MARKUP_STATICCAST(CXTPMarkupBrush, GetValue(m_pStrokeProperty));
}

void CXTPMarkupShape::SetStroke(CXTPMarkupBrush* brush)
{
	SetValue(m_pStrokeProperty, brush);
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPointCollection

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupPointCollection, CXTPMarkupObject)

void CXTPMarkupPointCollection::RegisterMarkupClass()
{

}

CXTPMarkupPointCollection::CXTPMarkupPointCollection()
{
	m_rcBounds.SetRectEmpty();
}

CXTPMarkupPointCollection::CXTPMarkupPointCollection(CPointArray& arr)
{
	m_arrPoints.Copy(arr);

	m_rcBounds.SetRectEmpty();
	for (int i = 0; i < (int)m_arrPoints.GetSize(); i++)
	{
		POINT& pt = m_arrPoints[i];
		if (pt.x > m_rcBounds.right) m_rcBounds.right = pt.x;
		if (pt.y > m_rcBounds.bottom) m_rcBounds.bottom = pt.y;
	}
}


BOOL CXTPMarkupPointCollection::GetNextValue(LPCWSTR& lpszValue, int& nValue)
{
	while (*lpszValue == ' ') lpszValue++;
	LPCWSTR lpszNext = lpszValue;

	nValue = 0;
	int nSign = 1;
	if (*lpszNext == '-')
	{
		nSign = -1;
		lpszNext++;
	}

	if (*lpszNext == 0)
		return FALSE;

	while (*lpszNext != 0)
	{
		WCHAR c = *lpszNext;

		if (c == ' ' || c == ',')
		{
			if (lpszNext == lpszValue)
				return FALSE;
			lpszNext++;
			break;
		}

		if (c <'0' || c > '9')
			return FALSE;

		nValue = 10 * nValue + (c - '0');

		lpszNext++;
	}

	lpszValue = lpszNext;
	nValue *= nSign;

	return TRUE;
}

BOOL CXTPMarkupPointCollection::ConvertFromString(LPCWSTR lpszValue, CXTPMarkupPointCollection::CPointArray& arr)
{
	if (!lpszValue)
		return FALSE;

	while (*lpszValue != 0)
	{
		int x, y;
		if (!GetNextValue(lpszValue, x))
			return FALSE;

		if (!GetNextValue(lpszValue, y))
			return FALSE;

		while (*lpszValue == ' ') lpszValue++;

		POINT pt = {x, y};
		arr.Add(pt);
	}

	return TRUE;
}

CXTPMarkupObject* CXTPMarkupPointCollection::ConvertFrom(CXTPMarkupObject* pObject) const
{
	if (IsStringObject(pObject))
	{
		CPointArray arr;
		if (ConvertFromString(*((CXTPMarkupString*)pObject), arr))
		{
			return new CXTPMarkupPointCollection(arr);
		}
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPolygon


CXTPMarkupDependencyProperty* CXTPMarkupPolygon::m_pPointsProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"Polygon", CXTPMarkupPolygon, CXTPMarkupShape)

void CXTPMarkupPolygon::RegisterMarkupClass()
{
	m_pPointsProperty = CXTPMarkupDependencyProperty::Register(L"Points", MARKUP_TYPE(CXTPMarkupPointCollection), MARKUP_TYPE(CXTPMarkupPolygon),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

}

CXTPMarkupPolygon::CXTPMarkupPolygon()
{
}

CXTPMarkupPolygon::~CXTPMarkupPolygon()
{

}

void CXTPMarkupPolygon::SetPoints(CXTPMarkupPointCollection* pPoints)
{
	SetValue(m_pPointsProperty, pPoints);
}

CXTPMarkupPointCollection* CXTPMarkupPolygon::GetPoints() const
{
	return MARKUP_STATICCAST(CXTPMarkupPointCollection, GetValue(m_pPointsProperty));
}

CSize CXTPMarkupPolygon::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize /*szAvailableSize*/)
{
	CXTPMarkupPointCollection* pPoints = GetPoints();
	if (!pPoints)
		return CSize(0, 0);

	return pPoints->GetBounds().Size();
}

void CXTPMarkupPolygon::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CXTPMarkupBrush* pStrokeBrush = GetStroke();
	CXTPMarkupBrush* pFillBrush = GetFill();

	if (!pStrokeBrush && !pFillBrush)
		return;

	CXTPMarkupPointCollection* pPoints = GetPoints();
	if (!pPoints)
		return;

	const CXTPMarkupPointCollection::CPointArray& arr = pPoints->GetPoints();

	int nStroke = pStrokeBrush ? GetStrokeThickness() : 0;

	CPen penStroke;
	if (nStroke > 0) penStroke.CreatePen(PS_SOLID, nStroke, pStrokeBrush->GetHintColor());

	CBrush brushFill;
	if (pFillBrush) brushFill.CreateSolidBrush(pFillBrush->GetHintColor());

	HGDIOBJ hOldPen = penStroke.GetSafeHandle() ? ::SelectObject(pDC->GetSafeHdc(), penStroke) : ::SelectObject(pDC->GetSafeHdc(), ::GetStockObject(NULL_PEN));
	HGDIOBJ hOldBrush = brushFill.GetSafeHandle() ? ::SelectObject(pDC->GetSafeHdc(), brushFill) : ::SelectObject(pDC->GetSafeHdc(), ::GetStockObject(NULL_BRUSH));

	::Polygon(pDC->GetSafeHdc(), arr.GetData(), (int)arr.GetSize());

	if (hOldPen) ::SelectObject(pDC->GetSafeHdc(), hOldPen);
	if (hOldBrush) ::SelectObject(pDC->GetSafeHdc(), hOldBrush);
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPolyline


CXTPMarkupDependencyProperty* CXTPMarkupPolyline::m_pPointsProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"Polyline", CXTPMarkupPolyline, CXTPMarkupShape)

void CXTPMarkupPolyline::RegisterMarkupClass()
{
	m_pPointsProperty = CXTPMarkupDependencyProperty::Register(L"Points", MARKUP_TYPE(CXTPMarkupPointCollection), MARKUP_TYPE(CXTPMarkupPolyline),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));
}

CXTPMarkupPolyline::CXTPMarkupPolyline()
{
}

CXTPMarkupPolyline::~CXTPMarkupPolyline()
{

}

void CXTPMarkupPolyline::SetPoints(CXTPMarkupPointCollection* pPoints)
{
	SetValue(m_pPointsProperty, pPoints);
}

CXTPMarkupPointCollection* CXTPMarkupPolyline::GetPoints() const
{
	return MARKUP_STATICCAST(CXTPMarkupPointCollection, GetValue(m_pPointsProperty));
}

CSize CXTPMarkupPolyline::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize /*szAvailableSize*/)
{
	CXTPMarkupPointCollection* pPoints = GetPoints();
	if (!pPoints)
		return CSize(0, 0);

	CSize sz = pPoints->GetBounds().Size();

	CXTPMarkupBrush* pStrokeBrush = GetStroke();
	int nStroke = pStrokeBrush ? GetStrokeThickness() : 0;

	sz.cx += nStroke;
	sz.cy += nStroke;

	return sz;
}

void CXTPMarkupPolyline::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CXTPMarkupBrush* pStrokeBrush = GetStroke();

	if (!pStrokeBrush)
		return;

	CXTPMarkupPointCollection* pPoints = GetPoints();
	if (!pPoints)
		return;

	const CXTPMarkupPointCollection::CPointArray& arr = pPoints->GetPoints();

	int nStroke = pStrokeBrush ? GetStrokeThickness() : 0;

	CPen penStroke;
	if (nStroke > 0) penStroke.CreatePen(PS_SOLID, nStroke, pStrokeBrush->GetHintColor());

	HGDIOBJ hOldPen = penStroke.GetSafeHandle() ? ::SelectObject(pDC->GetSafeHdc(), penStroke) : ::SelectObject(pDC->GetSafeHdc(), ::GetStockObject(NULL_PEN));

	if (GetStretch() != xtpMarkupStretchNone)
	{
		CXTPMarkupPointCollection::CPointArray arrStretch;
		arrStretch.Copy(arr);
		int nCount = (int)arrStretch.GetSize();

		CSize sz = GetRenderSize();
		CRect rc = pPoints->GetBounds();
		for (int i = 0; i < nCount; i++)
		{
			POINT& pt = arrStretch[i];
			if (rc.Width() != 0) pt.x = pt.x * sz.cx / rc.Width();
			if (rc.Height() != 0) pt.y = pt.y * sz.cy / rc.Height();
		}

		::Polyline(pDC->GetSafeHdc(), arrStretch.GetData(), nCount);
	}
	else
	{
		::Polyline(pDC->GetSafeHdc(), arr.GetData(), (int)arr.GetSize());
	}

	if (hOldPen) ::SelectObject(pDC->GetSafeHdc(), hOldPen);
}




//////////////////////////////////////////////////////////////////////////
// CXTPMarkupRectangle

IMPLEMENT_MARKUPCLASS(L"Rectangle", CXTPMarkupRectangle, CXTPMarkupShape)

void CXTPMarkupRectangle::RegisterMarkupClass()
{

}

CXTPMarkupRectangle::CXTPMarkupRectangle()
{
}

CXTPMarkupRectangle::~CXTPMarkupRectangle()
{

}

CSize CXTPMarkupRectangle::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize /*szAvailableSize*/)
{
	return CSize(0, 0);
}

void CXTPMarkupRectangle::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CXTPMarkupBrush* pStrokeBrush = GetStroke();
	CXTPMarkupBrush* pFillBrush = GetFill();

	if (!pStrokeBrush && !pFillBrush)
		return;

	int nStroke = pStrokeBrush ? GetStrokeThickness() : 0;

	CRect rc(0, 0, GetRenderSize().cx, GetRenderSize().cy);
	if (rc.Width() == 0 || rc.Height() == 0)
		return;


	if (FALSE)
	{
		CPoint ptViewortOrg;
		GetViewportOrgEx(pDC->GetSafeHdc(), &ptViewortOrg);

		CRgn rgn;
		rgn.Attach(::CreateRoundRectRgn(ptViewortOrg.x, ptViewortOrg.y, ptViewortOrg.x + rc.Width(), ptViewortOrg.y + rc.Height(), 0, 0));

		::ExtSelectClipRgn(pDC->GetSafeHdc(), rgn, RGN_AND);
	}

	if (pFillBrush) pFillBrush->FillRect(pDC, rc);

	if (nStroke > 0)
	{
		pStrokeBrush->FillRect(pDC, CRect(0, 0, nStroke, rc.bottom));
		pStrokeBrush->FillRect(pDC, CRect(rc.right - nStroke, 0, rc.right, rc.bottom));
		pStrokeBrush->FillRect(pDC, CRect(0, 0, rc.right, nStroke));
		pStrokeBrush->FillRect(pDC, CRect(0, rc.bottom - nStroke, rc.right, rc.bottom));

	}

	if (FALSE)
	{
		::SelectClipRgn(pDC->GetSafeHdc(), 0);
	}
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupEllipse


IMPLEMENT_MARKUPCLASS(L"Ellipse", CXTPMarkupEllipse, CXTPMarkupShape)

void CXTPMarkupEllipse::RegisterMarkupClass()
{

}

CXTPMarkupEllipse::CXTPMarkupEllipse()
{
}

CXTPMarkupEllipse::~CXTPMarkupEllipse()
{

}

CSize CXTPMarkupEllipse::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize /*szAvailableSize*/)
{
	return CSize(0, 0);
}

void CXTPMarkupEllipse::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CXTPMarkupBrush* pStrokeBrush = GetStroke();
	CXTPMarkupBrush* pFillBrush = GetFill();

	if (!pStrokeBrush && !pFillBrush)
		return;

	int nStroke = pStrokeBrush ? GetStrokeThickness() : 0;

	CPen penStroke;
	if (nStroke > 0) penStroke.CreatePen(PS_SOLID, nStroke, pStrokeBrush->GetHintColor());

	CBrush brushFill;
	if (pFillBrush) brushFill.CreateSolidBrush(pFillBrush->GetHintColor());

	HGDIOBJ hOldPen = penStroke.GetSafeHandle() ? ::SelectObject(pDC->GetSafeHdc(), penStroke) : ::SelectObject(pDC->GetSafeHdc(), ::GetStockObject(NULL_PEN));
	HGDIOBJ hOldBrush = brushFill.GetSafeHandle() ? ::SelectObject(pDC->GetSafeHdc(), brushFill) : ::SelectObject(pDC->GetSafeHdc(), ::GetStockObject(NULL_BRUSH));

	::Ellipse(pDC->GetSafeHdc(), 0, 0, GetRenderSize().cx, GetRenderSize().cy);

	if (hOldPen) ::SelectObject(pDC->GetSafeHdc(), hOldPen);
	if (hOldBrush) ::SelectObject(pDC->GetSafeHdc(), hOldBrush);
}

CXTPMarkupInputElement* CXTPMarkupEllipse::InputHitTestOverride(CPoint point) const
{
	if (m_szRenderSize.cx < 1 || m_szRenderSize.cy < 1)
		return (CXTPMarkupInputElement*)this;

   // Determine radii
	double a = m_szRenderSize.cx / 2;
	double b = m_szRenderSize.cy / 2;

	double x = point.x - a;
	double y = point.y - b;

	return ((x * x) / (a * a) + (y * y) / (b * b) <= 1) ? (CXTPMarkupInputElement*)this : NULL;
}


//////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupLine


CXTPMarkupDependencyProperty* CXTPMarkupLine::m_pX1Property = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupLine::m_pY1Property = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupLine::m_pX2Property = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupLine::m_pY2Property = NULL;


IMPLEMENT_MARKUPCLASS(L"Line", CXTPMarkupLine, CXTPMarkupShape)

void CXTPMarkupLine::RegisterMarkupClass()
{
	m_pX1Property = CXTPMarkupDependencyProperty::Register(L"X1", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupLine),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pY1Property = CXTPMarkupDependencyProperty::Register(L"Y1", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupLine),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pX2Property = CXTPMarkupDependencyProperty::Register(L"X2", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupLine),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pY2Property = CXTPMarkupDependencyProperty::Register(L"Y2", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupLine),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));
}

CXTPMarkupLine::CXTPMarkupLine()
{
}

CXTPMarkupLine::~CXTPMarkupLine()
{

}

int CXTPMarkupLine::GetX1() const
{
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pX1Property));
	return pValue != NULL ? (int)*pValue : 0;
}

int CXTPMarkupLine::GetX2() const
{
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pX2Property));
	return pValue != NULL ? (int)*pValue : 0;
}

int CXTPMarkupLine::GetY1() const
{
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pY1Property));
	return pValue != NULL ? (int)*pValue : 0;
}

int CXTPMarkupLine::GetY2() const
{
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pY2Property));
	return pValue != NULL ? (int)*pValue : 0;
}

CSize CXTPMarkupLine::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize /*szAvailableSize*/)
{
	int x = max(GetX1(), GetX2());
	int y = max(GetY1(), GetY2());

	return CSize(x, y);
}

void CXTPMarkupLine::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CXTPMarkupBrush* pStrokeBrush = GetStroke();

	if (!pStrokeBrush)
		return;

	int x1 = GetX1();
	int x2 = GetX2();
	int y1 = GetY1();
	int y2 = GetY2();
	if (x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0)
		return;

	int nStroke = GetStrokeThickness();
	if (nStroke == 0)
		return;

	CPen penStroke;
	penStroke.CreatePen(PS_SOLID, nStroke, pStrokeBrush->GetHintColor());

	HGDIOBJ hOldPen = penStroke.GetSafeHandle() ? ::SelectObject(pDC->GetSafeHdc(), penStroke) : ::SelectObject(pDC->GetSafeHdc(), ::GetStockObject(NULL_PEN));

	::MoveToEx(pDC->GetSafeHdc(), x1, y1, NULL);
	::LineTo(pDC->GetSafeHdc(), x2, y2);

	if (hOldPen) ::SelectObject(pDC->GetSafeHdc(), hOldPen);
}

CXTPMarkupInputElement* CXTPMarkupLine::InputHitTestOverride(CPoint point) const
{
	if (!GetStroke())
		return NULL;

	int nStroke = GetStrokeThickness();
	if (nStroke == 0)
		return NULL;

	double x = GetX2() - GetX1();
	double y = GetY2() - GetY1();

	double xp = point.x - GetX1();
	double yp = point.y - GetY1();

	double s = (double)nStroke / 2.0;

	if (xp + s < min(x, 0) || xp - s > max(x, 0) || yp + s < min(y, 0) || yp - s > max(y, 0))
		return NULL;

	if (x == 0)
		return fabs(xp) <= s ? (CXTPMarkupInputElement*)this : NULL;

	double yStroke = fabs(s / cos(atan(y / x)));

	double y0 = y * xp / (double)x;

	return fabs(y0 - yp) <= yStroke ? (CXTPMarkupInputElement*)this : NULL;
}
