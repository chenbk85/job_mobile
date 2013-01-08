// a1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "windows.h"
#include "assert.h"
#include "TimeHelper.h"

int _tmain1(int argc, _TCHAR* argv[])
{
	char buf[]="1234567890123456789";
	signed __int64 i64=0;
	sscanf(buf,"%I64d",&i64);


	SYSTEMTIME t;

#define jSPREED_SYSTEMTIME_PTR(t) &t.wYear,&t.wMonth,&t.wDay,&t.wHour,&t.wMinute,&t.wSecond
#define jPRINTF_SYSTEMTIME "%d-%d-%d %d:%d:%d"
	
	char buf2[]= "1234-56-78 12:34:56";
	sscanf(buf2,jPRINTF_SYSTEMTIME,jSPREED_SYSTEMTIME_PTR(t));

	return 0;
}


//http://www.tipssoft.com/bulletin/board.php?bo_table=update&wr_id=891
void _modifyDate(SYSTEMTIME *parm_date, int parm_interval_day)
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
int to_second(int day,int hour,int min, int sec)
{
	return day*24*60*60 + hour*60*60 + min*60 + sec;
}
void to_day(IN int second,OUT int &day,OUT int &hour, OUT int &min, OUT int&sec)
{
	sec = second;

	min = sec/60;
	sec %= 60;

	hour = min/60;
	min %= 60;

	day = hour /24;
	hour %= 24;
}

SYSTEMTIME calcProceedTime(SYSTEMTIME tNow ,int proceed_sec)
{
	int day, hour,min,sec;
	to_day(proceed_sec,day,hour,min,sec);
	_modifyDate(&tNow,day);
	tNow.wHour += hour;
	tNow.wMinute +=min;
	tNow.wSecond +=sec;
	return tNow;
}
//현제 시간에서 해당 초만큼 지난 시간 리턴
SYSTEMTIME calcProceedTime(int proceed_sec)
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

int DifferenceSec(SYSTEMTIME t2, SYSTEMTIME t1) // t2 -t1 시간차이 second // 월을 넘어가는건 에러남.
{

	return // 차후 월 년처리해야함
		(t2.wDay-t1.wDay)*24*60*60 
		+ (t2.wHour-t1.wHour)*60*60
		+ (t2.wMinute - t1.wMinute) * 60
		+ (t2.wSecond - t1.wSecond);
}

int _tmain2(int argc, _TCHAR* argv[])
{
	int day, hour,min,sec;
	to_day(42383,day,hour,min,sec);
	int second = to_second(day,hour,min,sec);
	assert(second == 42383);

	SYSTEMTIME tNow,tNow2;
	GetLocalTime(&tNow);
	{
		int d= 0;
		int h = 25;
		int m= 62341*60;
		int s = 6321;
		int sec1 = to_second(d,h,m,s);
		tNow2 = calcProceedTime(tNow,sec1);// 한달, 2일 , 2시간,2분 ,1초
		int sec2 = DifferenceSec(tNow2,tNow);
		assert(sec1==sec2);
	}

	printf("\nd%dh%dm%ds%d\n",tNow.wDay,tNow.wHour,tNow.wMinute,tNow.wSecond);
	printf("\nd%dh%dm%ds%d\n",tNow2.wDay,tNow2.wHour,tNow2.wMinute,tNow2.wSecond);

	return 0;
}




int main3()
{
	char tmpbuf[128], timebuf[26], ampm[] = "AM";
	time_t ltime;
	struct _timeb tstruct;
	struct tm today, gmt, xmas = { 0, 0, 12, 25, 11, 110 };
#if 0
	struct tm {
	int tm_sec;     /* seconds after the minute - [0,59] */
	int tm_min;     /* minutes after the hour - [0,59] */
	int tm_hour;    /* hours since midnight - [0,23] */
	int tm_mday;    /* day of the month - [1,31] */
	int tm_mon;     /* months since January - [0,11] */
	int tm_year;    /* years since 1900 */
	int tm_wday;    /* days since Sunday - [0,6] */
	int tm_yday;    /* days since January 1 - [0,365] */
	int tm_isdst;   /* daylight savings time flag */
};
#endif
	errno_t err;

	// Set time zone from TZ environment variable. If TZ is not set,
	// the operating system is queried to obtain the default value 
	// for the variable. 
	//
	_tzset();

	// Display operating system-style date and time. 
	_strtime_s( tmpbuf, sizeof(tmpbuf) );
	printf( "OS time:\t\t\t\t%s\n", tmpbuf );
	_strdate_s( tmpbuf, sizeof(tmpbuf));
	printf( "OS date:\t\t\t\t%s\n", tmpbuf );

	// Get UNIX-style time and display as number and string. 
	time( &ltime );
	printf( "Time in seconds since UTC 1/1/70:\t%ld\n", ltime );
	err = ctime_s(timebuf, sizeof(timebuf), &ltime);
	if (err)
	{
		printf("ctime_s failed due to an invalid argument.");
		exit(1);
	}
	printf( "UNIX time and date:\t\t\t%s", timebuf );

	// Display UTC. 
	err = _gmtime64_s( &gmt, &ltime );
	if (err)
	{
		printf("_gmtime64_s failed due to an invalid argument.");
	}
	err = asctime_s(timebuf, 26, &gmt);
	if (err)
	{
		printf("asctime_s failed due to an invalid argument.");
		exit(1);
	}
	printf( "Coordinated universal time:\t\t%s", timebuf );

	// Convert to time structure and adjust for PM if necessary. 
	err = _localtime64_s( &today, &ltime );
	if (err)
	{
		printf("_localtime64_s failed due to an invalid argument.");
		exit(1);
	}
	if( today.tm_hour >= 12 )
	{
		strcpy_s( ampm, sizeof(ampm), "PM" );
		today.tm_hour -= 12;
	}
	if( today.tm_hour == 0 )  // Adjust if midnight hour.
		today.tm_hour = 12;

	// Convert today into an ASCII string 
	err = asctime_s(timebuf, 26, &today);
	if (err)
	{
		printf("asctime_s failed due to an invalid argument.");
		exit(1);
	}

	// Note how pointer addition is used to skip the first 11 
	// characters and printf is used to trim off terminating 
	// characters.
	//
	printf( "12-hour time:\t\t\t\t%.8s %s\n",
		timebuf + 11, ampm );

	// Print additional time information. 
	_ftime( &tstruct ); // C4996
	// Note: _ftime is deprecated; consider using _ftime_s instead
	printf( "Plus milliseconds:\t\t\t%u\n", tstruct.millitm );
	printf( "Zone difference in hours from UTC:\t%u\n", 
		tstruct.timezone/60 );
	printf( "Time zone name:\t\t\t\t%s\n", _tzname[0] ); //C4996
	// Note: _tzname is deprecated; consider using _get_tzname
	printf( "Daylight savings:\t\t\t%s\n", 
		tstruct.dstflag ? "YES" : "NO" );

	// Make time for noon on Christmas, 1993. 
	if( mktime( &xmas ) != (time_t)-1 )
	{
		err = asctime_s(timebuf, 26, &xmas);
		if (err)
		{
			printf("asctime_s failed due to an invalid argument.");
			exit(1);
		}
		printf( "Christmas\t\t\t\t%s\n", timebuf );
	}

	// Use time structure to build a customized time string. 
	err = _localtime64_s( &today, &ltime );
	if (err)
	{
		printf(" _localtime64_s failed due to invalid arguments.");
		exit(1);
	}

	// Use strftime to build a customized time string. 
	strftime( tmpbuf, 128,
		"Today is %A, day %d of %B in the year %Y.\n", &today );
	printf( tmpbuf );

	{
		time_t t1,t2;
		time(&t1);
		Sleep(2000);
		time(&t2);
		time_t tDiff = t2-t1;

		err = _gmtime64_s( &gmt, &tDiff);
		if (err)
		{
			printf("_gmtime64_s failed due to an invalid argument.");
		}
		err = asctime_s(timebuf, sizeof(timebuf) ,&gmt);
		if (err)
		{
			printf("asctime_s failed due to an invalid argument.");
			exit(1);
		}
		printf( "Coordinated universal time:\t\t%s", timebuf );

	}


}

void main()
{
	jTimeHelper t,t3;
	t.Get_curr_time();

	for(int day=0; day < 1000; ++day)
	{
		for(int hour=0; hour < 1000; ++hour)
		{
			for(int min=0; min < 1000; ++min)
			{
				for(int sec=0; sec < 1000; ++sec)
				{
					printf("day=%d,hour=%d,min=%d,sec=%d\n",day,hour,min,sec);
					int proceed_sec = jTimeHelper::to_second(day,hour,min,sec);
					WORD day1,hour1,min1,sec1;
					jTimeHelper::to_day(proceed_sec,day1,hour1,min1,sec1);

					t3.m_t = t.m_t + proceed_sec;
#if 0
					char buf[256];
					t.ToString(buf);printf("%s",buf);
					t3.ToString(buf);printf("%s",buf);
					printf("da1=%d,hou1=%d,mi1=%d,se1=%d\n",day1,hour1,min1,sec1);
					t.Get_diff_day_string(t3.m_t,buf);printf("%s\n",buf);
					printf("\n");
#endif

					SYSTEMTIME st = t.Get_diff_day(t3.m_t);
					assert(day1==st.wDay);
					assert(hour1==st.wHour);
					assert(min1==st.wMinute);
					assert(sec1 == st.wSecond);
				}
			}

		}

	}

}