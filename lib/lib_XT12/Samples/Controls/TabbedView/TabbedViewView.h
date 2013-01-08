// TabbedViewView.h : interface of the CTabbedViewView class
//
// This file is a part of the XTREME TOOLKIT MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO 
// BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED 
// WRITTEN CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS 
// OUTLINED IN THE XTREME TOOLKIT LICENSE AGREEMENT.  CODEJOCK SOFTWARE 
// GRANTS TO YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE 
// THIS SOFTWARE ON A SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TabbedViewVIEW_H__AEE169F1_953B_4155_BCCC_BCF03F26DD12__INCLUDED_)
#define AFX_TabbedViewVIEW_H__AEE169F1_953B_4155_BCCC_BCF03F26DD12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabEdit.h"
#include "TabTreeResource.h"
#include "TabTreeFile.h"
#include "TabTreeClass.h"

class CTabbedViewDoc;
class CTabbedViewView : public CXTTabView
{
protected: // create from serialization only
	CTabbedViewView();
	DECLARE_DYNCREATE(CTabbedViewView)

// Attributes
public:
	CTabbedViewDoc* GetDocument();

// Operations
public:

    UINT				m_nIDEvent;
	int					m_iHitTest;
	CImageList			m_imageList;
    CPoint				m_point;
	CTabEdit			m_editTab;
	CTabTreeResource    m_treeTabResource;
	CTabTreeFile		m_treeTabFile;
	CTabTreeClass		m_treeTabClass;
	COleDropTarget	    m_dropTarget;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabbedViewView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateTabBorders();
	virtual ~CTabbedViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	virtual void OnSelChanging();
	virtual void OnSelChange();
    void SetTabIcon(int iTab, int iImage);
    void SetTabIcon(int iTab, HICON hIcon);

// Generated message map functions
protected:
	//{{AFX_MSG(CTabbedViewView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileOpen();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnTabActivate();
	afx_msg void OnTabClose();
	afx_msg void OnTabSave();
	afx_msg void OnTabSaveAs();
	afx_msg void OnTabPrint();
	afx_msg void OnTabPrintPreview();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	afx_msg void OnCloseTab();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TabbedViewView.cpp
inline CTabbedViewDoc* CTabbedViewView::GetDocument()
   { return (CTabbedViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TabbedViewVIEW_H__AEE169F1_953B_4155_BCCC_BCF03F26DD12__INCLUDED_)
