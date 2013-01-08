// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "header/jDefine.h"
#include "header/jTypedef_type.h"
#include "header/jTCHAR_util.h"
using namespace nMech;
void kill_Process_byID(DWORD kill_id);
void kill_Process_byName(tcstr strProcessName,DWORD skip_id);
bool Is_Exist(cstr sz);

typedef void for_each_folder_function_t(tcstr szFile,void*);
void for_each_folder( tcstr szPath,for_each_folder_function_t* func ,void* v);
