// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// LowLib.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.


_xmlid_LIST(jxDEFINE);

var_enum(jCV_DEFINE);


namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(jNet_DLL); // �ش� DLL ,EXE ��⸶�� �����صξ����.

}


nMech::tcstr g_szTestName =_T("DefaultSuite_jINet_OGS");

#define BOOST_TEST_MODULE DefaultSuite_jINet_OGS
#include "base/jTestUnit.h"
#include "base/VUTPPBind.h"
#include "interface/xml/jIXml.h"

void VCTESTPP_RunTest_Init()
{
	//nMech::GetjIXml();

}
