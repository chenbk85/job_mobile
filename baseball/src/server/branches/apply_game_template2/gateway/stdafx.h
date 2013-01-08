
#include <boost/bind.hpp>
#ifndef jEXCEL_SERVER_SIDE_CODE
#define jEXCEL_SERVER_SIDE_CODE
#endif

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "common/header/jHeader.h"
#include "common/jILog.h"
#include "excel/db_type.h"
#include "excel/excel_all.h"
#include "common/jILog.h"
#include "protoHelper.h"


#include "protocol/ug.pb.h"
#include "../game/proto.h"
#include "DBHelper.h"
#include "baseball_db_interface.h"
#include "gateway/database.hpp"
#include <gateway/gateway.hpp>
#include "../game/dump.h"


#include "nDB.h"
#include "nREDIS.h"
#include "nMOB.h"
#include "nBASE_BALL.h"




#include "jUser.h"

using namespace std;
using namespace MSG;



#define OUT
#define IN
#define INOUT




#define jRETURN_ERROR_ret(ret, vaild_val, _ERROR_STRING)\
{\
	if (false == (vaild_val) )\
	{\
	jMAKE_PACKET_ans_ug_error(_ERROR_STRING);\
	return ret;\
	}\
}\

#define jAAA() \
do { int a = 0; a++; } while(0)


