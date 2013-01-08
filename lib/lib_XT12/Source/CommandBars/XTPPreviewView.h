// XTPPreviewView.h : header file
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

#if !defined(_XTPPREVIEWVIEW_H__)
#define _XTPPREVIEWVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPToolBar.h"
/////////////////////////////////////////////////////////////////////////////
// CXTPPreviewView view

#define XPT_ZOOM_WHOLEPAGE 0
#define XPT_ZOOM_PAGEWIDTH 1

class _XTP_EXT_CLASS CXTPPreviewView : public CPreviewView
{
	DECLARE_DYNCREATE(CXTPPreviewView)


protected:
	CXTPPreviewView();

private:
	CXTPControl* FindToolbarButton(UINT nCommandID);
	virtual void PositionPage(UINT nPage);
	void SetScaledSize(UINT nPage);
	void DoZoom(UINT nPage, CPoint point);
	void SetZoomState(UINT nNewState, UINT nPage, CPoint point);
	CSize CalcPageDisplaySize() ;
	void SetupScrollbar() ;
	void ZoomIn(UINT nPage, CPoint point);

protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_VIRTUAL(CXTPPreviewView)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTPPreviewView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC*);
	afx_msg void OnNumPageChange();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateNumPageChange(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPreviewPages();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) ;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGotoPageSetFocus(NMHDR* pNMHDR, LRESULT* pRes);
	afx_msg void OnGotoPageKillFocus(NMHDR* pNMHDR, LRESULT* pRes);
	afx_msg void OnUpdateGotoPage(CCmdUI* pCmdUI);
	afx_msg void OnZoomCombo(NMHDR* pNMHDR, LRESULT* pRes);
	afx_msg void OnOnePage();
	afx_msg void OnTwoPage(NMHDR* pNMHDR, LRESULT* pRes);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	// note that is you change the maximum number of pages that can be displayed in preview mode
	// you have to increase the size of this array to make sure there is an entry available for every
	// possible page that can be shown at once.
	PAGE_INFO m_pageInfoArray2[9]; // Embedded array for the default implementation - replaces MFC one of size 2!
	CXTPToolBar m_wndToolBar;
	int m_cxPixelsPerInch;
	int m_cyPixelsPerInch;

	// these variables are used in the page layout algorithm
	int m_Across ;          // number across the page, >= 1
	int m_Down ;            // number down the page, >= 1
	CPoint m_PageOffset;    // amount to move the page from one position to the next
};

#endif // !defined(_XTPPREVIEWVIEW_H__)
