/* file : test_Array.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-22 12:01:40
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"


void test_Array()
{
	SquirrelObject root = GetjISQ()->VM_GetRootTable();

	// === BEGIN Array Tests ===
	SquirrelObject array = GetjISQ()->VM_CreateArray(10);
	int i;
	for (i = 0; i < 10; i++) array.SetValue(i,i);
	array.ArrayAppend(123);          // int
	array.ArrayAppend(true);         // bool (must use bool and not SQBool (SQBool is treated as INT by compiler).
	array.ArrayAppend(false);        // bool (must use bool and not SQBool (SQBool is treated as INT by compiler).
	array.ArrayAppend(123.456f);     // float
	array.ArrayAppend(_T("string")); // string
	array.ArrayAppend(456);          // Will be popped and thrown away (below).
	array.ArrayAppend((SQUserPointer)0);

	// Pop 3 items from array:
	array.ArrayPop(SQFalse);                 // Don't retrieve the popped value (int:123).
	SquirrelObject so1 = array.ArrayPop();   // Retrieve the popped value.
	const SQChar * val1 = so1.ToString();      // Get string.
	float val2 = array.ArrayPop().ToFloat(); // Pop and get float.
	scprintf(_T("[Popped values] Val1: %s, Val2: %f\n"),val1,val2);

	int startIndex = array.Len();
	array.ArrayExtend(10); // Implemented as: ArrayResize(Len()+amount).
	for (i = startIndex; i < array.Len(); i++) array.SetValue(i,i*10);
	root.SetValue(_T("array"),array);

	SquirrelObject arrayr = array.Clone(); // Get a copy as opposed to another reference.
	arrayr.ArrayReverse();
	root.SetValue(_T("arrayr"),arrayr);

	// === END Array Tests ===

	SquirrelObject define_printArray = GetjISQ()->VM_CompileBuffer(_T(" \
			function printArray(name,array) \
			{ \
				print(name+\".len() = \"+array.len()); \
				foreach(i, v in array) if (v != null) \
				{ \
					if (typeof v == \"bool\") \
						v = v ? \"true\" : \"false\"; \
					print(\"[\"+i+\"]: \"+v); \
				} \
			} "));
	GetjISQ()->VM_RunScript(define_printArray);
	SquirrelObject test = GetjISQ()->VM_CompileBuffer(_T(" \
			printArray(\"array\",array); \
			printArray(\"arrayr\",arrayr); "));

	GetjISQ()->VM_RunScript(test);
	/* Ãâ·Â

	array.len() = 24
	[0]: 0
	[1]: 1
	[2]: 2
	[3]: 3
	[4]: 4
	[5]: 5
	[6]: 6
	[7]: 7
	[8]: 8
	[9]: 9
	[10]: 123
	[11]: true
	[12]: false
	[13]: 123.456
	[14]: 140
	[15]: 150
	[16]: 160
	[17]: 170
	[18]: 180
	[19]: 190
	[20]: 200
	[21]: 210
	[22]: 220
	[23]: 230

	arrayr.len() = 24
	[0]: 230
	[1]: 220
	[2]: 210
	[3]: 200
	[4]: 190
	[5]: 180
	[6]: 170
	[7]: 160
	[8]: 150
	[9]: 140
	[10]: 123.456
	[11]: false
	[12]: true
	[13]: 123
	[14]: 9
	[15]: 8
	[16]: 7
	[17]: 6
	[18]: 5
	[19]: 4
	[20]: 3
	[21]: 2
	[22]: 1
	[23]: 0

	*/

}

