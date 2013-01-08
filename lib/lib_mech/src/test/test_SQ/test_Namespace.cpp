/* file : test_Namespace.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 12:49:09
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"



// You can add functions/vars here, as well as bind globals to be accessed through this class as shown in the NameSpace example.
// If the class is instantiated in script, the instance is "locked", preventing accidental changes to elements.
// Thus using an instance as the namespace can be a better design for development.
// If variables/constants are bound to the class and/or non-static/non-global functions, the class must be instantiated before use.

struct NamespaceClass 
{
};

// === END Class Instance Test ===
extern void globalFunc(const SQChar * s,int val) ;




//--------------------------------------------------------------------------
void test_Namespace()
//--------------------------------------------------------------------------
{
	HSQUIRRELVM v = GetjISQ()->VM_GetVMPtr();
	SquirrelObject root = GetjISQ()->VM_GetRootTable();

	// === BEGIN Namespace examples ===

	// Create a namespace using a table.
	SquirrelObject nameSpaceTable = GetjISQ()->VM_CreateTable();
	root.SetValue(_T("Namespace1"),nameSpaceTable);
	Register(v,nameSpaceTable.GetObjectHandle(),globalFunc,_T("namespaceFunc"));

	// Create a namespace using a class. If an instance is created from the class, using the instance will prevent accidental changes to the instance members.
	// Using the class/instance form also allows extra information to be added to the proxy class, if desired (such as vars/funcs).
	// NOTE: If any variables/static-variables/constants are registered to the class, it must be instantiated before use.
	SQClassDef<NamespaceClass>(_T("Namespace2")).
		staticFunc(globalFunc,_T("namespaceFunc"));

	SquirrelObject testNameSpace = GetjISQ()->VM_CompileBuffer(_T("\
												Namespace1.namespaceFunc(\"Hello Namespace1 (table),\",321); \n\
												Namespace2.namespaceFunc(\"Hello Namespace2 (class),\",654); \n\
												local Namespace3 = Namespace2(); \n\
												Namespace3.namespaceFunc(\"Hello Namespace3 (instance),\",987); \n\
										"));

	GetjISQ()->VM_RunScript(testNameSpace);

	// === END Namespace examples ===

}

