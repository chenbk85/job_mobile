// jSrcBackupDlg.h : ��� ����
//

#pragma once


// CjSrcBackupDlg ��ȭ ����
class CjSrcBackupDlg : public CDialog
{
// ����
public:
	CjSrcBackupDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_JSRCBACKUP_DIALOG };

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
	CString m_desc;
	CString m_ext;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	CString m_desc2;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedYyy();
};
