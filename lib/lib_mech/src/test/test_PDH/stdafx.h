// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
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
	TCHAR pCounterName[100]; // ī������ �̸��� ������ ����
	HCOUNTER hCounter; // ���� ī���� �����͸� ���� ����
} COUNTERSTRUCT;


// ���ÿ� 100�� �̻� ������ ���� ������?
#define COUNTER_MAX 100


extern DWORD gdwReturnPathSize;
void pdh_init(HWND hwnd, TCHAR *buff, DWORD buffsize);