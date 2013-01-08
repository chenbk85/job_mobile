// PaneStyles.cpp : implementation file
//

#include "stdafx.h"
#include "ribbonsample.h"
#include "PaneStyles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPaneStyles dialog


CPaneStyles::CPaneStyles(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CPaneStyles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaneStyles)
	//}}AFX_DATA_INIT
}


void CPaneStyles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaneStyles)
	DDX_Control(pDX, IDC_LIST_STYLES, m_lstStyles);
	DDX_Control(pDX, IDC_CHECK_LINKEDSTYLE, m_chkLinkedStyle);
	DDX_Control(pDX, IDC_CHECK_PREVIEW, m_chkPreview);
	DDX_Control(pDX, IDC_BUTTON_STYLEINSPECTOR, m_btnStyleInspector);
	DDX_Control(pDX, IDC_BUTTON_NEWSTYLE, m_btnNewStyle);
	DDX_Control(pDX, IDC_BUTTON_MANAGESTYLES, m_btnManageStyles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaneStyles, CXTResizeDialog)
	//{{AFX_MSG_MAP(CPaneStyles)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaneStyles message handlers

void CPaneStyles::OnCancel()
{
}

void CPaneStyles::OnOK()
{
}

HBRUSH CPaneStyles::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	return m_brush;
}

BOOL CPaneStyles::OnInitDialog() 
{
	CXTResizeDialog::OnInitDialog();
	
	SetResize(IDC_LIST_STYLES,       SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);

	SetResize(IDC_CHECK_PREVIEW,     SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_CHECK_LINKEDSTYLE,     SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUTTON_NEWSTYLE,     SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUTTON_STYLEINSPECTOR,     SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUTTON_MANAGESTYLES,     SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);

	m_lstStyles.AddString(_T("Clear All"));
	m_lstStyles.AddString(_T("Normal"));
	m_lstStyles.AddString(_T("No Spacing"));
	m_lstStyles.AddString(_T("Heading 1"));
	m_lstStyles.AddString(_T("Heading 2"));
	m_lstStyles.AddString(_T("Heading 3"));
	m_lstStyles.AddString(_T("Title"));
	m_lstStyles.AddString(_T("Subtitle"));
	m_lstStyles.SetListStyle(xtListBoxOffice2007);

	m_chkLinkedStyle.SetTheme(xtpButtonThemeOffice2007);
	m_chkPreview.SetTheme(xtpButtonThemeOffice2007);
	m_btnStyleInspector.SetTheme(xtpButtonThemeOffice2007);
	m_btnNewStyle.SetTheme(xtpButtonThemeOffice2007);
	m_btnManageStyles.SetTheme(xtpButtonThemeOffice2007);

	CXTPImageManagerIconHandle ih;
	CXTPImageManagerIconHandle ihh;
	
	ih = CXTPImageManagerIcon::LoadBitmapFromResource(MAKEINTRESOURCE(IDC_BUTTON_NEWSTYLE), NULL);
	m_btnNewStyle.SetIcon(CSize(16, 16), ih, ihh);

	ih = CXTPImageManagerIcon::LoadBitmapFromResource(MAKEINTRESOURCE(IDC_BUTTON_MANAGESTYLES), NULL);
	m_btnManageStyles.SetIcon(CSize(16, 16), ih, ihh);

	ih = CXTPImageManagerIcon::LoadBitmapFromResource(MAKEINTRESOURCE(IDC_BUTTON_STYLEINSPECTOR), NULL);
	m_btnStyleInspector.SetIcon(CSize(16, 16), ih, ihh);

	RefreshMetrics();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPaneStyles::RefreshMetrics()
{
	m_brush.DeleteObject();

	COLORREF clr = XTPOffice2007Images()->GetImageColor(_T("DockingPane"), _T("WordPaneBackground"));
	m_brush.CreateSolidBrush(clr);
}

