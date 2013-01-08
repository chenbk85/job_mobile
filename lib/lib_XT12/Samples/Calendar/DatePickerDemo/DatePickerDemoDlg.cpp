// DatePickerDemoDlg.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DatePickerDemo.h"
#include "DatePickerDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString LoadResourceString(UINT nID)
{
	CString str;
	VERIFY(str.LoadString(nID));
	return str;
}

///////////////////////////////////////////////////////////

// Class CDayFontColor is derived from CCmdTarget.
// This class is used to associate a "day" with a font
// and a font color.
struct CDayFontColor : CCmdTarget
{
	CFont fnt;
	COLORREF color;
};

//------------------------------------------------
// GetStartPosition:
// Returns a POSITION value that
// indicates a starting position for iterating 
// through the map, or NULL if the map is empty.
//------------------------------------------------
// rNextPosition:
// Specifies a reference to a POSITION
// value returned by a previous GetNextAssoc or 
// GetStartPosition call.
//------------------------------------------------
// GetNextAssoc:
// Retrieves the map element at rNextPosition, 
// then updates rNextPosition to refer to the next 
// element in the map. This function is most useful 
// for iterating through all the elements in the map. 
// Note that the position sequence is not necessarily 
// the same as the key value sequence.
// If the retrieved element is the last in the map, 
// then the new value of rNextPosition is set to NULL.
//------------------------------------------------

// struct CStaticFontMap is used to associate each 
// visible "day" with a CDayFontColor class.

struct CStaticFontMap : public CMap<int,int,CDayFontColor*,CDayFontColor*>
{
	~CStaticFontMap()
	{
		POSITION pos = GetStartPosition();
		int nKey;
		CDayFontColor* pFC = NULL;
		while (pos != NULL)
		{
			GetNextAssoc(pos, nKey, pFC);
			if (pFC) {
				pFC->InternalRelease();// Decrement reference count by one.
			}
		}
	}
};

static CStaticFontMap mapFontColor;

void CALLBACK DayMetricsCallback(CXTPDatePickerControl* pControl, const COleDateTime &dtDay, XTP_DAYITEM_METRICS* pDayItemMetrics, void*)
{
    // This function is used to determine if a given day is special.
    // If the day is special then the day is highlighted.

    // Get the number of days from December 30, 1899 to present day.
    // COleDateTime operator =(DATE dtSrc) Note: DATE is a double.
    // The DATE value is copied into this COleDateTime object and its 
    // status is set to valid.
	COleDateTime dtNow = (double)long(COleDateTime::GetCurrentTime());
	COleDateTimeSpan span = dtDay - dtNow;

	static CFont fntBold;
	if (fntBold.GetSafeHandle() == 0)
	{
		LOGFONT lf;
		pControl->GetPaintManager()->GetDayTextFont()->GetLogFont(&lf);
		
		lf.lfWeight = FW_BOLD;
		fntBold.CreateFontIndirect(&lf);
	}

	if (abs(span.GetDays()) <= 2)
	{
		pDayItemMetrics->clrForeground = RGB(0xFF, 0, 0);
	}

	if (dtNow.GetMonth() == dtDay.GetMonth() - 1 && dtDay.GetDay() == dtNow.GetDay())
	{
		pDayItemMetrics->SetFont(&fntBold);
		pDayItemMetrics->clrForeground = RGB(0, 0, 0xFF);
	}

	CDayFontColor* pFontColor;
	if (mapFontColor.Lookup((int)dtDay, pFontColor))
	{
		pDayItemMetrics->SetFont(&pFontColor->fnt);
		pDayItemMetrics->clrForeground = pFontColor->color;
	}
}


// CDatePickerDemoDlg dialog

CDatePickerDemoDlg::CDatePickerDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDatePickerDemoDlg::IDD, pParent)
	, m_nRows(2)
	, m_nCols(4)
	, m_bShowWeekNumbers(FALSE)
	, m_bHighlightToday(TRUE)
	, m_bShowNonMonthDays(TRUE)
	, m_bShow3DBorder(TRUE)
	, m_bTheme(TRUE)
	, m_bThemeOffice2007(FALSE)
	, m_bShowNoneBtn(TRUE)
	, m_bShowTodayBtn(TRUE)
	, m_bIsAutoSize(TRUE)
	, m_strPopup(_T(""))
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDatePickerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatePickerDemoDlg)
	DDX_Control(pDX, IDC_COMBO_DATEPICKER, m_cmbDatePicker);
	DDX_Control(pDX, IDC_DATEPICKER, m_wndDatePicker);
	DDX_Control(pDX, IDC_COMBO_FIRST_WEEK_DAY, m_cmbFirstWeekDay);
	DDX_Control(pDX, IDC_COMBO_MAX_SELECTED, m_cmbMaxSelDays);
	DDX_Check(pDX, IDC_CHECK_SHOWWEEKNRS, m_bShowWeekNumbers);
	DDX_Check(pDX, IDC_CHECK_HIGHLIGHT_TODAY, m_bHighlightToday);
	DDX_Check(pDX, IDC_CHECK_SHOWTODAYBTN, m_bShowTodayBtn);
	DDX_Check(pDX, IDC_CHECK_SHOWNONEBTN, m_bShowNoneBtn);
	DDX_Check(pDX, IDC_CHECK_AUTO_SIZE, m_bIsAutoSize);
	DDX_Check(pDX, IDC_CHECK_NON_MONTH_DAYS, m_bShowNonMonthDays);
	DDX_Check(pDX, IDC_CHECK_SHOW_3D_BORDER, m_bShow3DBorder);
	DDX_Check(pDX, IDC_CHECK_THEME, m_bTheme);
	DDX_Check(pDX, IDC_CHECK_THEME_OFFICE_2007, m_bThemeOffice2007);	
	DDX_Text(pDX, IDC_EDIT_POPUP, m_strPopup);
	DDX_Control(pDX, IDC_EDIT_COLS, m_edtCols);
	DDX_Control(pDX, IDC_EDIT_ROWS, m_edtRows);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatePickerDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDatePickerDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()

	ON_EN_CHANGE(IDC_EDIT_COLS, OnEnChangeEditGridSize)
	ON_EN_CHANGE(IDC_EDIT_ROWS, OnEnChangeEditGridSize)
	ON_BN_CLICKED(IDC_CHECK_SHOWWEEKNRS, OnBnClickedCheckShowWeekNumbers)
	ON_BN_CLICKED(IDC_CHECK_HIGHLIGHT_TODAY, OnBnClickedCheckHighlightToday)
	ON_BN_CLICKED(IDC_CHECK_SHOWTODAYBTN, OnBnClickedCheckShowTodayBtn)
	ON_BN_CLICKED(IDC_CHECK_SHOWNONEBTN, OnBnClickedCheckShowNoneBtn)
	ON_BN_CLICKED(IDC_CHECK_AUTO_SIZE, OnClickedCheckAutoSize)
	ON_BN_CLICKED(IDC_CHECK_THEME, OnClickedTheme)
	
	ON_BN_CLICKED(IDC_CHECK_NON_MONTH_DAYS, OnBnClickedCheckNonMonthDays)
	ON_BN_CLICKED(IDC_CHECK_SHOW_3D_BORDER, OnBnClickedCheckShow3dBorder)
	ON_NOTIFY(XTP_NC_DATEPICKER_BUTTON_CLICK, 1000, OnButtonPressed)
	ON_BN_CLICKED(IDC_BTN_POPUP, OnBnClickedBtnPopup)
	ON_BN_CLICKED(IDC_CHECK_THEME_OFFICE_2007, OnCheckThemeOffice2007)
	
	ON_CBN_SELCHANGE(IDC_COMBO_FIRST_WEEK_DAY, OnCbnChangeFirstWeekDay)
	ON_CBN_SELCHANGE(IDC_COMBO_MAX_SELECTED, OnCbnChangeMaxSelDays)
	ON_CBN_EDITCHANGE(IDC_COMBO_MAX_SELECTED, OnCbnEditMaxSelDays)

	ON_BN_CLICKED(IDC_BTN_CHANGE_SEL_FONT, OnBnClickedSelTextFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDatePickerDemoDlg message handlers

BOOL CDatePickerDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog.
	SetIcon(m_hIcon, TRUE);  // Set big icon.
	SetIcon(m_hIcon, FALSE); // Set small icon.

	m_wndDatePicker.SetCallbackDayMetrics(DayMetricsCallback);

	m_bIsAutoSize = m_wndDatePicker.IsAutoSize();
	m_edtCols.EnableWindow(!m_bIsAutoSize);
	m_edtRows.EnableWindow(!m_bIsAutoSize);

	// The first day of the week initialization.
	m_cmbFirstWeekDay.SetCurSel(0);
    m_wndDatePicker.SetFirstDayOfWeek(1);

	// THe maximum days selection initialization.
	m_cmbMaxSelDays.SetItemData(m_cmbMaxSelDays.AddString(LoadResourceString(IDS_NOLIMIT)), XTP_SELECTION_INFINITE);
	m_cmbMaxSelDays.SetItemData(m_cmbMaxSelDays.AddString(_T("5")),  5);
	m_cmbMaxSelDays.SetItemData(m_cmbMaxSelDays.AddString(_T("10")), 10);
	m_cmbMaxSelDays.SetItemData(m_cmbMaxSelDays.AddString(_T("15")), 15);
	m_cmbMaxSelDays.SetItemData(m_cmbMaxSelDays.AddString(_T("20")), 20);
	m_cmbMaxSelDays.SetItemData(m_cmbMaxSelDays.AddString(_T("25")), 25);
	m_cmbMaxSelDays.SetItemData(m_cmbMaxSelDays.AddString(_T("30")), 30);
	m_cmbMaxSelDays.SetCurSel(0);

	// Initialize tool tip captions.
	m_ToolTip.Create(this);
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_COLS), LoadResourceString(IDS_HINT_COLUMNS));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_ROWS), LoadResourceString(IDS_HINT_ROWS));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_FIRST_WEEK_DAY), LoadResourceString(IDS_HINT_FIRST_WEEK_DAY));
	m_ToolTip.AddTool(GetDlgItem(IDC_COMBO_MAX_SELECTED),	LoadResourceString(IDS_HINT_MAX_SEL_DAYS  ));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_SHOWWEEKNRS),	LoadResourceString(IDS_HINT_WEEK_NUMBERS  ));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_HIGHLIGHT_TODAY),LoadResourceString(IDS_HINT_TODAY         ));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_NON_MONTH_DAYS),	LoadResourceString(IDS_HINT_NONMONTH_DAYS ));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_SHOW_3D_BORDER), LoadResourceString(IDS_HINT_3DBORDER      ));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_SHOWTODAYBTN),	LoadResourceString(IDS_HINT_BTN_TODAY     ));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_SHOWNONEBTN),	LoadResourceString(IDS_HINT_BTN_NONE      ));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_THEME),			LoadResourceString(IDS_HINT_LUNA_THEME    ));
	m_ToolTip.AddTool(GetDlgItem(IDC_CHECK_AUTO_SIZE),		LoadResourceString(IDS_HINT_AUTOSIZE      ));
	m_ToolTip.AddTool(GetDlgItem(IDC_BTN_POPUP),			LoadResourceString(IDS_HINT_TEST_POPUP    ));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_POPUP),			LoadResourceString(IDS_HINT_POPUP_RESULTS ));
	m_ToolTip.AddTool(GetDlgItem(IDC_BTN_CHANGE_SEL_FONT),	LoadResourceString(IDS_HINT_FONT_SELECTED ));
	m_ToolTip.Activate(TRUE);

	if (!CXTPWinThemeWrapper().IsThemeActive())
	{
		GetDlgItem(IDC_CHECK_THEME)->EnableWindow(FALSE);
		m_bTheme = FALSE;
	}

	UpdateData(FALSE);
	
	UpdateRowsColsControls();
	
	return TRUE;  // Return TRUE unless you set the focus to a control.
}

void CDatePickerDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
// to draw the icon.  For MFC applications using the document/view model,
// this is automatically done for you by the framework.

void CDatePickerDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Device context for painting.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor
// to display while the user drags the minimized window.
HCURSOR CDatePickerDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDatePickerDemoDlg::OnEnChangeEditGridSize()
{
	CString strRows, strCols;
	m_edtRows.GetWindowText(strRows);
	m_edtCols.GetWindowText(strCols);

	if (strRows.IsEmpty() || strCols.IsEmpty())
		return;
	
	m_nRows = _ttoi(strRows);
	m_nCols = _ttoi(strCols);

	if (m_nRows > 0 && m_nCols > 0)
		m_wndDatePicker.SetGridSize(m_nRows, m_nCols);	
}

void CDatePickerDemoDlg::OnBnClickedCheckShowWeekNumbers()
{
	UpdateData();
	m_wndDatePicker.SetShowWeekNumbers(m_bShowWeekNumbers);
}

void CDatePickerDemoDlg::OnBnClickedCheckHighlightToday()
{
	UpdateData();
	m_wndDatePicker.SetHighlightToday(m_bHighlightToday);
}


void CDatePickerDemoDlg::OnBnClickedCheckShowTodayBtn()
{
	UpdateData();
	m_wndDatePicker.SetButtonsVisible(m_bShowTodayBtn, m_bShowNoneBtn);
}

void CDatePickerDemoDlg::OnBnClickedCheckShowNoneBtn()
{
	UpdateData();
	m_wndDatePicker.SetButtonsVisible(m_bShowTodayBtn, m_bShowNoneBtn);
}

void CDatePickerDemoDlg::OnClickedTheme()
{
	UpdateData();
	
	m_wndDatePicker.GetPaintManager()->EnableTheme(m_bTheme);
	m_wndDatePicker.RedrawControl();
}

void CDatePickerDemoDlg::OnClickedCheckAutoSize()
{
	UpdateData();
	m_wndDatePicker.SetAutoSize(m_bIsAutoSize);

	m_edtCols.EnableWindow(!m_wndDatePicker.IsAutoSize());
	m_edtRows.EnableWindow(!m_wndDatePicker.IsAutoSize());

	if (m_bIsAutoSize)
		UpdateRowsColsControls();
}


void CDatePickerDemoDlg::OnButtonPressed(NMHDR* pNotifyStruct, LRESULT*)
{
	XTP_NC_DATEPICKER_BUTTON* pNMButton = (XTP_NC_DATEPICKER_BUTTON*)pNotifyStruct;

	switch (pNMButton->nID)
	{	
		case XTP_IDS_DATEPICKER_TODAY:
			TRACE(_T("TODAY BUTTON PRESSED\n"));
			break;
		case XTP_IDS_DATEPICKER_NONE:
			TRACE(_T("NONE BUTTON PRESSED\n"));
			break;
	}
}

void CDatePickerDemoDlg::OnBnClickedCheckNonMonthDays()
{
	UpdateData();
	m_wndDatePicker.SetShowNonMonthDays(m_bShowNonMonthDays);
}

void CDatePickerDemoDlg::OnBnClickedCheckShow3dBorder()
{
	UpdateData();
	m_wndDatePicker.SetBorderStyle(m_bShow3DBorder? xtpDatePickerBorder3D: xtpDatePickerBorderNone);
}

void CDatePickerDemoDlg::OnBnClickedBtnPopup()
{
	CXTPDatePickerControl wndDatePicker;
	
	CXTPWindowRect rcPopup(GetDlgItem(IDC_BTN_POPUP));

	CRect rc;
	wndDatePicker.GetMinReqRect(&rc);
	
	rc.InflateRect(0 ,0, 4, 4);
	rc.OffsetRect(rcPopup.right - rc.Width(), rcPopup.bottom);
	
	wndDatePicker.SetButtonsVisible(TRUE, FALSE);
	wndDatePicker.SetShowWeekNumbers(TRUE);

	if (wndDatePicker.GoModal(rc, this))
	{
		COleDateTime dtFrom;
		COleDateTime dtTo;

		if (wndDatePicker.GetSelRange(dtFrom, dtTo))
		{
			if (dtFrom == dtTo)
			{
				m_strPopup.Format(_T("%d.%d.%d"),	
					dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay());
			} else
			{
				// edit
				m_strPopup.Format(_T("%d.%d.%d - %d.%d.%d"), 
					dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 
					dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay());
			}
		}
		else
			m_strPopup.Format(_T("Nothing selected"));
	}
	else
		m_strPopup.Format(_T("Error Popup wnd!"));

	UpdateData(FALSE);
}

void CDatePickerDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (::IsWindow(m_wndDatePicker.GetSafeHwnd()))
	{
		CRect rcDP;
		m_wndDatePicker.GetWindowRect(&rcDP);
		if (!rcDP.IsRectEmpty())
		{
			ScreenToClient(&rcDP);
			rcDP.bottom = cy - 5;
			rcDP.right = cx - 5;
			if (!rcDP.IsRectEmpty())
				m_wndDatePicker.MoveWindow(rcDP);
		}

		UpdateRowsColsControls();
	}
}

void CDatePickerDemoDlg::UpdateRowsColsControls()
{
	m_nRows = m_wndDatePicker.GetRows();
	m_nCols = m_wndDatePicker.GetCols();
	
	CString strRows, strCols;
	strRows.Format(_T("%d"), m_nRows);
	strCols.Format(_T("%d"), m_nCols);

	m_edtRows.SetWindowText(strRows);
	m_edtCols.SetWindowText(strCols);
}

BOOL CDatePickerDemoDlg::OnEraseBkgnd(CDC* pDC)
{
	CDialog::OnEraseBkgnd(pDC);
	return FALSE;
}

void CDatePickerDemoDlg::OnCbnChangeFirstWeekDay()
{
	UpdateData();
    m_wndDatePicker.SetFirstDayOfWeek(m_cmbFirstWeekDay.GetCurSel()+1);
}

void CDatePickerDemoDlg::OnCbnChangeMaxSelDays()
{
	UpdateData();
	
	int nMaxSelectedDays = (int)m_cmbMaxSelDays.GetItemData(m_cmbMaxSelDays.GetCurSel());
	m_wndDatePicker.SetMaxSelCount(nMaxSelectedDays);
}

void CDatePickerDemoDlg::OnCbnEditMaxSelDays()
{
	UpdateData();
	
	int nMaxSelectedDays = -1;
	CString strMaxDays;
	m_cmbMaxSelDays.GetWindowText(strMaxDays);
	SCANF_S(strMaxDays, _T("%d"), &nMaxSelectedDays);

	m_wndDatePicker.SetMaxSelCount(nMaxSelectedDays);
}

void CDatePickerDemoDlg::OnBnClickedSelTextFont()
{
	LOGFONT lf;
	m_wndDatePicker.GetPaintManager()->GetDayTextFont()->GetLogFont(&lf);
	
	CFontDialog dlg(&lf);
	if (dlg.DoModal() == IDOK)
	{
		COleDateTime dtFrom;
		COleDateTime dtTo;
		
		if (m_wndDatePicker.GetSelRange(dtFrom, dtTo))
		{
			CDayFontColor* pFontColor = new CDayFontColor;
			pFontColor->color = dlg.GetColor();
			pFontColor->fnt.CreateFontIndirect(&lf);
			
            // Span 1 day at a time.
			COleDateTimeSpan spDay(1,  // Day
                                   0,  // Hour
                                   0,  // Minute
                                   0); // Second

            // Loop on the number of days selected.
            // Start at dtFrom and increment 1 day at a time until we are equal to dtTo.
			for (COleDateTime dtDay(dtFrom); dtDay <= dtTo; dtDay += spDay)
			{
				if (m_wndDatePicker.IsSelected(dtDay))
				{
					CDayFontColor* pFC;
					if (mapFontColor.Lookup((int)dtDay, pFC))
					{
						pFC->InternalRelease();
					}
					pFontColor->InternalAddRef();
					mapFontColor.SetAt((int)dtDay, pFontColor);
				}
			}
			// add new font to the collection
			pFontColor->InternalRelease();
			m_wndDatePicker.SetCurSel(dtFrom);
			m_wndDatePicker.RedrawControl();
		}
	}
}

BOOL CDatePickerDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CDatePickerDemoDlg::OnCheckThemeOffice2007() 
{
	UpdateData();

	if (m_bThemeOffice2007)
	{
		CXTPDatePickerThemeOffice2007* pTheme2007 = new CXTPDatePickerThemeOffice2007;
		m_wndDatePicker.SetTheme(pTheme2007);
	}
	else 
	{			
		m_wndDatePicker.SetTheme(NULL);
	}
}
