// StaticMenuGrabber.cpp : implementation file
//

#include "stdafx.h"
#include "commandbarsdesigner.h"
#include "StaticMenuGrabber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticMenuGrabber

CStaticMenuGrabber::CStaticMenuGrabber()
{
	m_hCursor = AfxGetApp()->LoadCursor(IDC_GRABBER);
	m_bGrabbing = FALSE;

	m_pMenuBar = NULL;
}

CStaticMenuGrabber::~CStaticMenuGrabber()
{
}


BEGIN_MESSAGE_MAP(CStaticMenuGrabber, CStatic)
	//{{AFX_MSG_MAP(CStaticMenuGrabber)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticMenuGrabber message handlers

void CStaticMenuGrabber::OnPaint() 
{
	CPaintDC dcPaint(this); // device context for painting
	CXTPBufferDC dc(dcPaint);
	CXTPClientRect rc(this);

	dc.FillSolidRect(rc, GetXtremeColor(COLOR_WINDOW));
	dc.Draw3dRect(rc, GetXtremeColor(COLOR_BTNSHADOW), GetXtremeColor(COLOR_BTNSHADOW));

	CString str;
	GetWindowText(str);
	CXTPFontDC font(&dc, GetFont());
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(GetXtremeColor(COLOR_WINDOWTEXT));

	if (m_bGrabbing)
	{
		rc.left += 5 + 32 + 5;

		dc.DrawText(_T("Now drag the mouse to select a menu"), rc, DT_VCENTER | DT_LEFT| DT_SINGLELINE);

	}
	else
	{
		::DrawIconEx(dc, rc.left + 5, rc.CenterPoint().y - 16, m_hCursor, 32, 32, 0, 0, DI_NORMAL);

		rc.left += 5 + 32 + 5;

		dc.DrawText(str, rc, DT_VCENTER | DT_LEFT| DT_SINGLELINE);
	}
}

struct XTP_MENUBARINFO
{
    DWORD cbSize;
    RECT  rcBar;          // rect of bar, popup, item
    HMENU hMenu;          // real menu handle of bar, popup
    HWND  hwndMenu;       // hwnd of item submenu if one
    BOOL  fBarFocused:1;  // bar, popup has the focus
    BOOL  fFocused:1;     // item has the focus
};

#ifndef OBJID_MENU
#define OBJID_MENU 0xFFFFFFFD
#endif

void CStaticMenuGrabber::HighlightWindow(HWND hwnd, BOOL fDraw)
{
	#define DINV                3
	HDC hdc;
    RECT rcWindow;
    RECT rc;
	BOOL bBorderOn;
    bBorderOn = fDraw;

    if (hwnd == NULL || !IsWindow(hwnd))
        return;

	typedef BOOL (WINAPI* PFNGETMENUBARINFO)( HWND hwnd, LONG idObject, LONG idItem, XTP_MENUBARINFO* pmbi);
	
	HINSTANCE hInst = ::GetModuleHandleA("USER32.DLL");
	PFNGETMENUBARINFO pfnGetMenuBarInfo = (PFNGETMENUBARINFO)GetProcAddress(hInst, "GetMenuBarInfo");
	if (!pfnGetMenuBarInfo)
		return;

	XTP_MENUBARINFO mbInfo = {sizeof(mbInfo)};
	if (!(*pfnGetMenuBarInfo)(hwnd, OBJID_MENU, 0, &mbInfo))
		return;

    hdc = ::GetWindowDC(hwnd);
    ::GetWindowRect(hwnd, &rcWindow);

    rc = mbInfo.rcBar;

    ::OffsetRect(&rc, -rcWindow.left, -rcWindow.top);


    if (!IsRectEmpty(&rc))
    {
        PatBlt(hdc, rc.left, rc.top, rc.right - rc.left, DINV,  DSTINVERT);
        PatBlt(hdc, rc.left, rc.bottom - DINV, DINV,
            -(rc.bottom - rc.top - 2 * DINV), DSTINVERT);
        PatBlt(hdc, rc.right - DINV, rc.top + DINV, DINV,
            rc.bottom - rc.top - 2 * DINV, DSTINVERT);
        PatBlt(hdc, rc.right, rc.bottom - DINV, -(rc.right - rc.left),
            DINV, DSTINVERT);
    }

    ::ReleaseDC(hwnd, hdc);
}

void CStaticMenuGrabber::ConvertMenu(HWND hWnd)
{
	if (!m_pMenuBar)
		return;

	m_pMenuBar->GetControls()->RemoveAll();
	
	HMENU hMenu = ::GetMenu(hWnd);
	if (!hMenu)
		return;

	m_pMenuBar->LoadMenu(CMenu::FromHandle(hMenu));

	CXTPClientRect rc(m_pMenuBar->GetParent());

	CSize sz = m_pMenuBar->CalcDockingLayout(rc.Width(), /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);

	m_pMenuBar->MoveWindow(0, 0, rc.Width(), sz.cy);
	m_pMenuBar->Invalidate(FALSE);
}

void CStaticMenuGrabber::OnLButtonDown(UINT /*nFlags*/, CPoint point) 
{
	m_bGrabbing = TRUE;
	Invalidate(FALSE);

	SetCapture();

	::SetCursor(m_hCursor);
	
	HWND hPrevSpyWnd = 0;
	BOOL bAccept = FALSE;

	for (;;)
	{
		MSG msg;
		VERIFY(::GetMessage(&msg, NULL, 0, 0));

		if (msg.message == WM_LBUTTONUP)
		{
			bAccept = TRUE;
			break;
		}
		else if (msg.message == WM_KEYDOWN)
		{
			if (msg.wParam == VK_ESCAPE)
				break;
		}
		else if (msg.message == WM_MOUSEMOVE)
		{
			GetCursorPos(&point);

			HWND hWnd = ::WindowFromPoint(point);
			
			CRect rc;
			GetWindowRect(rc);
			if (rc.PtInRect(point))
				hWnd = 0;

			HMENU hMenu = hWnd ? ::GetMenu(hWnd) : NULL;

			if (!hMenu)
				hWnd = NULL;
			
			if(hWnd != hPrevSpyWnd)
			{
				
				if(hPrevSpyWnd) HighlightWindow(hPrevSpyWnd, FALSE);
				if(hWnd) HighlightWindow(hWnd,TRUE);			
				
				hPrevSpyWnd = hWnd;
			}	
			//continue;
		}		

		DispatchMessage (&msg);

		if (::GetCapture() != m_hWnd)
			break;
	}
	
	if (hPrevSpyWnd)
	{
		HighlightWindow(hPrevSpyWnd, FALSE);
	}

	ReleaseCapture();

	if (bAccept && hPrevSpyWnd)
	{
		ConvertMenu(hPrevSpyWnd);
	}

	hPrevSpyWnd = 0;

	m_bGrabbing = FALSE;
	Invalidate(FALSE);
}
