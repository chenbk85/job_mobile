// NotepadCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "styler.h"
#include "NotepadCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotepadCtrl

CNotepadCtrl::CNotepadCtrl() : m_dropTarget(this)
{
	LOGFONT lfIcon;
	VERIFY( ::SystemParametersInfo( SPI_GETICONTITLELOGFONT, sizeof( lfIcon ), &lfIcon, 0 ) );
	VERIFY( m_fntText.CreateFontIndirect(&lfIcon  ) );
}

CNotepadCtrl::~CNotepadCtrl()
{
}

BOOL CNotepadCtrl::Create(CWnd* pParent)
{
	if (!CXTPEdit::Create(WS_VSCROLL | WS_HSCROLL| WS_VISIBLE | WS_CHILD | 
		ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL | ES_WANTRETURN, 
		CRect(0,0,0,0), pParent, 1))
	{
		return FALSE;
	}
	
	
	CFile fNotepad;
	if (fNotepad.Open(GetModuleDir() + _T("notepad"), CFile::modeRead))
	{
		DWORD dwSize = (DWORD)fNotepad.GetLength();
		TCHAR* pBuffer = new TCHAR[dwSize / sizeof(TCHAR) + 1];
		if (pBuffer)
		{
			fNotepad.Read(pBuffer, dwSize);
			pBuffer[dwSize/sizeof(TCHAR)] = 0;
			
			SetWindowText(pBuffer);
			delete[] pBuffer;
		}
		fNotepad.Close();
	}



	m_dropTarget.Register(this);

	SetFont(&m_fntText, FALSE);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CNotepadCtrl, CXTPEdit)
	//{{AFX_MSG_MAP(CNotepadCtrl)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotepadCtrl message handlers


void CNotepadCtrl::OnDestroy() 
{

	CString str;
	CFile fNotepad;	

	if (fNotepad.Open(GetModuleDir() + _T("notepad"), CFile::modeWrite | CFile::modeCreate))
	{
		GetWindowText(str);
		if (str.GetLength()) fNotepad.Write((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		fNotepad.Close();
	}

	CEdit::OnDestroy();

}


DROPEFFECT CTxtDropTarget::OnDragScroll(CWnd* /*pWnd*/, DWORD /*dwKeyState*/, CPoint /*point*/)
{
	return DROPEFFECT_SCROLL | DROPEFFECT_COPY | DROPEFFECT_LINK;
}

DROPEFFECT CTxtDropTarget::OnDragEnter(CWnd* /*pWnd*/, COleDataObject* /*pDataObject*/, 
                                      DWORD /*dwKeyState*/, CPoint /*point*/)
{
    return DROPEFFECT_COPY;
}

void CTxtDropTarget::OnDragLeave(CWnd* /*pWnd*/)
{
}

DROPEFFECT CTxtDropTarget::OnDragOver(CWnd* /*pWnd*/, COleDataObject* /*pDataObject*/, 
                                     DWORD /*dwKeyState*/, CPoint /*point*/)
{  
	return DROPEFFECT_COPY;
}

BOOL CTxtDropTarget::OnDrop(CWnd* /*pWnd*/, COleDataObject* pDataObject,
                           DROPEFFECT /*dropEffect*/, CPoint /*point*/)
{

	try
	{
		
		HGLOBAL hData=pDataObject->GetGlobalData(CF_TEXT);
		if (hData)
		{	
			
			LPCSTR lpcszData=(LPCSTR)GlobalLock(hData);
			
			CString strText(lpcszData);
			GlobalUnlock(hData);
			
			//if it is a link?
			HGLOBAL hLinkData=pDataObject->GetGlobalData((CLIPFORMAT)RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR));
			if(hLinkData)
			{
				LPCSTR lpcszLink;
				lpcszLink=((LPCSTR)GlobalLock(hLinkData)) + 76;
				strText += "\r\n";
				strText += lpcszLink;
				strText = strText.Left(strText.GetLength()-4);
				GlobalUnlock(hLinkData);
			}
			strText += "\r\n\r\n";
			
			ASSERT(m_pParent && m_pParent->m_hWnd);
			if(m_pParent && m_pParent->m_hWnd)
			{
				int nLen = ((CEdit*)m_pParent)->GetWindowTextLength();
				((CEdit*)m_pParent)->SetSel(nLen, nLen);
				((CEdit*)m_pParent)->ReplaceSel(strText);			
			}
		}
	}
	catch(...)
	{

	}
    return TRUE;
}
