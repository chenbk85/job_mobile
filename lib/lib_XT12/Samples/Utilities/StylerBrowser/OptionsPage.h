#if !defined(AFX_OPTIONSPAGE_H__2723E5A8_844C_4E27_B808_E375A6BEF1AD__INCLUDED_)
#define AFX_OPTIONSPAGE_H__2723E5A8_844C_4E27_B808_E375A6BEF1AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsPage dialog

class COptionsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsPage)

// Construction
public:
	COptionsPage(UINT nIDTemplate = 0);
	~COptionsPage();

// Dialog Data
	//{{AFX_DATA(COptionsPage)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA
	CString m_strTitle;
	

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

void ConvertMenuItem(CString &strTitle);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSPAGE_H__2723E5A8_844C_4E27_B808_E375A6BEF1AD__INCLUDED_)
