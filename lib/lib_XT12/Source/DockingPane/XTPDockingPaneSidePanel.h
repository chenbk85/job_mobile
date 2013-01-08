// XTPDockingPaneSidePanel.h : interface for the CXTPDockingPaneSidePanel class.
//
// This file is a part of the XTREME DOCKINGPANE MFC class library.
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

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTPDOCKINGPANESIDEPANEL_H__)
#define __XTPDOCKINGPANESIDEPANEL_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTPDockingPaneBaseContainer.h"

class CXTPDockingPaneLayout;
class CXTPDockingPaneSidePanel;

//===========================================================================
// Summary:
//     CXTPDockingPaneSidePanel is a multiple inheritance class derived from
//     CWnd and CXTPDockingPaneBase. It is used internally as an auto-hide container
//     for CXTPDockingPaneBase derived classes.
//===========================================================================
class _XTP_EXT_CLASS CXTPDockingPaneSidePanel : public CMiniFrameWnd, public CXTPDockingPaneBaseContainer
{
protected:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPDockingPaneAutoHidePanel object
	//     Protected constructor. Internally constructed only.
	// Parameters:
	//     pLayout - Points to a CXTPDockingPaneLayout object.
	//-----------------------------------------------------------------------
	CXTPDockingPaneSidePanel(CXTPDockingPaneLayout* pLayout);

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXTPDockingPaneAutoHidePanel object, handles cleanup and
	//     deallocation
	//-----------------------------------------------------------------------
	~CXTPDockingPaneSidePanel();

public:
	CXTPDockingPaneTabbedContainer* GetTopContainer() const;

	XTPDockingPaneDirection GetDirection() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to get child pane state.
	// Returns:
	//     TRUE if a child pane is active.
	//-----------------------------------------------------------------------
	BOOL IsActive() const;

	CString GetTitle() const;

	CXTPDockingPane* GetSelectedPane() const;

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     This method is called to collapse frame.
	// Parameters:
	//     bDelay - TRUE to collapse after small delay with animation.
	//-----------------------------------------------------------------------
	void Collapse(BOOL bDelay = FALSE);

	//-----------------------------------------------------------------------
	// Summary:
	//     Determines if frame is collapsed
	//-----------------------------------------------------------------------
	BOOL IsCollapsed() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this method to expand collapsed frame.
	//-----------------------------------------------------------------------
	void Expand();

	void MovePanel(XTPDockingPaneDirection direction, CRect rect);

protected:
	BOOL Init(CXTPDockingPaneBase* pPane, XTPDockingPaneDirection direction, CRect rc);
	BOOL Create(CRect rc);

	static void AFX_CDECL OnSizeParentEx(CXTPDockingPaneManager* pManager, CWnd* pParent, CRect rect);

protected:
	void DeletePane();
	void OnFinalRelease();
	void PostNcDestroy();
	void RecalcLayout(BOOL bNotify = TRUE);
	void OnFocusChanged();

	void RemovePane(CXTPDockingPaneBase* pPane);
	void OnChildContainerChanged(CXTPDockingPaneBase* /*pContainer*/);
	void CreateContainer();
	void Copy(CXTPDockingPaneBase* pClone, CXTPPaneToPaneMap* pMap, DWORD dwIgnoredOptions);

	void _InsertPane(CXTPDockingPaneBase* pPane);

	void GetMinMaxInfo(LPMINMAXINFO pMinMaxInfo) const;
	BOOL IsHorizontal() const;

	INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member is called to save/restore the settings of the pane.
	// Parameters:
	//     pPX - Points to a CXTPPropExchange object.
	// Returns:
	//     TRUE if successful; otherwise returns FALSE.
	//-----------------------------------------------------------------------
	virtual BOOL DoPropExchange(CXTPPropExchange* pPX);


	//-----------------------------------------------------------------------
	// Summary:
	//     This member is called when a need to redraw pane.
	// Parameters:
	//     bSelectionChanged - TRUE if selected pane was changed
	//-----------------------------------------------------------------------
	virtual void InvalidatePane(BOOL bSelectionChanged);

	HWND GetPaneHwnd() const;

protected:
		//-----------------------------------------------------------------------
	// Summary:
	//     This method is called to animate collapsed frame
	// Parameters:
	//     bActivate - TRUE to activate frame.
	//-----------------------------------------------------------------------
	void DoSlideStep(BOOL bActivate = FALSE);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member is called when the "pin" caption button is clicked.
	//-----------------------------------------------------------------------
	void OnPinButtonClick();


private:
	typedef CArray<CXTPDockingPaneSidePanel*, CXTPDockingPaneSidePanel*> CSidePanelArray;

	static void AFX_CDECL OnSizeParentEx(CSidePanelArray& arrSide, CWnd* pParent, CRect rect);
	static int _cdecl CompareLength(const void *arg1, const void *arg2);

	struct LENGTH;
	static void SortLength(LENGTH* pLength, int nFirstIndex, int nLastIndex);

private:
	CXTPDockingPaneCaptionButton* HitTestCaptionButton(CPoint point) const;
	void OnCaptionButtonClick(CXTPDockingPaneCaptionButton* pButton);
	void OnCaptionLButtonDown(CPoint point);
	void _RestoreFocus();

	BOOL IsCaptionButtonVisible(CXTPDockingPaneCaptionButton* pButton);
	void MovePanel(LENGTH* pLength, CRect rect);

	int GetMinHeight();

protected:
//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()

	//{{AFX_VIRTUAL(CXTPDockingPaneSidePanel)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTPDockingPaneSidePanel)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnMouseHover(WPARAM, LPARAM lParam);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint pt);
	afx_msg void OnRButtonUp(UINT /*nFlags*/, CPoint point);
	//}}AFX_MSG
	BOOL IsResizable(int nHit);

//}}AFX_CODEJOCK_PRIVATE


protected:
	XTPDockingPaneDirection m_direction;                          // Location of side panel
	int m_nLengthIndex;

	int m_nStepsCount;          // Total steps of animation process
	int m_nSlideStep;           // Current step of animation process
	int m_nDeactivationCount;   // Deactivation counter.

	BOOL m_bCollapsed;          // Pane is collapsed
	BOOL m_bExpanded;           // Pane is collapsed but expanded now
	BOOL m_bSlideOut;           // Pane is currently expanding.


	friend class CXTPDockingPaneManager;
	friend class CXTPDockingPaneLayout;

};

AFX_INLINE HWND CXTPDockingPaneSidePanel::GetPaneHwnd() const {
	return CWnd::GetSafeHwnd();
}
AFX_INLINE XTPDockingPaneDirection CXTPDockingPaneSidePanel::GetDirection() const {
	return m_direction;
}
AFX_INLINE BOOL CXTPDockingPaneSidePanel::IsActive() const {
	return m_bActive;
}

#endif // #if !defined(__XTPDOCKINGPANESIDEPANEL_H__)
