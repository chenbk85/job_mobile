// TaskEditButtonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VistaTaskDialog.h"
#include "TaskSheetProperties.h"
#include "TaskEditButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskEditButtonDlg dialog

CTaskEditButtonDlg::CTaskEditButtonDlg(CComboBox* pWndCombo /*=NULL*/, BOOL bIsEdit /*=TRUE*/, CWnd* pParent /*=NULL*/)
	: CDialog(CTaskEditButtonDlg::IDD, pParent)
	, m_bIsEdit(bIsEdit)
	, m_pWndCombo(pWndCombo)
{
	//{{AFX_DATA_INIT(CTaskEditButtonDlg)
	m_strText = _T("");
	m_nID = 100;
	//}}AFX_DATA_INIT

	m_pDlgParent = DYNAMIC_DOWNCAST(CTaskSheetProperties, pParent);
	ASSERT_VALID(m_pDlgParent);

	//AddButton(L"OK",     IDOK);
	//AddButton(L"Cancel", IDCANCEL);
	//AddButton(L"Retry",  IDRETRY);
	//AddButton(L"Yes",    IDYES);
	//AddButton(L"No",     IDNO);
	//AddButton(L"Cancel", IDCLOSE);

	GetNextAvailableID();
}

void CTaskEditButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskEditButtonDlg)
	DDX_Control(pDX, IDC_EDIT_ID, m_wndEditCtrl);
	DDX_Control(pDX, IDC_SPIN_ID, m_wndSpinCtrl);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_wndEditText);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	DDX_Text(pDX, IDC_EDIT_ID, m_nID);
	DDV_MinMaxInt(pDX, m_nID, 100, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaskEditButtonDlg, CDialog)
	//{{AFX_MSG_MAP(CTaskEditButtonDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskEditButtonDlg message handlers

BOOL CTaskEditButtonDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_wndSpinCtrl.SetRange(100,200);

	if (!m_bIsEdit)
	{
		SetWindowText(_T("Add Button"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTaskEditButtonDlg::AddButton(PCWSTR pszText, int nButtonID)
{
	TASKDIALOG_BUTTON button;
	button.pszButtonText = pszText;
	button.nButtonID = nButtonID;
	m_arButtons.Add(button);
}

void CTaskEditButtonDlg::GetNextAvailableID(BOOL bUpdateData /*=FALSE*/)
{
	if (::IsWindow(m_pDlgParent->GetSafeHwnd()))
	{
		CButtonMap& map = m_pDlgParent->GetButtonMap();

		POSITION pos = map.GetStartPosition();
		while (pos != NULL)
		{
			int nID; CString strText;
			map.GetNextAssoc(pos, nID, strText);
			m_nID = __max(m_nID, nID);
		}

		m_nID++;
		m_strText.Format(_T("New Button %d"), m_nID);

		if (bUpdateData)
			UpdateData(FALSE);
	}
}

void CTaskEditButtonDlg::OnOK()
{
	// Don't allow buttons with ID's that are already in use.
	for (int i = 0; i <= m_arButtons.GetUpperBound(); i++)
	{
		TASKDIALOG_BUTTON& button = m_arButtons.GetAt(i);
		if (m_nID == button.nButtonID)
		{
			USES_CONVERSION;

			CString strBuffer;
			strBuffer.Format(IDS_ERROR_RESERVED,
				m_nID, W2CA(button.pszButtonText));

			AfxMessageBox(strBuffer, MB_ICONEXCLAMATION|MB_OK);
			GetNextAvailableID(TRUE);
			return;
		}
	}

	if (::IsWindow(m_pDlgParent->GetSafeHwnd()))
	{
		m_wndEditText.GetWindowText(m_strText);
		UpdateData(FALSE);

		if (m_bIsEdit)
		{
			m_pDlgParent->UpdateButtonMap(
				m_strText, m_nID, m_pWndCombo, FALSE);
		}

		UpdateData();

		if (m_pDlgParent->UpdateButtonMap(
			m_strText, m_nID, m_pWndCombo, TRUE))
		{
			CDialog::OnOK();
		}
		else
		{
			GetNextAvailableID(TRUE);
		}
	}
}

void CTaskEditButtonDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
