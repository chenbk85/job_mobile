// testtoolDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

#include "resource.h"
#include "DummyClientManager.h"
#include "MakeClientDlg.h"
#include "CommonDef.h"
#include <list>

// CtesttoolDlg ��ȭ ����

class CtesttoolDlg : public CDialog
{
// �����Դϴ�.
public:
	CtesttoolDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CtesttoolDlg();
	void initTestTool();
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TESTTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	CString mainLogStr;
	// 
	CListBox threadList;
	std::list< CDummyClient *> selectedDummyClientList;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	///
	void AddListBox( int _startIndex, int _endIndex );
	///
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	
	
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedMake();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedThreadClearlog();
	afx_msg void OnBnClickedClearlog();

	void showLog( CString log );
	void addMainLog( CString log );
	void showMainLog();
	void temp();
	CString logStr;
	CString logString;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit logEditCtrl;
	void UpdateSelectedClientInfo();

	CString clientInfoID;
	CString clientInfoPassword;
	CString clientInfoScriptFileName;
	CString clientInfoIP;
	CString clientInfoPort;
	CString clientInfoConnectState;

	void AddClient( CLIENT_INFO &clientInfo, int count = 1 );
	afx_msg void OnBnClickedButton1();
	CListBox gamePlayingRoomCtrl;
	afx_msg void OnLbnSelchangeList3();
	afx_msg void OnShowCmd();
	afx_msg void OnBnClicked_SHOW_CMD();
	afx_msg void OnBnClicked_SHOW_CONSOLE();
	afx_msg void OnBnClickedShowLog();

	nXML::jE m_eDocUser;
};
