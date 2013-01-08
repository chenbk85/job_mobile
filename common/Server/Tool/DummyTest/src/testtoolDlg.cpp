// testtoolDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "testtool.h"
#include "testtoolDlg.h"
#include "settings.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CtesttoolDlg ��ȭ ����




CtesttoolDlg::CtesttoolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtesttoolDlg::IDD, pParent)
	, logStr(_T(""))
	, clientInfoID(_T(""))
	, clientInfoPassword(_T(""))
	, clientInfoScriptFileName(_T(""))
	, clientInfoIP(_T(""))
	, clientInfoPort(_T(""))
	, clientInfoConnectState(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CtesttoolDlg::~CtesttoolDlg()
{
	mainLogStr = L"";
	logStr = L"";
	logString = L"";
	nMOB::ConsoleDlg_Close();

	delete g_dummyClientManager;
}

void CtesttoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, logStr);
	DDX_Control(pDX, IDC_LIST1, threadList);
	DDX_Control(pDX, IDC_EDIT1, logEditCtrl);
	DDX_Text(pDX, IDC_EDIT_ID, clientInfoID);
	DDX_Text(pDX, IDC_EDIT_PASSWD, clientInfoPassword);
	DDX_Text(pDX, IDC_EDIT_SCRIPT_FILE, clientInfoScriptFileName);
	DDX_Text(pDX, IDC_EDIT_IP, clientInfoIP);
	DDX_Text(pDX, IDC_EDIT_PORT, clientInfoPort);
	DDX_Text(pDX, IDC_EDIT_CONN_STATE, clientInfoConnectState);
	DDX_Control(pDX, IDC_LIST3, gamePlayingRoomCtrl);
}

BEGIN_MESSAGE_MAP(CtesttoolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_LBN_SELCHANGE(IDC_LIST1, &CtesttoolDlg::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT1, &CtesttoolDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDBUTTON_MAKE, &CtesttoolDlg::OnBnClickedMake)
	ON_BN_CLICKED(IDBUTTON_DELETE, &CtesttoolDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDBUTTON_RUN, &CtesttoolDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDBUTTON_STOP, &CtesttoolDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDBUTTON_EXIT, &CtesttoolDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDBUTTON_THREAD_CLEARLOG, &CtesttoolDlg::OnBnClickedThreadClearlog)
	ON_BN_CLICKED(IDBUTTON_CLEARLOG, &CtesttoolDlg::OnBnClickedClearlog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CtesttoolDlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST3, &CtesttoolDlg::OnLbnSelchangeList3)
	ON_COMMAND(ID_SHOW_CMD, &CtesttoolDlg::OnShowCmd)
	ON_BN_CLICKED(IDBUTTON_CLEARLOG3, &CtesttoolDlg::OnBnClicked_SHOW_CMD)
	ON_BN_CLICKED(IDBUTTON_CLEARLOG2, &CtesttoolDlg::OnBnClicked_SHOW_CONSOLE)
	ON_BN_CLICKED(IDBUTTON_SHOW_LOG, &CtesttoolDlg::OnBnClickedShowLog)
END_MESSAGE_MAP()


// CtesttoolDlg �޽��� ó����

BOOL CtesttoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	initTestTool();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}


void CtesttoolDlg::initTestTool()
{
	mainLogStr = L"";
	UpdateData(false);
	SetTimer(0, 50, 0);

	jAssert0(g_dummyClientManager==0);
	g_dummyClientManager = new CDummyClientManager();
	logEditCtrl.SetLimitText(999999);

	for( int i = 0; i < NUM_DUMMY_CLIENT; i++ )
	{
		OnBnClickedMake();
	}
}



void CtesttoolDlg::addMainLog( CString log )
{
	mainLogStr = mainLogStr + log + L"\r\n";
}

void CtesttoolDlg::showLog( CString log )
{
	jLOG((cstr)log);
	logStr = log;
	int scrollLIne = logEditCtrl.GetLineCount();
	UpdateData(false);
	logEditCtrl.LineScroll(scrollLIne);
}

void CtesttoolDlg::showMainLog()
{
	showLog( mainLogStr );
}

void CtesttoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CtesttoolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CtesttoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtesttoolDlg::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nCount = threadList.GetSelCount();
	int *seletedListIndex = new int[nCount];
	threadList.GetSelItems(nCount, seletedListIndex); 

	selectedDummyClientList.clear();

	for( int i = 0; i < nCount; i++ )
	{
		TCHAR text[64];
		threadList.GetText( seletedListIndex[i], text );
		CDummyClient *dummyClient = g_dummyClientManager->GetDummyClientByName( text );
		selectedDummyClientList.push_back( dummyClient );
	}
	
	delete seletedListIndex;
	UpdateSelectedClientInfo();

	if( nCount != 1 )
	{
		showLog(L"");
	}
}

void CtesttoolDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� �������ϰ�  ����ũ�� OR �����Ͽ� ������
	// ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ���ؾ߸�
	// �ش� �˸� �޽����� �����ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CtesttoolDlg::OnBnClickedMake()
{
	CWnd *pWnd = AfxGetMainWnd();
	CMakeClientDlg *pDialog = new CMakeClientDlg( pWnd );
	pDialog->Create(this);
	pDialog->ShowWindow(SW_SHOW);
}


void CtesttoolDlg::AddClient( CLIENT_INFO &clientInfo, int count )
{
	int createCount = 0;
	int startIndex = g_dummyClientManager->GetCurIndex();
	createCount = g_dummyClientManager->MakeDummyClient( count, clientInfo );
	int endIndex = startIndex + createCount;

	AddListBox( startIndex, endIndex );

	CString logStr;
	logStr.Format( L"���� Ŭ���̾�Ʈ ���� �Ϸ� (��û %d�� / ���� ���� %d��)", count, createCount );
	addMainLog( logStr );
	showMainLog();
}

void CtesttoolDlg::AddListBox( int _startIndex, int _endIndex )
{
	for( int i = _startIndex; i < _endIndex; i++ )
	{
		CDummyClient *dummyClient = g_dummyClientManager->GetDummyClientByIndex( i );
		if( dummyClient != NULL )
		{
			threadList.AddString( dummyClient->m_clientInfo.GetName() );
		}
	}
}


void CtesttoolDlg::OnBnClickedDelete()
{
	std::list<CDummyClient *>::iterator iter = selectedDummyClientList.begin();
	for( ; iter != selectedDummyClientList.end(); iter++ )
	{
		CDummyClient *dummyClient = *iter;
		int index = dummyClient->m_clientInfo.m_iIndex;
		if( g_dummyClientManager->DeleteDummyClient( index, index ) == 1 )
		 {
			CString clientName = dummyClient->m_clientInfo.GetName();
			int nIndex = 0;
			while ( ( nIndex = threadList.FindStringExact(nIndex, clientName) ) != LB_ERR )
			{
			   threadList.DeleteString( nIndex );
			}

			 CString logStr;
			 logStr.Format( L"%s ����", clientName );
			 addMainLog( logStr );
			 showMainLog();
		 }	
	}
	selectedDummyClientList.clear();
	UpdateSelectedClientInfo();
}

void CtesttoolDlg::OnBnClickedRun()
{
	std::list<CDummyClient *>::iterator iter = selectedDummyClientList.begin();

	for( ; iter != selectedDummyClientList.end(); iter++ )
	{
		CDummyClient *dummyClient = *iter;
		int index = dummyClient->m_clientInfo.m_iIndex;
		g_dummyClientManager->Connect( index, index, 1, 20 );
	}
}

void CtesttoolDlg::OnBnClickedStop()
{
	std::list<CDummyClient *>::iterator iter = selectedDummyClientList.begin();

	for( ; iter != selectedDummyClientList.end(); iter++ )
	{
		CDummyClient *dummyClient = *iter;
		int index = dummyClient->m_clientInfo.m_iIndex;
		g_dummyClientManager->Disconnect( index, index, 1, 20 );
	}
}

void CtesttoolDlg::OnBnClickedThreadClearlog()
{
	std::list<CDummyClient *>::iterator iter = selectedDummyClientList.begin();
	for( ; iter != selectedDummyClientList.end(); iter++ )
	{
		CDummyClient *dummyClient = *iter;
		if( dummyClient != NULL )
		{
			dummyClient->ClearLog();
		}
	}
}

void CtesttoolDlg::OnBnClickedExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	KillTimer(0);
	OnOK();
}

void CtesttoolDlg::OnBnClickedClearlog()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	mainLogStr = L"";
	showLog( mainLogStr );
}

void CtesttoolDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if( selectedDummyClientList.size() == 1 )
	{
		CString log;
		CDummyClient *dummyClient = *selectedDummyClientList.begin();
		if( dummyClient != NULL )
		{
			dummyClient->GetLog( log );
			if( logStr != log )
			{
				showLog( log );
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CtesttoolDlg::UpdateSelectedClientInfo()
{
	int selectedDubbyClientCount = selectedDummyClientList.size();

	if( selectedDubbyClientCount == 0 )
	{
		clientInfoID = "";
		clientInfoPassword = "";
		clientInfoScriptFileName = "";
		clientInfoIP = "";
		clientInfoPort = "";
		clientInfoConnectState = "";
	}
	else if( selectedDubbyClientCount == 1 )
	{
		CDummyClient *dummyClient =  *selectedDummyClientList.begin();
		if( dummyClient != NULL )
		{
			clientInfoID = dummyClient->m_clientInfo.GetName();
			clientInfoPassword = dummyClient->m_clientInfo.dPwd;
			clientInfoScriptFileName = dummyClient->m_clientInfo.dScriptFileName;
			clientInfoIP = dummyClient->m_clientInfo.dServerIP;
			CString portStr;
			portStr.Format( L"%d", dummyClient->m_clientInfo.m_iServerPort );
			clientInfoPort = portStr;
			clientInfoConnectState = dummyClient->m_clientInfo.dState;
		}
	}
	else
	{
		clientInfoID = "";
		clientInfoPassword = "";
		clientInfoScriptFileName = "";
		clientInfoIP = "";
		clientInfoPort = "";
		clientInfoConnectState = "";
	}
	UpdateData(false);
}
void CtesttoolDlg::OnBnClickedButton1()
{
	// ������ ����Ʈ �ڽ� �ʱ�ȭ
	int count = gamePlayingRoomCtrl.GetCount();
	for( int i = count; i >= 0; i-- )
	{
		gamePlayingRoomCtrl.DeleteString(i);
	}

	// Ŭ���̾�Ʈ ����Ʈ�ڽ����� Ű�� ���
	count = threadList.GetCount();
	for( int i = 0; i < count; i++ )
	{
		TCHAR text[64];
		threadList.GetText( i, text );
		CDummyClient *dummyClient = g_dummyClientManager->GetDummyClientByName( text );
		if( dummyClient != NULL )
		{
			bool isPlaying = dummyClient->GetIsPlaying();
			if( isPlaying == true )
			{
				gamePlayingRoomCtrl.AddString(text);
			}
		}
	}

	UpdateData(false);
}

void CtesttoolDlg::OnLbnSelchangeList3()
{
	int selectedSel = gamePlayingRoomCtrl.GetCurSel();
	if( selectedSel == -1 )
	{
		return;
	}
	else
	{
		int index = -1;
		TCHAR text1[64];
		gamePlayingRoomCtrl.GetText( selectedSel, text1 );
		
		int count = threadList.GetCount();
		for( int i = 0; i < count; i++ )
		{
			TCHAR text2[64];
			threadList.GetText( i, text2 );
			if( _tcscmp(text1, text2) == 0 )
			{
				index = i;
				break;
			}
		}
		
		if( index != -1 )
		{
			int count = threadList.GetCount();
			for( int i = 0; i < count; i++ )
			{
				threadList.SetSel(i, false);
			}
			threadList.SetSel(index, true);
			UpdateData(false);
			OnLbnSelchangeList1();
		}
	}
}

void CtesttoolDlg::OnShowCmd()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CtesttoolDlg::OnBnClicked_SHOW_CMD()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(_T("@con.toggle_console"));
	nMOB::ConsoleDlg_Show(theApp.m_hInstance,this->m_hWnd);
}

void CtesttoolDlg::OnBnClicked_SHOW_CONSOLE()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//
}

void CtesttoolDlg::OnBnClickedShowLog()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(_T("@con.open_log"));
}
