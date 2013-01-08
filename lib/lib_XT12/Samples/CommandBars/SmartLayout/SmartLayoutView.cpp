// SmartLayoutView.cpp : implementation of the CSmartLayoutView class
//

#include "stdafx.h"
#include "SmartLayout.h"

#include "SmartLayoutDoc.h"
#include "CntrItem.h"
#include "SmartLayoutView.h"

#include "ControlSelector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutView

IMPLEMENT_DYNCREATE(CSmartLayoutView, CRichEditView)

BEGIN_MESSAGE_MAP(CSmartLayoutView, CRichEditView)
	//{{AFX_MSG_MAP(CSmartLayoutView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)

	ON_COMMAND(ID_CHAR_BOLD, OnCharBold)
	ON_UPDATE_COMMAND_UI(ID_CHAR_BOLD, OnUpdateCharBold)
	ON_COMMAND(ID_CHAR_ITALIC, OnCharItalic)
	ON_UPDATE_COMMAND_UI(ID_CHAR_ITALIC, OnUpdateCharItalic)
	ON_COMMAND(ID_CHAR_UNDERLINE, OnCharUnderline)
	ON_UPDATE_COMMAND_UI(ID_CHAR_UNDERLINE, OnUpdateCharUnderline)
	ON_COMMAND(ID_PARA_CENTER, OnParaCenter)
	ON_UPDATE_COMMAND_UI(ID_PARA_CENTER, OnUpdateParaCenter)
	ON_COMMAND(ID_PARA_LEFT, OnParaLeft)
	ON_UPDATE_COMMAND_UI(ID_PARA_LEFT, OnUpdateParaLeft)
	ON_COMMAND(ID_PARA_RIGHT, OnParaRight)
	ON_UPDATE_COMMAND_UI(ID_PARA_RIGHT, OnUpdateParaRight)

	ON_COMMAND(ID_INSERT_BULLET, CRichEditView::OnBullet)
	ON_UPDATE_COMMAND_UI(ID_INSERT_BULLET, CRichEditView::OnUpdateBullet)


	ON_NOTIFY(XTP_FN_GETFORMAT, ID_COMBO_SIZE, OnGetCharFormat)
	ON_NOTIFY(XTP_FN_SETFORMAT, ID_COMBO_SIZE, OnSetCharFormat)
	ON_UPDATE_COMMAND_UI(ID_COMBO_SIZE, OnUpdateComboSize)

	ON_NOTIFY(XTP_FN_SETFORMAT, ID_COMBO_FONT, OnSetCharFormat)
	ON_UPDATE_COMMAND_UI(ID_COMBO_FONT, OnUpdateComboFont)

	ON_XTP_EXECUTE(ID_SELECTOR_TEXT, OnSelectorText)
	ON_UPDATE_COMMAND_UI(ID_SELECTOR_TEXT, OnUpdateSelectorText)

	ON_COMMAND(ID_BUTTON_TEXT, OnButtonText)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TEXT, OnUpdateText)

	ON_COMMAND(XTP_IDS_AUTOMATIC, OnTextAuto)
	ON_UPDATE_COMMAND_UI(XTP_IDS_AUTOMATIC, OnUpdateTextAuto)

	ON_COMMAND(XTP_IDS_MORE_COLORS, OnTextMore)

	ON_XTP_EXECUTE(ID_EDIT_UNDO, OnEditUndo)
	ON_NOTIFY(XTP_LBN_SELCHANGE, ID_EDIT_UNDO, OnListBoxControlSelChange)
	ON_NOTIFY(XTP_LBN_POPUP, ID_EDIT_UNDO, OnListBoxControlPoup)

	ON_NOTIFY(XTP_SLN_SELCHANGE, ID_INSERT_COLUMNS, OnColumnsSelChange)
	ON_NOTIFY(XTP_SLN_SELCHANGE, ID_INSERT_TABLE, OnTableSelChange)

	ON_XTP_EXECUTE(ID_INSERT_TABLE, OnInsertTable)
	ON_XTP_EXECUTE(ID_INSERT_COLUMNS, OnInsertColumns)
	ON_UPDATE_COMMAND_UI(ID_INSERT_TABLE, OnEnableCommand)
	ON_UPDATE_COMMAND_UI(ID_INSERT_COLUMNS, OnEnableCommand)

	ON_COMMAND_RANGE(ID_BDR_OUTSIDE, ID_BDR_INSIDE_VERT, OnBorders)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BDR_OUTSIDE, ID_BDR_INSIDE_VERT, OnUpdateBorders)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutView construction/destruction

CSmartLayoutView::CSmartLayoutView()
{
	m_clr = 0;
	m_dwBorders = 0;

}

CSmartLayoutView::~CSmartLayoutView()
{
}

BOOL CSmartLayoutView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CSmartLayoutView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutView printing

BOOL CSmartLayoutView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CSmartLayoutView::OnDestroy()
{
	CRichEditView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutView diagnostics

#ifdef _DEBUG
void CSmartLayoutView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CSmartLayoutView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CSmartLayoutDoc* CSmartLayoutView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSmartLayoutDoc)));
	return (CSmartLayoutDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutView message handlers


void CSmartLayoutView::OnGetCharFormat(NMHDR* pNMHDR, LRESULT* pRes)
{
	ASSERT(pNMHDR != NULL);
	ASSERT(pRes != NULL);
	((NMXTPCHARHDR*)pNMHDR)->cf = GetCharFormatSelection();
	*pRes = 1;
}

void CSmartLayoutView::OnSetCharFormat(NMHDR* pNMHDR, LRESULT* pRes)
{
	ASSERT(pNMHDR != NULL);
	ASSERT(pRes != NULL);

#if (_MSC_VER < 1300)
	CHARFORMAT& cf = ((NMXTPCHARHDR*)pNMHDR)->cf;
#else
	CHARFORMAT2 cf;
	MEMCPY_S(&cf, &((NMXTPCHARHDR*)pNMHDR)->cf, sizeof(((NMXTPCHARHDR*)pNMHDR)->cf));
#endif
	SetCharFormat(cf);
	*pRes = 1;
}

void CSmartLayoutView::OnUpdateComboFont(CCmdUI* pCmd)
{
	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmd->m_pOther;
	if (pToolBar)
	{
		CXTPControlFontComboBox* pFontCombo = (CXTPControlFontComboBox*)pToolBar->GetControls()->GetAt(pCmd->m_nIndex);

		if (pFontCombo->GetType() == xtpControlComboBox)
		{
			pFontCombo->SetCharFormat((CHARFORMAT&)GetCharFormatSelection());
		}
	}
	pCmd->Enable(TRUE);
}

void CSmartLayoutView::OnUpdateComboSize(CCmdUI* pCmd)
{
	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmd->m_pOther;
	if (pToolBar)
	{
		CXTPControlSizeComboBox* pSizeCombo = (CXTPControlSizeComboBox*)pToolBar->GetControls()->GetAt(pCmd->m_nIndex);

		if (pSizeCombo->GetType() == xtpControlComboBox)
		{
			CHARFORMAT& cf = GetCharFormatSelection();
			pSizeCombo->SetTwipSize( (cf.dwMask & CFM_SIZE) ? cf.yHeight : -1);
		}
	}
	pCmd->Enable(TRUE);
}



void CSmartLayoutView::OnUpdateSelectorText(CCmdUI* pCmd)
{
	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmd->m_pOther;
	if (pToolBar)
	{
		CHARFORMAT& cfm = GetCharFormatSelection( );
		CXTPControlColorSelector* pSelector = (CXTPControlColorSelector*)pToolBar->GetControls()->GetAt(pCmd->m_nIndex);
		pSelector->SetColor(cfm.dwEffects & CFE_AUTOCOLOR? -1: cfm.crTextColor);
	}
	pCmd->Enable(TRUE);
}

void CSmartLayoutView::OnButtonText()
{
	CHARFORMAT& cfm = GetCharFormatSelection( );
	cfm.dwMask |= CFM_COLOR;
	cfm.dwEffects &= ~CFE_AUTOCOLOR ;
	cfm.crTextColor = m_clr;
	GetRichEditCtrl().SetSelectionCharFormat(cfm);

}
void CSmartLayoutView::OnSelectorText(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlColorSelector* pControl = (CXTPControlColorSelector*)tagNMCONTROL->pControl;
	m_clr = pControl->GetColor();

	OnButtonText();

	*pResult = 1;
}


void CSmartLayoutView::OnUpdateText(CCmdUI* pCmd)
{

	CXTPCommandBar* pToolBar = (CXTPToolBar*)pCmd->m_pOther;
	if (pToolBar)
	{
		CXTPControlPopupColor* pPopup = (CXTPControlPopupColor*)pToolBar->GetControls()->GetAt(pCmd->m_nIndex);
		pPopup->SetColor(m_clr);
	}

	pCmd->Enable(TRUE);
}



void CSmartLayoutView::OnTextAuto()
{
	CHARFORMAT& cfm = GetCharFormatSelection( );
	cfm.dwMask |= CFM_COLOR;
	cfm.dwEffects |= CFE_AUTOCOLOR ;
	GetRichEditCtrl().SetSelectionCharFormat(cfm);
	m_clr = GetSysColor(COLOR_BTNTEXT);
}

void CSmartLayoutView::OnUpdateTextAuto(CCmdUI* pCmd)
{
	CHARFORMAT& cfm = GetCharFormatSelection( );
	pCmd->SetCheck(cfm.dwEffects & CFE_AUTOCOLOR? TRUE: FALSE);
}



void CSmartLayoutView::OnTextMore()
{
	CColorDialog cd(m_clr);
	if (cd.DoModal())
	{
		m_clr = cd.GetColor();
		OnButtonText();
	}

}



void CSmartLayoutView::OnEditUndo(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (((NMXTPCONTROL*)pNMHDR)->pControl->GetType() == xtpControlSplitButtonPopup)
	{
		CRichEditView::OnEditUndo();

		*pResult = 1; // Handled;
	}

	CXTPControlListBox* pControlListBox = DYNAMIC_DOWNCAST(CXTPControlListBox, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlListBox)
	{
		CString str;
		str.Format(_T("Undo last %i actions"), pControlListBox->GetListCtrl()->GetSelCount());

		AfxMessageBox(str);

		*pResult = 1; // Handled;
	}
}

CXTPControlStatic* CSmartLayoutView::FindInfoControl(CXTPControl* pControl)
{
	CXTPCommandBar* pCommandBar = pControl->GetParent();

	for (int i = 0; i < pCommandBar->GetControls()->GetCount(); i++)
	{
		CXTPControlStatic* pControlStatic = DYNAMIC_DOWNCAST(CXTPControlStatic, pCommandBar->GetControl(i));
		if (pControlStatic && pControlStatic->GetID() == pControl->GetID())
		{
			return pControlStatic;
		}

	}
	return NULL;
}


void CSmartLayoutView::OnListBoxControlSelChange(NMHDR* pNMHDR, LRESULT* pRes)
{
	ASSERT(pNMHDR != NULL);
	ASSERT(pRes != NULL);

	CXTPControlListBox* pControlListBox = DYNAMIC_DOWNCAST(CXTPControlListBox, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlListBox)
	{

		CXTPControlStatic* pInfo = FindInfoControl(pControlListBox);
		if (pInfo)
		{
			CString str;
			str.Format(_T("Undo %i Actions"), pControlListBox->GetListCtrl()->GetSelCount());
			pInfo->SetCaption(str);
			pInfo->DelayRedrawParent();
		}



		*pRes = 1;
	}
}

void CSmartLayoutView::OnListBoxControlPoup(NMHDR* pNMHDR, LRESULT* pRes)
{
	ASSERT(pNMHDR != NULL);
	ASSERT(pRes != NULL);
	CXTPControlListBox* pControlListBox = DYNAMIC_DOWNCAST(CXTPControlListBox, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlListBox)
	{
		CListBox* pListBox = pControlListBox->GetListCtrl();
		pListBox->ResetContent();

		int nCount = RAND_S() % 20 + 3;

		for (int i = 0; i < nCount; i++)
		{
			CString str;
			str.Format(_T("Undo String %i"), i + 1);
			pListBox->AddString(str);
		}

		CXTPControlStatic* pInfo = FindInfoControl(pControlListBox);
		if (pInfo)
		{
			CString str;
			pInfo->SetCaption(_T("Undo 0 Actions"));
			pInfo->DelayRedrawParent();
		}


		*pRes = 1;
	}
}



void CSmartLayoutView::OnColumnsSelChange(NMHDR* pNMHDR, LRESULT* pRes)
{
	ASSERT(pNMHDR != NULL);
	ASSERT(pRes != NULL);

	CControlColumns* pControlColumns = DYNAMIC_DOWNCAST(CControlColumns, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlColumns)
	{

		CXTPControlStatic* pInfo = FindInfoControl(pControlColumns);
		if (pInfo)
		{
			int nCount = pControlColumns->m_szItemsActive.cx;

			CString str = _T("Cancel");
			if (nCount != 0)
			{
				str.Format(_T("%i Columns"), nCount);
			}

			pInfo->SetWidth(pControlColumns->m_szItem.cx * pControlColumns->m_szItemsVisible.cx);


			pInfo->SetCaption(str);
			pInfo->DelayRedrawParent();
		}

		*pRes = 1;
	}

}
void CSmartLayoutView::OnInsertTable(NMHDR* pNMHDR, LRESULT* pResult)
{

	CControlTable* pControlTable = DYNAMIC_DOWNCAST(CControlTable, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlTable)
	{
		CSize szActive = pControlTable->m_szResult;

		CString str;
		str.Format(_T("<%i x %i Table>"), szActive.cx, szActive.cy);

		GetRichEditCtrl().ReplaceSel(str);

		*pResult = 1; // Handled;
	}
}
void CSmartLayoutView::OnInsertColumns(NMHDR* pNMHDR, LRESULT* pResult)
{

	CControlColumns* pControlColumns = DYNAMIC_DOWNCAST(CControlColumns, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlColumns)
	{
		int nCount = pControlColumns->m_szResult.cx;

		CString str;
		str.Format(_T("<%i Columns>"), nCount);

		GetRichEditCtrl().ReplaceSel(str);

		*pResult = 1; // Handled;
	}
}


void CSmartLayoutView::OnTableSelChange(NMHDR* pNMHDR, LRESULT* pRes)
{

	ASSERT(pNMHDR != NULL);
	ASSERT(pRes != NULL);

	CControlTable* pControlTable = DYNAMIC_DOWNCAST(CControlTable, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlTable)
	{

		CXTPControlStatic* pInfo = FindInfoControl(pControlTable);
		if (pInfo)
		{
			CSize szActive = pControlTable->m_szItemsActive;

			CString str = _T("Cancel");
			if (szActive != CSize(0))
			{
				str.Format(_T("%i x %i Table"), szActive.cx, szActive.cy);
			}

			pInfo->SetWidth(pControlTable->m_szItem.cx * pControlTable->m_szItemsVisible.cx);

			pInfo->SetCaption(str);
			pInfo->DelayRedrawParent();
		}

		*pRes = 1;
	}
}

enum Borders {borderTop = 1, borderLeft = 2, borderRight = 4, borderBottom = 8, borderInsideVert = 16, borderInsideHorz = 32,
	borderOutside = borderBottom | borderTop | borderLeft | borderRight,
	borderInside = borderInsideVert | borderInsideHorz,
	borderAll = borderInside | borderOutside};


void CSmartLayoutView::SwitchBorders(DWORD dwState)
{
	if (m_dwBorders & dwState) m_dwBorders &= ~dwState; else m_dwBorders |= dwState;

}


void CSmartLayoutView::OnBorders(UINT nID)
{
	switch (nID)
	{
		case ID_BDR_TOP: SwitchBorders(borderTop); break;
		case ID_BDR_LEFT: SwitchBorders(borderLeft); break;
		case ID_BDR_RIGHT: SwitchBorders(borderRight); break;
		case ID_BDR_BOTTOM: SwitchBorders(borderBottom); break;
		case ID_BDR_NONE: m_dwBorders = 0; break;
		case ID_BDR_OUTSIDE: SwitchBorders(borderOutside); break;
		case ID_BDR_ALL: SwitchBorders(borderAll); break;
		case ID_BDR_INSIDE_VERT: SwitchBorders(borderInsideVert); break;
		case ID_BDR_INSIDE_HORZ: SwitchBorders(borderInsideHorz); break;
		case ID_BDR_INSIDE: SwitchBorders(borderInside); break;
	}

}

void CSmartLayoutView::OnUpdateBorders(CCmdUI* pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
		case ID_BDR_TOP: pCmdUI->SetCheck(m_dwBorders & borderTop? TRUE: FALSE); break;
		case ID_BDR_LEFT: pCmdUI->SetCheck(m_dwBorders & borderLeft? TRUE: FALSE); break;
		case ID_BDR_RIGHT: pCmdUI->SetCheck(m_dwBorders & borderRight? TRUE: FALSE); break;
		case ID_BDR_BOTTOM: pCmdUI->SetCheck(m_dwBorders & borderBottom? TRUE: FALSE); break;
		case ID_BDR_OUTSIDE : pCmdUI->SetCheck((m_dwBorders & borderOutside) == borderOutside? TRUE: FALSE); break;
		case ID_BDR_ALL : pCmdUI->SetCheck((m_dwBorders & borderAll) == borderAll? TRUE: FALSE); break;
		case ID_BDR_INSIDE_VERT: pCmdUI->SetCheck(m_dwBorders & borderInsideVert? TRUE: FALSE); break;
		case ID_BDR_INSIDE_HORZ: pCmdUI->SetCheck(m_dwBorders & borderInsideHorz? TRUE: FALSE); break;
		case ID_BDR_INSIDE: pCmdUI->SetCheck((m_dwBorders & borderInside) == borderInside? TRUE: FALSE); break;
	}
}


void CSmartLayoutView::OnEnableCommand(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();

}
