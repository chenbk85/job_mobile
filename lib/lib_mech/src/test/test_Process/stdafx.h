// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#pragma comment(lib, "Psapi.lib")
//psapi.h MS에서 지원해주는 거임 2003은 그냥 컴파일되나 6.0은 SDK 설치 해야 됨..

#include "base/jBase.h"
using namespace nMech;
