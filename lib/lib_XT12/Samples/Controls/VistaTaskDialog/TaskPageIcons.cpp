// TaskPageIcons.cpp : implementation file
//

#include "stdafx.h"
#include "VistaTaskDialog.h"
#include "TaskSheetProperties.h"
#include "TaskPageIcons.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskPageIcons property page

IMPLEMENT_DYNCREATE(CTaskPageIcons, CPropertyPage)

CTaskPageIcons::CTaskPageIcons() : CPropertyPage(CTaskPageIcons::IDD)
{
	//{{AFX_DATA_INIT(CTaskPageIcons)
	m_nFootIcon = 4;
	m_nMainIcon = 2;
	m_strFootPath = _T("");
	m_strMainPath = _T("");
	m_bSysIcons = TRUE;
	//}}AFX_DATA_INIT

	m_hMainIcon = 0;
	m_hFootIcon = 0;
}

CTaskPageIcons::~CTaskPageIcons()
{
	SAFE_DELETE_HICON(m_hMainIcon);
	SAFE_DELETE_HICON(m_hFootIcon);
}

void CTaskPageIcons::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskPageIcons)
	DDX_Control(pDX, IDC_COMBO_MAINICON, m_comboMainIcon);
	DDX_Control(pDX, IDC_COMBO_FOOTICON, m_comboFootIcon);
	DDX_CBIndex(pDX, IDC_COMBO_FOOTICON, m_nFootIcon);
	DDX_CBIndex(pDX, IDC_COMBO_MAINICON, m_nMainIcon);
	DDX_Text(pDX, IDC_EDIT_FOOTPATH, m_strFootPath);
	DDX_Text(pDX, IDC_EDIT_MAINPATH, m_strMainPath);
	DDX_Check(pDX, IDC_CHK_SYSICON, m_bSysIcons);
	DDX_Control(pDX, IDC_CHK_SYSICON, m_chkSysIcon);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTaskPageIcons, CPropertyPage)
	//{{AFX_MSG_MAP(CTaskPageIcons)
	ON_CBN_SELENDOK(IDC_COMBO_MAINICON, OnSelEndOkMainIcon)
	ON_EN_CHANGE(IDC_EDIT_MAINPATH, OnEditChangeMainPath)
	ON_BN_CLICKED(IDC_BTN_MAINPATH, OnBtnMainPath)
	ON_CBN_SELENDOK(IDC_COMBO_FOOTICON, OnSelEndOkFootIcon)
	ON_EN_CHANGE(IDC_EDIT_FOOTPATH, OnEditChangeFootPath)
	ON_BN_CLICKED(IDC_BTN_FOOTPATH, OnBtnFootPath)
	ON_BN_CLICKED(IDC_CHK_SYSICON, OnChkSysIcon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskPageIcons message handlers

void CTaskPageIcons::OnSelEndOkMainIcon()
{
	UpdateData();
	SAFE_DELETE_HICON(m_hMainIcon);
	m_strMainPath.Empty();
	UpdateData(FALSE);
}

void CTaskPageIcons::OnEditChangeMainPath()
{
	UpdateData();

	if (FILEEXISTS_S(m_strMainPath))
	{
		SAFE_DELETE_HICON(m_hMainIcon);
		m_hMainIcon = (HICON)::LoadImage(NULL, m_strMainPath, IMAGE_ICON,
			::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_LOADFROMFILE);
		m_nMainIcon = 0;
		m_comboMainIcon.SetCurSel(m_nMainIcon);
	}
}

void CTaskPageIcons::OnSelEndOkFootIcon()
{
	UpdateData();
	SAFE_DELETE_HICON(m_hFootIcon);
	m_strFootPath.Empty();
	UpdateData(FALSE);
}

void CTaskPageIcons::OnEditChangeFootPath()
{
	UpdateData();
	
	if (FILEEXISTS_S(m_strFootPath))
	{
		SAFE_DELETE_HICON(m_hFootIcon);
		m_hFootIcon = (HICON)::LoadImage(NULL, m_strFootPath, IMAGE_ICON,
			::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_LOADFROMFILE);
		m_nFootIcon = 0;
		m_comboFootIcon.SetCurSel(m_nFootIcon);
	}
}

void CTaskPageIcons::OnBtnMainPath() 
{
	CString strFilter = _T("Icon Files|*.ico||All files (*.*)|*.*||");
	
	CFileDialog dlg(TRUE, _T("ico"), NULL,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER, strFilter, this);
	
	if (dlg.DoModal() == IDOK)
	{
		m_strMainPath = dlg.GetPathName();
		UpdateData(FALSE);
		OnEditChangeMainPath();
	}
}

void CTaskPageIcons::OnBtnFootPath() 
{
	CString strFilter = _T("Icon Files|*.ico||All files (*.*)|*.*||");
	
	CFileDialog dlg(TRUE, _T("ico"), NULL,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER, strFilter, this);
	
	if (dlg.DoModal() == IDOK)
	{
		m_strFootPath = dlg.GetPathName();
		UpdateData(FALSE);
		OnEditChangeFootPath();
	}
}

void CTaskPageIcons::OnChkSysIcon() 
{
	UpdateData();
}

static const TCHAR* TASKICON[5][2] = 
{
	{ (TCHAR*)NULL,					_T("None")				},
	{ (TCHAR*)TD_ERROR_ICON,		_T("Error Icon")		},
	{ (TCHAR*)TD_WARNING_ICON,		_T("Warning Icon")		},
	{ (TCHAR*)TD_INFORMATION_ICON,	_T("Information Icon")	},
	{ (TCHAR*)TD_SHIELD_ICON,		_T("Shield Icon")		}
};

BOOL CTaskPageIcons::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_pDlgParent = DYNAMIC_DOWNCAST(CTaskSheetProperties, GetParent());
	ASSERT_VALID(m_pDlgParent);

	for (int i = 0; i < 5; ++i)
	{
		m_comboMainIcon.SetItemData(
			m_comboMainIcon.AddString(TASKICON[i][1]), (DWORD_PTR)TASKICON[i][0]);

		m_comboFootIcon.SetItemData(
			m_comboFootIcon.AddString(TASKICON[i][1]), (DWORD_PTR)TASKICON[i][0]);
	}

	UpdateData(FALSE);

	//m_comboMainIcon.SetCurSel(4);
	//m_comboFootIcon.SetCurSel(3);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTaskPageIcons::OnSetActive()
{
	if (!CPropertyPage::OnSetActive())
		return FALSE;

	if (m_pDlgParent)
	{
		m_chkSysIcon.EnableWindow(!m_pDlgParent->UsingComCtl32());
	}

	return TRUE;
}
