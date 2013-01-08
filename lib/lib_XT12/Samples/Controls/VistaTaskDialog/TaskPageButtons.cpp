// TaskPageButtons.cpp : implementation file
//

#include "stdafx.h"
#include "VistaTaskDialog.h"
#include "TaskSheetProperties.h"
#include "TaskPageButtons.h"
#include "TaskEditButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskPageButtons property page

IMPLEMENT_DYNCREATE(CTaskPageButtons, CPropertyPage)

CTaskPageButtons::CTaskPageButtons() : CPropertyPage(CTaskPageButtons::IDD)
{
	//{{AFX_DATA_INIT(CTaskPageButtons)
	m_bCancel = FALSE;
	m_bClose = FALSE;
	m_bShowIcons = TRUE;
	m_bNo = FALSE;
	m_bOk = FALSE;
	m_bRetry = FALSE;
	m_bUseLinks = FALSE;
	m_bYes = FALSE;
	//}}AFX_DATA_INIT

	XTPResourceManager()->LoadString(&m_strOk, XTP_IDS_TASK_OK);
	XTPDrawHelpers()->StripMnemonics(m_strOk);

	XTPResourceManager()->LoadString(&m_strYes, XTP_IDS_TASK_YES);
	XTPDrawHelpers()->StripMnemonics(m_strYes);

	XTPResourceManager()->LoadString(&m_strNo, XTP_IDS_TASK_NO);
	XTPDrawHelpers()->StripMnemonics(m_strNo);

	XTPResourceManager()->LoadString(&m_strCancel, XTP_IDS_TASK_CANCEL);
	XTPDrawHelpers()->StripMnemonics(m_strCancel);

	XTPResourceManager()->LoadString(&m_strRetry, XTP_IDS_TASK_RETRY);
	XTPDrawHelpers()->StripMnemonics(m_strRetry);

	XTPResourceManager()->LoadString(&m_strClose, XTP_IDS_TASK_CLOSE);
	XTPDrawHelpers()->StripMnemonics(m_strClose);
}

CTaskPageButtons::~CTaskPageButtons()
{
}

void CTaskPageButtons::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskPageButtons)
	DDX_Control(pDX, IDC_BTN_REMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_LIST_CUSTOM, m_listCustom);
	DDX_Control(pDX, IDC_COMBO_DEFAULT, m_comboDefault);
	DDX_Check(pDX, IDC_CHK_CANCEL, m_bCancel);
	DDX_Check(pDX, IDC_CHK_CLOSE, m_bClose);
	DDX_Check(pDX, IDC_CHK_SHOWICONS, m_bShowIcons);
	DDX_Check(pDX, IDC_CHK_NO, m_bNo);
	DDX_Check(pDX, IDC_CHK_OK, m_bOk);
	DDX_Check(pDX, IDC_CHK_RETRY, m_bRetry);
	DDX_Check(pDX, IDC_CHK_USELINKS, m_bUseLinks);
	DDX_Check(pDX, IDC_CHK_YES, m_bYes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaskPageButtons, CPropertyPage)
	//{{AFX_MSG_MAP(CTaskPageButtons)
	ON_BN_CLICKED(IDC_CHK_USELINKS, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_OK, OnChkOk)
	ON_BN_CLICKED(IDC_CHK_YES, OnChkYes)
	ON_BN_CLICKED(IDC_CHK_CANCEL, OnChkCancel)
	ON_BN_CLICKED(IDC_CHK_NO, OnChkNo)
	ON_BN_CLICKED(IDC_CHK_RETRY, OnChkRetry)
	ON_BN_CLICKED(IDC_CHK_CLOSE, OnChkClose)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_REMOVE, OnBtnRemove)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CUSTOM, OnItemChangedListCustom)
	ON_BN_CLICKED(IDC_CHK_SHOWICONS, OnUpdateData)
	ON_CBN_SELENDOK(IDC_COMBO_DEFAULT, OnUpdateData)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskPageButtons message handlers

void CTaskPageButtons::AddCommonButton(int nID)
{
	switch (nID)
	{
	case IDOK:
		m_pDlgParent->UpdateButtonMap(
			m_strOk, IDOK, &m_comboDefault, m_bOk);
		break;
	case IDYES:
		m_pDlgParent->UpdateButtonMap(
			m_strYes, IDYES, &m_comboDefault, m_bYes);
		break;
	case IDCANCEL:
		m_pDlgParent->UpdateButtonMap(
			m_strCancel, IDCANCEL, &m_comboDefault, m_bCancel);
		break;
	case IDNO:
		m_pDlgParent->UpdateButtonMap(
			m_strNo, IDNO, &m_comboDefault, m_bNo);
		break;
	case IDRETRY:
		m_pDlgParent->UpdateButtonMap(
			m_strRetry, IDRETRY, &m_comboDefault, m_bRetry);
		break;
	case IDCLOSE:
		m_pDlgParent->UpdateButtonMap(
			m_strClose, IDCLOSE, &m_comboDefault, m_bClose);
		break;
	}
}

void CTaskPageButtons::OnChkOk()
{
	UpdateData();
	AddCommonButton(IDOK);
}

void CTaskPageButtons::OnChkYes()
{
	UpdateData();
	AddCommonButton(IDYES);
}

void CTaskPageButtons::OnChkCancel()
{
	UpdateData();
	AddCommonButton(IDCANCEL);
}

void CTaskPageButtons::OnChkNo()
{
	UpdateData();
	AddCommonButton(IDNO);
}

void CTaskPageButtons::OnChkRetry()
{
	UpdateData();
	AddCommonButton(IDRETRY);
}

void CTaskPageButtons::OnChkClose()
{
	UpdateData();
	AddCommonButton(IDCLOSE);
}

void CTaskPageButtons::OnUpdateData()
{
	UpdateData();

	GetDlgItem(IDC_CHK_SHOWICONS)->EnableWindow(m_bUseLinks);
}

void CTaskPageButtons::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	CTaskEditButtonDlg dlg(&m_comboDefault, FALSE, m_pDlgParent);
	if (dlg.DoModal() == IDOK)
	{
		CString strID;
		strID.Format(_T("%d"), dlg.m_nID);
		int nIndex = m_listCustom.GetItemCount();
		m_listCustom.InsertItem(nIndex, dlg.m_strText);
		m_listCustom.SetItemText(nIndex, 1, strID);
	}
	m_listCustom.SetFocus();
}

void CTaskPageButtons::OnBtnEdit() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listCustom.GetFirstSelectedItemPosition();
	if (pos)
	{
		CTaskEditButtonDlg dlg(&m_comboDefault, TRUE, m_pDlgParent);

		int nIndex = m_listCustom.GetNextSelectedItem(pos);

		dlg.m_strText = m_listCustom.GetItemText(nIndex, 0);
		dlg.m_nID = _ttoi(m_listCustom.GetItemText(nIndex, 1));

		if (dlg.DoModal() == IDOK)
		{
			CString strID;
			strID.Format(_T("%d"), dlg.m_nID);
			m_listCustom.SetItemText(nIndex, 0, dlg.m_strText);
			m_listCustom.SetItemText(nIndex, 1, strID);
		}
	}
	m_listCustom.SetFocus();
}

void CTaskPageButtons::OnBtnRemove() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listCustom.GetFirstSelectedItemPosition();
	if (pos)
	{
		if (::MessageBox(m_hWnd, _T("Are you sure you want to delete this item?"),
			_T("Confirm Delete"), MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			int nIndex = m_listCustom.GetNextSelectedItem(pos);
			if (nIndex != LB_ERR)
			{
				int nID = _ttoi(m_listCustom.GetItemText(nIndex, 1));
				CString strText = m_listCustom.GetItemText(nIndex, 0);

				m_pDlgParent->UpdateButtonMap(
					strText, nID, &m_comboDefault, FALSE);

				m_listCustom.DeleteItem(nIndex);
			}
		}
	}
	m_listCustom.SetFocus();
}

void CTaskPageButtons::OnItemChangedListCustom(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	EnableButtons();
	
	*pResult = 0;
}

void CTaskPageButtons::InsertItem(CString strText, UINT nID)
{
	CString strID;
	strID.Format(_T("%d"), nID);

	int nIndex = m_listCustom.GetItemCount();
	m_listCustom.InsertItem(nIndex, strText);
	m_listCustom.SetItemText(nIndex, 1, strID);

	m_pDlgParent->UpdateButtonMap(
		strText, nID, &m_comboDefault, TRUE);
}

void CTaskPageButtons::InsertItem(UINT nString, UINT nID)
{
	CString strText;
	strText.LoadString(nString);
	InsertItem(strText, nID);
}

BOOL CTaskPageButtons::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_pDlgParent = DYNAMIC_DOWNCAST(CTaskSheetProperties, GetParent());
	ASSERT_VALID(m_pDlgParent);

	m_listCustom.InsertColumn(0, _T("Text"),  LVCFMT_LEFT, 160);
	m_listCustom.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 60);

	ListView_SetExtendedListViewStyle(
		m_listCustom.m_hWnd, LVS_EX_FULLROWSELECT);

	LoadState();

	GetDlgItem(IDC_CHK_SHOWICONS)->EnableWindow(m_bUseLinks);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTaskPageButtons::OnSetActive()
{
	if (!CPropertyPage::OnSetActive())
		return FALSE;

	EnableButtons();

	return TRUE;
}

void CTaskPageButtons::EnableButtons()
{
	if (::IsWindow(m_listCustom.m_hWnd))
	{
		BOOL bEnable = (m_listCustom.GetSelectedCount() > 0);
		m_btnEdit.EnableWindow(bEnable);
		m_btnRemove.EnableWindow(bEnable);
	}
}

#define REG_SETTINGS	_T("Settings\\Buttons")

void CTaskPageButtons::LoadState()
{
	m_bOk = theApp.GetProfileInt(REG_SETTINGS, m_strOk, FALSE);
	AddCommonButton(IDOK);

	m_bYes = theApp.GetProfileInt(REG_SETTINGS, m_strYes, FALSE);
	AddCommonButton(IDYES);

	m_bNo = theApp.GetProfileInt(REG_SETTINGS, m_strNo, FALSE);
	AddCommonButton(IDNO);

	m_bCancel = theApp.GetProfileInt(REG_SETTINGS, m_strCancel, FALSE);
	AddCommonButton(IDCANCEL);

	m_bRetry = theApp.GetProfileInt(REG_SETTINGS, m_strRetry, FALSE);
	AddCommonButton(IDRETRY);

	m_bClose = theApp.GetProfileInt(REG_SETTINGS, m_strClose, FALSE);
	AddCommonButton(IDCLOSE);

	m_bUseLinks = theApp.GetProfileInt(REG_SETTINGS, _T("UseLinks"), FALSE);
	m_bShowIcons = theApp.GetProfileInt(REG_SETTINGS, _T("ShowIcons"), TRUE);

	if (::IsWindow(m_listCustom.m_hWnd))
	{
		int nCount = theApp.GetProfileInt(REG_SETTINGS, _T("Count"), 0);
		for (int i = 0; i < nCount; ++i)
		{
			CString strSection;
			strSection.Format(_T("UserItem_%d"), i);

			CString strBuffer = theApp.GetProfileString(REG_SETTINGS, strSection);

			CString strText;
			AfxExtractSubString(strText, strBuffer, 0, '~');

			CString strValue;
			AfxExtractSubString(strValue, strBuffer, 1, '~');

			InsertItem(strText, _ttoi(strValue));
		}
	}

	UpdateData(FALSE);
}

void CTaskPageButtons::SaveState()
{
	UpdateData();

	theApp.WriteProfileInt(REG_SETTINGS, m_strOk, m_bOk);
	theApp.WriteProfileInt(REG_SETTINGS, m_strYes, m_bYes);
	theApp.WriteProfileInt(REG_SETTINGS, m_strNo, m_bNo);
	theApp.WriteProfileInt(REG_SETTINGS, m_strCancel, m_bCancel);
	theApp.WriteProfileInt(REG_SETTINGS, m_strRetry, m_bRetry);
	theApp.WriteProfileInt(REG_SETTINGS, m_strClose, m_bClose);
	theApp.WriteProfileInt(REG_SETTINGS, _T("UseLinks"), m_bUseLinks);
	theApp.WriteProfileInt(REG_SETTINGS, _T("ShowIcons"), m_bShowIcons);

	if (::IsWindow(m_listCustom.m_hWnd))
	{
		int nCount = m_listCustom.GetItemCount();
		theApp.WriteProfileInt(REG_SETTINGS, _T("Count"), nCount);

		for (int i = 0; i < nCount; ++i)
		{
			CString strSection;
			strSection.Format(_T("UserItem_%d"), i);

			CString strText = m_listCustom.GetItemText(i,0);
			CString strValue = m_listCustom.GetItemText(i,1);

			CString strBuffer;
			strBuffer.Format(_T("%s~%s"), strText, strValue);
			theApp.WriteProfileString(REG_SETTINGS, strSection, strBuffer);
		}
	}
}

void CTaskPageButtons::OnDestroy() 
{
	SaveState();
	CPropertyPage::OnDestroy();
}

