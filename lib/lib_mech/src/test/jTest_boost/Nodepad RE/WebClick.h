////////////////////////////////////////////////////////////////////////////
//
// WebClick.h : definition of the CWebClick class
//
// kishan@hackorama.com  http://www.hackorama.com
//
// Circa: Feb 1998
//
////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CWebClick window

class CWebClick : public CButton
{
// Construction
public:
	//CWebClick();
	CWebClick(TCHAR * strConnectToURL, CString szURLAnchorName);
	CWebClick(TCHAR * strEmailID, CString szMailAnchorName,CString szSubject);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebClick)

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWebClick();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWebClick)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void		SendMail();
	void		OpenURL(void);

	CString		m_szSubject;
	int		m_nOption;
	bool		m_bClicked;
	CString		m_strURL;
	CString		m_szAnchor;
	int		m_nLinkStatus;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
