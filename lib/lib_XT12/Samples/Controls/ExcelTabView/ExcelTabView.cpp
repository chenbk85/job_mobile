// ExcelTabView.cpp : implementation of the CExcelTabView class
//

#include "stdafx.h"
#include "ExcelTab.h"

#include "ExcelTabDoc.h"
#include "ExcelTabView.h"
#include "ExcelTabProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExcelTabView

IMPLEMENT_DYNCREATE(CExcelTabView, CView)

BEGIN_MESSAGE_MAP(CExcelTabView, CView)
	//{{AFX_MSG_MAP(CExcelTabView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_COMMAND(ID_EXCELTAB_PROPERTIES, OnExceltabProperties)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelTabView construction/destruction

CExcelTabView::CExcelTabView()
: m_dwTabStyle(0)
, m_bBottom(TRUE)
, m_bHasArrows(TRUE)
, m_bHasHomeEnd(FALSE)
, m_bHScroll(TRUE)
, m_pSheet7(NULL)
, m_pSheet8(NULL)
, m_pExcelTabCtrl(NULL)
{
	UpdateTabsStyle();
}

CExcelTabView::~CExcelTabView()
{
	if (::IsWindow(m_pSheet7->GetSafeHwnd()))
		m_pSheet7->DestroyWindow();

	if (::IsWindow(m_pSheet8->GetSafeHwnd()))
		m_pSheet8->DestroyWindow();

	SAFE_DELETE(m_pExcelTabCtrl);
}

BOOL CExcelTabView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CView::PreCreateWindow(cs))
		return FALSE;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CExcelTabView drawing

void CExcelTabView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CExcelTabView printing

BOOL CExcelTabView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExcelTabView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExcelTabView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExcelTabView diagnostics

#ifdef _DEBUG
void CExcelTabView::AssertValid() const
{
	CView::AssertValid();
}

void CExcelTabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExcelTabDoc* CExcelTabView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExcelTabDoc)));
	return (CExcelTabDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExcelTabView message handlers

void CExcelTabView::UpdateTabsStyle()
{
	DWORD dwNewStyle = 0;

	if (m_bHasHomeEnd)
	{
		dwNewStyle |= FTS_XT_HASHOMEEND;
		m_bHasArrows = TRUE;
	}

	if (m_bBottom)
		dwNewStyle |= FTS_XT_BOTTOM;

	if (m_bHasArrows)
		dwNewStyle |= FTS_XT_HASARROWS;

	if (m_bHScroll)
		dwNewStyle |= FTS_XT_HSCROLL;

	dwNewStyle |= FTS_XT_TOOLTIPS;

	if (dwNewStyle != m_dwTabStyle)
	{
		m_dwTabStyle = dwNewStyle;
	}
}

int CExcelTabView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create  the flat tab control.
	if (!CreateExcelTab())
		return -1;

	return 0;
}

BOOL CExcelTabView::CreateExcelTab()
{
	int iSel = 0;
	CXTPEmptyRect rTab;

	m_pExcelTabCtrl = new CXTExcelTabCtrl();

	// Create  the flat tab control.
	if (!m_pExcelTabCtrl->Create(WS_CHILD|WS_VISIBLE|m_dwTabStyle,
		rTab, this, IDC_EXCEL_TABCTRL))
	{
		TRACE0( "Failed to create flattab control\n" );
		return FALSE;
	}

	if (!CreateSheet1()) return FALSE;
	if (!CreateSheet2()) return FALSE;
	if (!CreateSheet3()) return FALSE;
	if (!CreateSheet4()) return FALSE;
	if (!CreateSheet5()) return FALSE;
	if (!CreateSheet6()) return FALSE;
	if (!CreateSheet7()) return FALSE;
	if (!CreateSheet8()) return FALSE;
	
	// Insert tabs into the flat tab control.
	m_pExcelTabCtrl->InsertItem(0, _T("Build"),           &m_sheet1);
	m_pExcelTabCtrl->InsertItem(1, _T("Debug"),           &m_sheet2);
	m_pExcelTabCtrl->InsertItem(2, _T("Find in Files 1"), &m_sheet3);
	m_pExcelTabCtrl->InsertItem(3, _T("Find in Files 2"), &m_sheet4);
	m_pExcelTabCtrl->InsertItem(4, _T("Results"),         &m_sheet5);
	m_pExcelTabCtrl->InsertItem(5, _T("SQL Debugging"),   &m_sheet6);
	m_pExcelTabCtrl->InsertItem(6, _T("Form View"),       m_pSheet7);
	m_pExcelTabCtrl->InsertItem(7, _T("Scroll View"),     m_pSheet8);

	
	m_pExcelTabCtrl->SetCurSel(iSel);

	return TRUE;
}

BOOL CExcelTabView::CreateSheet1()
{
	// Create the sheet1 list box.
	if (!m_sheet1.Create(WS_CHILD |
		LVS_REPORT | LVS_NOCOLUMNHEADER, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET1 ))
	{
		TRACE0( "Failed to create sheet1.\n" );
		return FALSE;
	}
	ListView_SetExtendedListViewStyleEx(m_sheet1.m_hWnd,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	m_sheet1.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet1.InsertColumn(0, _T("Column"), LVCFMT_LEFT, 512);
	m_sheet1.InsertItem(0, _T("--------------------Configuration: ExcelTabView - Win32 Debug--------------------"));
	m_sheet1.InsertItem(1, _T("Compiling resources..."));
	m_sheet1.InsertItem(2, _T("Compiling..."));
	m_sheet1.InsertItem(3, _T("StdAfx.cpp"));
	m_sheet1.InsertItem(5, _T("Compiling..."));
    m_sheet1.InsertItem(6, _T("ExcelEditCtrl.cpp"));
    m_sheet1.InsertItem(7, _T("ExcelFormView.cpp"));
    m_sheet1.InsertItem(8, _T("ExcelListCtrl.cpp"));
    m_sheet1.InsertItem(9, _T("ExcelScrollView.cpp"));
    m_sheet1.InsertItem(10, _T("ExcelTab.cpp"));
    m_sheet1.InsertItem(11, _T("ExcelTabDoc.cpp"));
    m_sheet1.InsertItem(12, _T("ExcelTabProperties.cpp"));
    m_sheet1.InsertItem(13, _T("ExcelTabView.cpp"));
    m_sheet1.InsertItem(14, _T("ExcelTreeCtrl.cpp"));
    m_sheet1.InsertItem(15, _T("MainFrm.cpp"));
	m_sheet1.InsertItem(16, _T("Generating Code..."));
	m_sheet1.InsertItem(17, _T("Linking..."));
	m_sheet1.InsertItem(18, _T(""));
	m_sheet1.InsertItem(19, _T("ExcelTabView.exe - 0 error(s), 0 warning(s)"));

	CXTLogFont lf;
	XTAuxData().font.GetLogFont(&lf);
	STRCPY_S(lf.lfFaceName, LF_FACESIZE, _T("Courier New"));
	m_font.CreateFontIndirect(&lf);
	m_sheet1.SetFont(&m_font);

	return TRUE;
}

BOOL CExcelTabView::CreateSheet2()
{
	// Create the sheet2 list box.
	if (!m_sheet2.Create( WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN |
		WS_HSCROLL | WS_VSCROLL | ES_MULTILINE, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET2 ))
	{
		TRACE0( "Failed to create sheet2.\n" );
		return FALSE;
	}
	m_sheet2.SetFont(m_sheet1.GetFont());
	m_sheet2.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet2.SetWindowText(
		_T("Loaded 'C:\\WINNT\\System32\\ntdll.dll', no matching symbolic information found.\r\n")
		_T("Loaded symbols for 'C:\\WINNT\\system32\\MFC42D.DLL'\r\n")
		_T("Loaded symbols for 'C:\\WINNT\\system32\\MSVCRTD.DLL'\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\KERNEL32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\GDI32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\USER32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\ADVAPI32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\rpcrt4.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\SHELL32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\shlwapi.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\comctl32.dll', no matching symbolic information found.\r\n")
		_T("Loaded symbols for 'C:\\WINNT\\system32\\MFCO42D.DLL'\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\OLE32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\OLEAUT32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\lpk.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\usp10.dll', no matching symbolic information found.\r\n")
		_T("XTTOOLKIT_DLL.DLL Initializing!\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\indicdll.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\imm32.dll', no matching symbolic information found.\r\n")
		_T("The program 'D:\\Controls\\Bin\\ExcelTabView.exe' has exited with code 0 (0x0).\r\n"));
	return TRUE;
}

BOOL CExcelTabView::CreateSheet3()
{
	// Create the sheet3 list box.
	if (!m_sheet3.Create(
		WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | WS_VSCROLL,
		CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET3 ))
	{
		TRACE0( "Failed to create sheet3.\n" );
		return FALSE;
	}
	m_sheet3.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	HTREEITEM file;
	file = m_sheet3.InsertItem(_T("D:\\Controls\\Samples\\ExcelTabView\\EditCtrlForFlatTab.cpp"));
	m_sheet3.InsertItem(_T("Line 92:            pSB->Create(WS_CHILD, CRect(0, 0, 0, 0), (CWnd *)this, 0)"), 0, 0, file);
	file = m_sheet3.InsertItem(_T("D:\\Controls\\Samples\\ExcelTabView\\ExcelTabView.rc"));
	m_sheet3.InsertItem(_T("Line 190:STYLE WS_CHILD"), 0, 0, file);
	file = m_sheet3.InsertItem(_T("D:\\Controls\\Samples\\ExcelTabView\\ExcelTabView.cpp"));
	m_sheet3.InsertItem(_T("Line 92:            pSB->Create(WS_CHILD, CRect(0, 0, 0, 0), (CWnd *)this, 0)"), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 265:   if (!m_pExcelTabView->Create(WS_CHILD|WS_VISIBLE|m_dwTabStyle,"), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 293:   if (!m_sheet1.Create(WS_CHILD |  "), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 303:   if (!m_sheet2.Create( WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN |"), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 312:   DWORD dwStyle = WS_CHILD | LBS_NOINTEGRALHEIGHT | WS_TABSTOP | WS_VSCROLL;"), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 316:       WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | WS_VSCROLL, "), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 348:        !((CWnd *)m_pSheet7)->Create(NULL, NULL, WS_CHILD, "), 0, 0, file);
	file = m_sheet3.InsertItem(_T("D:\\Controls\\Samples\\ExcelTabView\\SampleFormView.cpp"));
	m_sheet3.InsertItem(_T("Line 79:    m_ScrollBarH.Create(WS_CHILD, CRect(0, 0, 0, 0), this, 0);"), 0, 0, file);
	return TRUE;
}

BOOL CExcelTabView::CreateSheet4()
{
	// Define the default style for the output list boxes.
	DWORD dwStyle = WS_CHILD | LBS_NOINTEGRALHEIGHT | WS_TABSTOP | WS_VSCROLL;

	// Create the sheet4 list box.
	if (!m_sheet4.Create( dwStyle, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET4 ))
	{
		TRACE0( "Failed to create sheet4.\n" );
		return FALSE;
	}
	m_sheet4.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet4.SetFont(&XTAuxData().font);
	m_sheet4.AddString(_T("Find in Files 2 Tab Output..."));
	return TRUE;
}

BOOL CExcelTabView::CreateSheet5()
{
	// Define the default style for the output list boxes.
	DWORD dwStyle = WS_CHILD | LBS_NOINTEGRALHEIGHT | WS_TABSTOP | WS_VSCROLL;

	// Create the sheet5 list box.
	if (!m_sheet5.Create( dwStyle, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET5 ))
	{
		TRACE0( "Failed to create sheet5.\n" );
		return FALSE;
	}
	m_sheet5.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet5.SetFont(&XTAuxData().font);
	m_sheet5.AddString(_T("Results Tab Output..."));
	return TRUE;
}

BOOL CExcelTabView::CreateSheet6()
{
	// Define the default style for the output list boxes.
	DWORD dwStyle = WS_CHILD | LBS_NOINTEGRALHEIGHT | WS_TABSTOP | WS_VSCROLL;

	// Create the sheet6 list box.
	if (!m_sheet6.Create( dwStyle, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET6 ))
	{
		TRACE0( "Failed to create sheet6.\n" );
		return FALSE;
	}
	m_sheet6.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet6.SetFont(&XTAuxData().font);
	m_sheet6.AddString(_T("SQL Debugging Tab Output..."));
	return TRUE;
}

BOOL CExcelTabView::CreateSheet7()
{
	// views must be created dynamically because they are destroyed during
	// window destruction
	CCreateContext cc;
	::ZeroMemory(&cc, sizeof(cc));

	m_pSheet7 = (CExcelFormView*)RUNTIME_CLASS(CExcelFormView)->CreateObject();
	if (!m_pSheet7  || !((CWnd *)m_pSheet7)->Create(
		NULL, NULL, WS_CHILD, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET7, &cc))
	{
		TRACE0( "Failed to create sheet7.\n" );
		return FALSE;
	}
	return TRUE;
}

BOOL CExcelTabView::CreateSheet8()
{
	// Create the Test Scroll View
	CCreateContext cc;
	::ZeroMemory(&cc, sizeof(cc));

	m_pSheet8 = (CExcelScrollView*)RUNTIME_CLASS(CExcelScrollView)->CreateObject();
	if (!m_pSheet8  || !((CWnd *)m_pSheet8)->Create( NULL, NULL, WS_CHILD |
		WS_VSCROLL|WS_HSCROLL, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET8, &cc))
	{
		TRACE0( "Failed to create m_pSheet8.\n" );
		return FALSE;
	}
	return TRUE;
}

void CExcelTabView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (::IsWindow(m_pExcelTabCtrl->GetSafeHwnd()))
	{
		m_pExcelTabCtrl->SetWindowPos(NULL, 0,0, cx, cy, SWP_FRAMECHANGED);
	}
}

BOOL CExcelTabView::OnEraseBkgnd(CDC* pDC) 
{
	UNREFERENCED_PARAMETER(pDC);
	return TRUE;
}

void CExcelTabView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CXTPClientRect rClient(this);
	CXTMemDC memDC(&dc, rClient, GetXtremeColor(COLOR_WINDOW));
}

void CExcelTabView::OnExceltabProperties() 
{
	CExcelTabProperties dlg(m_bBottom, m_bHasArrows, m_bHasHomeEnd, m_bHScroll, this);
	if (dlg.DoModal() == IDOK)
	{
	}	
}

void CExcelTabView::UpdateExcelTab()
{
	UpdateTabsStyle();
	m_pExcelTabCtrl->SetTabStyle(m_dwTabStyle);
}
