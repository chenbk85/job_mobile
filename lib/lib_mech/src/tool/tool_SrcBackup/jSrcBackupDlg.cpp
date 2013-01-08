// jSrcBackupDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "jSrcBackup.h"
#include "jSrcBackupDlg.h"
#include ".\jsrcbackupdlg.h"

inline void jSplit(const std::string& inLine, const std::string& Separ, std::vector<std::string>& out)
////////////////////////////////////////////////////////////////
{
	const size_t N = inLine.length();
	size_t iStart, iEnd;

	iStart = inLine.find_first_not_of(Separ);
	while ((iStart >= 0) && (iStart < N)) 
	{
		iEnd = inLine.find_first_of(Separ, iStart);
		if ((iEnd < 0) || (iEnd > N)) iEnd = N;
		out.push_back(inLine.substr(iStart, iEnd - iStart));
		iStart = inLine.find_first_not_of(Separ, iEnd+1);
	}
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

// 구현
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


// CjSrcBackupDlg 대화 상자



CjSrcBackupDlg::CjSrcBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CjSrcBackupDlg::IDD, pParent)
	, m_desc(_T(""))
	, m_ext(_T("*.pak"))
	, m_desc2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CjSrcBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_desc);
	DDX_Text(pDX, IDC_EDIT2, m_ext);
	DDX_Text(pDX, IDC_EDIT3, m_desc2);
}

BEGIN_MESSAGE_MAP(CjSrcBackupDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT3, OnEnChangeEdit3)
	ON_BN_CLICKED(ID_YYY, OnBnClickedYyy)
END_MESSAGE_MAP()


// CjSrcBackupDlg 메시지 처리기

BOOL CjSrcBackupDlg::OnInitDialog()
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
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

void CjSrcBackupDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CjSrcBackupDlg::OnPaint() 
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
HCURSOR CjSrcBackupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CjSrcBackupDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우 이 컨트롤은
	// CDialog::마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여
	// CRichEditCtrl().SetEventMask()를 호출하도록 OnInitDialog() 함수를 재지정하지 않으면
	// 이 알림을 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CjSrcBackupDlg::OnBnClickedOk()
{

	UpdateData();
	extern CString g_sProjName;
	extern CString g_sTargetDir;
	extern CString g_sDestDir;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*
	pkzipc -add -max -rec -pass=govkfl -dir=full -excl=*.obj -excl=*.ncb -excl=*.sbr -excl=*.bak -excl=*.bsc -excl=*.pch 
	-excl=*.pdb -excl=*.ilk -excl=*.idb -excl=.svn -excl=*.zip %~3\%%d.zip %~2\*.*
	*/
	char tmpbuf[128];


	_strtime( tmpbuf );
	CString sTime = tmpbuf;
	sTime.Replace(':', '-');
	_strdate( tmpbuf );
	CString sDate = tmpbuf ;
	sDate.Replace('/', '_');
	sDate =sDate + "y" + sTime;
	
	CString sExcl_est="";
	std::vector<std::string> out;
	jSplit((const char*)m_ext , "; ",out);
	for( int ii = 0; ii< out.size() ; ++ii)
	{
		sExcl_est +=" -excl=";
		sExcl_est +=out[ii].c_str();
	}

	char* szFormat = "pkzipc -add -max -rec -dir=full -excl=*.obj \
-excl=*.ncb -excl=*.sbr -excl=*.bak -excl=*.bsc -excl=*.pch %s \
-excl=*.pdb -excl=*.ilk -excl=*.idb -excl=.svn -excl=*.zip %s\\%s_%s_%s.zip %s\\*.*";

	//char* szFormat = "pkzipc -add -max -rec -pass=govkfl -dir=full -excl=*.obj \
									 -excl=*.ncb -excl=*.sbr -excl=*.bak -excl=*.bsc -excl=*.pch %s \
									 -excl=*.pdb -excl=*.ilk -excl=*.idb -excl=.svn -excl=*.zip %s\\%s_%s_%s.zip %s\\*.*";

	char szExe[2048], szTxt[2048];
	m_desc.Replace(' ', '_');
	sprintf(szExe,szFormat,sExcl_est,g_sDestDir, sDate,m_desc,g_sProjName,g_sTargetDir);
	WinExec(szExe, SW_NORMAL);
	sprintf(szTxt,"%s\\%s_%s_%s.txt",g_sDestDir, sDate,m_desc,g_sProjName);
	FILE* fp = fopen(szTxt,"wt");
	if(fp)
	{
		fprintf(fp, "%s\n\n\n", szExe);
		fprintf(fp, "-------------------------------------------------------\n\n");
		fprintf(fp, m_desc2);
		fclose(fp);
	}

	extern std::vector<std::string> s_list;
	if(s_list.size())
	{
		if(s_list.size() %2 !=0)
		{
			MessageBox("입력 인수중에서 나머지 포함 폴더에 대한 값들이 짝수가 아님다.", "error",MB_OK);
			return;
		}
		for(int ii=0; ii < s_list.size() ; ii+=2)
		{
			const char* sz1 =s_list[ii].c_str();
			const char* sz2 = s_list[ii+1].c_str();
			sprintf(szExe,szFormat,g_sDestDir, sDate,m_desc,sz1 , sz2);
			WinExec(szExe, SW_NORMAL);
		}
	}

	OnOK();

}

void CjSrcBackupDlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우 이 컨트롤은
	// CDialog::마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여
	// CRichEditCtrl().SetEventMask()를 호출하도록 OnInitDialog() 함수를 재지정하지 않으면
	// 이 알림을 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CjSrcBackupDlg::OnBnClickedYyy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
