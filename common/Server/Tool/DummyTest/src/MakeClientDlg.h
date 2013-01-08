#pragma once
#include "afxwin.h"


// CMakeClientDlg ��ȭ �����Դϴ�.

class CMakeClientDlg : public CDialog
{
	DECLARE_DYNAMIC(CMakeClientDlg)

public:
	CMakeClientDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMakeClientDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAKECLIENTDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(CWnd* pParentWnd = NULL);
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonCreateClient();
	CString m_sInputIDTag;
	CString m_sInputPassword;
	CString m_sInputScriptFileName;
	CString m_sInputIP;
	UINT m_iInputPort;
	UINT m_iInputNumClient;
	afx_msg void OnBnClickedButton2();
	CEdit IDEditControl;
	virtual BOOL OnInitDialog();
	CString m_sInputID;
};
