// RegexSyntaxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "notepadre.h"
#include "RegexSyntaxDlg.h"

#include <htmlhelp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegexSyntaxDlg dialog


CRegexSyntaxDlg::CRegexSyntaxDlg (const boost::regbase::flag_type tSyntax,
	const unsigned int uiMatchFlags, CWnd* pParent /*=NULL*/)
	: CDialog (CRegexSyntaxDlg::IDD, pParent),
	m_tSyntax (tSyntax),
	m_uiMatchFlags (uiMatchFlags)
{
	int iSyntax = 0;

	if ((m_tSyntax & boost::regbase::perl) == boost::regbase::perl)
	{
		iSyntax = 3;
	}
	else if ((m_tSyntax & boost::regbase::grep) == boost::regbase::grep)
	{
		iSyntax = 6;
	}
	else if ((m_tSyntax & boost::regbase::basic) == boost::regbase::basic)
	{
		iSyntax = 1;
	}
	else if ((m_tSyntax & boost::regbase::egrep) == boost::regbase::egrep)
	{
		iSyntax = 7;
	}
	else if ((m_tSyntax & boost::regbase::awk) == boost::regbase::awk)
	{
		iSyntax = 5;
	}
	else if ((m_tSyntax & boost::regbase::extended) ==
		boost::regbase::extended)
	{
		iSyntax = 2;
	}
	else if ((m_tSyntax & boost::regbase::emacs) == boost::regbase::emacs)
	{
		iSyntax = 4;
	}

	//{{AFX_DATA_INIT(CRegexSyntaxDlg)
	m_iSyntax = iSyntax;
	m_bescape_in_lists = (m_tSyntax & boost::regbase::escape_in_lists) != 0;
	m_bchar_classes = (m_tSyntax & boost::regbase::char_classes) != 0;
	m_bintervals = (m_tSyntax & boost::regbase::intervals) != 0;
	m_blimited_ops = (m_tSyntax & boost::regbase::limited_ops) != 0;
	m_bnewline_alt = (m_tSyntax & boost::regbase::newline_alt) != 0;
	m_bbk_plus_qm = (m_tSyntax & boost::regbase::bk_plus_qm) != 0;
	m_bbk_braces = (m_tSyntax & boost::regbase::bk_braces) != 0;
	m_bbk_parens = (m_tSyntax & boost::regbase::bk_parens) != 0;
	m_bbk_refs = (m_tSyntax & boost::regbase::bk_refs) != 0;
	m_bbk_vbar = (m_tSyntax & boost::regbase::bk_vbar) != 0;
	m_bliteral = (m_tSyntax & boost::regbase::literal) != 0;
	m_bcollate = (m_tSyntax & boost::regbase::collate) != 0;
	m_bperlex = (m_tSyntax & boost::regbase::perlex) != 0;
	m_bnosubs = (m_tSyntax & boost::regbase::nosubs) != 0;
	m_bmatch_not_dot_newline = (m_uiMatchFlags & boost::regex_constants::match_not_dot_newline) != 0;
	m_bmatch_not_dot_null = (m_uiMatchFlags & boost::regex_constants::match_not_dot_null) != 0;
	m_bmatch_any = (m_uiMatchFlags & boost::regex_constants::match_any) != 0;
	m_bmatch_not_null = (m_uiMatchFlags & boost::regex_constants::match_not_null) != 0;
	m_bmatch_continuous = (m_uiMatchFlags & boost::regex_constants::match_continuous) != 0;
	m_bmatch_extra = (m_uiMatchFlags & boost::regex_constants::match_extra) != 0;
	m_bmatch_single_line = (m_uiMatchFlags & boost::regex_constants::match_single_line) != 0;
	m_bformat_perl = (m_uiMatchFlags & boost::regex_constants::format_perl) != 0;
	m_bformat_sed = (m_uiMatchFlags & boost::regex_constants::format_sed) != 0;
	m_bformat_all = (m_uiMatchFlags & boost::regex_constants::format_all) != 0;
	m_bformat_first_only = (m_uiMatchFlags & boost::regex_constants::format_first_only) != 0;
	//}}AFX_DATA_INIT
}

void CRegexSyntaxDlg::DoDataExchange (CDataExchange *pDX)
{
	CDialog::DoDataExchange (pDX);
	//{{AFX_DATA_MAP(CRegexSyntaxDlg)
	DDX_Radio(pDX, IDC_RADIO_NONE, m_iSyntax);
	DDX_Check(pDX, IDC_CHECK_ESCAPE_IN_LISTS, m_bescape_in_lists);
	DDX_Check(pDX, IDC_CHECK_CHAR_CLASSES, m_bchar_classes);
	DDX_Check(pDX, IDC_CHECK_INTERVALS, m_bintervals);
	DDX_Check(pDX, IDC_CHECK_LIMITED_OPS, m_blimited_ops);
	DDX_Check(pDX, IDC_CHECK_NEWLINE_ALT, m_bnewline_alt);
	DDX_Check(pDX, IDC_CHECK_BK_PLUS_QM, m_bbk_plus_qm);
	DDX_Check(pDX, IDC_CHECK_BK_BRACES, m_bbk_braces);
	DDX_Check(pDX, IDC_CHECK_BK_PARENS, m_bbk_parens);
	DDX_Check(pDX, IDC_CHECK_BK_REFS, m_bbk_refs);
	DDX_Check(pDX, IDC_CHECK_BK_VBAR, m_bbk_vbar);
	DDX_Check(pDX, IDC_CHECK_LITERAL, m_bliteral);
	DDX_Check(pDX, IDC_CHECK_COLLATE, m_bcollate);
	DDX_Check(pDX, IDC_CHECK_PERLEX, m_bperlex);
	DDX_Check(pDX, IDC_CHECK_NOSUBS, m_bnosubs);
	DDX_Check(pDX, IDC_CHECK_NOT_DOT_NEWLINE, m_bmatch_not_dot_newline);
	DDX_Check(pDX, IDC_CHECK_NOT_DOT_NULL, m_bmatch_not_dot_null);
	DDX_Check(pDX, IDC_CHECK_ANY, m_bmatch_any);
	DDX_Check(pDX, IDC_CHECK_NOT_NULL, m_bmatch_not_null);
	DDX_Check(pDX, IDC_CHECK_CONTINUOUS, m_bmatch_continuous);
	DDX_Check(pDX, IDC_CHECK_EXTRA, m_bmatch_extra);
	DDX_Check(pDX, IDC_CHECK_SINGLE_LINE, m_bmatch_single_line);
	DDX_Check(pDX, IDC_CHECK_PERL, m_bformat_perl);
	DDX_Check(pDX, IDC_CHECK_SED, m_bformat_sed);
	DDX_Check(pDX, IDC_CHECK_ALL, m_bformat_all);
	DDX_Check(pDX, IDC_CHECK_FIRST_ONLY, m_bformat_first_only);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegexSyntaxDlg, CDialog)
	//{{AFX_MSG_MAP(CRegexSyntaxDlg)
	ON_BN_CLICKED(IDC_RADIO_NONE, OnRadioNone)
	ON_BN_CLICKED(IDC_RADIO_BASIC_POSIX, OnRadioBasic)
	ON_BN_CLICKED(IDC_RADIO_EXTENDED_POSIX, OnRadioExtended)
	ON_BN_CLICKED(IDC_RADIO_PERL_SUBSET, OnRadioPerl)
	ON_BN_CLICKED(IDC_RADIO_EMACS, OnRadioEmacs)
	ON_BN_CLICKED(IDC_RADIO_AWK, OnRadioAwk)
	ON_BN_CLICKED(IDC_RADIO_GREP, OnRadioGrep)
	ON_BN_CLICKED(IDC_RADIO_EGREP, OnRadioEgrep)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CRegexSyntaxDlg::ClearDisabledSyntaxFlags ()
{

	if (!GetDlgItem (IDC_CHECK_ESCAPE_IN_LISTS)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_ESCAPE_IN_LISTS, FALSE);
		GetDlgItem (IDC_CHECK_ESCAPE_IN_LISTS)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_CHAR_CLASSES)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_CHAR_CLASSES, FALSE);
		GetDlgItem (IDC_CHECK_CHAR_CLASSES)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_INTERVALS)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_INTERVALS, FALSE);
		GetDlgItem (IDC_CHECK_INTERVALS)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_LIMITED_OPS)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_LIMITED_OPS, FALSE);
		GetDlgItem (IDC_CHECK_LIMITED_OPS)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_NEWLINE_ALT)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_NEWLINE_ALT, FALSE);
		GetDlgItem (IDC_CHECK_NEWLINE_ALT)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_BK_PLUS_QM)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_BK_PLUS_QM, FALSE);
		GetDlgItem (IDC_CHECK_BK_PLUS_QM)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_BK_BRACES)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_BK_BRACES, FALSE);
		GetDlgItem (IDC_CHECK_BK_BRACES)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_BK_PARENS)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_BK_PARENS, FALSE);
		GetDlgItem (IDC_CHECK_BK_PARENS)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_BK_REFS)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_BK_REFS, FALSE);
		GetDlgItem (IDC_CHECK_BK_REFS)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_BK_VBAR)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_BK_VBAR, FALSE);
		GetDlgItem (IDC_CHECK_BK_VBAR)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_COLLATE)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_COLLATE, FALSE);
		GetDlgItem (IDC_CHECK_COLLATE)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_PERLEX)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_PERLEX, FALSE);
		GetDlgItem (IDC_CHECK_PERLEX)->EnableWindow (TRUE);
	}

	if (!GetDlgItem (IDC_CHECK_NOSUBS)->IsWindowEnabled ())
	{
		CheckDlgButton (IDC_CHECK_NOSUBS, FALSE);
		GetDlgItem (IDC_CHECK_NOSUBS)->EnableWindow (TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRegexSyntaxDlg message handlers

BOOL CRegexSyntaxDlg::OnInitDialog ()
{
	CDialog::OnInitDialog ();

	if (m_iSyntax == 1)
	{
		OnRadioBasic ();
	}
	else if (m_iSyntax == 2)
	{
		OnRadioExtended ();
	}
	else if (m_iSyntax == 3)
	{
		OnRadioPerl ();
	}
	else if (m_iSyntax == 4)
	{
		OnRadioEmacs ();
	}
	else if (m_iSyntax == 5)
	{
		OnRadioAwk ();
	}
	else if (m_iSyntax == 6)
	{
		OnRadioGrep ();
	}
	else if (m_iSyntax == 7)
	{
		OnRadioEgrep ();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRegexSyntaxDlg::OnRadioNone ()
{
	// Not called by OnInitDialog, but if statement added anyway
	ClearDisabledSyntaxFlags ();
}

void CRegexSyntaxDlg::OnRadioBasic ()
{
	ClearDisabledSyntaxFlags ();

	CheckDlgButton (IDC_CHECK_CHAR_CLASSES, TRUE);
	GetDlgItem (IDC_CHECK_CHAR_CLASSES)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_INTERVALS, TRUE);
	GetDlgItem (IDC_CHECK_INTERVALS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_LIMITED_OPS, TRUE);
	GetDlgItem (IDC_CHECK_LIMITED_OPS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_BK_BRACES, TRUE);
	GetDlgItem (IDC_CHECK_BK_BRACES)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_BK_PARENS, TRUE);
	GetDlgItem (IDC_CHECK_BK_PARENS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_BK_REFS, TRUE);
	GetDlgItem (IDC_CHECK_BK_REFS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_COLLATE, TRUE);
	GetDlgItem (IDC_CHECK_COLLATE)->EnableWindow (FALSE);
}

void CRegexSyntaxDlg::OnRadioExtended ()
{
	ClearDisabledSyntaxFlags ();

	CheckDlgButton (IDC_CHECK_CHAR_CLASSES, TRUE);
	GetDlgItem (IDC_CHECK_CHAR_CLASSES)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_INTERVALS, TRUE);
	GetDlgItem (IDC_CHECK_INTERVALS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_BK_REFS, TRUE);
	GetDlgItem (IDC_CHECK_BK_REFS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_COLLATE, TRUE);
	GetDlgItem (IDC_CHECK_COLLATE)->EnableWindow (FALSE);
}

void CRegexSyntaxDlg::OnRadioPerl ()
{
	ClearDisabledSyntaxFlags ();

	CheckDlgButton (IDC_CHECK_PERLEX, TRUE);
	GetDlgItem (IDC_CHECK_PERLEX)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_ESCAPE_IN_LISTS, TRUE);
	GetDlgItem (IDC_CHECK_ESCAPE_IN_LISTS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_CHAR_CLASSES, TRUE);
	GetDlgItem (IDC_CHECK_CHAR_CLASSES)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_INTERVALS, TRUE);
	GetDlgItem (IDC_CHECK_INTERVALS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_BK_REFS, TRUE);
	GetDlgItem (IDC_CHECK_BK_REFS)->EnableWindow (FALSE);
	// nocollate depricated...
}

void CRegexSyntaxDlg::OnRadioEmacs ()
{
	ClearDisabledSyntaxFlags ();

	CheckDlgButton (IDC_CHECK_BK_BRACES, TRUE);
	GetDlgItem (IDC_CHECK_BK_BRACES)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_BK_PARENS, TRUE);
	GetDlgItem (IDC_CHECK_BK_PARENS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_BK_REFS, TRUE);
	GetDlgItem (IDC_CHECK_BK_REFS)->EnableWindow (FALSE);
	CheckDlgButton (IDC_CHECK_BK_VBAR, TRUE);
	GetDlgItem (IDC_CHECK_BK_VBAR)->EnableWindow (FALSE);
}

void CRegexSyntaxDlg::OnRadioAwk ()
{
	OnRadioExtended ();
	CheckDlgButton (IDC_CHECK_ESCAPE_IN_LISTS, TRUE);
	GetDlgItem (IDC_CHECK_ESCAPE_IN_LISTS)->EnableWindow (FALSE);
}

void CRegexSyntaxDlg::OnRadioGrep ()
{
	OnRadioBasic ();
	CheckDlgButton (IDC_CHECK_NEWLINE_ALT, TRUE);
	GetDlgItem (IDC_CHECK_NEWLINE_ALT)->EnableWindow (FALSE);
}

void CRegexSyntaxDlg::OnRadioEgrep ()
{
	OnRadioExtended ();
	CheckDlgButton (IDC_CHECK_NEWLINE_ALT, TRUE);
	GetDlgItem (IDC_CHECK_NEWLINE_ALT)->EnableWindow (FALSE);
}

void CRegexSyntaxDlg::OnOk ()
{
	CDialog::OnOK ();
	m_tSyntax = 0;

	if (m_iSyntax == 1)
	{
		m_tSyntax |= boost::regbase::basic;
	}
	else if (m_iSyntax == 2)
	{
		m_tSyntax |= boost::regbase::extended;
	}
	else if (m_iSyntax == 3)
	{
		m_tSyntax |= boost::regbase::perl;
	}
	else if (m_iSyntax == 4)
	{
		m_tSyntax |= boost::regbase::emacs;
	}
	else if (m_iSyntax == 5)
	{
		m_tSyntax |= boost::regbase::awk;
	}
	else if (m_iSyntax == 6)
	{
		m_tSyntax |= boost::regbase::grep;
	}
	else if (m_iSyntax == 7)
	{
		m_tSyntax |= boost::regbase::egrep;
	}

	if (m_bescape_in_lists) m_tSyntax |= boost::regbase::escape_in_lists;
	if (m_bchar_classes) m_tSyntax |= boost::regbase::char_classes;
	if (m_bintervals) m_tSyntax |= boost::regbase::intervals;
	if (m_blimited_ops) m_tSyntax |= boost::regbase::limited_ops;
	if (m_bnewline_alt) m_tSyntax |= boost::regbase::newline_alt;
	if (m_bbk_plus_qm) m_tSyntax |= boost::regbase::bk_plus_qm;
	if (m_bbk_braces) m_tSyntax |= boost::regbase::bk_braces;
	if (m_bbk_parens) m_tSyntax |= boost::regbase::bk_parens;
	if (m_bbk_refs) m_tSyntax |= boost::regbase::bk_refs;
	if (m_bbk_vbar) m_tSyntax |= boost::regbase::bk_vbar;
	if (m_bliteral) m_tSyntax |= boost::regbase::literal;
	if (m_bcollate) m_tSyntax |= boost::regbase::collate;
	if (m_bperlex) m_tSyntax |= boost::regbase::perlex;
	if (m_bnosubs) m_tSyntax |= boost::regbase::nosubs;

	m_uiMatchFlags = boost::match_default;

	if (m_bmatch_not_dot_newline) m_uiMatchFlags |= boost::match_not_dot_newline;
	if (m_bmatch_not_dot_null) m_uiMatchFlags |= boost::match_not_dot_null;
	if (m_bmatch_any) m_uiMatchFlags |= boost::regex_constants::match_any;
	if (m_bmatch_not_null) m_uiMatchFlags |= boost::regex_constants::match_not_null;
	if (m_bmatch_continuous) m_uiMatchFlags |= boost::match_continuous;
	if (m_bmatch_extra) m_uiMatchFlags |= boost::match_extra;
	if (m_bmatch_single_line) m_uiMatchFlags |= boost::match_single_line;
	if (m_bformat_perl) m_uiMatchFlags |= boost::format_perl;
	if (m_bformat_sed) m_uiMatchFlags |= boost::format_sed;
	if (m_bformat_all) m_uiMatchFlags |= boost::format_all;
	if (m_bformat_first_only) m_uiMatchFlags |= boost::format_first_only;
}

BOOL CRegexSyntaxDlg::OnHelpInfo (HELPINFO *pHelpInfo)
{
	BOOL bRet = TRUE;
	RECT rect;
	HH_POPUP popup;
	CString strArial8;

	switch (pHelpInfo->iCtrlId)
	{
		case IDC_RADIO_NONE :
			GetDlgItem (IDC_RADIO_NONE)->GetWindowRect (&rect);
			popup.pszText = _T("All flags editable");
			break;
		case IDC_RADIO_BASIC_POSIX :
			GetDlgItem (IDC_RADIO_BASIC_POSIX)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the grammar recognized by the")
				_T("regular expression engine is the same as that used by ")
				_T("POSIX basic regular expressions in IEEE Std 1003.1-2001,")
				_T(" Portable Operating System Interface (POSIX ), Base ")
				_T("Definitions and Headers, Section 9, Regular Expressions ")
				_T("(FWD.1).");
			break;
		case IDC_RADIO_EXTENDED_POSIX :
			GetDlgItem (IDC_RADIO_BASIC_POSIX)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the grammar recognized by the ")
				_T("regular expression engine is the same as that used by ")
				_T("POSIX extended regular expressions in IEEE Std 1003.1-2001")
				_T(", Portable Operating System Interface (POSIX ), Base ")
				_T("Definitions and Headers, Section 9, Regular Expressions ")
				_T("(FWD.1).");
			break;
		case IDC_RADIO_PERL_SUBSET :
			GetDlgItem (IDC_RADIO_PERL_SUBSET)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the grammar recognized by the ")
				_T("regular expression engine uses its normal semantics: ")
				_T("that is the same as that given in the ECMA-262, ")
				_T("ECMAScript Language Specification, Chapter 15 part 10, ")
				_T("RegExp (Regular Expression) Objects (FWD.1).  ")
				_T("Also includes the Perl5 extensions.");
			break;
		case IDC_RADIO_EMACS :
			GetDlgItem (IDC_RADIO_EMACS)->GetWindowRect (&rect);
			popup.pszText = _T("Provides compatability with the emacs ")
				_T("editor, eqivalent to: bk_braces | bk_parens | ")
				_T("bk_refs | bk_vbar.");
			break;
		case IDC_RADIO_AWK :
			GetDlgItem (IDC_RADIO_AWK)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the grammar recognized by the ")
				_T("regular expression engine is the same as that used by ")
				_T("POSIX utility awk in IEEE Std 1003.1-2001, Portable ")
				_T("Operating System Interface (POSIX ), Shells and ")
				_T("Utilities, Section 4, awk (FWD.1).");
			break;
		case IDC_RADIO_GREP :
			GetDlgItem (IDC_RADIO_GREP)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the grammar recognized by the ")
				_T("regular expression engine is the same as that used by ")
				_T("POSIX utility grep in IEEE Std 1003.1-2001, Portable ")
				_T("Operating System Interface (POSIX ), Shells and ")
				_T("Utilities, Section 4, Utilities, grep (FWD.1).");
			break;
		case IDC_RADIO_EGREP :
			GetDlgItem (IDC_RADIO_EGREP)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the grammar recognized by ")
				_T("the regular expression engine is the same as that used ")
				_T("by POSIX utility grep when given the -E option in IEEE ")
				_T("Std 1003.1-2001, Portable Operating System Interface ")
				_T("(POSIX ), Shells and Utilities, Section 4, Utilities, ")
				_T("grep (FWD.1).");
			break;
		case IDC_CHECK_ESCAPE_IN_LISTS :
			GetDlgItem (IDC_CHECK_ESCAPE_IN_LISTS)->GetWindowRect (&rect);
			popup.pszText = _T("Allows the use of the escape \"\\\" ")
				_T("character in sets of characters, for example [\\]] ")
				_T("represents the set of characters containing only \"]\"")
				_T(". If this flag is not set then \"\\\" is an ordinary ")
				_T("character inside sets.");
			break;
		case IDC_CHECK_CHAR_CLASSES :
			GetDlgItem (IDC_CHECK_CHAR_CLASSES)->GetWindowRect (&rect);
			popup.pszText = _T("When this bit is set, character classes ")
				_T("[:classname:] are allowed inside character set ")
				_T("declarations, for example \"[[:word:]]\" represents ")
				_T("the set of all characters that belong to the character ")
				_T("class \"word\".");
			break;
		case IDC_CHECK_INTERVALS :
			GetDlgItem (IDC_CHECK_INTERVALS)->GetWindowRect (&rect);
			popup.pszText = _T("When this bit is set, repetition intervals ")
				_T("are allowed, for example \"a{2,4}\" represents a repeat ")
				_T("of between 2 and 4 letter a's.");
			break;
		case IDC_CHECK_LIMITED_OPS :
			GetDlgItem (IDC_CHECK_LIMITED_OPS)->GetWindowRect (&rect);
			popup.pszText = _T("When this bit is set all of \"+\", \"?\" and ")
				_T("\"|\" are ordinary characters in all situations.");
			break;
		case IDC_CHECK_NEWLINE_ALT :
			GetDlgItem (IDC_CHECK_NEWLINE_ALT)->GetWindowRect (&rect);
			popup.pszText = _T("When this bit is set, then the newline ")
				_T("character \"\\n\" has the same effect as the alternation ")
				_T("operator \"|\".");
			break;
		case IDC_CHECK_BK_PLUS_QM :
			GetDlgItem (IDC_CHECK_BK_PLUS_QM)->GetWindowRect (&rect);
			popup.pszText = _T("When this bit is set then \"\\+\" represents ")
				_T("the one or more repetition operator and \"\\?\" ")
				_T("represents the zero or one repetition operator. When ")
				_T("this bit is not set then \"+\" and \"?\" are used instead.");
			break;
		case IDC_CHECK_BK_BRACES :
			GetDlgItem (IDC_CHECK_BK_BRACES)->GetWindowRect (&rect);
			popup.pszText = _T("When this bit is set then \"\\{\" and ")
				_T("\"\\}\" are used for bounded repetitions and \"{\" ")
				_T("and \"}\" are normal characters. This is the opposite ")
				_T("of default behavior.");
			break;
		case IDC_CHECK_BK_PARENS :
			GetDlgItem (IDC_CHECK_BK_PARENS)->GetWindowRect (&rect);
			popup.pszText = _T("When this bit is set then \"\\(\" and ")
				_T("\"\\)\" are used to group sub-expressions and \"(\" ")
				_T("and \")\" are ordinary characters, this is the opposite ")
				_T("of default behavior.");
			break;
		case IDC_CHECK_BK_REFS :
			GetDlgItem (IDC_CHECK_BK_REFS)->GetWindowRect (&rect);
			popup.pszText = _T("When this bit is set then back references ")
				_T("are allowed.");
			break;
		case IDC_CHECK_BK_VBAR :
			GetDlgItem (IDC_CHECK_BK_VBAR)->GetWindowRect (&rect);
			popup.pszText = _T("When this bit is set then \"\\|\" represents ")
				_T("the alternation operator and \"|\" is an ordinary ")
				_T("character. This is the opposite of default behavior.");
			break;
		case IDC_CHECK_LITERAL :
			GetDlgItem (IDC_CHECK_LITERAL)->GetWindowRect (&rect);
			popup.pszText = _T("All characters in the string are treated as ")
				_T("literals, there are no special characters or escape ")
				_T("sequences.");
			break;
		case IDC_CHECK_COLLATE :
			GetDlgItem (IDC_CHECK_COLLATE)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that character ranges of the form ")
				_T("\"[a-b]\" should be locale sensitive.");
			break;
		case IDC_CHECK_PERLEX :
			GetDlgItem (IDC_CHECK_PERLEX)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the Perl extensions should be ")
				_T("used.");
			break;
		case IDC_CHECK_NOSUBS :
			GetDlgItem (IDC_CHECK_NOSUBS)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that when a regular expression is ")
				_T("matched against a character container sequence, then no ")
				_T("sub-expression matches are to be stored in the supplied ")
				_T("match_results structure.");
			break;
		case IDC_CHECK_NOT_DOT_NEWLINE :
			GetDlgItem (IDC_CHECK_NOT_DOT_NEWLINE)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the expression \".\" does not ")
				_T("match a newline character.");
			break;
		case IDC_CHECK_NOT_DOT_NULL :
			GetDlgItem (IDC_CHECK_NOT_DOT_NULL)->GetWindowRect (&rect);
			popup.pszText = _T("Specified that the expression \".\" does not ")
				_T("match a character null '\0'.");
			break;
		case IDC_CHECK_ANY :
			GetDlgItem (IDC_CHECK_ANY)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that if more than one match is ")
				_T("possible then any match is an acceptable result.");
			break;
		case IDC_CHECK_NOT_NULL :
			GetDlgItem (IDC_CHECK_NOT_NULL)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the expression can not be ")
				_T("matched against an empty sequence.");
			break;
		case IDC_CHECK_CONTINUOUS :
			GetDlgItem (IDC_CHECK_CONTINUOUS)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that the expression must match a ")
				_T("sub-sequence that begins at first.");
			break;
		case IDC_CHECK_EXTRA :
			GetDlgItem (IDC_CHECK_EXTRA)->GetWindowRect (&rect);
			popup.pszText = _T("Instructs the matching engine to retain all ")
				_T("available capture information");
			break;
		case IDC_CHECK_SINGLE_LINE :
			GetDlgItem (IDC_CHECK_SINGLE_LINE)->GetWindowRect (&rect);
			popup.pszText = _T("Equivalent to Perl's s/ modifier; prevents ^ ")
				_T("from matching after an embedded newline character (so ")
				_T("that it only matches at the start of the text being ")
				_T("matched), and $ from matching before an embedded newline ")
				_T("(so that it only matches at the end of the text being ")
				_T("matched).");
			break;
		case IDC_CHECK_PERL :
			GetDlgItem (IDC_CHECK_PERL)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that when a regular expression ")
				_T("match is to be replaced by a new string, that the new ")
				_T("string is constructed using the same rules as Perl 5.");
			break;
		case IDC_CHECK_SED :
			GetDlgItem (IDC_CHECK_SED)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that when a regular expression ")
				_T("match is to be replaced by a new string, that the new ")
				_T("string is constructed using the rules used by the Unix ")
				_T("sed utility in IEEE Std 1003.1-2001, Portable Operating ")
				_T("SystemInterface (POSIX ), Shells and Utilities.");
			break;
		case IDC_CHECK_ALL :
			GetDlgItem (IDC_CHECK_ALL)->GetWindowRect (&rect);
			popup.pszText = _T("Specifies that all syntax extensions are ")
				_T("enabled, including conditional (?ddexpression1:")
				_T("expression2) replacements:");
			break;
		case IDC_CHECK_FIRST_ONLY :
			GetDlgItem (IDC_CHECK_FIRST_ONLY)->GetWindowRect (&rect);
			popup.pszText = _T("When specified during a search and replace ")
				_T("operation, then only the first occurrence of the regular ")
				_T("expression is replaced.");
			break;
		default:
			bRet = FALSE;
			ASSERT (0);
			break;
	}

	if (bRet)
	{
		popup.cbStruct = sizeof (popup);
		popup.hinst = AfxGetResourceHandle ();
		popup.idString = 0;
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
	}
	else
	{
		CDialog::OnHelpInfo (pHelpInfo);
	}

	return bRet;
}
