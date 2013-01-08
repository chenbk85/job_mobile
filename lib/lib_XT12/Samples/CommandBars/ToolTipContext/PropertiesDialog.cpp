// PropertiesDialog.cpp : implementation file
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

#include "stdafx.h"
#include "ToolTipContext.h"
#include "PropertiesDialog.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDialog dialog


CPropertiesDialog::CPropertiesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertiesDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertiesDialog)
	m_bPopupBarTips = TRUE;
	m_bShowDescription = TRUE;
	m_nToolTipStyle = 1;
	m_bToolBarScreenTips = TRUE;
	m_bToolBarAccelTips = FALSE;
	m_bShowDescription = TRUE;
	m_bShowIcons = FALSE;
	m_bShowShadow = FALSE;
	m_bShowOfficeBorder = TRUE;
	//}}AFX_DATA_INIT
}


void CPropertiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertiesDialog)
	DDX_Check(pDX, IDC_CHECK_POPUPBARTIPS, m_bPopupBarTips);
	DDX_Check(pDX, IDC_CHECK_SHOWDESCRIPTION, m_bShowDescription);
	DDX_Radio(pDX, IDC_RADIO_TOOLTIPSTYLE, m_nToolTipStyle);
	DDX_Check(pDX, IDC_CHECK_SHOWTIPS, m_bToolBarScreenTips);
	DDX_Check(pDX, IDC_CHECK_SHOWSHORTCUTS, m_bToolBarAccelTips);
	DDX_Check(pDX, IDC_CHECK_SHOWIMAGE, m_bShowIcons);
	DDX_Check(pDX, IDC_CHECK_SHOWSHADOW, m_bShowShadow);
	DDX_Check(pDX, IDC_CHECK_SHOWBORDER, m_bShowOfficeBorder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertiesDialog, CDialog)
	//{{AFX_MSG_MAP(CPropertiesDialog)
	ON_BN_CLICKED(IDC_CHECK_POPUPBARTIPS, OnCheckPopupBarTips)
	ON_BN_CLICKED(IDC_CHECK_SHOWDESCRIPTION, OnCheckShowDescription)
	ON_BN_CLICKED(IDC_CHECK_SHOWTIPS, OnCheckShowTips)
	ON_BN_CLICKED(IDC_RADIO_TOOLTIPSTYLE, OnRadioTooltipStyle)
	ON_BN_CLICKED(IDC_RADIO_TOOLTIPSTYLE_BALLOON, OnRadioTooltipStyle)
	ON_BN_CLICKED(IDC_RADIO_TOOLTIPSTYLE_OFFICE, OnRadioTooltipStyle)
	ON_BN_CLICKED(IDC_RADIO_TOOLTIPSTYLE_RTF, OnRadioTooltipStyle)
	ON_BN_CLICKED(IDC_RADIO_TOOLTIPSTYLE_LUNA, OnRadioTooltipStyle)
	ON_BN_CLICKED(IDC_RADIO_TOOLTIPSTYLE_OFFICE2007, OnRadioTooltipStyle)
	ON_BN_CLICKED(IDC_RADIO_TOOLTIPSTYLE_HTML, OnRadioTooltipStyle)
	ON_BN_CLICKED(IDC_RADIO_TOOLTIPSTYLE_MARKUP, OnRadioTooltipStyle)

	ON_BN_CLICKED(IDC_CHECK_SHOWIMAGE, OnCheckShowIcons)
	ON_BN_CLICKED(IDC_CHECK_SHOWSHADOW, OnCheckShowShadow)
	ON_BN_CLICKED(IDC_CHECK_SHOWBORDER, OnCheckShowOfficeBorder)
	ON_BN_CLICKED(IDC_CHECK_SHOWSHORTCUTS, OnCheckShowshortcuts)

	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnToolTipText)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDialog message handlers

BOOL CPropertiesDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	BOOL bBalloonStyleSupported = m_moduleContext.IsBalloonStyleSupported();

	if (!bBalloonStyleSupported)
	{
		m_nToolTipStyle = 0;
		GetDlgItem(IDC_RADIO_TOOLTIPSTYLE_BALLOON)->EnableWindow(FALSE);
		UpdateData(FALSE);
	}
	
	EnableToolTips();
	
	m_moduleContext.SetModuleToolTipContext();
	m_moduleContext.SetStyle(xtpToolTipMarkup);
	m_moduleContext.SetMaxTipWidth(200);
	
	UpdateControls();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CreateHTMLTool(LPCTSTR strCaption, LPCTSTR strDesc)
{
	TCHAR lpszModule[_MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(), lpszModule, _MAX_PATH);
	
	CString strHTML;
	strHTML.Format(_T("<table cellspacing=4 cellpadding=0 border=0><tr><td><b>%s</b></td></tr>")
		_T("<tr><td><table cellspacing=4 cellpadding=0 border=0><tr><td width=6></td><td>%s</td></tr></table></td></tr>")
        _T("<tr><td><table width=100%% cellspacing=0 cellpadding=0 border=0 bgcolor=gray><tr><td></td></tr></table></td></tr>")
		_T("<tr><td><table><tr><td><img width=16 height=16 src=res://%s/Help.gif></td>")
		_T("<td><b>Press F1 for more help</b></td></tr></table></td></tr></table>"),
			strCaption, strDesc, (LPCTSTR)lpszModule);
	
	return strHTML;
}

CString CreateMarkupTool(LPCTSTR strCaption, LPCTSTR strDesc)
{
	TCHAR lpszModule[_MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(), lpszModule, _MAX_PATH);
	
	CString strHTML;
	strHTML.Format(
			_T("<StackPanel Margin='1' MaxWidth='200'>")
				_T("<TextBlock Padding='1, 3, 1, 3' FontWeight='Bold'>%s</TextBlock>")
				_T("<TextBlock Padding='9, 6, 30, 7' TextWrapping='Wrap'>%s</TextBlock>")
				_T("<Border Height='1' Background='#9ebbdd' />")
				_T("<Border Height='1' Background='White' />")
				_T("<StackPanel Margin='1, 7, 0, 3' Orientation='Horizontal'>")
					_T("<Image Source='res://Help.ico'/><TextBlock Margin='7, 0, 0, 0' VerticalAlignment='Center' FontWeight='Bold'>Press F1 for more help.</TextBlock>")
				_T("</StackPanel>")
			_T("</StackPanel>"),
		strCaption, strDesc, (LPCTSTR)lpszModule);
	
	return strHTML;
}

void CPropertiesDialog::UpdateCommandBarToolTips()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CXTPCommandBars* pCommandBars = pMainFrame->GetCommandBars();
	
	if (pCommandBars->GetToolTipContext()->GetStyle() == xtpToolTipMarkup)
	{
		pCommandBars->GetActions()->FindAction(ID_FILE_NEW)->SetTooltip(_T("<TextBlock FontWeight='Bold' Text='New'/>"));
		pCommandBars->GetActions()->FindAction(ID_FILE_OPEN)->SetTooltip(_T("<TextBlock Foreground='Red' Text='Open'/>"));
		pCommandBars->GetActions()->FindAction(ID_FILE_SAVE)->SetTooltip(_T("<TextBlock FontStyle='Italic' TextDecorations='Underline' Text='Save'/>"));

		pCommandBars->GetActions()->FindAction(ID_EDIT_CUT)->SetTooltip(
			CreateMarkupTool(_T("Cut"), _T("Cut the selection and <Underline>put</Underline> it on the Clipboard")));

		pCommandBars->GetActions()->FindAction(ID_EDIT_COPY)->SetTooltip(
			CreateMarkupTool(_T("Copy"), _T("Copy the selection and put it on the Clipboard")));
		
		pCommandBars->GetActions()->FindAction(ID_EDIT_PASTE)->SetTooltip(
			CreateMarkupTool(_T("Paste"), _T("Insert Clipboard contents")));
	
		pCommandBars->GetActions()->FindAction(ID_FILE_PRINT)->SetTooltip(
			CreateMarkupTool(_T("Print"), _T("Print the active document")));
	
		pCommandBars->GetActions()->FindAction(ID_APP_ABOUT)->SetTooltip(
			CreateMarkupTool(_T("About"),_T("Display program information, version number and copyright")));
	}
	else if (pCommandBars->GetToolTipContext()->GetStyle() == xtpToolTipHTML)
	{
		pCommandBars->GetActions()->FindAction(ID_FILE_NEW)->SetTooltip(_T("<b>New<b>"));
		pCommandBars->GetActions()->FindAction(ID_FILE_OPEN)->SetTooltip(_T("<font color=red>Open</font>"));
		pCommandBars->GetActions()->FindAction(ID_FILE_SAVE)->SetTooltip(_T("<i><u>Save</u></i>"));
		
		pCommandBars->GetActions()->FindAction(ID_EDIT_CUT)->SetTooltip(
			CreateHTMLTool(_T("Cut"), _T("Cut the selection and put it on the Clipboard")));

		pCommandBars->GetActions()->FindAction(ID_EDIT_COPY)->SetTooltip(
			CreateHTMLTool(_T("Copy"), _T("Copy the selection and put it on the Clipboard")));
		
		pCommandBars->GetActions()->FindAction(ID_EDIT_PASTE)->SetTooltip(
			CreateHTMLTool(_T("Paste"), _T("Insert Clipboard contents")));
	
		pCommandBars->GetActions()->FindAction(ID_FILE_PRINT)->SetTooltip(
			CreateHTMLTool(_T("Print"), _T("Print the active document")));
	
		pCommandBars->GetActions()->FindAction(ID_APP_ABOUT)->SetTooltip(
			CreateHTMLTool(_T("About"),_T("Display program information, version number and copyright")));
	}
	else if (pCommandBars->GetToolTipContext()->GetStyle() == xtpToolTipRTF)
	{
            pCommandBars->GetActions()->FindAction(ID_FILE_NEW)->SetTooltip(
                _T("{\\rtf1\\fbidis\\ansi\\ansicpg1256\\deff0\\deflang1025{\\fonttbl{\\f0\\fscript\\fprq2\\fcharset0 Lucida Handwriting;}{\\f1\\fnil\\fcharset0 Courier New;}}{\\colortbl ;\\red0\\green0\\blue0;}\\viewkind4\\uc1\\pard\\ltrpar\\cf1\\lang1033\\f0\\fs28 Create a \\b new\\b0  document\\cf0\\f1\\fs20\\par}"));
            pCommandBars->GetActions()->FindAction(ID_FILE_OPEN)->SetTooltip(
                _T("{\\rtf1\\fbidis\\ansi\\ansicpg1256\\deff0\\deflang1025{\\fonttbl{\\f0\\fnil\\fcharset0 Courier New;}{\\f1\\fmodern\\fprq1\\fcharset0 Courier New;}}{\\colortbl ;\\red255\\green0\\blue0;}\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\f0\\fs20 Open an \\cf1\\ul\\i\\f1 existing\\cf0\\ulnone\\i0\\f0  document\\par}"));
            pCommandBars->GetActions()->FindAction(ID_FILE_SAVE)->SetTooltip(
                _T("{\\rtf1\\fbidis\\ansi\\ansicpg1256\\deff0\\deflang1025{\\fonttbl{\\f0\\fswiss\\fprq2\\fcharset0 Arial;}{\\f1\\fnil\\fcharset0 Courier New;}}{\\colortbl ;\\red0\\green0\\blue255;}\\viewkind4\\uc1\\pard\\ltrpar\\cf1\\lang1033\\b\\i\\f0\\fs20 Save the active document\\cf0\\b0\\i0\\f1\\par}"));
            pCommandBars->GetActions()->FindAction(ID_EDIT_CUT)->SetTooltip(
                _T("{\\rtf1\\fbidis\\ansi\\ansicpg1256\\deff0\\deflang1025{\\fonttbl{\\f0\\fmodern\\fprq1\\fcharset0 Courier New;}{\\f1\\fnil\\fcharset0 Courier New;}{\\f2\\fnil\\fcharset2 Symbol;}}\\viewkind4\\uc1\\pard{\\pntext\\f2\\'B7\\tab}{\\*\\pn\\pnlvlblt\\pnf2\\pnindent0{\\pntxtb\\'B7}}\\ltrpar\\fi-720\\li720\\lang1033\\f0\\fs20 Cuts the selection \\par{\\pntext\\f2\\'B7\\tab}Then puts it on the Clipboard\\par{\\pntext\\f2\\'B7\\tab}The \\ul\\b Paste\\ulnone\\b0  command can then be used to retrieve the text\\f1\\par}"));
            pCommandBars->GetActions()->FindAction(ID_EDIT_COPY)->SetTooltip(
                _T("{\\rtf1\\fbidis\\ansi\\ansicpg1256\\deff0\\deflang1025{\\fonttbl{\\f0\\fdecor\\fprq2\\fcharset0 Ravie;}{\\f1\\fnil\\fcharset0 Courier New;}{\\f2\\fnil\\fcharset2 Symbol;}}{\\colortbl ;\\red0\\green0\\blue255;\\red255\\green0\\blue0;\\red0\\green255\\blue0;\\red0\\green128\\blue0;\\red255\\green0\\blue255;\\red255\\green255\\blue0;}\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\f0\\fs20 Clipboard Actions:\\par\\pard{\\pntext\\f2\\'B7\\tab}{\\*\\pn\\pnlvlblt\\pnf2\\pnindent0{\\pntxtb\\'B7}}\\ltrpar\\fi-720\\li720\\cf1 Copy \\cf2 the\\cf0  \\cf3 selection \\cf0\\par\\pard{\\pntext\\f2\\'B7\\tab}{\\*\\pn\\pnlvlblt\\pnf2\\pnindent0{\\pntxtb\\'B7}}\\ltrpar\\fi-720\\li720\\tx3780\\cf4 Then \\cf5 put \\cf1 it \\cf6 on \\cf3 the \\cf2\\ul\\b Clipboard\\cf0\\ulnone\\b0\\f1\\par}"));
            pCommandBars->GetActions()->FindAction(ID_EDIT_PASTE)->SetTooltip(
                _T("{\\rtf1\\fbidis\\ansi\\ansicpg1256\\deff0\\deflang1025{\\fonttbl{\\f0\\froman\\fprq2\\fcharset0 Times New Roman;}{\\f1\\fnil\\fcharset0 Courier New;}}\\viewkind4\\uc1\\pard\\ltrpar\\lang1033\\f0\\fs36 Insert\\fs20  \\fs26 Clipboard\\fs20  \\fs16 contents\\f1\\fs20\\par}"));
            pCommandBars->GetActions()->FindAction(ID_FILE_PRINT)->SetTooltip(
                _T("{\\rtf {\\b Print} the {\\i\\ul active} document}"));
            pCommandBars->GetActions()->FindAction(ID_APP_ABOUT)->SetTooltip(
                _T("{\\rtf1\\fbidis\\ansi\\ansicpg1256\\deff0\\deflang1025{\\fonttbl{\\f0\\fnil\\fcharset0 Courier New;}}{\\colortbl ;\\red0\\green255\\blue0;\\red0\\green0\\blue255;\\red0\\green255\\blue255;\\red255\\green255\\blue0;\\red128\\green128\\blue128;\\red255\\green0\\blue255;\\red0\\green128\\blue0;}\\viewkind4\\uc1\\pard\\ltrpar\\cf1\\lang1033\\f0\\fs20 Display\\cf0  \\cf2 help\\cf0  \\cf3 for \\cf4 current \\cf5 task \\cf6 or \\cf7 command\\cf0\\par}"));

	}
	else
	{
		pCommandBars->GetActions()->FindAction(ID_FILE_NEW)->SetTooltip(_T("New"));
		pCommandBars->GetActions()->FindAction(ID_FILE_OPEN)->SetTooltip(_T("Open"));
		pCommandBars->GetActions()->FindAction(ID_FILE_SAVE)->SetTooltip(_T("Save"));
		pCommandBars->GetActions()->FindAction(ID_EDIT_CUT)->SetTooltip(_T("Cut"));
		pCommandBars->GetActions()->FindAction(ID_EDIT_COPY)->SetTooltip(_T("Copy"));
		pCommandBars->GetActions()->FindAction(ID_EDIT_PASTE)->SetTooltip(_T("Paste"));
		pCommandBars->GetActions()->FindAction(ID_FILE_PRINT)->SetTooltip(_T("Print"));
		pCommandBars->GetActions()->FindAction(ID_APP_ABOUT)->SetTooltip(_T("About"));
	}
} 


void CPropertiesDialog::OnCheckPopupBarTips() 
{
	UpdateData();

	((CXTPMDIFrameWnd*) AfxGetMainWnd())->GetCommandBars()->
		GetCommandBarsOptions()->bShowPopupBarToolTips = m_bPopupBarTips;
}

CXTPToolTipContext* CPropertiesDialog::GetToolTipContext()
{
	return ((CXTPMDIFrameWnd*) GetTopLevelFrame())->GetCommandBars()->GetToolTipContext();
}

void CPropertiesDialog::OnCheckShowDescription() 
{
	UpdateData();

	((CXTPMDIFrameWnd*) AfxGetMainWnd())->GetCommandBars()->GetToolTipContext()->
		ShowTitleAndDescription(m_bShowDescription);
	
}

void CPropertiesDialog::UpdateControls()
{
	BOOL bSystemStyle = m_nToolTipStyle == xtpToolTipStandard || m_nToolTipStyle == xtpToolTipBalloon;

	GetDlgItem(IDC_CHECK_SHOWSHADOW)->EnableWindow(!bSystemStyle);
	GetDlgItem(IDC_CHECK_SHOWIMAGE)->EnableWindow(!bSystemStyle && (m_nToolTipStyle != xtpToolTipRTF && m_nToolTipStyle != xtpToolTipHTML && m_nToolTipStyle != xtpToolTipMarkup));
	GetDlgItem(IDC_CHECK_SHOWBORDER)->EnableWindow(!bSystemStyle);
	
	GetDlgItem(IDC_CHECK_SHOWDESCRIPTION)->EnableWindow((m_nToolTipStyle != xtpToolTipRTF && m_nToolTipStyle != xtpToolTipHTML && m_nToolTipStyle != xtpToolTipMarkup));

	m_bShowOfficeBorder = GetToolTipContext()->GetControlStyle() & XTP_TTS_OFFICEFRAME ? 1 : 0;
	m_bShowShadow = (GetToolTipContext()->GetControlStyle() & XTP_TTS_NOSHADOW) == 0;

	UpdateData(FALSE);
}

void CPropertiesDialog::OnRadioTooltipStyle() 
{
	UpdateData();


	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	pMainFrame->GetCommandBars()->GetToolTipContext()->
		SetStyle((XTPToolTipStyle)m_nToolTipStyle);

	pMainFrame->m_wndClient.GetToolTipContext()->
		SetStyle((XTPToolTipStyle)m_nToolTipStyle);

	if (m_nToolTipStyle == xtpToolTipMarkup)
	{
		pMainFrame->GetCommandBars()->GetToolTipContext()->ModifyToolTipStyle(0, XTP_TTS_OFFICE2007FRAME);
	}

	UpdateControls();
	UpdateCommandBarToolTips();
}

void CPropertiesDialog::OnCheckShowIcons()
{
	UpdateData();

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	pMainFrame->GetCommandBars()->GetToolTipContext()->ShowImage(m_bShowIcons);
	pMainFrame->m_wndClient.GetToolTipContext()->ShowImage(m_bShowIcons);


}

void CPropertiesDialog::ToggleStyle(DWORD dwStyle)
{
	CXTPToolTipContext* pToolTipContext = 
		((CXTPMDIFrameWnd*) AfxGetMainWnd())->GetCommandBars()->GetToolTipContext();

	if (pToolTipContext->GetControlStyle() & dwStyle)
		pToolTipContext->ModifyToolTipStyle(dwStyle, 0);
	else
		pToolTipContext->ModifyToolTipStyle(0, dwStyle);
}

void CPropertiesDialog::OnCheckShowShadow()
{
	UpdateData();

	ToggleStyle(XTP_TTS_NOSHADOW);
}

void CPropertiesDialog::OnCheckShowOfficeBorder()
{
	UpdateData();

	ToggleStyle(XTP_TTS_OFFICEFRAME);
}


void CPropertiesDialog::OnCheckShowTips() 
{
	UpdateData();

	((CXTPMDIFrameWnd*) AfxGetMainWnd())->GetCommandBars()->
		GetCommandBarsOptions()->bToolBarScreenTips = m_bToolBarScreenTips;

	GetDlgItem(IDC_CHECK_SHOWSHORTCUTS)->EnableWindow(m_bToolBarScreenTips);
	GetDlgItem(IDC_CHECK_POPUPBARTIPS)->EnableWindow(m_bToolBarScreenTips);

	
}

void CPropertiesDialog::OnCheckShowshortcuts() 
{
	UpdateData();

	((CXTPMDIFrameWnd*) AfxGetMainWnd())->GetCommandBars()->
		GetCommandBarsOptions()->bToolBarAccelTips = m_bToolBarAccelTips;
}

BOOL CPropertiesDialog::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXT);

	TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;

	if (!(pTTT->uFlags & TTF_IDISHWND))
		return FALSE;

	UINT_PTR hWnd = pNMHDR->idFrom;
	// idFrom is actually the HWND of the tool
	UINT nID = (UINT)(WORD)::GetDlgCtrlID((HWND)hWnd);

	pTTT->lpszText = MAKEINTRESOURCE(nID);
	pTTT->hinst = AfxGetInstanceHandle();

	*pResult = 0;

	// bring the tooltip window above other popup windows
	::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
		SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);

	return TRUE;    // message was handled
}


INT_PTR CPropertiesDialog::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	
	HWND hWndChild = NULL;
	// find child window which hits the point
	// (don't use WindowFromPoint, because it ignores disabled windows)
	// see _AfxChildWindowFromPoint(m_hWnd, point);
	::ClientToScreen(m_hWnd, &point);
	HWND hChild = ::GetWindow(m_hWnd, GW_CHILD);
	for (; hChild != NULL; hChild = ::GetWindow(hChild, GW_HWNDNEXT))
	{
		if ((UINT)(WORD)::GetDlgCtrlID(hChild) != (WORD)-1 &&
			(::GetWindowLong(hChild, GWL_STYLE) & WS_VISIBLE))
		{
            // see if point hits the child window
            CRect rect;
            ::GetWindowRect(hChild, rect);
            if (rect.PtInRect(point))
            {
				hWndChild = hChild;
				break;
            }
		}
	}
	
	if (hWndChild != NULL)
	{
		// return positive hit if control ID isn't -1
		INT_PTR nHit = (UINT)(WORD)::GetDlgCtrlID(hWndChild);
		
		// hits against child windows always center the tip
		if (pTI != NULL && pTI->cbSize >= sizeof(XTP_TOOLTIP_TOOLINFO))
		{
            // setup the TOOLINFO structure
            pTI->hwnd = m_hWnd;
            pTI->uId = (UINT_PTR)hWndChild;
            pTI->uFlags |= TTF_IDISHWND;
            pTI->lpszText = LPSTR_TEXTCALLBACK;
			
			// set TTF_NOTBUTTON and TTF_CENTERTIP if it isn't a button
			if (!(::SendMessage(hWndChild, WM_GETDLGCODE, 0, 0) &
				DLGC_BUTTON))
				pTI->uFlags |= TTF_NOTBUTTON|TTF_CENTERTIP;
		}
		return nHit;
	}
	return -1;  // not found
} 
