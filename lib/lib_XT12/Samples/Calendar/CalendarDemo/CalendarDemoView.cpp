// CalendarDemoView.cpp : implementation of the CCalendarDemoView class
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
#include "CalendarDemo.h"

#include "MainFrm.h"
#include "CalendarDemoDoc.h"
#include "CalendarDemoView.h"
#include "DataProvidersOptions.h"
#include "AdvancedCalendarOptionsDlg.h"

#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
extern CString GetDPName(int nDPType);
extern int GetDPType(CXTPCalendarData* pData);

//////////////////////////////////////////////////////////////////////////
static CXTPCalendarRemindersDialog* s_pDlgReminders = NULL;

CString cstrMarkupDynamicSample(
_T("<StackPanel Margin='2, 2, 2, 2' VerticalAlignment='Top'")
_T("HorizontalAlignment='Center'>")
_T("<TextBlock Padding='0,10,0,0' TextWrapping='Wrap'>")
_T("<Italic>Dynamically Customized Subject:</Italic><Bold>/Calendar/Events/Event/Subject</Bold></TextBlock>")
_T("<TextBlock Padding='0,10,0,0'>Dynamically Customized Body:</TextBlock>")
_T("<TextBlock Padding='10,10,0,0' TextWrapping='Wrap'>")
_T("/Calendar/Events/Event/Body")
_T("</TextBlock>")
_T("<TextBlock Padding='10,10,0,0'> - Regards</TextBlock>")
_T("</StackPanel>"));

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView

IMPLEMENT_DYNCREATE(CCalendarDemoView, CXTPCalendarControlView)

BEGIN_MESSAGE_MAP(CCalendarDemoView, CXTPCalendarControlView)
	//{{AFX_MSG_MAP(CCalendarDemoView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PAGE_SETUP, CXTPCalendarControlView::OnFilePageSetup)
	ON_COMMAND(ID_FILE_PRINT, CXTPCalendarControlView::OnFilePrint)	
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CXTPCalendarControlView::OnFilePrintPreview)

	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)

	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	// User commands
	ON_COMMAND(ID_VIEW_REMINDERS, OnViewReminders)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REMINDERS,  OnUpdateViewReminders)
	
	ON_COMMAND(ID_CALENDAR_VIEW_DAY, OnCalendarViewDay)
	ON_COMMAND(ID_CALENDAR_VIEW_WORKWEEK, OnCalendarViewWorkWeek)
	ON_COMMAND(ID_CALENDAR_VIEW_WEEK, OnCalendarViewWeek)
	ON_COMMAND(ID_CALENDAR_VIEW_MONTH, OnCalendarViewMonth)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_VIEW_DAY, OnUpdateCalendarViewDay)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_VIEW_WORKWEEK, OnUpdateCalendarViewWorkWeek)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_VIEW_WEEK, OnUpdateCalendarViewWeek)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_VIEW_MONTH, OnUpdateCalendarViewMonth)
	ON_COMMAND(ID_CALENDAR_CHANGETIMESCALE_60MINUTES, OnCalendarTimescale60)
	ON_COMMAND(ID_CALENDAR_CHANGETIMESCALE_30MINUTES, OnCalendarTimescale30)
	ON_COMMAND(ID_CALENDAR_CHANGETIMESCALE_15MINUTES, OnCalendarTimescale15)
	ON_COMMAND(ID_CALENDAR_CHANGETIMESCALE_10MINUTES, OnCalendarTimescale10)
	ON_COMMAND(ID_CALENDAR_CHANGETIMESCALE_6MINUTES,  OnCalendarTimescale6)
	ON_COMMAND(ID_CALENDAR_CHANGETIMESCALE_5MINUTES,  OnCalendarTimescale5)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_CHANGETIMESCALE_60MINUTES, OnUpdateCalendarTimescale60)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_CHANGETIMESCALE_30MINUTES, OnUpdateCalendarTimescale30)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_CHANGETIMESCALE_15MINUTES, OnUpdateCalendarTimescale15)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_CHANGETIMESCALE_10MINUTES, OnUpdateCalendarTimescale10)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_CHANGETIMESCALE_6MINUTES,  OnUpdateCalendarTimescale6)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_CHANGETIMESCALE_5MINUTES,  OnUpdateCalendarTimescale5)
	ON_COMMAND(ID_CALENDAR_CHANGETIMESCALE_CHANGETIMEZONE,  OnCalendarTimezone)
	ON_COMMAND(ID_CALENDAR_ADD_NEW_EVENT, OnAddNewEvent)	
	
//	ON_COMMAND(ID_CALENDAR_LANGUAGE_RUSSIAN,  OnCalendarLangRussian)
//	ON_COMMAND(ID_CALENDAR_LANGUAGE_DEFAULT,  OnCalendarLangDefault)

	ON_BN_CLICKED(IDC_TIME_ZONE_BTN, OnCalendarTimezone)
	ON_BN_CLICKED(IDC_ADVANCED_OPT_BTN, OnAdvancedOptions)
	
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView construction/destruction

CCalendarDemoView::CCalendarDemoView()
{
	m_dsDayViewDays.SetDateTimeSpan(4,0,0,0);

	SetCalendarCtrl(&m_wndCalendarEx, FALSE);

	// Advise To Notifications
	CXTPNotifyConnection* ptrCalendarConn = GetCalendarCtrl().GetConnection();
	ASSERT(ptrCalendarConn);
	
	if(!ptrCalendarConn) {		
		return;
	}	

	m_nScale = -1;

	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDARCONTEXTMENU, &CCalendarDemoView::OnEvent_Calendar);
	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDARLBUTTONDBLCLICK, &CCalendarDemoView::OnEvent_Calendar);
	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDARKEYDOWN, &CCalendarDemoView::OnEvent_Calendar);
	
	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAR_IS_EVENT_EDIT_OPERATION_DISABLED, &CCalendarDemoView::OnEvent_IsEditActionDisabled);
	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAR_BEFORE_EVENT_EDIT_OPERATION, &CCalendarDemoView::OnEvent_BeforeEditAction);

	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAR_PREPOPULATE, &CCalendarDemoView::OnEvent_PrePopulate);

	//m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAR_SELECTION_CHANGED, &CCalendarDemoView::OnEvent_SelChanged);
	    	
	// Advise to Calendar Data Provider notifications
	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAREVENTWASADDED, &CCalendarDemoView::OnEvent_CalendarData);
	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAREVENTWASDELETED, &CCalendarDemoView::OnEvent_CalendarData);
	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAREVENTWASCHANGED, &CCalendarDemoView::OnEvent_CalendarData);

	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDARPATTERNWASADDED, &CCalendarDemoView::OnEvent_CalendarData);
	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDARPATTERNWASDELETED, &CCalendarDemoView::OnEvent_CalendarData);
	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDARPATTERNWASCHANGED, &CCalendarDemoView::OnEvent_CalendarData);

//	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAR_ON_REMINDERS, &CCalendarDemoView::OnReminders);

	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAR_BEFORE_DRAW_THEMEOBJECT, &CCalendarDemoView::OnBeforeDrawThemeObject);

	m_Sink.Advise(ptrCalendarConn, XTP_NC_CALENDAR_GETITEMTEXT, &CCalendarDemoView::OnEvent_GetItemText);
	
}

CCalendarDemoView::~CCalendarDemoView()
{
	if (s_pDlgReminders)
		delete s_pDlgReminders;
	s_pDlgReminders = NULL;
}

BOOL CCalendarDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~WS_BORDER;

	return CXTPCalendarControlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView drawing

void CCalendarDemoView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);

	CCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView diagnostics

#ifdef _DEBUG
void CCalendarDemoView::AssertValid() const
{
	CXTPCalendarControlView::AssertValid();
}

void CCalendarDemoView::Dump(CDumpContext& dc) const
{
	CXTPCalendarControlView::Dump(dc);
}

CCalendarDemoDoc* CCalendarDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCalendarDemoDoc)));
	return (CCalendarDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoView message handlers

int CCalendarDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTPCalendarControlView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	((CWnd*)&GetCalendarCtrl())->EnableToolTips(TRUE);
	
	CCalendarDemoDoc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->m_pCalendar = &GetCalendarCtrl();
	}
    
	m_CalendarController.SetCalendar(&GetCalendarCtrl());

	m_wndScrollBar.Create(WS_CHILD | WS_VISIBLE | SBS_VERT, CRect(0, 0, 0, 0), this, 100);
	m_wndScrollBar.SetScrollBarStyle(xtpScrollStyleOffice2007Dark);
	SetScrollBarCtrl(&m_wndScrollBar);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//  User message handlers
//

void CCalendarDemoView::SetView(XTPCalendarViewType viewType)
{
	GetCalendarCtrl().SwitchActiveView(viewType);

	//GetCalendarCtrl().GetActiveView()->SetDayHeaderFormatLong(_T("dddd, d MMMM yyyy 'year'"));
	//GetCalendarCtrl().GetActiveView()->SetDayHeaderFormatMiddle(_T("ddd, d MMM yy"));
	//GetCalendarCtrl().GetActiveView()->SetDayHeaderFormatShort(_T("d MMMM"));
	//GetCalendarCtrl().GetActiveView()->SetDayHeaderFormatShortest(_T("d MMM"));

	((CMainFrame*)GetParentFrame())->m_dlgOptions.OnViewChanged(viewType);
}



void CCalendarDemoView::OnCalendarViewDay() 
{
	if(GetCalendarCtrl().GetActiveView() && 
		GetCalendarCtrl().GetActiveView()->GetViewType() != xtpCalendarDayView) 
	{
		TRACE(_T("Switch to 1 day view.\n"));
		SetView(xtpCalendarDayView);

		OnUpdateTimeScale();
	}	
}

void CCalendarDemoView::OnCalendarViewWorkWeek() 
{
	if(GetCalendarCtrl().GetActiveView() && 
		GetCalendarCtrl().GetActiveView()->GetViewType() != xtpCalendarWorkWeekView) 
	{
		TRACE(_T("Switch to work week day view.\n"));
		SetView(xtpCalendarWorkWeekView);
		
		OnUpdateTimeScale();
	}	
}

void CCalendarDemoView::OnCalendarViewWeek() 
{
	if(GetCalendarCtrl().GetActiveView() && 
		GetCalendarCtrl().GetActiveView()->GetViewType() != xtpCalendarWeekView) 
	{
		TRACE(_T("Switch to week view.\n"));
		SetView(xtpCalendarWeekView);
	}
}

void CCalendarDemoView::OnCalendarViewMonth() 
{   
//	CXTPCalendarControl::CUpdateContext cnt(&GetCalendarCtrl(), xtpCalendarUpdateLayout);

	if(GetCalendarCtrl().GetActiveView() && 
		GetCalendarCtrl().GetActiveView()->GetViewType() != xtpCalendarMonthView) 
	{
		TRACE(_T("Switch to month view.\n"));
		SetView(xtpCalendarMonthView);

	}

	// In month view Long, Middle and Short formats are always used for first month day header
	//GetCalendarCtrl().GetActiveView()->SetDayHeaderFormatLong(_T("d MMMM yyy"));
	//GetCalendarCtrl().GetActiveView()->SetDayHeaderFormatMiddle(_T("d MMM yy"));
	//GetCalendarCtrl().GetActiveView()->SetDayHeaderFormatShort(_T("d MMM"));
	
	// // In month view Shortest format is always used for not first month day header
	//GetCalendarCtrl().GetActiveView()->SetDayHeaderFormatShortest(_T("d"));	
}

void CCalendarDemoView::OnUpdateCalendarViewDay(CCmdUI* pCmdUI) 
{
	BOOL bViewDay = FALSE;
	CXTPCalendarView* pView = GetCalendarCtrl().GetActiveView();
	if (pView && pView->GetViewType() == xtpCalendarDayView) {
		bViewDay = TRUE;			
	}
	pCmdUI->SetCheck(bViewDay);	
}

void CCalendarDemoView::OnUpdateCalendarViewWorkWeek(CCmdUI* pCmdUI) 
{
	BOOL bViewDays = FALSE;
	CXTPCalendarView* pView = GetCalendarCtrl().GetActiveView();
	if (pView && pView->GetViewType() == xtpCalendarWorkWeekView) {
		bViewDays = TRUE;			
	}
	pCmdUI->SetCheck(bViewDays);	
}

void CCalendarDemoView::OnUpdateCalendarViewWeek(CCmdUI* pCmdUI) 
{
	BOOL bViewWeek = FALSE;
	CXTPCalendarView* pView = GetCalendarCtrl().GetActiveView();
	if (pView && pView->GetViewType() == xtpCalendarWeekView) 
		bViewWeek = TRUE;	
	pCmdUI->SetCheck(bViewWeek);	
}

void CCalendarDemoView::OnUpdateCalendarViewMonth(CCmdUI* pCmdUI) 
{
	BOOL bViewMonth = FALSE;
	CXTPCalendarView* pView = GetCalendarCtrl().GetActiveView();
	if (pView && pView->GetViewType() == xtpCalendarMonthView) 
		bViewMonth = TRUE; 
	pCmdUI->SetCheck(bViewMonth);	
}

//////////////////////////////////////////////////////////////////////////

void CCalendarDemoView::SetCalendarToolTipMode(int nToolTipMode)
{
	m_wndCalendarEx.m_nToolTipMode = nToolTipMode;

	GetCalendarCtrl().EnableToolTips(nToolTipMode == ctmStandard);
}

void CCalendarDemoView::SetCalendarTimeScale(int nScale)
{
	m_nScale = nScale;
	OnUpdateTimeScale();
}

void CCalendarDemoView::OnCalendarTimescale60() 
{
	SetCalendarTimeScale(60);
}

void CCalendarDemoView::OnCalendarTimescale30() 
{
	SetCalendarTimeScale(30);
}

void CCalendarDemoView::OnCalendarTimescale15() 
{
	SetCalendarTimeScale(15);
}

void CCalendarDemoView::OnCalendarTimescale10() 
{
	SetCalendarTimeScale(10);
}

void CCalendarDemoView::OnCalendarTimescale6() 
{
	SetCalendarTimeScale(6);
}

void CCalendarDemoView::OnCalendarTimescale5() 
{
	SetCalendarTimeScale(5);
}

void CCalendarDemoView::OnUpdateCalendarTimescale60(CCmdUI* pCmdUI)
{
	OnUpdateCalendarTimescale(pCmdUI, 60);
}

void CCalendarDemoView::OnUpdateCalendarTimescale30(CCmdUI* pCmdUI)
{
	OnUpdateCalendarTimescale(pCmdUI, 30);
}

void CCalendarDemoView::OnUpdateCalendarTimescale15(CCmdUI* pCmdUI)
{
	OnUpdateCalendarTimescale(pCmdUI, 15);
}

void CCalendarDemoView::OnUpdateCalendarTimescale10(CCmdUI* pCmdUI)
{
	OnUpdateCalendarTimescale(pCmdUI, 10);
}

void CCalendarDemoView::OnUpdateCalendarTimescale6(CCmdUI* pCmdUI)
{
	OnUpdateCalendarTimescale(pCmdUI, 6);
}

void CCalendarDemoView::OnUpdateCalendarTimescale5(CCmdUI* pCmdUI)
{
	OnUpdateCalendarTimescale(pCmdUI, 5);
}



void CCalendarDemoView::OnUpdateCalendarTimescale(CCmdUI* pCmdUI, int nScale) 
{
	BOOL bEnable = FALSE;
	BOOL bChecked = FALSE;

	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl().GetActiveView());
	if (pDayView) 
	{
		bEnable = TRUE;
	
		if (pDayView->GetScaleInterval().GetTotalMinutes() == nScale) 
			bChecked = TRUE;
	}
	
	pCmdUI->Enable(bEnable);	
	pCmdUI->SetCheck(bChecked);
}

void CCalendarDemoView::OnUpdateViewReminders(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetCalendarCtrl().IsRemindersEnabled());
}

CString GetModulePath()
{
	TCHAR szCurPath[_MAX_PATH + 2];
	::GetModuleFileName(AfxGetInstanceHandle(), szCurPath, _MAX_PATH);

	CString strCurPath(szCurPath);
	strCurPath = strCurPath.Left(strCurPath.ReverseFind('\\')+1);

	return strCurPath;
}

//void CCalendarDemoView::OnCalendarLangDefault()
//{
//	XTPResourceManager()->SetResourceFile(_T(""));
//
//	GetCalendarCtrl().Populate();
//	
//	m_wndDatePicker.AdjustLayout();
//	m_wndDatePicker.RedrawControl();
//}

//void CCalendarDemoView::OnCalendarLangRussian()
//{
//	CString strRCpath = GetModulePath();
//
//	strRCpath += _T("Translations\\ToolkitPro.ResourceRu.dll");
//			 
//	XTPResourceManager()->SetResourceFile(strRCpath);
//
//	GetCalendarCtrl().Populate();
//
//	m_wndDatePicker.AdjustLayout();
//	m_wndDatePicker.RedrawControl();
//
//}

//////////////////////////////////////////////////////////////////////////
//
void CCalendarDemoView::OnAddNewEvent() 
{
	AddNewEvent();
}

void CCalendarDemoView::AddNewEvent(CPoint* /*pPtHitContext*/) 
{
	CXTPCalendarEventPropertiesDlg dlg(&GetCalendarCtrl(), TRUE, this);
	dlg.DoModal();
}

void CCalendarDemoView::OnCalendarTimezone() 
{
	TRACE(_T("Time zone dialog.\n"));

	CXTPCalendarOptions* pOptions = GetCalendarCtrl().GetCalendarOptions();
	ASSERT(pOptions);
	if (pOptions) 
	{
		CXTPCalendarTimeScalePropertiesDlg dlg;
		// init parameters
		dlg.m_strCaption1 = pOptions->strDayView_ScaleLabel;
		dlg.m_strCaption2 = pOptions->strDayView_Scale2Label;
		dlg.m_bShowScale2 = pOptions->bDayView_Scale2Visible;
		dlg.m_tziScale2	  = pOptions->tziDayView_Scale2TimeZone;

		// execute and save
		if (dlg.DoModal() == IDOK)
		{
			// first time scale
			pOptions->strDayView_ScaleLabel = dlg.m_strCaption1;

			// second time scale
			pOptions->bDayView_Scale2Visible = dlg.m_bShowScale2;
			if (dlg.m_bShowScale2)
			{
				pOptions->strDayView_Scale2Label = dlg.m_strCaption2;
				pOptions->tziDayView_Scale2TimeZone = dlg.m_tziScale2;
			}

			pOptions->OnOptionsChanged();
			// redraw
			GetCalendarCtrl().Populate();
		}		
	}
}

void CCalendarDemoView::OnAdvancedOptions()
{
	CAdvancedCalendarOptionsDlg dlgOptEx(&GetCalendarCtrl(), this);
	
	dlgOptEx.DoModal();
}


void CCalendarDemoView::OnInitialUpdate() 
{
	CXTPCalendarControlView::OnInitialUpdate();
			
	// date picker
	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
		
	//m_CalendarController.SetBoldDaysPerIdleStep(1);
	//m_CalendarController.SetBoldDaysIdleStepTime_ms(999);
	m_CalendarController.SetDatePicker(&pWnd->m_dlgDatePicker.m_wndDatePicker);		
    	
	//---------------------------------------------------------------------------
	m_dtDayViewStart = COleDateTime::GetCurrentTime();
	//---------------------------------------------------------------------------

	((CMainFrame*)GetParentFrame())->m_dlgOptions.Init();

	m_nScale = GetCalendarCtrl().GetCalendarOptions()->nDayView_ScaleInterval;
    
	// initial settings
	OnCalendarViewWorkWeek();

	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl().GetDayView() );
	if(pDayView) {
		pDayView->ScrollToWorkDayBegin();	
	}
	//---------------------------------------------------------------------------
	OnOfficeThemeChanged(xtpCalendarThemeOffice2007);

	CreateRemindersWindow();

	ShowCaptionBar(TRUE);
}

void CCalendarDemoView::OnUpdateTimeScale()
{   
	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl().GetActiveView());
	if (pDayView) 
	{
		pDayView->SetScaleInterval(COleDateTimeSpan(0, m_nScale/60, m_nScale%60, 0));
	} 
	else {
		GetCalendarCtrl().GetCalendarOptions()->nDayView_ScaleInterval = m_nScale;
		GetCalendarCtrl().GetCalendarOptions()->OnOptionsChanged();
	}
}


void CCalendarDemoView::OnEvent_Calendar(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	if (!GetCalendarCtrl().GetActiveView())
		return;

	CPoint ptHit(wParam);
	XTP_CALENDAR_HITTESTINFO hitInfo;
	BOOL bHitTest = GetCalendarCtrl().GetActiveView()->HitTest(ptHit, &hitInfo);

	if (XTP_NC_CALENDARKEYDOWN == Event)
	{
		if (wParam == VK_RETURN && !GetCalendarCtrl().GetActiveView()->IsEditingSubject()
			&& GetCalendarCtrl().GetActiveView()->GetDraggingMode() == xtpCalendaDragModeUnknown)
		{		
			CXTPCalendarViewEvents* selectedEvents = GetCalendarCtrl().GetActiveView()->GetSelectedViewEvents();
			
			if (selectedEvents && selectedEvents->GetCount() > 0)
			{
				
				CXTPCalendarEventPtr ptrEvent = selectedEvents->GetAt(0)->GetEvent()->CloneEvent();
				
				CXTPCalendarEventPropertiesDlg dlg(&GetCalendarCtrl(), FALSE, this, ptrEvent);
				dlg.DoModal();			
				
			}
			else
			{
				AddNewEvent();
				
			}
		}
	}
	else if (XTP_NC_CALENDARCONTEXTMENU == Event)
	{
		if (bHitTest)
		{
			CPoint ptMenu = ptHit;
			GetCalendarCtrl().ClientToScreen(&ptMenu);

			if (hitInfo.pViewEvent)
			{
				CMenu menu;
				VERIFY(menu.LoadMenu(IDR_MENU_CONTEXT_EVENT));
				
				// track menu
				int nMenuResult = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(0), 
					TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, 
					ptMenu.x, ptMenu.y, this, NULL);
				
				// general items processing
				switch (nMenuResult)
				{
				case ID_POPUP_DELETEEVENT:
					{
						VERIFY( GetCalendarCtrl().DoDeleteSelectedEvents(hitInfo.pViewEvent) );
						
						GetCalendarCtrl().Populate();
					}
					break;
				case ID_POPUP_PROPERTIES:
					{
						ASSERT(hitInfo.pViewEvent);
						if(hitInfo.pViewEvent)
						{
							CXTPCalendarEvent* pEvent = hitInfo.pViewEvent->GetEvent();
							CXTPCalendarEventPtr ptrEvent = pEvent->CloneEvent();

							CXTPCalendarControl::CUpdateContext updateContext(&GetCalendarCtrl(), xtpCalendarUpdateLayout|xtpCalendarUpdateRedraw);
							CXTPCalendarEventPropertiesDlg dlg(&GetCalendarCtrl(), FALSE, this, ptrEvent);
							dlg.DoModal();
						}						
					}
					break;
				}
			}
			else if (GetCalendarCtrl().GetActiveView()->IsKindOf( RUNTIME_CLASS(CXTPCalendarDayView) ))
			{
				CMenu menu;
				VERIFY(menu.LoadMenu(IDR_MENU_CONTEXT_DAY));

				CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl().GetActiveView());
				if (pDayView)
				{
					int nInterval = (int)pDayView->GetScaleInterval().GetTotalMinutes();
					int nMenuItem = nInterval >= 60 ? ID_CALENDAR_CHANGETIMESCALE_60MINUTES :
									(nInterval >= 30 ? ID_CALENDAR_CHANGETIMESCALE_30MINUTES :
									(nInterval >= 15 ? ID_CALENDAR_CHANGETIMESCALE_15MINUTES :
									(nInterval >= 10 ? ID_CALENDAR_CHANGETIMESCALE_10MINUTES :
									(nInterval >=  6 ? ID_CALENDAR_CHANGETIMESCALE_6MINUTES :
									(nInterval >=  5 ? ID_CALENDAR_CHANGETIMESCALE_5MINUTES : 0)))));
					menu.CheckMenuItem(nMenuItem, MF_CHECKED);
				}
				
				// track menu
				int nMenuResult = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(0), 
					TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, 
					ptMenu.x, ptMenu.y, this, NULL);
				
				// general items processing
				switch (nMenuResult)
				{
				case ID_CALENDAR_CHANGETIMESCALE_60MINUTES:
					OnCalendarTimescale60();
					break;
				case ID_CALENDAR_CHANGETIMESCALE_30MINUTES:
					OnCalendarTimescale30();
					break;
				case ID_CALENDAR_CHANGETIMESCALE_15MINUTES:
					OnCalendarTimescale15();
					break;
				case ID_CALENDAR_CHANGETIMESCALE_10MINUTES:
					OnCalendarTimescale10();
					break;
				case ID_CALENDAR_CHANGETIMESCALE_6MINUTES:
					OnCalendarTimescale6();
					break;
				case ID_CALENDAR_CHANGETIMESCALE_5MINUTES:
					OnCalendarTimescale5();
					break;
				case ID_CALENDAR_CHANGETIMESCALE_CHANGETIMEZONE:
					OnCalendarTimezone();
					break;
				case ID_CALENDAR_ADD_NEW_EVENT:
					AddNewEvent(&ptHit);
					break;
				default:
					ASSERT(nMenuResult == 0);
				}
			}
			else //if (GetCalendarCtrl().GetActiveView()->IsKindOf( RUNTIME_CLASS(CXTPCalendarWeekView) ))
			{
				CMenu menu;
				VERIFY(menu.LoadMenu(IDR_MENU_CONTEXT_WEEK));
				
				// track menu
				int nMenuResult = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(0), 
					TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, 
					ptMenu.x, ptMenu.y, this, NULL);
				
				// general items processing
				switch (nMenuResult)
				{
				case ID_POPUP_GOTOTHISDAY:
					{					
						GetCalendarCtrl().SwitchActiveView(xtpCalendarDayView);
						CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl().GetActiveView());
						if (pDayView)
						{
							COleDateTime dtThisDay(hitInfo.dt);
							pDayView->ResetSelection();
							pDayView->ShowDay(dtThisDay);							
						}
					}
					break;
				case ID_CALENDAR_ADD_NEW_EVENT:
					AddNewEvent(&ptHit);
					break;
				}
			}
		}
	}
	else if (XTP_NC_CALENDARLBUTTONDBLCLICK == Event)
	{
		if (bHitTest && hitInfo.pViewEvent)
		{
			// mouse double clicked - show event edit dialog
			CXTPCalendarEvent* pEvent = hitInfo.pViewEvent->GetEvent();
			CXTPCalendarEventPtr ptrEvent = pEvent->CloneEvent();
            			
			if(hitInfo.pViewEvent->IsShowingToolTip()) { 
				hitInfo.pViewEvent->HideToolTip(); 
			}

			CXTPCalendarEventPropertiesDlg dlg(&GetCalendarCtrl(), FALSE, this, ptrEvent);
			dlg.DoModal();			
		}
		else if (bHitTest && (hitInfo.uHitCode & (xtpCalendarHitTestDayArea|xtpCalendarHitTestDayHeader)))
		{
			AddNewEvent(&ptHit);
		}
	}
}

void CCalendarDemoView::OnFileSave()
{
	CXTPCalendarData* pData = GetCalendarCtrl().GetDataProvider();
	if(!pData) {
		ASSERT(FALSE);
		return;
	}
	if(GetDPType(pData) == xtpCalendarDataProviderMemory) 
	{
		CString strFileName = AfxGetApp()->GetProfileString(cstrDP_Opt_section, cstrUseDP_Mem_File_opt);
		if(!pData->Save()) 
		{
			CString strDPname = GetDPName(xtpCalendarDataProviderMemory);
			CString strMsg;
			strMsg.Format(_T("%s cannot create file: \n%s"), strDPname, strFileName);
			AfxMessageBox(strMsg);
		}
	}  
}

void CCalendarDemoView::OnFileSaveAs()
{
	CXTPCalendarData* pData = GetCalendarCtrl().GetDataProvider();
	if(!pData) {
		ASSERT(FALSE);
		return;
	}
	if(GetDPType(pData) != xtpCalendarDataProviderMemory) {
		ASSERT(FALSE);
		return;		
	}  

	CDataProvidersOptions optDlg;	
	optDlg.m_strTitle = _T("Save calendar data as:");
	optDlg.m_bOpenMode = FALSE;
	optDlg.m_bWarnIfExist = TRUE;
	optDlg.m_eMode = CDataProvidersOptions::modeMemOnly;

	int nDlgRes = (int)optDlg.DoModal();
	if(nDlgRes != IDOK) {
		return;
	}
	
	CString strFileName = AfxGetApp()->GetProfileString(cstrDP_Opt_section, cstrUseDP_Mem_File_opt);
	if(!pData->Save()) 
	{
		CString strDPname = GetDPName(xtpCalendarDataProviderMemory);
		CString strMsg;
		strMsg.Format(_T("%s cannot create file: \n%s"), strDPname, strFileName);
		AfxMessageBox(strMsg);
	}
}

void CCalendarDemoView::OnUpdateFileSave(CCmdUI* pCmdUI)
{
	CXTPCalendarData* pData = GetCalendarCtrl().GetDataProvider();
	
	int nDPType = GetDPType(pData);
	
	pCmdUI->Enable(nDPType == xtpCalendarDataProviderMemory);
}

void CCalendarDemoView::OnUpdateFileSaveAs(CCmdUI* pCmdUI)
{
	OnUpdateFileSave(pCmdUI);
}

void CCalendarDemoView::OnEvent_IsEditActionDisabled(XTP_NOTIFY_CODE Event, 
													WPARAM wParam, LPARAM lParam)
{   	
	if (XTP_NC_CALENDAR_IS_EVENT_EDIT_OPERATION_DISABLED != Event) {
		ASSERT(FALSE);
		return;
	}

	XTP_EVENT_EDIT_OPERATION_PARAMS* pOPparams = (XTP_EVENT_EDIT_OPERATION_PARAMS*)wParam;
	BOOL* pbCancel = (BOOL*)lParam;
	ASSERT(pbCancel);

	// check is already canceled/handled
	if(!pOPparams || !pbCancel || *pbCancel) {
		return;
	}

	// Disable dragging for recurrence events
	//
//	CXTPCalendarEvent* pEvent = pOPparams->pEventViews->GetAt(0)->GetEvent();
//	ASSERT(pEvent);

//	if((pOPparams->eOperation == xtpCalendarEO_DragCopy || pOPparams->eOperation == xtpCalendarEO_DragMove ||
//		pOPparams->eOperation == xtpCalendarEO_DragResizeBegin || pOPparams->eOperation == xtpCalendarEO_DragResizeEnd)
//		&& pEvent 
//		&& pEvent->GetRecurrenceState() != xtpCalendarRecurrenceNotRecurring) 
//	{
//		*pbCancel = TRUE;
//	}
}

void CCalendarDemoView::OnEvent_BeforeEditAction(XTP_NOTIFY_CODE Event, 
													WPARAM wParam, LPARAM lParam)
{   	
	if (XTP_NC_CALENDAR_BEFORE_EVENT_EDIT_OPERATION != Event) {
		ASSERT(FALSE);
		return;
	}
    	
	XTP_EVENT_EDIT_OPERATION_PARAMS* pOPparams = (XTP_EVENT_EDIT_OPERATION_PARAMS*)wParam;
	BOOL* pbHandled = (BOOL*)lParam;
	ASSERT(pbHandled && pOPparams);

	// check is already canceled/handled
	if(!pOPparams || !pbHandled || *pbHandled) {
		return;
	}

	if(pOPparams->eOperation == xtpCalendarEO_DeleteEvent)
	{
		if(!pOPparams->pEventViews || !pOPparams->pEventViews->GetAt(0)) {
			ASSERT(FALSE);
			return;
		}

		CXTPCalendarEvent* pEvent = pOPparams->pEventViews->GetAt(0)->GetEvent();
		if(!pEvent) {
			ASSERT(FALSE);
			return;
		}

		if(pEvent->GetRecurrenceState() == xtpCalendarRecurrenceNotRecurring)
		{
			CString strMsg;
			strMsg.Format(_T("Would you like to delete event: \"%s\" ?"), pEvent->GetSubject());
			int nRes = AfxMessageBox(strMsg, MB_YESNO);
			if(nRes == IDNO) 
			{
				*pbHandled = TRUE;
			}
		}
	}
	
	//**  since ver 9.81
	//******************
	//if (pOPparams->eOperation == xtpCalendarEO_DragMove ||
	//	pOPparams->eOperation == xtpCalendarEO_DragCopy )
	//{
	//	XTP_EVENT_DRAG_OPERATION_PARAMS* pOpDrag = (XTP_EVENT_DRAG_OPERATION_PARAMS*)pOPparams;
	//	ASSERT(pOpDrag->pDraggingEvent && pOpDrag->pDraggingEventNew);
	//
	//	if(pOpDrag->pDraggingEvent && pOpDrag->pDraggingEventNew)
	//	{
	//		COleDateTime dtOrigStart = pOpDrag->pDraggingEvent->GetStartTime();
	//		COleDateTime dtNewStart = pOpDrag->pDraggingEventNew->GetStartTime();;
	//			
	//		if (CXTPCalendarUtils::ResetTime(dtOrigStart) != CXTPCalendarUtils::ResetTime(dtNewStart) 
	//			|| pOpDrag->pDraggingEvent->IsAllDayEvent() != pOpDrag->pDraggingEventNew->IsAllDayEvent()) 
	//		{
	//			*pbHandled = TRUE;
	//		}
	//	}
	//}

	//**  for ver 9.80
	//******************
	//if(pOPparams->eOperation == xtpCalendarEO_DragMove &&
	//	GetCalendarCtrl().GetActiveView()->GetDraggingEventOrig())
	//{
	//	CPoint pt;
	//	GetCursorPos(&pt);
	//	GetCalendarCtrl().ScreenToClient(&pt);

	//	XTP_CALENDAR_HITTESTINFO hitInfo;
	//	if(GetCalendarCtrl().GetActiveView()->HitTest(pt, &hitInfo)) 
	//	{
	//		COleDateTime dtOrigStart = GetCalendarCtrl().GetActiveView()->GetDraggingEventOrig()->GetStartTime(); 
	//		
	//		// store previous version to rollback
	//		CXTPCalendarEventPtr ptrEventPrev = GetCalendarCtrl().GetActiveView()->GetDraggingEventNew()->CloneEvent(); 
	//		
	//		if(GetCalendarCtrl().GetActiveView()->OnDragging(pt, &hitInfo))
	//		{
	//			CXTPCalendarEvent* pEventNew = GetCalendarCtrl().GetActiveView()->GetDraggingEventNew();
	//			COleDateTime dtNewStart = pEventNew->GetStartTime();
	//
	//			if(CXTPCalendarUtils::ResetTime(dtOrigStart) !=
	//				CXTPCalendarUtils::ResetTime(dtNewStart) ) 
	//			{
	//				*pbHandled = TRUE;
	//			}
	//			
	//			pEventNew->Update(ptrEventPrev);
	//		
	//			//TRACE(_T("orig: %s - point: %s = [%d] \n"), dtOrigStart.Format(), hitInfo.dt.Format(),
	//			//		*pbHandled);
	//		}
	//	}		
	//}
}

void CCalendarDemoView::OnEvent_CalendarData(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(wParam);

	CString strActionText;
    
	switch(Event)
	{
	case XTP_NC_CALENDAREVENTWASADDED:
		strActionText = _T("Event_WasAdded");
		break;
	case XTP_NC_CALENDAREVENTWASDELETED:
		strActionText = _T("Event_WasDeleted");
		break;
	case XTP_NC_CALENDAREVENTWASCHANGED:
		strActionText = _T("Event_WasChanged");
		break;

	case XTP_NC_CALENDARPATTERNWASADDED:
		strActionText = _T("Pattern_WasAdded");
		break;
	case XTP_NC_CALENDARPATTERNWASDELETED:
		strActionText = _T("Pattern_WasDeleted");
		break;
	case XTP_NC_CALENDARPATTERNWASCHANGED:
		strActionText = _T("Pattern_WasChanged");
		break;
	default:
		ASSERT(FALSE);
		return;
	}

	//===========================================================================
	CXTPCalendarData* pData = GetCalendarCtrl().GetDataProvider();
	if(!pData) {
		ASSERT(FALSE);
		return;
	}

	if(Event == XTP_NC_CALENDAREVENTWASADDED || Event == XTP_NC_CALENDAREVENTWASDELETED ||
		Event == XTP_NC_CALENDAREVENTWASCHANGED)
	{
		//EVENT:
		CXTPCalendarEvent* pEvent = (CXTPCalendarEvent*)lParam;
		if(pEvent)
		{
			COleDateTime dtStart = pEvent->GetStartTime();
			COleDateTime dtEnd = pEvent->GetEndTime();
			CString strSubject = pEvent->GetSubject();
			TRACE(_T("%s (ID=%d): %s-%s, '%s' \n"), strActionText, 
					pEvent->GetEventID(), dtStart.Format(), dtEnd.Format(), strSubject);
		} 
		else {
			TRACE(_T("%s (pEvent=%x) \n"), strActionText, wParam);
		}
	}
	else {
		//PATTERN:
		CXTPCalendarRecurrencePatternPtr ptrPattern = pData->GetRecurrencePattern((DWORD)wParam);
		if(ptrPattern)
		{
			COleDateTime dtStartPatt = ptrPattern->GetPatternStartDate();
			CXTPCalendarEventPtr ptrMasterEvent = ptrPattern->GetMasterEvent();
			ASSERT(ptrMasterEvent);
			CString strSubject = ptrMasterEvent ? ptrMasterEvent->GetSubject() : _T("");
			
			TRACE(_T("%s (ID=%d): pattern starts at %s, '%s' \n"), strActionText, 
					wParam, dtStartPatt.Format(), strSubject);
		} 
		else {
			TRACE(_T("%s (ID=%d) \n"), strActionText, wParam);
		}
	}
}

void CCalendarDemoView::CreateRemindersWindow()
{
	if(!s_pDlgReminders || !s_pDlgReminders->GetSafeHwnd()) 
	{
		if(!s_pDlgReminders)
			s_pDlgReminders = new CXTPCalendarRemindersDialog();

		VERIFY( s_pDlgReminders->Create() );
		s_pDlgReminders->CenterWindow();
		
		s_pDlgReminders->SetRemindersManager(&GetCalendarCtrl());
	}
}

void CCalendarDemoView::OnViewReminders()
{	
	s_pDlgReminders->ShowWindow(SW_SHOWNORMAL);
}

//void CCalendarDemoView::OnReminders(XTP_NOTIFY_CODE Event, WPARAM wParam , LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	
//	if (Event != XTP_NC_CALENDAR_ON_REMINDERS) {
//		ASSERT(FALSE);
//		return;
//	}
//
//	int eAction = (int)wParam;
//	if (eAction == xtpCalendarRemindersMonitoringStarted)
//	{
//		CreateRemindersWindow();	
//	}
//	if (eAction == xtpCalendarRemindersMonitoringStopped)
//	{
//		if (s_pDlgReminders)
//		{
//			delete s_pDlgReminders;
//			s_pDlgReminders = NULL;
//		}
//	}
//}

void CCalendarDemoView::OnBeforeDrawThemeObject(XTP_NOTIFY_CODE Event, WPARAM wParam , LPARAM lParam)
{
	ASSERT(Event == XTP_NC_CALENDAR_BEFORE_DRAW_THEMEOBJECT);
	if (Event != XTP_NC_CALENDAR_BEFORE_DRAW_THEMEOBJECT)
		return;

	CXTPCalendarThemeOffice2007* pTheme2007 = DYNAMIC_DOWNCAST(CXTPCalendarThemeOffice2007, GetCalendarCtrl().GetTheme());
	ASSERT(pTheme2007);
	if (!pTheme2007)
		return;
		
	static CFont s_fntStriked;
	if (s_fntStriked.m_hObject == NULL)
	{
		LOGFONT lfIcon;
		VERIFY(::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lfIcon), &lfIcon, 0));
		lfIcon.lfWeight = FW_BOLD;

		lfIcon.lfStrikeOut = 1;
		
		s_fntStriked.CreateFontIndirect(&lfIcon);
	}

	if (wParam == xtpCalendarBeforeDraw_DayViewEvent)
	{
		CXTPCalendarDayViewEvent* pViewEvent = (CXTPCalendarDayViewEvent*)lParam;
		if (pViewEvent && pViewEvent->GetEvent()->GetSubject().Left(1) == _T("*"))
		{
			
			pTheme2007->GetDayViewPartX()->GetDayPartX()->GetGroupPartX()->GetSingleDayEventPartX()->m_fcsetNormal.fcsetSubject.fntFont.SetCustomValue(&s_fntStriked);
			pTheme2007->GetDayViewPartX()->GetDayPartX()->GetGroupPartX()->GetMultiDayEventPartX()->m_fcsetNormal.fcsetSubject.fntFont.SetCustomValue(&s_fntStriked);

			pTheme2007->GetDayViewPartX()->GetDayPartX()->GetGroupPartX()->GetSingleDayEventPartX()->m_fcsetSelected.fcsetSubject.fntFont.SetCustomValue(&s_fntStriked);
			pTheme2007->GetDayViewPartX()->GetDayPartX()->GetGroupPartX()->GetMultiDayEventPartX()->m_fcsetSelected.fcsetSubject.fntFont.SetCustomValue(&s_fntStriked);
		}
	}

	if (wParam == xtpCalendarBeforeDraw_MonthViewDay)
	{
		CXTPCalendarMonthViewDay* pDay = (CXTPCalendarMonthViewDay*)lParam;
		
		if (pDay->GetDayDate().GetDayOfWeek() == 3)
		{
			pTheme2007->GetMonthViewPartX()->GetDayPartX()->m_clrBackgroundDark = RGB(196, 128, 128);
			pTheme2007->GetMonthViewPartX()->GetDayPartX()->m_clrBackgroundLight = RGB(230, 128, 128);
			pTheme2007->GetMonthViewPartX()->GetDayPartX()->m_clrBackgroundSelected = RGB(128, 228, 228);
		}
	}	
}

void CCalendarDemoView::OnEvent_GetItemText(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	XTP_CALENDAR_GETITEMTEXT_PARAMS* pParams = (XTP_CALENDAR_GETITEMTEXT_PARAMS*)wParam ;
	
	if (XTP_NC_CALENDAR_GETITEMTEXT != Event || !pParams)
		return;

	if (xtpCalendarItemText_EventMarkupTemplate == pParams->nItem)
	{
		pParams->pstrText->Format(cstrMarkupDynamicSample);
	}

	if (xtpCalendarItemText_EventSubject == pParams->nItem)
	{
		// Dynamically customize Location text
		pParams->pstrText->MakeReverse();
	}

}

CXTPCalendarControl_Custom::CXTPCalendarControl_Custom()
{
	m_nToolTipMode = ctmStandard;
}

INT_PTR CXTPCalendarControl_Custom::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	if(m_nToolTipMode == ctmCustom)
	{	
		XTP_CALENDAR_HITTESTINFO hitTest;
		if( ((CXTPCalendarControl*)this)->GetActiveView()->HitTest(point, &hitTest))
		{
			if(hitTest.pViewEvent) 
			{
				pTI->hwnd = m_hWnd; //   Handle to a window 
				pTI->uId = (UINT_PTR)m_hWnd; //   Handle to a child window 
				pTI->uFlags |= TTF_IDISHWND | TTF_NOTBUTTON; 

				CString strToolText;
				strToolText.Format(_T("[ID = 0x%08X] (%s - %s) %s"),
					hitTest.pViewEvent->GetEvent()->GetEventID(),					
					hitTest.pViewEvent->FormatEventTime(hitTest.pViewEvent->GetEvent()->GetStartTime()),
					hitTest.pViewEvent->FormatEventTime(hitTest.pViewEvent->GetEvent()->GetEndTime()),
					hitTest.pViewEvent->GetEvent()->GetSubject()
					);

				int nBuffSize = strToolText.GetLength()*2 +10;
				TCHAR* pBuffer = (TCHAR*)malloc(nBuffSize);
				
				STRCPY_S(pBuffer, nBuffSize, (LPCTSTR)strToolText);
				
				pTI->lpszText = pBuffer;
				
				return 333;
			}
		}		
	}
	
	return CXTPCalendarControl::OnToolHitTest(point, pTI);	
}

void CCalendarDemoView::OnEvent_PrePopulate(XTP_NOTIFY_CODE Event, 
											 WPARAM wParam, LPARAM lParam)
{   	
	UNREFERENCED_PARAMETER(wParam);

	if (XTP_NC_CALENDAR_PREPOPULATE != Event) {
		ASSERT(FALSE);
		return;
	}

	// Theme 2007.
	CXTPCalendarThemeOffice2007* pTheme2007 = DYNAMIC_DOWNCAST(CXTPCalendarThemeOffice2007, GetCalendarCtrl().GetTheme());
	if (!pTheme2007)
		return;

//	pTheme2007->SetBeforeDrawFlags(pTheme2007->GetBeforeDrawFlags() | xtpCalendarBeforeDraw_MonthViewDay);
//	pTheme2007->SetBeforeDrawFlags(pTheme2007->GetBeforeDrawFlags() | xtpCalendarBeforeDraw_DayViewEvent);

	// add icons for reminder and meting flags as custom icons
	// See Also: 
	//	CAdvancedCalendarOptionsDlg::OnOK() 
	//	The custom icons images added there and IDs assigned to them. 

	// wParam - [in] CXTPCalendarViewGroup* - A pointer to Group View.
	// lParam - [in/out] CXTPCalendarEvents* - A pointer to events array to draw.

	CXTPCalendarEvents* pEvents = (CXTPCalendarEvents*)lParam;
	ASSERT(pEvents);
	if (!pEvents)
		return;

	int nCount = pEvents->GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CXTPCalendarEvent* pEvent = pEvents->GetAt(i);
		ASSERT(pEvent);

		if (!pEvent)
			continue;

		if (pEvent->IsReminder()) {				
			pEvent->GetCustomIcons()->AddIfNeed((UINT)xtpCalendarEventIconIDReminder);
		}
		else {
			pEvent->GetCustomIcons()->RemoveID((UINT)xtpCalendarEventIconIDReminder);
		}

		if (pEvent->IsMeeting()) {
			pEvent->GetCustomIcons()->AddIfNeed((UINT)xtpCalendarEventIconIDMeeting);
		}
		else {
			pEvent->GetCustomIcons()->RemoveID((UINT)xtpCalendarEventIconIDMeeting);
		}

		//-------------------------------------------------------------------
		// There are 3 standard icons for Office2007 theme: 
		//  * recurrence occurrence
		//  * recurrence exception
		//  * private
		// Its IDs are from from XTPCalendarEventIconIDs enum.
		// If custom icons have an icon with the same ID as standard 
		// icon - custom icon will be used instead of standard.
		//-------------------------------------------------------------------
		
		// this code customize private icon from the standard Office2007 
		// theme set. 
		//
		// uncomment code below to see the customization. 		
		
		//if (pEvent->IsPrivate()) {
		//	pEvent->GetCustomIcons()->AddIfNeed((UINT)xtpCalendarEventIconIDPrivate);
		//}
		//else 
		{
			pEvent->GetCustomIcons()->RemoveID((UINT)xtpCalendarEventIconIDPrivate);
		}
		
	}
}

//void CCalendarDemoView::OnEvent_SelChanged(XTP_NOTIFY_CODE Event, 
//												 WPARAM wParam, LPARAM lParam)
//{   	
//	if (XTP_NC_CALENDAR_SELECTION_CHANGED != Event) {
//		ASSERT(FALSE);
//		return;
//	}
//	if(wParam != xtpCalendarSelectionEvents) {
//		return;
//	}
//
//	static BOOL s_bInProgress = FALSE;
//
//	CXTPCalendarView* pView = GetCalendarCtrl().GetActiveView();
//
//	if(!pView || s_bInProgress) {
//		return;
//	}
//
//	if(pView->GetSelectedEvents()->GetCount() <= 1) {
//		return;
//	}
//	
//	// Protect from processing self sending notifications.
//	//
//	// see lines below:
//	//		pView->UnselectAllEvents(); // will send XTP_NC_CALENDAR_SELECTION_CHANGED
//	//		pView->SelectEvent(pLastSelEView->GetEvent()); // will send XTP_NC_CALENDAR_SELECTION_CHANGED
//	//
//	s_bInProgress = TRUE;
//
//	CXTPCalendarViewEvent* pLastSelEView = pView->GetLastSelectedViewEvent();
//	if(pLastSelEView) 
//	{
//		// Lock event view
//		// for case when it can be destroyed in UnselectAllEvents() call.
//		pLastSelEView->InternalAddRef();
//
//		pView->UnselectAllEvents();
//		pView->SelectEvent(pLastSelEView->GetEvent());
//
//		// Unlock event view 
//		pLastSelEView->InternalRelease();
//	}
//	
//	s_bInProgress = FALSE;
//}

void CCalendarDemoView::OnOfficeThemeChanged(int nCalendarTheme)
{
	CXTPCalendarControl::CUpdateContext updateContext(&GetCalendarCtrl(), xtpCalendarUpdateAll);

	GetCalendarCtrl().SetPaintTheme((XTPCalendarTheme)nCalendarTheme);

	if (nCalendarTheme == xtpCalendarThemeOffice2007)
	{
		m_wndScrollBar.SetScrollBarStyle(xtpScrollStyleOffice2007Dark);
	}
	else
	{
		m_wndScrollBar.SetScrollBarStyle(xtpScrollStyleDefault);
	}
}















