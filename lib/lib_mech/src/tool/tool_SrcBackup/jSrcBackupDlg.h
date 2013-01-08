// jSrcBackupDlg.h : 헤더 파일
//

#pragma once


// CjSrcBackupDlg 대화 상자
class CjSrcBackupDlg : public CDialog
{
// 생성
public:
	CjSrcBackupDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_JSRCBACKUP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
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
