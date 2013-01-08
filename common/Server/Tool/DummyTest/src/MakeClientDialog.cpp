// MakeClientDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "testtool.h"
#include "MakeClientDialog.h"
#include "CommonDef.h"
#include "testtoolDlg.h"


// CMakeClientDialog ��ȭ �����Դϴ�.

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


// CMakeClientDialog �޽��� ó�����Դϴ�.

BOOL CMakeClientDialog::Create(CWnd* pParentWnd)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialog::Create(IDD, pParentWnd);
}

void CMakeClientDialog::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialog::PostNcDestroy();
}

void CMakeClientDialog::OnBnClickedButtonCreateClient()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	clientInfo.dState = L"���� ����";
	clientInfo.dName = m_sInputID;

	dlg->AddClient( clientInfo, m_iInputNumClient );
	OnOK();
}

void CMakeClientDialog::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

BOOL CMakeClientDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	IDEditControl.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
