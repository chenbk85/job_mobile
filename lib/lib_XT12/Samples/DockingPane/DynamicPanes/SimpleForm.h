// SimpleForm.h : header file
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

#if !defined(AFX_SIMPLEFORM_H__CD375CBC_CB75_4973_B05B_1D158BFEA6BF__INCLUDED_)
#define AFX_SIMPLEFORM_H__CD375CBC_CB75_4973_B05B_1D158BFEA6BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSimpleForm form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

template <class BASE_CLASS>
class CAutoFocusWnd : public BASE_CLASS
{
public:
	CAutoFocusWnd(UINT nIDTemplate) : BASE_CLASS(nIDTemplate)
	{
		m_hwndLastFocus = 0;
	}

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_SETFOCUS:
			if (m_hwndLastFocus)
			{
				::SetFocus(m_hwndLastFocus);
				return TRUE;
			}
			break;
		
		case WM_IDLEUPDATECMDUI:
			
			HWND hwndFocus = ::GetFocus();

			if (m_hwndLastFocus != hwndFocus && ::IsChild(m_hWnd, hwndFocus))
			{
				m_hwndLastFocus = hwndFocus;
			}
			break;

		}
		
		return BASE_CLASS::WindowProc(message, wParam, lParam);		
	}
	
protected:
	HWND m_hwndLastFocus;
};

class CSimpleForm : public CAutoFocusWnd<CFormView>
{
protected:
	CSimpleForm();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSimpleForm)

// Form Data
public:
	//{{AFX_DATA(CSimpleForm)
	enum { IDD = IDD_DIALOG_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleForm)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSimpleForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSimpleForm)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEFORM_H__CD375CBC_CB75_4973_B05B_1D158BFEA6BF__INCLUDED_)
