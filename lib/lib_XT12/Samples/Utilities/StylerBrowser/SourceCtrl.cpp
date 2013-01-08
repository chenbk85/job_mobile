// SourceCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "styler.h"
#include "SourceCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSourceCtrl

CSourceCtrl::CSourceCtrl()
{
	LOGFONT lfIcon;
	VERIFY( ::SystemParametersInfo( SPI_GETICONTITLELOGFONT, sizeof( lfIcon ), &lfIcon, 0 ) );
	VERIFY( m_fntText.CreateFontIndirect(&lfIcon  ) );

}

CSourceCtrl::~CSourceCtrl()
{
}

BOOL CSourceCtrl::Create(CWnd* pParent)
{
	if (!CRichEditCtrl::Create(WS_VSCROLL | WS_HSCROLL| WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL | ES_SAVESEL | ES_READONLY , 
		CRect(0,0,0,0), pParent, 1))
	{
		return FALSE;
	}

	SetBackgroundColor(FALSE, GetSysColor(COLOR_3DFACE));	
	SetFont(&m_fntText, FALSE);

	return TRUE;



}

void CSourceCtrl::Refresh(CHtmlView* pView, BOOL /*bForce*/)
{
	USES_CONVERSION;
	HRESULT hr;

	LPDISPATCH lpDisp = pView->GetHtmlDocument();
	if (!lpDisp)
		return;

	// Verify that what we get is a pointer to a IHTMLDocument2 
	// interface. To be sure, let's query for 
	// the IHTMLDocument2 interface (through smart pointers)
	CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> spHTML(lpDisp);

	// The previous step is sufficient to keep Explorer aside
	// without an explicit check against the loader module

	// Extract the source code of the document
	CComPtr<IHTMLElement> m_pBody = NULL;

	if (spHTML)
	{
	

		// Get the BODY object
		hr = spHTML->get_body(&m_pBody); 
		if (FAILED(hr) || !m_pBody)
			return;

		// Get the HTML text
		BSTR bstrHTMLText;
		hr = m_pBody->get_outerHTML(&bstrHTMLText); 
		if (FAILED(hr))
			return;

		// Convert the text from Unicode to ANSI
		int nLength = SysStringLen(bstrHTMLText);

		LPTSTR psz = new TCHAR[nLength + 1];
		lstrcpy(psz, OLE2T(bstrHTMLText));
		
		SetTextFormat(psz);

		delete [] psz;
	}
	else	// The document isn't a HTML page
	{
	
	}
	lpDisp->Release();
}

void AddLine(CStringArray& sa, LPTSTR pStart, int nCount)
{
	CString str;
	LPTSTR pLine = str.GetBufferSetLength(nCount);
	STRNCPY_S(pLine, nCount + 1, pStart, nCount);
	pLine[nCount] = 0;
	str.TrimLeft();
	if (str != "")
		sa.Add(str);			
}

CString GetTag(CString str)
{
	str.TrimLeft();
	if (str.IsEmpty() || str[0] != _T('<')) 
		return _T("");

	int nStart = 1;
	while (nStart < str.GetLength() && str[nStart] == ' ') nStart++;
	
	int nEnd = str.Find(' ', nStart);	
	int nTag = str.Find('>', nStart);
	if (nEnd != -1) 
	{		
		if (nTag != -1)
			nEnd = min(nEnd, nTag);
	} else nEnd = nTag;
	
	if (nEnd == -1)
	{
		return _T("");
	}

	CString strTag  = str.Mid(nStart, nEnd - nStart);


	return strTag;
}

void Format(CStringArray& sa)
{
	for (int i = 0; i < sa.GetSize(); i++)	
	{
		CString& strNext = sa[i];
		CString strTag = GetTag(strNext);

		if (!strTag.IsEmpty() && strTag[0] == '/')
		{
			CString strClose = strTag.Right(strTag.GetLength() - 1);
			int nRefCount = 1;
			int k = i - 1;
			
			while (k >= 0)
			{
				CString& str = sa[k];
				CString strOpen = GetTag(str);
				if (strOpen == strTag) nRefCount ++;
				if (strOpen == strClose)
				{
					nRefCount --;
					if (nRefCount == 0) break;
				}

				

				k--;
			}
			if (k>= 0)
			{
				
				while (++k < i)
				{
					sa[k] = _T("  ") + sa[k];					
				}
			}
		}
	}
}

void CSourceCtrl::SetTextFormat(LPTSTR pText)
{
	CStringArray sa;

	CString str;
	
	TCHAR* pChar = pText;
	TCHAR* pStart = pText;
	while (*pChar)
	{
		if (*pChar == '<' && pStart != pChar)
		{
			AddLine(sa, pStart, (int)(pChar - pStart));			

			pStart = pChar;
			
		} else
		if (*pChar == '>')
		{
			AddLine(sa, pStart, int(pChar - pStart + 1));

			pStart = pChar + 1;
		}
		if (*pChar == '\n' || *pChar == '\r')
			*pChar = ' ';

		pChar ++;
	}

	if (pChar!=pStart)
	{
		AddLine(sa, pStart, int(pChar - pStart));
	}

	Format(sa);
	

	LockWindowUpdate();

	SetSel(0, -1);
	Clear();
	
	CString strBody;
	for (int i = 0; i < sa.GetSize(); i++)	
	{
		strBody = sa[i] + _T("\r\n");		

		
		if (strBody.Find('<') == -1)
		{
			CHARFORMAT cf;
			cf.cbSize = sizeof CHARFORMAT;
			cf.dwMask = CFM_BOLD;
			cf.dwEffects = CFE_BOLD;
			SetSelectionCharFormat (cf);		

		}
		ReplaceSel(strBody);

	}

	UnlockWindowUpdate();
}



BEGIN_MESSAGE_MAP(CSourceCtrl, CRichEditCtrl)
	//{{AFX_MSG_MAP(CSourceCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSourceCtrl message handlers
