// intrinsics_readwritebarrier.c
// compile with: /O2 -DNO_BARRIER
// This code contains an error--dereferencing a null pointer--
// which will be optimized away as a useless assignment.
// Omit the NO_BARRIER command line to activate the Write Barrier.
// With the barrier activated, the assignment is not optimized away
// and causes an access violation.
#include "stdafx.h"
#include <windows.h> // for EXCEPTION_ACCESS_VIOLATION
#include <excpt.h>
#include <stdio.h>
#include <intrin.h>

#pragma intrinsic(_ReadWriteBarrier)

int x = 0;
//#define NO_BARRIER
__declspec(noinline) int f(int* p)
{
	x = *p; //ȣ��ȵ� ����ȭ!
	x = 7; //ȣ��ȵ� ����ȭ!
	x = 3; // ȣ���.
	return x;
}
__declspec(noinline) int f1(int* p)
{
	x = *p; //ȣ��ȵ� ����ȭ!
	x = 11; // ȣ�� �ȵ�.
	x = 7; // ȣ���
	_ReadWriteBarrier();
	x = 33; //ȣ�� �ȵ�.
	x = 3; // ȣ���.
	return x;
}
__declspec(noinline) int f3(int* p)
{
	x = *p; //ȣ��ȵ� ����ȭ!
	x = 11; // ȣ�� �ȵ�.
	x = 7; // ȣ���
	_ReadWriteBarrier();
	x = 31; //ȣ���
	_ReadWriteBarrier();
	x = 32; // ȣ��ȵ�.
	x = 33; // ȣ���.
	return x;
}
__declspec(noinline) int f5(volatile int* p)
{
	x = 11; // ȣ�� �ȵ�.
	x = 7; // ȣ�� �ȵ�.
	x = 31; // ȣ�� �ȵ�.
	x = *p; //ȣ���
	x = 32; // ȣ��ȵ�.
	x = 33; // ȣ���.
	return x;
}

__declspec(noinline)  int volatile f7(volatile int* p)
{
	x = 11; //ȣ�� �ȵ�.
	x = 7; // ȣ�� �ȵ�.
	x = 31; // ȣ�� �ȵ�.
	x = *p; //ȣ���
	x = 32; // ȣ�� �ȵ�.
	x = 33; // ȣ���.
	return x;
}

volatile int y = 0;
__declspec(noinline) int f6(volatile int* p)
{
	y = 11; //ȣ���
	y = 7; // ȣ���.
	y = 31; // ȣ���
	y = *p; //ȣ���
	y = 32; // ȣ���
	y = 33; // ȣ���.
	return y;
}

__declspec(noinline) int g(int* p)
{
	x = *p; //ȣ��ȵ�.
	_ReadWriteBarrier();
	x = 3; // ȣ���.
	return x;
}

// If code is EXCEPTION_ACCESS_VIOLATION it means an
// attempt to read from the NULL pointer we passed in, so
// we handle the exception.
int filter_readwritebarrier(unsigned int code, struct _EXCEPTION_POINTERS *ep)
{
	if (code == EXCEPTION_ACCESS_VIOLATION)
	{
		printf_s("AV\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// If not what we were looking for, we don't want to handle it.
	return EXCEPTION_CONTINUE_SEARCH;
}

int main_readwritebarrier()
{
	int nRet = 0;

	__try
	{
		// Should return only if the first assignment is
		// optimized away.
		int asdf=1;
		nRet = f(&asdf);
		printf_s("Assignment was optimized away!\n");
	}
	__except(filter_readwritebarrier(GetExceptionCode(), GetExceptionInformation()))
	{
		// We get here if an Access violation occurred.
		printf_s("Access Violation: assignment was not optimized away.\n");
	}
	return 1;
}

