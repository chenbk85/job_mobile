// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// MonitorServer.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.
_xmlid_LIST(jxDEFINE);

var_enum(jCV_DEFINE);


#define BOOST_TEST_MODULE MonitorServer_DLL
nMech::tcstr g_szTestName =jTEXT(BOOST_TEST_MODULE);
#include "base/jTestUnit.h"
#include "base/VUTPPBind.h"

jIPlugIn_Server_IOCP *g_pCurrPlugIn=0;

void VCTESTPP_RunTest_Init()
{

}
namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(MonitorServer_DLL);
}
