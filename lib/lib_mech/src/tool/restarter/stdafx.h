// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "header/jDefine.h"
#include "header/jTypedef_type.h"
#include "header/jTCHAR_util.h"
using namespace nMech;
void kill_Process_byID(DWORD kill_id);
void kill_Process_byName(tcstr strProcessName,DWORD skip_id);
bool Is_Exist(cstr sz);

typedef void for_each_folder_function_t(tcstr szFile,void*);
void for_each_folder( tcstr szPath,for_each_folder_function_t* func ,void* v);
