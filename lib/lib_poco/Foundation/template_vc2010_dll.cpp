// template_vc2010_dll.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "template_vc2010_dll.h"


// ������ ������ �����Դϴ�.
TEMPLATE_VC2010_DLL_API int ntemplate_vc2010_dll=0;

// ������ �Լ��� �����Դϴ�.
TEMPLATE_VC2010_DLL_API int fntemplate_vc2010_dll(void)
{
	return 42;
}

// ������ Ŭ������ �������Դϴ�.
// Ŭ���� ���Ǹ� ������ template_vc2010_dll.h�� �����Ͻʽÿ�.
Ctemplate_vc2010_dll::Ctemplate_vc2010_dll()
{
	return;
}
