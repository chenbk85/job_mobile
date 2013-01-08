// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include <stdio.h>

#ifdef DEF_WINDOWS
#include <tchar.h>
#endif


//--------------------------------------------------------------------------
// MOB_lib
//--------------------------------------------------------------------------
#include "MOB_net_define.h"

//--------------------------------------------------------------------------
// google proto buf
//--------------------------------------------------------------------------

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "protobuf/gameLogic.pb.h"
#include "protobuf/game.pb.h"
#include "protobuf/ug.pb.h"

#include "SAMPLE_Plugin_Connection.h"
#include "SAMPLE_Plugin_NetIOModel.h"
