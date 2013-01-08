// PaneControls.h : header file
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

#if !defined(AFX_PANECONTROLS_H__CF8F9984_CE54_47AE_AE7A_B4DE8F3FCD4B__INCLUDED_)
#define AFX_PANECONTROLS_H__CF8F9984_CE54_47AE_AE7A_B4DE8F3FCD4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPaneControls window

class CPaneControls;

class CControlsListBox : public CListBox
{
public:
	CControlsListBox();
	~CControlsListBox();

	class CListBoxDropTarget;

public:
	void RegisterDropTarget();

public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void MeasureItem(LPMEASUREITEMSTRUCT) {};
	LRESULT WindowProc(UINT message,WPARAM wParam,LPARAM lParam);
	void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP();


public:
	CPaneControls* m_pPaneControls;
	COleDropTarget* m_pDropTarget;
};

class CPaneControls : public CPaneHolder
{


// Construction
public:
	CPaneControls();

// Operations
public:
	BOOL OnDropLibrary();
	void Refresh(BOOL bForce = FALSE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaneControls)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaneControls();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPaneControls)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPanecontrolsAdd();
	afx_msg void OnUpdatePanecontrolsAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePanecontrolsUp(CCmdUI* pCmdUI);
	afx_msg void OnPanecontrolsUp();
	afx_msg void OnPanecontrolsDown();
	afx_msg void OnUpdatePanecontrolsDown(CCmdUI* pCmdUI);
	afx_msg void OnPanecontrolsDelete();
	afx_msg void OnUpdatePanecontrolsDelete(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd*);
	//}}AFX_MSG
	afx_msg void OnCategoryChanged();
	afx_msg void OnControlChanged();


	DECLARE_MESSAGE_MAP()

public:
	CXTPCommandBars* m_pActiveCommandBars;
	CXTPControls* m_pControls;
	CComboBox m_wndCategories;
	CString m_strSelectedCategory;
	CXTPToolBar m_wndToolBar;
	CControlsListBox m_wndListBox;
	CFont m_fntRegular;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANECONTROLS_H__CF8F9984_CE54_47AE_AE7A_B4DE8F3FCD4B__INCLUDED_)
