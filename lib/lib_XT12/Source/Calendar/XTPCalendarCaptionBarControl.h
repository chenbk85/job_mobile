// XTPCalendarCaptionBarControl.h: interfaces for Time Zone Helper classes.
//
// This file is a part of the XTREME CALENDAR MFC class library.
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
#if !defined(__XTPCalendarCaptionBarControl_H__)
#define __XTPCalendarCaptionBarControl_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Common/XTPWinThemeWrapper.h"

//#include "XTPCalendarTheme.h"
#include "XTPCalendarView.h"
#include "XTPCalendarViewPart.h"

class CXTPCalendarCaptionBarTheme;

//////////////////////////////////////////////////////////////////////////
// Office2007

/*
	Switch View Bar:
		SwitchViewButtonPart
		RadioButtonPart
		// LabelPart

	Scroll Date Bar:
		ScrollDateButtonPart
		DateLabelPart

	==========================================
	ButtonViewDay   : SwitchViewButtonPart
	ButtonViewWeek  : SwitchViewButtonPart
	ButtonViewMonth : SwitchViewButtonPart

	ShowWorkWeek    : RadioButtonPart
	ShowFullWeek    : RadioButtonPart
	---------------------------------
	ScrollPrevDate  : ScrollDateButtonPart
	ScrollNextDate  : ScrollDateButtonPart
	DateLabel       : DateLabelPart

	---------------------------------
	SwitchViewBarBkColor
	ScrollDateBarBkColor

*/


//===========================================================================
// Summary:
//     Enumerates Calendar Caption Bar graphical objects .
//===========================================================================
enum XTPEnumCalendarCaptionBarThemeObject
{
	xtpCalendarCaptionBar_Unknown           = 0,			// Defines Unknown (NULL) value.

	xtpCalendarCaptionBar_ButtonViewDay     = 0x00000001,	// Defines SwitchViewBar DayViewButton.
	xtpCalendarCaptionBar_ButtonViewWeek    = 0x00000002,	// Defines SwitchViewBar WeekViewButton.
	xtpCalendarCaptionBar_ButtonViewMonth   = 0x00000004,	// Defines SwitchViewBar MonthViewButton.

	xtpCalendarCaptionBar_ShowWorkWeek      = 0x00000010,	// Defines SwitchViewBar ShowWorkWeek radio button.
	xtpCalendarCaptionBar_ShowFullWeek      = 0x00000020,	// Defines SwitchViewBar ShowFullWeek radio button.

	xtpCalendarCaptionBar_ScrollPrevDate    = 0x00000100,	// Defines ScrollDateBar PrevDateButton.
	xtpCalendarCaptionBar_ScrollNextDate    = 0x00000200,	// Defines ScrollDateBar NextDateButton.
	xtpCalendarCaptionBar_DateLabel         = 0x00000400	// Defines ScrollDateBar DateLabel.
};

//===========================================================================
// Summary:
//     CXTPCalendarCaptionBarControl represents CalendarCaptionBar control and
//	   used as a part of CXTPCalendarControl object. They looks and works as 
//	   a single control but separated on 2 objects for customization 
//	   possibilities.
// Remarks:
//	   This class is used as owner (host, events source) window for 
//	   CXTPCalendarCaptionBarTheme object which implements the most control logic.
//		
// See Also: CXTPCalendarCaptionBarTheme, CXTPCalendarControl
//===========================================================================
class _XTP_EXT_CLASS CXTPCalendarCaptionBarControl : public CWnd
{
	//{{AFX_CODEJOCK_PRIVATE
	DECLARE_DYNAMIC(CXTPCalendarCaptionBarControl)
	//}}AFX_CODEJOCK_PRIVATE
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Default object constructor.
	// See Also: 
	//	   ~CXTPCalendarCaptionBarControl
	//-----------------------------------------------------------------------
	CXTPCalendarCaptionBarControl();
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Default object destructor.
	// See Also: 
	//	   CXTPCalendarCaptionBarControl
	//-----------------------------------------------------------------------
	virtual ~CXTPCalendarCaptionBarControl();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function retrieves the minimum size required to show a
	//     CaptionBar control.
	// Parameters:
	//     pDC		- Pointer to a valid device context (may be NULL).
	// Remarks:
	//     This member function call CXTPCalendarCaptionBarTheme::CalcMinRect
	//	   function.	
	// Returns:
	//     A minimum rectangle required to show CaptionBar control.
	// See Also:
	//     CXTPCalendarCaptionBarTheme::CalcMinRect
	// --------------------------------------------------------------------------
	virtual CRect CalcMinRect(CDC* pDC = NULL);

	// -----------------------------------------------------------------------
	// Summary:
	//     This member function is used to create the CaptionBar control window.
	// Parameters:
	//     dwStyle :     Specifies the window style attributes.
	//     rect :        A RECT object that contains the coordinates of the
	//                   window, in the client coordinates of pParentWnd.
	//     pParentWnd :  A CWnd pointer to the parent window.
	//     nID :         A UINT that contains the ID of the child window.
	// Returns:
	//     Nonzero if successful. Otherwise 0.
	// -----------------------------------------------------------------------
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to adjust the object's layout depending
	//     on the provided bounding rectangle.
	// Parameters:
	//     pDC		- Pointer to a valid device context (may be NULL).
	//     rcRect   - A CRect object containing the dimensions of the bounding
	//               rectangle for this part.
	//-----------------------------------------------------------------------
	virtual void AdjustLayout(CDC* pDC = NULL, const CRect* prcWnd = NULL);
	
	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain pointer to
	//	   CXTPCalendarCaptionBarTheme object.
	// Returns:
	//     A pointer to CXTPCalendarCaptionBarTheme object.
	//-----------------------------------------------------------------------
	CXTPCalendarCaptionBarTheme* GetTheme();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to set theme object.
	// Parameters:
	//     pTheme - A pointer to CXTPCalendarCaptionBarTheme object.
	//-----------------------------------------------------------------------
	void SetTheme(CXTPCalendarCaptionBarTheme* pTheme);

	//-----------------------------------------------------------------------
	// Summary:
	//     Register the window class if it has not already been registered.
	// Parameters:
	//     hInstance - Instance of resource where control is located
	// Returns:
	//     TRUE if the window class was successfully registered.  FALSE otherwise.
	//-----------------------------------------------------------------------
	BOOL RegisterWindowClass(HINSTANCE hInstance = NULL);

protected:
	CXTPCalendarCaptionBarTheme* m_pTheme; // Store pointer to CXTPCalendarCaptionBarTheme object.

protected:	
	//{{AFX_CODEJOCK_PRIVATE
	afx_msg void OnPaint();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR uTimerID);
	afx_msg void OnDestroy();
//  afx_msg void OnEnable(BOOL bEnable);
//  afx_msg UINT OnGetDlgCode();
//  afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus (CWnd* pNewWnd);

	DECLARE_MESSAGE_MAP()
//}}AFX_CODEJOCK_PRIVATE
};

//===========================================================================
// Summary:
//     This class used as a base class for graphical Parts of CalendarCaptionBar 
//	   paint theme.
// See Also: CXTPCalendarCaptionBarTheme
//===========================================================================
class _XTP_EXT_CLASS CXTPCalendarCaptionBarThemePart : public CXTPCalendarWMHandler
{
	//{{AFX_CODEJOCK_PRIVATE
	friend class CXTPCalendarCaptionBarTheme;

	DECLARE_DYNAMIC(CXTPCalendarCaptionBarThemePart)
	//}}AFX_CODEJOCK_PRIVATE

public:
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Default object constructor.
	// Parameters:
	//     pTheme - Pointer to parent CXTPCalendarCaptionBarTheme object.
	//     nPartID - An object identifier (value from enum XTPEnumCalendarCaptionBarThemeObject).	
	// See Also: 
	//	   ~CXTPCalendarCaptionBarThemePart
	//-----------------------------------------------------------------------
	CXTPCalendarCaptionBarThemePart(CXTPCalendarCaptionBarTheme* pTheme, int nPartID);

	//-----------------------------------------------------------------------
	// Summary:
	//     Default object destructor.
	// See Also: 
	//	   CXTPCalendarCaptionBarThemePart
	//-----------------------------------------------------------------------
	virtual ~CXTPCalendarCaptionBarThemePart();
	
	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to adjust the object's layout depending
	//     on the provided bounding rectangle.
	// Parameters:
	//     pDC		- Pointer to a valid device context (may be NULL).
	//     rcRect   - A CRect object containing the dimensions of the bounding
	//               rectangle for this part.
	//-----------------------------------------------------------------------
	virtual void AdjustLayout(CDC* pDC, const CRect& rcRect);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to draw the part content utilizing
	//     the specified device context.
	// Parameters:
	//     pDC - Pointer to a valid device context.		
	//-----------------------------------------------------------------------
	virtual void Draw(CDC* pDC);

	//-------------------------------------------------------------------
	// Summary:
	//     Performs refreshing of graphical related parameters from
	//     system settings. Base implementation do nothing.
	//-------------------------------------------------------------------
	virtual void RefreshMetrics() {};

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function initiates the CalendarCaptionBar control's redrawing.
	// Parameters:
	//     bUpdateNow : Set this parameter to TRUE if you'd like to force
	//					control's redrawing.
	// Remarks:
	//     Call this member function if you want to request or force the control's
	//     redrawing.
	// See Also: 
	//	   CXTPCalendarCaptionBarTheme::Redraw, AdjustLayout
	//-----------------------------------------------------------------------
	virtual void Redraw(BOOL bUpdateNow = FALSE);


	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to determine is the specified point 
	//	   over visible object rectangle.
	// Parameters:
	//     pt - A CPoint object reference that contains the point to test.
	//-----------------------------------------------------------------------
	virtual BOOL HitTest(const CPoint& pt);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain pointer to parent 
	//	   CXTPCalendarCaptionBarTheme object.
	// Returns:
	//     A pointer to CXTPCalendarCaptionBarTheme object.
	//-----------------------------------------------------------------------
	virtual CXTPCalendarCaptionBarTheme* GetTheme();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain current paint theme.
	// Returns:
	//     A paint theme ID from enum XTPCalendarTheme.
	//-----------------------------------------------------------------------
	virtual XTPCalendarTheme GetPaintTheme() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain an object identifier.
	// Returns:
	//     An object ID (value from enum XTPEnumCalendarCaptionBarThemeObject).
	//-----------------------------------------------------------------------
	virtual int GetPartID();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain an object rectangle.
	// Returns:
	//     An object rectangle.
	//-----------------------------------------------------------------------
	virtual CRect GetRect();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain an object text.
	// Returns:
	//     An object text as CString.
	// See Also: SetText
	//-----------------------------------------------------------------------
	virtual CString GetText();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to set object text.
	// Parameters:
	//     pcszText - An object text to set.
	// See Also: GetText
	//-----------------------------------------------------------------------
	virtual void SetText(LPCTSTR pcszText);
	
	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to get is part object visible.
	// Returns:
	//     TRUE if object is visible, FALSE otherwise.
	// See Also: SetVisible
	//-----------------------------------------------------------------------
	virtual BOOL IsVisible();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to set visible object's state.
	// Parameters:
	//     bVisible - A BOOL value to define visible state.
	// See Also: GetVisible
	//-----------------------------------------------------------------------
	virtual void SetVisible(BOOL bVisible);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to get checked state.
	// Returns:
	//     Non-zero if object is checked, 0 (zero) otherwise.
	// See Also: SetCheck
	//-----------------------------------------------------------------------
	virtual int GetCheck();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to set checked state.
	// Parameters:
	//     nCheck - Set as Non-zero if object is checked, 0 (zero) otherwise.
	// See Also: GetCheck
	//-----------------------------------------------------------------------
	virtual void SetCheck(int nCheck);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to get object state (flags from 
	//	   CXTPCalendarCaptionBarThemePart::EStates enum).
	// Returns:
	//     Current object state flags.
	// See Also: SetState
	//-----------------------------------------------------------------------
	virtual int GetState();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to set object state as set of flags 
	//	   from CXTPCalendarCaptionBarThemePart::EStates enum.
	// Parameters:
	//     nState - Current object state flags.
	// See Also: SetState
	//-----------------------------------------------------------------------
	virtual void SetState(int nState);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to get object text color.
	// Returns:
	//     m_clrTextColor value returned if it is defined, otherwise 
	//	   GetTheme()->m_clrTextColor value returned.
	// See Also: 
	//	   CXTPCalendarCaptionBarThemePart::m_clrTextColor,
	//	   CXTPCalendarCaptionBarTheme::m_clrTextColor
	//-----------------------------------------------------------------------
	virtual COLORREF GetTextColor();

public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Defines the part object states flags.
	//-----------------------------------------------------------------------
	enum EStates
	{
		xtpBtnStateNormal       = 0,		// defines a normal state.
		xtpBtnStateMouseOver    = 0x001,	// defines a mouse over state.
		xtpBtnStatePressed      = 0x002,	// defines a pressed state.
		xtpBtnStateChecked      = 0x004,	// defines a checked state.
		xtpBtnStateFocused      = 0x008,	// defines a ficused state.
	};

	
	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to processes mouse movement events.
	// Parameters:
	//     nFlags  - A UINT that is used to indicate whether various virtual
	//               keys are down.
	//     point   - A CPoint that specifies the x- and y- coordinates of the cursor.
	//               These coordinates are always relative to the
	//               upper-left corner of the window.
	// Remarks:
	//     This method is called by the parent object when the user
	//     moves the mouse cursor.
	//-----------------------------------------------------------------------
	virtual void OnMouseMove(UINT nFlags, CPoint point);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to process left mouse button down events.
	// Parameters:
	//     nFlags  - An int that indicates whether various virtual keys are down.
	//     point   - A CPoint object that specifies the x- and y- coordinates of the cursor.
	//               These coordinates are always relative to the
	//               upper-left corner of the window.
	// Remarks:
	//     This method is called by the parent object when the user
	//     presses the left mouse button.
	//-----------------------------------------------------------------------
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to process left mouse button up events.
	// Parameters:
	//     nFlags  - An int that indicates whether various virtual keys are down.
	//     point   - A CPoint object that specifies the x- and y- coordinates of the cursor.
	//               These coordinates are always relative to the
	//               upper-left corner of the window.
	// Remarks:
	//     This method is called by the parent object when the user
	//     releases the left mouse button.
	//-----------------------------------------------------------------------
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point);
	
public:
	CXTPPaintManagerColor   m_clrTextColor;	// Store the object's text color.

protected:
	CXTPCalendarCaptionBarTheme* m_pTheme;	// Store pointer to a parent theme object.
	int m_nPartID;		// Store a Part ID.

	CRect   m_rcRect;	// Store a Part rectangle.
	CString m_strText;	// Store a Part text.
	int     m_nState;	// Store a Part state.
	BOOL    m_bVisible;	// Store a Part visible state.
};



//===========================================================================
// Summary:
//     This class CalendarCaptionBar control drawing, user interaction logic 
//	   and interaction logic with attached Calendar control.
//	   paint theme.
// See Also: CXTPCalendarCaptionBarTheme
//===========================================================================
class _XTP_EXT_CLASS CXTPCalendarCaptionBarTheme : public CXTPCalendarWMHandler
{
	//{{AFX_CODEJOCK_PRIVATE
	DECLARE_DYNCREATE(CXTPCalendarCaptionBarTheme)

	friend class CXTPCalendarCaptionBarControl;
	friend class CXTPCalendarCaptionBarThemePart;
	//}}AFX_CODEJOCK_PRIVATE

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Default object constructor.
	// See Also:
	//	   ~CXTPCalendarCaptionBarTheme
	//-----------------------------------------------------------------------
	CXTPCalendarCaptionBarTheme();

	//-----------------------------------------------------------------------
	// Summary:
	//     Default object destructor.
	// See Also:
	//	   CXTPCalendarCaptionBarTheme
	//-----------------------------------------------------------------------
	virtual ~CXTPCalendarCaptionBarTheme();

public:

	//-----------------------------------------------------------------------
	// Summary:
	//	   This class implements SwitchView button part of the SwitchViewBar.
	// See Also:
	//	   CXTPCalendarCaptionBarThemePart
	//-----------------------------------------------------------------------
	class _XTP_EXT_CLASS CSwitchViewButtonPart: public CXTPCalendarCaptionBarThemePart
	{
	public:
		//{{AFX_CODEJOCK_PRIVATE
		CSwitchViewButtonPart(CXTPCalendarCaptionBarTheme* pTheme, int nPartID) :
							CXTPCalendarCaptionBarThemePart (pTheme, nPartID) {};

		virtual void RefreshMetrics();
		virtual void AdjustLayout(CDC* pDC, const CRect& rcRect);
		virtual void Draw(CDC* pDC);
		//}}AFX_CODEJOCK_PRIVATE
	};

	//-----------------------------------------------------------------------
	// Summary:
	//	   This class implements Radio button part of the SwitchViewBar.
	// See Also:
	//	   CXTPCalendarCaptionBarThemePart
	//-----------------------------------------------------------------------
	class _XTP_EXT_CLASS CRadioButtonPart : public CXTPCalendarCaptionBarThemePart
	{
	public:
		//{{AFX_CODEJOCK_PRIVATE
		CRadioButtonPart(CXTPCalendarCaptionBarTheme* pTheme, int nPartID) :
							CXTPCalendarCaptionBarThemePart (pTheme, nPartID) {};

		virtual void AdjustLayout(CDC* pDC, const CRect& rcRect);
		virtual void RefreshMetrics();
		virtual void Draw(CDC* pDC);
		//}}AFX_CODEJOCK_PRIVATE
	};

	//-----------------------------------------------------------------------
	// Summary:
	//	   This class implements Scroll Date button part of the ScrollDateBar.
	// See Also:
	//	   CXTPCalendarCaptionBarThemePart
	//-----------------------------------------------------------------------
	class _XTP_EXT_CLASS CScrollDateButtonPart : public CXTPCalendarCaptionBarThemePart
	{
	public:
		//{{AFX_CODEJOCK_PRIVATE
		CScrollDateButtonPart(CXTPCalendarCaptionBarTheme* pTheme, int nPartID) :
							CXTPCalendarCaptionBarThemePart (pTheme, nPartID) {};

		virtual void Draw(CDC* pDC);
		virtual void AdjustLayout(CDC* pDC, const CRect& rcRect);

		virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
		virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
		//}}AFX_CODEJOCK_PRIVATE
	protected:
		//{{AFX_CODEJOCK_PRIVATE
		virtual LPCTSTR _GetImageName();

		virtual void _DrawTriangle(CDC* pDC, CPoint pt0, CPoint pt1, CPoint pt2, COLORREF clrColor);
		virtual void DrawScrollTriangle(CDC* pDC, CRect rcRect, BOOL bLeftDirection, COLORREF clrColor);
		//}}AFX_CODEJOCK_PRIVATE
	};

	//-----------------------------------------------------------------------
	// Summary:
	//	   This class implements Date Label part of the ScrollDateBar.
	// See Also:
	//	   CXTPCalendarCaptionBarThemePart
	//-----------------------------------------------------------------------
	class _XTP_EXT_CLASS CDateLabelPart : public CXTPCalendarCaptionBarThemePart
	{
	public:
		//{{AFX_CODEJOCK_PRIVATE
		CDateLabelPart(CXTPCalendarCaptionBarTheme* pTheme, int nPartID) :
							CXTPCalendarCaptionBarThemePart (pTheme, nPartID) {};

		virtual void RefreshMetrics();
		virtual void Draw(CDC* pDC);

		virtual CString _FormatDate(COleDateTime dtDay1, COleDateTime dtDay2, BOOL bShowMonthDay);
		LPCTSTR _AddSpace(CString& rStr);
		//}}AFX_CODEJOCK_PRIVATE
	public:
		CXTPCalendarThemeFontValue  m_fntTextFont; // Store the text font.		
	};


public:
	//-----------------------------------------------------------------------
	// Summary:
	//     This member function retrieves the minimum size required to show a
	//     CaptionBar control.
	// Parameters:
	//     pDC		- Pointer to a valid device context (may be NULL).
	// Returns:
	//     A minimum rectangle required to show CaptionBar control.
	// See Also:
	//     CXTPCalendarCaptionBarControl::CalcMinRect
	// --------------------------------------------------------------------------
	virtual CRect CalcMinRect(CDC* pDC = NULL);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to adjust the object's layout depending
	//     on the provided bounding rectangle.
	// Parameters:
	//     pDC		- Pointer to a valid device context (may be NULL).
	//     rcRect   - A CRect object containing the dimensions of the bounding
	//               rectangle for this part.
	//-----------------------------------------------------------------------
	virtual void AdjustLayout(CDC* pDC, const CRect& rcRect);

	//-------------------------------------------------------------------
	// Summary:
	//     Performs refreshing of graphical related parameters from
	//     system settings. Base implementation do nothing.
	//-------------------------------------------------------------------
	virtual void RefreshMetrics();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function initiates the CalendarCaptionBar control's redrawing.
	// Parameters:
	//     bUpdateNow : Set this parameter to TRUE if you'd like to force
	//					control's redrawing.
	// Remarks:
	//     Call this member function if you want to request or force the control's
	//     redrawing.
	// See Also: 
	//	   CXTPCalendarCaptionBarTheme::Redraw, AdjustLayout
	//-----------------------------------------------------------------------
	virtual void Redraw(BOOL bUpdateNow = FALSE);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member functions is used to get is CaptionBar object visible.
	// Returns:
	//     TRUE if corresponding object is visible, FALSE otherwise.
	// See Also: 
	//	   SetSwitchViewButtons, SetScrollDateButtons, SetDateLabel
	//-----------------------------------------------------------------------
	virtual BOOL IsSwitchViewButtons();
	virtual BOOL IsScrollDateButtons(); // <COMBINE IsSwitchViewButtons>
	virtual BOOL IsDateLabel();			// <COMBINE IsSwitchViewButtons>

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to set visible CaptionBar object's state.
	// Parameters:
	//     bVisible - A BOOL value to define visible state.
	// See Also: GetVisible
	//-----------------------------------------------------------------------
	virtual void SetSwitchViewButtons(BOOL bVisible);
	virtual void SetScrollDateButtons(BOOL bVisible);	// <COMBINE SetSwitchViewButtons>
	virtual void SetDateLabel(BOOL bVisible);			// <COMBINE SetSwitchViewButtons>

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain current paint theme.
	// Returns:
	//     A paint theme ID from enum XTPCalendarTheme.
	//-----------------------------------------------------------------------
	virtual XTPCalendarTheme GetPaintTheme() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to set current paint theme.
	// Parameters:
	//     ePaintTheme - A paint theme ID from enum XTPCalendarTheme.
	//-----------------------------------------------------------------------
	virtual void SetPaintTheme(XTPCalendarTheme nTheme);

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to draw the object content utilizing
	//     the specified device context.
	// Parameters:
	//     pDC - Pointer to a valid device context.		
	//-----------------------------------------------------------------------
	virtual void Draw(CDC* pDC);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain an object rectangle.
	// Returns:
	//     An object rectangle.
	//-----------------------------------------------------------------------
	virtual const CRect& GetRect();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain an owner (parent, host) window.
	// Returns:
	//     A pointer to CWnd object.
	//-----------------------------------------------------------------------
	virtual CWnd* GetOwnerWnd();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to set owner (parent, host) window.
	// Remarks:
	//	   CXTPCalendarCaptionBarControl::SetTheme call this method.
	// Parameters:
	//     pCaptionBar - A pointer to CXTPCalendarCaptionBarControl window.
	//-----------------------------------------------------------------------
	virtual void SetOwner(CXTPCalendarCaptionBarControl* pCaptionBar);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to attach to CalendarControl to interact 
	//	   as a single control.
	// Parameters:
	//     pCalendar - A pointer to CXTPCalendarControl object or set as NULL 
	//				   to detach from calendar.
	// See Also: GetCalendarCtrl
	//-----------------------------------------------------------------------
	virtual void AttachCalendar(CXTPCalendarControl* pCalendar);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to obtain attached calendar control.
	// Returns:
	//     A pointer to CXTPCalendarControl object.
	//-----------------------------------------------------------------------
	virtual CXTPCalendarControl* GetCalendarCtrl();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is called to update CaptionBar controls states
	//	   correspondingly to attached calendar control.
	//-----------------------------------------------------------------------
	virtual void UpdateControlsState();

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is used to read color by name from resources.
	// Returns:
	//     A RGB color value.
	//-----------------------------------------------------------------------
	virtual COLORREF GetColor2(LPCTSTR pcszColorName, COLORREF clrDefault);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is called when user click on the caption bar 
	//	   element (part).
	// Parameters:
	//     nPartID - An identifier of clicked part object.
	//-----------------------------------------------------------------------
	virtual void OnPartClick(int nPartID);

protected:
	
	//{{AFX_CODEJOCK_PRIVATE
	virtual int GetChildHandlersCount();
	virtual CXTPCalendarWMHandler* GetChildHandlerAt(int nIndex);

	virtual void OnBeforeDestroy();
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnTimer(UINT_PTR uTimerID);

	virtual void OnKillFocus (CWnd* pNewWnd);
	virtual BOOL _UpdateControlsHotState(BOOL* pbMouseLeave = NULL);
	//}}AFX_CODEJOCK_PRIVATE

protected:

	CXTPCalendarCaptionBarControl* m_pCaptionBar; // Store pointer owner CaptionBar control.
	CXTPCalendarControl* m_pCalendar;	// Store pointer attached calendar control.

	CRect m_rcRect;						// Store object rect.
	UINT_PTR m_nCheckHotStateTimerID;	// Store timer ID to refresh controls hot state.

	XTPCalendarTheme m_nPaintTheme;		// Store current paint theme.

protected:

	CSwitchViewButtonPart*  m_pButtonViewDay;	// Store Swich to DayView button part object.
	CSwitchViewButtonPart*  m_pButtonViewWeek;	// Store Swich to WeekView button part object.
	CSwitchViewButtonPart*  m_pButtonViewMonth;	// Store Swich to MonthView button part object.

	CRadioButtonPart* m_pShowWorkWeek;	// Store Show Work Week radio button part object.
	CRadioButtonPart* m_pShowFullWeek;	// Store Show Full Week radio button part object.
	
	//---------------------------------
	CScrollDateButtonPart*  m_pScrollPrevDate;	// Store Scroll Date Prev button part object.
	CScrollDateButtonPart*  m_pScrollNextDate;	// Store Scroll Date Next button part object.
	CDateLabelPart*         m_pDateLabel;		// Store Date Label part object.

	//---------------------------------
	BOOL m_bIsSwitchViewButtons;	// Store option is SwitchViewBar visible. 
	BOOL m_bIsScrollDateButtons;	// Store option is ScrollDate buttons visible.
	BOOL m_bIsDateLabel;			// Store option is date Label visible.

public:
	
	CXTPPaintManagerColor   m_clrSwitchViewBarBk;	// Store SwitchViewBar background color.
	CXTPPaintManagerColor   m_clrScrollDateBarBk;	// Store ScrollDateBar background color.	
	CXTPPaintManagerColor   m_clrBorders;			// Store ScrollDateBar background color.

	CXTPCalendarThemeFontValue  m_fntTextFont;		// Store the text font.
	CXTPPaintManagerColor       m_clrTextColor;		// Store the text color.

public:
	//{{AFX_CODEJOCK_PRIVATE
	typedef CXTPCalendarPtrCollectionT<CXTPCalendarCaptionBarThemePart> CThemePartsArray;
	CThemePartsArray            m_arMembers;
	CXTPWinThemeWrapper     m_themeButton;
	//}}AFX_CODEJOCK_PRIVATE

protected:
	//{{AFX_CODEJOCK_PRIVATE
	DECLARE_XTP_SINK(CXTPCalendarCaptionBarTheme, m_Sink)
	virtual void OnEvent_Calendar(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam);
	virtual void OnEvent_Office2007ImagesChanged(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam);
	//}}AFX_CODEJOCK_PRIVATE
};

/////////////////////////////////////////////////////////////////////////////
AFX_INLINE CRect CXTPCalendarCaptionBarControl::CalcMinRect(CDC* pDC) {
	return m_pTheme ? m_pTheme->CalcMinRect(pDC) : CRect(0, 0, 0, 0);
}

AFX_INLINE CXTPCalendarControl* CXTPCalendarCaptionBarTheme::GetCalendarCtrl() {
	return m_pCalendar;
}

AFX_INLINE CXTPCalendarCaptionBarTheme* CXTPCalendarCaptionBarControl::GetTheme() {
	return m_pTheme;
}

AFX_INLINE const CRect& CXTPCalendarCaptionBarTheme::GetRect() {
	return m_rcRect;
}
AFX_INLINE CWnd* CXTPCalendarCaptionBarTheme::GetOwnerWnd() {
	return m_pCaptionBar;
}
AFX_INLINE BOOL CXTPCalendarCaptionBarTheme::IsSwitchViewButtons() {
	return m_bIsSwitchViewButtons;
}
AFX_INLINE BOOL CXTPCalendarCaptionBarTheme::IsScrollDateButtons() {
	return m_bIsScrollDateButtons;
}
AFX_INLINE BOOL CXTPCalendarCaptionBarTheme::IsDateLabel() {
	return m_bIsDateLabel;
}
AFX_INLINE void CXTPCalendarCaptionBarTheme::SetSwitchViewButtons(BOOL bVisible) {
	m_bIsSwitchViewButtons = bVisible;
	Redraw();
}
AFX_INLINE void CXTPCalendarCaptionBarTheme::SetScrollDateButtons(BOOL bVisible) {
	m_bIsScrollDateButtons = bVisible;
	Redraw();
}
AFX_INLINE void CXTPCalendarCaptionBarTheme::SetDateLabel(BOOL bVisible) {
	m_bIsDateLabel = bVisible;
	Redraw();
}
AFX_INLINE XTPCalendarTheme CXTPCalendarCaptionBarTheme::GetPaintTheme() const {
	return m_nPaintTheme;
}
AFX_INLINE void CXTPCalendarCaptionBarTheme::SetPaintTheme(XTPCalendarTheme nTheme) {
	m_nPaintTheme = nTheme;
	RefreshMetrics();
	Redraw();
}

AFX_INLINE CXTPCalendarCaptionBarTheme* CXTPCalendarCaptionBarThemePart::GetTheme() {
	return m_pTheme;
}
AFX_INLINE XTPCalendarTheme CXTPCalendarCaptionBarThemePart::GetPaintTheme() const {
	return m_pTheme ? m_pTheme->GetPaintTheme() : xtpCalendarThemeUnknown;
}

AFX_INLINE CRect CXTPCalendarCaptionBarThemePart::GetRect() {
	return m_rcRect;
}

AFX_INLINE CString CXTPCalendarCaptionBarThemePart::GetText() {
	return m_strText;
}

AFX_INLINE void CXTPCalendarCaptionBarThemePart::SetText(LPCTSTR pcszText) {
	m_strText = pcszText;
}

AFX_INLINE int CXTPCalendarCaptionBarThemePart::GetPartID() {
	return m_nPartID;
}

AFX_INLINE BOOL CXTPCalendarCaptionBarThemePart::IsVisible() {
	return m_bVisible;
}

AFX_INLINE void CXTPCalendarCaptionBarThemePart::SetVisible(BOOL bVisible) {
	m_bVisible = bVisible;
}

AFX_INLINE int CXTPCalendarCaptionBarThemePart::GetCheck() {
	return !!(m_nState & xtpBtnStateChecked);
}

AFX_INLINE void CXTPCalendarCaptionBarThemePart::SetCheck(int nCheck) {
	if (nCheck)
		m_nState = m_nState | xtpBtnStateChecked;
	else
		m_nState = m_nState & (~xtpBtnStateChecked);
}

AFX_INLINE int CXTPCalendarCaptionBarThemePart::GetState() {
	return m_nState;
}

AFX_INLINE void CXTPCalendarCaptionBarThemePart::SetState(int nState) {
	m_nState = nState;
}

#endif // !defined(__XTPCalendarCaptionBarControl_H__)
