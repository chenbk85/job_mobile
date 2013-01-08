// XTPMarkupFrameworkElement.h: interface for the CXTPMarkupFrameworkElement class.
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

#if !defined(__XTPMARKUPFRAMEWORKELEMENT_H__)
#define __XTPMARKUPFRAMEWORKELEMENT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupUIElement.h"

class CXTPMarkupResourceDictionary;
class CXTPMarkupStyle;
class CXTPMarkupTriggerCollection;

class _XTP_EXT_CLASS CXTPMarkupFrameworkElement : public CXTPMarkupUIElement
{
private:
	struct MINMAX
	{
	public:
		MINMAX();
		void Update(const CXTPMarkupFrameworkElement* pElement);

	public:
		int nMaxHeight;
		int nMinHeight;
		int nMaxWidth;
		int nMinWidth;
	};

private:
	DECLARE_MARKUPCLASS(CXTPMarkupFrameworkElement)

protected:
	CXTPMarkupFrameworkElement();
	virtual ~CXTPMarkupFrameworkElement();

public:
	void SetMargin(int nLeft, int nTop, int nRight, int nBottom);
	void SetMargin(int nMargin);
	CXTPMarkupThickness* GetMargin() const;

	void SetMinWidth(int nWidth);
	void SetMaxWidth(int nWidth);
	void SetWidth(int nWidth);

	void SetMinHeight(int nHeight);
	void SetMaxHeight(int nHeight);
	void SetHeight(int nHeight);

	int GetMinWidth() const;
	int GetMaxWidth() const;
	int GetWidth() const;
	int GetMinHeight() const;
	int GetMaxHeight() const;
	int GetHeight() const;

	CXTPMarkupObject* GetTag() const;
	void SetTag(CXTPMarkupObject* pTag);

	void SetHorizontalAlignment(XTPMarkupHorizontalAlignment alignment);
	void SetVerticalAlignment(XTPMarkupVerticalAlignment alignment);

	XTPMarkupHorizontalAlignment GetHorizontalAlignment() const;
	XTPMarkupVerticalAlignment GetVerticalAlignment() const;

	CSize GetActualSize() const;

	BOOL GetClipToBounds() const;

	CXTPMarkupStyle* GetStyle() const;

protected:
	virtual CSize MeasureCore(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);

	virtual void ArrangeCore(CRect rcFinalRect);
	virtual CSize ArrangeOverride(CSize szFinalSize);

	BOOL GetLayoutClip(CRect& rc) const;
	virtual void OnPropertyChanged(CXTPMarkupDependencyProperty* pProperty, CXTPMarkupObject* pOldValue, CXTPMarkupObject* pNewValue);

private:
	CPoint ComputeAlignmentOffset(CSize clientSize, CSize inkSize) const;

protected:
	BOOL m_bNeedsClipBounds;

	CSize m_szUnclippedDesiredSize;
	BOOL m_bUnclippedDesiredSize;

	MINMAX m_mmBounds;

public:
	static CXTPMarkupDependencyProperty* m_pMarginProperty;
	static CXTPMarkupDependencyProperty* m_pHorizontalAlignmentProperty;
	static CXTPMarkupDependencyProperty* m_pVerticalAlignmentProperty;
	static CXTPMarkupDependencyProperty* m_pWidthProperty;
	static CXTPMarkupDependencyProperty* m_pHeightProperty;
	static CXTPMarkupDependencyProperty* m_pMinWidthProperty;
	static CXTPMarkupDependencyProperty* m_pMinHeightProperty;
	static CXTPMarkupDependencyProperty* m_pMaxWidthProperty;
	static CXTPMarkupDependencyProperty* m_pMaxHeightProperty;
	static CXTPMarkupDependencyProperty* m_pTagProperty;
};

AFX_INLINE void CXTPMarkupFrameworkElement::SetMargin(int nLeft, int nTop, int nRight, int nBottom) {
	SetValue(m_pMarginProperty, new CXTPMarkupThickness(nLeft, nTop, nRight, nBottom));
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetMargin(int nMargin) {
	SetValue(m_pMarginProperty, new CXTPMarkupThickness(nMargin));
}
AFX_INLINE CXTPMarkupThickness* CXTPMarkupFrameworkElement::GetMargin() const {
	return MARKUP_STATICCAST(CXTPMarkupThickness, GetValue(m_pMarginProperty));
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetMinWidth(int nWidth) {
	SetValue(m_pMinWidthProperty, new CXTPMarkupInt(nWidth));
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetMaxWidth(int nWidth) {
	SetValue(m_pMaxWidthProperty, new CXTPMarkupInt(nWidth));
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetWidth(int nWidth) {
	SetValue(m_pWidthProperty, new CXTPMarkupInt(nWidth));
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetMinHeight(int nHeight) {
	SetValue(m_pMinHeightProperty, new CXTPMarkupInt(nHeight));
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetMaxHeight(int nHeight) {
	SetValue(m_pMaxHeightProperty, new CXTPMarkupInt(nHeight));
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetHeight(int nHeight) {
	SetValue(m_pHeightProperty, new CXTPMarkupInt(nHeight));
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetHorizontalAlignment(XTPMarkupHorizontalAlignment alignment) {
	SetValue(m_pHorizontalAlignmentProperty, CXTPMarkupEnum::CreateValue(alignment));
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetVerticalAlignment(XTPMarkupVerticalAlignment alignment) {
	SetValue(m_pVerticalAlignmentProperty, CXTPMarkupEnum::CreateValue(alignment));
}
AFX_INLINE CSize CXTPMarkupFrameworkElement::GetActualSize() const {
	return m_szRenderSize;
}
AFX_INLINE int CXTPMarkupFrameworkElement::GetMinWidth() const {
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pMinWidthProperty));
	return pValue != NULL ? (int)*pValue : 0;
}
AFX_INLINE int CXTPMarkupFrameworkElement::GetMaxWidth() const {
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pMaxWidthProperty));
	return pValue != NULL ? (int)*pValue : INT_MAX;
}
AFX_INLINE int CXTPMarkupFrameworkElement::GetWidth() const {
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pWidthProperty));
	return pValue != NULL ? (int)*pValue : 0;
}
AFX_INLINE int CXTPMarkupFrameworkElement::GetMinHeight() const {
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pMinHeightProperty));
	return pValue != NULL ? (int)*pValue : 0;
}
AFX_INLINE int CXTPMarkupFrameworkElement::GetMaxHeight() const {
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pMaxHeightProperty));
	return pValue != NULL ? (int)*pValue : INT_MAX;
}
AFX_INLINE int CXTPMarkupFrameworkElement::GetHeight() const {
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pHeightProperty));
	return pValue != NULL ? (int)*pValue : 0;
}
AFX_INLINE void CXTPMarkupFrameworkElement::SetTag(CXTPMarkupObject* pTag) {
	SetValue(m_pTagProperty, pTag);
}
AFX_INLINE CXTPMarkupObject* CXTPMarkupFrameworkElement::GetTag() const {
	return GetValue(m_pTagProperty);
}
AFX_INLINE CXTPMarkupStyle* CXTPMarkupFrameworkElement::GetStyle() const {
	return m_pStyleCache;
}


#endif // !defined(__XTPMARKUPFRAMEWORKELEMENT_H__)
