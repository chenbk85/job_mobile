/* file : maestia_make_merge_note.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-06-07 21:29:32
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "conio.h"
#include "common/jCommon.h"
#include "common/jInit.h"
using namespace nMech;
#include "interface/jIOrb.h"
#include "interface/jIWinUtil.h"
#include "interface/jIConsoleCmd.h"

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "header/jBoost.h"

#define _jF(X) endl<< boost::tformat(_T(X))


int _tmain(int argc, _TCHAR* argv[])
{
	if(argc!=3)
	{
		printf("arg : <src_dir> <target_dir\\000-패치준비txt>\n");
		return 0;
	}
	jSET_LOCALE1("kor");

	tstring src_dir = argv[1];
	tstring target_dir = argv[2];

	tofstream of(jA(target_dir));

	tname1024_t buf;
	jt_strcpy(buf, target_dir.c_str());
	TCHAR* ch = jt_strrchr(buf , '\\');
	if(ch)
	{
		*ch =0;
	}
	of <<	_jF("[네트웍경로] : \\\\221.132.84.143\\MaestiaBuild\\YDBuild\\");
	of <<	_jF("[패치 폴더] : %1%") % buf ;
	of <<	_jF("[패치 원본 폴더] : %1%") % src_dir;

	tname1024_t szCurrentTime;

	SYSTEMTIME	SystemTime;
	GetLocalTime(&SystemTime);
	_sntprintf(szCurrentTime, 250, _T("%d %02d-%02d %02d:%02d:%02d.%03d"),
		SystemTime.wYear, 
		SystemTime.wMonth, 
		SystemTime.wDay, 
		SystemTime.wHour,
		SystemTime.wMinute,
		SystemTime.wSecond,
		SystemTime.wMilliseconds);


	of <<	_jF("[패치준비 시각] : %1%") % szCurrentTime ;
	of <<	_jF("[패치준비 작업자] : ") ;
	of <<	_jF("[패치완료시각] : ") ;
	of <<	_jF("\n\n\n") ;
	of <<	_jF("[참고사항]\n\t머지노트번호는 xxx부터 시작하세요.") ;
	of <<	_jF("\t머지하기전에 머지노트 파일명에 \"머지중\" 이라고 태그를 붙입시다.") ;
	of <<	_jF("\t머지가 끝나면 머지노트 파일명에 \"머지완료\" 라고 변경합시다.") ;

	return 0;

}


