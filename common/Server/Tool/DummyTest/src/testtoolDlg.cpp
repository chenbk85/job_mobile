// testtoolDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "testtool.h"
#include "testtoolDlg.h"
#include "settings.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CtesttoolDlg 대화 상자




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


// CtesttoolDlg 메시지 처리기

BOOL CtesttoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	initTestTool();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CtesttoolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CtesttoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtesttoolDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정하고  마스크에 OR 연산하여 설정된
	// ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출해야만
	// 해당 알림 메시지를 보냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	logStr.Format( L"더미 클라이언트 생성 완료 (요청 %d개 / 실제 생성 %d개)", count, createCount );
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
			 logStr.Format( L"%s 삭제", clientName );
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	KillTimer(0);
	OnOK();
}

void CtesttoolDlg::OnBnClickedClearlog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mainLogStr = L"";
	showLog( mainLogStr );
}

void CtesttoolDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// 게임중 리스트 박스 초기화
	int count = gamePlayingRoomCtrl.GetCount();
	for( int i = count; i >= 0; i-- )
	{
		gamePlayingRoomCtrl.DeleteString(i);
	}

	// 클라이언트 리스트박스에서 키값 얻기
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CtesttoolDlg::OnBnClicked_SHOW_CMD()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(_T("@con.toggle_console"));
	nMOB::ConsoleDlg_Show(theApp.m_hInstance,this->m_hWnd);
}

void CtesttoolDlg::OnBnClicked_SHOW_CONSOLE()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//
}

void CtesttoolDlg::OnBnClickedShowLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(_T("@con.open_log"));
}
