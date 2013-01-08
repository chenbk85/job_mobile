// SampleText.cpp : implementation file
//

#include "stdafx.h"
#include "FontCombo.h"
#include "FontComboDlg.h"
#include "SampleText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleText

CSampleText::CSampleText()
{
	m_cr = COLORREF_NULL;
}

CSampleText::~CSampleText()
{
}


BEGIN_MESSAGE_MAP(CSampleText, CStatic)
	//{{AFX_MSG_MAP(CSampleText)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleText message handlers

void CSampleText::UpdateFont(const CXTLogFont& lf, const COLORREF& cr)
{
	m_cr = cr;
	m_lf = lf;

	if (::IsWindow(m_hWnd))
		RedrawWindow();
}

void CSampleText::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CXTPClientRect rClient(this);
	
	// Paint to a memory device context to help
	// eliminate screen flicker...
	CXTMemDC memDC(&dc, rClient, GetXtremeColor(COLOR_WINDOW));

	// create a font based on the current font selection.
	CFont font;
	font.CreateFontIndirect(&m_lf);

	// set the text color and font based on current selection
	CXTPFontDC fontDC(&memDC, &font);
	memDC.SetBkMode(TRANSPARENT);

	CString csWindowText;
	GetWindowText(csWindowText);

	// display the sample text.
	memDC.SetTextColor(m_cr);
	memDC.DrawText(csWindowText, &rClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void CSampleText::OnNcPaint() 
{
	CWindowDC dc(this);

	// convert to client coordinates
	CXTPWindowRect rWindow(this);
	ScreenToClient(rWindow);
	
	// exclude the client area from paint operation.
	CXTPClientRect rClient(this);
	rClient.OffsetRect(-rWindow.left, -rWindow.top);
	dc.ExcludeClipRect(rClient);
	rWindow.OffsetRect(-rWindow.left, -rWindow.top);
	
	// Paint to a memory device context to help
	// eliminate screen flicker...
	CXTMemDC memDC(&dc, rWindow, GetXtremeColor(COLOR_WINDOW));
	memDC.Draw3dRect(&rWindow, GetXtremeColor(XPCOLOR_HIGHLIGHT_BORDER), GetXtremeColor(XPCOLOR_HIGHLIGHT_BORDER));
}
