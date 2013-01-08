// XTPMarkupDecorator.h: interface for the CXTPMarkupDecorator class.
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

#if !defined(__XTPMARKUPDECORATOR_H__)
#define __XTPMARKUPDECORATOR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPMarkupFrameworkElement.h"

class CXTPMarkupBuilder;

class _XTP_EXT_CLASS CXTPMarkupDecorator : public CXTPMarkupFrameworkElement
{
protected:
	CXTPMarkupDecorator();
	virtual ~CXTPMarkupDecorator();

public:
	CXTPMarkupUIElement* GetChild() const;
	void SetChild(CXTPMarkupUIElement* pChild);

public:
	virtual int GetVisualChildrenCount() const;
	virtual CXTPMarkupVisual* GetVisualChild(int nIndex) const;

protected:
	virtual void SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent);
	virtual BOOL HasContentObject() const;


protected:
	CXTPMarkupUIElement* m_pChild;
};

AFX_INLINE int CXTPMarkupDecorator::GetVisualChildrenCount() const {
	return m_pChild != NULL ? 1 : 0;
}
AFX_INLINE CXTPMarkupVisual* CXTPMarkupDecorator::GetVisualChild(int nIndex) const {
	return nIndex == 0 ? m_pChild : NULL;
}


#endif // !defined(__XTPMARKUPDECORATOR_H__)
