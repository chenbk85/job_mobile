#ifndef MYPAGESETUPDLG_H
#define MYPAGESETUPDLG_H

class CMyPageSetupDlg : public CPageSetupDialog
{
public:
	CMyPageSetupDlg (const CString &strHeader, const CString &strFooter,
		DWORD dwFlags = PSD_MARGINS | PSD_INWININIINTLMEASURE,
		CWnd* pParentWnd = NULL);
	void GetHeader (CString &strHeader);
	void GetFooter (CString &strFooter);

protected:
	//{{AFX_MSG(CMyPageSetupDlg)
	virtual BOOL OnInitDialog ();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnDestroy ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strHeader;
	CString m_strFooter;
	CEdit m_EditHeader;
	CEdit m_EditFooter;
};

#endif
