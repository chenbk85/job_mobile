// TabEdit.cpp : implementation file
//

#include "StdAfx.h"
#include "Resource.h"
#include "TabEdit.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabEdit

CTabEdit::CTabEdit()
{
}

CTabEdit::~CTabEdit()
{
}

BEGIN_MESSAGE_MAP(CTabEdit, CEdit)
	//{{AFX_MSG_MAP(CTabEdit)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabEdit message handlers

BOOL CTabEdit::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CEdit::PreCreateWindow(cs))
		return FALSE;

	cs.style |= ES_MULTILINE|WS_HSCROLL|WS_VSCROLL;

	return TRUE;
}

int CTabEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Register as a drop target
	m_dropTarget.Register(this);
	DragAcceptFiles();
	
	CreateFont();

	return 0;
}

void CTabEdit::CreateFont()
{
	LOGFONT lf;
	XTAuxData().font.GetLogFont(&lf);
	STRCPY_S(lf.lfFaceName, LF_FACESIZE, _T("Courier New"));
	m_font.CreateFontIndirect(&lf);

	SetFont(&m_font);
}

void CTabEdit::OnContextMenu(CWnd*, CPoint point)
{
	if (point.x == -1 && point.y == -1)
	{
		//keystroke invocation
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		
		point = rect.TopLeft();
		point.Offset(5, 5);
	}
	
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_EDIT));
	
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;
	
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

void CTabEdit::OnEditUndo() 
{
	Undo();
}

void CTabEdit::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CanUndo());
}

void CTabEdit::OnEditCut() 
{
	Cut();
}

void CTabEdit::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(SelectionMade());
}

void CTabEdit::OnEditCopy() 
{
	Copy();
}

void CTabEdit::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(SelectionMade());
}

void CTabEdit::OnEditPaste() 
{
	Paste();
}

void CTabEdit::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CanPaste());
}

void CTabEdit::OnEditClear() 
{
	Clear();
}

void CTabEdit::OnUpdateEditClear(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(SelectionMade());
}

void CTabEdit::OnEditSelectAll() 
{
	SetSel(0, -1);
}

void CTabEdit::OnUpdateEditSelectAll(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetWindowTextLength() > 0);
}

BOOL CTabEdit::CanPaste()
{
	return ::IsClipboardFormatAvailable(CF_TEXT);
}

BOOL CTabEdit::SelectionMade()
{
	int nStartChar, nEndChar;
	GetSel( nStartChar, nEndChar );
	return (nStartChar < nEndChar);
}

BOOL CTabEdit::OnEraseBkgnd(CDC* pDC) 
{
	UNREFERENCED_PARAMETER(pDC);
	return TRUE;
}

void CTabEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Get the client rect.
	CRect r;
	GetClientRect(&r);

	// Paint to a memory device context to help
	// eliminate screen flicker.
	CXTMemDC memDC(&dc, r, GetXtremeColor(COLOR_WINDOW));

	// Now let the window do its default painting...
	CEdit::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );
}

void CTabEdit::OnDropFiles(HDROP hDropInfo) 
{
    SetWindowText(_T(""));

	TCHAR szFileName[MAX_PATH];
    ::DragQueryFile(hDropInfo,0,szFileName,MAX_PATH);

	if (_taccess(szFileName, 0) != -1)
    {
        CStdioFile file(szFileName, CFile::modeRead | CFile::typeText);
        
	    CString strBuffer1;
	    file.ReadString( strBuffer1 );

	    CString strBuffer2;
	    while (file.ReadString(strBuffer1))
	    {
		    strBuffer2 += (strBuffer1 + _T("\r\n"));
	    }
        
        file.Close();

	    if ( strBuffer2.GetLength( ) )
	    {
            SetWindowText(strBuffer2);
	    }
	}
    
	CEdit::OnDropFiles(hDropInfo);
}
