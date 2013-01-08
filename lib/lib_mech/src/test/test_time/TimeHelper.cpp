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


// ����� �ð����ʸ� �߿�
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

// �̷��� ��� �ð����� ���̸� ����

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

//���� �ð����� �ش� �ʸ�ŭ ���� �ð� ����
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

