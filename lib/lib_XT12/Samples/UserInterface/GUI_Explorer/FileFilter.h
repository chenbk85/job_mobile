#pragma once


// CFileFilter dialog

class CFileFilter : public CDialog
{
	DECLARE_DYNCREATE(CFileFilter)

public:
	CFileFilter(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileFilter();
// Overrides
// Dialog Data
	enum { IDD = IDD_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_csFilter;
};
