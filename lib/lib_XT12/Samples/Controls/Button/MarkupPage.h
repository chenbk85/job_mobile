#if !defined(AFX_MARKUPPAGE_H__B562CD82_7DEE_4D53_8D59_6DAD12D3ECAF__INCLUDED_)
#define AFX_MARKUPPAGE_H__B562CD82_7DEE_4D53_8D59_6DAD12D3ECAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkupPage.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CMarkupPage dialog

class CMarkupPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMarkupPage)

// Construction
public:
	CMarkupPage();
	~CMarkupPage();

// Dialog Data
	//{{AFX_DATA(CMarkupPage)
	enum { IDD = IDD_PAGE_MARKUPBUTTONS };
	CXTPButton	m_btnRadioWithLink;
	CXTPButton	m_btnDeleteOutbox;
	CXTPButton	m_btnDeleteInbox;
	CXTPButton	m_btnFirewall;
	CXTPButton	m_btnPushButton;
	CXTPButton	m_btnRadio;
	CXTPButton	m_btnCheckBox;
	//}}AFX_DATA

#ifdef _XTP_INCLUDE_MARKUP
	void OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);
#endif

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMarkupPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMarkupPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPPAGE_H__B562CD82_7DEE_4D53_8D59_6DAD12D3ECAF__INCLUDED_)
