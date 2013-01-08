// AlphaIconsPage.cpp : implementation file
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
#include "resource.h"
#include "TabClientPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabManagerPage dialog


CTabManagerPage::CTabManagerPage()
	: CXTPPropertyPage(CTabManagerPage::IDD)
{
	//{{AFX_DATA_INIT(CTabManagerPage)
	m_nAppearance = xtpTabAppearancePropertyPage2003;
	m_nColor = -1;
	m_nLayout = -1;
	m_nPosition = -1;
	m_bFillBackground = FALSE;
	m_bBoldSelected = TRUE;
	m_bLunaColors = TRUE;
	m_bOneNoteColors = TRUE;
	m_bHotTracking = FALSE;
	m_bShowIcons = FALSE;
	m_nArrows = -1;
	m_nClose = -1;
	m_bShowStaticFrame = FALSE;
	m_nClientFrame = -1;
	m_bAllowReorder = TRUE;
	m_bMultiRowFixedSelection = FALSE;
	m_bMultiRowJustified = FALSE;
	//}}AFX_DATA_INIT


	m_bShowIcons = TRUE;
}


void CTabManagerPage::DoDataExchange(CDataExchange* pDX)
{
	CXTPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabManagerPage)
	DDX_Control(pDX, IDC_COMBO_APPEARANCE, m_comboAppearance);
	DDX_Control(pDX, IDC_COMBO_POSITION, m_comboPosition);
	DDX_Control(pDX, IDC_COMBO_COLOR, m_comboColor);
	DDX_CBIndex(pDX, IDC_COMBO_APPEARANCE, m_nAppearance);
	DDX_CBIndex(pDX, IDC_COMBO_COLOR, m_nColor);
	DDX_CBIndex(pDX, IDC_COMBO_LAYOUT, m_nLayout);
	DDX_CBIndex(pDX, IDC_COMBO_POSITION, m_nPosition);
	DDX_Check(pDX, IDC_CHECK_BOLD_SELECTED, m_bBoldSelected);
	DDX_Check(pDX, IDC_CHECK_LUNA_COLORS, m_bLunaColors);
	DDX_Check(pDX, IDC_CHECK_ONENOTE_COLORS, m_bOneNoteColors);
	DDX_Check(pDX, IDC_CHECK_HOTTRACKING, m_bHotTracking);
	DDX_Check(pDX, IDC_CHECK_ICONS, m_bShowIcons);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabManagerPage, CXTPPropertyPage)
	//{{AFX_MSG_MAP(CTabManagerPage)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOR, OnSelchangeComboColor)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITION, OnSelchangeComboPosition)
	ON_CBN_SELCHANGE(IDC_COMBO_APPEARANCE, OnSelchangeComboAppearance)
	ON_BN_CLICKED(IDC_CHECK_BOLD_SELECTED, OnCheckBoldSelected)
	ON_BN_CLICKED(IDC_CHECK_LUNA_COLORS, OnCheckLunaColors)
	ON_BN_CLICKED(IDC_CHECK_ONENOTE_COLORS, OnCheckOnenoteColors)
	ON_BN_CLICKED(IDC_CHECK_HOTTRACKING, OnCheckHottracking)
	ON_BN_CLICKED(IDC_CHECK_ICONS, OnCheckIcons)
	ON_CBN_SELCHANGE(IDC_COMBO_LAYOUT, OnSelchangeComboLayout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTabManagerPage message handlers

BOOL CTabManagerPage::OnInitDialog()
{
	CXTPPropertyPage::OnInitDialog();

	// Initialize OneNote style tabs.
	//GetPaintManager()->SetAppearance((XTPTabAppearanceStyle)m_nAppearance);
	//GetPaintManager()->DisableLunaColors(!m_bLunaColors);
	//GetPaintManager()->SetOneNoteColors(m_bOneNoteColors);

	Update();

	m_comboPosition.SetItemData(0, xtpTabPositionTop);
	m_comboPosition.SetItemData(1, xtpTabPositionLeft);
	m_comboPosition.SetItemData(2, xtpTabPositionBottom);
	m_comboPosition.SetItemData(3, xtpTabPositionRight);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTabManagerPage::Update()
{
	m_nAppearance = GetPaintManager()->GetAppearance();
	m_nColor = 1;
	m_bFillBackground = GetPaintManager()->m_bFillBackground;
	m_nLayout = GetPaintManager()->GetLayout();
	m_nPosition = GetPaintManager()->GetPosition();
	m_bBoldSelected = GetPaintManager()->m_bBoldSelected;
	m_bLunaColors = !GetPaintManager()->IsLunaColorsDisabled();
	m_bOneNoteColors = GetPaintManager()->m_bOneNoteColors;

	m_bHotTracking = GetPaintManager()->m_bHotTracking;
	m_bShowStaticFrame = GetPaintManager()->m_bStaticFrame;

	CXTPTabManager* pManager = GetManager();
	if (pManager)
	{
		m_nArrows = pManager->FindNavigateButton(xtpTabNavigateButtonLeft)->GetFlags();
		m_nClose = pManager->FindNavigateButton(xtpTabNavigateButtonClose)->GetFlags();
	}

	m_nClientFrame = GetPaintManager()->m_clientFrame;

	m_bMultiRowFixedSelection = GetPaintManager()->m_bMultiRowFixedSelection;
	m_bMultiRowJustified = GetPaintManager()->m_bMultiRowJustified;

	UpdateData(FALSE);

	UpdateControls();

}

void CTabManagerPage::OnCancel()
{

}

void CTabManagerPage::OnSelchangeComboColor()
{
	UpdateData();

	XTPTabColorStyle color = (XTPTabColorStyle)m_comboColor.GetItemData(m_nColor);

	GetPaintManager()->SetColor(color);

	UpdateControls();
	Reposition();

}

void CTabManagerPage::OnSelchangeComboPosition()
{
	UpdateData();

	XTPTabPosition position = (XTPTabPosition)m_comboPosition.GetItemData(m_nPosition);

	GetPaintManager()->SetPosition(position);
	Reposition();

}

void CTabManagerPage::OnSelchangeComboAppearance()
{
	UpdateData();
	GetPaintManager()->SetAppearance((XTPTabAppearanceStyle)m_nAppearance);

	UpdateControls();
	Reposition();
}

void CTabManagerPage::OnSelchangeComboLayout()
{
	UpdateData();
	GetPaintManager()->SetLayout((XTPTabLayoutStyle)m_nLayout);

	UpdateControls();
	Reposition();

}

void CTabManagerPage::OnSelchangeComboArrows()
{
	UpdateData();

	CXTPTabManager* pManager = GetManager();
	if (pManager)
	{
		pManager->FindNavigateButton(xtpTabNavigateButtonLeft)->SetFlags((XTPTabNavigateButtonFlags)m_nArrows);
		pManager->FindNavigateButton(xtpTabNavigateButtonRight)->SetFlags((XTPTabNavigateButtonFlags)m_nArrows);
	}

	Reposition();

}

void CTabManagerPage::OnSelchangeComboClose()
{
	UpdateData();

	CXTPTabManager* pManager = GetManager();
	if (pManager)
	{
		pManager->FindNavigateButton(xtpTabNavigateButtonClose)->SetFlags((XTPTabNavigateButtonFlags)m_nClose);
	}

	Reposition();
}

void CTabManagerPage::OnSelchangeComboClientFrame()
{
	UpdateData();
	GetPaintManager()->m_clientFrame = (XTPTabClientFrame)m_nClientFrame;
	Reposition();
}




void CTabManagerPage::UpdateControls()
{

	const struct
	{
		int nColorSet;
		LPCTSTR strColorSet;
	}
	colors[] =
	{
		xtpTabColorDefault, _T("xtpTabColorDefault"),
		xtpTabColorVisualStudio, _T("xtpTabColorVisualStudio"),
		xtpTabColorOffice2003, _T("xtpTabColorOffice2003"),
		xtpTabColorWinXP, _T("xtpTabColorWinXP"),
		xtpTabColorWhidbey, _T("xtpTabColorWhidbey")
	};

	int nSupported = GetPaintManager()->GetAppearanceSet()->GetSupportedColorSets();

	m_comboColor.ResetContent();

	for (int i = 0; i < 5; i++)
	{
		if (nSupported & colors[i].nColorSet)
		{
			int nItem = m_comboColor.AddString(colors[i].strColorSet);
			m_comboColor.SetItemData(nItem, colors[i].nColorSet);
			if (GetPaintManager()->GetColor() == colors[i].nColorSet)
			{
				m_nColor = nItem;
				m_comboColor.SetCurSel(nItem);
			}

		}
	}
	GetDlgItem(IDC_CHECK_LUNA_COLORS)->EnableWindow((m_comboColor.GetItemData(m_nColor) & (xtpTabColorOffice2003|xtpTabColorWhidbey)) != 0);
	GetDlgItem(IDC_CHECK_ONENOTE_COLORS)->EnableWindow(m_comboColor.GetItemData(m_nColor) != xtpTabColorWinXP);
}

void CTabManagerPage::OnCheckBoldSelected()
{
	UpdateData();

	GetPaintManager()->m_bBoldSelected = m_bBoldSelected;

	Reposition();

}

void CTabManagerPage::OnCheckLunaColors()
{
	UpdateData();
	GetPaintManager()->DisableLunaColors(!m_bLunaColors);
	Reposition();
}

void CTabManagerPage::OnCheckOnenoteColors()
{
	UpdateData();
	GetPaintManager()->SetOneNoteColors(m_bOneNoteColors);
	Reposition();
}

void CTabManagerPage::OnCheckHottracking()
{
	UpdateData();

	GetPaintManager()->m_bHotTracking = m_bHotTracking;

	Reposition();

}

void CTabManagerPage::OnCheckIcons()
{
	UpdateData();
	GetPaintManager()->m_bShowIcons = m_bShowIcons;

	Reposition();	
}


void CTabManagerPage::OnCheckStaticFrame()
{
	UpdateData();

	GetPaintManager()->m_bStaticFrame = m_bShowStaticFrame;
	Reposition();
}

void CTabManagerPage::OnCheckAllowReorder()
{
	UpdateData();
	if (GetManager())
		GetManager()->SetAllowReorder(m_bAllowReorder);
}

void CTabManagerPage::OnCheckFixedSelection() 
{
	UpdateData();
	GetPaintManager()->m_bMultiRowFixedSelection = m_bMultiRowFixedSelection;
	Reposition();	
}

void CTabManagerPage::OnCheckBackground()
{
	UpdateData();
	GetPaintManager()->m_bFillBackground = m_bFillBackground;	
	Reposition();
}


void CTabManagerPage::OnCheckJustified() 
{
	UpdateData();
	GetPaintManager()->m_bMultiRowJustified = m_bMultiRowJustified;	
	Reposition();
}

//////////////////////////////////////////////////////////////////////////
// CTabControlPage

CTabControlPage::CTabControlPage()
{
	m_bShowIcons = FALSE;
	m_bAllowReorder = FALSE;
}

CXTPTabManager* CTabControlPage::GetManager()
{
	CXTPPropertyPageNavigator* pNavigator = m_pSheet->GetNavigator();

	return (CXTPPropertyPageTabNavigator*)pNavigator;
}

void CTabControlPage::Reposition()
{
	GetManager()->Reposition();
	m_pSheet->RecalcLayout();
	m_pSheet->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_ALLCHILDREN| RDW_ERASE);
}


