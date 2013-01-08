// XTPButton.h : interface for the CXTPButton class.
//
// This file is a part of the XTREME CONTROLS MFC class library.
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
#if !defined(__XTPBUTTON_H__)
#define __XTPBUTTON_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXTPImageManager;
class CXTPImageManagerIcon;
class CXTPMarkupContext;
class CXTPMarkupUIElement;
class CXTPButtonTheme;
class CXTPImageManagerIconHandle;


#define CXTPButtonBase CButton


enum XTPButtonTextImageRelation
{
	xtpButtonOverlay,
	xtpButtonImageAboveText,
	xtpButtonTextAboveImage,
	xtpButtonImageBeforeText,
	xtpButtonTextBeforeImage
};

enum XTPPushButtonStyle
{
	xtpButtonNormal,
	xtpButtonDropDown,
	xtpButtonDropDownRight,
	xtpButtonSplitDropDown
};

enum XTPButtonTheme
{
	xtpButtonThemeStandard,
	xtpButtonThemeFlat,
	xtpButtonThemeUltraFlat,
	xtpButtonThemeOffice2000,
	xtpButtonThemeOfficeXP,
	xtpButtonThemeOffice2003,
	xtpButtonThemeOffice2007
};

enum XTPGroupBoxBorderStyle
{
	xtpGroupBoxBorder,
	xtpGroupBoxSingleLine,
	xtpGroupBoxNone
};


class _XTP_EXT_CLASS CXTPButton : public CXTPButtonBase
{
	DECLARE_DYNAMIC(CXTPButton)
public:
	// ----------------------------------------
	// Summary:
	//     Constructs a CXTPButton object
	// ----------------------------------------
	CXTPButton();

	// -----------------------------------------------------------
	// Summary:
	//     Destroys a CXTPButton object, handles cleanup and
	//     deallocation
	// -----------------------------------------------------------
	virtual ~CXTPButton();

public:
	BYTE GetButtonStyle() const;

	virtual BOOL IsPushed();

	virtual BOOL IsHighlighted();

	virtual BOOL GetChecked();

	void SetChecked(BOOL bChecked);

	BOOL GetFlatStyle() const;

	void SetFlatStyle(BOOL bFlatStyle = TRUE);

	BOOL GetUseVisualStyle() const;

	void SetUseVisualStyle(BOOL bUseVisualStyle = TRUE);

	long GetBorderGap() const;

	void SetBorderGap(int nBorderGap);

	XTPPushButtonStyle GetPushButtonStyle() const;

	void SetPushButtonStyle(XTPPushButtonStyle nPushButtonStyle);

	virtual int GetTextAlignment() const;

	void SetTextAlignment(DWORD dwAlignment);

	virtual int GetImageAlignment() const;

	void SetImageAlignment(DWORD dwAlignment);

	XTPButtonTextImageRelation GetTextImageRelation() const;

	void SetTextImageRelation(XTPButtonTextImageRelation realtion);

	long GetImageGap() const;

	void SetImageGap(int nImageGap);

	virtual CSize GetImageSize();

	CXTPImageManagerIcon* GetIcon() const;

	virtual void DrawImage(CDC* pDC, CRect rc);

	XTPGroupBoxBorderStyle GetBorderStyle() const;

	void SetBorderStyle(XTPGroupBoxBorderStyle style);

	BOOL GetShowFocus() const;

	void SetShowFocus(BOOL bShowFocus);

	void SetTheme(XTPButtonTheme nStyle);

	void RedrawButton();

	BOOL IsDropDownStyle() const;

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     This member function will set the normal and hot state icons for
	//     the push button.
	// Parameters:
	//     size           - CSize object that represents the size of the icon.
	//     hIcon          - Handle to the normal icon.
	//     hIconHandle    - Handle to the normal icon.
	//     hIconHot       - Handle to the hot icon.
	//     hIconHotHandle - Handle to the hot icon.
	//     nID            - Resource ID for the normal icon.
	//     nHotID         - Resource ID for the pressed icon.
	//     lpszID         - Resource string ID for the normal icon.
	//     lpszHotID      - Resource string ID for the hot icon.
	//     bRedraw        - Specifies whether the button is to be redrawn. A
	//                      nonzero value redraws the button. A zero value does
	//                      not redraw the button. The button is redrawn by default.
	// Returns:
	//     TRUE if successful, otherwise returns FALSE.
	//-----------------------------------------------------------------------
	virtual BOOL SetIcon(CSize size, HICON hIcon, HICON hIconHot = NULL, BOOL bRedraw = TRUE);
	virtual BOOL SetIcon(CSize size, UINT nID, UINT nHotID = 0, BOOL bRedraw = TRUE);                //<COMBINE CXTButton::SetIcon@CSize@HICON@HICON@BOOL>
	virtual BOOL SetIcon(CSize size, LPCTSTR lpszID, LPCTSTR lpszHotID = NULL, BOOL bRedraw = TRUE); //<COMBINE CXTButton::SetIcon@CSize@HICON@HICON@BOOL>
	virtual BOOL SetIcon(CSize size, const CXTPImageManagerIconHandle& hIconHandle, const CXTPImageManagerIconHandle& hIconHotHandle, BOOL bRedraw = TRUE); //<COMBINE CXTButton::SetIcon@CSize@HICON@HICON@BOOL>
	BOOL SetIcon(CSize size, CXTPImageManagerIcon* pIcon, BOOL bRedraw = TRUE);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function will set the bitmap associated with the
	//     button.
	// Parameters:
	//     size    - CSize object that represents the size of the bitmap.
	//     nID     - Resource ID for the bitmap.
	//     bRedraw - Specifies whether the button is to be redrawn. A nonzero
	//               value redraws the button. A zero value does not redraw
	//               the button. The button is redrawn by default.
	// Returns:
	//     TRUE if successful, otherwise returns FALSE.
	//-----------------------------------------------------------------------

	virtual BOOL SetBitmap(CSize size, UINT nID, BOOL bRedraw = TRUE);

public:
	virtual CString GetButtonText();
	CSize GetGlyphSize(BOOL bCheckBox);
	BOOL IsPushButton() const;

	void EnableMarkup(BOOL bEnableMarkup = TRUE);
	virtual COLORREF GetButtonTextColor();
	virtual COLORREF GetButtonBackColor();
	CXTPMarkupContext* GetMarkupContext() const;
	CXTPMarkupUIElement* GetMarkupUIElement();

protected:
	virtual void OnDropDown();
	virtual void OnDraw(CDC* pDC);
	virtual void InternalTextChanged();
	void DoDropDown();

protected:
//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()

	//{{AFX_VIRTUAL(CXTPButton)
	virtual void DoDraw(CDC* pDC);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTPButton)
	afx_msg LRESULT OnSetStyle(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg LRESULT OnSetState(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseLeave();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInvalidate();
	afx_msg LRESULT OnDefaultAndInvalidate(WPARAM, LPARAM);
	afx_msg LRESULT OnUpdateUIState(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPrintClient(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysColorChange();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnGetDlgCode(WPARAM wParam, LPARAM lParam);

	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE

protected:
	BOOL m_bPushed;         // TRUE if button was pressed
	BOOL m_bHot;            // TRUE if mouse under button
	CXTPButtonTheme* m_pButtonTheme;
	BOOL m_bChecked;

	BOOL m_bFlatStyle;
	BOOL m_bUseVisualStyle;

	long m_nImageAlignment;
	long m_nBorderGap;

	long m_nPushButtonStyle;

	BOOL m_bEnableMarkup;

	long m_nImageGap;
	long m_nTextImageRelation;
	CXTPImageManagerIcon* m_pIcon;
	long m_nBorderStyle;
	BOOL m_bShowFocus;

protected:
	CXTPMarkupContext* m_pMarkupContext;
	CXTPMarkupUIElement* m_pUIElement;
};

#include "Common/XTPWinThemeWrapper.h"
#include "Common/XTPColorManager.h"

class _XTP_EXT_CLASS CXTPButtonTheme : public CCmdTarget
{
public:
	CXTPButtonTheme();
	virtual ~CXTPButtonTheme();

	virtual void DrawButtonBackground(CDC* pDC, CXTPButton* pButton);
	void DrawFocusRect(CDC* pDC, CXTPButton* pButton);

	void DrawButtonVisualStyleBackground(CDC* pDC, CXTPButton* pButton);
	virtual void RefreshMetrics(CXTPButton* pButton);

	void DrawPushButtonText(CDC* pDC, CXTPButton* pButton);
	void DrawPushButtonIcon(CDC* pDC, CXTPButton* pButton);
	void DrawPushButtonDropDown(CDC* pDC, CXTPButton* pButton);

	COLORREF GetTextColor(CXTPButton* pButton);

	virtual void DrawCheckBoxMark(CDC* pDC, CXTPButton* pButton);
	virtual void DrawRadioButtonMark(CDC* pDC, CXTPButton* pButton);

	void DrawButtonText(CDC* pDC, CXTPButton* pButton);

	virtual void DrawGroupBox(CDC* pDC, CXTPButton* pButton);

	void CalcRects(CDC* pDC, CXTPButton* pButton, CRect* pButtonText, UINT* pDrawFlags, CRect* pButtonIcon);
	void CalcRect(CDC* pDC, CXTPButton* pButton, LPRECT lprc, int code);
	BOOL IsVisualThemeUsed(CXTPButton* pButton);
	void AlphaEllipse(CDC* pDC, CRect rc, COLORREF clrBorder, COLORREF clrFace);

	CXTPPaintManagerColor m_crTextDisabled;     // RGB value for disabled text color.
	CXTPPaintManagerColor m_crBorderHilite;     // RGB value for border highlight color.
	CXTPPaintManagerColor m_crBorderShadow;     // RGB value for border shadow color.
	CXTPPaintManagerColor m_crBorder3DHilite;   // RGB value for 3D border highlight color.
	CXTPPaintManagerColor m_crBorder3DShadow;   // RGB value for 3D border shadow color.
	CXTPPaintManagerColor m_crBack;
	CXTPPaintManagerColor m_crText;

	CXTPWinThemeWrapper m_themeButton;

	BOOL m_bOffsetHiliteText;
	int m_nBorderWidth;
	BOOL m_bFlatGlyphs;

	int m_cxBorder;
	int m_cyBorder;
	int m_cyEdge;
	int m_cxEdge;
};

class _XTP_EXT_CLASS CXTPButtonFlatTheme : public CXTPButtonTheme
{
public:
	CXTPButtonFlatTheme();
	void DrawButtonBackground(CDC* pDC, CXTPButton* pButton);
};


class _XTP_EXT_CLASS CXTPButtonUltraFlatTheme : public CXTPButtonTheme
{
public:
	CXTPButtonUltraFlatTheme();
	void RefreshMetrics(CXTPButton* pButton);

	void DrawButtonBackground(CDC* pDC, CXTPButton* pButton);
	virtual void DrawGroupBox(CDC* pDC, CXTPButton* pButton);
	virtual void DrawCheckBoxMark(CDC* pDC, CXTPButton* pButton);
	virtual void DrawRadioButtonMark(CDC* pDC, CXTPButton* pButton);

	CXTPPaintManagerColor m_crBackPushed; // RGB value for pushed background color.
	CXTPPaintManagerColor m_crBackHilite; // RGB value for highlighted background color.
	CXTPPaintManagerColor m_crTextPushed; // RGB value for highlighted text color.
	CXTPPaintManagerColor m_crTextHilite; // RGB value for pushed text color.
	CXTPPaintManagerColor m_crBackChecked;// RGB value for when the control is checked.

	BOOL m_bHiglightButtons;

};

class _XTP_EXT_CLASS CXTPButtonOffice2000Theme : public CXTPButtonUltraFlatTheme
{
public:
	CXTPButtonOffice2000Theme();
	void DrawButtonBackground(CDC* pDC, CXTPButton* pButton);
};


class _XTP_EXT_CLASS CXTPButtonOffice2007Theme : public CXTPButtonUltraFlatTheme
{
public:
	CXTPButtonOffice2007Theme();
	void DrawButtonBackground(CDC* pDC, CXTPButton* pButton);
	void DrawCheckBoxMark(CDC* pDC, CXTPButton* pButton);
	void DrawRadioButtonMark(CDC* pDC, CXTPButton* pButton);
	void RefreshMetrics(CXTPButton* pButton);

};

class _XTP_EXT_CLASS CXTPButtonOfficeXPTheme : public CXTPButtonUltraFlatTheme
{
public:
	CXTPButtonOfficeXPTheme();
	void DrawButtonBackground(CDC* pDC, CXTPButton* pButton);
	void RefreshMetrics(CXTPButton* pButton);

};

class _XTP_EXT_CLASS CXTPButtonOffice2003Theme : public CXTPButtonOfficeXPTheme
{
public:
	CXTPButtonOffice2003Theme();
	BOOL m_bLunaTheme;

	void DrawButtonBackground(CDC* pDC, CXTPButton* pButton);
	void RefreshMetrics(CXTPButton* pButton);

};



AFX_INLINE BOOL CXTPButton::IsPushed() {
	return m_bPushed;
}
AFX_INLINE BOOL CXTPButton::IsHighlighted() {
	return m_bHot || (::GetCapture() == m_hWnd);
}
AFX_INLINE BOOL CXTPButton::GetFlatStyle() const{
	return m_bFlatStyle;
}
AFX_INLINE void CXTPButton::SetFlatStyle(BOOL bFlatStyle/* = TRUE*/) {
	m_bFlatStyle = bFlatStyle;
	RedrawButton();
}
AFX_INLINE BOOL CXTPButton::GetUseVisualStyle() const {
	return m_bUseVisualStyle;
}
AFX_INLINE long CXTPButton::GetBorderGap() const {
	return m_nBorderGap;
}
AFX_INLINE void CXTPButton::SetBorderGap(int nBorderGap) {
	m_nBorderGap = nBorderGap;
	RedrawButton();
}
AFX_INLINE XTPPushButtonStyle CXTPButton::GetPushButtonStyle() const {
	return (XTPPushButtonStyle)m_nPushButtonStyle;
}
AFX_INLINE void CXTPButton::SetPushButtonStyle(XTPPushButtonStyle nPushButtonStyle) {
	m_nPushButtonStyle = nPushButtonStyle;
	RedrawButton();
}
AFX_INLINE void CXTPButton::SetTextAlignment(DWORD dwAlignment) {
	ModifyStyle(BS_LEFT | BS_CENTER | BS_RIGHT | BS_TOP | BS_BOTTOM | BS_VCENTER, dwAlignment);
	RedrawButton();
}
AFX_INLINE int CXTPButton::GetImageAlignment() const {
	return m_nImageAlignment;
}
AFX_INLINE void CXTPButton::SetImageAlignment(DWORD dwAlignment) {
	m_nImageAlignment = dwAlignment;
	RedrawButton();
}
AFX_INLINE XTPButtonTextImageRelation CXTPButton::GetTextImageRelation() const {
	return (XTPButtonTextImageRelation)m_nTextImageRelation;
}
AFX_INLINE void CXTPButton::SetTextImageRelation(XTPButtonTextImageRelation realtion) {
	m_nTextImageRelation = realtion;
	RedrawButton();
}
AFX_INLINE long CXTPButton::GetImageGap() const {
	return m_nImageGap;
}
AFX_INLINE void CXTPButton::SetImageGap(int nImageGap) {
	m_nImageGap = nImageGap;
}
AFX_INLINE CXTPImageManagerIcon* CXTPButton::GetIcon() const {
	return m_pIcon;
}
AFX_INLINE XTPGroupBoxBorderStyle CXTPButton::GetBorderStyle() const {
	return (XTPGroupBoxBorderStyle)m_nBorderStyle;
}
AFX_INLINE void CXTPButton::SetBorderStyle(XTPGroupBoxBorderStyle style) {
	m_nBorderStyle = style;
}
AFX_INLINE BOOL CXTPButton::GetShowFocus() const {
	return m_bShowFocus;
}
AFX_INLINE void CXTPButton::SetShowFocus(BOOL bShowFocus) {
	m_bShowFocus = bShowFocus;
}
AFX_INLINE void CXTPButton::RedrawButton() {
	if (m_hWnd) Invalidate(FALSE);
}
AFX_INLINE CXTPMarkupContext* CXTPButton::GetMarkupContext() const {
	return m_pMarkupContext;
}

AFX_INLINE CXTPMarkupUIElement* CXTPButton::GetMarkupUIElement() {
	return m_pUIElement;
}
AFX_INLINE BOOL CXTPButton::IsDropDownStyle() const {
	return m_nPushButtonStyle == xtpButtonDropDown || m_nPushButtonStyle == xtpButtonDropDownRight || m_nPushButtonStyle == xtpButtonSplitDropDown;
}

#endif // #if !defined(__XTPBUTTON_H__)
