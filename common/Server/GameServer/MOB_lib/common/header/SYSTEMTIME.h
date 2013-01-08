/* file : SYSTEMTIME.h
Coder : by icandoit ( mech12@nate.com)
Date : 2011-10-07 14:17:04
comp.: neovian.co.kr
title : 
desc : 

*/

#ifndef __SYSTEMTIME_header__
#define __SYSTEMTIME_header__
#pragma once


namespace nMech
{
	inline tcstr ToString(fname_t szBuf, SYSTEMTIME& t)
	{
		jt_sprintf(szBuf, _T("%02d-%02d-%02d %02d.%02d.%02d"),t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond);
		return szBuf;
	}


	int64 Diff(SYSTEMTIME sTm1, SYSTEMTIME sTm2)
	{
		/*
		SYSTEMTIME t1 ,t2;
		ZeroMemory(&t1,sizeof(t1));
		ZeroMemory(&t2,sizeof(t2));

		t1.wYear=2001;
		t1.wMonth=9;
		t1.wDay=29;
		t1.wHour=1;
		t1.wMinute=1;
		t1.wSecond=1;
		t1.wMilliseconds=1;

		t2.wYear=2012;
		t2.wMonth=2;
		t2.wDay=29;
		t2.wHour=1;
		t2.wMinute=1;
		t2.wSecond=1;
		t2.wMilliseconds=2;

		int64 ss = Diff(t2,t1);

		*/
		int64 nRtn;
		FILETIME fTm1, fTm2;
		ULONGLONG *ullVal1, *ullVal2;

		SystemTimeToFileTime(&sTm1, &fTm1);
		SystemTimeToFileTime(&sTm2, &fTm2);

		ullVal1 = (ULONGLONG *)&fTm1;
		ullVal2 = (ULONGLONG *)&fTm2;
		nRtn = *ullVal1 - *ullVal2;
		return nRtn;
	}
}


#endif // __SYSTEMTIME_header__
