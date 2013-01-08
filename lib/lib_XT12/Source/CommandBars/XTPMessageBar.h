// XTPMessageBar.h : interface for the CXTPMessageBar class.
//
// This file is a part of the XTREME COMMANDBARS MFC class library.
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
#if !defined(__XTPMESSAGEBAR_H__)
#define __XTPMESSAGEBAR_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define XTP_IDW_MESSAGE_BAR 0xE806

class CXTPCommandBars;
class CXTPMarkupUIElement;
class CXTPMarkupContext;
class CXTPMessageBar;
class CXTPPaintManager;

//===========================================================================
// Summary:
//     CXTPMessageBarButton is a standalone class. It represents single button of message bar
//===========================================================================
class _XTP_EXT_CLASS CXTPMessageBarButton
{
public:
	CXTPMessageBarButton();

public:
	void PerformClick(CXTPMessageBar* pBar, CPoint pt);
public:
	CRect m_rcButton;
	CString m_strCaption;
	CString m_strToolTip;
	BOOL m_bPressed;
	BOOL m_bHot;
	UINT m_nID;
};

//===========================================================================
// Summary:
//     CXTPMessageBar is a CControlBar derived class. It can be used to show some information in top of Frame
//===========================================================================
class _XTP_EXT_CLASS  CXTPMessageBar : public CControlBar
{
public:
	CXTPMessageBar();
	virtual ~CXTPMessageBar();

public:
	BOOL Create(CXTPCommandBars* pCommandBars, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, UINT nID = XTP_IDW_MESSAGE_BAR);

public:
	void SetMessage(LPCTSTR lpszMessage);
	void EnableMarkup(BOOL bEnableMarkup = TRUE);

	void AddButton(UINT nID, LPCTSTR lpszCaption, LPCTSTR lpszToolTop = NULL);

	void RemoveButtons();

	virtual void Click(CXTPMessageBarButton* pButton);

public:
	CRect GetMessageRect();
	CXTPPaintManager* GetPaintManager() const;

	CXTPMessageBarButton* HitTestButton(CPoint point) const;
	CXTPMessageBarButton* FindButton(UINT nID) const;

	CXTPMarkupContext* GetMarkupContext() const;


protected:
	virtual void FillMessageBar(CDC* pDC);
	virtual CSize MeasureContent(CDC* pDC);
	virtual CSize MeasureButton(CDC* pDC, CXTPMessageBarButton* pButton);
	virtual void DrawContent(CDC* pDC);
	virtual void RecalcLayout(CDC* pDC);
	virtual void DrawButton(CDC* pDC, CXTPMessageBarButton* pButton);

	void DrawButtons(CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()

	//{{AFX_VIRTUAL(CXTPMessageBar)
	virtual CSize CalcFixedLayout(BOOL, BOOL bHorz);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTPMessageBar)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	//}}AFX_MSG

protected:
	CString m_strContent;
	CXTPMarkupUIElement* m_pUIElement;
	CXTPMarkupContext* m_pMarkupContext;
	CXTPCommandBars* m_pCommandBars;

	CXTPMessageBarButton* m_pHotButton;
	CArray<CXTPMessageBarButton*, CXTPMessageBarButton*> m_arrButtons;

	CRect m_rcBorder;
	CRect m_rcPadding;
	CRect m_rcContent;


};

/////////////////////////////////////////////////////////////////////////////

AFX_INLINE CXTPMarkupContext* CXTPMessageBar::GetMarkupContext() const {
	return m_pMarkupContext;
}

#endif // !defined(__XTPMESSAGEBAR_H__)
