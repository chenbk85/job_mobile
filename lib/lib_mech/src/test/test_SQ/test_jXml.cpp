/* file : test_jXml.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-07 18:10:15
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "interface/xml/jIXml.h"
using namespace std;
#include "base/jSQ_bind.h"

SquirrelObject asdfnewtestR1(HSQUIRRELVM v) 
{
	StackHandler sa(v);
	fname_t buf;
	jt_sprintf(buf, _T("asdfasdf %s %d"),_T("1234asdf"),234);
	return buf;
	//return sa.Return(obj);
	//return net_string256(buf);
}


void test_jXml()
{
	HSQUIRRELVM v = GetjISQ()->VM_GetVMPtr();

	RegisterGlobal(v,asdfnewtestR1,_T("asdfnewtestR1"));


	nFileSystem::jFolder dir;
	fname_t buf;
	GetCurrentDirectory(sizeof(buf), buf );
	if( dir.Is_Exist(_T("xml\\test\\test_sq.nut") ) )
	{
		SquirrelObject testRegConstant = GetjISQ()->VM_CompileScript(_T("xml\\test\\test_sq.nut"));
		GetjISQ()->VM_RunScript(testRegConstant);

	}

	

}

	