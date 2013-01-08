// jRegexToolDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

// CjRegexToolDlg 대화 상자
class CjRegexToolDlg : public CDialog
{
// 생성
public:
	CjRegexToolDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_JREGEXTOOL_DIALOG };

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
