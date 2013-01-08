#include "stdafx.h"
// exceptions_try_except_Statement.cpp

// Example of try-except and try-finally statements
#include <stdio.h>

#include <windows.h> // for EXCEPTION_ACCESS_VIOLATION

#include <excpt.h>

int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep) {

	puts("in filter.");

	if (code == EXCEPTION_ACCESS_VIOLATION) {

		puts("caught AV as expected.");

		return EXCEPTION_EXECUTE_HANDLER;

	}

	else {

		puts("didn't catch AV, unexpected.");

		return EXCEPTION_CONTINUE_SEARCH;

	};

}

int main_test_exception()

{

	int* p = 0x00000000;   // pointer to NULL

	puts("hello");

	__try{

		puts("in try");
asdfaasdf:
		__try{

			puts("in try");

			*p = 13;    // causes an access violation exception;

		}__finally{

			puts("in finally. termination: ");

			puts(AbnormalTermination() ? "\tabnormal" : "\tnormal");

#pragma warning(disable : 4532)
			goto asdfaasdf;
#pragma warning(default : 4532)

		}

	}__except(filter(GetExceptionCode(), GetExceptionInformation())){

		puts("in except");

	}

	puts("world");

	return 0;
}


