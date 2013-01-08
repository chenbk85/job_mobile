// ExplorerTheme.cpp: implementation of the CExplorerTheme class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExplorerTheme.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExplorerTabPaintManager::CExplorerTabPaintManager()
{
	SetAppearanceSet(new CExplorerTabAppearance());
	SetColor(xtpTabColorWinXP);
	m_bBoldSelected = FALSE;
	m_rcButtonMargin.SetRect(4, 2, 4, 1);
	m_bHotTracking = TRUE;
	m_bFillBackground = FALSE;
	m_szNavigateButton = CSize(17, 16);
}

void CExplorerTabPaintManager::DrawNavigateButton(CDC* pDC, CXTPTabManagerNavigateButton* pButton, CRect& rc)
{
	if (GetColorSet()->IsAppThemed() && pButton->GetID() == xtpTabNavigateButtonClose)
	{
		LPCTSTR lpszImage = pButton->IsPressed() ? _T("IDB_EXPLORERTABCLOSEBUTTONPUSHED") : 
			pButton->IsHighlighted() ? _T("IDB_EXPLORERTABCLOSEBUTTONHOT") : _T("IDB_EXPLORERTABCLOSEBUTTON");

		CXTPOffice2007Image* pImage = ((CExplorerTabAppearance*)GetAppearanceSet())->m_images.LoadFile(lpszImage);
		if (pImage)
		{
			pImage->Premultiply();
			pImage->DrawImage(pDC, rc, pImage->GetSource());
		}

	}
	else
	{
		CXTPTabPaintManager::DrawNavigateButton(pDC, pButton, rc);
	}
}



void CExplorerTabPaintManager::CExplorerTabAppearance::DrawSingleButton(CDC* pDC, CXTPTabManagerItem* pItem)
{
	if (!m_pPaintManager->GetColorSet()->IsAppThemed())
	{
		CAppearanceSetPropertyPage::DrawSingleButton(pDC, pItem);
		return;
	}
	
	CRect rcItem = pItem->GetRect();

	if (pItem->IsSelected())
		rcItem.InflateRect(1, 2, 1, 0);
	else rcItem.InflateRect(0, 0, 1, 0);


	LPCTSTR lpszImage = pItem->IsSelected() ? _T("IDB_EXPLORERTABSELECTED") : 
		pItem->IsHighlighted() ? _T("IDB_EXPLORERTABHOT") : _T("IDB_EXPLORERTABNORMAL");

	CXTPOffice2007Image* pImage = m_images.LoadFile(lpszImage);
	ASSERT(pImage);

	if (pImage)
	{
		pImage->Premultiply();
		pImage->DrawImage(pDC, rcItem, pImage->GetSource(), CRect(3, 3, 3, 3));
	}

	m_pPaintManager->DrawSingleButtonIconAndText(pDC, pItem, rcItem, TRUE);
}
