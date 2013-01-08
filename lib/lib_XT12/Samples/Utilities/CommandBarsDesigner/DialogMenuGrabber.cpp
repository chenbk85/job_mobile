// DialogMenuGrabber.cpp : implementation file
//

#include "stdafx.h"
#include "commandbarsdesigner.h"
#include "DialogMenuGrabber.h"
#include "EmbeddedFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogMenuGrabber dialog


CDialogMenuGrabber::CDialogMenuGrabber(CEmbeddedFrame* pFrame, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMenuGrabber::IDD, pParent)
{
	m_pFrame = pFrame;
	//{{AFX_DATA_INIT(CDialogMenuGrabber)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogMenuGrabber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogMenuGrabber)
	DDX_Control(pDX, IDC_STATIC_GRABBER, m_wndGrabber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogMenuGrabber, CDialog)
	//{{AFX_MSG_MAP(CDialogMenuGrabber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogMenuGrabber message handlers

BOOL CDialogMenuGrabber::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	VERIFY(m_wndMenuBar.CreateToolBar(WS_TABSTOP|WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this));
	CXTPClientRect rc(this);

	m_wndMenuBar.SetCommandBars(m_pFrame->GetCommandBars());

	if (m_wndMenuBar.GetSafeHwnd())
	{
		CSize sz = m_wndMenuBar.CalcDockingLayout(rc.Width(), /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);

		m_wndMenuBar.MoveWindow(0, 0, rc.Width(), sz.cy);
		m_wndMenuBar.Invalidate(FALSE);
	}

	m_wndMenuBar.EnableCustomization(FALSE);

	m_wndGrabber.m_pMenuBar = &m_wndMenuBar;

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
