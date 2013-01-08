// MakeClientDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "testtool.h"
#include "MakeClientDialog.h"
#include "CommonDef.h"
#include "testtoolDlg.h"


// CMakeClientDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMakeClientDialog, CDialog)

CMakeClientDialog::CMakeClientDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMakeClientDialog::IDD, pParent)
	, m_sInputIDTag(pv_ClientID->Get_cstr() )
	, m_sInputPassword(pv_ClientPassword->Get_cstr())
	, m_sInputScriptFileName(pv_PythonScript->Get_cstr())
	, m_sInputIP(pv_ServerIP->Get_cstr() )
	, m_iInputPort(pv_ServerPort->Get_int())
	, m_iInputNumClient(pv_ClientCreateNum->Get_int())
	, m_sInputID(_T(""))
{

}

CMakeClientDialog::~CMakeClientDialog()
{
}

void CMakeClientDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sInputIDTag);
	DDX_Text(pDX, IDC_EDIT8, m_sInputPassword);
	DDX_Text(pDX, IDC_EDIT9, m_sInputScriptFileName);
	DDX_Text(pDX, IDC_EDIT10, m_sInputIP);
	DDX_Text(pDX, IDC_EDIT11, m_iInputPort);
	DDX_Text(pDX, IDC_EDIT12, m_iInputNumClient);
	DDX_Control(pDX, IDC_EDIT1, IDEditControl);
	DDX_Text(pDX, IDC_EDIT13, m_sInputID);
}


BEGIN_MESSAGE_MAP(CMakeClientDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_CLIENT, &CMakeClientDialog::OnBnClickedButtonCreateClient)
	ON_BN_CLICKED(IDC_BUTTON2, &CMakeClientDialog::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMakeClientDialog 메시지 처리기입니다.

BOOL CMakeClientDialog::Create(CWnd* pParentWnd)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::Create(IDD, pParentWnd);
}

void CMakeClientDialog::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialog::PostNcDestroy();
}

void CMakeClientDialog::OnBnClickedButtonCreateClient()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
	pv_PythonScript->Set_cstr((cstr)m_sInputScriptFileName);
	pv_ClientID->Set_cstr((cstr)m_sInputIDTag);
	pv_ClientPassword->Set_cstr((cstr) m_sInputPassword);
	pv_ServerIP->Set_cstr((cstr)m_sInputIP);
	pv_ServerPort->Set_int(m_iInputPort);
	pv_ClientCreateNum->Set_int(m_iInputNumClient);

	CLIENT_INFO clientInfo;
	clientInfo.dNameTag = m_sInputIDTag;
	clientInfo.dPwd = m_sInputPassword;
	clientInfo.dScriptFileName = m_sInputScriptFileName;
	clientInfo.dServerIP = m_sInputIP;
	clientInfo.m_iServerPort = m_iInputPort;
	clientInfo.dState = L"접속 해제";
	clientInfo.dName = m_sInputID;

	dlg->AddClient( clientInfo, m_iInputNumClient );
	OnOK();
}

void CMakeClientDialog::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

BOOL CMakeClientDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	IDEditControl.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
