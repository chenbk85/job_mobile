// BCommonClient.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "BCommonClient.h"


// ������ ������ �����Դϴ�.
BCOMMONCLIENT_API int nBCommonClient=0;

// ������ �Լ��� �����Դϴ�.
BCOMMONCLIENT_API int fnBCommonClient(void)
{
	return 42;
}

// ������ Ŭ������ �������Դϴ�.
// Ŭ���� ���Ǹ� ������ BCommonClient.h�� �����Ͻʽÿ�.
CBCommonClient::CBCommonClient()
{
	return;
}
