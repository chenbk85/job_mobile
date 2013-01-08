// XTPMarkupTextBlock.h: interface for the CXTPMarkupTextBlock class.
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

#if !defined(__XTPMARKUPTEXTBLOCK_H__)
#define __XTPMARKUPTEXTBLOCK_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupFrameworkElement.h"

class CXTPMarkupBrush;
class CXTPMarkupInlineCollection;
class CXTPMarkupInline;
class CXTPMarkupDrawingContext;

enum XTPMarkupTextTrimming
{
	xtpMarkupTextTrimmingNone,
	xtpMarkupTextTrimmingCharacterEllipsis,
	xtpMarkupTextTrimmingWordEllipsis,

};

class _XTP_EXT_CLASS CXTPMarkupTextBlock : public CXTPMarkupFrameworkElement
{
	DECLARE_MARKUPCLASS(CXTPMarkupTextBlock)

private:
	struct CLine;
	struct CLineIterator;
	struct CLinePart;
	class CLinePartList;
	class CLineList;

protected:
	CXTPMarkupTextBlock();
	virtual ~CXTPMarkupTextBlock();

public:
	void SetText(LPCWSTR lpszText);
	CString GetText() const;

	CXTPMarkupInlineCollection* GetInlines() const;

	void SetBackground(CXTPMarkupBrush* brush);
	CXTPMarkupBrush* GetBackground() const;

	void SetForeground(CXTPMarkupBrush* brush);
	CXTPMarkupBrush* GetForeground() const;

	void SetTextAlignment(XTPMarkupTextAlignment alignment);
	XTPMarkupTextAlignment GetTextAlignment() const;

	void SetTextWrapping(BOOL bTextWrapping);
	BOOL GetTextWrapping() const;

	void SetTextTrimming(XTPMarkupTextTrimming bTextTrimming);
	XTPMarkupTextTrimming GetTextTrimming() const;

	void SetPadding(int nLeft, int nTop, int nRight, int nBottom);
	void SetPadding(int nPadding);
	CXTPMarkupThickness* GetPadding() const;

	void SetFontSize(int nFontSize);
	int GetFontSize() const;

	void SetFontWeight(int nFontWeight);
	int GetFontWeight() const;

	void SetFontFamily(LPCWSTR lpszFontFamily);
	LPCWSTR GetFontFamily() const;

	void SetFontStyle(int nFontStyle);
	int GetFontStyle() const;

	void SetTextDecorations(int nTextDecorations);
	int GetTextDecorations() const;

public:
	CXTPMarkupInline* GetFirstInline() const;

public:
	virtual void SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent);
	virtual BOOL HasContentObject() const;

protected:
	virtual CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize);
	virtual CSize ArrangeOverride(CSize szFinal);
	virtual void OnRender(CXTPMarkupDrawingContext* pDC);

	virtual BOOL AllowWhiteSpaceContent() const;
	virtual void OnPropertyChanged(CXTPMarkupDependencyProperty* pProperty, CXTPMarkupObject* pOldValue, CXTPMarkupObject* pNewValue);

	virtual int GetLogicalChildrenCount() const;
	virtual CXTPMarkupObject* GetLogicalChild(int nIndex) const;

	CXTPMarkupInputElement* InputHitTestOverride(CPoint point) const;

	void InvalidateMeasureOverride(CXTPMarkupDrawingContext* pDC);


private:
	void RemoveAllLines();

	void CloseLine(CLineIterator& li, int nWidth);
	void TrimLine(CLineIterator& li, int nWidth);
	void PushLinePart(CLineIterator& li, int nWidth, BOOL bAddToStack = TRUE);

	void CalculateLines(CXTPMarkupDrawingContext* pDC, int nWidth);

	void RenderTextDecorations(CXTPMarkupDrawingContext* pDC, CLinePart* part);
	int GetStackWidth(CLineIterator& li) const;

protected:
	CXTPMarkupInlineCollection* m_pInlines;

public:
	static CXTPMarkupDependencyProperty* m_pBackgroundProperty;
	static CXTPMarkupDependencyProperty* m_pForegroundProperty;
	static CXTPMarkupDependencyProperty* m_pTextWrappingProperty;
	static CXTPMarkupDependencyProperty* m_pTextTrimmingProperty;
	static CXTPMarkupDependencyProperty* m_pTextAlignmentProperty;
	static CXTPMarkupDependencyProperty* m_pTextDecorationsProperty;
	static CXTPMarkupDependencyProperty* m_pFontSizeProperty;
	static CXTPMarkupDependencyProperty* m_pFontWeightProperty;
	static CXTPMarkupDependencyProperty* m_pFontFamilyProperty;
	static CXTPMarkupDependencyProperty* m_pFontStyleProperty;
	static CXTPMarkupDependencyProperty* m_pPaddingProperty;
	static CXTPMarkupDependencyProperty* m_pTextProperty;
	static CXTPMarkupDependencyProperty* m_pFontQualityProperty;

private:
	CLineList* m_pLineList;
	int m_nLastWidth;
	CSize m_szBlockSize;
};

AFX_INLINE CXTPMarkupInlineCollection* CXTPMarkupTextBlock::GetInlines() const {
	return m_pInlines;
}
AFX_INLINE void CXTPMarkupTextBlock::SetTextWrapping(BOOL bTextWrapping) {
	SetValue(m_pTextWrappingProperty, CXTPMarkupEnum::CreateValue(bTextWrapping ? 1 : 0));
}
AFX_INLINE BOOL CXTPMarkupTextBlock::GetTextWrapping() const {
	CXTPMarkupEnum* pTextWrapping = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pTextWrappingProperty));
	return pTextWrapping != NULL ? (BOOL)*pTextWrapping : (BOOL)FALSE;
}
AFX_INLINE void CXTPMarkupTextBlock::SetTextTrimming(XTPMarkupTextTrimming bTextTrimming) {
	SetValue(m_pTextTrimmingProperty, CXTPMarkupEnum::CreateValue(bTextTrimming));
}
AFX_INLINE XTPMarkupTextTrimming CXTPMarkupTextBlock::GetTextTrimming() const {
	CXTPMarkupEnum* pTextTrimming = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pTextTrimmingProperty));
	return pTextTrimming != NULL ? (XTPMarkupTextTrimming)(int)*pTextTrimming : (XTPMarkupTextTrimming)xtpMarkupTextTrimmingNone;
}
AFX_INLINE void CXTPMarkupTextBlock::SetPadding(int nLeft, int nTop, int nRight, int nBottom) {
	SetValue(m_pPaddingProperty, new CXTPMarkupThickness(nLeft, nTop, nRight, nBottom));
}
AFX_INLINE void CXTPMarkupTextBlock::SetPadding(int padding) {
	SetValue(m_pPaddingProperty, new CXTPMarkupThickness(padding));
}
AFX_INLINE CXTPMarkupThickness* CXTPMarkupTextBlock::GetPadding() const {
	return  MARKUP_STATICCAST(CXTPMarkupThickness, GetValue(m_pPaddingProperty));
}
AFX_INLINE int CXTPMarkupTextBlock::GetLogicalChildrenCount() const {
	return m_pInlines != NULL ? 1 : 0;
}
AFX_INLINE CXTPMarkupObject* CXTPMarkupTextBlock::GetLogicalChild(int nIndex) const {
	return nIndex == 0 ? (CXTPMarkupObject*)m_pInlines : NULL;
}


#endif // !defined(__XTPMARKUPTEXTBLOCK_H__)
