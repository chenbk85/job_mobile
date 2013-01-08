// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "header/jDefine.h"

#include <windows.h>
#include <pdh.h>
#include <pdhmsg.h>
#include <tchar.h>
#include <stdio.h>

#include "base\\jBase.h"
#include "common/jCommon.h"
#include "common/jInit.h"

using namespace nMech;


extern std::vector<TCHAR> gszReturnPath;

#define BUFFER_INCREMENT_SIZE 100
#define INIT_RETURNPATH_SIZE 100
extern HQUERY hQuery;
extern PDH_BROWSE_DLG_CONFIG pdhconf;

typedef struct
{
	TCHAR pCounterName[100]; // 카운터의 이름을 저장할 변수
	HCOUNTER hCounter; // 실제 카운터 데이터를 담을 변수
} COUNTERSTRUCT;


// 동시에 100개 이상 관찰할 일이 있을까?
#define COUNTER_MAX 100


extern DWORD gdwReturnPathSize;
void pdh_init(HWND hwnd, TCHAR *buff, DWORD buffsize);