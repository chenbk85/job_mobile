//////////////////////////////////////////////////////////////////////////
// Safe DateTime class
// Author: Chunmin Ahn (emocreator@gmail.com)
// Version: 1.00
// History: 
//  2008-04: Initial work
//

//#include <windows.h>
//#include <stdio.h>
//#include <time.h>
#include "stdafx.h"
#include "SafeDateTime.h"

#define ONE_MILLION 1000000
#define UNIX_WIN32_EPOCH_DIFF 11644473600
#define UNITS_100NS_PER_1US 10
#define ONE_MIN_SEC		60
#define ONE_HOUR_SEC	(ONE_MIN_SEC * 60)
#define ONE_DAY_SEC		(ONE_HOUR_SEC * 24)

#pragma warning( disable : 4996 )



namespace nMech
{

	DATETIME ToSafeTime(SysTime& time)
	{
		SafeDateTime sdt(time);
		if (sdt.GetDateTime() == DB_START_TIME)
			return 0;
		else
			return sdt.GetDateTime();
	}


	tcstr ToDateStr(INT64 dateTime, OUT fname_t buf)
	{
		if (dateTime == 0)
			dateTime = DB_START_TIME;
		SafeDateTime sdt(dateTime);
		SYSTEMTIME sys;
		if (sdt.GetSysTime(sys))
		{
			jt_sprintf(buf,_T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
				sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
		}
		else
		{
			buf[0]=0;
		}
		return buf;
	}



SafeDateTime::SafeDateTime(bool setNow) : _dt(0)
{
	if (setNow)
		SetNow();
}

SafeDateTime::SafeDateTime(int year, int month, int day, int hour, int min, int sec, int msec)
{
	SYSTEMTIME sys;
	sys.wYear         = (WORD)year;
	sys.wMonth        = (WORD)month;
	sys.wDayOfWeek    = 0;
	sys.wDay          = (WORD)day;
	sys.wHour         = (WORD)hour;
	sys.wMinute       = (WORD)min;
	sys.wSecond       = (WORD)sec;
	sys.wMilliseconds = (WORD)msec;
	_dt = _GetTime(sys);
}

SafeDateTime::SafeDateTime(const SYSTEMTIME& sys)
{
	_dt = _GetTime(sys);
}

SafeDateTime::SafeDateTime(const FILETIME& ft)
{
	_dt = _GetTime(ft);
}

SafeDateTime::SafeDateTime(const DATETIME& dt)
{
	_dt = dt;
}

bool SafeDateTime::GetSysTime(SYSTEMTIME& sys)
{
	FILETIME ft = _GetTime(_dt);
	if (FileTimeToSystemTime(&ft, &sys) == FALSE)
	{
		memset(&sys, 0, sizeof(sys));
		return false;
	}
	return true;
}

FILETIME SafeDateTime::GetFileTime()
{
	return _GetTime(_dt);
}

DATETIME SafeDateTime::GetDateTime()
{
	return _dt;
}

void SafeDateTime::SetNow()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	_dt = _GetTime(sys);
}

void SafeDateTime::AddYear(int year)
{
	SYSTEMTIME sys;
	if (GetSysTime(sys))
	{
		sys.wYear += year;
		_dt = _GetTime(sys);
	}
}

void SafeDateTime::AddMonth(int month)
{
	SYSTEMTIME sys;
	if (GetSysTime(sys))
	{
		int newMon  = (sys.wMonth-1) + month;
		sys.wYear  += newMon / 12;
		sys.wMonth  = newMon % 12 + 1;
		_dt = _GetTime(sys);
	}
}

void SafeDateTime::AddDay(int day)
{
	_dt += ((DATETIME)day * ONE_DAY_SEC * ONE_MILLION * UNITS_100NS_PER_1US);
}

void SafeDateTime::AddHour(int hour)
{
	_dt += ((DATETIME)hour * ONE_HOUR_SEC * ONE_MILLION * UNITS_100NS_PER_1US);
}

void SafeDateTime::AddMinute(int minute)
{
	_dt += ((DATETIME)minute * ONE_MIN_SEC * ONE_MILLION * UNITS_100NS_PER_1US);
}

void SafeDateTime::AddSecond(int second)
{
	_dt += ((DATETIME)second * ONE_MILLION * UNITS_100NS_PER_1US);
}

DATETIME SafeDateTime::_GetTime(const SYSTEMTIME& sys)
{
	FILETIME ft;
	if (SystemTimeToFileTime(&sys, &ft))
		return _GetTime(ft);
	else
		return 0;
}

DATETIME SafeDateTime::_GetTime(const FILETIME& ft)
{
	return (((DATETIME)ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
}

FILETIME SafeDateTime::_GetTime(const DATETIME& dt)
{
	FILETIME ft;
	ft.dwHighDateTime = (DWORD)(dt >> 32);
	ft.dwLowDateTime  = (DWORD)dt;
	return ft;
}

void SafeDateTime::SetDateStr(tcstr szTime)
{
	if (szTime == NULL || *szTime == 0)
	{
		_dt = 0;
	}
	else
	{
		int year, month, day, hour, min, sec, msec;
		if (jt_sscanf(szTime, _T("%d-%d-%d %d:%d:%d.%d"), &year, &month, &day, &hour, &min, &sec, &msec) == 7)
		{
			SYSTEMTIME sys;
			sys.wYear         = (WORD)year;
			sys.wMonth        = (WORD)month;
			sys.wDayOfWeek    = 0;
			sys.wDay          = (WORD)day;
			sys.wHour         = (WORD)hour;
			sys.wMinute       = (WORD)min;
			sys.wSecond       = (WORD)sec;
			sys.wMilliseconds = (WORD)msec;
			_dt = _GetTime(sys);
		}
	}
}

void SafeDateTime::GetDateStr(fname_t szTime)
{
	SYSTEMTIME sys;
	if (GetSysTime(sys))
	{
		jt_sprintf(szTime, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),
			sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	}
	else
	{
		if (szTime)
			*szTime = 0;
	}
}


}//nMech