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


struct jTimeHelper
{
	time_t m_t;
	time_t Get_curr_time();
	SYSTEMTIME& jTimeHelper::Get_day();
	char* jTimeHelper::ToString(OUT char buf[256]);
	SYSTEMTIME jTimeHelper::Get_diff_day(IN time_t tFuture);
	char* jTimeHelper::Get_diff_day_string(IN time_t tFuture, char buf[128]);

	static void _modifyDate(SYSTEMTIME *parm_date, int parm_interval_day);
	static int to_second(int day,int hour,int min, int sec);

	//������ �ð��� diff_second�� �� �� �� �ʷ� �и��� ����.
	static void to_day(IN int diff_second,OUT WORD &day,OUT WORD &hour, OUT WORD &min, OUT WORD&sec);
	static SYSTEMTIME calcProceedTime(SYSTEMTIME tNow ,int proceed_sec);
	static SYSTEMTIME calcProceedTime(int proceed_sec);//���� �ð����� �ش� �ʸ�ŭ ���� �ð� ����

};

#endif // __TimeHelper_header__
