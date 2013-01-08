// XTTipOfTheDay.cpp : implementation of the CXTTipOfTheDay class.
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

#include "stdafx.h"
#include "Common/XTPVC80Helpers.h"  // Visual Studio 2005 helper functions
#include "Common/XTPResourceManager.h"
#include "Common/XTPDrawHelpers.h"
#include "Common/XTPColorManager.h"

#include "Resource.h"
#include "XTDefines.h"
#include "XTGlobal.h"
#include "XTTipOfTheDay.h"
#include "XTRegistryManager.h"

#include <winreg.h>
#include <sys\stat.h>
#include <sys\types.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MAX_BUFLEN 1000

static const TCHAR szSection[] = _T("Tip");
static const TCHAR szIntFilePos[] = _T("FilePos");
static const TCHAR szTimeStamp[] = _T("TimeStampLong");
static const TCHAR szIntStartup[] = _T("StartUp");
/////////////////////////////////////////////////////////////////////////////
// CXTTipOfTheDay dialog
/////////////////////////////////////////////////////////////////////////////
CXTTipOfTheDay::CXTTipOfTheDay(LPCTSTR lpszTipFile/*= NULL*/, CWnd* pParent/*= NULL*/)
{
	InitModalIndirect(XTPResourceManager()->LoadDialogTemplate(IDD), pParent);

	//{{AFX_DATA_INIT(CXTTipOfTheDay)
	m_bStartup = TRUE;
	//}}AFX_DATA_INIT

	SetTipsFilePath(lpszTipFile);
	VERIFY(XTPResourceManager()->LoadString(&m_strTipTitle, XT_IDS_DIDYOUKNOW));

	m_strTipText = _T("");
	m_pFontTitle = NULL;
	m_pFontTip = NULL;

	m_bClassicStyle = FALSE;

	{
		CXTPResourceManager::CManageState state;
		m_ilLightBulb.SetIcon(XT_IDI_LIGHTBULB, 1);
	}

	// We need to find out what the startup and file position parameters are
	// If startup does not exist, we assume that the Tips on startup is checked TRUE.
	CXTRegistryManager regManager;
	m_bStartup = !regManager.GetProfileInt(szSection, szIntStartup, 0);
	UINT iFilePos = regManager.GetProfileInt(szSection, szIntFilePos, 0);

	// Now try to open the tips file
	m_pStream = FOPEN_S((TCHAR*)(LPCTSTR)m_strTipFile, _T("r"));
	if (m_pStream == NULL)
	{
		VERIFY(XTPResourceManager()->LoadString(&m_strTipText, XT_IDS_FILE_ABSENT));
		return;
	}

	// If the timestamp in the INI file is different from the timestamp of
	// the tips file, then we know that the tips file has been modified
	// Reset the file position to 0 and write the latest timestamp to the
	// ini file
	struct _stat buf;
	_fstat(_fileno(m_pStream), &buf);

	int nCurrentTime = (int)(buf.st_ctime);

	int nStoredTime = (int)regManager.GetProfileInt(
		szSection, szTimeStamp, NULL);

	if (nCurrentTime != nStoredTime)
	{
		iFilePos = 0;
		regManager.WriteProfileInt(szSection, szTimeStamp, nCurrentTime);
	}

	if (fseek(m_pStream, iFilePos, SEEK_SET) != 0)
	{
		XTPResourceManager()->ShowMessageBox(XT_IDS_FILE_CORRUPT);
	}
	else
	{
		GetNextTipString(m_strTipText);
	}
}

CXTTipOfTheDay::~CXTTipOfTheDay()
{
	// This destructor is executed whether the user had pressed the escape key
	// or clicked on the close button. If the user had pressed the escape key,
	// it is still required to update the filepos in the ini file with the
	// latest position so that we don't repeat the tips!

	// But make sure the tips file existed in the first place....
	if (m_pStream != NULL)
	{
		CXTRegistryManager regManager;
		regManager.WriteProfileInt(szSection, szIntFilePos, ftell(m_pStream));
		fclose(m_pStream);
	}

	if (m_fontTitle.GetSafeHandle())
		m_fontTitle.DeleteObject();

	if (m_fontTip.GetSafeHandle())
		m_fontTip.DeleteObject();
}

void CXTTipOfTheDay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXTTipOfTheDay)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, XT_IDC_CHK_DAYTIP_SHOW, m_showTips);
	DDX_Control(pDX, XT_IDC_BTN_DAYTIP_NEXT, m_btnNextTip);
	DDX_Control(pDX, XT_IDC_BTN_DAYTIP_BORDER, m_staticBorder);
	DDX_Check(pDX, XT_IDC_CHK_DAYTIP_SHOW, m_bStartup);
	//}}AFX_DATA_MAP
}

IMPLEMENT_DYNAMIC(CXTTipOfTheDay, CDialog)

BEGIN_MESSAGE_MAP(CXTTipOfTheDay, CDialog)
	//{{AFX_MSG_MAP(CXTTipOfTheDay)
	ON_WM_PAINT()
	ON_BN_CLICKED(XT_IDC_BTN_DAYTIP_NEXT, OnDaytipNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CXTTipOfTheDay::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.SetBkMode(TRANSPARENT);

	if (m_bClassicStyle)
	{
		CRect rcBorder(m_rcBorder);
		rcBorder.DeflateRect(10, 10, 10, 0);

		dc.FillSolidRect(rcBorder.left + 50, rcBorder.top, rcBorder.Width() - 50, rcBorder.Height(), GetXtremeColor(COLOR_WINDOW));
		dc.FillSolidRect(rcBorder.left, rcBorder.top, 50, rcBorder.Height(), RGB(128, 128, 128));

		dc.Draw3dRect(rcBorder, GetXtremeColor(COLOR_3DSHADOW), GetXtremeColor(COLOR_3DHIGHLIGHT));

		// Draw the light bulb bitmap to the screen.
		CXTPImageManagerIcon* pIcon = m_ilLightBulb.GetImage(1, 32);
		if (pIcon) pIcon->Draw(&dc, CPoint(rcBorder.left + 8, rcBorder.top + 8));

		// Draw the title text.
		CXTPFontDC font(&dc, m_pFontTitle);
		dc.SetTextColor(GetXtremeColor(COLOR_WINDOWTEXT));
		dc.TextOut(52 + 10 + 5, 14 + 5, m_strTipTitle);

		// Draw the tip of the day text.
		font.SetFont(m_pFontTip);
		dc.DrawText(m_strTipText, m_rcTipText, DT_END_ELLIPSIS | DT_WORDBREAK);
	}
	else
	{
		dc.FillSolidRect(m_rcBorder, GetXtremeColor(COLOR_WINDOW));
		dc.FillSolidRect(m_rcBorder.left, m_rcBorder.bottom, m_rcBorder.Width(), 1, GetXtremeColor(COLOR_3DSHADOW));

		// Draw the light bulb bitmap to the screen.
		CXTPImageManagerIcon* pIcon = m_ilLightBulb.GetImage(1, 32);
		if (pIcon) pIcon->Draw(&dc, CPoint(8, 8));

		// Draw the title text.
		CXTPFontDC font(&dc, m_pFontTitle);
		dc.SetTextColor(RGB(0x00, 0x33, 0x99));
		dc.TextOut(52, 14, m_strTipTitle);

		// Draw the tip of the day text.
		font.SetFont(m_pFontTip);
		dc.SetTextColor(GetXtremeColor(COLOR_WINDOWTEXT));
		dc.DrawText(m_strTipText, m_rcTipText, DT_END_ELLIPSIS | DT_WORDBREAK);
	}

	// Do not call CDialog::OnPaint() for painting messages

}

BOOL CXTTipOfTheDay::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set font title if it has not been already set.
	if (m_pFontTitle == NULL && m_pFontTip == NULL)
	{
		CWindowDC dc(NULL);

		NONCLIENTMETRICS ncm;
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);

		if (_tcscmp(ncm.lfMenuFont.lfFaceName, _T("Segoe UI")) == 0)
			ncm.lfMenuFont.lfQuality = 5;

		ncm.lfMenuFont.lfWeight = FW_NORMAL;
		ncm.lfMenuFont.lfItalic = 0;
		m_fontTip.CreateFontIndirect(&ncm.lfMenuFont);

		ncm.lfMenuFont.lfHeight = ::MulDiv(-12, ::GetDeviceCaps(dc.m_hDC, LOGPIXELSY), 72);

		if (_tcscmp(ncm.lfMenuFont.lfFaceName, _T("Segoe UI")) != 0)
			ncm.lfMenuFont.lfWeight = FW_BOLD;
		m_fontTitle.CreateFontIndirect(&ncm.lfMenuFont);

		m_pFontTip = &m_fontTip;
		m_pFontTitle = &m_fontTitle;
	}

	// If Tips file does not exist then disable NextTip
	m_btnNextTip.EnableWindow(m_pStream != NULL);

	// Get the border size, this will be the base for our
	// painting routines.

	CRect rcBorder;
	m_staticBorder.GetWindowRect(&rcBorder);
	ScreenToClient(&rcBorder);

	m_rcBorder = CXTPClientRect(this);
	m_rcBorder.bottom = rcBorder.bottom - 1;

	if (!m_bClassicStyle)
		m_rcTipText.SetRect(52, 44, m_rcBorder.right - 6, m_rcBorder.bottom - 6);
	else
		m_rcTipText.SetRect(52 + 10 + 5, 44 + 5, m_rcBorder.right - 6 - 10, m_rcBorder.bottom - 6);

	m_ok.SetFont(&XTAuxData().font);
	m_showTips.SetFont(&XTAuxData().font);
	m_btnNextTip.SetFont(&XTAuxData().font);

	return TRUE;
}

void CXTTipOfTheDay::SetDefaultFonts(CFont* pFontTitle, CFont* pFontTip)
{
	m_pFontTitle = pFontTitle;
	m_pFontTip = pFontTip;
}

void CXTTipOfTheDay::GetNextTipString(CString& strNext)
{
	LPTSTR lpsz = strNext.GetBuffer(MAX_BUFLEN);

	// This routine identifies the next string that needs to be
	// read from the tips file
	BOOL bStop = FALSE;
	while (!bStop)
	{
		if (_fgetts(lpsz, MAX_BUFLEN, m_pStream) == NULL)
		{
			// We have either reached EOF or encountered some problem
			// In both cases reset the pointer to the beginning of the file
			// This behavior is same as VC++ Tips file
			if (fseek(m_pStream, 0, SEEK_SET) != 0)
				XTPResourceManager()->ShowMessageBox(XT_IDS_FILE_CORRUPT);
		}
		else
		{
			if (*lpsz != ' ' && *lpsz != '\t' &&
				*lpsz != '\n' && *lpsz != ';')
			{
				// There should be no space at the beginning of the tip
				// This behavior is same as VC++ Tips file
				// Comment lines are ignored and they start with a semicolon
				bStop = TRUE;
			}
		}
	}
	strNext.ReleaseBuffer();
}

void CXTTipOfTheDay::OnOK()
{
	// Update the startup information stored in the INI file
	UpdateData();
	CXTRegistryManager regManager;
	regManager.WriteProfileInt(szSection, szIntStartup, !m_bStartup);

	CDialog::OnOK();
}

void CXTTipOfTheDay::OnDaytipNext()
{
	UpdateData();
	GetNextTipString(m_strTipText);
	InvalidateRect(m_rcTipText);
	UpdateData(FALSE);
}

void CXTTipOfTheDay::SetTipsFilePath(LPCTSTR lpszTipFile)
{
	CFileFind file;
	if (lpszTipFile && file.FindFile(lpszTipFile))
	{
		m_strTipFile = lpszTipFile;
	}
	else
	{
		m_strTipFile = _T("tips.txt");
	}
}
