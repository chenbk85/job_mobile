// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <assert.h>

#define JBASE_API 


#include "header/jHeader.h"

#include "Registry.h"
#include "Winperf.h"
#include "header/MemoryMap.h"
#include "header/jSyncObject.h"
#include "interface/jIPerfCounter.h"
using namespace nMech;



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#include "jPerfCounter.h"



extern cstr get_my_service_url(fname_t buf);