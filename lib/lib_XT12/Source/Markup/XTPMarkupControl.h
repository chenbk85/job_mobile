// XTPMarkupControl.h: interface for the CXTPMarkupControl class.
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

#if !defined(__XTPMARKUPCONTROL_H__)
#define __XTPMARKUPCONTROL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupFrameworkElement.h"

class CXTPMarkupBrush;
class CXTPMarkupBuilder;

class _XTP_EXT_CLASS CXTPMarkupControl : public CXTPMarkupFrameworkElement
{
	DECLARE_MARKUPCLASS(CXTPMarkupControl);

public:
	void SetPadding(int nLeft, int nTop, int nRight, int nBottom);
	void SetPadding(int nPadding);
	CXTPMarkupThickness* GetPadding() const;

protected:
	CSize ArrangeOverride(CSize szFinalSize);
	CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);

public:
	static CXTPMarkupDependencyProperty* m_pPaddingProperty;
	static CXTPMarkupDependencyProperty* m_pBackgroundProperty;
	static CXTPMarkupDependencyProperty* m_pForegroundProperty;
};

class _XTP_EXT_CLASS CXTPMarkupContentControl : public CXTPMarkupControl
{
	DECLARE_MARKUPCLASS(CXTPMarkupContentControl);
protected:
	CXTPMarkupContentControl();
	~CXTPMarkupContentControl();
public:
	CXTPMarkupUIElement* GetContent() const;
	void SetContent(CXTPMarkupUIElement* pContent);

public:
	virtual int GetVisualChildrenCount() const;
	virtual CXTPMarkupVisual* GetVisualChild(int nIndex) const;

protected:
	virtual void SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent);
	virtual BOOL HasContentObject() const;

protected:
	static CXTPMarkupDependencyProperty* m_pContentProperty;
};


AFX_INLINE void CXTPMarkupControl::SetPadding(int nLeft, int nTop, int nRight, int nBottom) {
	SetValue(m_pPaddingProperty, new CXTPMarkupThickness(nLeft, nTop, nRight, nBottom));
}
AFX_INLINE void CXTPMarkupControl::SetPadding(int padding) {
	SetValue(m_pPaddingProperty, new CXTPMarkupThickness(padding));
}
AFX_INLINE CXTPMarkupThickness* CXTPMarkupControl::GetPadding() const {
	return  MARKUP_STATICCAST(CXTPMarkupThickness, GetValue(m_pPaddingProperty));
}
AFX_INLINE int CXTPMarkupContentControl::GetVisualChildrenCount() const {
	return GetContent() != NULL ? 1 : 0;
}
AFX_INLINE CXTPMarkupVisual* CXTPMarkupContentControl::GetVisualChild(int nIndex) const {
	return nIndex == 0 ? GetContent() : NULL;
}

#endif // !defined(__XTPMARKUPCONTROL_H__)
