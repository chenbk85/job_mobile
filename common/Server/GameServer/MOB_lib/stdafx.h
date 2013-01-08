
#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#ifdef DEF_WINDOWS
#include <tchar.h>
#else
#define _T(X) X
#endif

#include "jILog.h"
