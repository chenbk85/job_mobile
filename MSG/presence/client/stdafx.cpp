// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// template_vc2010_dll.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.

#define BOOST_TEST_MODULE MSG_presence_dummy
nMech::tcstr g_szTestName =jTEXT(BOOST_TEST_MODULE);
#include "base/jTestUnit.h"
#include "base/VUTPPBind.h"

void VCTESTPP_RunTest_Init()
{

}
namespace nMech
{
  StringID g_Current_LogLevel_jStringID = jx(MSG_presence_dummy);
}

