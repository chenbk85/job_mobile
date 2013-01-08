// notepadreDoc.cpp : implementation of the CNotepadreDoc class
//

#include "stdafx.h"
#include "messages.h"
#include "notepadre.h"

#include "FindReplaceDlg.h"
#include "MainFrm.h"
#include "notepadreDoc.h"
#include "NotepadreView.h"
#include "RegexSyntaxDlg.h"
#include "enums.h"

#include <algorithm>
#include "nocasepred.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotepadreDoc

#ifdef _UNICODE
#define _tcstoi _wtoi
#else
#define _tcstoi atoi
#endif

unsigned int CNotepadreDoc::m_uiMatchFlags = boost::match_default;
bool CNotepadreDoc::m_bReplaceAllLikeNotepad = false;
TReplacementStack CNotepadreDoc::m_ReplacementStack;
LPCTSTR CNotepadreDoc::m_pszText = 0;
ULONG CNotepadreDoc::m_ulTextIndex = 0;
ULONG CNotepadreDoc::m_ulBufferIncrement = 1024;
TString CNotepadreDoc::m_strBuffer;
LPCTSTR CNotepadreDoc::m_lpszReplace = 0;
TString CNotepadreDoc::m_strReplaceText;

IMPLEMENT_DYNCREATE(CNotepadreDoc, CDocument)

BEGIN_MESSAGE_MAP(CNotepadreDoc, CDocument)
	//{{AFX_MSG_MAP(CNotepadreDoc)
	ON_COMMAND(ID_OPTIONS_REGEX_SYNTAX, OnOptionsRegexSyntax)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotepadreDoc construction/destruction

CNotepadreDoc::CNotepadreDoc () :
	m_tSyntax (0),
	m_bReadOnly (false),
	m_eFileType (CNotepadreFile::eANSI),
	m_eFileFormat (CNotepadreFile::eWindows),
	m_eRequestedFileType (CNotepadreFile::eANSI),
	m_eRequestedFileFormat (CNotepadreFile::eWindows),
	m_bWholeWordOnly (false),
	m_bMatchCase (false),
	m_bRegEx (true),
	m_bCompiled (false),
	m_bSearchForward (true),
	m_bCloseOnMatch (false),
	m_bScrollToEnd (false),
	m_bFileChangeNotify (true),
	m_bAutoReload (false)
{
	HKEY hKey = 0;
	CString strNotepadreRegKey;
	LONG lRet = 0;

	m_strValidChars.LoadString (IDS_VALID_CHARS);
	strNotepadreRegKey.LoadString (IDS_NOTEPADRE_REG_KEY);
	lRet = ::RegOpenKey (HKEY_CURRENT_USER, strNotepadreRegKey, &hKey);

	if (lRet == ERROR_SUCCESS)
	{
		CString strEntry;
		ULONG ulSize = 4;
		DWORD dwType = 0;
		DWORD dwRegEx = 1;
		DWORD dwScrollToEnd = 0;
		DWORD dwFileChangeNotify = 1;
		DWORD dwAutoReload = 0;

		DWORD dwescape_in_lists = 1;
		DWORD dwchar_classes = 1;
		DWORD dwintervals = 1;
		DWORD dwlimited_ops = 0;
		DWORD dwnewline_alt = 0;
		DWORD dwbk_plus_qm = 0;
		DWORD dwbk_braces = 0;
		DWORD dwbk_parens = 0;
		DWORD dwbk_refs = 1;
		DWORD dwbk_vbar = 0;
		DWORD dwliteral = 0;
		DWORD dwcollate = 0;
		DWORD dwperlex = 1;
		DWORD dwnosubs = 0;

		DWORD dwmatch_not_dot_newline = 1;
		DWORD dwmatch_not_dot_null = 0;
		DWORD dwmatch_any = 0;
		DWORD dwmatch_not_null = 0;
		DWORD dwmatch_continuous = 0;
		DWORD dwmatch_extra = 0;
		DWORD dwmatch_single_line = 0;
		DWORD dwformat_perl = 0;
		DWORD dwformat_sed = 0;
		DWORD dwformat_all = 0;
		DWORD dwformat_first_only = 0;

		strEntry.LoadString (IDS_REG_EX);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwRegEx, &ulSize);
		m_bRegEx = dwRegEx != 0;
		strEntry.LoadString (IDS_SCROLL_TO_END);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwScrollToEnd, &ulSize);
		m_bScrollToEnd = dwScrollToEnd != 0;
		strEntry.LoadString (IDS_FILE_CHANGE_NOTIFY);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwFileChangeNotify, &ulSize);
		m_bFileChangeNotify = dwFileChangeNotify != 0;
		strEntry.LoadString (IDS_AUTO_RELOAD);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwAutoReload, &ulSize);

		if (m_bFileChangeNotify && dwAutoReload)
		{
			m_bAutoReload = true;
		}

		strEntry.LoadString (IDS_ESCAPE_IN_LISTS);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwescape_in_lists, &ulSize);
		strEntry.LoadString (IDS_CHAR_CLASSES);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwchar_classes, &ulSize);
		strEntry.LoadString (IDS_INTERVALS);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwintervals, &ulSize);
		strEntry.LoadString (IDS_LIMITED_OPS);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwlimited_ops, &ulSize);
		strEntry.LoadString (IDS_NEWLINE_ALT);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwnewline_alt, &ulSize);
		strEntry.LoadString (IDS_BK_PLUS_QM);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwbk_plus_qm, &ulSize);
		strEntry.LoadString (IDS_BK_BRACES);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwbk_braces, &ulSize);
		strEntry.LoadString (IDS_BK_PARENS);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwbk_parens, &ulSize);
		strEntry.LoadString (IDS_BK_REFS);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwbk_refs, &ulSize);
		strEntry.LoadString (IDS_BK_VBAR);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwbk_vbar, &ulSize);
		strEntry.LoadString (IDS_LITERAL);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwliteral, &ulSize);
		strEntry.LoadString (IDS_COLLATE);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwcollate, &ulSize);
		strEntry.LoadString (IDS_PERLEX);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwperlex, &ulSize);
		strEntry.LoadString (IDS_NOSUBS);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwnosubs, &ulSize);

		strEntry.LoadString (IDS_MATCH_NOT_DOT_NEWLINE);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwmatch_not_dot_newline, &ulSize);
		strEntry.LoadString (IDS_MATCH_NOT_DOT_NULL);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwmatch_not_dot_null, &ulSize);
		strEntry.LoadString (IDS_MATCH_ANY);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwmatch_any, &ulSize);
		strEntry.LoadString (IDS_MATCH_NOT_NULL);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwmatch_not_null, &ulSize);
		strEntry.LoadString (IDS_MATCH_CONTINUOUS);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwmatch_continuous, &ulSize);
		strEntry.LoadString (IDS_MATCH_EXTRA);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwmatch_extra, &ulSize);
		strEntry.LoadString (IDS_MATCH_SINGLE_LINE);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwmatch_single_line, &ulSize);
		strEntry.LoadString (IDS_FORMAT_PERL);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwformat_perl, &ulSize);
		strEntry.LoadString (IDS_FORMAT_SED);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwformat_sed, &ulSize);
		strEntry.LoadString (IDS_FORMAT_ALL);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwformat_all, &ulSize);
		strEntry.LoadString (IDS_FORMAT_FIRST_ONLY);
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwformat_first_only, &ulSize);

		if (dwescape_in_lists) m_tSyntax |= boost::regbase::escape_in_lists;
		if (dwchar_classes) m_tSyntax |= boost::regbase::char_classes;
		if (dwintervals) m_tSyntax |= boost::regbase::intervals;
		if (dwlimited_ops) m_tSyntax |= boost::regbase::limited_ops;
		if (dwnewline_alt) m_tSyntax |= boost::regbase::newline_alt;
		if (dwbk_plus_qm) m_tSyntax |= boost::regbase::bk_plus_qm;
		if (dwbk_braces) m_tSyntax |= boost::regbase::bk_braces;
		if (dwbk_parens) m_tSyntax |= boost::regbase::bk_parens;
		if (dwbk_refs) m_tSyntax |= boost::regbase::bk_refs;
		if (dwbk_vbar) m_tSyntax |= boost::regbase::bk_vbar;
		if (dwliteral) m_tSyntax |= boost::regbase::literal;
		if (dwcollate) m_tSyntax |= boost::regbase::collate;
		if (dwperlex) m_tSyntax |= boost::regbase::perlex;
		if (dwnosubs) m_tSyntax |= boost::regbase::nosubs;

		if (dwmatch_not_dot_newline) m_uiMatchFlags |= boost::match_not_dot_newline;
		if (dwmatch_not_dot_null) m_uiMatchFlags |= boost::match_not_dot_null;
		if (dwmatch_any) m_uiMatchFlags |= boost::match_any;
		if (dwmatch_not_null) m_uiMatchFlags |= boost::match_not_null;
		if (dwmatch_continuous) m_uiMatchFlags |= boost::match_continuous;
		if (dwmatch_extra) m_uiMatchFlags |= boost::match_extra;
		if (dwmatch_single_line) m_uiMatchFlags |= boost::match_single_line;
		if (dwformat_perl) m_uiMatchFlags |= boost::format_perl;
		if (dwformat_sed) m_uiMatchFlags |= boost::format_sed;
		if (dwformat_all) m_uiMatchFlags |= boost::format_all;
		if (dwformat_first_only) m_uiMatchFlags |= boost::format_first_only;
		::RegCloseKey (hKey);
	}
}

CNotepadreDoc::~CNotepadreDoc ()
{
}

void CNotepadreDoc::SetReadOnly (const bool bReadOnly)
{
	m_bReadOnly = bReadOnly;
}

bool CNotepadreDoc::GetReadOnly () const
{
	return m_bReadOnly;
}

void CNotepadreDoc::SetFileType (const CNotepadreFile::e_FileType eFileType,
	const CNotepadreFile::e_FileFormat eFileFormat)
{
	m_eRequestedFileType = eFileType;
	m_eRequestedFileFormat = eFileFormat;
}

void CNotepadreDoc::GetFileType (CNotepadreFile::e_FileType &eFileType,
	CNotepadreFile::e_FileFormat &eFileFormat) const
{
	eFileType = m_eFileType;
	eFileFormat = m_eFileFormat;
}

void CNotepadreDoc::StartFileChangeNotification (LPCTSTR lpszPathName)
{
	CNotepadreView *pView = static_cast <CNotepadreView *>
		(m_viewList.GetHead());

	pView->StartTimer (lpszPathName);
}

void CNotepadreDoc::StopFileChangeNotification ()
{
	// Cater for the case when an invalid file is passed on the command line
	if (!m_viewList.IsEmpty ())
	{
		CNotepadreView *pView = static_cast <CNotepadreView *>
			(m_viewList.GetHead());

		if (pView)
		{
			pView->StopTimer ();
		}
	}
}

const CString &CNotepadreDoc::GetFindText () const
{
	return m_strFind;
}

const CString &CNotepadreDoc::GetReplaceText () const
{
	return m_strReplace;
}

const bool CNotepadreDoc::GetWholeWordOnly () const
{
	return m_bWholeWordOnly;
}

const bool CNotepadreDoc::GetMatchCase () const
{
	return m_bMatchCase;
}

const bool CNotepadreDoc::GetRegEx () const
{
	return m_bRegEx;
}

const bool CNotepadreDoc::GetCompiled () const
{
	return m_bCompiled;
}

const bool CNotepadreDoc::GetSearchForward () const
{
	return m_bSearchForward;
}

void CNotepadreDoc::SetSearchForward (const bool bSearchForward)
{
	m_bSearchForward = bSearchForward;
}

const bool CNotepadreDoc::GetCloseOnMatch () const
{
	return m_bCloseOnMatch;
}

const bool CNotepadreDoc::GetReplaceAllLikeNotepad () const
{
	return m_bReplaceAllLikeNotepad;
}

const bool CNotepadreDoc::NeedFind () const
{
	return m_bRegEx ? !m_regex.empty() : m_strFind.GetLength ();
}

bool CNotepadreDoc::FindText ()
{
	int iStart, iEnd;
	CNotepadreView *pView = static_cast <CNotepadreView *>
		(m_viewList.GetHead());
	CEdit &EditCtrl = pView->GetEditCtrl();
	const TCHAR *pszTargetText = 0;
	int iTotalTextLen = pView->GetWindowTextLength ();
	const TCHAR *pszTextToFind = m_strFind;
	const int iTextToFindLen = m_strFind.GetLength ();
	bool bFound = false;
	bool bFinished = false;
	bool bWrappedAround = false;

	EditCtrl.GetSel (iStart, iEnd);

	if (m_bSearchForward)
	{
		iStart = iEnd;
	}

	m_pszText = pView->LockBuffer ();
	pszTargetText = m_pszText + iStart;
	// Perform find operation
	bFound = FindTextHelper (iStart, pszTargetText,
		m_bSearchForward ? m_pszText + iTotalTextLen : m_pszText,
		iTotalTextLen, pszTextToFind, iTextToFindLen);

	while (!bFinished)
	{
		if (bFound)
		{
			// Calculate start and end positions
			if (m_bSearchForward)
			{
				iEnd = iStart + iTextToFindLen;
			}
			else
			{
				iEnd = iStart;
				iStart = iEnd - iTextToFindLen;
			}

			EditCtrl.SetSel (iStart, iEnd);
			bFinished = true;
		}
		else
		{
			bFinished = bWrappedAround;

			if (bFinished)
			{
				CString strCannotFindFmt;
				CString strErrMsg;

				// Could not find string
				strCannotFindFmt.LoadString (IDS_CANNOT_FIND_FMT);
				strErrMsg.Format (strCannotFindFmt, m_strFind);
				pView->DisplayErrorMsg (strErrMsg);
			}
			else
			{
				// Wrap around and continue search
				if (m_bSearchForward)
				{
					iStart = 0;
				}
				else
				{
					iStart = EditCtrl.GetWindowTextLength ();
				}

				pszTargetText = m_pszText + iStart;
				// Try to find string again
				bFound = FindTextHelper (iStart, pszTargetText,
					m_bSearchForward ? m_pszText + iTotalTextLen : m_pszText,
					iTotalTextLen, pszTextToFind, iTextToFindLen);
				bWrappedAround = true;
			}
		}
	}

	pView->UnlockBuffer ();
	m_pszText = 0;
	return bFound;
}

bool CNotepadreDoc::FindTextRE ()
{
	bool bFound = true;
	bool bFinished = false;
	bool bWrappedAround = false;
	unsigned int uiflags = m_uiMatchFlags;
	int iStart, iEnd;
	LPCTSTR pszText = 0;
	boost::match_results<TString::const_iterator> matches;
	CNotepadreView *pView = static_cast <CNotepadreView *>
		(m_viewList.GetHead());
	CEdit &EditCtrl = pView->GetEditCtrl();

	EditCtrl.GetSel (iStart, iEnd);
	pszText = pView->LockBuffer ();

	if (pszText[iEnd] == 0)
	{
		bFound = false;
	}
	else
	{
		if (iStart == iEnd)
		{
			TCHAR c = pszText[iEnd];

			// Don't re-match beginning of word
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
				(c >= '0' && c <= '9') || c == '_' || c == 'ç' ||
				c == 'è' || c == 'ü' || c == 'é' ||
				c == 'ö' || c == 'à' || c == 'ä')
			{
				uiflags |= boost::match_not_bow;
			}

			// Don't re-match beginning or end of line
			if (c == '\r')
			{
				iEnd++;

				if (pszText[iEnd] == '\n')
				{
					iEnd++;
				}
			}
			else
			{
				uiflags |= boost::match_not_bol;
			}
		}
		else if (iEnd > 0 && pszText[iEnd - 1] != '\n')
		{
			// We are definitely not at the beginning of a line!
			uiflags |= boost::match_not_bol;
		}

		bFound = boost::regex_search (&pszText[iEnd], matches, m_regex,
			uiflags);
	}

	while (!bFinished)
	{
		if (bFound)
		{
			int iOldStart = iEnd;
			int iLine, iLineIndex;
			TCHAR *pcCR = 0;
			TCHAR c;

			// Keep a local copy of the match
			// in case the text is changed before the
			// next Replace.
			iStart = matches[0].first - pszText;
			iEnd = matches[0].second - pszText;
			pcCR = _tcschr (&pszText[iEnd], '\n');

			if (pcCR)
			{
				pcCR++;
				c = *pcCR;
				*pcCR = 0;
			}

			iLine = EditCtrl.LineFromChar (iOldStart);
			iLineIndex = EditCtrl.LineIndex (iLine);
			m_strMatchLine = &pszText[iLineIndex];

			if (pcCR)
			{
				*pcCR = c;
			}

			bFound = boost::regex_search (&m_strMatchLine[iOldStart -
				iLineIndex], m_line_matches, m_regex, uiflags);
			bFinished = true;
		}
		else
		{
			bFinished = bWrappedAround;

			if (bFinished)
			{
				CString strCannotFindFmt;
				CString strErrMsg;

				m_strMatchLine.erase ();
				strCannotFindFmt.LoadString (IDS_CANNOT_FIND_FMT);
				strErrMsg.Format (strCannotFindFmt, m_regex.str ().c_str ());
				pView->DisplayErrorMsg (strErrMsg);
			}
			else
			{
				uiflags = m_uiMatchFlags;
				iStart = iEnd = 0;
				bFound = boost::regex_search (pszText, matches, m_regex,
					uiflags);
				bWrappedAround = true;
			}
		}
	}

	pView->UnlockBuffer ();

	if (bFound)
	{
		// Only set the selection after '\n'
		// has been re-inserted
		EditCtrl.SetSel (iStart, iEnd);
	}

	return bFound;
}

void CNotepadreDoc::OnNotifyFindReplace (WPARAM wParam, LPARAM lParam)
{
	if (wParam == eWholeWordOnly)
	{
		m_bWholeWordOnly = lParam != 0;
	}
	else if (wParam == eMatchCase)
	{
		m_bMatchCase = lParam != 0;
	}
	else if (wParam == eRegEx)
	{
		m_bRegEx = lParam != 0;
		// Whether m_bRegEx is set or not
		// the current string has not been compiled
		m_bCompiled = false;
	}
	else if (wParam == eReplaceAllLikeNotepad)
	{
		m_bReplaceAllLikeNotepad = lParam != 0;
	}
	else if (wParam == eUp)
	{
		m_bSearchForward = false;
	}
	else if (wParam == eDown)
	{
		m_bSearchForward = true;
	}
	else if (wParam == eCloseOnMatch)
	{
		m_bCloseOnMatch = lParam != 0;
	}
	else if (wParam == eFind)
	{
		CFindReplaceDlg *pDlg = reinterpret_cast<CFindReplaceDlg *> (lParam);

		m_strFind = pDlg->GetFindText ();

		if (OnFindNext () && pDlg->GetIDD () == IDD_FIND &&
			m_bCloseOnMatch)
		{
			static_cast<CMainFrame *> (AfxGetMainWnd ())->
				ShowControlBar (pDlg, FALSE, FALSE);
		}
	}
	else if (wParam == eReplace)
	{
		if (!m_bReadOnly)
		{
			CFindReplaceDlg *pDlg = reinterpret_cast<CFindReplaceDlg *> (lParam);

			m_strFind = pDlg->GetFindText ();
			m_strReplace = pDlg->GetReplaceText ();
			OnReplaceSel ();
		}
	}
	else if (wParam == eReplaceAll)
	{
		if (!m_bReadOnly)
		{
			CFindReplaceDlg *pDlg = reinterpret_cast<CFindReplaceDlg *> (lParam);

			m_strFind = pDlg->GetFindText ();
			m_strReplace = pDlg->GetReplaceText ();
			OnReplaceAll ();
		}
	}
	else if (wParam == eHelp)
	{
		AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_HELP_REGEX, 0);
	}
	else
	{
		ASSERT (FALSE);
	}
}

bool CNotepadreDoc::GetScrollToEnd () const
{
	return m_bScrollToEnd;
}

void CNotepadreDoc::ToggleScrollToEnd ()
{
	m_bScrollToEnd ^= 1;
}

bool CNotepadreDoc::GetFileChangeNotify () const
{
	return m_bFileChangeNotify;
}

void CNotepadreDoc::ToggleFileChangeNotify ()
{
	m_bFileChangeNotify = !m_bFileChangeNotify;

	if (m_bFileChangeNotify)
	{
		StartFileChangeNotification (GetPathName ());
	}
	else
	{
		StopFileChangeNotification ();
		m_bAutoReload = false;
	}
}

bool CNotepadreDoc::GetAutoReload () const
{
	return m_bAutoReload;
}

void CNotepadreDoc::ToggleAutoReload ()
{
	m_bAutoReload = !m_bAutoReload;
}

void CNotepadreDoc::OnCloseDocument()
{
	HKEY hKey = 0;
	CString strNotepadreRegKey;
	LONG lRet = 0;

	strNotepadreRegKey.LoadString (IDS_NOTEPADRE_REG_KEY);
	lRet = ::RegCreateKey (HKEY_CURRENT_USER, strNotepadreRegKey, &hKey);

	if (lRet == ERROR_SUCCESS)
	{
		CString strEntry;
		DWORD dwType = REG_DWORD;
		ULONG ulSize = sizeof (REG_DWORD);
		DWORD dwRegEx = m_bRegEx;
		DWORD dwScrollToEnd = m_bScrollToEnd;
		DWORD dwFileChangeNotify = m_bFileChangeNotify;
		DWORD dwAutoReload = m_bAutoReload;

		DWORD dwescape_in_lists =
			(m_tSyntax & boost::regbase::escape_in_lists) != 0;
		DWORD dwchar_classes = (m_tSyntax & boost::regbase::char_classes) != 0;
		DWORD dwintervals = (m_tSyntax & boost::regbase::intervals) != 0;
		DWORD dwlimited_ops = (m_tSyntax & boost::regbase::limited_ops) != 0;
		DWORD dwnewline_alt = (m_tSyntax & boost::regbase::newline_alt) != 0;
		DWORD dwbk_plus_qm = (m_tSyntax & boost::regbase::bk_plus_qm) != 0;
		DWORD dwbk_braces = (m_tSyntax & boost::regbase::bk_braces) != 0;
		DWORD dwbk_parens = (m_tSyntax & boost::regbase::bk_parens) != 0;
		DWORD dwbk_refs = (m_tSyntax & boost::regbase::bk_refs) != 0;
		DWORD dwbk_vbar = (m_tSyntax & boost::regbase::bk_vbar) != 0;
		DWORD dwliteral = (m_tSyntax & boost::regbase::literal) != 0;
		DWORD dwcollate = (m_tSyntax & boost::regbase::collate) != 0;
		DWORD dwperlex = (m_tSyntax & boost::regbase::perlex) != 0;
		DWORD dwnosubs = (m_tSyntax & boost::regbase::nosubs) != 0;

		DWORD dwmatch_not_dot_newline =
			(m_uiMatchFlags & boost::match_not_dot_newline) != 0;
		DWORD dwmatch_not_dot_null =
			(m_uiMatchFlags & boost::match_not_dot_null) != 0;
		DWORD dwmatch_any = (m_uiMatchFlags & boost::match_any) != 0;
		DWORD dwmatch_not_null = (m_uiMatchFlags & boost::match_not_null) != 0;
		DWORD dwmatch_continuous =
			(m_uiMatchFlags & boost::match_continuous) != 0;
		DWORD dwmatch_extra = (m_uiMatchFlags & boost::match_extra) != 0;
		DWORD dwmatch_single_line =
			(m_uiMatchFlags & boost::match_single_line) != 0;
		DWORD dwformat_perl = (m_uiMatchFlags & boost::format_perl) != 0;
		DWORD dwformat_sed = (m_uiMatchFlags & boost::format_sed) != 0;
		DWORD dwformat_all = (m_uiMatchFlags & boost::format_all) != 0;
		DWORD dwformat_first_only =
			(m_uiMatchFlags & boost::format_first_only) != 0;

		strEntry.LoadString (IDS_REG_EX);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwRegEx, ulSize);
		strEntry.LoadString (IDS_SCROLL_TO_END);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwScrollToEnd, ulSize);
		strEntry.LoadString (IDS_FILE_CHANGE_NOTIFY);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwFileChangeNotify, ulSize);
		strEntry.LoadString (IDS_AUTO_RELOAD);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwAutoReload, ulSize);

		strEntry.LoadString (IDS_ESCAPE_IN_LISTS);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwescape_in_lists, ulSize);
		strEntry.LoadString (IDS_CHAR_CLASSES);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwchar_classes, ulSize);
		strEntry.LoadString (IDS_INTERVALS);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwintervals, ulSize);
		strEntry.LoadString (IDS_LIMITED_OPS);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwlimited_ops, ulSize);
		strEntry.LoadString (IDS_NEWLINE_ALT);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwnewline_alt, ulSize);
		strEntry.LoadString (IDS_BK_PLUS_QM);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwbk_plus_qm, ulSize);
		strEntry.LoadString (IDS_BK_BRACES);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwbk_braces, ulSize);
		strEntry.LoadString (IDS_BK_PARENS);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwbk_parens, ulSize);
		strEntry.LoadString (IDS_BK_REFS);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwbk_refs, ulSize);
		strEntry.LoadString (IDS_BK_VBAR);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwbk_vbar, ulSize);
		strEntry.LoadString (IDS_LITERAL);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwliteral, ulSize);
		strEntry.LoadString (IDS_COLLATE);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwcollate, ulSize);
		strEntry.LoadString (IDS_PERLEX);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwperlex, ulSize);
		strEntry.LoadString (IDS_NOSUBS);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwnosubs, ulSize);

		strEntry.LoadString (IDS_MATCH_NOT_DOT_NEWLINE);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwmatch_not_dot_newline, ulSize);
		strEntry.LoadString (IDS_MATCH_NOT_DOT_NULL);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwmatch_not_dot_null, ulSize);
		strEntry.LoadString (IDS_MATCH_ANY);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwmatch_any, ulSize);
		strEntry.LoadString (IDS_MATCH_NOT_NULL);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwmatch_not_null, ulSize);
		strEntry.LoadString (IDS_MATCH_CONTINUOUS);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwmatch_continuous, ulSize);
		strEntry.LoadString (IDS_MATCH_EXTRA);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwmatch_extra, ulSize);
		strEntry.LoadString (IDS_MATCH_SINGLE_LINE);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwmatch_single_line, ulSize);
		strEntry.LoadString (IDS_FORMAT_PERL);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwformat_perl, ulSize);
		strEntry.LoadString (IDS_FORMAT_SED);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwformat_sed, ulSize);
		strEntry.LoadString (IDS_FORMAT_ALL);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwformat_all, ulSize);
		strEntry.LoadString (IDS_FORMAT_FIRST_ONLY);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwformat_first_only, ulSize);
		::RegCloseKey (hKey);
	}

	if (m_bFileChangeNotify)
	{
		StopFileChangeNotification ();
	}

	CDocument::OnCloseDocument();
}

BOOL CNotepadreDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CNotepadreView *pView = ((CNotepadreView *)m_viewList.GetHead ());

	pView->SetWindowText (NULL);

	if (m_bFileChangeNotify)
	{
		StopFileChangeNotification ();
	}

	if (m_bReadOnly)
	{
		pView->ToggleReadOnly ();
	}

	m_eFileType = CNotepadreFile::eANSI;
	m_eFileFormat = CNotepadreFile::eWindows;

	// (SDI documents will reuse this document)
	return TRUE;
}

BOOL CNotepadreDoc::OnOpenDocument (LPCTSTR lpszPathName)
{
	BOOL bRet = TRUE;
	CNotepadreView *pView = static_cast <CNotepadreView *>
		(m_viewList.GetHead());
	DWORD dwChars = 0;

	if (m_bFileChangeNotify)
	{
		StopFileChangeNotification ();
	}

	// Throws an exception if there is a problem
	TRY
	{
		CFile File (lpszPathName, CFile::modeRead | CFile::shareDenyNone);

		LoadText (&File, dwChars, pView);
		SetModifiedFlag (FALSE);

		// Check if start of file starts with ".LOG"
		if (dwChars > 3)
		{
			TCHAR szHeader[4 + 1] = _T("");
			CString strDotLog;

			m_pszText = pView->LockBuffer ();
			_tcsncpy (szHeader, m_pszText, 4);
			szHeader[4] = 0;
			pView->UnlockBuffer ();
			m_pszText = 0;
			strDotLog.LoadString (IDS_DOT_LOG);

			if (_tcscmp (strDotLog, szHeader) == 0)
			{
				pView->GetEditCtrl ().SetSel (dwChars, dwChars, FALSE);
				pView->InsertTimeDate (true);
			}
		}

		pView->Invalidate ();
		// File loaded, so flags can be safely set
		m_eFileType = m_eRequestedFileType;
		m_eFileFormat = m_eRequestedFileFormat;

		if (m_bScrollToEnd)
		{
			// Re-calculate in case ".LOG" was at start of file
			int iLen = pView->GetWindowTextLength ();

			pView->GetEditCtrl ().SetSel (iLen, iLen);
		}
	}
	CATCH_ALL(e)
	{
		TRY
		{
			ReportSaveLoadException (lpszPathName, e,
				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		}
		END_TRY

		bRet = FALSE;
	}
	END_CATCH_ALL

	if (m_bFileChangeNotify)
	{
		if (bRet)
		{
			StartFileChangeNotification (lpszPathName);
		}
		else
		{
			StartFileChangeNotification (GetPathName ());
		}
	}

	return bRet;
}

BOOL CNotepadreDoc::OnSaveDocument (LPCTSTR lpszPathName)
{
	CNotepadreView *pView = static_cast <CNotepadreView *>
		(m_viewList.GetHead());
	LPCTSTR lpszText = pView->LockBuffer ();
	const UINT nLen = pView->GetBufferLength ();

	if (m_bFileChangeNotify)
	{
		StopFileChangeNotification ();
	}

	TRY
	{
		CFile File (lpszPathName, CFile::modeCreate | CFile::modeWrite);

		if (pView->IsWordWrapEnabled ())
			pView->GetEditCtrl ().FmtLines (FALSE);

		CNotepadreFile::Save (lpszText, nLen, m_eRequestedFileType,
			m_eRequestedFileFormat, &File);

		if (pView->IsWordWrapEnabled ())
			pView->GetEditCtrl ().FmtLines (TRUE);

		SetModifiedFlag (FALSE);
	}
	CATCH_ALL(e)
	{
		pView->UnlockBuffer ();

		if (m_bFileChangeNotify)
		{
			StartFileChangeNotification (GetPathName ());
		}

		THROW_LAST ();
	}
	END_CATCH_ALL

	pView->UnlockBuffer ();
	m_eFileType = m_eRequestedFileType;
	m_eFileFormat = m_eRequestedFileFormat;

	if (m_bFileChangeNotify)
	{
		StartFileChangeNotification (lpszPathName);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadreDoc diagnostics

#ifdef _DEBUG
void CNotepadreDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNotepadreDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CNotepadreDoc::LoadText (CFile *pFile, DWORD &dwChars, CEditView *pView)
{
	LPVOID hText = 0;
	LPTSTR pszText = 0;

	m_eRequestedFileType = CNotepadreFile::eAutoFileType;
	m_eRequestedFileFormat = CNotepadreFile::eAutoFileFormat;

	hText = CNotepadreFile::Load (pFile, m_eRequestedFileType,
		m_eRequestedFileFormat);

	HLOCAL hOldText = pView->GetEditCtrl ().GetHandle ();

	ASSERT (hOldText != NULL);
	::LocalFree (hOldText);
	pView->GetEditCtrl ().SetHandle ((HLOCAL)(UINT)(DWORD)hText);

}

bool CNotepadreDoc::OnFindNext ()
{
	bool bSuccess = false;

	if (m_bRegEx)
	{
		if (CompileRegEx ())
		{
			CWaitCursor wait;

			try
			{
				bSuccess = FindTextRE ();
			}
			catch (std::runtime_error &e)
			{
				CNotepadreView *pView = static_cast <CNotepadreView *>
					(m_viewList.GetHead());
				CString strErrorMsg = e.what ();

				bSuccess = false;
				// Clean up
				pView->UnlockBuffer ();
				// Display error
				pView->DisplayErrorMsg (strErrorMsg);
			}
		}
	}
	else
	{
		CWaitCursor wait;

		bSuccess = FindText ();
	}

	return bSuccess;
}

bool CNotepadreDoc::CompileRegEx ()
{
	bool bSuccess = true;

	try
	{
		boost::regbase::flag_type tflags = m_tSyntax;

		if (!m_bMatchCase)
		{
			tflags |= boost::regbase::icase;
		}

		m_regex.assign (m_strFind, tflags);
		m_bCompiled = true;
	}
	catch (boost::bad_expression &be)
	{
		CNotepadreView *pView = static_cast <CNotepadreView *>
			(m_viewList.GetHead());
		CString strErrorMsg = be.what ();

		bSuccess = false;
		m_bCompiled = false;
		pView->DisplayErrorMsg (strErrorMsg);
	}

	return bSuccess;
}

bool CNotepadreDoc::FindTextHelper (int &iStart, const TCHAR *pszTextStart,
	const TCHAR *pszTextEnd, const int iTotalTextLen, const TCHAR *pszTextToFind,
	const int iTextToFindLen)
{
	bool bFound = false;
	const TCHAR *pszMatchCandidate = 0;

	do
	{
		if (m_bSearchForward)
		{
			if (m_bMatchCase)
			{
				pszMatchCandidate = std::search (pszTextStart, pszTextEnd,
					pszTextToFind, pszTextToFind + iTextToFindLen);
			}
			else
			{
				pszMatchCandidate = std::search (pszTextStart, pszTextEnd,
					pszTextToFind, pszTextToFind + iTextToFindLen,
					std::equal_to_no_case<TCHAR> ());
			}

			bFound = pszMatchCandidate < pszTextEnd;
		}
		else
		{
			Treverse_iterator Iter;

			if (m_bMatchCase)
			{
				Iter = std::search (Treverse_iterator (pszTextStart),
					Treverse_iterator (pszTextEnd),
					Treverse_iterator (pszTextToFind + iTextToFindLen),
					Treverse_iterator (pszTextToFind));
			}
			else
			{
				Iter = std::search (Treverse_iterator (pszTextStart),
					Treverse_iterator (pszTextEnd),
					Treverse_iterator (pszTextToFind + iTextToFindLen),
					Treverse_iterator (pszTextToFind),
					std::equal_to_no_case<TCHAR> ());
			}

			pszMatchCandidate = Iter.base ();
			bFound = pszMatchCandidate > pszTextEnd;
		}

		int iOffSet = pszMatchCandidate - pszTextStart;

		iStart += iOffSet;

		if (bFound && m_bWholeWordOnly)
		{
			const TCHAR *pszBefore = m_bSearchForward ? pszMatchCandidate - 1 :
				pszMatchCandidate - iTextToFindLen - 1;
			const TCHAR *pszAfter = pszBefore + iTextToFindLen + 1;
			bool bAtStart = pszBefore < m_pszText ||
				!_tcschr (m_strValidChars, *pszBefore);
			bool bAtEnd = (pszAfter == m_pszText + iTotalTextLen) ||
				!_tcschr (m_strValidChars, *pszAfter);

			bFound = bAtStart && bAtEnd;

			if (!bFound)
			{
				pszTextStart += iOffSet + (m_bSearchForward ? iTextToFindLen :
					-iTextToFindLen);
				iStart += (m_bSearchForward ? iTextToFindLen : -iTextToFindLen);
			}
		}
	} while (!bFound && m_bWholeWordOnly &&
		(m_bSearchForward ? iStart < iTotalTextLen :
		iStart > 0));

	return bFound;
}

void CNotepadreDoc::replace_postprocess (TString &strReplaceText,
	const boost::match_results<const TCHAR *> &matches, const int iIndex)
{
	size_t pos = strReplaceText.find (_T("$"));

	while (pos != TString::npos)
	{
		TCHAR cCmd = strReplaceText[pos + 1];
		CString str = _T("$");

		if (cCmd == '=')
		{
			const TCHAR *pszStart = m_pszText;
			const TCHAR *pszEnd = m_pszText + iIndex;
			int iLine = 1;

			while (pszStart < pszEnd)
			{
				if (*pszStart == '\n') iLine++;

				pszStart++;
			}

			str.Format (_T("%d"), iLine);
			strReplaceText.replace (pos, 2, str);
		}
		else if (cCmd == 'd' || cCmd == 'i' || cCmd == 'u' ||
			cCmd == 'l')
		{
			TCHAR c = strReplaceText[pos + 2];

			if (c >= '0' && c <= '9')
			{
				int i = c - '0';

				if (i < matches.size ())
				{
					str = matches[i].str ().c_str ();

					switch (cCmd)
					{
						case 'd':
						{
							int i = _tcstoi (str);

							i--;
							str.Format (_T("%d"), i);
							break;
						}
						case 'i':
						{
							int i = _tcstoi (str);

							i++;
							str.Format (_T("%d"), i);
							break;
						}
						case 'l':
							str.MakeLower ();
							break;
						case 'u':
							str.MakeUpper ();
							break;
					}

					strReplaceText.replace (pos, 3, str);
				}
			}
		}

		pos += str.GetLength ();
		pos = strReplaceText.find (_T("$"), pos);
	}
}

void CNotepadreDoc::OnReplaceSel()
{
	bool bValidExpression = true;
	CEditView *pView = static_cast <CEditView *>
		(m_viewList.GetHead());
	CEdit &EditCtrl = pView->GetEditCtrl();

	// NOTE: If we're doing a regex search, then we don't know if a match has
	// occured or not, as the user is free to move the cursor then
	// press Replace.  If the regex includes a '^' or '$', it might be that
	// we have matched, but no text is selected, so we have no choice but to
	// perform the Replace regardless.
	// If on the other hand it's a non-regex search (i.e. like notepad), then
	// we can rely on text being selected as proof of a match...
	if (m_bRegEx)
	{
		bValidExpression = CompileRegEx ();

		if (bValidExpression)
		{
			try
			{
				TString strReplaceText = m_line_matches.
					format (static_cast<const TCHAR *> (m_strReplace),
					m_uiMatchFlags);
				int iStart = -1;
				int iEnd = -1;


				EditCtrl.GetSel (iStart, iEnd);
				m_pszText = pView->LockBuffer ();
				replace_postprocess (strReplaceText, m_line_matches, iStart);
				pView->UnlockBuffer ();
				m_pszText = 0;
				EditCtrl.ReplaceSel (strReplaceText.c_str (), TRUE);
			}
			catch (std::runtime_error &e)
			{
				CNotepadreView *pView = static_cast <CNotepadreView *>
					(m_viewList.GetHead());
				CString strErrorMsg = e.what ();

				bValidExpression = false;
				pView->DisplayErrorMsg (strErrorMsg);
			}
		}
	}
	else
	{
		int iStart = 0, iEnd = 0;

		pView->GetEditCtrl ().GetSel (iStart, iEnd);

		if (iStart != iEnd)
		{
			EditCtrl.ReplaceSel (m_strReplace, TRUE);
		}
	}

	if (bValidExpression)
	{
		OnFindNext ();
	}
}

void CNotepadreDoc::AppendToBuffer (const TCHAR *pszText, const ULONG ulTextLen)
{
	ULONG ulBufferSize = m_strBuffer.capacity ();
	ULONG ulNeededLen = m_strBuffer.size () + ulTextLen;

	if (ulNeededLen > ulBufferSize)
	{
		do
		{
			ulBufferSize += m_ulBufferIncrement;
		}
		while (ulBufferSize < ulNeededLen);

		m_strBuffer.reserve (ulBufferSize + 1);
	}

	m_strBuffer.append (pszText, ulTextLen);
}

bool CNotepadreDoc::regex_callback (const boost::match_results<const TCHAR *> &matches)
{
	// Replacement text
	m_strReplaceText = matches.format (m_lpszReplace, m_uiMatchFlags);
	replace_postprocess (m_strReplaceText, matches,
		matches[0].first - m_pszText);

	if (m_bReplaceAllLikeNotepad)
	{
		SReplacement Replacement;

		Replacement.m_iStart = matches[0].first - m_pszText;
		Replacement.m_iEnd = matches[0].second - m_pszText;
		Replacement.m_strText = m_strReplaceText;
		m_ReplacementStack.push (Replacement);
	}
	else
	{
		// Text before match
		AppendToBuffer (&m_pszText[m_ulTextIndex], 	matches[0].first - m_pszText -
			m_ulTextIndex);
		// Append replacement text
		AppendToBuffer (m_strReplaceText.c_str (), m_strReplaceText.size ());
		// Move text index to char after match
		m_ulTextIndex = matches[0].second - m_pszText;
	}

	return true;
}

void CNotepadreDoc::ReplaceAllHelper (const int iTextLen)
{
	int iStart = 0, iEnd = 0;
	const TCHAR *pszTargetText = m_pszText;
	const TCHAR *pszEndOfText = m_pszText + iTextLen;
	const TCHAR *pszTextToFind = m_strFind;
	const int iTextToFindLen = m_strFind.GetLength ();
	bool bSearchForward = m_bSearchForward;

	m_bSearchForward = true;

	while (FindTextHelper (iStart, pszTargetText, pszEndOfText, iTextLen,
		pszTextToFind, iTextToFindLen))
	{
		iEnd = iStart + iTextToFindLen;

		if (m_bReplaceAllLikeNotepad)
		{
			SReplacement Replacement;

			Replacement.m_iStart = iStart;
			Replacement.m_iEnd = iEnd;
			// Replacement text always the same in this case, so no need to store it.
			m_ReplacementStack.push (Replacement);
		}
		else
		{
			// Text before match
			AppendToBuffer (&m_pszText[m_ulTextIndex], iStart - m_ulTextIndex);
			// Append replacement text
			AppendToBuffer (m_strReplace, m_strReplace.GetLength ());
		}

		iStart = iEnd;
		// Move text index to char after match
		m_ulTextIndex = iStart;
		pszTargetText = m_pszText + m_ulTextIndex;
	}

	m_bSearchForward = bSearchForward;
}

void CNotepadreDoc::ReplaceAll ()
{
	bool bSuccess = true;
	CEditView *pView = static_cast <CEditView *> (m_viewList.GetHead());
	CEdit &EditCtrl = pView->GetEditCtrl();
	const int iTextLen = pView->GetWindowTextLength ();

	// Ensure replacement stack is empty
	while (m_ReplacementStack.size ()) m_ReplacementStack.pop ();

	if (!m_bReplaceAllLikeNotepad)
	{
		m_strBuffer.reserve (m_ulBufferIncrement + 1);
	}

	// Optimisation: Buffer increment 10% of text size
	m_ulBufferIncrement = (iTextLen / 10) > 1024 ? (iTextLen / 10) : 1024;

	m_pszText = pView->LockBuffer ();
	m_ulTextIndex = 0;

	if (m_bRegEx)
	{
		try
		{
			boost::regex_iterator<const TCHAR *> m1 (m_pszText, m_pszText +
				iTextLen, m_regex, m_uiMatchFlags);
			boost::regex_iterator<const TCHAR *> m2;

			m_lpszReplace = m_strReplace;
			std::for_each (m1, m2, &regex_callback);
		}
		catch (std::runtime_error &e)
		{
			CNotepadreView *pView = static_cast <CNotepadreView *>
				(m_viewList.GetHead());
			CString strErrorMsg = e.what ();

			bSuccess = false;
			pView->DisplayErrorMsg (strErrorMsg);
		}
	}
	else
	{
		ReplaceAllHelper (iTextLen);
	}

	if (bSuccess && !m_bReplaceAllLikeNotepad)
	{
		// Text after match
		AppendToBuffer (&m_pszText[m_ulTextIndex], iTextLen - m_ulTextIndex);
	}

	// Unlock buffer before selecting/replacing text
	pView->UnlockBuffer ();

	if (bSuccess)
	{
		if (m_bReplaceAllLikeNotepad)
		{
			SReplacement Replacement;

			while (m_ReplacementStack.size ())
			{
				Replacement = m_ReplacementStack.top ();
				EditCtrl.SetSel (Replacement.m_iStart, Replacement.m_iEnd);

				// Can't Undo Replace All..!
				if (m_bRegEx)
				{
					EditCtrl.ReplaceSel (Replacement.m_strText.c_str ());
				}
				else
				{
					EditCtrl.ReplaceSel (m_strReplace);
				}

				m_ReplacementStack.pop ();
			}
		}
		else
		{
			// Replace text
			// (do it this way so that the document is marked
			// as in need of a save)
			EditCtrl.SetSel (0, -1);
			// Can't Undo Replace All..!
			EditCtrl.ReplaceSel (m_strBuffer.c_str ());
		}
	}
	else
	{
		while (m_ReplacementStack.size ())
		{
			m_ReplacementStack.pop ();
		}
	}

	m_strBuffer.erase ();
	m_pszText = 0;
}

void CNotepadreDoc::OnReplaceAll()
{
	CWaitCursor wait;

	if (m_bRegEx)
	{
		if (CompileRegEx ())
		{
			ReplaceAll ();
		}
	}
	else
	{
		ReplaceAll ();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNotepadreDoc commands

void CNotepadreDoc::OnOptionsRegexSyntax ()
{
	CEditView *pView = static_cast <CEditView *> (m_viewList.GetHead());
	CRegexSyntaxDlg Dlg (m_tSyntax, m_uiMatchFlags, pView);

	if (Dlg.DoModal () == IDOK)
	{
		m_tSyntax = Dlg.m_tSyntax;
		m_uiMatchFlags = Dlg.m_uiMatchFlags;

		// Only re-compile (with new flags) if a successfully compiled
		// regex is present
		if (m_bRegEx && m_bCompiled)
		{
			CompileRegEx ();
		}
	}
}
