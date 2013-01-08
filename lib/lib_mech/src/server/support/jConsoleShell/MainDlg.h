// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "resource.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
	enum { STATUS_NOT_READY, STATUS_CREATED, STATUS_RUNNING };
public:

	int	 m_status; // 서버상태 
	
	WTL::CListBox		m_lv_log;
	WTL::CEdit m_edit;


	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();
	void Log(CString str);

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)

		MESSAGE_HANDLER(WM_ACTIVATEAPP, OnActvateApp)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_LIST1, LBN_DBLCLK, OnListDblClick)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		//COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_BTN_START, BN_CLICKED, OnBnClickedStart)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		COMMAND_HANDLER(IDC_BTN_MIDDLEWARE, BN_CLICKED, OnBnClickedRefreshMiddleware)
		COMMAND_HANDLER(ID_COMMAND_LOADCMDFILE, BN_CLICKED, On_ID_COMMAND_LOADCMDFILE)
		//COMMAND_HANDLER(IDC_EDIT1, EN_CHANGE, OnEnChangeEdit1)
	END_MSG_MAP()

	LRESULT CMainDlg::OnActvateApp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnListDblClick(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);
	LRESULT OnBnClickedStart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	static CMainDlg* m_pSingleton;
	static CMainDlg* Get() { return m_pSingleton; }
	LRESULT OnBnClickedRefreshMiddleware(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);	
	LRESULT On_ID_COMMAND_LOADCMDFILE(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);	
	LRESULT OnEnChangeEdit1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void LoadWinPos();
	void SaveWinPos();
	void LogCmd(CString str);
	void CMainDlg::load_default_cmd_cache_file(tcstr szFile);
};
extern HWND m_ConsoleHWND;


extern jIVar* g_pvNetConfigXml;
extern jIVar* pvNetConfigNode;
