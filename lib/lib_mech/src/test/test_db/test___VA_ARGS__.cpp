/* file : test___VA_ARGS__.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-25 14:52:07
comp.: t3.co.kr
title : 
desc : 

*/
#include "stdafx.h"
// variadic_macros.cpp
#include <stdio.h>
#define EMPTY

#define CHECK1(x, ...) if (!(x)) { printf(__VA_ARGS__); }
#define CHECK2(x, ...) if ((x)) { printf(__VA_ARGS__); }
#define CHECK3(...) { printf(__VA_ARGS__); }
#define MACRO(s, ...) printf(s, __VA_ARGS__)

void main__VA_ARGS__() {
	CHECK1(0, "here %s %s %s", "are", "some", "varargs1(1)\n");
	CHECK1(1, "here %s %s %s", "are", "some", "varargs1(2)\n");   // won't print

	CHECK2(0, "here %s %s %s", "are", "some", "varargs2(3)\n");   // won't print
	CHECK2(1, "here %s %s %s", "are", "some", "varargs2(4)\n");

	// always invokes printf in the macro
	CHECK3("here %s %s %s", "are", "some", "varargs3(5)\n");

	MACRO("hello, world\n");
	// MACRO("error\n", EMPTY);   would cause C2059
}

