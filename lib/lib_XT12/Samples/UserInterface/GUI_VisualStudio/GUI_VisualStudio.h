// GUI_VisualStudio.h : main header file for the GUI_VISUALSTUDIO application
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

#if !defined(AFX_GUI_VISUALSTUDIO_H__43A4C0AC_0369_4063_BC19_7EBCB371EFD9__INCLUDED_)
#define AFX_GUI_VISUALSTUDIO_H__43A4C0AC_0369_4063_BC19_7EBCB371EFD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioApp:
// See GUI_VisualStudio.cpp for the implementation of this class
//

class CGUI_VisualStudioApp : public CWinApp
{
public:
	CGUI_VisualStudioApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGUI_VisualStudioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGUI_VisualStudioApp)
	afx_msg void OnAppAbout();
	afx_msg void OnWindowCloseAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

AFX_INLINE BOOL CreateImageList(CImageList& il, UINT nID)
{
	if (!il.Create(16, 16, ILC_MASK|ILC_COLOR24, 0, 1))
		return FALSE;
	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(nID));

	il.Add(&bmp, CXTPImageManager::GetBitmapMaskColor(bmp, CPoint(0, 0)));

	return TRUE;
}

class COfficeTreeCtrl : public CXTPOfficeBorder<CTreeCtrl>
{
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)		
	{
		NMHDR* pNMHDR = (NMHDR*)lParam;
		
		switch (pNMHDR->code)
		{
		case TTN_SHOW:
			{
				// get a pointer to the tooltip control.
				HWND hWnd = TreeView_GetToolTips(m_hWnd);
				if (hWnd != NULL)
				{
					// make sure the tooltip is at the top of the "Z" order, otherwise
					// it will appear behind popup windows....
					::SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0,
						SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
				}
			}
			break;
		}
		return CXTPOfficeBorder<CTreeCtrl>::OnNotify(wParam, lParam, pResult);
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_VISUALSTUDIO_H__43A4C0AC_0369_4063_BC19_7EBCB371EFD9__INCLUDED_)
