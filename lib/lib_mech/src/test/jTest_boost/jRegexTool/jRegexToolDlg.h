// jRegexToolDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

// CjRegexToolDlg ��ȭ ����
class CjRegexToolDlg : public CDialog
{
// ����
public:
	CjRegexToolDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_JREGEXTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtSearch();
	CString m_editOrg;
	CString m_editMatch;
	CString m_editResult;
	afx_msg void OnBnClickedBtReplace();
	CString m_editReplace;
	afx_msg void OnBnClickedBtMatch();
	CComboBox m_Flag1;
	unsigned long  CjRegexToolDlg::GetFlagMatch2();
	unsigned long GetFlagMatch();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedHelp();
	CComboBox m_Flag2;
	void CjRegexToolDlg::SaveFile1(const char* strAction,bool iscustomSave=false);
	afx_msg void OnBnClickedOpenlog();
	CString m_logFile;
	BOOL m_caseOk;
	BOOL m_bAutoSave;
	afx_msg void OnBnClickedBtSave();
	CString m_editDesc;
};
