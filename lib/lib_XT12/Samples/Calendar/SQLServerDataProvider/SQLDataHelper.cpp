// SQLDataHelper.cpp: implementation of the CSQLDataHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SQLServerDataProvider.h"
#include "SQLDataHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AFX_INLINE CString _MakeSQLDateTime(DATE t)
{
	COleDateTime ct(t);
	return ct.Format(_T("{ts'%Y-%m-%d %H:%M:%S'}"));
}

void TRACE_ComError(_com_error &e)
{
	CXTPCalendarDatabaseDataProvider::TRACE_ComError(e);
}

//===========================================================================
void TRACE_ProviderError(XTPADODB::_Connection* pConnDB)
{
	CXTPCalendarDatabaseDataProvider::TRACE_ProviderError(pConnDB);
}

void TRACE_ProviderError(XTPADODB::_Recordset* pRS)
{
	ASSERT(pRS);

	if (pRS && pRS->GetActiveConnection().vt == VT_DISPATCH &&
		pRS->GetActiveConnection().pdispVal)
	{
		XTPADODB::_Connection* pConnDB = NULL;
		HRESULT hr = pRS->GetActiveConnection().pdispVal->QueryInterface(__uuidof(XTPADODB::_Connection), (void**)&pConnDB);
		if (SUCCEEDED(hr))
		{
			TRACE_ProviderError(pConnDB);
		}
	}
}

template<class _TData>
_TData _GetField(XTPADODB::_Recordset* pRS, LPCTSTR pcszFName, _TData defVal)
{
	_TData dataValue;
	try
	{
		XTPADODB::FieldPtr ptrField = pRS->Fields->GetItem(pcszFName);
		if (ptrField)
		{
			_variant_t vtValue = ptrField->Value;

			if (vtValue.vt == VT_NULL || vtValue.vt == VT_EMPTY ||
				vtValue.vt == VT_ERROR)
			{
				return defVal;
			}

			dataValue = (_TData)vtValue;
			return dataValue;
		}
	}
	catch (_com_error &e)
	{
		e;
#ifdef _DEBUG
		if (pRS->GetActiveConnection().vt == VT_DISPATCH &&
			pRS->GetActiveConnection().pdispVal)
		{
			XTPADODB::_Connection* pConnDB = NULL;
			HRESULT hr = pRS->GetActiveConnection().pdispVal->QueryInterface(__uuidof(XTPADODB::_Connection), (void**)&pConnDB);
			if (SUCCEEDED(hr))
			{
				TRACE_ProviderError(pConnDB);
			}
		}
		TRACE_ComError(e);
#endif
	}
	catch(...)
	{}

	TRACE(_T("ERROR: CalendarDB provider: Cannot Get field '%s' \n"), pcszFName);
	return defVal;
}

BOOL _SetField(XTPADODB::_Recordset* pRS, LPCTSTR pcszFName, _variant_t vtValue, VARTYPE vtType = VT_ILLEGAL)
{		
	try
	{
		XTPADODB::FieldPtr ptrField = pRS->Fields->GetItem(pcszFName);
		if (ptrField)
		{
			if (vtType != VT_ILLEGAL)
			{
				// Implemented to set VT_DATE instead of VT_R8.
				// VariantChangeType may be used for more complex situations.
				//
				ASSERT(vtType == VT_DATE || vtType == vtValue.vt);

				vtValue.vt = vtType;
			}

			ptrField->Value = vtValue;
			return TRUE;
		}
	}
	catch (_com_error &e)
	{
		e;
#ifdef _DEBUG
		if (pRS->GetActiveConnection().vt == VT_DISPATCH &&
			pRS->GetActiveConnection().pdispVal)
		{
			XTPADODB::_Connection* pConnDB = NULL;
			HRESULT hr = pRS->GetActiveConnection().pdispVal->QueryInterface(__uuidof(XTPADODB::_Connection), (void**)&pConnDB);
			if (SUCCEEDED(hr))
			{
				TRACE_ProviderError(pConnDB);
			}
		}
		TRACE_ComError(e);
#endif
	}
	catch(...)
	{}

	TRACE(_T("ERROR: CalendarDB provider: Cannot Set field '%s' \n"), pcszFName);
	return FALSE;
}

CSQLDataHelper::CSQLDataHelper(CXTPCalendarData* pDataProvider, XTPADODB::_Connection* pDBconn)
{
	ASSERT(pDataProvider);
	m_pDataProvider = pDataProvider;
	if (m_pDataProvider)
		m_pDataProvider->InternalAddRef();

	m_ptrDBconn = pDBconn;
}

CSQLDataHelper::~CSQLDataHelper()
{
	if (m_pDataProvider)
		m_pDataProvider->InternalRelease();
	m_pDataProvider = NULL;
}

CString CSQLDataHelper::MakeRetrieveDayEventsSQL(COleDateTime dtDay)
{
	CString strSQL;

	TCHAR szBuffer[64];
	CString strYear = ITOT_S(dtDay.GetYear(), szBuffer, 64);
	CString strMonth = ITOT_S(dtDay.GetMonth(), szBuffer, 64);
	CString strDay = ITOT_S(dtDay.GetDay(), szBuffer, 64);

	strSQL = _T("SELECT * FROM CalendarEvents WHERE \r\n");
		
	strSQL += _T(" ( RecurrenceState = 0 OR RecurrenceState = 1 ) AND \r\n"); //xtpCalendarRecurrenceNotRecurring OR xtpCalendarRecurrenceMaster
	
	strSQL += _T("( YEAR(StartDateTime) < ") + strYear + _T("\r\n");
	strSQL += _T("  OR ( YEAR(StartDateTime) = ") + strYear + _T(" AND \r\n");
	strSQL += _T("       ( MONTH(StartDateTime) < ") + strMonth + _T(" OR \r\n");
	strSQL += _T("         MONTH(StartDateTime) = ") + strMonth + _T(" AND \r\n");
	strSQL += _T("         DAY(StartDateTime) <= ") + strDay + _T("\r\n");

	strSQL += _T("     ) ) ) AND \r\n");

	strSQL += _T("( YEAR(EndDateTime) > ") + strYear + _T("\r\n");
	strSQL += _T("  OR ( YEAR(EndDateTime) = ") + strYear + _T(" AND \r\n");
	strSQL += _T("       ( MONTH(EndDateTime) > ") + strMonth + _T(" OR \r\n");
	strSQL += _T("         MONTH(EndDateTime) = ") + strMonth + _T(" AND \r\n");
	strSQL += _T("         DAY(EndDateTime) >= ") + strDay + _T("\r\n");
	strSQL += _T("     ) ) ) \r\n");

	return strSQL;
}

CString CSQLDataHelper::MakeGetUpcomingEventsSQL(COleDateTime dtFrom, int nPeriodMinutes, BOOL bOptimized)
{
	// The SQL script below can be created in 2 ways - simple or optimized.
	//
	// * The simple script is read all events from DB.
	//   RemindersManager will filter events and use only events with reminder 
	//   which will be Fired untill dtFrom + PeriodMinutes. 
	//   This can be very slow operation, 
	//   but it is called no so often - once per 2 hours by default.
	// 
	// * The optimized script is filter events instead of reminder manager.
	//   This can significantly improve performance.
	//
	// The simple variant can be useful for some debug purposes.
	// 
	// NOTE: generally dtFrom is Now.
	
	TCHAR szBuffer[64];
	CString strRState_no = ITOT_S(xtpCalendarRecurrenceNotRecurring, szBuffer, 64);		
	CString strRState_master = ITOT_S(xtpCalendarRecurrenceMaster, szBuffer, 64);				
	CString strRState_exception = ITOT_S(xtpCalendarRecurrenceException, szBuffer, 64);

	CString strSQL = _T("SELECT * FROM CalendarEvents WHERE \r\n");
	strSQL += _T(" (RecurrenceState = ") + strRState_no + _T(" OR \r\n");			
	strSQL += _T("  RecurrenceState = ") + strRState_master + _T(") \r\n");

	//----------------------------------------------------------
	if(bOptimized)
	{
		COleDateTime dtUntil = dtFrom + CXTPCalendarUtils::Minutes2Span(nPeriodMinutes);
		CString strUntil = _MakeSQLDateTime(dtUntil);
		
		strSQL += _T(" AND \r\n");
		strSQL += _T(" ( IsReminder <> 0 OR \r\n");
		strSQL += _T("     ( RecurrenceState = ") + strRState_master + _T(" AND \r\n");
		strSQL += _T("       RecurrencePatternID IN ");
		strSQL += _T("         ( SELECT RecurrencePatternID  FROM CalendarEvents \r\n");
		strSQL += _T("           WHERE ");
		strSQL += _T("             RecurrenceState = ")  + strRState_exception + _T(" AND \r\n");
		strSQL += _T("             IsReminder <> 0 AND ");
		strSQL += _T("				DATEADD(\"n\", -1 * ReminderMinutesBeforeStart, StartDateTime) <= ") + strUntil + _T("\r\n");
		strSQL += _T("         ) \r\n");
		strSQL += _T("     ) \r\n");
		strSQL += _T(" ) AND \r\n");
		strSQL += _T(" DATEADD(\"n\", -1 * ReminderMinutesBeforeStart, StartDateTime) <= ") + strUntil;
	}

	return strSQL;
}

CXTPCalendarEventsPtr CSQLDataHelper::CreateEventsFromData(XTPADODB::_Recordset* pRSevents, BOOL bCloseRS)
{
	if (!pRSevents || m_ptrDBconn == NULL) 
	{
		ASSERT(FALSE);
		return NULL;
	}

	CXTPCalendarEventsPtr ptrEvents = new CXTPCalendarEvents();
	if (!ptrEvents)
	{
		return NULL;
	}
	CXTPCalendarEventPtr  ptrEvent;
	
 	try
	{
		// process recordset
		while(!pRSevents->bEOF)
		{
			ptrEvent = _CreateEventFromData(pRSevents, FALSE);
			ASSERT(ptrEvent);

			if (ptrEvent)
			{
				ptrEvents->Add(ptrEvent);
			}

			// next record
			pRSevents->MoveNext();
		}

		//----------------
		if (bCloseRS && pRSevents->GetState() == XTPADODB::adStateOpen) 
		{
			pRSevents->Close();
		}

		return ptrEvents;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch(...)
	{}

	TRACE(_T("ERROR: Exeption in CSQLDataHelper::CreateEventsFromData \n"));
	return NULL;
}

CXTPCalendarEventPtr CSQLDataHelper::CreateEventFromData(XTPADODB::_Recordset* pRSevent, BOOL bCloseRS)
{
	if (!pRSevent || m_ptrDBconn == NULL) 
	{
		ASSERT(FALSE);
		return NULL;
	}
			
 	try
	{
		CXTPCalendarEventPtr ptrEvent;

		// process recordset
		if(!pRSevent->bEOF)
		{
			ptrEvent = _CreateEventFromData(pRSevent, FALSE);
			ASSERT(ptrEvent);
		}

		//----------------
		if (bCloseRS && pRSevent->GetState() == XTPADODB::adStateOpen) 
		{
			pRSevent->Close();
		}

		return ptrEvent;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch(...)
	{}

	TRACE(_T("ERROR: Exeption in CSQLDataHelper::CreateEventFromData \n"));
	return NULL;

}

CXTPCalendarEventPtr CSQLDataHelper::_CreateEventFromData(XTPADODB::_Recordset* pRS, BOOL bException)
{
	try
	{
		ASSERT(m_pDataProvider);

		if (!pRS || pRS->GetState() != XTPADODB::adStateOpen || !m_pDataProvider || m_ptrDBconn == NULL) 
		{
			return NULL;
		}			
				
		DWORD dwEventID = (DWORD)(long)pRS->Fields->GetItem(_T("EventID"))->Value;
		CXTPCalendarEventPtr ptrEvent = m_pDataProvider->CreateNewEvent(dwEventID);
		if (!ptrEvent)
			return NULL;

		ptrEvent->SetEndTime((DATE)pRS->Fields->GetItem(_T("EndDateTime"))->Value);
		ptrEvent->SetStartTime((DATE)pRS->Fields->GetItem(_T("StartDateTime"))->Value);

		ptrEvent->SetAllDayEvent(_GetField<long>(pRS, _T("IsAllDayEvent"), 0) != 0);

		ptrEvent->SetSubject(_GetField<_bstr_t>(pRS, _T("Subject"), _T("") ));
		ptrEvent->SetLocation(_GetField<_bstr_t>(pRS, _T("Location"), _T("") ));
		ptrEvent->SetBody(_GetField<_bstr_t>(pRS, _T("Body"), _T("") ));

		ptrEvent->SetReminderSoundFile(_GetField<_bstr_t>(pRS, _T("RemainderSoundFile"), _T("") ));

		ptrEvent->SetBusyStatus(_GetField<long>(pRS, _T("BusyStatus"), 0));
		ptrEvent->SetImportance(_GetField<long>(pRS, _T("ImportanceLevel"), 0));
		ptrEvent->SetLabelID(_GetField<long>(pRS, _T("LabelID"), 0));
		ptrEvent->SetScheduleID(_GetField<long>(pRS, _T("ScheduleID"), 0));

		ptrEvent->SetCreationTime(_GetField<DATE>(pRS, _T("Created"), 0));
		ptrEvent->SetLastModificationTime(_GetField<DATE>(pRS, _T("Modified"), 0));

		ptrEvent->SetMeeting(_GetField<long>(pRS, _T("IsMeeting"), 0) != 0);
		ptrEvent->SetPrivate(_GetField<long>(pRS, _T("IsPrivate"), 0) != 0);

		ptrEvent->SetReminder(_GetField<long>(pRS, _T("IsReminder"), 0) != 0);
		ptrEvent->SetReminderMinutesBeforeStart(_GetField<long>(pRS, _T("ReminderMinutesBeforeStart"), 0));

		if (ptrEvent->GetCustomIcons())
		{
			_bstr_t bstrArray = _GetField<_bstr_t>(pRS, _T("CustomIconsIDs"), _T(""));				
			ptrEvent->GetCustomIcons()->LoadFromString(bstrArray);
		}

		if (ptrEvent->GetCustomProperties())
		{
			_bstr_t bstrPropsXMLData = _GetField<_bstr_t>(pRS, _T("CustomPropertiesXMLData"), _T("") );
			ptrEvent->GetCustomProperties()->LoadFromXML(bstrPropsXMLData);
		}
			
		if(bException)
		{
			ptrEvent->MakeAsRException();

			ptrEvent->SetRException_StartTimeOrig((DATE)pRS->Fields->GetItem(_T("RExceptionStartTimeOrig"))->Value);
			ptrEvent->SetRException_EndTimeOrig((DATE)pRS->Fields->GetItem(_T("RExceptionEndTimeOrig"))->Value);
			ptrEvent->SetRExceptionDeleted(_GetField<long>(pRS, _T("ISRecurrenceExceptionDeleted"), 0) != 0);
		} 
		else // if(!bException)
		{			        
			//	"process_RecurrenceState" and "process_RecurrencePatternID" properties
			//	 are used to process master events.
			//	
			//	 If they are set and RecurrenceStaie is Master Data provider will
			//	 fier DoReadRPattern event and make event as Master.
			//	 And it will also generate occurrences for RetrieveDayEvents method.
			//	
			//	 These properties are temporary and they will be removed by data provider.
			//	
			//	 If these properties are not set data provider expect that master event
			//	 is already compleated - CreateRecurrence method is called and
			//	 Recurrence pattern is set.
			//	
			//	 This mechanism is useful for DB data providers, when events and patterns
			//	 are stored separately (in tables).
			//	 But if events stored in some memory collection or array
			//	 it should not be used because master event store recurrence pattern inside.

			long nRState = _GetField<long>(pRS, _T("RecurrenceState"), xtpCalendarRecurrenceNotRecurring);
			long nPatternID = _GetField<long>(pRS, _T("RecurrencePatternID"), XTP_CALENDAR_UNKNOWN_RECURRENCE_PATTERN_ID);

			ptrEvent->GetCustomProperties()->SetProperty(cszProcess_RecurrenceState, COleVariant((long)nRState));
			ptrEvent->GetCustomProperties()->SetProperty(cszProcess_RecurrencePatternID, COleVariant((long)nPatternID));
		}
			
		return ptrEvent;    	
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch(...)
	{}

	TRACE(_T("ERROR: Exeption in CSQLDataHelper::_CreateEventFromData \n"));
	return NULL;

}

void CSQLDataHelper::PutEventToData(CXTPCalendarEvent* pEvent, XTPADODB::_Recordset* pRS)
{
	try
	{
		ASSERT(pEvent && pRS);
		ASSERT(m_pDataProvider);

		if (!pEvent || !pRS || pRS->GetState() != XTPADODB::adStateOpen || !m_pDataProvider || m_ptrDBconn == NULL) 
		{
			return;
		}			
				
//		pRS->Fields->GetItem(_T("EventID"))->Value = (long)pEvent->GetEventID();
		
		BOOL bStart = _SetField(pRS, _T("StartDateTime"), (DATE)pEvent->GetStartTime(), VT_DATE);
		BOOL bEnd = _SetField(pRS, _T("EndDateTime"), (DATE)pEvent->GetEndTime(), VT_DATE);

		if (!bStart || !bEnd)
		{
			return;
		}
		
		_SetField(pRS, _T("IsAllDayEvent"), (long)pEvent->IsAllDayEvent());

		_SetField(pRS, _T("Subject"),	_bstr_t(pEvent->GetSubject()) );
		_SetField(pRS, _T("Location"),	_bstr_t(pEvent->GetLocation()) );
		_SetField(pRS, _T("Body"),		_bstr_t(pEvent->GetBody()) );

		_SetField(pRS, _T("RemainderSoundFile"), _bstr_t(pEvent->GetReminderSoundFile()) );

		_SetField(pRS, _T("BusyStatus"),		(long)pEvent->GetBusyStatus());
		_SetField(pRS, _T("ImportanceLevel"),	(long)pEvent->GetImportance());
		_SetField(pRS, _T("LabelID"),			(long)pEvent->GetLabelID());
		_SetField(pRS, _T("ScheduleID"),		(long)pEvent->GetScheduleID());

		_SetField(pRS, _T("Created"),	(DATE)pEvent->GetCreationTime(), VT_DATE);
		_SetField(pRS, _T("Modified"),	(DATE)pEvent->GetLastModificationTime(), VT_DATE);

		_SetField(pRS, _T("IsMeeting"), (long)pEvent->IsMeeting());
		_SetField(pRS, _T("IsPrivate"), (long)pEvent->IsPrivate());

		_SetField(pRS, _T("IsReminder"), (long)pEvent->IsReminder());
		_SetField(pRS, _T("ReminderMinutesBeforeStart"), (long)pEvent->GetReminderMinutesBeforeStart());

		if (pEvent->GetCustomIcons())
		{
			CString strArray = pEvent->GetCustomIcons()->SaveToString();
			_SetField(pRS, _T("CustomIconsIDs"), _bstr_t(strArray));
		}

		if (pEvent->GetCustomProperties())
		{
			CString strCustProps;
			pEvent->GetCustomProperties()->SaveToXML(strCustProps);
			_SetField(pRS, _T("CustomPropertiesXMLData"), _bstr_t(strCustProps) );
		}
				
		_SetField(pRS, _T("RecurrenceState"),	  (long)pEvent->GetRecurrenceState());		
		_SetField(pRS, _T("RecurrencePatternID"), (long)pEvent->GetRecurrencePatternID());

		_SetField(pRS, _T("RExceptionStartTimeOrig"), (DATE)pEvent->GetRException_StartTimeOrig(), VT_DATE);
		_SetField(pRS, _T("RExceptionEndTimeOrig"),	  (DATE)pEvent->GetRException_EndTimeOrig(), VT_DATE);
				
		_SetField(pRS, _T("ISRecurrenceExceptionDeleted"), (long)pEvent->IsRExceptionDeleted());
						
		return;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch(...)
	{}

	TRACE(_T("ERROR: Exeption in CSQLDataHelper::PutEventToData \n"));
}

CXTPCalendarRecurrencePatternPtr CSQLDataHelper::CreatePatternFromData(XTPADODB::_Recordset* pRS)
{
	try
	{
		ASSERT(m_pDataProvider);

		if (!pRS || pRS->GetState() != XTPADODB::adStateOpen || !m_pDataProvider || m_ptrDBconn == NULL) 
		{
			return NULL;
		}			
		DWORD dwPatternID = (DWORD)(long)pRS->Fields->GetItem(_T("RecurrencePatternID"))->Value;
		CXTPCalendarRecurrencePatternPtr ptrPattern = m_pDataProvider->CreateNewRecurrencePattern(dwPatternID);

		if (!ptrPattern)
			return NULL;

		ptrPattern->SetMasterEventID((DWORD)(long)pRS->Fields->GetItem(_T("MasterEventID"))->Value);
						    
		ptrPattern->SetPatternStartDate((DATE)pRS->Fields->GetItem(_T("PatternStartDate"))->Value);
		
		int nUseEnd = _GetField<long>(pRS, _T("PatternEndMethod"), xtpCalendarPatternEndNoDate);
		if (nUseEnd == xtpCalendarPatternEndDate)
		{
			ptrPattern->SetPatternEndDate(_GetField<DATE>(pRS, _T("PatternEndDate"), 0));
		}
		else if (nUseEnd == xtpCalendarPatternEndAfterOccurrences)
		{
			ptrPattern->SetEndAfterOccurrences(_GetField<long>(pRS, _T("PatternEndAfterOccurrences"), 1));
		}
		else 
		{
			ASSERT(nUseEnd == xtpCalendarPatternEndNoDate);
			ptrPattern->SetNoEndDate();
		}
		
		long nData1 = (long)pRS->Fields->GetItem(_T("OptionsData1"))->Value;
		long nData2 = (long)pRS->Fields->GetItem(_T("OptionsData2"))->Value;
		long nData3 = (long)pRS->Fields->GetItem(_T("OptionsData3"))->Value;
		long nData4 = (long)pRS->Fields->GetItem(_T("OptionsData4"))->Value;
				
		XTP_CALENDAR_RECURRENCE_OPTIONS _options;		
		_options.SetData(nData1, nData2, nData3, nData4);
		
		// for previous versions use code below instead of SetData
		//
		//_options.m_nRecurrenceType = (XTPCalendarEventRecurrenceType)nData1;
		//_options.m_YearNth.nWhichDay = nData2;
		//_options.m_YearNth.nWhichDayMask = nData3;
		//_options.m_YearNth.nMonthOfYear = nData4;
		
		ptrPattern->SetRecurrenceOptions(_options);
					
		ptrPattern->SetStartTime(_GetField<DATE>(pRS, _T("EventStartTime"), 0));
		ptrPattern->SetDurationMinutes(_GetField<long>(pRS, _T("EventDuration"), 0));

		
		if (ptrPattern->GetCustomProperties())
		{
			_bstr_t bstrPropsXMLData = _GetField<_bstr_t>(pRS, _T("CustomPropertiesXMLData"), _T("") );
			ptrPattern->GetCustomProperties()->LoadFromXML(bstrPropsXMLData);
		}
				          
		pRS->Close();

		ReadRPatternExceptions(ptrPattern);
				
		return ptrPattern;    	
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch(...)
	{}

	TRACE(_T("ERROR: Exeption in CSQLDataHelper::CreatePatternFromData \n"));
	return NULL;
}

void CSQLDataHelper::ReadRPatternExceptions(CXTPCalendarRecurrencePattern* pPattern)
{
	if (!pPattern || m_ptrDBconn == NULL) 
	{
		ASSERT(FALSE);
		return;
	}
			
 	try
	{
		CString strSQL;
		strSQL.Format(_T("SELECT * FROM CalendarEvents WHERE RecurrenceState = %d AND RecurrencePatternID = %d"),
					  xtpCalendarRecurrenceException, pPattern->GetPatternID());

		XTPADODB::_RecordsetPtr ptrRS = m_ptrDBconn->Execute(_bstr_t(strSQL), NULL, XTPADODB::adOptionUnspecified);		
		if (ptrRS == NULL)
		{
			ASSERT(FALSE);
			return;	  
		}

		// process recordset
		while(!ptrRS->bEOF)
		{
			CXTPCalendarEventPtr ptrEvent = _CreateEventFromData(ptrRS, TRUE);
			ASSERT(ptrEvent);

			if (ptrEvent)
			{
				pPattern->SetException(ptrEvent);
			}

			// next record
			ptrRS->MoveNext();
		}

		//----------------
		ptrRS->Close();
				
		return;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch(...)
	{}

	TRACE(_T("ERROR: Exeption in CSQLDataHelper::ReadRPatternExceptions \n"));
}

void CSQLDataHelper::PutPatternToData(CXTPCalendarRecurrencePattern* pPattern, XTPADODB::_Recordset* pRS)
{
	try
	{
		ASSERT(pPattern && pRS);
		ASSERT(m_pDataProvider && m_ptrDBconn != NULL);

		if (!pPattern || !pRS || pRS->GetState() != XTPADODB::adStateOpen || !m_pDataProvider || m_ptrDBconn == NULL) 
		{
			return;
		}
		
		_SetField(pRS, _T("MasterEventID"), (long)pPattern->GetMasterEventID());						    
		_SetField(pRS, _T("PatternStartDate"), (DATE)pPattern->GetPatternStartDate(), VT_DATE);
				
		_SetField(pRS, _T("PatternEndMethod"), (long)pPattern->GetUseEndMethod());
		_SetField(pRS, _T("PatternEndDate"), (DATE)pPattern->GetPatternEndDate(), VT_DATE);
		_SetField(pRS, _T("PatternEndAfterOccurrences"), (long)pPattern->GetEndAfterOccurrences());

		XTP_CALENDAR_RECURRENCE_OPTIONS _options = pPattern->GetRecurrenceOptions();
		long nData1 = 0, nData2 = 0, nData3 = 0, nData4 = 0;
		_options.GetData(nData1, nData2, nData3, nData4);

		// for previous versions use code below instead of GetData
		//
		//nData1 = _options.m_nRecurrenceType;
		//nData2 = _options.m_YearNth.nWhichDay;
		//nData3 = _options.m_YearNth.nWhichDayMask;
		//nData4 = _options.m_YearNth.nMonthOfYear;		
		
		_SetField(pRS, _T("OptionsData1"), (long)nData1);
		_SetField(pRS, _T("OptionsData2"), (long)nData2);
		_SetField(pRS, _T("OptionsData3"), (long)nData3);
		_SetField(pRS, _T("OptionsData4"), (long)nData4);
		
		_SetField(pRS, _T("EventStartTime"), (DATE)pPattern->GetStartTime(), VT_DATE);		
		_SetField(pRS, _T("EventDuration"), (long)pPattern->GetDurationMinutes());
				
		if (pPattern->GetCustomProperties())		
		{
			CString strCustProps;
			pPattern->GetCustomProperties()->SaveToXML(strCustProps);
			_SetField(pRS, _T("CustomPropertiesXMLData"), _bstr_t(strCustProps) );
		}		
						
		return;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch(...)
	{}

	TRACE(_T("ERROR: Exeption in CSQLDataHelper::PutPatternToData \n"));
}

