// 다음 ifdef 블록은 DLL에서 내보내기하는 작업을 쉽게 해 주는 매크로를 만드는 
// 표준 방식입니다. 이 DLL에 들어 있는 파일은 모두 명령줄에 정의된 _EXPORTS 기호로
// 컴파일되며, 동일한 DLL을 사용하는 다른 프로젝트에서는 이 기호를 정의할 수 없습니다.
// 이렇게 하면 소스 파일에 이 파일이 들어 있는 다른 모든 프로젝트에서는 
// TESTCLIENT_API 함수를 DLL에서 가져오는 것으로 보고, 이 DLL은
// 이 DLL은 해당 매크로로 정의된 기호가 내보내지는 것으로 봅니다.
#ifdef TESTCLIENT_EXPORTS
#define TESTCLIENT_API __declspec(dllexport)
#else
#define TESTCLIENT_API __declspec(dllimport)
#endif


#include "util/jUtil.h"
#include "util/jConsoleDLL.h"

#include "../TCommonServer/TCommonServer.h"
#include "../TCommonServer/csv_loader.h"
#include "../TCommonServer/jXmlSaveManager.h"

#include "../TCommonClient/protocal/PT_LoginServer_Enum.h"
using namespace nMech::nNET::nLoginServer;
#include "../TCommonClient/protocal/PT_ChannelServer_Enum.h"
using namespace nMech::nNET::nChannelServer;
#include "../TCommonClient/protocal/PT_GameServer_Enum.h"
using namespace nMech::nNET::nGameServer;
#include "../TCommonClient/protocal/PT_DummyServer_Enum.h"
using namespace nNET::nDummyServer;



// 프론트엔드와 백엔드서버 모두 include해야함.
//#include "../TCommonServer/define_code_BackEndServer.h"
#include "../TCommonServer/define_code_FrontEndServer.h"
//#include "../TCommonServer/define_code_Server.h"
#include "../TCommonServer/define_code_PlugIn.h"

//front end server에서 클라이언트 컨넥션 관련 코드.
#include "../TCommonServer/define_code_ToClient.h"


// console cmd .cpp에만 추가하자.
#include "../TCommonServer/define_code_jIConsoleCmd.h"

#include "../TCommonServer/jGridNode_Client.h"


#include "jPlayerObj.h"
#include "jNetClient.h"
#include "jPlayerList_Dummy.h"

//#include "PlugIn_Server.h"
#include "PlugIn_Connect.h"

#define _xmlid_LIST(X)\
	X(TPlayer)\

_xmlid_LIST(jxDECL);


#define var_enum(func)\
	func(Dummy,TEST_ID_START_NUM,500,0,"Test Account start number")\
	func(Dummy,DummyCount,50,0,"기본 더미클라이언트 세션 갯수")\
	func(Dummy,DefaultLoginIP,_T("127.0.0.1"), 0,"기본 세션(로긴)접속 IP")\
	func(Dummy,DefaultLoginPort,3002,0,"기본 로긴접속 포트")\
	func(jSERVER_NAME,DEFAULT_LOGIN_IP,_T("50.10.125.119:3002"),0,"SamGame.exe에서 디펄트 접속IP")\
	func(jSERVER_NAME,DOMAIN_NAME, _T("Client"), 0 , "Server Cluster Name.  not use in clinet")\

var_enum(jCV_DECLARE);


#define jDELAY(i) if(i>per_user){if(delay_msec)Sleep(delay_msec);i=0;}



//--------------------------------------------------------------------------
class T_NetDLL : public nCONSOLE::jConsoleDLL_Net
	//--------------------------------------------------------------------------
{
public:
	jINTERFACE_HEADER(jIConsoleDLL);

};

extern T_NetDLL* g_pjConsoleDLL;

