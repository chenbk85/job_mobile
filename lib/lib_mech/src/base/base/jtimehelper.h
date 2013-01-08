/* file : TimeHelper.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-18 13:06:05
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __TimeHelper_header__
#define __TimeHelper_header__
#pragma once


#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>

namespace nMech
{

struct JBASE_API jTimeHelper
{
	time_t m_t;
	time_t Get_curr_time();
	SYSTEMTIME jTimeHelper::Get_day();
	const TCHAR* jTimeHelper::ToString(OUT TCHAR buf[256]);
	SYSTEMTIME jTimeHelper::Get_diff_day(IN time_t tFuture);
	const TCHAR* jTimeHelper::Get_diff_day_string(IN time_t tFuture, TCHAR buf[128]);

	static void _modifyDate(SYSTEMTIME *parm_date, int parm_interval_day);

	static int to_second(int day,int hour,int min, int sec);
	//임의의 시간차 diff_second를 일 시 분 초로 분리해 낸다.
	static void to_day(IN int diff_second,OUT WORD &day,OUT WORD &hour, OUT WORD &min, OUT WORD&sec);
	static SYSTEMTIME to_day(IN int diff_second);

	static SYSTEMTIME calcProceedTime(SYSTEMTIME tNow ,int proceed_sec);
	static SYSTEMTIME calcProceedTime(int proceed_sec);//현제 시간에서 해당 초만큼 지난 시간 리턴

};


}
/*

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
*/
#endif // __TimeHelper_header__
