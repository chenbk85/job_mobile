// PropertiesDialog.cpp : implementation file
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
#include "PropertiesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDialog dialog


CPropertiesDialog::CPropertiesDialog(CWnd* pParent /*=NULL*/)
	: CXTPPropertySheet(IDD_DIALOG_PROPERTIES, pParent)
{
	m_pageTabClient.SetCaption( _T("TabWorkspace"));
	AddPage(&m_pageTabClient);

	m_pageTabControl.SetCaption( _T("TabControl"));
	AddPage(&m_pageTabControl);

	m_pageDockingPane.SetCaption( _T("DockingPane"));
	AddPage(&m_pageDockingPane);

	m_pagePanel.SetCaption( _T("AutoHidePanel"));
	AddPage(&m_pagePanel);

	m_pageMargins.SetCaption( _T("Margins"));
	AddPage(&m_pageMargins);

}


BEGIN_MESSAGE_MAP(CPropertiesDialog, CXTPPropertySheet)
	//{{AFX_MSG_MAP(CPropertiesDialog)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDialog message handlers

void CPropertiesDialog::UpdateAll()
{
	m_pageTabClient.Update();
	m_pageTabControl.Update();
	m_pageDockingPane.Update();
	m_pagePanel.Update();

}

BOOL CPropertiesDialog::OnInitDialog()
{
	CXTPPropertySheet::OnInitDialog();

	m_ilTabCtrl.Create(16, 16, ILC_COLOR24|ILC_MASK, 0, 1);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_TABCTRL_ICONS);
	m_ilTabCtrl.Add(&bmp, RGB(0xC0, 0xC0, 0xC0));

	CXTPTabControl* pTabControl = (CXTPPropertyPageTabNavigator*)GetNavigator();


	for (int i = 0; i < pTabControl->GetItemCount(); i++)
	{
		pTabControl->GetItem(i)->SetImageIndex(0);
	}

	pTabControl->SetImageList(&m_ilTabCtrl);

	pTabControl->ShowIcons(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertiesDialog::OnClose()
{
	ShowWindow(SW_HIDE);
}
