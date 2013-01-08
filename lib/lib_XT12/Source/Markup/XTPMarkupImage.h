// XTPMarkupImage.h: interface for the CXTPMarkupImage class.
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

#if !defined(__XTPMARKUPIMAGE_H__)
#define __XTPMARKUPIMAGE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupFrameworkElement.h"

class CXTPImageManagerIcon;
class CXTPImageManager;

class _XTP_EXT_CLASS CXTPMarkupImage : public CXTPMarkupFrameworkElement
{
	DECLARE_MARKUPCLASS(CXTPMarkupImage)

protected:
	CXTPMarkupImage();
	virtual ~CXTPMarkupImage();

public:
	CSize MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize constraint);
	void OnRender(CXTPMarkupDrawingContext* pDC);

protected:
	void LoadImage();

protected:
	CXTPImageManager* m_pImageManager;
	CXTPImageManagerIcon* m_pImage;

public:
	static CXTPMarkupDependencyProperty* m_pSourceProperty;

};

#endif // !defined(__XTPMARKUPIMAGE_H__)
