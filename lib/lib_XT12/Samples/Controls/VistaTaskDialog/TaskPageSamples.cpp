// TaskPageSamples.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "TaskSheetProperties.h"
#include "TaskPageSamples.h"

#include "TaskDialogSamples.h"


// CTaskPageSamples dialog

IMPLEMENT_DYNAMIC(CTaskPageSamples, CPropertyPage)

CTaskPageSamples::CTaskPageSamples()
	: CPropertyPage(CTaskPageSamples::IDD)
	, m_bSkinFramework(FALSE)
{
	m_pDlgParent = 0;
}

CTaskPageSamples::~CTaskPageSamples()
{

}

void CTaskPageSamples::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LINK, m_wndLinkCtrl);
	DDX_Control(pDX, IDC_STATIC_TDPAD, m_wndLinkPadCtrl);
	DDX_Check(pDX, IDC_CHECK_SKINFRAMEWORK, m_bSkinFramework);
}


BEGIN_MESSAGE_MAP(CTaskPageSamples, CPropertyPage)
	ON_BN_CLICKED(IDC_STATIC_LINK, OnLinkClicked)
	ON_BN_CLICKED(IDC_STATIC_TDPAD, OnLinkTDPadClicked)
	ON_BN_CLICKED(IDC_CHECK_SKINFRAMEWORK, OnBnClickedCheckSkinframework)
	ON_BN_CLICKED(IDC_BUTTON_PROGRESSDIALOG, OnBnClickedButtonProgressdialog)
	ON_BN_CLICKED(IDC_BUTTON_DYNAMICDIALOG, OnBnClickedButtonDynamicdialog)
	ON_BN_CLICKED(IDC_BUTTON_TIMERDIALOG, OnBnClickedButtonTimerdialog)
	ON_BN_CLICKED(IDC_BUTTON_SHEET, OnBnClickedButtonSheet)
	ON_BN_CLICKED(IDC_BUTTON_XMLDIALOG1, OnBnClickedXMLDialog1)
	ON_BN_CLICKED(IDC_BUTTON_XMLDIALOG2, OnBnClickedXMLDialog2)
	ON_BN_CLICKED(IDC_BUTTON_XMLDIALOG3, OnBnClickedXMLDialog3)
	ON_BN_CLICKED(IDC_BUTTON_XMLDIALOG4, OnBnClickedXMLDialog4)
	ON_BN_CLICKED(IDC_BUTTON_XMLDIALOG5, OnBnClickedXMLDialog5)
	ON_BN_CLICKED(IDC_BUTTON_XMLDIALOG6, OnBnClickedXMLDialog6)
	ON_BN_CLICKED(IDC_BUTTON_XMLDIALOG7, OnBnClickedXMLDialog7)
END_MESSAGE_MAP()


// CTaskPageSamples message handlers

BOOL CTaskPageSamples::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_pDlgParent = DYNAMIC_DOWNCAST(CTaskSheetProperties, GetParent());
	ASSERT_VALID(m_pDlgParent);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTaskPageSamples::OnLinkClicked()
{
	CXTPTaskDialogLinkCtrl::LINKITEM* pItem = m_wndLinkCtrl.GetFocusedLink();

	if (pItem) AfxMessageBox(pItem->strUrl);
}

void CTaskPageSamples::OnLinkTDPadClicked()
{
	CXTPTaskDialogLinkCtrl::LINKITEM* pItem = m_wndLinkPadCtrl.GetFocusedLink();

	if (pItem) ::ShellExecute(NULL, _T("open"), pItem->strUrl, 0, 0, SW_SHOW);
}

void CTaskPageSamples::OnBnClickedCheckSkinframework()
{
	UpdateData();

#ifdef _XTP_INCLUDE_SKINFRAMEWORK
	if (m_bSkinFramework)
	{
		XTPSkinManager()->LoadSkin(_T("Styles\\zune.msstyles"));
	}
	else
	{
		XTPSkinManager()->LoadSkin(0, 0);
	}
#endif
}


void CTaskPageSamples::OnBnClickedButtonSheet()
{
	CPropetySheetTaskDialog taskDlg(this);
	int nRet = (int)taskDlg.DoModal(m_pDlgParent->m_bUseComCtl32);
	
	TRACE(_T("Result = %i\n"), nRet);
	TRACE(_T("Option = %i\n"), taskDlg.m_page2.m_nOption);
	TRACE(_T("CheckState = %i\n"), taskDlg.m_page3.m_bState);
}

void CTaskPageSamples::OnBnClickedButtonProgressdialog()
{
	CProgressEffectsDialog taskDlg(this);
	taskDlg.SetCommonButtons(TDCBF_CANCEL_BUTTON);
	taskDlg.SetMainIcon(TD_WARNING_ICON);
	taskDlg.SetMainInstruction(_T("Change Password"));
	taskDlg.SetContent(_T("Remember your changed password."));

	INT_PTR nRet = taskDlg.DoModal(m_pDlgParent->m_bUseComCtl32);
	switch (nRet)
	{
	case 0: 
		AfxMessageBox(_T("Task Dialog could not be created!"));
		break;
	case IDOK:
		// the user pressed the OK button, change password.
		break;
	case IDCANCEL:
		// user canceled the dialog.
		break;
	};

}

void CTaskPageSamples::OnBnClickedButtonDynamicdialog()
{
	CDynamicTextDialog td(this);
	td.DoModal(m_pDlgParent->m_bUseComCtl32);
}

void CTaskPageSamples::OnBnClickedButtonTimerdialog()
{
	CTimerDialog td(this);
	td.DoModal(m_pDlgParent->m_bUseComCtl32);
}

void CTaskPageSamples::OnShowXMLDialog(LPCTSTR lpszName)
{
	CXTPTaskDialog td(this);
	VERIFY(td.CreateFromResource(IDR_DIALOGS, lpszName));

	td.DoModal(m_pDlgParent->m_bUseComCtl32);
}

void CTaskPageSamples::OnBnClickedXMLDialog1()
{
	OnShowXMLDialog(_T("Dialog001"));
}
void CTaskPageSamples::OnBnClickedXMLDialog2()
{
	OnShowXMLDialog(_T("Dialog002"));
}
void CTaskPageSamples::OnBnClickedXMLDialog3()
{
	OnShowXMLDialog(_T("Dialog003"));
}
void CTaskPageSamples::OnBnClickedXMLDialog4()
{
	OnShowXMLDialog(_T("Dialog004"));
}
void CTaskPageSamples::OnBnClickedXMLDialog5()
{
	OnShowXMLDialog(_T("Dialog005"));
}
void CTaskPageSamples::OnBnClickedXMLDialog6()
{
	OnShowXMLDialog(_T("Dialog006"));
}
void CTaskPageSamples::OnBnClickedXMLDialog7()
{
	CXTPTaskDialog td(this);

	LPCTSTR rglpsz[3];
	rglpsz[0] = _T("ToolkitEval.zip");
	rglpsz[1] = _T("WinZip File, 10.8MB");
	rglpsz[2] = _T("www.codejock.com");
	VERIFY(td.CreateFromResourceParam(AfxGetInstanceHandle(), IDR_DIALOGS, _T("Dialog007"), rglpsz, 3));

	td.DoModal(m_pDlgParent->m_bUseComCtl32);
}
