// a1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	// 1�� 12���� ���ڸ� �迭�� �����Ѵ�.
	// 1������ ���������� 12�������� ���� �� �ϼ��̴�.
	int month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// �Էµ� ���ڿ� Calendar�� ������ ���̰� 0 ���� ū ���
	// ��, Calendar�� ���� ���ں��� �Էµ� ���ڰ� �� ū ���
	if(parm_interval_day > 0){

		// �ش� ���� 2���� ���, 4�� �� 400�� ���� �ѹ��� �����̹Ƿ� ������ ��� �ϼ��� 29���� �ȴ�.
		// ���� ���� �ϼ��� 28�� ���� 1���� �����ش�.
		if(parm_date->wMonth == 2){
			if(!(parm_date->wYear%4) && ((parm_date->wYear%100) || !(parm_date->wYear%400))) 
				month_day[1]++;
		}

		// Calendar�� ���õ� ���� ���ڿ� parm_interval_day �� ���� ���� 
		// Calendar�� ���õ� ���� ���� �� �ϼ����� Ŭ ���
		if(month_day[parm_date->wMonth-1] < parm_date->wDay + parm_interval_day){

			// Calendar�� ���õ� ���� ���ڿ� parm_interval_day �� ���� ������ 
			// Calendar�� ���õ� ���� ���� �� �ϼ��� �� �ϼ��� ���� �̵��� �ϼ��� �ȴ�.
			// ���� ��� �Է¹��� ���ڰ� 2009�� 7�� 4���̰� Calendar �� ���� ��¥�� 2009�� 6�� 29��
			// �̶�� �Ѵٸ� parm_interval_day �� 7�� 4�� - 6�� 29�� = '5' �� �ȴ�.
			// �׸��� parm_date->wDay �� ���õ� ��¥�� 29�� �̹Ƿ� '29' �� �ȴ�.
			// �� month_day[parm_date->wMonth-1] �� 6�� �̹Ƿ� '30' �� �ȴ�.
			// �׷��Ƿ� parm_date->wDay ���� '29' + '5' - '30' = '4' �� �ȴ�.
			// ��������� ������ ��¥�� 6�� 29�� �̰� ���̰� +5�� �̹Ƿ� 6�� 29�Ͽ��� 5�ϸ�ŭ ������
			// ���ڰ� Calendar �� ǥ�õǾ���� ���ڰ� �Ǵ� ���̴�.
			parm_date->wDay = parm_date->wDay + parm_interval_day - 
				month_day[parm_date->wMonth-1];

			// ���� ����� 6�������� ǥ�õǾ���� ���ڴ� 7���� �Ѿ�� ���̹Ƿ� ���� ������ 1����
			// ���ؾ� �Ѵ�.
			parm_date->wMonth++;

			// ���� 1���� ���� ���� 12������ ū ���
			// ��, 12���� �Ѿ�� ���� 1���� �Ѿ�� ���̹Ƿ� ���� �⿡�� 1���� ���ؾ� �Ѵ�.
			if(parm_date->wMonth > 12){

				// 1���� ���ϸ� ���� 12������ 1���� ��������� �Ѵ�.
				parm_date->wMonth = 1;

				// ���� �⿡ 1���� ���Ѵ�.
				parm_date->wYear++;
			}
		} else {

			// Calendar�� ���õ� ���� ���ڿ� parm_interval_day �� ���� ���� 
			// Calendar�� ���õ� ���� ���� �� �ϼ����� Ŭ ��� �ش� parm_interval_day ��ŭ�� �ϼ���
			// ���ϸ� �ȴ�.
			parm_date->wDay += parm_interval_day;
		}
	} else {

		// Calendar�� ���õ� ���� ���ڿ� parm_interval_day �� ���� ���� Calendar�� ���õ� ���� ����
		// �� �ϼ����� Ŭ ���
		if(parm_date->wDay + parm_interval_day <= 0){

			// Calendar�� ���õ� ���� ���ڿ� parm_interval_day �� ���� ������ 
			// Calendar�� ���õ� ���� ���� �� �ϼ��� �� �ϼ��� ���� �̵��� �ϼ��� �ȴ�.
			// ���� ��� �Է¹��� ���ڰ� 2009�� 6�� 29�� �̰�, Calendar �� ���� ��¥�� 2009�� 7�� 3��
			// �̶�� �Ѵٸ� parm_interval_day �� 6�� 29�� - 7�� 3�� = '-4' �� �ȴ�.
			// �׸��� parm_date->wDay �� ���õ� ��¥�� 3�� �̹Ƿ� '3' �� �ȴ�.
			// �� month_day[parm_date->wMonth-1] �� 6�� �̹Ƿ� '30' �� �ȴ�.
			// �׷��Ƿ� parm_date->wDay ���� '3' + '-4' + '30' = '-1' �� �ȴ�.
			// ��������� ������ ��¥�� 7�� 3�� �̰� ���̰� -4 �̹Ƿ� 7�� 3�Ͽ��� 4�ϸ�ŭ �� ���ڰ�
			// Calendar �� ǥ�õǾ���� ���ڰ� �Ǵ� ���̴�.

			// ���� ���õ� ���� 7������ 1���� ����.
			parm_date->wMonth--;

			// ���� 1���� �� ���� 0 ���� �۰ų� ���� ���
			// ��, 1�� ������ ���� ���� �� ������ �Ǵ� ���̹Ƿ� ���� �⿡�� 1���� ���� �Ѵ�.
			if(parm_date->wMonth <= 0){

				// 1���� ���� ���� 12������ 1���� ��������� �Ѵ�.
				parm_date->wMonth = 12;

				// ���� �⿡ 1���� ����.
				parm_date->wYear--;
			}

			// �ش� ���� 2���� ���, 4�� �� 400�⿡ �ѹ��� �����̹Ƿ� ������ ��� �ϼ��� 29���� �ȴ�.
			// ���� ���� �ϼ��� 28�� ���� 1���� �����ش�.
			if(parm_date->wMonth == 2){
				if(!(parm_date->wYear%4) && ((parm_date->wYear%100) || 
					!(parm_date->wYear%400))) month_day[1]++;
			}
			parm_date->wDay = month_day[parm_date->wMonth-1] + parm_date->wDay + 
				parm_interval_day;
		} else {

			// Calendar�� ���õ� ���� ���ڿ� parm_interval_day �� ���� ���� 0 ���� ū ���
			// �ش� parm_interval_day ��ŭ�� �ϼ��� ���ϸ� �ȴ�.
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
//���� �ð����� �ش� �ʸ�ŭ ���� �ð� ����
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

int DifferenceSec(SYSTEMTIME t2, SYSTEMTIME t1) // t2 -t1 �ð����� second // ���� �Ѿ�°� ������.
{

	return // ���� �� ��ó���ؾ���
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
		tNow2 = calcProceedTime(tNow,sec1);// �Ѵ�, 2�� , 2�ð�,2�� ,1��
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