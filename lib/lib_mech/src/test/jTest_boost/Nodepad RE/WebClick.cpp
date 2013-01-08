////////////////////////////////////////////////////////////////////////////
//
// WebClick.cpp : impementation of the CWebClick class
//
// kishan@hackorama.com  http://www.hackorama.com
//
// Circa: Feb 1998
//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Overloaded constructor instatiates either
// a URL link control or a mail to control.
//
// If you  want to use the mail-to feature
// Please un-commend the code segments
// between "//for email start" and "//for  email end"
//////////////////////////////////////////////////////

#include "stdafx.h"
#include "WebClick.h"

//TO DO - INCLUDE YOUR APPLICATIONS HEADER FILE HERE
//#include "yourapp.h"
//TO DO - INCLUDE YOUR APPLICATIONS HEADER FILE HERE

//for email start
//#include "Maildlg.h"
//#include "SimpleMail.h"
//for email end

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebClick

//for web connection
CWebClick::CWebClick(TCHAR *strConnectToURL, CString szURLAnchorName)
{
	m_nOption		= 1;			//0 - email connection 1 - web link
	m_szAnchor		= szURLAnchorName;	//The displayed Anchor string
	m_strURL		= strConnectToURL;	//the URL to open or Email-id to send mail
	m_nLinkStatus	= 0;
	m_bClicked		= FALSE;
}

//for email connection
CWebClick::CWebClick(TCHAR *strEmailID, CString szMailAnchorName, CString szSubject)
{
	m_nOption		= 0;			//0 - email connection 1 - web link
	m_szAnchor		= szMailAnchorName;	//The displayed Anchor string
	m_strURL		= strEmailID;		//the URL to open or Email-id to send mail
	m_szSubject		= szSubject;

	m_nLinkStatus	= 0;
	m_bClicked		= FALSE;
}

CWebClick::~CWebClick()
{
}

BEGIN_MESSAGE_MAP(CWebClick, CButton)
	//{{AFX_MSG_MAP(CWebClick)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCRBUTTONDBLCLK()
	ON_WM_NCRBUTTONDOWN()
	ON_WM_NCRBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebClick message handlers

//for web connection
void CWebClick::OpenURL()
{
	CWaitCursor wait;
	TCHAR szCurDir[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, szCurDir);

	CWnd* pMainWind = AfxGetMainWnd();
	HWND handle = pMainWind->m_hWnd;

	HINSTANCE retHInstance  = ShellExecute(
		handle,		//HWND hwnd, 		// handle to parent window
		NULL,		//LPCTSTR lpOperation, 	// pointer to string that specifies operation to perform
		m_strURL,	//LPCTSTR lpFile,	// pointer to filename or folder name string
		NULL,		//LPCTSTR lpParameters, // pointer to string that specifies executable-file parameters
		szCurDir,	//LPCTSTR lpDirectory, 	// pointer to string that specifies default directory
		0		//INT nShowCmd 		// whether file is shown when opened
	);

	if((int)retHInstance <= 32 ){
		switch((int)retHInstance){

			case ERROR_FILE_NOT_FOUND:
				AfxMessageBox(_T("Unable to connect to the required URL"),
					MB_OK|MB_ICONERROR, 0);
			break;
			case ERROR_PATH_NOT_FOUND:
				AfxMessageBox(_T("Unable to connect to the required URL"),
					MB_OK|MB_ICONERROR, 0);
			break;
			default:
				AfxMessageBox(_T("Unable to launch the browser, Check browser")
					_T("settings.\n"), MB_OK|MB_ICONERROR, 0);
			break;
		}
	}

}

//for email start
//void CWebClick::SendMail()
//{
//	CMailDlg dlg;
//	if (dlg.DoModal() == IDOK)
//	{
//		CWaitCursor wait;
//
//		CString Address;
//		Address.Format("%s", m_strURL);		//Mail To Address
//		//CString Subject = m_szSubject;	//Mail Subject
//		CString Text ="Name:	";		//Mail Body
//		Text += dlg.m_strName + "\n\n";
//		Text += "Email:	";
//		Text += dlg.m_strMailId + "\n\n";
//		Text += dlg.m_strMessage + "\n\n";
//
//		ULONG Err = CCSendMail(Address.GetBuffer(Address.GetLength()), m_szSubject.GetBuffer(m_szSubject.GetLength()), Text.GetBuffer(m_szSubject.GetLength()));
//		if (Err != SUCCESS_SUCCESS)
//		{
//			if (AfxGetMainWnd() != NULL)
//				AfxGetMainWnd()-&gt;MessageBox("Could not send mail", "Mail Error", MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
//			else
//				::MessageBox(NULL, "Could not send mail", "Mail Error", MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
//		}
//		else
//		{
//			if (AfxGetMainWnd() != NULL)
//				AfxGetMainWnd()-&gt;MessageBox("Mail sent", "Mail status", MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
//			else
//				::MessageBox(NULL, "Mail sent", "Mail Status", MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
//		}
//	}
//
//}
//for email end

void CWebClick::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	dc.SetBkMode(TRANSPARENT);

	//select under lined font
	LOGFONT logFont;
	memset(&logFont, 0, sizeof(LOGFONT));
	logFont.lfUnderline	= TRUE;

	CFont font;
	CFont* pOldFont = NULL;
	if (font.CreateFontIndirect(&logFont))
		pOldFont = dc.SelectObject(&font);


	switch(m_nLinkStatus){
		case 0://not clicked
			dc.SetTextColor(RGB(0,0,255));
			break;
		case 1://during click
			dc.SetTextColor(RGB(255,0,0));
			break;
		case 2://clicked
			dc.SetTextColor(RGB(0,0,150));
			break;
		default://no default handling
			break;
	}

	dc.TextOut(1,1,m_szAnchor);

	//bring back original font settings
	if (pOldFont != NULL)
			dc.SelectObject(pOldFont);

}

void CWebClick::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_nLinkStatus	= 2;
	m_bClicked		= TRUE;
	OnPaint();
	RedrawWindow();
	if(m_nOption)
		OpenURL();
	//for email start
	//else
        //	SendMail();
	//for email end
}

void CWebClick::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CButton::OnLButtonDown(nFlags, point);
}

void CWebClick::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	//CButton::OnNcLButtonUp(nHitTest, point);
}

void CWebClick::OnNcRButtonDblClk(UINT nHitTest, CPoint point)
{
	//CButton::OnNcRButtonDblClk(nHitTest, point);
}

void CWebClick::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	//CButton::OnNcRButtonDown(nHitTest, point);
}

void CWebClick::OnNcRButtonUp(UINT nHitTest, CPoint point)
{
	//CButton::OnNcRButtonUp(nHitTest, point);
}

void CWebClick::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//CButton::OnLButtonDblClk(nFlags, point);
}

void CWebClick::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	//CButton::OnMButtonDblClk(nFlags, point);
}

void CWebClick::OnMButtonDown(UINT nFlags, CPoint point)
{
	//CButton::OnMButtonDown(nFlags, point);
}

void CWebClick::OnMButtonUp(UINT nFlags, CPoint point)
{
	//CButton::OnMButtonUp(nFlags, point);
}

BOOL CWebClick::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	HCURSOR hCursor;
	hCursor	= AfxGetApp()->LoadStandardCursor(IDC_UPARROW);
	//hCursor = ::LoadCursor(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDC_WEBLINK) );
	if(hCursor){
		::SetCursor( hCursor);
		return TRUE;
	}
	else{
		return FALSE;
	}
	//return CButton::OnSetCursor(pWnd, nHitTest, message);
}
