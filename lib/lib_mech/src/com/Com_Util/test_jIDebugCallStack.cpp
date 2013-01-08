/* file : test_jIDebugCallStack.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-11 15:36:38
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTestUnit.h"
#include "interface/jIDebugCallStack.h"

using namespace nMech;
namespace 
{
	jTEST_SUITE_BEGIN(com_util)
	jTEST(jIDebugCallStack_test)
	{
		jCREATE_INTERFACE_AUTO(pDebugger, nMech::nUtil::nDebug::jIDebugCallStack);
		jCHECK(pDebugger);
		if(!pDebugger) return;
		pDebugger->Init();

#if 0
		int *p =0;
		*p =12334;
#endif

	}

	jTEST_SUITE_END(com_util)
}
