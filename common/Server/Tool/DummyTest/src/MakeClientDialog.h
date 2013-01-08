#pragma once
#include "afxwin.h"


// CMakeClientDialog ��ȭ �����Դϴ�.

class CMakeClientDialog : public CDialog
{
	DECLARE_DYNAMIC(CMakeClientDialog)

public:
	CMakeClientDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMakeClientDialog();

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
