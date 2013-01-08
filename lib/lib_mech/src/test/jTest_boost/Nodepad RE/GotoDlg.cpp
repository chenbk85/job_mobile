// GotoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "notepadre.h"
#include "GotoDlg.h"

#include <htmlhelp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoDlg dialog
CGotoDlg::CGotoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoDlg)
	m_uiLine = 1;
	m_uiColumn = 1;
	//}}AFX_DATA_INIT
}

void CGotoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoDlg)
	DDX_Text(pDX, IDC_EDIT_LINE, m_uiLine);
	DDX_Text(pDX, IDC_EDIT_COLUMN, m_uiColumn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGotoDlg, CDialog)
	//{{AFX_MSG_MAP(CGotoDlg)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoDlg message handlers

BOOL CGotoDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	BOOL bRet = TRUE;
	RECT rect;
	HH_POPUP popup;
	CString strArial8;

	switch (pHelpInfo->iCtrlId)
	{
		case IDC_EDIT_LINE :
			GetDlgItem (IDC_EDIT_LINE)->GetWindowRect (&rect);
			popup.idString = IDS_LINE;
			break;
		case IDC_EDIT_COLUMN :
			GetDlgItem (IDC_EDIT_COLUMN)->GetWindowRect (&rect);
			popup.idString = IDS_COLUMN;
			break;
		case IDOK :
			GetDlgItem (IDOK)->GetWindowRect (&rect);
			popup.idString = IDS_OK_GOTO;
			break;
		case IDCANCEL :
			GetDlgItem (IDCANCEL)->GetWindowRect (&rect);
			popup.idString = IDS_CANCEL;
			break;
		default:
			ASSERT (0);
			break;
	}

	popup.cbStruct = sizeof (popup);
	popup.hinst = AfxGetResourceHandle ();
	popup.pszText = 0;
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
	::HtmlHelp (0, 0, HH_DISPLAY_TEXT_POPUP,
		(DWORD) &popup);
	return bRet;
}
