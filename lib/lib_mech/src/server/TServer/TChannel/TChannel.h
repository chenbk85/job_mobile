// 다음 ifdef 블록은 DLL에서 내보내기하는 작업을 쉽게 해 주는 매크로를 만드는 
// 표준 방식입니다. 이 DLL에 들어 있는 파일은 모두 명령줄에 정의된 _EXPORTS 기호로
// 컴파일되며, 동일한 DLL을 사용하는 다른 프로젝트에서는 이 기호를 정의할 수 없습니다.
// 이렇게 하면 소스 파일에 이 파일이 들어 있는 다른 모든 프로젝트에서는 
// AQTOWN_API 함수를 DLL에서 가져오는 것으로 보고, 이 DLL은
// 이 DLL은 해당 매크로로 정의된 기호가 내보내지는 것으로 봅니다.
#ifdef AQTOWN_EXPORTS
#define AQTOWN_API __declspec(dllexport)
#else
#define AQTOWN_API __declspec(dllimport)
#endif


#include "util/jUtil.h"
#include "util/jConsoleDLL.h"


#include "../TCommonServer/TCommonServer.h"
#include "../TCommonServer/csv_loader.h"
#include "../TCommonServer/jXmlSaveManager.h"

#include "../TCommonClient/protocal/PT_CentralServer_Enum.h"
using namespace nMech::nNET::nCentralServer;
#include "../TCommonClient/protocal/PT_CommandServer_Enum.h"
using namespace nMech::nNET::nCommandServer;
#include "../TCommonClient/protocal/PT_UserServer_Enum.h"
using namespace nMech::nNET::nUserServer;

#include "../TCommonClient/protocal/PT_DBCacheServer_Enum.h"
using namespace nMech::nNET::nDBCacheServer;
#include "../TCommonClient/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;
#include "../TCommonClient/protocal/PT_DBCacheServer_Enum.h"
using namespace nMech::nNET::nDBCacheServer;

#include "../TCommonClient/protocal/PT_LoginServer_Enum.h"
using namespace nMech::nNET::nLoginServer;
#include "../TCommonClient/protocal/PT_ChannelServer_Enum.h"
using namespace nMech::nNET::nChannelServer;


// 프론트엔드와 백엔드서버 모두 include해야함.
#include "../TCommonServer/define_code_BackEndServer.h"
#include "../TCommonServer/define_code_FrontEndServer.h"
#include "../TCommonServer/define_code_Server.h"
#include "../TCommonServer/define_code_PlugIn.h"

//front end server에서 클라이언트 컨넥션 관련 코드.
#include "../TCommonServer/define_code_ToClient.h"

// console cmd .cpp에만 추가하자.
#include "../TCommonServer/define_code_jIConsoleCmd.h"

#include "jPlayerObj.h"
#include "../TCommonServer/jGridNode_Client.h"

#include "PlugIn_Connect.h"
#include "PlugIn_Server.h"




#define _xmlid_LIST(X)\
	X(TChannel)\

_xmlid_LIST(jxDECL);




#define var_enum(var_func)\
	var_func(jSERVER_NAME,DOMAIN_NAME, _T("Fuzhou"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\
	var_func(jSERVER_NAME,C4_USER_CONNECTION_NOTIFY, 3.0f, 0 , "C4_USER_CONNECTION_NOTIFY send term (sec)")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);


bool jCheck_ObjName(wcstr szName);

//이름이 규칙에 어긋납니다. 두자 이상!
#define pUser_Check_make_name(name)\
	if(!jCheck_ObjName(name))\
{\
	pS_eSEND_jError_ToClient(T,SR_t(OBJ_NAME_LEN_ERROR),CR_t(jCheck_ObjName));\
	return;\
}\



#define jUSER_ERROR_CHECK(condition,SR,CR) if((condition)){	pS_eSEND_jError_ToClient(T,SR_t(SR),CR_t(CR));	return;		}


//--------------------------------------------------------------------------
class T_NetDLL : public nCONSOLE::jConsoleDLL_Net
	//--------------------------------------------------------------------------
{
public:
	jINTERFACE_HEADER(jIConsoleDLL);

};

extern T_NetDLL* g_pjConsoleDLL;
