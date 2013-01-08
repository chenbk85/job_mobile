
#pragma once

#include <stdio.h>

#ifdef DEF_WINDOWS
#include <tchar.h>
#endif


//--------------------------------------------------------------------------
// MOB_lib
//--------------------------------------------------------------------------
#include <boost/bind.hpp>
#include "MOB_net_define.h"

//--------------------------------------------------------------------------
// google proto buf
//--------------------------------------------------------------------------
#include "jILog.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "protobuf/gameLogic.pb.h"
#include "protobuf/game.pb.h"
#include "protobuf/ug.pb.h"
#include "excel/db_type.h"
#include "excel/excel_code_util.h"
#include "excel/excel_all.h"

#include "BB_Plugin_Connection.h"
#include "BB_Plugin_NetIOModel.h"
