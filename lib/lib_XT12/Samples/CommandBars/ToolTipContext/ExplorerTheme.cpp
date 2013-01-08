// ExplorerTheme.cpp: implementation of the CExplorerTheme class.
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
#include "ExplorerTheme.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExplorerTheme::CExplorerTheme()
{
	m_bSelectImageInPopupBar = TRUE;
	m_bThickCheckMark = TRUE;

	RefreshMetrics();
}

CExplorerTheme::~CExplorerTheme()
{

}

void CExplorerTheme::RefreshMetrics()
{
	CXTPNativeXPTheme::RefreshMetrics();

	m_bLunaTheme = FALSE;

	switch (XTPColorManager()->GetCurrentSystemTheme())
	{	
		case xtpSystemThemeBlue:
			m_clrPopupBarBorder = RGB(64, 134, 228);
			m_clrPopupBarGripperShadow = RGB(136, 181, 237);

			m_bLunaTheme = TRUE;
			break;

		case xtpSystemThemeOlive:
			m_clrPopupBarBorder = RGB(142, 152, 102);
			m_clrPopupBarGripperShadow = RGB(181, 187, 159);

			m_bLunaTheme = TRUE;
			break;
		
		case xtpSystemThemeSilver:
			m_clrPopupBarBorder = RGB(166, 167, 193);
			m_clrPopupBarGripperShadow = RGB(226, 226, 225);

			m_bLunaTheme = TRUE;
			break;
	}
}

CRect CExplorerTheme::GetCommandBarBorders(CXTPCommandBar* pBar)
{
	if (m_bLunaTheme)
	{	
		if (pBar->GetType() == xtpBarTypePopup)
			return CRect(6, 1, 1, 1);

		if (pBar->GetType() == xtpBarTypeMenuBar)
			return CRect(1, 0, 1, 1);
	}

	return CXTPNativeXPTheme::GetCommandBarBorders(pBar);
}


void CExplorerTheme::FillCommandBarEntry(CDC* pDC, CXTPCommandBar* pBar)
{
	
	if (pBar->GetPosition() == xtpBarPopup && m_bLunaTheme)
	{
		CRect rc;
		pBar->GetClientRect(&rc);

		pDC->FillSolidRect(rc, GetXtremeColor(COLOR_MENU));
		pDC->Draw3dRect(rc, m_clrPopupBarBorder,  m_clrPopupBarBorder);
		
		if (pBar->GetType() == xtpBarTypePopup)
		{
			pDC->FillSolidRect(rc.left, rc.top, 6, rc.Height(), m_clrPopupBarBorder);
			pDC->FillSolidRect(rc.left + 1, rc.top + 1, 1, rc.Height() - 2, m_clrPopupBarGripperShadow);
		}
	}
	else
	{
		CXTPNativeXPTheme::FillCommandBarEntry(pDC, pBar);
	}
}


void CExplorerTheme::AdjustExcludeRect(CRect& rc, CXTPControl* pControl, BOOL bVertical)
{
	if (!m_bLunaTheme)
	{
		CXTPNativeXPTheme::AdjustExcludeRect(rc, pControl, bVertical);
	}

}

COLORREF CExplorerTheme::GetControlTextColor(CXTPControl* pButton)
{
	if (m_bLunaTheme && pButton->GetType() == xtpControlPopup && pButton->GetParent()->GetType() == xtpBarTypeMenuBar)
	{
		return pButton->GetSelected()? GetXtremeColor(COLOR_HIGHLIGHTTEXT): GetXtremeColor(COLOR_BTNTEXT);
	}
	
	return CXTPNativeXPTheme::GetControlTextColor(pButton);
}

void CExplorerTheme::DrawControlEntry(CDC* pDC, CXTPControl* pButton)
{
	if (m_bLunaTheme && pButton->GetType() == xtpControlPopup && pButton->GetParent()->GetType() == xtpBarTypeMenuBar)
	{
		pDC->SetBkMode(TRANSPARENT);

		if (pButton->GetSelected())
			pDC->FillSolidRect(pButton->GetRect(), GetXtremeColor(COLOR_HIGHLIGHT));
	}
	else
	{	
		CXTPNativeXPTheme::DrawControlEntry(pDC, pButton);
	}

}

