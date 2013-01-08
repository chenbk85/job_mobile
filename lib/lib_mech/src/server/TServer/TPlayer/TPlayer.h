// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// TESTCLIENT_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
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



// ����Ʈ����� �鿣�弭�� ��� include�ؾ���.
//#include "../TCommonServer/define_code_BackEndServer.h"
#include "../TCommonServer/define_code_FrontEndServer.h"
//#include "../TCommonServer/define_code_Server.h"
#include "../TCommonServer/define_code_PlugIn.h"

//front end server���� Ŭ���̾�Ʈ ���ؼ� ���� �ڵ�.
#include "../TCommonServer/define_code_ToClient.h"


// console cmd .cpp���� �߰�����.
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
	func(Dummy,DummyCount,50,0,"�⺻ ����Ŭ���̾�Ʈ ���� ����")\
	func(Dummy,DefaultLoginIP,_T("127.0.0.1"), 0,"�⺻ ����(�α�)���� IP")\
	func(Dummy,DefaultLoginPort,3002,0,"�⺻ �α����� ��Ʈ")\
	func(jSERVER_NAME,DEFAULT_LOGIN_IP,_T("50.10.125.119:3002"),0,"SamGame.exe���� ����Ʈ ����IP")\
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

