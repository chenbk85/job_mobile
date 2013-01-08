/* file : test_Simple_Variable_binding.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-22 11:44:00
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"


void test_Simple_Variable_binding()
{
	SquirrelObject root = GetjISQ()->VM_GetRootTable();

	SquirrelObject main = GetjISQ()->VM_CompileBuffer(_T("\
							table1 <- {\
								key1=\"keyVal\",\
								key2 = 123\
							};\n\
							if (\"key1\" in table1)\n\
								print(\"Sq: Found it\");\n\
							else\n\
								print(\"Sq: Not found\");"));
	GetjISQ()->VM_RunScript(main);
	/* Ãâ·Â

	Sq: Found it
	*/

	SquirrelObject table1 = root.GetValue(_T("table1"));
	if (table1.Exists(_T("key1"))) {
		scprintf(_T("C++: Found it.\n"));
	} else {
		scprintf(_T("C++: Did not find it.\n"));
	} // if

	// === BEGIN Simple variable binding tests ===


	int iVar = 777;
	float fVar = 88.99f;
	bool bVar = true;
	BindVariable(root,&iVar,_T("iVar"));
	BindVariable(root,&fVar,_T("fVar"));
	BindVariable(root,&bVar,_T("bVar"));

	static ScriptStringVar128 testString;
	scsprintf(testString,_T("This is a test string"));
	BindVariable(root,&testString,_T("testString"));

	// === END Simple variable binding tests ===


}

