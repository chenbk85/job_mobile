// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// jXml.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.
_xmlid_LIST(jxDEFINE);


nMech::tcstr g_szTestName =_T("DefaultSuite_jXml");

#define BOOST_TEST_MODULE DefaultSuite_jXml
#include "base/jTestUnit.h"
#include "base/VUTPPBind.h"
#include "interface/xml/jIXml.h"

void VCTESTPP_RunTest_Init()
{
	//nMech::GetjIXml();

}
