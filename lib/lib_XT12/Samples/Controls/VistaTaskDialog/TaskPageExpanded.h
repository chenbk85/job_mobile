#if !defined(AFX_TASKPAGEEXPANDED_H__8144BA9B_1833_4CF3_BB89_6D0777B408EC__INCLUDED_)
#define AFX_TASKPAGEEXPANDED_H__8144BA9B_1833_4CF3_BB89_6D0777B408EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TaskPageExpanded.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTaskPageExpanded dialog

class CTaskSheetProperties;
class CTaskPageExpanded : public CPropertyPage
{
	DECLARE_DYNCREATE(CTaskPageExpanded)

public:
	CTaskPageExpanded();
	~CTaskPageExpanded();

	//{{AFX_DATA(CTaskPageExpanded)
	enum { IDD = IDD_TASKDIALOG_EXPANDED };
	BOOL	m_bByDefault;
	BOOL	m_bFooterArea;
	CString	m_strCollapsedControlText;
	CString	m_strExpandedControlText;
	CString	m_strExpandedInformation;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTaskPageExpanded)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:
	CTaskSheetProperties* m_pDlgParent;

	//{{AFX_MSG(CTaskPageExpanded)
	afx_msg void OnUpdateData();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKPAGEEXPANDED_H__8144BA9B_1833_4CF3_BB89_6D0777B408EC__INCLUDED_)
