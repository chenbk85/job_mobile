// XTPMarkupImage.cpp: implementation of the CXTPMarkupImage class.
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

#include "Common/XTPImageManager.h"

#include "XTPMarkupImage.h"
#include "XTPMarkupDrawingContext.h"
#include "XTPMarkupContext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXTPMarkupDependencyProperty* CXTPMarkupImage::m_pSourceProperty = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_MARKUPCLASS(L"Image", CXTPMarkupImage, CXTPMarkupFrameworkElement)

void CXTPMarkupImage::RegisterMarkupClass()
{
	m_pSourceProperty = CXTPMarkupDependencyProperty::Register(L"Source", MARKUP_TYPE(CXTPMarkupString), MARKUP_TYPE(CXTPMarkupImage),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));
}

CXTPMarkupImage::CXTPMarkupImage()
{
	m_pImageManager = NULL;
	m_pImage = NULL;

}

CXTPMarkupImage::~CXTPMarkupImage()
{
	CMDTARGET_RELEASE(m_pImage);
	CMDTARGET_RELEASE(m_pImageManager);
}

void CXTPMarkupImage::LoadImage()
{
	CXTPMarkupString* pSource = MARKUP_STATICCAST(CXTPMarkupString, GetValue(m_pSourceProperty));
	if (!pSource)
		return;

	CMDTARGET_RELEASE(m_pImageManager);
	CMDTARGET_RELEASE(m_pImage);

	LPCWSTR lpszSource = (*pSource);
	if (wcsncmp(lpszSource, L"file://", 7) == 0)
	{
		CString strFileName(lpszSource + 7);

		m_pImageManager = new CXTPImageManager();
		m_pImageManager->SetMaskColor(0x00FF00);

		BOOL bAlphaBitmap = FALSE;
		HBITMAP hBitmap = CXTPImageManagerIcon::LoadBitmapFromFile(strFileName, &bAlphaBitmap);

		if (hBitmap)
		{
			CBitmap bmp;
			bmp.Attach(hBitmap),
			m_pImageManager->SetIcons(bmp, 0, 1, 0, xtpImageNormal, bAlphaBitmap);
		}
		m_pImage = m_pImageManager->GetImage(0, 0);
		CMDTARGET_ADDREF(m_pImage);
	}
	else if (wcsncmp(lpszSource, L"res://", 6) == 0)
	{
		CString strResourceName(lpszSource + 6);

		m_pImageManager = new CXTPImageManager();
		m_pImageManager->SetMaskColor(0x00FF00);

		BOOL bAlphaBitmap = FALSE;
		HBITMAP hBitmap = CXTPImageManagerIcon::LoadBitmapFromResource(AfxGetInstanceHandle(), strResourceName, &bAlphaBitmap);
		if (hBitmap)
		{
			CBitmap bmp;
			bmp.Attach(hBitmap),
			m_pImageManager->SetIcons(bmp, 0, 1, 0, xtpImageNormal, bAlphaBitmap);
		}
		else
		{
			m_pImageManager->SetIcon(strResourceName, 0);
		}

		m_pImage = m_pImageManager->GetImage(0, 0);
		CMDTARGET_ADDREF(m_pImage);
	}
	else
	{
		int nIndex = _wtoi(lpszSource);
		if (nIndex > 0)
		{
			m_pImageManager = m_pMarkupContext->m_pImageManager ? m_pMarkupContext->m_pImageManager : XTPImageManager();
			CMDTARGET_ADDREF(m_pImageManager);

			m_pImage = m_pImageManager->GetImage(nIndex, 0);
			CMDTARGET_ADDREF(m_pImage);
		}
	}
}

CSize CXTPMarkupImage::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize /*constraint*/)
{
	LoadImage();

	if (!m_pImage)
		return CSize(0, 0);

	return CSize(m_pImage->GetWidth(), m_pImage->GetHeight());
}

void CXTPMarkupImage::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CSize szRender = GetRenderSize();

	if (!m_pImage)
		return;

	m_pImage->Draw(CDC::FromHandle(pDC->GetSafeHdc()), CPoint(0, 0), szRender);
}
