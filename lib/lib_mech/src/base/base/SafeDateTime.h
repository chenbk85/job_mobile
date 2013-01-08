//////////////////////////////////////////////////////////////////////////
// Safe DateTime class
// Author: Chunmin Ahn (emocreator@gmail.com)
// modify : icandoit
// Version: 1.00
// History: 
//  2008-04: Initial work
//

#pragma once
#include <time.h>
#include <sqltypes.h>

namespace nMech
{

#define DB_START_TIME	0x014F373BFDE04000	// 1900-01-01 00:00:00.000
typedef __int64	DATETIME;


//--------------------------------------------------------------------------
class JBASE_API SafeDateTime
//--------------------------------------------------------------------------
{
public:
	SafeDateTime(bool setNow=false);
	SafeDateTime(int year, int month, int day, int hour, int min, int sec, int msec);
	SafeDateTime(const SYSTEMTIME& sys);
	SafeDateTime(const FILETIME& ft);
	SafeDateTime(const DATETIME& dt);

	bool GetSysTime(SYSTEMTIME& sys);
	FILETIME GetFileTime();
	DATETIME GetDateTime();

	void SetNow();
	void AddYear(int year);
	void AddMonth(int month);
	void AddDay(int day);
	void AddHour(int hour);
	void AddMinute(int minute);
	void AddSecond(int second);

	// Time format: "2008-08-18 04:30:21.387"
	void SetDateStr(tcstr szTime);
	void GetDateStr(OUT fname_t szTime);

protected:
	void		_GetSysTime(SYSTEMTIME& sys, const DATETIME& dt);
	DATETIME	_GetTime(const SYSTEMTIME& sys);
	DATETIME	_GetTime(const FILETIME& ft);
	FILETIME	_GetTime(const DATETIME& dt);

	DATETIME	_dt;
};


namespace nDB
{

	inline bool IsSQLTimeStampNull(const SQL_TIMESTAMP_STRUCT& SQLTimeStamp)
	{
		return SQLTimeStamp.second == 0 && SQLTimeStamp.minute == 0 && SQLTimeStamp.hour == 0 
			&& SQLTimeStamp.day == 0 && SQLTimeStamp.month == 0 && SQLTimeStamp.year == 0;
	}


	inline time_t _convert_UTC(const SQL_TIMESTAMP_STRUCT& SQLTimeStamp)
	{
		if (IsSQLTimeStampNull(SQLTimeStamp))
			return 0;

		tm Tm = { 0 };
		Tm.tm_sec = SQLTimeStamp.second;
		Tm.tm_min = SQLTimeStamp.minute;
		Tm.tm_hour = SQLTimeStamp.hour;
		Tm.tm_mday = SQLTimeStamp.day;
		Tm.tm_mon = SQLTimeStamp.month - 1;
		Tm.tm_year = SQLTimeStamp.year - 1900;
		return _mkgmtime(&Tm);
	}

	inline time_t _convert_Local(const SQL_TIMESTAMP_STRUCT& SQLTimeStamp)
	{
		if (IsSQLTimeStampNull(SQLTimeStamp))
			return 0;

		tm Tm = { 0 };
		Tm.tm_sec = SQLTimeStamp.second;
		Tm.tm_min = SQLTimeStamp.minute;
		Tm.tm_hour = SQLTimeStamp.hour;
		Tm.tm_mday = SQLTimeStamp.day;
		Tm.tm_mon = SQLTimeStamp.month - 1;
		Tm.tm_year = SQLTimeStamp.year - 1900;
		return _mktime64(&Tm);
	}
	//-----------------------------------------------------------

	inline SQL_TIMESTAMP_STRUCT _convert_UTC_to_DB(time_t TimeT)
	{
		SQL_TIMESTAMP_STRUCT SQLTimeStamp = { 0 };
		if (TimeT == 0)
			return SQLTimeStamp;

		tm Tm = { 0 };
		//This code is vulnerable: the mail system allows user specified times,
		//and Microsoft's implementation intentionally crashes for times outside
		//the value range.  Thus we have to seperately pre-check the range.
		//jASSERT0(TimeT > 0 && TimeT < _MAX__TIME64_T );
		jASSERT0(gmtime_s(&Tm, &TimeT) == 0);
		SQLTimeStamp.year = static_cast<SQLSMALLINT>(Tm.tm_year + 1900);
		SQLTimeStamp.month = static_cast<SQLSMALLINT>(Tm.tm_mon + 1);
		SQLTimeStamp.day = static_cast<SQLSMALLINT>(Tm.tm_mday);
		SQLTimeStamp.hour = static_cast<SQLSMALLINT>(Tm.tm_hour);
		SQLTimeStamp.minute = static_cast<SQLSMALLINT>(Tm.tm_min);
		SQLTimeStamp.second = static_cast<SQLSMALLINT>(Tm.tm_sec);
		return SQLTimeStamp;
	}

	inline TIMESTAMP_STRUCT _convert(SYSTEMTIME st)
	{
		TIMESTAMP_STRUCT ts;
		ts.year     = st.wYear;
		ts.month    = st.wMonth;
		ts.day      = st.wDay;
		ts.hour     = st.wHour;
		ts.minute   = st.wMinute;
		ts.second   = st.wSecond;
		ts.fraction = st.wMilliseconds * 1000000;
		return ts;
	}

	inline SYSTEMTIME _convert(TIMESTAMP_STRUCT ts)
	{
		SYSTEMTIME st;
		st.wYear   = ts.year;
		st.wMonth  = ts.month;
		st.wDay    = ts.day;
		st.wHour   = ts.hour;
		st.wMinute = ts.minute;
		st.wSecond = ts.second;
		st.wMilliseconds = (WORD)(ts.fraction / 1000000);
		st.wDayOfWeek    = 0;
		return st;
	}

}//namespace nDB


struct SysTime : public SYSTEMTIME // odbc patch 용
{
	SYSTEMTIME& BaseST(){return *this;}
	TIMESTAMP_STRUCT& BaseTS(){ return *(TIMESTAMP_STRUCT*)_dummy;}
	CHAR		_dummy[64];
	void To_TS(){BaseTS() = nDB::_convert(BaseST());}
	void To_ST(){BaseST() = nDB::_convert(BaseTS());}

};


extern DATETIME   ToSafeTime(SysTime& time); // DB_START_TIME 시간을 기준으로 한 DATETIME 으로 표현된 시간 리턴
extern tcstr ToDateStr(INT64 dateTime, fname_t str); // DATETIME기준 시간을 스트링으로 표현



}//namespace nMech