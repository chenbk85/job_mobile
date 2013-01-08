// MainFrm.h : interface of the CMainFrame class
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

#if !defined(AFX_MAINFRM_H__04D2F152_F10A_4AC1_AA87_556FC6E4887B__INCLUDED_)
#define AFX_MAINFRM_H__04D2F152_F10A_4AC1_AA87_556FC6E4887B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TaskPanel.h"

class CMainFrame : public CXTPMDIFrameWnd, CXTPOffice2007FrameHook
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	CTaskPanel m_wndTaskPanel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CXTPMessageBar  m_wndMessageBar;
	int m_nState;

	CXTPTabClientWnd m_wndClient;

public:
	UINT m_nIDSaveAs;

private:
	void SetCustomTheme(CXTPPaintManager* pTheme);
	void DockRightOf(CXTPToolBar* pBarToDock, CXTPToolBar* pBarOnLeft);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnScrollItem(UINT);

	afx_msg void OnCustomize();
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	afx_msg int OnCreateCommandBar(LPCREATEBARSTRUCT lpCreatePopup);


	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnClose();
	afx_msg void OnEditState(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFileNew(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEditState(CCmdUI* pCmdUI);

	afx_msg void OnTextBelow();
	afx_msg void OnUpdateTextBelow(CCmdUI* pCmdUI);

	afx_msg void OnSaveAs(UINT nID);
	afx_msg void OnUpdateSaveAs(CCmdUI* pCmdUI);
	afx_msg BOOL OnTaskPanelCaption(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateTaskPanelCaption(CCmdUI* pCmdUI);
	afx_msg LRESULT OnControlRButtonUp(WPARAM, LPARAM lParam);
	void OnThemeCustom();
	void OnUpdateTheme(CCmdUI* pCmdUI);
	void OnSwitchTheme(UINT nTheme);
	void OnUpdateViewOffice2007Frame(CCmdUI* pCmdUI);
	void OnViewOffice2007Frame();

protected:
	UINT m_nCurrentTheme;

	BOOL m_bOffice2007Frame;

	void OnOptionsRighttoleft();
	void OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI);

	void OnComboDate(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateComboDate(CCmdUI* pCmdUI);
	COleDateTime m_dt;

		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__04D2F152_F10A_4AC1_AA87_556FC6E4887B__INCLUDED_)
