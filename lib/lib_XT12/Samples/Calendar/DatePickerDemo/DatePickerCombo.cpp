// DatePickerCombo.cpp : implementation file
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
#include "DatePickerCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatePickerCombo

CDatePickerCombo::CDatePickerCombo()
{
}

CDatePickerCombo::~CDatePickerCombo()
{
}


BEGIN_MESSAGE_MAP(CDatePickerCombo, CComboBox)
	//{{AFX_MSG_MAP(CDatePickerCombo)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropDown)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CTLCOLORLISTBOX, OnCtlColorListBox)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatePickerCombo message handlers

//////////////////////////////////////////////////////////////////////////
// Process combobox DropDown notification:
// Show DatePicker and format results.
//
void CDatePickerCombo::OnDropDown() 
{

	// Identify size and coordinates of the popup DatePicker window
	CXTPWindowRect rcPopup(this);

	CXTPDatePickerControl wndDatePicker;
	
	// Ask DatePicker control about how much space we'd need 
	// to show one full month item.
	CRect rc;
	wndDatePicker.GetMinReqRect(&rc);
	
	// Make small size correction for pretty result
	rc.InflateRect(0 ,0, 4, 4);
	// Shift the prepared rectangle near to the ComboBox
	rc.OffsetRect(rcPopup.right - rc.Width(), rcPopup.bottom);
	
	// Enable some visual effects
	wndDatePicker.SetButtonsVisible(TRUE, FALSE);
	wndDatePicker.SetShowWeekNumbers(TRUE);
	wndDatePicker.SetBorderStyle(xtpDatePickerBorderOffice);
	CString strPopup;

	// Run DatePicker on the prepared rectangle in the Modal mode.
	if (wndDatePicker.GoModal(rc, this))
	{
		COleDateTime dtFrom;
		COleDateTime dtTo;

		// Retrieve the selection result from the DatePicker
		if (wndDatePicker.GetSelRange(dtFrom, dtTo))
		{
			if (dtFrom == dtTo)
			{
				// When only 1 day has been selected, format string to show
				// it in the following way
				strPopup.Format(_T("%d.%d.%d"),	
					dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay());
			} else
			{
				// When a days range has been selected, format string to show
				// it in the following way
				strPopup.Format(_T("%d.%d.%d - %d.%d.%d"), 
					dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 
					dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay());
			}
		}
		else
		{
			// GetSelRange returned not TRUE, so there were no selection made
			strPopup.Format(_T("Nothing selected"));
		}
	}
	else
	{
		// Exception case -- GoModal returned FALSE
		strPopup.Format(_T("Error Popup wnd!"));
	}

	// Show retrieved result inside the ComboBox
	SetWindowText(strPopup);
	SetEditSel(0, -1);
	
	// Hide the list box part of the ComboBox
	PostMessage(CB_SHOWDROPDOWN, FALSE);
	//ShowDropDown(FALSE);
}

LRESULT CDatePickerCombo::OnCtlColorListBox(WPARAM wParam, LPARAM lParam) 
{
	HWND hWnd = (HWND)lParam;

	if (hWnd != 0 && hWnd != m_hWnd) 
	{
		::ShowWindow(hWnd , SW_HIDE);
	}


    return DefWindowProc(WM_CTLCOLORLISTBOX, wParam, lParam);
}
