
#include "util/jUtil.h"
#include "util/jConsoleDLL.h"


#include "../TCommonServer/TCommonServer.h"

#include "../TCommonServer/csv_loader.h"

#include "../TCommonClient/protocal/PT_CentralServer_Enum.h"
using namespace nNET::nCentralServer;

#include "../TCommonClient/protocal/PT_CommandServer_Enum.h"
using namespace nNET::nCommandServer;



#define _xmlid_LIST(X)\
	X(TCentral)\

_xmlid_LIST(jxDECL);



#define var_enum(var_func)\
	var_func(jSERVER_NAME,DOMAIN_NAME, _T("TheOne"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\
	var_func(jSERVER_NAME,LOG_FILE_CHANGE_MINITE, 720.f, 0,"log file rename time (minite)")\
	var_func(jSERVER_NAME,C2_USER_CONNECTION_NOTIFY, 3.0f, 0,"server user tot count notify time (sec)")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);




// 프론트엔드와 백엔드서버 모두 include해야함.
#include "../TCommonServer/define_code_BackEndServer.h"
#include "../TCommonServer/define_code_FrontEndServer.h"
#include "../TCommonServer/define_code_Server.h"
#include "../TCommonServer/define_code_PlugIn.h"

// console cmd .cpp에만 추가하자.
#include "../TCommonServer/define_code_jIConsoleCmd.h"


#include "PlugIn_Server.h"
#include "PlugIn_Connect.h"


//--------------------------------------------------------------------------
class T_NetDLL : public nCONSOLE::jConsoleDLL_Net
	//--------------------------------------------------------------------------
{
public:
	jINTERFACE_HEADER(jIConsoleDLL);

};

extern T_NetDLL* g_pjConsoleDLL;

