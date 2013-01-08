/* file : TimeHelper.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-18 13:06:07
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "windows.h"

#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>


#include "TimeHelper.h"

time_t jTimeHelper::Get_curr_time()
{ 
	time( &m_t);
	return m_t;
}


// 년월일 시간분초를 추울
SYSTEMTIME& jTimeHelper::Get_day()
{
	SYSTEMTIME t;
	struct tm gmt;
	int err = _localtime64_s( &gmt, &m_t);
	if (err)
	{
		throw ("_localtime64_s failed due to an invalid argument.");
	}
	t.wYear= gmt.tm_year+1900;
	t.wMonth= gmt.tm_mon+1;
	t.wDay= gmt.tm_mday;
	t.wHour= gmt.tm_hour;
	t.wMinute= gmt.tm_min;
	t.wSecond= gmt.tm_sec;
	return t;

}
char* jTimeHelper::ToString(OUT char buf[256])
{ 
	struct tm gmt;
	int err = _localtime64_s( &gmt, &m_t);
	if (err)
	{
		throw ("_localtime64_s failed due to an invalid argument.");
	}
	err = asctime_s(buf,128, &gmt);
	if (err)
	{
		throw "asctime_s failed due to an invalid argument.";
	}
	//printf( "Coordinated universal time:\t\t%s", timebuf );
	return buf;
}

// 미래의 어느 시간과의 차이를 구함

SYSTEMTIME jTimeHelper::Get_diff_day(IN time_t tFuture)
{
	time_t ret;
	ret = tFuture - m_t;
	if(tFuture< m_t) ret = m_t-tFuture;
	SYSTEMTIME t;
	memset(&t,0,sizeof(t));
	jTimeHelper::to_day(ret,t.wDay,t.wHour,t.wMinute,t.wSecond);
	return t;
}
char* jTimeHelper::Get_diff_day_string(IN time_t tFuture, char buf[128])
{
	SYSTEMTIME st = Get_diff_day(tFuture);
	sprintf(buf, "%d/%d/%d %d:%d:%d", st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	return buf;
}


//http://www.tipssoft.com/bulletin/board.php?bo_table=update&wr_id=891
void jTimeHelper::_modifyDate(SYSTEMTIME *parm_date, int parm_interval_day)
{
	// 1년 12월별 일자를 배열로 구성한다.
	// 1월부터 순차적으로 12월까지의 월별 총 일수이다.
	int month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// 입력된 일자와 Calendar의 일자의 차이가 0 보다 큰 경우
	// 즉, Calendar의 선택 일자보다 입력된 일자가 더 큰 경우
	if(parm_interval_day > 0){

		// 해당 월이 2월인 경우, 4년 및 400년 마다 한번씩 윤달이므로 윤달일 경우 일수가 29일이 된다.
		// 따라서 기준 일수인 28일 에서 1일을 더해준다.
		if(parm_date->wMonth == 2){
			if(!(parm_date->wYear%4) && ((parm_date->wYear%100) || !(parm_date->wYear%400))) 
				month_day[1]++;
		}

		// Calendar에 선택된 현재 일자에 parm_interval_day 를 더한 값이 
		// Calendar에 선택된 현재 월의 총 일수보다 클 경우
		if(month_day[parm_date->wMonth-1] < parm_date->wDay + parm_interval_day){

			// Calendar에 선택된 현재 일자에 parm_interval_day 를 더한 값에서 
			// Calendar에 선택된 현재 월의 총 일수를 뺀 일수가 실제 이동될 일수가 된다.
			// 예를 들어 입력받은 일자가 2009년 7월 4일이고 Calendar 의 선택 날짜가 2009년 6월 29일
			// 이라고 한다면 parm_interval_day 는 7월 4일 - 6월 29일 = '5' 가 된다.
			// 그리고 parm_date->wDay 는 선택된 날짜가 29일 이므로 '29' 가 된다.
			// 또 month_day[parm_date->wMonth-1] 는 6월 이므로 '30' 이 된다.
			// 그러므로 parm_date->wDay 에는 '29' + '5' - '30' = '4' 가 된다.
			// 결과적으로 선택한 날짜가 6월 29일 이고 차이가 +5일 이므로 6월 29일에서 5일만큼 더해진
			// 일자가 Calendar 에 표시되어야할 일자가 되는 것이다.
			parm_date->wDay = parm_date->wDay + parm_interval_day - 
				month_day[parm_date->wMonth-1];

			// 따라서 현재는 6월이지만 표시되어야할 일자는 7월로 넘어가는 것이므로 현재 월에서 1월을
			// 더해야 한다.
			parm_date->wMonth++;

			// 만약 1월을 더한 월이 12월보다 큰 경우
			// 즉, 12월을 넘어서는 경우는 1년이 넘어가는 것이므로 현재 년에서 1년을 더해야 한다.
			if(parm_date->wMonth > 12){

				// 1년을 더하면 월도 12월에서 1월로 변경해줘야 한다.
				parm_date->wMonth = 1;

				// 현재 년에 1년을 더한다.
				parm_date->wYear++;
			}
		} else {

			// Calendar에 선택된 현재 일자에 parm_interval_day 를 더한 값이 
			// Calendar에 선택된 현재 월의 총 일수보다 클 경우 해당 parm_interval_day 만큼만 일수를
			// 더하면 된다.
			parm_date->wDay += parm_interval_day;
		}
	} else {

		// Calendar에 선택된 현재 일자에 parm_interval_day 를 더한 값이 Calendar에 선택된 현재 월의
		// 총 일수보다 클 경우
		if(parm_date->wDay + parm_interval_day <= 0){

			// Calendar에 선택된 현재 일자에 parm_interval_day 를 더한 값에서 
			// Calendar에 선택된 현재 월의 총 일수를 뺀 일수가 실제 이동될 일수가 된다.
			// 예를 들어 입력받은 일자가 2009년 6월 29일 이고, Calendar 의 선택 날짜가 2009년 7월 3일
			// 이라고 한다면 parm_interval_day 는 6월 29일 - 7월 3일 = '-4' 가 된다.
			// 그리고 parm_date->wDay 는 선택된 날짜가 3일 이므로 '3' 이 된다.
			// 또 month_day[parm_date->wMonth-1] 는 6월 이므로 '30' 이 된다.
			// 그러므로 parm_date->wDay 에는 '3' + '-4' + '30' = '-1' 이 된다.
			// 결과적으로 선택한 날짜가 7월 3일 이고 차이가 -4 이므로 7월 3일에서 4일만큼 뺀 일자가
			// Calendar 에 표시되어야할 일자가 되는 것이다.

			// 따라서 선택된 월인 7월에서 1월을 뺀다.
			parm_date->wMonth--;

			// 만약 1월을 뺀 월이 0 보다 작거나 같은 경우
			// 즉, 1월 이전인 경우는 현재 년 이전이 되는 것이므로 현재 년에서 1년을 빼야 한다.
			if(parm_date->wMonth <= 0){

				// 1년을 빼면 월도 12월에서 1월로 변경해줘야 한다.
				parm_date->wMonth = 12;

				// 현재 년에 1년을 뺀다.
				parm_date->wYear--;
			}

			// 해당 월이 2월인 경우, 4년 및 400년에 한번씩 윤달이므로 윤달일 경우 일수가 29일이 된다.
			// 따라서 기준 일수인 28일 에서 1일을 더해준다.
			if(parm_date->wMonth == 2){
				if(!(parm_date->wYear%4) && ((parm_date->wYear%100) || 
					!(parm_date->wYear%400))) month_day[1]++;
			}
			parm_date->wDay = month_day[parm_date->wMonth-1] + parm_date->wDay + 
				parm_interval_day;
		} else {

			// Calendar에 선택된 현재 일자에 parm_interval_day 를 더한 값이 0 보다 큰 경우
			// 해당 parm_interval_day 만큼만 일수를 더하면 된다.
			parm_date->wDay += parm_interval_day;
		}
	}
}


void jTimeHelper::to_day(IN int diff_second,OUT WORD &day,OUT WORD &hour, OUT WORD &min, OUT WORD&sec)
{
	sec = diff_second;

	min = sec/60;
	sec %= 60;

	hour = min/60;
	min %= 60;

	day = hour /24;
	hour %= 24;
}
int jTimeHelper::to_second(int day,int hour,int min, int sec)
{
	return day*24*60*60 + hour*60*60 + min*60 + sec;
}

SYSTEMTIME jTimeHelper::calcProceedTime(SYSTEMTIME tNow ,int proceed_sec)
{
	WORD day, hour,min,sec;
	to_day(proceed_sec,day,hour,min,sec);
	_modifyDate(&tNow,day);
	tNow.wHour += hour;
	tNow.wMinute +=min;
	tNow.wSecond +=sec;
	return tNow;
}

//현제 시간에서 해당 초만큼 지난 시간 리턴
SYSTEMTIME jTimeHelper::calcProceedTime(int proceed_sec)
{
	SYSTEMTIME tNow;
	if(proceed_sec<=0)
	{
		memset(&tNow, 0, sizeof(tNow));
		return tNow;
	}
	GetLocalTime(&tNow);
	return calcProceedTime(tNow,proceed_sec);
}

