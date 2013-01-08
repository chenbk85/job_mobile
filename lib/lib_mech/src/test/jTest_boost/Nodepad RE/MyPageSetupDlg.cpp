#include "stdafx.h"

#include <htmlhelp.h>

#include "MyPageSetupDlg.h"

#include "resource.h"

BEGIN_MESSAGE_MAP(CMyPageSetupDlg, CPageSetupDialog)
	//{{AFX_MSG_MAP(CMyPageSetupDlg)
	ON_WM_HELPINFO()
	ON_WM_DESTROY ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyPageSetupDlg::CMyPageSetupDlg (const CString &strHeader,
	const CString &strFooter, DWORD dwFlags, CWnd* pParentWnd) :
	CPageSetupDialog (dwFlags | PSD_ENABLEPAGESETUPTEMPLATE, pParentWnd),
	m_strHeader (strHeader),
	m_strFooter (strFooter)
{
	m_psd.hInstance = AfxGetResourceHandle ();
	m_psd.lpPageSetupTemplateName =	MAKEINTRESOURCE (IDD_PAGE_SETUP);
}

void CMyPageSetupDlg::GetHeader (CString &strHeader)
{
	strHeader = m_strHeader;
}

void CMyPageSetupDlg::GetFooter (CString &strFooter)
{
	strFooter = m_strFooter;
}

BOOL CMyPageSetupDlg::OnInitDialog ()
{
	BOOL bRet = CPageSetupDialog::OnInitDialog ();

	m_EditHeader.SubclassDlgItem (IDC_EDIT_HEADER, this);
	m_EditFooter.SubclassDlgItem (IDC_EDIT_FOOTER, this);
	m_EditHeader.SetWindowText (m_strHeader);
	m_EditFooter.SetWindowText (m_strFooter);
	m_EditHeader.LimitText (40);
	m_EditFooter.LimitText (40);
	return bRet;
}

BOOL CMyPageSetupDlg::OnHelpInfo (HELPINFO* pHelpInfo)
{
	BOOL bRet = TRUE;

	if (pHelpInfo->iCtrlId == IDC_EDIT_HEADER ||
		pHelpInfo->iCtrlId == IDC_EDIT_FOOTER)
	{
		HH_POPUP popup;
		RECT rect;
		CString strArial8;

		pHelpInfo->iCtrlId == IDC_EDIT_HEADER ?
			m_EditHeader.GetWindowRect (&rect) :
			m_EditFooter.GetWindowRect (&rect);
		popup.cbStruct = sizeof (popup);
		popup.hinst = AfxGetResourceHandle ();
		popup.idString = 0;
		// Resource strings seem to be length limited for HtmlHelp, so
		// a straight C string is used instead...
		popup.pszText = _T("You can print information at the bottom of each ")
			_T("page in the file.\n")
			_T("To have Notepad RE print information in the footer, use the ")
			_T("letter\n")
			_T("and character combination in the following table.\n\n")
			_T("To\t\t\t\t\t\t\tType\nInsert the open files name or \"(untitled)\" ")
			_T("if the file has no\t&f\n")
			_T("name.\n")
			_T("Insert the date.\t\t\t\t\t\t&d\n")
			_T("Insert the time specified by your computers clock.\t\t&t\n")
			_T("Insert page numbers.\t\t\t\t\t&p\n")
			_T("Insert page numbers offset by n.\t\t\t\t&p+n\n")
			_T("Insert an ampersand (&).\t\t\t\t&&\n")
			_T("Align the header to the left, centre, or right.\t\t&l, &c or &r");
		popup.pt.x = rect.left;
		popup.pt.y = rect.top;
		popup.clrForeground = -1;
		popup.clrBackground = -1;
		popup.rcMargins.top = 7;
		popup.rcMargins.left = 20;
		popup.rcMargins.bottom = 7;
		popup.rcMargins.right = 7;
		strArial8.LoadString (IDS_ARIAL_8);
		popup.pszFont = strArial8;
		::HtmlHelp (0, 0, HH_DISPLAY_TEXT_POPUP, (DWORD) &popup);
	}
	else
	{
		bRet = CPageSetupDialog::OnHelpInfo (pHelpInfo);
	}

	return bRet;
}

void CMyPageSetupDlg::OnDestroy ()
{
	m_EditHeader.GetWindowText (m_strHeader);
	m_EditFooter.GetWindowText (m_strFooter);
	CPageSetupDialog::OnDestroy ();
}
