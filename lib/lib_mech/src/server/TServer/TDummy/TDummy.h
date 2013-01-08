// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// AQMSG_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef AQMSG_EXPORTS
#define AQMSG_API __declspec(dllexport)
#else
#define AQMSG_API __declspec(dllimport)
#endif


#include "util/jUtil.h"
#include "util/jConsoleDLL.h"

#include "../TCommonServer/TCommonServer.h"
#include "../TCommonServer/csv_loader.h"

#include "../TCommonClient/protocal/PT_CentralServer_Enum.h"
using namespace nNET::nCentralServer;

#include "../TCommonClient/protocal/PT_CommandServer_Enum.h"
using namespace nNET::nCommandServer;

#include "../TCommonClient/protocal/PT_UserServer_Enum.h"
using namespace nNET::nUserServer;

#include "../TCommonClient/protocal/PT_DummyServer_Enum.h"
using namespace nNET::nDummyServer;

#define _xmlid_LIST(X)\
	X(TDummy)\

_xmlid_LIST(jxDECL);




#define var_enum(var_func)\
	var_func(jSERVER_NAME,DOMAIN_NAME, _T("TheOne"), 0 , "Server Cluster Name.(Seual ,Fuzhou ,Shanghi)")\


var_enum_ServerCommon(jCV_DECLARE);
var_enum(jCV_DECLARE);



// ����Ʈ����� �鿣�弭�� ��� include�ؾ���.
#include "../TCommonServer/define_code_BackEndServer.h"
#include "../TCommonServer/define_code_FrontEndServer.h"
#include "../TCommonServer/define_code_Server.h"
#include "../TCommonServer/define_code_PlugIn.h"

// console cmd .cpp���� �߰�����.
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
