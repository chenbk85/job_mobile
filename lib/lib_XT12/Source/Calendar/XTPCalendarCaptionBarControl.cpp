// // XTPCalendarCaptionBarControl.cpp : implementation file
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

#include "stdafx.h"
#include "Resource.h"

#include "Common/XTPResourceManager.h"
#include "Common/XTPOffice2007Image.h"

#include "XTPCalendarUtils.h"
#include "XTPCalendarThemeOffice2007.h"
#include "XTPCalendarControl.h"
#include "XTPCalendarCaptionBarControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CXTPCalendarCaptionBarControl, CWnd)
IMPLEMENT_DYNAMIC(CXTPCalendarCaptionBarThemePart, CXTPCalendarWMHandler)
IMPLEMENT_DYNCREATE(CXTPCalendarCaptionBarTheme, CXTPCalendarWMHandler)

CXTPCalendarCaptionBarControl::CXTPCalendarCaptionBarControl()
{
	RegisterWindowClass();

	m_pTheme = NULL;
	SetTheme(new CXTPCalendarCaptionBarTheme());
}

CXTPCalendarCaptionBarControl::~CXTPCalendarCaptionBarControl()
{
	CMDTARGET_RELEASE(m_pTheme);
}

BOOL CXTPCalendarCaptionBarControl::RegisterWindowClass(HINSTANCE hInstance /*= NULL*/)
{
	return XTPDrawHelpers()->RegisterWndClass(hInstance,
			XTPCALENDARCAPTIONBAR_CLASSNAME, /*CS_DBLCLKS |*/ CS_HREDRAW | CS_VREDRAW);
}

BOOL CXTPCalendarCaptionBarControl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if (!CWnd::Create(XTPCALENDARCAPTIONBAR_CLASSNAME, NULL, dwStyle, rect, pParentWnd, nID))
		return FALSE;

	AdjustLayout(NULL);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CXTPCalendarCaptionBarControl, CWnd)
//{{AFX_MSG_MAP(CXTPCalendarControl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_KILLFOCUS()
	ON_WM_DESTROY()
//  ON_WM_GETDLGCODE()
	ON_WM_ENABLE()
	ON_WM_TIMER()
//}}AFX_MSG_MAP

END_MESSAGE_MAP()


void CXTPCalendarCaptionBarControl::SetTheme(CXTPCalendarCaptionBarTheme* pTheme)
{
	ASSERT(pTheme);
	if (pTheme)
	{
		CMDTARGET_RELEASE(m_pTheme);
		m_pTheme = pTheme;
		m_pTheme->SetOwner(this);
		m_pTheme->RefreshMetrics();
	}
}

void CXTPCalendarCaptionBarControl::AdjustLayout(CDC* pDC, const CRect* prcWnd)
{
	CXTPClientRect rcClient(this);

	if (prcWnd)
		((CRect&)rcClient) = *prcWnd;

	if (m_pTheme)
		m_pTheme->AdjustLayout(pDC, rcClient);
}

void CXTPCalendarCaptionBarControl::OnPaint()
{
	CXTPClientRect rc(this);

	if (rc.IsRectEmpty())
		return;

	CPaintDC dc(this); // device context for painting

	CXTPBufferDC memDC(dc.GetSafeHdc(), rc);
	//memDC.FillSolidRect(rc, m_crBack);

	if (m_pTheme)
		m_pTheme->Draw(&memDC);
}

BOOL CXTPCalendarCaptionBarControl::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void CXTPCalendarCaptionBarControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (!GetSafeHwnd())
		return;

	CRect rcRect(0, 0, cx, cy);
	if (m_pTheme)
		m_pTheme->AdjustLayout(NULL, rcRect);

}

void CXTPCalendarCaptionBarControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pTheme)
		m_pTheme->OnLButtonDown(nFlags, point);

	if (GetCapture() != this)
		SetCapture();
}

void CXTPCalendarCaptionBarControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_pTheme)
		m_pTheme->OnLButtonUp(nFlags, point);

	if (GetCapture() == this)
		ReleaseCapture();
}

void CXTPCalendarCaptionBarControl::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pTheme)
		m_pTheme->OnMouseMove(nFlags, point);
}

void CXTPCalendarCaptionBarControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_pTheme)
		m_pTheme->OnKeyDown(nChar, nRepCnt, nFlags);
}

void CXTPCalendarCaptionBarControl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_pTheme)
		m_pTheme->OnKeyUp(nChar, nRepCnt, nFlags);
}

void CXTPCalendarCaptionBarControl::OnTimer(UINT_PTR uTimerID)
{
	if (m_pTheme)
		m_pTheme->OnTimer(uTimerID);
}

void CXTPCalendarCaptionBarControl::OnDestroy()
{
	if (m_pTheme)
		m_pTheme->OnBeforeDestroy();
}

void CXTPCalendarCaptionBarControl::OnKillFocus (CWnd* pNewWnd)
{
	if (m_pTheme)
		m_pTheme->OnKillFocus(pNewWnd);
}
//////////////////////////////////////////////////////////////////////////

CXTPCalendarCaptionBarTheme::CXTPCalendarCaptionBarTheme()
{
	m_pCaptionBar   = NULL;
	m_pCalendar     = NULL;
	m_nCheckHotStateTimerID = 0;

	m_bIsSwitchViewButtons = TRUE;
	m_bIsScrollDateButtons = TRUE;
	m_bIsDateLabel = TRUE;

	m_pButtonViewDay = new CSwitchViewButtonPart(this, xtpCalendarCaptionBar_ButtonViewDay);
	m_pButtonViewWeek = new CSwitchViewButtonPart(this, xtpCalendarCaptionBar_ButtonViewWeek);
	m_pButtonViewMonth = new CSwitchViewButtonPart(this, xtpCalendarCaptionBar_ButtonViewMonth);

	m_pButtonViewDay->SetText(XTPResourceManager()->LoadString(XTP_IDS_CALENDAR_DAY));
	m_pButtonViewWeek->SetText(XTPResourceManager()->LoadString(XTP_IDS_CALENDAR_WEEK));
	m_pButtonViewMonth->SetText(XTPResourceManager()->LoadString(XTP_IDS_CALENDAR_MONTH));

	m_pShowWorkWeek = new CRadioButtonPart(this, xtpCalendarCaptionBar_ShowWorkWeek);
	m_pShowFullWeek = new CRadioButtonPart(this, xtpCalendarCaptionBar_ShowFullWeek);

	m_pShowWorkWeek->SetText(XTPResourceManager()->LoadString(XTP_IDS_CALENDAR_SHOWWORKWEK));
	m_pShowFullWeek->SetText(XTPResourceManager()->LoadString(XTP_IDS_CALENDAR_SHOWFULLKWEK));

	m_pShowWorkWeek->SetCheck(1);
	m_pShowFullWeek->SetCheck(0);

	//---------------------------------
	m_pScrollPrevDate = new CScrollDateButtonPart(this, xtpCalendarCaptionBar_ScrollPrevDate);
	m_pScrollNextDate = new CScrollDateButtonPart(this, xtpCalendarCaptionBar_ScrollNextDate);

	m_pDateLabel = new CDateLabelPart(this, xtpCalendarCaptionBar_DateLabel);

	m_nPaintTheme = xtpCalendarThemeOffice2007;

	RefreshMetrics();
}

CXTPCalendarCaptionBarTheme::~CXTPCalendarCaptionBarTheme()
{
	m_Sink.UnadviseAll();

	CMDTARGET_RELEASE(m_pButtonViewDay);
	CMDTARGET_RELEASE(m_pButtonViewWeek);
	CMDTARGET_RELEASE(m_pButtonViewMonth);

	CMDTARGET_RELEASE(m_pShowWorkWeek);
	CMDTARGET_RELEASE(m_pShowFullWeek);

	CMDTARGET_RELEASE(m_pScrollPrevDate);
	CMDTARGET_RELEASE(m_pScrollNextDate);

	CMDTARGET_RELEASE(m_pDateLabel);

	CMDTARGET_RELEASE(m_pCalendar);
}

void CXTPCalendarCaptionBarTheme::OnBeforeDestroy()
{
	m_Sink.UnadviseAll();
	CMDTARGET_RELEASE(m_pCalendar);
}

void CXTPCalendarCaptionBarTheme::SetOwner(CXTPCalendarCaptionBarControl* pCaptionBar)
{
	ASSERT(pCaptionBar);
	if (pCaptionBar)
	{
		m_pCaptionBar = pCaptionBar;
	}
}

void CXTPCalendarCaptionBarTheme::AttachCalendar(CXTPCalendarControl* pCalendar)
{
	m_Sink.UnadviseAll();
	CMDTARGET_RELEASE(m_pCalendar);

	m_pCalendar = pCalendar;
	CMDTARGET_ADDREF(m_pCalendar);

	if (m_pCalendar && m_pCalendar->GetConnection())
	{
		CXTPNotifyConnection* pConn = m_pCalendar->GetConnection();

		m_Sink.Advise(pConn, XTP_NC_CALENDARVIEWWASCHANGED, &CXTPCalendarCaptionBarTheme::OnEvent_Calendar);
		m_Sink.Advise(pConn, XTP_NC_CALENDAR_THEME_CHANGED, &CXTPCalendarCaptionBarTheme::OnEvent_Calendar);

		UpdateControlsState();

		if (XTPOffice2007Images() && XTPOffice2007Images()->GetConnection())
		{
			m_Sink.Advise(XTPOffice2007Images()->GetConnection(), XTP_NC_COMMON_OFFICE2007IMAGES_CHANGED,
						   &CXTPCalendarCaptionBarTheme::OnEvent_Office2007ImagesChanged);
		}
	}
}

int CXTPCalendarCaptionBarTheme::GetChildHandlersCount()
{
	return m_arMembers.GetCount();
}

CXTPCalendarWMHandler* CXTPCalendarCaptionBarTheme::GetChildHandlerAt(int nIndex)
{
	return m_arMembers.GetAt(nIndex);
}

void CXTPCalendarCaptionBarTheme::OnMouseMove(UINT nFlags, CPoint point)
{
	CXTPCalendarWMHandler::OnMouseMove(nFlags, point);

	if (GetOwnerWnd() && m_nCheckHotStateTimerID == 0)
	{
		m_nCheckHotStateTimerID = GetOwnerWnd()->SetTimer(1, 100, NULL);
	}
}

BOOL CXTPCalendarCaptionBarTheme::OnTimer(UINT_PTR uTimerID)
{
	if (uTimerID == m_nCheckHotStateTimerID && GetOwnerWnd() &&
		::GetCapture() != GetOwnerWnd()->GetSafeHwnd())
	{
		BOOL bMouseLeave;
		BOOL bChanged = _UpdateControlsHotState(&bMouseLeave);

		if (bMouseLeave)
		{
			GetOwnerWnd()->KillTimer(1);
			m_nCheckHotStateTimerID = 0;
		}

		if (bChanged)
			GetOwnerWnd()->Invalidate(FALSE);

		return TRUE;
	}
	return FALSE;
}

CRect CXTPCalendarCaptionBarTheme::CalcMinRect(CDC* /*pDC*/)
{
	if (!IsSwitchViewButtons() &&
		!IsScrollDateButtons() &&
		!IsDateLabel())
	{
		return CRect(0, 0, 0, 0);
	}

	CRect rc(0, 0, 525, 71);

	if (!IsSwitchViewButtons())
		rc.bottom -= 27;

	if (!IsScrollDateButtons() && !IsDateLabel())
		rc.bottom -= 33;

	return rc;
};

void CXTPCalendarCaptionBarTheme::AdjustLayout(CDC* pDC, const CRect& rcRect)
{
	if (!pDC && GetOwnerWnd() && GetOwnerWnd()->m_hWnd)
	{
		CClientDC dc(GetOwnerWnd());
		AdjustLayout(&dc, rcRect);
		return;
	}

	m_rcRect = rcRect;
	CRect rc00(rcRect.left, rcRect.top, rcRect.left, rcRect.top);

	CRect rc = m_rcRect;
	//rc.DeflateRect(1, 1, 1, 0);
	rc.DeflateRect(0, 1, 0, 0);

	int nNextY = rc.top;

	m_pButtonViewDay->SetVisible(IsSwitchViewButtons());
	m_pButtonViewWeek->SetVisible(IsSwitchViewButtons());
	m_pButtonViewMonth->SetVisible(IsSwitchViewButtons());

	if (IsSwitchViewButtons())
	{
		rc.bottom = rc.top + 26;

		rc.right = rc.left + 83;
		m_pButtonViewDay->AdjustLayout(pDC, rc);

		rc.left = m_pButtonViewDay->GetRect().right;
		rc.right = rc.left + 83;
		m_pButtonViewWeek->AdjustLayout(pDC, rc);

		rc.left = m_pButtonViewWeek->GetRect().right;
		rc.right = rc.left + 83;
		m_pButtonViewMonth->AdjustLayout(pDC, rc);

		//--------------------------------------
		rc.left = m_pButtonViewMonth->GetRect().right + 21;
		rc.right = rc.left + 5;
		m_pShowWorkWeek->AdjustLayout(pDC, rc);

		rc.left = m_pShowWorkWeek->GetRect().right + 11;
		rc.right = rc.left + 5;
		m_pShowFullWeek->AdjustLayout(pDC, rc);

		//--------------------------------------
		// to align next controls
		rc = m_pButtonViewDay->GetRect();
		nNextY = rc.bottom + 1;
	}
	else
	{
		m_pButtonViewDay->AdjustLayout(pDC, rc00);
		m_pButtonViewWeek->AdjustLayout(pDC, rc00);
		m_pButtonViewMonth->AdjustLayout(pDC, rc00);

		m_pShowWorkWeek->SetVisible(FALSE);
		m_pShowFullWeek->SetVisible(FALSE);
		m_pShowWorkWeek->AdjustLayout(pDC, rc00);
		m_pShowFullWeek->AdjustLayout(pDC, rc00);

		nNextY = rc.top;
	}

	int nNextX = rc.left;
	//--------------------------------------
	m_pScrollPrevDate->SetVisible(IsScrollDateButtons());
	m_pScrollNextDate->SetVisible(IsScrollDateButtons());

	if (IsScrollDateButtons())
	{
		rc.top = nNextY + 12;
		rc.bottom = rc.top + 20;
		rc.left += 20;
		rc.right = rc.left + 20;
		m_pScrollPrevDate->AdjustLayout(pDC, rc);

		rc.left = m_pScrollPrevDate->GetRect().right + 9;
		rc.right = rc.left + 20;
		m_pScrollNextDate->AdjustLayout(pDC, rc);

		nNextX = rc.right;
	}
	else
	{
		m_pScrollPrevDate->AdjustLayout(pDC, rc00);
		m_pScrollNextDate->AdjustLayout(pDC, rc00);
	}

	//--------------------------------------
	m_pDateLabel->SetVisible(IsDateLabel());

	if (IsDateLabel())
	{
		rc.top = nNextY + 12;
		rc.bottom = rc.top + 20;
		rc.left = nNextX + 11;
		rc.right = m_rcRect.right - 2;
		m_pDateLabel->AdjustLayout(pDC, rc);
	}
	else
	{
		m_pDateLabel->AdjustLayout(pDC, rc00);
	}
}

COLORREF CXTPCalendarCaptionBarTheme::GetColor2(LPCTSTR pcszColorName, COLORREF clrDefault)
{
	COLORREF clrColor = COLORREF_NULL;

	if (XTPOffice2007Images()->IsValid())
	{
		clrColor = XTPOffice2007Images()->GetImageColor(_T("CalendarControl"), pcszColorName);
	}

	if (clrColor == COLORREF_NULL)
	{
		clrColor = clrDefault;
	}

	return clrColor;
}

void CXTPCalendarCaptionBarTheme::RefreshMetrics()
{
	m_themeButton.OpenTheme(0, L"BUTTON");

	LOGFONT lfBaseFont;
	::ZeroMemory(&lfBaseFont, sizeof(lfBaseFont));
	BOOL bUseFont2007 = FALSE;

	if (GetPaintTheme() >= xtpCalendarThemeOffice2007)
	{
		m_clrSwitchViewBarBk.SetStandardValue(GetColor2(_T("CaptionBarSwitchViewBarBk"), RGB(173, 209, 255)));
		m_clrScrollDateBarBk.SetStandardValue(GetColor2(_T("CaptionBarDateBarBk"), RGB(227, 239, 255)));

		m_clrBorders.SetStandardValue(GetColor2(_T("CaptionBarBorders"), RGB(101, 147, 201)));
		m_clrTextColor.SetStandardValue(RGB(0, 0, 0));

		// Try to set default Office 2007 font,
		// otherwise icon font used.
		bUseFont2007 = XTPDrawHelpers()->FontExists(XTP_CALENDAR_OFFICE2007_FONT_NAME);
	}
	else
	{
		//m_clrSwitchViewBarBk.SetStandardValue(RGB(192, 192, 192));
		m_clrSwitchViewBarBk.SetStandardValue(GetSysColor(COLOR_BTNFACE));

		if (GetPaintTheme() == xtpCalendarThemeOffice2000)
			m_clrScrollDateBarBk.SetStandardValue(RGB(146, 146, 146));
		else
			m_clrScrollDateBarBk.SetStandardValue(RGB(130, 130, 130));

		m_clrBorders.SetStandardValue(RGB(130, 130, 130));
		m_clrTextColor.SetStandardValue(RGB(255, 255, 255));
	}

	if (bUseFont2007)
	{
		STRCPY_S(lfBaseFont.lfFaceName, LF_FACESIZE, XTP_CALENDAR_OFFICE2007_FONT_NAME);
		lfBaseFont.lfCharSet = DEFAULT_CHARSET;
		lfBaseFont.lfHeight = -11;
		lfBaseFont.lfWeight = FW_NORMAL;

		if (XTPSystemVersion()->IsClearTypeTextQualitySupported())
			lfBaseFont.lfQuality = 5;
	}
	else
	{
		VERIFY(::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lfBaseFont), &lfBaseFont, 0));
	}

	m_fntTextFont.SetStandardValue(&lfBaseFont);

	//-----------------------------------------------
	int nCount = m_arMembers.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CXTPCalendarCaptionBarThemePart* pPart = m_arMembers.GetAt(i);
		ASSERT(pPart);
		if (pPart)
			pPart->RefreshMetrics();
	}

	//-----------------------------------------------
	AdjustLayout(NULL, GetRect());
}

void CXTPCalendarCaptionBarTheme::Draw(CDC* pDC)
{

#ifdef _DEBUG
	pDC->FillSolidRect(GetRect(), RGB(255, 0, 0));
#endif

	//_UpdateControlsHotState();

	// Fill SwitchViewBar
	CRect rcTopPart = m_pButtonViewDay->GetRect();
	rcTopPart.right = m_rcRect.right;
	pDC->FillSolidRect(rcTopPart, m_clrSwitchViewBarBk);

	rcTopPart.top = rcTopPart.bottom;
	rcTopPart.bottom++;
	pDC->FillSolidRect(rcTopPart, m_clrBorders); // m_clrSwitchViewBarBottomBorder);

	// Fill ScrollDateBar
	CRect rcBottomPart = m_rcRect;
	rcBottomPart.top = rcTopPart.bottom;
	pDC->FillSolidRect(rcBottomPart, m_clrScrollDateBarBk);

	// Draw borders
	CRect rc = m_rcRect;

	rc.bottom = rc.top + 1;
	pDC->FillSolidRect(rc, m_clrBorders);

	// Draw members
	int nCount = m_arMembers.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CXTPCalendarCaptionBarThemePart* pPart = m_arMembers.GetAt(i);
		ASSERT(pPart);
		if (pPart)
			pPart->Draw(pDC);
	}
}


//////////////////////////////////////////////////////////////////////////
CXTPCalendarCaptionBarThemePart::CXTPCalendarCaptionBarThemePart(CXTPCalendarCaptionBarTheme* pTheme, int nPartID)
{
	ASSERT(pTheme);
	m_pTheme = pTheme;
	m_nPartID = nPartID;
	m_nState = xtpBtnStateNormal;
	m_bVisible = TRUE;

	if (m_pTheme)
		m_pTheme->m_arMembers.Add(this, TRUE);
}

CXTPCalendarCaptionBarThemePart::~CXTPCalendarCaptionBarThemePart()
{

}

void CXTPCalendarCaptionBarThemePart::AdjustLayout(CDC* /*pDC*/, const CRect& rcRect)
{
	m_rcRect = rcRect;
}

COLORREF CXTPCalendarCaptionBarThemePart::GetTextColor()
{
	if (m_clrTextColor.IsDefaultValue() && m_pTheme)
		return (COLORREF)m_pTheme->m_clrTextColor;

	return (COLORREF)m_clrTextColor;
}

void CXTPCalendarCaptionBarThemePart::Draw(CDC* /*pDC*/)
{
//  if (!IsVisible())
//      return;
//
//#ifdef _DEBUG
//  if (m_nState == xtpBtnStateMouseOver)
//  {
//      pDC->FillSolidRect(GetRect(), RGB(155, 0, 0));
//  }
//  else if (m_nState & xtpBtnStatePressed)
//  {
//      pDC->FillSolidRect(GetRect(), RGB(255, 0, 0));
//  }
//  else if (m_nState & xtpBtnStateChecked)
//  {
//      pDC->FillSolidRect(GetRect(), RGB(0, 0, 0));
//  }
//  else
//      pDC->FillSolidRect(GetRect(), RGB(51 * m_nPartID % 255, 51 * m_nPartID % 255, 111 * m_nPartID % 255));
//
//#endif

};

BOOL CXTPCalendarCaptionBarThemePart::HitTest(const CPoint& pt)
{
	return IsVisible() && m_rcRect.PtInRect(pt);
};

void CXTPCalendarCaptionBarThemePart::Redraw(BOOL bUpdateNow)
{
	if (m_pTheme)
		m_pTheme->Redraw(bUpdateNow);
}

void CXTPCalendarCaptionBarTheme::Redraw(BOOL bUpdateNow)
{
	if (GetOwnerWnd() && GetOwnerWnd()->GetSafeHwnd())
	{
		GetOwnerWnd()->Invalidate(FALSE);

		if (bUpdateNow)
			GetOwnerWnd()->UpdateWindow();
	}
}

void CXTPCalendarCaptionBarThemePart::OnMouseMove(UINT nFlags, CPoint point)
{
	UNREFERENCED_PARAMETER(nFlags);

	int nStatePrev = m_nState;

	if (HitTest(point))
		m_nState = m_nState | xtpBtnStateMouseOver;
	else
		m_nState = m_nState & (~(xtpBtnStateMouseOver));

	if (nStatePrev != m_nState)
		Redraw();
}

BOOL CXTPCalendarCaptionBarThemePart::OnLButtonDown(UINT nFlags, CPoint point)
{
	UNREFERENCED_PARAMETER(nFlags);

	int nStatePrev = m_nState;

	BOOL bHitTest = HitTest(point);
	if (bHitTest)
	{
		m_nState = m_nState | xtpBtnStatePressed | xtpBtnStateFocused;
	}
	else
		m_nState = m_nState & (~(xtpBtnStatePressed | xtpBtnStateFocused));

	if (nStatePrev != m_nState)
		Redraw();

	return FALSE; // to allow receive this notification for all other parts (to clear state)
}

BOOL CXTPCalendarCaptionBarThemePart::OnLButtonUp(UINT nFlags, CPoint point)
{
	UNREFERENCED_PARAMETER(nFlags);

	int nStatePrev = m_nState;
	BOOL bHitTest = HitTest(point);

//  if (bHitTest)
//  {
//      TRACE(_T("%d = [PartID=%d] CXTPCalendarCaptionBarThemePart::OnLButtonUP(%d, %d) \n"), dbg_xtp_Counter++,
//                      m_nPartID, point.x, point.y);
//  }

	if (bHitTest && (m_nState & (xtpBtnStatePressed | xtpBtnStateFocused)))
	{
		m_nState = m_nState & (~xtpBtnStatePressed);

		if (m_pTheme && IsVisible())
			m_pTheme->OnPartClick(m_nPartID);
	}

	m_nState = m_nState & (~xtpBtnStatePressed);

	if (nStatePrev != m_nState)
		Redraw();

	return FALSE; // to allow receive this notification for all other parts (to clear state)
}

void CXTPCalendarCaptionBarTheme::OnEvent_Calendar(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam); UNREFERENCED_PARAMETER(lParam);


	if (Event == XTP_NC_CALENDARVIEWWASCHANGED)
	{
		UpdateControlsState();
	}
	else if (Event == XTP_NC_CALENDAR_THEME_CHANGED)
	{
		SetPaintTheme(GetCalendarCtrl()->GetPaintTheme());
	}
	else {
		ASSERT(FALSE);
		return;
	}

	if (GetOwnerWnd())
		GetOwnerWnd()->Invalidate(FALSE);
}

void CXTPCalendarCaptionBarTheme::OnEvent_Office2007ImagesChanged(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam); UNREFERENCED_PARAMETER(lParam);

	if (Event == XTP_NC_COMMON_OFFICE2007IMAGES_CHANGED)
	{
		RefreshMetrics();

		Redraw();
	}
}

void CXTPCalendarCaptionBarTheme::UpdateControlsState()
{
	if (!GetCalendarCtrl() || !GetCalendarCtrl()->GetActiveView())
	{
		return;
	}

	m_pShowWorkWeek->SetVisible(FALSE);
	m_pShowFullWeek->SetVisible(FALSE);

	m_pButtonViewDay->SetCheck(0);
	m_pButtonViewWeek->SetCheck(0);
	m_pButtonViewMonth->SetCheck(0);

	int nViewType = GetCalendarCtrl()->GetActiveView()->GetViewType();

	if (nViewType == xtpCalendarDayView)
	{
		m_pButtonViewDay->SetCheck(1);
	}
	else if (nViewType == xtpCalendarMonthView)
	{
		m_pButtonViewMonth->SetCheck(1);
	}
	else if (nViewType == xtpCalendarWeekView)
	{
		// the theme 2003 view type.
	}
	else
	{
		m_pButtonViewWeek->SetCheck(1);

		if (IsSwitchViewButtons())
		{
			m_pShowWorkWeek->SetVisible(TRUE);
			m_pShowFullWeek->SetVisible(TRUE);
		}

		if (nViewType == xtpCalendarWorkWeekView)
		{
			m_pShowWorkWeek->SetCheck(1);
			m_pShowFullWeek->SetCheck(0);
		}
		else if (nViewType == xtpCalendarFullWeekView)
		{
			m_pShowWorkWeek->SetCheck(0);
			m_pShowFullWeek->SetCheck(1);
		}
		else {
			ASSERT(FALSE);
		}
	}
}

void CXTPCalendarCaptionBarTheme::OnPartClick(int nPartID)
{

//  TRACE(_T("%d = CXTPCalendarCaptionBarTheme::OnPartClick(PartID=%d) \n"), dbg_xtp_Counter++, nPartID);

	//CWaitCursor _wc;

	if (!GetCalendarCtrl() || !GetCalendarCtrl()->GetActiveView())
	{
		ASSERT(FALSE);
		return;
	}

	if (nPartID == xtpCalendarCaptionBar_ButtonViewDay)
	{
		GetCalendarCtrl()->SwitchActiveView(xtpCalendarDayView);

		GetCalendarCtrl()->SetFocus();
	}
	else if (nPartID == xtpCalendarCaptionBar_ButtonViewWeek)
	{
		if (m_pShowWorkWeek->GetCheck())
			GetCalendarCtrl()->SwitchActiveView(xtpCalendarWorkWeekView);
		else
			GetCalendarCtrl()->SwitchActiveView(xtpCalendarFullWeekView);

		GetCalendarCtrl()->SetFocus();
	}
	else if (nPartID == xtpCalendarCaptionBar_ButtonViewMonth)
	{
		GetCalendarCtrl()->SwitchActiveView(xtpCalendarMonthView);

		GetCalendarCtrl()->SetFocus();
	}
	else if (nPartID == xtpCalendarCaptionBar_ShowWorkWeek)
	{
		GetCalendarCtrl()->SwitchActiveView(xtpCalendarWorkWeekView);

		GetCalendarCtrl()->SetFocus();
	}
	else if (nPartID == xtpCalendarCaptionBar_ShowFullWeek)
	{
		GetCalendarCtrl()->SwitchActiveView(xtpCalendarFullWeekView);

		GetCalendarCtrl()->SetFocus();
	}
	else if (nPartID == xtpCalendarCaptionBar_ScrollPrevDate ||
			 nPartID == xtpCalendarCaptionBar_ScrollNextDate)
	{
		CXTPCalendarView* pActiveView = GetCalendarCtrl()->GetActiveView();
		int nViewType = pActiveView->GetViewType();
		BOOL bNext = nPartID == xtpCalendarCaptionBar_ScrollNextDate;

		COleDateTime dtSelStart, dtSelEnd, dtFirst;
		int nGroupIndex = 0;
		BOOL bAllDay = TRUE;
		dtFirst = pActiveView->GetViewDayDate(0);
		if (!pActiveView->GetSelection(&dtSelStart, &dtSelEnd, &bAllDay, &nGroupIndex))
		{
			dtSelStart = dtFirst;
			dtSelEnd = dtFirst + COleDateTimeSpan(1);
		}

		if (nViewType == xtpCalendarDayView)
		{
			int nDays = pActiveView->GetViewDayCount();
			dtSelStart += COleDateTimeSpan(bNext ? nDays : -nDays);
			dtSelEnd += COleDateTimeSpan(bNext ? nDays : -nDays);
		}
		else if (nViewType == xtpCalendarWorkWeekView ||
				 nViewType == xtpCalendarFullWeekView ||
				 nViewType == xtpCalendarWeekView)
		{
			dtSelStart += COleDateTimeSpan(bNext ? 7 : -7);
			dtSelEnd += COleDateTimeSpan(bNext ? 7 : -7);
		}
		else if (nViewType == xtpCalendarMonthView)
		{
			int nSelDay = dtSelStart.GetDay();
			CXTPCalendarUtils::ShiftDate_Month(dtSelStart, bNext ? 1 : -1, 1);
			CXTPCalendarUtils::UpdateMonthDay(dtSelStart, nSelDay);

			dtSelEnd = dtSelStart + COleDateTimeSpan(1);
		}
		else
		{
			ASSERT(FALSE);
		}

		pActiveView->SetSelection(dtSelStart, dtSelEnd, bAllDay, nGroupIndex);

		GetCalendarCtrl()->SwitchActiveView((XTPCalendarViewType)nViewType);
	}
	else
	{
		return;
	}

	UpdateControlsState();

	if (GetOwnerWnd())
		GetOwnerWnd()->Invalidate(FALSE);
}

BOOL CXTPCalendarCaptionBarTheme::_UpdateControlsHotState(BOOL* pbMouseLeave)
{
	if (pbMouseLeave)
		*pbMouseLeave = FALSE;

	CPoint ptMouse(0, 0);

	if (GetCursorPos(&ptMouse) && GetOwnerWnd())
		GetOwnerWnd()->ScreenToClient(&ptMouse);
	else
		return FALSE;

	BOOL bMouseLeave = !m_rcRect.PtInRect(ptMouse);

	if (pbMouseLeave)
		*pbMouseLeave = bMouseLeave;

	if (!bMouseLeave)
		return FALSE;

	BOOL bResetFocused = CWnd::GetFocus() != GetOwnerWnd();
	//-------------------------------------------------------------------------
	BOOL bChanged = FALSE;

	int nCount = m_arMembers.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CXTPCalendarCaptionBarThemePart* pPart = m_arMembers.GetAt(i);
		ASSERT(pPart);
		if (pPart)
		{
			int nNewState = pPart->GetState() & (~(CXTPCalendarCaptionBarThemePart::xtpBtnStateMouseOver |
												   CXTPCalendarCaptionBarThemePart::xtpBtnStatePressed));
			if (bResetFocused)
				nNewState = nNewState & (~CXTPCalendarCaptionBarThemePart::xtpBtnStateFocused);

			if (nNewState != pPart->GetState())
			{
				pPart->SetState(nNewState);
				bChanged = TRUE;
			}
		}
	}

	return bChanged;
}

void CXTPCalendarCaptionBarTheme::OnKillFocus (CWnd* pNewWnd)
{
	UNREFERENCED_PARAMETER(pNewWnd);

	BOOL bChanged = _UpdateControlsHotState();

	if (bChanged)
		GetOwnerWnd()->Invalidate(FALSE);
}

void CXTPCalendarCaptionBarTheme::CSwitchViewButtonPart::RefreshMetrics()
{
	if (GetPaintTheme() <= xtpCalendarThemeOffice2003)
	{
		m_clrTextColor.SetStandardValue(RGB(0, 0, 0));
	}
}

void CXTPCalendarCaptionBarTheme::CSwitchViewButtonPart::AdjustLayout(CDC* pDC, const CRect& rcRect)
{
	m_rcRect = rcRect;

	if (m_rcRect.IsRectEmpty())
		return;

	if (pDC)
	{
		CXTPFontDC autoFont(pDC, GetTheme()->m_fntTextFont);

		CSize szText = pDC->GetTextExtent(GetText());

		if (szText.cx + 8 > m_rcRect.Width())
			m_rcRect.right = m_rcRect.left + szText.cx + 8;
	}
}

void CXTPCalendarCaptionBarTheme::CSwitchViewButtonPart::Draw(CDC* pDC)
{
	if (!IsVisible())
		return;

	CXTPOffice2007Image* pImage = XTPOffice2007Images()->LoadFile(_T("CALENDARCAPTIONBARSWITCHVIEWBUTTON"));
	CRect rcRect = GetRect();

	ASSERT(pImage);
	if (!pImage || !GetTheme())
	{
		pDC->FillSolidRect(rcRect , RGB(155, 0, 0));
		return;
	}


	if (GetPaintTheme() >= xtpCalendarThemeOffice2007)
	{
		int nImagePart = (m_nState & xtpBtnStateChecked) ? 3 : 0;

		if (m_nState & xtpBtnStatePressed)
		{
			nImagePart += 2;
		}
		else if (m_nState & xtpBtnStateMouseOver)
		{
			nImagePart += 1;
		}

		pImage->DrawImage(pDC, rcRect, pImage->GetSource(nImagePart, 6), CRect(0, 0, 0, 0));

		rcRect.left = rcRect.right - 1;
		pDC->FillSolidRect(&rcRect, GetTheme()->m_clrBorders);
	}
	else
	{
		if (GetTheme()->m_themeButton.IsAppThemed() &&
			GetPaintTheme() == xtpCalendarThemeOffice2003)
		{
			int nState = (m_nState & xtpBtnStatePressed) ? PBS_PRESSED :
						 (m_nState & xtpBtnStateMouseOver) ? PBS_HOT: PBS_NORMAL;

			if (m_nState & xtpBtnStateChecked)
				nState = PBS_PRESSED;

			GetTheme()->m_themeButton.DrawThemeBackground(pDC->GetSafeHdc(), BP_PUSHBUTTON, nState, rcRect, NULL);

		}
		else
		{
			UINT uFlags = DFCS_BUTTONPUSH | //DFCS_FLAT |
			((m_nState & xtpBtnStateChecked) ? DFCS_CHECKED : 0) |
			((m_nState & xtpBtnStatePressed) ? DFCS_PUSHED : 0); // | (bEnabled ? 0 : DFCS_INACTIVE)

//          if (GetPaintTheme() > xtpCalendarThemeOffice2000)
//              uFlags |= DFCS_FLAT;

			::DrawFrameControl(pDC->GetSafeHdc(), rcRect, DFC_BUTTON, uFlags);
		}
	}


	// drawText
	CFont fntTmp;
	CXTPFontDC autoFont(pDC, GetTheme()->m_fntTextFont, GetTextColor());

	if ((m_nState & xtpBtnStateChecked) && GetPaintTheme() <= xtpCalendarThemeOffice2003)
	{
		LOGFONT lf;
		if (GetTheme()->m_fntTextFont->GetLogFont(&lf))
		{
			lf.lfWeight = FW_BOLD;

			if (fntTmp.CreateFontIndirect(&lf))
				autoFont.SetFont(&fntTmp);
		}
	}

	CRect rcText = GetRect();
	rcText.DeflateRect(1, 1, 1, 1);

	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(GetText(), rcText, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
}

LPCTSTR CXTPCalendarCaptionBarTheme::CScrollDateButtonPart::_GetImageName()
{
	if (m_nPartID == xtpCalendarCaptionBar_ScrollNextDate)
		return _T("CALENDARCAPTIONBARNEXTDATEBUTTON");

	return _T("CALENDARCAPTIONBARPREVDATEBUTTON");
}

void CXTPCalendarCaptionBarTheme::CScrollDateButtonPart::AdjustLayout(CDC* /*pDC*/, const CRect& rcRect)
{
	m_rcRect = rcRect;

	if (m_rcRect.IsRectEmpty())
		return;

	CXTPOffice2007Image* pImage = XTPOffice2007Images()->LoadFile(_GetImageName());

	ASSERT(pImage);
	if (!pImage || !GetTheme())
		return;

	CRect rcImage = pImage->GetSource(0, 4);

	m_rcRect.right = m_rcRect.left + rcImage.Width();
	m_rcRect.bottom = m_rcRect.top + rcImage.Height();
}

void CXTPCalendarCaptionBarTheme::CScrollDateButtonPart::Draw(CDC* pDC)
{
	if (!IsVisible())
		return;

	CRect rcRect = GetRect();

	CXTPOffice2007Image* pImage = XTPOffice2007Images()->LoadFile(_GetImageName());

	ASSERT(pImage);
	if (!pImage || !GetTheme())
	{
		pDC->FillSolidRect(rcRect, RGB(155, 0, 0));
		return;
	}

	if (GetPaintTheme() == xtpCalendarThemeOffice2007)
	{
		int nImagePart = (m_nState & xtpBtnStatePressed) ? 2 : (m_nState & xtpBtnStateMouseOver) ? 1 : 0;

		pImage->DrawImage(pDC, rcRect, pImage->GetSource(nImagePart, 4),
							CRect(0, 0, 0, 0), RGB(255, 0, 255));

		if (m_nState & xtpBtnStateFocused)
			pImage->DrawImage(pDC, GetRect(), pImage->GetSource(3, 4),
					CRect(1, 1, 1, 1), RGB(255, 0, 255));
	}
	else
	{
		if (GetTheme()->m_themeButton.IsAppThemed() &&
			GetPaintTheme() == xtpCalendarThemeOffice2003)
		{
			int nState = (m_nState & xtpBtnStatePressed) ? PBS_PRESSED :
						 (m_nState & xtpBtnStateMouseOver) ? PBS_HOT: PBS_NORMAL;

			GetTheme()->m_themeButton.DrawThemeBackground(pDC->GetSafeHdc(), BP_PUSHBUTTON, nState, rcRect, NULL);
		}
		else
		{
			UINT uFlags = DFCS_BUTTONPUSH |
			((m_nState & xtpBtnStateChecked) ? DFCS_CHECKED : 0) |
			((m_nState & xtpBtnStatePressed) ? DFCS_PUSHED : 0); // | (bEnabled ? 0 : DFCS_INACTIVE)

			//if (GetPaintTheme() > xtpCalendarThemeOffice2000)
			//  uFlags = uFlags | DFCS_FLAT;

			::DrawFrameControl(pDC->GetSafeHdc(), rcRect, DFC_BUTTON, uFlags);
		}

		BOOL bLeftDirection = GetPartID() == xtpCalendarCaptionBar_ScrollPrevDate;
		DrawScrollTriangle(pDC, rcRect, bLeftDirection, RGB(0, 0, 0));
	}
}

void CXTPCalendarCaptionBarTheme::CScrollDateButtonPart::_DrawTriangle(CDC* pDC, CPoint pt0, CPoint pt1, CPoint pt2, COLORREF clrColor)
{
	CXTPPenDC pen (*pDC, clrColor);
	CXTPBrushDC brush (*pDC, clrColor);

	CPoint pts[3];
	pts[0] = pt0;
	pts[1] = pt1;
	pts[2] = pt2;
	pDC->Polygon(pts, 3);
}

void CXTPCalendarCaptionBarTheme::CScrollDateButtonPart::DrawScrollTriangle(CDC* pDC, CRect rcRect, BOOL bLeftDirection, COLORREF clrColor)
{
	CPoint ptCenter(rcRect.CenterPoint());
	ptCenter.y--;

	if (bLeftDirection)
	{
		ptCenter.x -= 3;
		_DrawTriangle(pDC, ptCenter, CPoint(ptCenter.x + 4, ptCenter.y - 4),
					  CPoint(ptCenter.x + 4, ptCenter.y + 4), clrColor);
	}
	else
	{
		ptCenter.x += 2;
		_DrawTriangle(pDC, ptCenter, CPoint(ptCenter.x - 4, ptCenter.y - 4),
					  CPoint(ptCenter.x - 4, ptCenter.y + 4), clrColor);
	}

}


BOOL CXTPCalendarCaptionBarTheme::CScrollDateButtonPart::OnLButtonDown(UINT nFlags, CPoint point)
{
	CXTPCalendarCaptionBarThemePart::OnLButtonDown(nFlags, point);

	if (GetTheme() && GetTheme()->GetOwnerWnd() && HitTest(point) &&
		CWnd::GetFocus() != GetTheme()->GetOwnerWnd() )
	{
		GetTheme()->GetOwnerWnd()->SetFocus();
	}

	return FALSE;
}

void CXTPCalendarCaptionBarTheme::CScrollDateButtonPart::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	UNREFERENCED_PARAMETER(nRepCnt);  UNREFERENCED_PARAMETER(nFlags);

	if (!IsVisible())
		return;

	if ((m_nState & xtpBtnStateFocused) && (m_nState & xtpBtnStatePressed) == 0 &&
		nChar == VK_SPACE)
	{
		m_nState |= xtpBtnStatePressed;

		Redraw();
	}
}

void CXTPCalendarCaptionBarTheme::CScrollDateButtonPart::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	UNREFERENCED_PARAMETER(nRepCnt);  UNREFERENCED_PARAMETER(nFlags);

	if (!IsVisible())
		return;

	int nMask = xtpBtnStateFocused | xtpBtnStatePressed;

	if ((m_nState & nMask) == nMask && nChar == VK_SPACE && GetTheme())
	{
		GetTheme()->OnPartClick(GetPartID());
	}

	if (nChar == VK_SPACE)
	{
		m_nState = m_nState & (~xtpBtnStatePressed);

		Redraw();
	}
}

void CXTPCalendarCaptionBarTheme::CRadioButtonPart::RefreshMetrics()
{
	if (GetPaintTheme() <= xtpCalendarThemeOffice2003)
	{
		m_clrTextColor.SetStandardValue(RGB(0, 0, 0));
	}
}

void CXTPCalendarCaptionBarTheme::CRadioButtonPart::AdjustLayout(CDC* pDC, const CRect& rcRect)
{
	m_rcRect = rcRect;

	if (m_rcRect.IsRectEmpty())
		return;

	CSize szRadio(13, 13);
	CRect rcRadio = GetRect();

	if (GetTheme() && GetTheme()->m_themeButton.IsAppThemed())
	{
		GetTheme()->m_themeButton.GetThemePartSize(NULL, BP_RADIOBUTTON, 1, rcRadio, TS_DRAW, &szRadio);
	}

	if (pDC)
	{
		CXTPFontDC autoFont(pDC, GetTheme()->m_fntTextFont);
		CSize szText = pDC->GetTextExtent(GetText());

		if (szRadio.cx + 9 + szText.cx + 8 > m_rcRect.Width())
			m_rcRect.right = m_rcRect.left + szRadio.cx + 9 + szText.cx + 8;

		szRadio.cy = max(szRadio.cy, szText.cy);
	}

	m_rcRect.top += (m_rcRect.Height() - szRadio.cy) / 2 + 1;
	m_rcRect.bottom = m_rcRect.top + szRadio.cy;
}

void CXTPCalendarCaptionBarTheme::CRadioButtonPart::Draw(CDC* pDC)
{
	if (!IsVisible())
		return;

	CSize szRadio(13, 13);
	CRect rcRadio = GetRect();

	BOOL bThemed = GetTheme() && GetTheme()->m_themeButton.IsAppThemed() &&
					GetPaintTheme() >= xtpCalendarThemeOffice2003;
	if (bThemed)
	{
		GetTheme()->m_themeButton.GetThemePartSize(NULL, BP_RADIOBUTTON, 1, rcRadio, TS_DRAW, &szRadio);
	}

	rcRadio.top += (rcRadio.Height() - szRadio.cy) / 2 + 1;
	rcRadio.bottom = rcRadio.top + szRadio.cy;
	rcRadio.right = rcRadio.left + szRadio.cx;

	if (bThemed)
	{
		GetTheme()->m_themeButton.GetThemePartSize(NULL, BP_RADIOBUTTON, 1, rcRadio, TS_DRAW, &szRadio);
		//-------------------

		int nState = (m_nState & xtpBtnStatePressed) ? RBS_UNCHECKEDPRESSED :
					 (m_nState & xtpBtnStateMouseOver) ? RBS_UNCHECKEDHOT: RBS_UNCHECKEDNORMAL;

		if (m_nState & xtpBtnStateChecked)
			nState += 4;

		GetTheme()->m_themeButton.DrawThemeBackground(pDC->GetSafeHdc(), BP_RADIOBUTTON, nState, rcRadio, NULL);

	}
	else
	{
		UINT uFlags = DFCS_BUTTONRADIO | //DFCS_FLAT |
			((m_nState & xtpBtnStateChecked) ? DFCS_CHECKED : 0) |
			((m_nState & xtpBtnStatePressed) ? DFCS_PUSHED : 0); // | (bEnabled ? 0 : DFCS_INACTIVE)

		if (GetPaintTheme() > xtpCalendarThemeOffice2000)
			uFlags |= DFCS_FLAT;

		::DrawFrameControl(pDC->GetSafeHdc(), rcRadio, DFC_BUTTON, uFlags);
	}

	// drawText
	CXTPFontDC autoFont(pDC, GetTheme()->m_fntTextFont, GetTextColor());
	pDC->SetBkMode(TRANSPARENT);

	CRect rcText = GetRect();
	//rcText.top +=2;
	rcText.bottom +=1;
	rcText.left = rcRadio.right + 9;

	pDC->DrawText(GetText(), rcText, DT_BOTTOM | DT_LEFT | DT_SINGLELINE);

	rcText.left--;
	rcText.right++;

	if (m_nState & xtpBtnStatePressed)
		pDC->DrawFocusRect(rcText);
}

void CXTPCalendarCaptionBarTheme::CDateLabelPart::RefreshMetrics()
{
	if (!GetTheme())
		return;

	m_clrTextColor.SetStandardValue(GetTheme()->m_clrTextColor);

	LOGFONT lfBaseFont;
	::ZeroMemory(&lfBaseFont, sizeof(lfBaseFont));

	GetTheme()->m_fntTextFont->GetLogFont(&lfBaseFont);
	lfBaseFont.lfHeight = -20;

	m_fntTextFont.SetStandardValue(&lfBaseFont);
}

void CXTPCalendarCaptionBarTheme::CDateLabelPart::Draw(CDC* pDC)
{
	if (!IsVisible())
		return;

	CXTPFontDC autoFont(pDC, m_fntTextFont, m_clrTextColor);
	pDC->SetBkMode(TRANSPARENT);

	CXTPCalendarView* pCalView = XTP_SAFE_GET2(GetTheme(), GetCalendarCtrl(), GetActiveView(), NULL);
	ASSERT(pCalView);
	if (!pCalView || !IsVisible())
		return;

	BOOL bShowMonthDay = pCalView->GetViewType() != xtpCalendarMonthView;
	COleDateTime dtDay1 = pCalView->GetViewDayDate(0);
	COleDateTime dtDay2 = pCalView->GetViewDayDate(max(0, pCalView->GetViewDayCount() - 1));

	m_strText = _FormatDate(dtDay1, dtDay2, bShowMonthDay);

	CRect rcText = GetRect();
	//rcText.top +=2;
	rcText.bottom +=1;
	//rcText.left = rcRadio.right + 9;

	UINT uFlags = DT_BOTTOM | DT_SINGLELINE;
	if (GetTheme() && !GetTheme()->IsScrollDateButtons() &&
		GetPaintTheme() < xtpCalendarThemeOffice2007)
	{
		uFlags |= DT_RIGHT;
		rcText.right = max(rcText.left, rcText.right - 9);
	}

	pDC->DrawText(GetText(), rcText, uFlags);
}

LPCTSTR CXTPCalendarCaptionBarTheme::CDateLabelPart::_AddSpace(CString& rStr)
{
	if (!rStr.IsEmpty())
		rStr = rStr + _T(' ');

	return (LPCTSTR)rStr;
}

CString CXTPCalendarCaptionBarTheme::CDateLabelPart::_FormatDate(COleDateTime dtDay1, COleDateTime dtDay2,
																 BOOL bShowMonthDay)
{
	//LOCALE_IDATE  -  short date format ordering
	// 0 Month-Day-Year
	// 1 Day-Month-Year
	// 2 Year-Month-Day

	int nDateOrdering = CXTPCalendarUtils::GetLocaleLong(LOCALE_IDATE);

	CString strDay1(bShowMonthDay ? _T("d") : _T(""));
	CString strDay2(strDay1);

	CString strMonth1;
	CString strMonth2 = _T("MMMM");

	if (dtDay1.GetMonth() != dtDay2.GetMonth())
		strMonth1 = _T("MMMM");

	CString strYear1;
	CString strYear2;
	strYear2 = _T("yyyy");
	if (dtDay1.GetYear() != dtDay2.GetYear())
		strYear1 = _T("yyyy");

	CString strFormat1, strFormat2;

	if (nDateOrdering == 1)
	{
		strFormat1.Format(_T("%s%s%s"), _AddSpace(strDay1), _AddSpace(strMonth1), _AddSpace(strYear1));
		strFormat2.Format(_T("%s%s%s"), _AddSpace(strDay2), _AddSpace(strMonth2), (LPCTSTR)strYear2);
	}
	else
	{
		if (!strYear1.IsEmpty() && !strDay1.IsEmpty())
			strDay1 += _T(",");

		if (!strYear2.IsEmpty() && !strDay2.IsEmpty())
			strDay2 += _T(",");

		strFormat1.Format(_T("%s%s%s"), _AddSpace(strMonth1), _AddSpace(strDay1), _AddSpace(strYear1));
		strFormat2.Format(_T("%s%s%s"), _AddSpace(strMonth2), _AddSpace(strDay2), (LPCTSTR)strYear2);
	}

	//----------------------------------------------------------------------------
	CString strCaption;

	if (!CXTPCalendarUtils::IsEqual(dtDay1, dtDay2))
	{
		strCaption = CXTPCalendarUtils::GetDateFormat(dtDay1, strFormat1);
		strCaption += _T("- ");
	}

	strCaption += CXTPCalendarUtils::GetDateFormat(dtDay2, strFormat2);

	return strCaption;
}
