// notepadreDoc.h : interface of the CNotepadreDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEPADREDOC_H__DBEAC583_9C57_49CF_8CD4_A7ABA704BE7C__INCLUDED_)
#define AFX_NOTEPADREDOC_H__DBEAC583_9C57_49CF_8CD4_A7ABA704BE7C__INCLUDED_

#include "NotepadreFile.h"

#pragma warning (disable:4786)

#include <boost/regex.hpp>
#include <stack>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _UNICODE
typedef boost::wregex CRegEx;
#else
typedef boost::regex CRegEx;
#endif

// This string type is used by the regular expression class.
typedef std::basic_string<TCHAR> TString;
typedef std::reverse_iterator<const TCHAR *, const TCHAR> Treverse_iterator;

struct SReplacement
{
	int m_iStart;
	int m_iEnd;
	TString m_strText;

	SReplacement () : m_iStart (0), m_iEnd (0) {}
};

typedef std::stack<SReplacement> TReplacementStack;

class CNotepadreDoc : public CDocument
{
protected: // create from serialization only
	CNotepadreDoc();
	DECLARE_DYNCREATE(CNotepadreDoc)

// Attributes
public:
	void CNotepadreDoc::SetReadOnly (const bool bReadOnly);
	bool CNotepadreDoc::GetReadOnly () const;
	void SetFileType (const CNotepadreFile::e_FileType eFileType,
		const CNotepadreFile::e_FileFormat eFileFormat);
	void GetFileType (CNotepadreFile::e_FileType &eFileType,
		CNotepadreFile::e_FileFormat &eFileFormat) const;
	void StartFileChangeNotification (LPCTSTR lpszPathName);
	void StopFileChangeNotification ();
	const CString &GetFindText () const;
	const CString &GetReplaceText () const;
	const bool GetWholeWordOnly () const;
	const bool GetMatchCase () const;
	const bool GetRegEx () const;
	const bool GetCompiled () const;
	const bool GetSearchForward () const;
	void SetSearchForward (const bool bSearchForward);
	const bool GetCloseOnMatch () const;
	const bool GetReplaceAllLikeNotepad () const;
	const bool NeedFind () const;
	bool FindText ();
	bool FindTextRE ();
	void OnNotifyFindReplace (WPARAM wParam, LPARAM lParam);
	bool GetScrollToEnd () const;
	void ToggleScrollToEnd ();
	bool GetFileChangeNotify () const;
	void ToggleFileChangeNotify ();
	bool GetAutoReload () const;
	void ToggleAutoReload ();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotepadreDoc)
	public:
	virtual void OnCloseDocument ();
	virtual BOOL OnNewDocument ();
	virtual BOOL OnOpenDocument (LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument (LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNotepadreDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void LoadText (CFile *pFile, DWORD &dwChars, CEditView *pView);
	bool OnFindNext ();
	bool CompileRegEx ();
	bool FindTextHelper (int &iStart, const TCHAR *pszTargetText,
		const TCHAR *pszTextEnd, const int iTotalTextLen, const TCHAR *pszTextToFind,
		const int iTextToFindLen);
	static void replace_postprocess (TString &strReplaceText,
		const boost::match_results<const TCHAR *> &matches, const int iIndex);
	void OnReplaceSel ();
	static void AppendToBuffer (const TCHAR *pszText, const ULONG ulTextLen);
	static bool regex_callback (const boost::match_results<const TCHAR *> &matches);
	void ReplaceAllHelper (const int iTextLen);
	void ReplaceAll ();
	void OnReplaceAll ();

// Generated message map functions
protected:
	//{{AFX_MSG(CNotepadreDoc)
	afx_msg void OnOptionsRegexSyntax();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	boost::regbase::flag_type m_tSyntax;
	static unsigned int m_uiMatchFlags;
	bool m_bReadOnly;
	// Current file type
	CNotepadreFile::e_FileType m_eFileType;
	CNotepadreFile::e_FileFormat m_eFileFormat;

	// These values are filled from the Save As dialog
	CNotepadreFile::e_FileType m_eRequestedFileType;
	CNotepadreFile::e_FileFormat m_eRequestedFileFormat;

	CString m_strValidChars;
	CString m_strFind;
	CString m_strReplace;
	bool m_bWholeWordOnly;
	bool m_bMatchCase;
	bool m_bRegEx;
	bool m_bCompiled;
	static bool m_bReplaceAllLikeNotepad;
	bool m_bSearchForward;
	bool m_bCloseOnMatch;
	CRegEx m_regex;
	// The last match...
	TString m_strMatchLine;
	boost::match_results<TString::const_iterator> m_line_matches;

	static TReplacementStack m_ReplacementStack;
	static TCHAR const *m_pszText;
	static ULONG m_ulTextIndex;
	static ULONG m_ulBufferIncrement;
	static TString m_strBuffer;
	static LPCTSTR m_lpszReplace;
	static TString m_strReplaceText;

	bool m_bScrollToEnd;
	bool m_bFileChangeNotify;
	bool m_bAutoReload;
	// Path and file name used for File Change Notification code
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEPADREDOC_H__DBEAC583_9C57_49CF_8CD4_A7ABA704BE7C__INCLUDED_)
