// EmbeddedFrame.h : header file
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

#if !defined(AFX_EMBEDDEDFRAME_H__51FE6C04_80EB_47DB_8E62_BE28CBCA1F57__INCLUDED_)
#define AFX_EMBEDDEDFRAME_H__51FE6C04_80EB_47DB_8E62_BE28CBCA1F57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EmbeddedView.h"
#include "ResourceManager.h"

class CCommandBarsDesignerView;
class CCommandBarsDesignerDesignerView;
/////////////////////////////////////////////////////////////////////////////
// CEmbeddedFrame frame

class CEmbeddedFrame : public CXTPFrameWnd, CXTPOffice2007FrameHook
{
public:
	DECLARE_DYNCREATE(CEmbeddedFrame)
	CEmbeddedFrame();           // protected constructor used by dynamic creation

// Attributes
public:

	CEmbeddedView m_wndView;

	CXTPControls* m_pControls;

	CCommandBarsDesignerDesignerView* m_pHostView;


	CResourceManager m_resourceManager;

	CResourceManager* ResourceManager() { return &m_resourceManager;}

	virtual void Serialize(CArchive& ar);
	void ReplaceControls(CXTPToolBar* pCommandBar, CXTPControls* pControls);

	void DoPropExchange(CXTPPropExchange* pPX);

	void ShowPropertyPage();
	void Clear();

	XTPPaintTheme m_theme;
	BOOL m_bCustomizable;
	CXTPToolBar* m_pContextMenu;
	CPoint m_ptContextMenu;

	void CommitContextMenu();
	static void ForceVectorDelete();

// Operations
public:

	void SetTheme(XTPPaintTheme theme);

	BOOL BuildControls();
	BOOL AddCategory(CString strCategory, CMenu* pMenu);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmbeddedFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	afx_msg void OnSimpleCommand(UINT);
	afx_msg void OnUpdateSimpleCommand(CCmdUI* pCmdUI);


// Implementation
protected:
	virtual ~CEmbeddedFrame();

	// Generated message map functions
	//{{AFX_MSG(CEmbeddedFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnDragControlChanged(WPARAM, LPARAM);


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMBEDDEDFRAME_H__51FE6C04_80EB_47DB_8E62_BE28CBCA1F57__INCLUDED_)
