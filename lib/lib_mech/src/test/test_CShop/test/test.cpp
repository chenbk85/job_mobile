// test.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

#import "mscorlib.tlb"
#import "../CShopUtil/CShopUtil.tlb" no_namespace  


int main(int argc, char* argv[])
{
	// Make the primary thread enter an STA
	::CoInitialize(NULL);

	HRESULT hr = S_OK;
	ITestComPtr pIT = 0;
	hr = pIT.CreateInstance(__uuidof(TestCom));
	if(pIT)
		pIT->DisplayCurrentTemperature();

	return 0;

}

