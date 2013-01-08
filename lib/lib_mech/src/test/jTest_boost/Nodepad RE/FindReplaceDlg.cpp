// FindReplaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "notepadre.h"
#include "FindReplaceDlg.h"
#include "enums.h"
#include "messages.h"

#include <htmlhelp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindReplaceDlg dialog
CFindReplaceDlg::CFindReplaceDlg () : m_pParentWnd (0), m_IDD (0),
	m_bInitialWholeWordOnly (false), m_bInitialMatchCase (false),
	m_bInitialRegEx (false)
{
}

void CFindReplaceDlg::SetInitial (CWnd *pParentWnd, const int IDD)
{
	m_pParentWnd = pParentWnd;
	m_IDD = IDD;
}

void CFindReplaceDlg::SetWholeWordOnly (const bool bWholeWordOnly)
{
	m_CheckWholeWordOnly.SetCheck (bWholeWordOnly);
}

void CFindReplaceDlg::SetMatchCase (const bool bMatchCase)
{
	m_CheckMatchCase.SetCheck (bMatchCase);
}

void CFindReplaceDlg::SetRegEx (const bool bRegEx)
{
	m_CheckRegEx.SetCheck (bRegEx);
	OnCheckRegex ();
}

void CFindReplaceDlg::SetSearchUp (const bool bUp)
{
	if (!m_CheckRegEx.GetCheck ())
	{
		m_RadioUp.SetCheck (bUp);
		m_RadioDown.SetCheck (!bUp);
	}
}

void CFindReplaceDlg::SetCloseOnMatch (const bool bCloseOnMatch)
{
	m_CheckCloseOnMatch.SetCheck (bCloseOnMatch);
}

void CFindReplaceDlg::
	SetReplaceAllLikeNotepad (const bool bReplaceAllLikeNotepad)
{
	m_CheckReplaceAllLikeNotepad.SetCheck (bReplaceAllLikeNotepad);
}

const CString &CFindReplaceDlg::GetFindText ()
{
	m_EditFindText.GetWindowText (m_strFindText);
	return m_strFindText;
}

const CString &CFindReplaceDlg::GetReplaceText ()
{
	m_EditReplaceText.GetWindowText (m_strReplaceText);
	return m_strReplaceText;
}

void CFindReplaceDlg::SetFindText (const CString &strFind)
{
	m_EditFindText.SetWindowText (strFind);
}

void CFindReplaceDlg::SetReplaceText (const CString &strReplace)
{
	m_EditReplaceText.SetWindowText (strReplace);
}

void CFindReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindReplaceDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFindReplaceDlg, CDialogBar)
	//{{AFX_MSG_MAP(CFindReplaceDlg)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_CHECK_WHOLE_WORD, OnCheckWholeWord)
	ON_BN_CLICKED(IDC_CHECK_MATCH_CASE, OnCheckMatchCase)
	ON_BN_CLICKED(IDC_CHECK_REGEX, OnCheckRegex)
	ON_BN_CLICKED(IDC_CHECK_LIKE_NOTEPAD, OnCheckLikeNotepad)
	ON_BN_CLICKED(IDC_RADIO_UP, OnRadioUp)
	ON_BN_CLICKED(IDC_RADIO_DOWN, OnRadioDown)
	ON_BN_CLICKED(IDC_CHECK_CLOSE_ON_MATCH, OnCheckCloseOnMatch)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE, OnButtonReplace)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE_ALL, OnButtonReplaceAll)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindReplaceDlg message handlers

LONG CFindReplaceDlg::OnInitDialog (UINT wParam, LONG lParam)
{
	BOOL bRet = HandleInitDialog (wParam, lParam);

	m_CheckWholeWordOnly.SubclassDlgItem (IDC_CHECK_WHOLE_WORD, this);

	if (m_bInitialRegEx)
	{
		m_CheckWholeWordOnly.EnableWindow (FALSE);
	}
	else
	{
		m_CheckWholeWordOnly.SetCheck (m_bInitialWholeWordOnly);
	}

	m_CheckMatchCase.SubclassDlgItem (IDC_CHECK_MATCH_CASE, this);
	m_CheckMatchCase.SetCheck (m_bInitialMatchCase);
	m_CheckRegEx.SubclassDlgItem (IDC_CHECK_REGEX, this);
	m_CheckRegEx.SetCheck (m_bInitialRegEx);

	if (m_IDD == IDD_FIND)
	{
		m_RadioUp.SubclassDlgItem (IDC_RADIO_UP, this);
		m_RadioDown.SubclassDlgItem (IDC_RADIO_DOWN, this);
		m_RadioDown.SetCheck (TRUE);
		if (m_bInitialRegEx) m_RadioUp.EnableWindow (FALSE);
		m_CheckCloseOnMatch.SubclassDlgItem (IDC_CHECK_CLOSE_ON_MATCH, this);
	}
	else
	{
		m_EditReplaceText.SubclassDlgItem (IDC_EDIT_REPLACE, this);
		m_CheckReplaceAllLikeNotepad.SubclassDlgItem (IDC_CHECK_LIKE_NOTEPAD,
			this);
	}

	m_EditFindText.SubclassDlgItem (IDC_EDIT_FIND, this);
	m_EditFindText.SetWindowText (m_strInitialFind);
	m_ButtonReplace.SubclassDlgItem (IDC_BUTTON_REPLACE, this);
	
	if (m_IDD == IDD_FIND)
	{
		SetWindowText (_T("Find"));
	}
	else
	{
		SetWindowText (_T("Replace"));
	}

	return bRet;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CFindReplaceDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	BOOL bRet = TRUE;
	RECT rect;
	HH_POPUP popup;
	CString strArial8;

	switch (pHelpInfo->iCtrlId)
	{
		case IDC_EDIT_FIND :
			m_EditFindText.GetWindowRect (&rect);
			popup.idString = IDS_FIND_WHAT;
			break;
		case IDC_EDIT_REPLACE :
			m_EditReplaceText.GetWindowRect (&rect);
			popup.idString = IDS_REPLACE_WHAT;
			break;
		case IDC_CHECK_WHOLE_WORD :
			m_CheckWholeWordOnly.GetWindowRect (&rect);
			popup.idString = IDS_WHOLE_WORD_ONLY;
			break;
		case IDC_CHECK_MATCH_CASE :
			m_CheckMatchCase.GetWindowRect (&rect);
			popup.idString = IDS_MATCH_CASE;
			break;
		case IDC_CHECK_REGEX :
			m_CheckRegEx.GetWindowRect (&rect);
			popup.idString = IDS_REGULAR_EXPRESSION;
			break;
		case IDC_CHECK_LIKE_NOTEPAD :
			m_CheckReplaceAllLikeNotepad.GetWindowRect (&rect);
			popup.idString = IDS_LIKE_NOTEPAD;
			break;
		case IDC_RADIO_UP :
			m_RadioUp.GetWindowRect (&rect);
			popup.idString = IDS_UP;
			break;
		case IDC_RADIO_DOWN :
			m_RadioDown.GetWindowRect (&rect);
			popup.idString = IDS_DOWN;
			break;
		case IDC_CHECK_CLOSE_ON_MATCH :
			m_CheckCloseOnMatch.GetWindowRect (&rect);
			popup.idString = IDS_CLOSE_ON_MATCH;
			break;
		case IDOK :
			GetDlgItem (IDOK)->GetWindowRect (&rect);
			popup.idString = IDS_FIND_NEXT;
			break;
		case IDC_BUTTON_REPLACE :
			GetDlgItem (IDC_BUTTON_REPLACE)->GetWindowRect (&rect);
			popup.idString = IDS_REPLACE;
			break;
		case IDC_BUTTON_REPLACE_ALL :
			GetDlgItem (IDC_BUTTON_REPLACE_ALL)->GetWindowRect (&rect);
			popup.idString = IDS_REPLACE_ALL;
			break;
		case IDCANCEL :
			GetDlgItem (IDCANCEL)->GetWindowRect (&rect);
			popup.idString = IDS_CANCEL;
			break;
		case IDC_BUTTON_HELP :
			GetDlgItem (IDC_BUTTON_HELP)->GetWindowRect (&rect);
			popup.idString = IDS_HELP;
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

void CFindReplaceDlg::OnCheckWholeWord ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eWholeWordOnly,
		m_CheckWholeWordOnly.GetCheck ());
}

void CFindReplaceDlg::OnCheckMatchCase ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eMatchCase,
		m_CheckMatchCase.GetCheck ());
}

void CFindReplaceDlg::OnCheckRegex ()
{
	const bool bRegEx = m_CheckRegEx.GetCheck () != 0;

	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eRegEx, bRegEx);

	if (bRegEx)
	{
		m_CheckWholeWordOnly.SetCheck (FALSE);
		OnCheckWholeWord ();
	}

	m_CheckWholeWordOnly.EnableWindow (!bRegEx);

	if (m_IDD == IDD_FIND)
	{
		if (bRegEx)
		{
			m_RadioUp.SetCheck (FALSE);
			m_RadioDown.SetCheck (TRUE);
			OnRadioDown ();
		}

		m_RadioUp.EnableWindow (!bRegEx);
	}
}

void CFindReplaceDlg::OnCheckLikeNotepad ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eReplaceAllLikeNotepad,
		m_CheckReplaceAllLikeNotepad.GetCheck ());
}

void CFindReplaceDlg::OnRadioUp ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eUp, 0);
}

void CFindReplaceDlg::OnRadioDown ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eDown, 0);
}

void CFindReplaceDlg::OnCheckCloseOnMatch ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eCloseOnMatch,
		m_CheckCloseOnMatch.GetCheck ());
}

void CFindReplaceDlg::OnOk ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eFind,
		reinterpret_cast<LPARAM> (this));
}

void CFindReplaceDlg::OnButtonReplace ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eReplace,
		reinterpret_cast<LPARAM> (this));
}

void CFindReplaceDlg::OnButtonReplaceAll ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eReplaceAll,
		reinterpret_cast<LPARAM> (this));
}

void CFindReplaceDlg::OnCancel ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eClose, 0);
}

void CFindReplaceDlg::OnButtonHelp ()
{
	m_pParentWnd->PostMessage (WM_NOTIFY_FIND_REPLACE, eHelp, 0);
}
