// XTPMarkupGrid.h: interface for the CXTPMarkupGrid class.
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

#if !defined(__XTPMARKUPGRID_H__)
#define __XTPMARKUPGRID_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupPanel.h"

class CXTPMarkupBuilder;
class CXTPMarkupUIElement;

class _XTP_EXT_CLASS CXTPMarkupGridLength : public CXTPMarkupObject
{
	DECLARE_MARKUPCLASS(CXTPMarkupGridLength);
public:
	enum GridUnitType
	{
		unitTypeAuto,
		unitTypePixel,
		unitTypeStar
	};
public:
	CXTPMarkupGridLength(double nValue = 0, GridUnitType type = unitTypePixel);

	GridUnitType GetUnitType() const;
	double GetValue() const;

	BOOL IsStar() const {
		return m_type == unitTypeStar;
	}

public:
	CXTPMarkupObject* ConvertFrom(CXTPMarkupObject* pObject) const;

public:
	double m_nValue;
	GridUnitType m_type;
};

class _XTP_EXT_CLASS CXTPMarkupDefinitionBase : public CXTPMarkupObject
{
protected:
	CXTPMarkupDefinitionBase(BOOL bIsColumnDefinition);

public:
	int GetUserMinSize() const;
	int GetUserMaxSize() const;
	CXTPMarkupGridLength* GetUserSize() const;

private:
	void OnBeforeLayout();
	void UpdateMinSize(int nMinSize);

protected:
	BOOL m_bIsColumnDefinition;
	int m_nMinSize;
	int m_nSizeType;
	double m_nMeasureSize;
	double m_nSizeCache;
	int m_nFinalOffset;

	friend class CXTPMarkupGrid;
};

class _XTP_EXT_CLASS CXTPMarkupColumnDefinition : public CXTPMarkupDefinitionBase
{
	DECLARE_MARKUPCLASS(CXTPMarkupColumnDefinition);
public:
	CXTPMarkupColumnDefinition();

public:
	void SetMinWidth(int nWidth);
	void SetMaxWidth(int nWidth);
	void SetWidth(int nWidth);

public:
	static CXTPMarkupDependencyProperty* m_pWidthProperty;
	static CXTPMarkupDependencyProperty* m_pMinWidthProperty;
	static CXTPMarkupDependencyProperty* m_pMaxWidthProperty;
};

class _XTP_EXT_CLASS CXTPMarkupRowDefinition : public CXTPMarkupDefinitionBase
{
	DECLARE_MARKUPCLASS(CXTPMarkupRowDefinition);
public:
	CXTPMarkupRowDefinition();

public:
	void SetMinHeight(int nHeight);
	void SetMaxHeight(int nHeight);
	void SetHeight(int nHeight);

public:
	static CXTPMarkupDependencyProperty* m_pHeightProperty;
	static CXTPMarkupDependencyProperty* m_pMinHeightProperty;
	static CXTPMarkupDependencyProperty* m_pMaxHeightProperty;
};

class _XTP_EXT_CLASS CXTPMarkupDefinitionCollection : public CXTPMarkupCollection
{
	DECLARE_MARKUPCLASS(CXTPMarkupDefinitionCollection);
public:
	CXTPMarkupDefinitionCollection();

public:
	CXTPMarkupDefinitionBase* GetItem(int nIndex) const;
};

class _XTP_EXT_CLASS CXTPMarkupRowDefinitionCollection : public CXTPMarkupDefinitionCollection
{
	DECLARE_MARKUPCLASS(CXTPMarkupRowDefinitionCollection);
public:
	CXTPMarkupRowDefinitionCollection();
};

class _XTP_EXT_CLASS CXTPMarkupColumnDefinitionCollection : public CXTPMarkupDefinitionCollection
{
	DECLARE_MARKUPCLASS(CXTPMarkupColumnDefinitionCollection);
public:
	CXTPMarkupColumnDefinitionCollection();
};

class _XTP_EXT_CLASS CXTPMarkupGrid : public CXTPMarkupPanel
{
private:
	enum LayoutTimeSizeType
	{
		sizeTypeNone = 0,
		sizeTypePixel = 1,
		sizeTypeAuto = 2,
		sizeTypeStar = 4
	};

private:
	struct CELLCACHE
	{
		int nColumnIndex;
		int nRowIndex;
		int nColumnSpan;
		int nRowSpan;
		int nSizeTypeU;
		int nSizeTypeV;
		int nNext;
	public:
		BOOL IsStarU() const;
		BOOL IsAutoU() const;
		BOOL IsStarV() const;
		BOOL IsAutoV() const;
	};

private:
	DECLARE_MARKUPCLASS(CXTPMarkupGrid)

protected:
	CXTPMarkupGrid();
	virtual ~CXTPMarkupGrid();

public:
	CXTPMarkupColumnDefinitionCollection* GetColumnDefinitions() const;
	CXTPMarkupRowDefinitionCollection* GetRowDefinitions() const;

	static int AFX_CDECL GetColumn(CXTPMarkupUIElement* pElement);
	static int AFX_CDECL GetRow(CXTPMarkupUIElement* pElement);

	static int AFX_CDECL GetColumnSpan(CXTPMarkupUIElement* pElement);
	static int AFX_CDECL GetRowSpan(CXTPMarkupUIElement* pElement);

	static void AFX_CDECL SetColumn(CXTPMarkupUIElement* pElement, int nColumn);
	static void AFX_CDECL SetRow(CXTPMarkupUIElement* pElement, int nRow);


protected:
	CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize availableSize);
	CSize ArrangeOverride(CSize arrangeSize);
	void SetPropertyObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupDependencyProperty* pProperty, CXTPMarkupObject* pValue);

private:
	void ValidateDefinitionsLayout(CXTPMarkupDefinitionCollection* pDefinitions, BOOL bTreatStarAsAuto);
	void ValidateCells();
	void ValidateDefinitions();
	int GetLengthTypeForRange(CXTPMarkupDefinitionCollection* pDefinitions, int start, int count);
	void MeasureCellsGroup(CXTPMarkupDrawingContext* pDC, int cellsHead, CSize referenceSize, BOOL ignoreDesiredSizeU, BOOL forceInfinityV);
	void MeasureCell(CXTPMarkupDrawingContext* pDC, int cell, BOOL forceInfinityV);
	int GetMeasureSizeForRange(CXTPMarkupDefinitionCollection* pDefinitions, int start, int count);
	int CalculateDesiredSize(CXTPMarkupDefinitionCollection* pDefinitions);
	void ResolveStar(CXTPMarkupDefinitionCollection* pDefinitions, double availableSize);
	int GetFinalSizeForRange(CXTPMarkupDefinitionCollection* pDefinitions, int start, int count);
	void SetFinalSize(CXTPMarkupDefinitionCollection* pDefinitions, int finalSize);
	static int _cdecl DistributionOrderComparer(const void *arg1, const void *arg2);
	static int _cdecl StarDistributionOrderComparer(const void *arg1, const void *arg2);

	static void AFX_CDECL CXTPMarkupGrid::OnCellAttachedPropertyChanged(CXTPMarkupObject* d, CXTPMarkupPropertyChangedEventArgs* e);

protected:
	CXTPMarkupRowDefinitionCollection* m_pRowDefinitions;
	CXTPMarkupColumnDefinitionCollection* m_pColumnDefinitions;

public:
	static CXTPMarkupDependencyProperty* m_pColumnDefinitionsProperty;
	static CXTPMarkupDependencyProperty* m_pRowDefinitionsProperty;
	static CXTPMarkupDependencyProperty* m_pRowProperty;
	static CXTPMarkupDependencyProperty* m_pColumnProperty;

private:
	CELLCACHE* m_pCellCachesCollection;
	int m_nCellGroup[4];
	BOOL m_bHasStarCellsU;
	BOOL m_bHasStarCellsV;
	BOOL m_bHasGroup2CellsInAutoRows;

	CXTPMarkupDefinitionCollection* m_pDefinitionsU;
	CXTPMarkupDefinitionCollection* m_pDefinitionsV;

	friend struct CELLCACHE;
};

AFX_INLINE CXTPMarkupColumnDefinitionCollection* CXTPMarkupGrid::GetColumnDefinitions() const {
	return m_pColumnDefinitions;
}
AFX_INLINE CXTPMarkupRowDefinitionCollection* CXTPMarkupGrid::GetRowDefinitions() const {
	return m_pRowDefinitions;
}
AFX_INLINE CXTPMarkupDefinitionBase* CXTPMarkupDefinitionCollection::GetItem(int nIndex) const {
	return nIndex >= 0 && nIndex < m_arrItems.GetSize() ? (CXTPMarkupDefinitionBase*)m_arrItems[nIndex] : NULL;
}
AFX_INLINE CXTPMarkupGridLength::GridUnitType CXTPMarkupGridLength::GetUnitType() const {
	return m_type;
};
AFX_INLINE double CXTPMarkupGridLength::GetValue() const {
	return m_nValue;
}

AFX_INLINE void CXTPMarkupColumnDefinition::SetMinWidth(int nWidth) {
	SetValue(m_pMinWidthProperty, new CXTPMarkupInt(nWidth));
}
AFX_INLINE void CXTPMarkupColumnDefinition::SetMaxWidth(int nWidth) {
	SetValue(m_pMaxWidthProperty, new CXTPMarkupInt(nWidth));
}
AFX_INLINE void CXTPMarkupColumnDefinition::SetWidth(int nWidth) {
	SetValue(m_pWidthProperty, new CXTPMarkupInt(nWidth));
}
AFX_INLINE void CXTPMarkupRowDefinition::SetMinHeight(int nHeight) {
	SetValue(m_pMinHeightProperty, new CXTPMarkupInt(nHeight));
}
AFX_INLINE void CXTPMarkupRowDefinition::SetMaxHeight(int nHeight) {
	SetValue(m_pMaxHeightProperty, new CXTPMarkupInt(nHeight));
}
AFX_INLINE void CXTPMarkupRowDefinition::SetHeight(int nHeight) {
	SetValue(m_pHeightProperty, new CXTPMarkupInt(nHeight));
}


#endif // !defined(__XTPMARKUPGRID_H__)
