// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일입니다.
#include <windows.h>

#define NOT_USE_JCGAME_MEMORY_MANAGER
/* *_* by icandoit : 2006-05-15 15:32:12

#include "jc\platform.h"
#define USE_NEWPOOL
#include <jc\jcMemoryManager.h>
*/ //*_* by icandoit : 2006-05-15 15:32:13


#include "common/jCommon.h"
#include <set>
#include "jc\\smartptr.h"
#include "interface\\jIPak.h"
#include "jc\\IStreamEngine.h"


using namespace std;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
