// XTPMarkupShape.h: interface for the CXTPMarkupShape class.
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

#if !defined(__XTPMARKUPSHAPE_H__)
#define __XTPMARKUPSHAPE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXTPMarkupBrush;

#include "XTPMarkupFrameworkElement.h"

enum XTPMarkupStretch
{
	xtpMarkupStretchNone,
	xtpMarkupStretchFill,
	xtpMarkupStretchUniform,
	xtpMarkupStretchUniformToFill
};

class _XTP_EXT_CLASS CXTPMarkupShape : public CXTPMarkupFrameworkElement
{
	DECLARE_MARKUPCLASS(CXTPMarkupShape)

protected:
	CXTPMarkupShape();
	~CXTPMarkupShape();

public:
	void SetFill(CXTPMarkupBrush* brush);
	CXTPMarkupBrush* GetFill() const;

	void SetStroke(CXTPMarkupBrush* brush);
	CXTPMarkupBrush* GetStroke() const;

	void SetStrokeThickness(int nThickness);
	int GetStrokeThickness() const;

	XTPMarkupStretch GetStretch() const;

public:
	static CXTPMarkupDependencyProperty* m_pStrokeProperty;
	static CXTPMarkupDependencyProperty* m_pFillProperty;
	static CXTPMarkupDependencyProperty* m_pStrokeThicknessProperty;
	static CXTPMarkupDependencyProperty* m_pStretchProperty;
};


class _XTP_EXT_CLASS CXTPMarkupPointCollection : public CXTPMarkupObject
{
	DECLARE_MARKUPCLASS(CXTPMarkupPointCollection)
public:
	typedef CArray<POINT, POINT&> CPointArray;
public:
	CXTPMarkupPointCollection();
	CXTPMarkupPointCollection(CPointArray& arr);

public:
	CRect GetBounds() const;
	const CPointArray& GetPoints() const;

protected:
	CXTPMarkupObject* CXTPMarkupPointCollection::ConvertFrom(CXTPMarkupObject* pObject) const;
	static BOOL AFX_CDECL ConvertFromString(LPCWSTR lpszValue, CPointArray& arr);
	static BOOL AFX_CDECL GetNextValue(LPCWSTR& lpszValue, int& nValue);

protected:
	CPointArray m_arrPoints;
	CRect m_rcBounds;
};

class _XTP_EXT_CLASS CXTPMarkupPolygon : public CXTPMarkupShape
{
	DECLARE_MARKUPCLASS(CXTPMarkupPolygon)

protected:
	CXTPMarkupPolygon();
	~CXTPMarkupPolygon();

public:
	void SetPoints(CXTPMarkupPointCollection* pPoints);
	CXTPMarkupPointCollection* GetPoints() const;

protected:
	CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	void OnRender(CXTPMarkupDrawingContext* pDC);

public:
	static CXTPMarkupDependencyProperty* m_pPointsProperty;

};

class _XTP_EXT_CLASS CXTPMarkupPolyline : public CXTPMarkupShape
{
	DECLARE_MARKUPCLASS(CXTPMarkupPolyline)

protected:
	CXTPMarkupPolyline();
	~CXTPMarkupPolyline();

public:
	void SetPoints(CXTPMarkupPointCollection* pPoints);
	CXTPMarkupPointCollection* GetPoints() const;

protected:
	CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	void OnRender(CXTPMarkupDrawingContext* pDC);

public:
	static CXTPMarkupDependencyProperty* m_pPointsProperty;

};

class _XTP_EXT_CLASS CXTPMarkupRectangle : public CXTPMarkupShape
{
	DECLARE_MARKUPCLASS(CXTPMarkupRectangle)

protected:
	CXTPMarkupRectangle();
	~CXTPMarkupRectangle();

protected:
	CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	void OnRender(CXTPMarkupDrawingContext* pDC);

public:
};

class _XTP_EXT_CLASS CXTPMarkupEllipse : public CXTPMarkupShape
{
	DECLARE_MARKUPCLASS(CXTPMarkupEllipse)

protected:
	CXTPMarkupEllipse();
	~CXTPMarkupEllipse();

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual void OnRender(CXTPMarkupDrawingContext* pDC);

	virtual CXTPMarkupInputElement* InputHitTestOverride(CPoint point) const;

public:
};

class _XTP_EXT_CLASS CXTPMarkupLine : public CXTPMarkupShape
{
	DECLARE_MARKUPCLASS(CXTPMarkupLine)

protected:
	CXTPMarkupLine();
	~CXTPMarkupLine();

public:
	int GetX1() const;
	int GetX2() const;
	int GetY1() const;
	int GetY2() const;

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual void OnRender(CXTPMarkupDrawingContext* pDC);
	virtual CXTPMarkupInputElement* InputHitTestOverride(CPoint point) const;

public:
	static CXTPMarkupDependencyProperty* m_pX1Property;
	static CXTPMarkupDependencyProperty* m_pY1Property;
	static CXTPMarkupDependencyProperty* m_pX2Property;
	static CXTPMarkupDependencyProperty* m_pY2Property;
};


AFX_INLINE CRect CXTPMarkupPointCollection::GetBounds() const {
	return m_rcBounds;
}
AFX_INLINE const CXTPMarkupPointCollection::CPointArray& CXTPMarkupPointCollection::GetPoints() const {
	return m_arrPoints;
}
AFX_INLINE void CXTPMarkupShape::SetStrokeThickness(int nThickness) {
	SetValue(m_pStrokeThicknessProperty, new CXTPMarkupInt(nThickness));
}
AFX_INLINE int CXTPMarkupShape::GetStrokeThickness() const {
	CXTPMarkupInt* pValue =  MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pStrokeThicknessProperty));
	return pValue != NULL ? (int)*pValue : 1;
}
AFX_INLINE XTPMarkupStretch CXTPMarkupShape::GetStretch() const {
	CXTPMarkupEnum* pValue =  MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pStretchProperty));
	return pValue != NULL ? (XTPMarkupStretch)(int)*pValue : xtpMarkupStretchNone;
}


#endif // !defined(__XTPMARKUPSHAPE_H__)
