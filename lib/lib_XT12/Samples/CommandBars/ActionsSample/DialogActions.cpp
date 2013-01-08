// DialogActions.cpp : implementation file
//

#include "stdafx.h"
#include "ActionsSample.h"
#include "DialogActions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogActions dialog


CDialogActions::CDialogActions(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogActions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogActions)
	m_bChecked = FALSE;
	m_bEnabled = FALSE;
	m_bVisible = FALSE;
	m_strCaption = _T("");
	m_strDescription = _T("");
	m_strTooltip = _T("");
	//}}AFX_DATA_INIT
	
	m_pActions = 0;
}


void CDialogActions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogActions)
	DDX_Control(pDX, IDC_COMBO_ACTIONS, m_lstActions);
	DDX_Check(pDX, IDC_CHECK_CHECKED, m_bChecked);
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_bEnabled);
	DDX_Check(pDX, IDC_CHECK_VISIBLE, m_bVisible);
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_strCaption);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_strDescription);
	DDX_Text(pDX, IDC_EDIT_TOOLTIP, m_strTooltip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogActions, CDialog)
	//{{AFX_MSG_MAP(CDialogActions)
	ON_CBN_SELCHANGE(IDC_COMBO_ACTIONS, OnComboActionsSelChanged)
	ON_BN_CLICKED(IDC_CHECK_VISIBLE, OnCheckVisible)
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	ON_BN_CLICKED(IDC_CHECK_CHECKED, OnCheckChecked)
	ON_EN_CHANGE(IDC_EDIT_CAPTION, OnChangeEditCaption)
	ON_EN_CHANGE(IDC_EDIT_TOOLTIP, OnChangeEditTooltip)
	ON_EN_CHANGE(IDC_EDIT_DESCRIPTION, OnChangeEditDescription)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogActions message handlers

void CDialogActions::OnOK() 
{
}

void CDialogActions::OnCancel() 
{
}

BOOL CDialogActions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CXTPFrameWnd* pFrame = (CXTPFrameWnd*)GetParentFrame();
	CXTPCommandBars* pCommandBars = pFrame->GetCommandBars();

	m_pActions = pCommandBars->GetActions();

	FillActionsCombos();
	OnComboActionsSelChanged();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogActions::OnComboActionsSelChanged() 
{
	int nSel = m_lstActions.GetCurSel();

	GetDlgItem(IDC_CHECK_VISIBLE)->EnableWindow(nSel != CB_ERR);
	GetDlgItem(IDC_CHECK_ENABLED)->EnableWindow(nSel != CB_ERR);
	GetDlgItem(IDC_CHECK_CHECKED)->EnableWindow(nSel != CB_ERR);
	GetDlgItem(IDC_EDIT_CAPTION)->EnableWindow(nSel != CB_ERR);
	GetDlgItem(IDC_EDIT_TOOLTIP)->EnableWindow(nSel != CB_ERR);
	GetDlgItem(IDC_EDIT_DESCRIPTION)->EnableWindow(nSel != CB_ERR);	

	if (nSel == CB_ERR)
		return;

	CXTPControlAction* pAction = (CXTPControlAction*)m_lstActions.GetItemData(nSel);

	m_bVisible = pAction->IsVisible();
	m_bEnabled = pAction->GetEnabled();
	m_bChecked = pAction->GetChecked();

	m_strCaption = pAction->GetCaption();
	m_strTooltip = pAction->GetTooltip();
	m_strDescription = pAction->GetDescription();

	UpdateData(FALSE);

}

void CDialogActions::FillActionsCombos()
{
	for (int i = 0; i < m_pActions->GetCount(); i++)
	{
		CXTPControlAction* pAction = m_pActions->GetAt(i);
		
		CString strCaption;
		strCaption.Format(_T("%i - %s"), pAction->GetID(), (LPCTSTR)pAction->GetCaption());

		int nIndex = m_lstActions.AddString(strCaption);
		m_lstActions.SetItemData(nIndex, (DWORD_PTR)pAction);

		ASSERT(m_pActions->FindAction(pAction->GetID()));
	}
}

void CDialogActions::OnCheckVisible() 
{
	UpdateData();
	CXTPControlAction* pAction = (CXTPControlAction*)m_lstActions.GetItemData(m_lstActions.GetCurSel());	

	pAction->SetVisible(m_bVisible);
}

void CDialogActions::OnCheckEnabled() 
{
	UpdateData();
	CXTPControlAction* pAction = (CXTPControlAction*)m_lstActions.GetItemData(m_lstActions.GetCurSel());	

	pAction->SetEnabled(m_bEnabled);
}

void CDialogActions::OnCheckChecked() 
{
	UpdateData();
	CXTPControlAction* pAction = (CXTPControlAction*)m_lstActions.GetItemData(m_lstActions.GetCurSel());	

	pAction->SetChecked(m_bChecked);
}

void CDialogActions::OnChangeEditCaption() 
{
	UpdateData();
	CXTPControlAction* pAction = (CXTPControlAction*)m_lstActions.GetItemData(m_lstActions.GetCurSel());	

	pAction->SetCaption(m_strCaption);
}

void CDialogActions::OnChangeEditTooltip() 
{
	UpdateData();
	CXTPControlAction* pAction = (CXTPControlAction*)m_lstActions.GetItemData(m_lstActions.GetCurSel());	

	pAction->SetTooltip(m_strTooltip);	
}

void CDialogActions::OnChangeEditDescription() 
{
	UpdateData();
	CXTPControlAction* pAction = (CXTPControlAction*)m_lstActions.GetItemData(m_lstActions.GetCurSel());	

	pAction->SetDescription(m_strDescription);
}

void CDialogActions::OnButtonLoad() 
{
	CString strFilter = _T("XML Document(*.xml)|*.xml|All files (*.*)|*.*||");
	CFileDialog fd(TRUE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
	if (fd.DoModal() == IDOK)
	{
		CXTPPropExchangeXMLNode px(TRUE, 0, _T("Settings"));
		if (!px.LoadFromFile(fd.GetFileName()))
			return;

		CXTPFrameWnd* pFrame = (CXTPFrameWnd*)GetParentFrame();	
		CXTPCommandBars* pCommandBars = pFrame->GetCommandBars();

		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param;
		param.bSaveOriginalControls = FALSE;
		param.bSerializeControls = FALSE;
		param.bSerializeOptions = FALSE;
		param.bSerializeLayout = FALSE;
		param.bSerializeActions = TRUE;

		pCommandBars->DoPropExchange(&px, &param);

		OnComboActionsSelChanged();

		pCommandBars->RedrawCommandBars();
	}	
}

void CDialogActions::OnButtonSave() 
{
	CString strFilter = _T("XML Document(*.xml)|*.xml|All files (*.*)|*.*||");
	CFileDialog fd(FALSE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
	if (fd.DoModal() == IDOK)
	{
		CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));

		CXTPFrameWnd* pFrame = (CXTPFrameWnd*)GetParentFrame();	
		CXTPCommandBars* pCommandBars = pFrame->GetCommandBars();

		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param;
		param.bSaveOriginalControls = FALSE;
		param.bSerializeControls = FALSE;
		param.bSerializeOptions = FALSE;
		param.bSerializeLayout = FALSE;
		param.bSerializeActions = TRUE;

		pCommandBars->DoPropExchange(&px, &param);
		
		px.SaveToFile(fd.GetFileName());
		
	}
}
