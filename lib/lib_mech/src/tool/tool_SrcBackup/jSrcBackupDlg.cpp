// jSrcBackupDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
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


// CjSrcBackupDlg ��ȭ ����



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


// CjSrcBackupDlg �޽��� ó����

BOOL CjSrcBackupDlg::OnInitDialog()
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
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CjSrcBackupDlg::OnPaint() 
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
HCURSOR CjSrcBackupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CjSrcBackupDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CjSrcBackupDlg::OnBnClickedOk()
{

	UpdateData();
	extern CString g_sProjName;
	extern CString g_sTargetDir;
	extern CString g_sDestDir;

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
			MessageBox("�Է� �μ��߿��� ������ ���� ������ ���� ������ ¦���� �ƴԴ�.", "error",MB_OK);
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
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CjSrcBackupDlg::OnBnClickedYyy()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
