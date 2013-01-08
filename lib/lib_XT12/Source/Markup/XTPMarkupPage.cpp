// XTPMarkupPage.cpp: implementation of the CXTPMarkupPage class.
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

#include "XTPMarkupPage.h"
#include "XTPMarkupBuilder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_MARKUPCLASS(L"Page", CXTPMarkupPage, CXTPMarkupFrameworkElement);

void CXTPMarkupPage::RegisterMarkupClass()
{

}

CXTPMarkupPage::CXTPMarkupPage()
{
	m_pContent = NULL;

}

CXTPMarkupPage::~CXTPMarkupPage()
{
	SetContent(NULL);
}


CXTPMarkupUIElement* CXTPMarkupPage::GetContent() const
{
	return m_pContent;
}

void CXTPMarkupPage::SetContent(CXTPMarkupUIElement* pContent)
{
	if (m_pContent)
	{
		m_pContent->SetLogicalParent(NULL);
		MARKUP_RELEASE(m_pContent);
	}

	m_pContent = pContent;

	if (m_pContent)
	{
		m_pContent->SetLogicalParent(this);
	}
}


CSize CXTPMarkupPage::MeasureOverride(CXTPMarkupDrawingContext* pDC, CSize szAvailableSize)
{
	if (m_pContent)
	{
		m_pContent->Measure(pDC, szAvailableSize);
		return m_pContent->GetDesiredSize();
	}

	return CSize(0, 0);
}

CSize CXTPMarkupPage::ArrangeOverride(CSize szFinalSize)
{
	if (m_pContent)
	{
		m_pContent->Arrange(CRect(0, 0, szFinalSize.cx, szFinalSize.cy));
	}

	return szFinalSize;
}

void CXTPMarkupPage::SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent)
{
	if (!pContent->IsKindOf(MARKUP_TYPE(CXTPMarkupUIElement)))
	{
		pBuilder->ThrowBuilderException(CXTPMarkupBuilder::FormatString(_T("'%ls' object cannot be added to '%ls'. Object cannot be converted to type 'CXTPMarkupUIElement'"),
			(LPCTSTR)pContent->GetType()->m_lpszClassName, (LPCTSTR)GetType()->m_lpszClassName));
	}

	if (m_pContent != NULL)
	{
		pBuilder->ThrowBuilderException(CXTPMarkupBuilder::FormatString(_T("'%ls' already has a child and cannot add ")
			_T("'%ls'. '%ls' can accept only one child."),
			(LPCTSTR)GetType()->m_lpszClassName, (LPCTSTR)pContent->GetType()->m_lpszClassName, (LPCTSTR)GetType()->m_lpszClassName));
	}


	SetContent((CXTPMarkupUIElement*)pContent);
}

BOOL CXTPMarkupPage::HasContentObject() const
{
	return m_pContent != NULL;
}

CXTPMarkupInputElement* CXTPMarkupPage::InputHitTestOverride(CPoint /*point*/) const
{
	return NULL;
}
